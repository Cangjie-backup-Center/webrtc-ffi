/**
 * Copyright (c) Huawei Technologies Co., Ltd. 2024-2025. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "peer_connection_factory.h"

#include "api/audio_codecs/builtin_audio_decoder_factory.h"
#include "api/audio_codecs/builtin_audio_encoder_factory.h"
#include "api/create_peerconnection_factory.h"
#include "api/scoped_refptr.h"
#include "rtc_base/physical_socket_server.h"

#include "media_track_constraints.h"
#include "audio_device/ohos_audio_device_module.h"
#include "audio_device/ohos_local_audio_source.h"
#include "camera/camera_enumerator.h"
#include "camera/camera_capturer.h"
#include "screen_capture/screen_capturer.h"
#include "video/video_track_source.h"
#include "user_media/media_constraints_util.h"
#include "ffi_video_encoder_factory.h"
#include "ffi_video_decoder_factory.h"
#include "render/egl_env.h"

namespace webrtc {

std::mutex PeerConnectionFactoryWrapper::mutex_;
std::shared_ptr<PeerConnectionFactoryWrapper> PeerConnectionFactoryWrapper::defaultFactory_;

std::shared_ptr<PeerConnectionFactoryWrapper> PeerConnectionFactoryWrapper::GetDefault()
{
    UNUSED std::lock_guard<std::mutex> lock(mutex_);
    if (!defaultFactory_) {
        defaultFactory_ = std::make_shared<PeerConnectionFactoryWrapper>();
        if (!defaultFactory_->Init(nullptr, nullptr, nullptr, nullptr)) {
            defaultFactory_.reset();
        }
    }

    return defaultFactory_;
}

void PeerConnectionFactoryWrapper::SetDefault(std::shared_ptr<PeerConnectionFactoryWrapper> wrapper)
{
    UNUSED std::lock_guard<std::mutex> lock(mutex_);
    defaultFactory_ = wrapper;
}

std::shared_ptr<PeerConnectionFactoryWrapper> PeerConnectionFactoryWrapper::Create(
    rtc::scoped_refptr<OhosAudioDeviceModule> adm, std::unique_ptr<VideoEncoderFactory> videoEncoderFactory,
    std::unique_ptr<VideoDecoderFactory> videoDecoderFactory, rtc::scoped_refptr<AudioProcessing> audioProcessing)
{
    auto wrapper = std::make_shared<PeerConnectionFactoryWrapper>();
    if (!wrapper->Init(adm, std::move(videoEncoderFactory), std::move(videoDecoderFactory), audioProcessing)) {
        return nullptr;
    }
    return wrapper;
}

rtc::scoped_refptr<OhosAudioDeviceModule> PeerConnectionFactoryWrapper::GetAudioDeviceModule() const
{
    return adm_;
}

rtc::scoped_refptr<OhosLocalAudioSource> PeerConnectionFactoryWrapper::CreateAudioSource(
    const cricket::AudioOptions& options, std::shared_ptr<AudioInput> audioInput)
{
    return adm_->CreateAudioSource(options, std::move(audioInput));
}

rtc::scoped_refptr<OhosVideoTrackSource> PeerConnectionFactoryWrapper::CreateVideoSource(
    std::unique_ptr<VideoCapturer> capturer)
{
    return OhosVideoTrackSource::Create(std::move(capturer), signalingThread_.get(),
                                        EglEnv::GetDefault().GetContext());
}

rtc::scoped_refptr<AudioTrackInterface> PeerConnectionFactoryWrapper::CreateAudioTrack(
    const std::string& label, rtc::scoped_refptr<OhosLocalAudioSource> source)
{
    if (!source) {
        return nullptr;
    }

    auto track = pcFactory_->CreateAudioTrack(label, source.get());
    if (!track) {
        return nullptr;
    }

    audioSources_[track] = source;
    return track;
}

rtc::scoped_refptr<VideoTrackInterface> PeerConnectionFactoryWrapper::CreateVideoTrack(
    const std::string& label, rtc::scoped_refptr<OhosVideoTrackSource> source)
{
    if (!source) {
        return nullptr;
    }

    auto track = pcFactory_->CreateVideoTrack(source, label);
    if (!track) {
        return nullptr;
    }

    videoSources_[track] = source;
    return track;
}

rtc::scoped_refptr<OhosLocalAudioSource> PeerConnectionFactoryWrapper::GetAudioSource(
    rtc::scoped_refptr<MediaStreamTrackInterface> track) const
{
    auto it = audioSources_.find(track);
    if (it == audioSources_.end()) {
        return nullptr;
    }
    return it->second;
}

rtc::scoped_refptr<OhosVideoTrackSource> PeerConnectionFactoryWrapper::GetVideoSource(
    rtc::scoped_refptr<MediaStreamTrackInterface> track) const
{
    auto it = videoSources_.find(track);
    if (it == videoSources_.end()) {
        return nullptr;
    }
    return it->second;
}

void PeerConnectionFactoryWrapper::RemoveAudioSource(rtc::scoped_refptr<MediaStreamTrackInterface> track)
{
    audioSources_.erase(track);
}

void PeerConnectionFactoryWrapper::RemoveVideoSource(rtc::scoped_refptr<MediaStreamTrackInterface> track)
{
    videoSources_.erase(track);
}

bool PeerConnectionFactoryWrapper::Init(
    rtc::scoped_refptr<OhosAudioDeviceModule> adm, std::unique_ptr<VideoEncoderFactory> videoEncoderFactory,
    std::unique_ptr<VideoDecoderFactory> videoDecoderFactory, rtc::scoped_refptr<AudioProcessing> audioProcessing)
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    rtc::ThreadManager::Instance()->WrapCurrentThread();

    auto socketServer = std::make_unique<rtc::PhysicalSocketServer>();
    auto networkThread = std::make_unique<rtc::Thread>(socketServer.get());
    networkThread->SetName("network_thread", nullptr);
    if (!networkThread->Start()) {
        RTC_LOG(LS_ERROR) << "Failed to start network thread";
        return false;
    }

    auto workerThread = rtc::Thread::Create();
    workerThread->SetName("worker_thread", nullptr);
    if (!workerThread->Start()) {
        RTC_LOG(LS_ERROR) << "Failed to start worker thread";
        return false;
    }

    auto signalingThread = rtc::Thread::Create();
    signalingThread->SetName("signaling_thread", NULL);
    if (!signalingThread->Start()) {
        RTC_LOG(LS_ERROR) << "Failed to start signaling thread";
        return false;
    }

    if (!adm) {
        adm = CreateDefaultAudioDeviceModule();
    }

    pcFactory_ = CreatePeerConnectionFactory(
        networkThread.get(), workerThread.get(), signalingThread.get(), adm, CreateBuiltinAudioEncoderFactory(),
        CreateBuiltinAudioDecoderFactory(),
        videoEncoderFactory ? std::move(videoEncoderFactory) : CreateDefaultVideoEncoderFactory(),
        videoDecoderFactory ? std::move(videoDecoderFactory) : CreateDefaultVideoDecoderFactory(),
        nullptr /* audio_mixer */, audioProcessing);

    if (!pcFactory_) {
        RTC_LOG(LS_ERROR) << "Failed to create PeerConnectionFactory";
        return false;
    }

    adm_ = adm;
    socketServer_ = std::move(socketServer);
    networkThread_ = std::move(networkThread);
    workerThread_ = std::move(workerThread);
    signalingThread_ = std::move(signalingThread);

    return true;
}

} // namespace webrtc
