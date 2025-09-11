#ifndef WEBRTC_FFI_MEDIA_STREAM_TRACK_H
#define WEBRTC_FFI_MEDIA_STREAM_TRACK_H

#include <cstdint>
#include <memory>
#include <set>
#include <mutex>


#include "api/media_stream_interface.h"
#include "api/peer_connection_interface.h"
#include "api/scoped_refptr.h"

#include "peer_connection_factory.h"
#include "logging/ohos_log.h"
#include "ffi_define_struct.h"

namespace webrtc {
class PeerConnectionFactoryWrapper;

class ffiMediaStreamTrack {
public:
    ffiMediaStreamTrack(std::shared_ptr<PeerConnectionFactoryWrapper> factory,
                        rtc::scoped_refptr<MediaStreamTrackInterface> track);
    ~ffiMediaStreamTrack();

    void AddSink(rtc::VideoSinkInterface<VideoFrame>* sink);
    void RemoveSink(rtc::VideoSinkInterface<VideoFrame>* sink);

    void RemoveVideoSink(rtc::VideoSinkInterface<VideoFrame>* sink);
    void AddVideoSink(rtc::VideoSinkInterface<VideoFrame>* sink);
    char* GetKind();
    char* GetId();
    bool GetEnabled();
    char* GetReadyState();
    void Stop();
    CJ_ffiMediaStreamTrackJson ToJson();
    int64_t GetSource();
    bool IsAudioTrack() const;
    bool IsVideoTrack() const;
    rtc::scoped_refptr<MediaStreamTrackInterface> Get() const
    {
        return track_;
    }

protected:
    void RemoveAllVideoSinks();
private:
    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<MediaStreamTrackInterface> track_;
    // rtc::scoped_refptr<OhosLocalAudioSource> audiosource_;
    // rtc::scoped_refptr<OhosVideoTrackSource> videosource_;
    // rtc::scoped_refptr<OhosLocalAudioSource>* audiosource_ptr_ = nullptr;
    // rtc::scoped_refptr<OhosVideoTrackSource>* videosource_ptr_ = nullptr;

    char* kind_ = nullptr;
    char* id_ = nullptr;
    bool enabled_ = false;
    char* readyState_ = nullptr;

    std::mutex sinksMutex_;
    std::set<rtc::VideoSinkInterface<VideoFrame>*> videoSinks_;
};
}
#endif // WEBRTC_FFI_MEDIA_STREAM_TRACK_H