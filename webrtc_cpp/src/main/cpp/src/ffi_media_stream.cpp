#include "ffi_media_stream.h"

#include "rtc_base/logging.h"
#include "rtc_base/helpers.h"
#include "ffi_media_stream_track.h"
#include <string>
#include <memory> 
#include <cstdint>


using namespace webrtc;


void webrtc::FFIMediaStream::AddTrack(int64_t mst){
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

void webrtc::FFIMediaStream::RemoveTrack(int64_t mst) {
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

int64_t webrtc::FFIMediaStream::GetTrackById(char* str){
    std::string trackId = str;
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

int64_t* webrtc::FFIMediaStream::GetTracks() {
    auto audioTracks = stream_->GetAudioTracks();
    auto videoTracks = stream_->GetVideoTracks();

    int64_t* result = new int64_t[audioTracks.size() + videoTracks.size()];  
    for (uint32_t i = 0; i < audioTracks.size(); i++) {
        result[i] = reinterpret_cast<int64_t>(audioTracks[i].get());
    }
    for (uint32_t i = 0; i < videoTracks.size(); i++) {
        result[audioTracks.size() + i] = reinterpret_cast<int64_t>(videoTracks[i].get());
    }

    return result;
}


int64_t* webrtc::FFIMediaStream::GetAudioTracks(){
    auto audioTracks = stream_->GetAudioTracks();
    int64_t* result = new int64_t[audioTracks.size()];  
    for (uint32_t i = 0; i < audioTracks.size(); i++) {
        result[i] = reinterpret_cast<int64_t>(audioTracks[i].get());
    }
    return result;
}

int64_t* webrtc::FFIMediaStream::GetVideoTracks(){
    auto videoTracks = stream_->GetVideoTracks();

    int64_t* result = new int64_t[videoTracks.size()];  
    for (uint32_t i = 0; i < videoTracks.size(); i++) {
        result[i] = reinterpret_cast<int64_t>(videoTracks[i].get());
    }

    return result;
}

