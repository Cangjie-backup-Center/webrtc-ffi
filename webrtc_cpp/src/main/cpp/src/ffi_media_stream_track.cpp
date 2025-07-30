#include "ffi_media_stream_track.h"
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

ffiMediaStreamTrack::~ffiMediaStreamTrack() = default;

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
            OH_LOG_Print(LOG_APP, LOG_ERROR, OHOS_LOG_DOMAIN, "webrtc", "Failed to erase video sink");
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
            OH_LOG_Print(LOG_APP, LOG_ERROR, OHOS_LOG_DOMAIN, "webrtc", "Failed to insert video sink");
            return;
        }
    }

    auto videoTrack = static_cast<VideoTrackInterface*>(track_.get());
    videoTrack->AddOrUpdateSink(sink,rtc::VideoSinkWants());
}

}
