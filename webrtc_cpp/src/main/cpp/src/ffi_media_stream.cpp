/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "ffi_media_stream.h"

#include "rtc_base/logging.h"
#include "rtc_base/helpers.h"
#include "ffi_media_stream_track.h"
#include <string>
#include <memory>
#include <cstdint>
namespace webrtc {

void webrtc::FFIMediaStream::AddTrack(int64_t mst)
{
    auto nativeTrack = reinterpret_cast<ffiMediaStreamTrack*>(mst);
    if (!nativeTrack) {
        CANGJIE_THROW("Invalid argument");
        return;
    }
    auto track = nativeTrack->Get();
    if (!track) {
        CANGJIE_THROW("Invalid argument");
        return;
    }
    bool success = false;
    if (track->kind() == MediaStreamTrackInterface::kAudioKind) {
        auto audioTrack = rtc::scoped_refptr<AudioTrackInterface>(static_cast<AudioTrackInterface*>(track.get()));
        success = stream_->AddTrack(audioTrack);
    } else if (track->kind() == MediaStreamTrackInterface::kVideoKind) {
        auto videoTrack = rtc::scoped_refptr<VideoTrackInterface>(static_cast<VideoTrackInterface*>(track.get()));
        success = stream_->AddTrack(videoTrack);
    } else {
        RTC_LOG(LS_WARNING) << "Unknown type of media stream track: " << track->id();
    }
    if (!success) {
        RTC_LOG(LS_ERROR) << "Failed to add track to media stream";
        CANGJIE_THROW("Unknown error");
        return;
    }
}

void webrtc::FFIMediaStream::RemoveTrack(int64_t mst)
{
    auto nativeTrack = reinterpret_cast<ffiMediaStreamTrack*>(mst);
    if (!nativeTrack) {
        CANGJIE_THROW("Invalid argument");
        return;
    }

    auto track = nativeTrack->Get();
    if (!track) {
        CANGJIE_THROW("Invalid argument");
    }

    bool success = false;
    if (track->kind() == MediaStreamTrackInterface::kAudioKind) {
        auto audioTrack = rtc::scoped_refptr<AudioTrackInterface>(static_cast<AudioTrackInterface*>(track.get()));
        success = stream_->RemoveTrack(audioTrack);
    } else if (track->kind() == MediaStreamTrackInterface::kVideoKind) {
        auto videoTrack = rtc::scoped_refptr<VideoTrackInterface>(static_cast<VideoTrackInterface*>(track.get()));
        success = stream_->RemoveTrack(videoTrack);
    } else {
        RTC_LOG(LS_WARNING) << "Unknown type of media stream track: " << track->id();
    }

    if (!success) {
        RTC_LOG(LS_ERROR) << "Failed to remove track from media stream";
        CANGJIE_THROW("Unknown error");
    }
}

int64_t webrtc::FFIMediaStream::GetTrackById(std::string trackId_str)
{
    std::string trackId = trackId_str;
    atif_ = stream_->FindAudioTrack(trackId);
    if (atif_) {
        return reinterpret_cast<int64_t>(atif_.get());
    }

    vtif_ = stream_->FindVideoTrack(trackId);
    if (vtif_) {
        return reinterpret_cast<int64_t>(vtif_.get());
    }
    RTC_LOG(LS_INFO) << "No track with id: " << trackId;
}

CJ_ReturnArray webrtc::FFIMediaStream::GetTracks()
{
    auto audioTracks = stream_->GetAudioTracks();  // typedef std::vector<rtc::scoped_refptr<AudioTrackInterface> > AudioTrackVector;
    auto videoTracks = stream_->GetVideoTracks();

    int64_t* result = new int64_t[audioTracks.size() + videoTracks.size()];
    for (uint32_t i = 0; i < audioTracks.size(); i++) {
        audioMediaStreamTrackPtr = new ffiMediaStreamTrack(factory_, audioTracks[i]);
        result[i] = reinterpret_cast<int64_t>(audioMediaStreamTrackPtr);
    }

    for (uint32_t i = 0; i < videoTracks.size(); i++) {
        videoMediaStreamTrackPtr = new ffiMediaStreamTrack(factory_, videoTracks[i]);
        result[audioTracks.size() + i] = reinterpret_cast<int64_t>(videoMediaStreamTrackPtr);
    }
    return (CJ_ReturnArray){result, (int64_t)(audioTracks.size() + videoTracks.size())};
}


CJ_ReturnArray webrtc::FFIMediaStream::GetAudioTracks()
{
    auto audioTracks = stream_->GetAudioTracks();
    int64_t* result = new int64_t[audioTracks.size()];
    for (uint32_t i = 0; i < audioTracks.size(); i++) {
        audioMediaStreamTrackPtr = new ffiMediaStreamTrack(factory_, audioTracks[i]);
        result[i] = reinterpret_cast<int64_t>(audioMediaStreamTrackPtr);
    }
    return (CJ_ReturnArray){result, (int64_t)(audioTracks.size())};
}

CJ_ReturnArray webrtc::FFIMediaStream::GetVideoTracks()
{
    auto videoTracks = stream_->GetVideoTracks();

    int64_t* result = new int64_t[videoTracks.size()];
    for (uint32_t i = 0; i < videoTracks.size(); i++) {
        videoMediaStreamTrackPtr = new ffiMediaStreamTrack(factory_, videoTracks[i]);
        result[i] = reinterpret_cast<int64_t>(videoMediaStreamTrackPtr);
    }

    return (CJ_ReturnArray){result, (int64_t)(videoTracks.size())};
}

void FFIMediaStream::OnAudioTrackAddedToStream(AudioTrackInterface* track, MediaStreamInterface* stream)
{
    (void)stream;
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " track: " << track->id();
}

void FFIMediaStream::OnVideoTrackAddedToStream(VideoTrackInterface* track, MediaStreamInterface* stream)
{
    (void)stream;
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " track: " << track->id();
}

void FFIMediaStream::OnAudioTrackRemovedFromStream(AudioTrackInterface* track, MediaStreamInterface* stream)
{
    (void)stream;
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " track: " << track->id();
}

void FFIMediaStream::OnVideoTrackRemovedFromStream(VideoTrackInterface* track, MediaStreamInterface* stream)
{
    (void)stream;
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__ << " track: " << track->id();
}

}