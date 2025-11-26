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

#ifndef WEBRTC_PEER_CONNECTION_FACTORY_H
#define WEBRTC_PEER_CONNECTION_FACTORY_H

#include "video/video_track_source.h"
#include "audio_device/ohos_audio_device_module.h"

#include <memory>
#include <mutex>

#include "api/peer_connection_interface.h"
//#include "rtc_base/socket_server.h"

namespace webrtc {

class PeerConnectionFactoryWrapper : public std::enable_shared_from_this<PeerConnectionFactoryWrapper> {
public:
    static std::shared_ptr<PeerConnectionFactoryWrapper> GetDefault();

    static void SetDefault(std::shared_ptr<PeerConnectionFactoryWrapper> wrapper);

    static std::shared_ptr<PeerConnectionFactoryWrapper> Create(
        rtc::scoped_refptr<OhosAudioDeviceModule> adm = nullptr,
        std::unique_ptr<VideoEncoderFactory> videoEncoderFactory = nullptr,
        std::unique_ptr<VideoDecoderFactory> videoDecoderFactory = nullptr,
        rtc::scoped_refptr<AudioProcessing> audioProcessing = nullptr);

    // Do not use this constructor directly, use 'Create' above.
    PeerConnectionFactoryWrapper() = default;

    PeerConnectionFactoryInterface* GetFactory()
    {
        return pcFactory_.get();
    }

    rtc::SocketServer* GetSocketServer()
    {
        return socketServer_.get();
    }

    rtc::Thread* GetNetworkThread()
    {
        return networkThread_.get();
    }

    rtc::Thread* GetSignalingThread()
    {
        return signalingThread_.get();
    }

    rtc::Thread* GetWorkerThread()
    {
        return workerThread_.get();
    }

    rtc::scoped_refptr<OhosAudioDeviceModule> GetAudioDeviceModule() const;

    // Create audio/video source and save to cache
    rtc::scoped_refptr<OhosLocalAudioSource>
    CreateAudioSource(const cricket::AudioOptions& options, std::shared_ptr<AudioInput> audioInput = nullptr);
    rtc::scoped_refptr<OhosVideoTrackSource> CreateVideoSource(std::unique_ptr<VideoCapturer> capturer);

    // Create audio/video track
    rtc::scoped_refptr<AudioTrackInterface>
    CreateAudioTrack(const std::string& label, rtc::scoped_refptr<OhosLocalAudioSource> source);
    rtc::scoped_refptr<VideoTrackInterface>
    CreateVideoTrack(const std::string& label, rtc::scoped_refptr<OhosVideoTrackSource> source);

    // Get audio/video source from cache
    rtc::scoped_refptr<OhosLocalAudioSource> GetAudioSource(rtc::scoped_refptr<MediaStreamTrackInterface> track) const;
    rtc::scoped_refptr<OhosVideoTrackSource> GetVideoSource(rtc::scoped_refptr<MediaStreamTrackInterface> track) const;

    // Remove audio/video source from cache
    void RemoveAudioSource(rtc::scoped_refptr<MediaStreamTrackInterface> track);
    void RemoveVideoSource(rtc::scoped_refptr<MediaStreamTrackInterface> track);

protected:
    bool Init(
        rtc::scoped_refptr<OhosAudioDeviceModule> adm, std::unique_ptr<VideoEncoderFactory> videoEncoderFactory,
        std::unique_ptr<VideoDecoderFactory> videoDecoderFactory, rtc::scoped_refptr<AudioProcessing> audioProcessing);

private:
    static std::mutex mutex_;
    static std::shared_ptr<PeerConnectionFactoryWrapper> defaultFactory_;

    std::unique_ptr<rtc::SocketServer> socketServer_;
    std::unique_ptr<rtc::Thread> networkThread_;
    std::unique_ptr<rtc::Thread> workerThread_;
    std::unique_ptr<rtc::Thread> signalingThread_;
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> pcFactory_;
    rtc::scoped_refptr<OhosAudioDeviceModule> adm_;

    std::map<rtc::scoped_refptr<MediaStreamTrackInterface>, rtc::scoped_refptr<OhosLocalAudioSource>> audioSources_;
    std::map<rtc::scoped_refptr<MediaStreamTrackInterface>, rtc::scoped_refptr<OhosVideoTrackSource>> videoSources_;
};

} // namespace webrtc

#endif // WEBRTC_PEER_CONNECTION_FACTORY_H
