#ifndef WEBRTC4CJ_FFI_MEDIA_STREAM_H
#define WEBRTC4CJ_FFI_MEDIA_STREAM_H
#include <cstdint>
#include "api/media_stream_interface.h"
#include "pc/media_stream_observer.h"

#include "ffi_exception.h"
#include "ffi_media_stream_track.h"

namespace webrtc {

class NapiMediaStreamTrack;
class PeerConnectionFactoryWrapper;

    class FFIMediaStream {
        private:
            std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
            rtc::scoped_refptr<MediaStreamInterface> stream_;
            std::unique_ptr<MediaStreamObserver> observer_;
        public:
            FFIMediaStream(std::shared_ptr<PeerConnectionFactoryWrapper> factory, rtc::scoped_refptr<MediaStreamInterface> stream) {
                factory_ = factory;
                stream_ = stream;
                observer_ = nullptr;
            }

            // Napi::Value GetId(const Napi::CallbackInfo& info);
            // Napi::Value GetActive(const Napi::CallbackInfo& info);
    
            rtc::scoped_refptr<AudioTrackInterface> atif_;
            rtc::scoped_refptr<VideoTrackInterface> vtif_;
    
            void AddTrack(int64_t mst);
            void RemoveTrack(int64_t mst);
            int64_t GetTrackById(char* trackId);
            int64_t* GetTracks();
            int64_t* GetAudioTracks();
            int64_t* GetVideoTracks();
            // Napi::Value ToJson(const Napi::CallbackInfo& info);
    };
}

#endif // WEBRTC4CJ_FFI_MEDIA_STREAM_H