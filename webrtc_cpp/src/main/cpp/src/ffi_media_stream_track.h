#ifndef WEBRTC_FFI_MEDIA_STREAM_TRACK_H
#define WEBRTC_FFI_MEDIA_STREAM_TRACK_H

#include <memory>
#include <set>
#include <mutex>


#include "api/media_stream_interface.h"
#include "api/peer_connection_interface.h"
#include "api/scoped_refptr.h"

#include "peer_connection_factory.h"

namespace webrtc {
class peerConnectionFactoryWrapper;

class ffiMediaStreamTrack {
public:
    ffiMediaStreamTrack(std::shared_ptr<PeerConnectionFactoryWrapper> factory,
                        rtc::scoped_refptr<MediaStreamTrackInterface> track);
    ~ffiMediaStreamTrack();

    void AddSink(rtc::VideoSinkInterface<VideoFrame>* sink);
    void RemoveSink(rtc::VideoSinkInterface<VideoFrame>* sink);

    void RemoveVideoSink(rtc::VideoSinkInterface<VideoFrame>* sink);
    void AddVideoSink(rtc::VideoSinkInterface<VideoFrame>* sink);

protected:

private:
    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<MediaStreamTrackInterface> track_;

    std::mutex sinksMutex_;
    std::set<rtc::VideoSinkInterface<VideoFrame>*> videoSinks_;
};
}
#endif // WEBRTC_FFI_MEDIA_STREAM_TRACK_H