#ifndef WEBRTC4CJ_FFI_MEDIA_STREAM_H
#define WEBRTC4CJ_FFI_MEDIA_STREAM_H
#include <cstdint>
#include "api/media_stream_interface.h"
#include "pc/media_stream_observer.h"

#include "ffi_exception.h"
#include "ffi_media_stream_track.h"
#include "ffi_define_struct.h"

namespace webrtc {

class FFIMediaStream {
public:
    FFIMediaStream(std::shared_ptr<PeerConnectionFactoryWrapper> factory,
                    rtc::scoped_refptr<MediaStreamInterface> stream)
    {
        factory_ = factory;
        stream_ = stream;
        observer_.reset(
            new MediaStreamObserver(
                stream_.get(),
                [this](AudioTrackInterface* audio_track, MediaStreamInterface* media_stream) {
                    OnAudioTrackAddedToStream(audio_track, media_stream);
                },
                [this](AudioTrackInterface* audio_track, MediaStreamInterface* media_stream) {
                    OnAudioTrackRemovedFromStream(audio_track, media_stream);
                },
                [this](VideoTrackInterface* video_track, MediaStreamInterface* media_stream) {
                    OnVideoTrackAddedToStream(video_track, media_stream);
                },
                [this](VideoTrackInterface* video_track, MediaStreamInterface* media_stream) {
                    OnVideoTrackRemovedFromStream(video_track, media_stream);
                }
            )
        );
    }

    rtc::scoped_refptr<MediaStreamInterface> Get() const
    {
        return stream_;
    }

    ~FFIMediaStream()
    {
        for (auto track: stream_->GetAudioTracks()) {
            factory_->RemoveAudioSource(track);
        }
        for (auto track : stream_->GetVideoTracks()) {
            factory_->RemoveVideoSource(track);
        }
    }

    void AddTrack(int64_t mst);
    void RemoveTrack(int64_t mst);
    int64_t GetTrackById(std::string trackId_str);
    CJ_ReturnArray GetTracks();
    CJ_ReturnArray GetAudioTracks();
    CJ_ReturnArray GetVideoTracks();
    // Napi::Value ToJson(const Napi::CallbackInfo& info);

protected:
    void OnAudioTrackAddedToStream(AudioTrackInterface* track, MediaStreamInterface* stream);
    void OnVideoTrackAddedToStream(VideoTrackInterface* track, MediaStreamInterface* stream);
    void OnAudioTrackRemovedFromStream(AudioTrackInterface* track, MediaStreamInterface* stream);
    void OnVideoTrackRemovedFromStream(VideoTrackInterface* track, MediaStreamInterface* stream);

    
private:
    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    rtc::scoped_refptr<MediaStreamInterface> stream_;
    std::unique_ptr<MediaStreamObserver> observer_;
};

}

#endif // WEBRTC4CJ_FFI_MEDIA_STREAM_H