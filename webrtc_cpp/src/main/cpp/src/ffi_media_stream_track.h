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
#include "./utils/marcos.h"
#include "ffi_define_struct.h"
#include "ffi_media_source.h"

namespace webrtc {

class ffiMediaStreamTrack: public ObserverInterface {
public:
    ffiMediaStreamTrack(std::shared_ptr<PeerConnectionFactoryWrapper> factory,
                        rtc::scoped_refptr<MediaStreamTrackInterface> track);
    ~ffiMediaStreamTrack();

    void AddSink(rtc::VideoSinkInterface<VideoFrame>* sink);
    void RemoveSink(rtc::VideoSinkInterface<VideoFrame>* sink);

    void RemoveVideoSink(rtc::VideoSinkInterface<VideoFrame>* sink);
    void AddVideoSink(rtc::VideoSinkInterface<VideoFrame>* sink);
    CHAR_PTR GetKind();
    CHAR_PTR GetId();
    bool GetEnabled();
    CHAR_PTR GetReadyState();
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
    void OnChanged() override;
private:
    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<MediaStreamTrackInterface> track_;
    // rtc::scoped_refptr<OhosLocalAudioSource> audiosource_;
    // rtc::scoped_refptr<OhosVideoTrackSource> videosource_;
    // rtc::scoped_refptr<OhosLocalAudioSource>* audiosource_ptr_ = nullptr;
    // rtc::scoped_refptr<OhosVideoTrackSource>* videosource_ptr_ = nullptr;

    std::mutex sinksMutex_;
    std::set<rtc::VideoSinkInterface<VideoFrame>*> videoSinks_;
};
}
#endif // WEBRTC_FFI_MEDIA_STREAM_TRACK_H