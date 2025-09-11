#include "ffi_media_stream_track.h"
#include "ffi_exception.h"
#include <cstdint>
#include <hilog/log.h>

#define OHOS_LOG_DOMAIN 0xD001234

namespace webrtc{

ffiMediaStreamTrack::ffiMediaStreamTrack(
    std::shared_ptr<PeerConnectionFactoryWrapper> factory,
    rtc::scoped_refptr<MediaStreamTrackInterface> track)
{
    factory_ = factory;
    track_ = track;
}

ffiMediaStreamTrack::~ffiMediaStreamTrack() {
    if (kind_){
        delete[] kind_;
        kind_ = nullptr;
    }

    if (id_){
        delete[] id_;
        id_ = nullptr;
    }

    if (readyState_) {
        delete[] readyState_;
        readyState_ = nullptr;
    }
    
    
}

void ffiMediaStreamTrack::AddSink(rtc::VideoSinkInterface<VideoFrame>* sink) {
    this->AddVideoSink(sink);
}

void ffiMediaStreamTrack::RemoveSink(rtc::VideoSinkInterface<VideoFrame>* sink){
    this->RemoveVideoSink(sink);    
}

void ffiMediaStreamTrack::RemoveVideoSink(rtc::VideoSinkInterface<VideoFrame>* sink){
    {
        std::lock_guard<std::mutex> lock(sinksMutex_);
        if (videoSinks_.erase(sink) == 0) {
            LOGI("Failed to erase video sink");
            return;
        }
    }

    auto videoTrack = static_cast<VideoTrackInterface*>(track_.get());
    videoTrack->RemoveSink(sink);
}

void ffiMediaStreamTrack::AddVideoSink(rtc::VideoSinkInterface<VideoFrame>* sink){
    {
        std::lock_guard<std::mutex> lock(sinksMutex_);
        auto setRet = videoSinks_.insert(sink);
        if (!setRet.second) {
            LOGI("Failed to insert video sink");
            return;
        }
    }

    auto videoTrack = static_cast<VideoTrackInterface*>(track_.get());
    videoTrack->AddOrUpdateSink(sink,rtc::VideoSinkWants());
}

char* ffiMediaStreamTrack::GetKind() {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    if (!track_) {
        CANGJIE_THROW("Illegal state");
    }

    auto retKind = track_->kind();
    kind_ = new char[retKind.size() + 1];
    strncpy(kind_, retKind.c_str(), retKind.size() + 1);

    return kind_;
}

char* ffiMediaStreamTrack::GetId() {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    if (!track_) {
        CANGJIE_THROW("Illegal state");
    }

    auto retId = track_->id();
    id_ = new char[retId.size() + 1];
    strncpy(id_, retId.c_str(), retId.size() + 1);

    return id_;
}

bool ffiMediaStreamTrack::GetEnabled() {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    if (!track_) {
        CANGJIE_THROW("Illegal state");
    }

    return track_->enabled();
}

char* ffiMediaStreamTrack::GetReadyState() {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    if (!track_) {
        CANGJIE_THROW("Illegal state");
    }

    const std::string mediaStreamTrackStateLive = "live";
    const std::string mediaStreamTrackStateEnded = "ended";

    auto state = track_->state();
    switch (state) {
        case MediaStreamTrackInterface::kLive: {
            readyState_ = new char[mediaStreamTrackStateLive.size() + 1];
            strncpy(readyState_, mediaStreamTrackStateLive.c_str(), mediaStreamTrackStateLive.size() + 1);
            return readyState_;
        }
        case MediaStreamTrackInterface::kEnded: {
            readyState_ = new char[mediaStreamTrackStateEnded.size() + 1];
            strncpy(readyState_, mediaStreamTrackStateEnded.c_str(), mediaStreamTrackStateEnded.size() + 1);
            return readyState_;
        }
        default: {
            break;
        }
    }

    CANGJIE_THROW("Illegal state");
}

void ffiMediaStreamTrack::Stop() {
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    if (!track_) {
        CANGJIE_THROW("Illegal state");
    }

    auto state = track_->state();
    if (state == MediaStreamTrackInterface::kEnded) {
        RTC_LOG(LS_VERBOSE) << "The track is already ended";
        return;
    }

    RemoveAllVideoSinks();

    return;
}

bool ffiMediaStreamTrack::IsVideoTrack() const
{
    return (track_->kind() == MediaStreamTrackInterface::kVideoKind);
}

bool ffiMediaStreamTrack::IsAudioTrack() const
{
    return (track_->kind() == MediaStreamTrackInterface::kAudioKind);
}


void ffiMediaStreamTrack::RemoveAllVideoSinks()
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;

    if (!IsVideoTrack()) {
        return;
    }

    std::set<rtc::VideoSinkInterface<VideoFrame>*> sinks;
    {
        UNUSED std::lock_guard<std::mutex> lock(sinksMutex_);
        videoSinks_.swap(sinks);
    }

    auto videoTrack = static_cast<VideoTrackInterface*>(track_.get());
    for (auto& sink : sinks) {
        if (sink) {
            videoTrack->RemoveSink(sink);
        }
    }
}

CJ_ffiMediaStreamTrackJson ffiMediaStreamTrack::ToJson(){
    CJ_ffiMediaStreamTrackJson js;
    if (track_) {
        js.id = track_->id().c_str();  // 直接传c_str() ?? TODO
        js.kind = track_->kind().c_str();
        js.enabled = track_->enabled() != 0;
        auto state = track_->state();
        switch (state) {
            case MediaStreamTrackInterface::kLive:
                js.readyState = "live";
                break;
            case MediaStreamTrackInterface::kEnded:
                js.readyState = "ended";
                break;
            default:
                break;
        }
        return js;
    }
    CANGJIE_THROW("Track_ is empty in the toJson function");
    return js;
}


int64_t ffiMediaStreamTrack::GetSource(){
    if (!track_) {
        CANGJIE_THROW("Illegal state");
    }
    
    if (IsAudioTrack()) {
        auto audioSource = factory_->GetAudioSource(track_);
        if (audioSource) {
//            return (int64_t)FFIAudioSource::NewInstance(audioSource);
            return 0;
        } 
    } else if (IsVideoTrack()) {
        auto videoSource = factory_->GetVideoSource(track_);
        if (videoSource) {
//            return (int64_t)FFIVideoSource::NewInstance(videoSource);
            return 0;
        }
    }

    return -1;
}

}
