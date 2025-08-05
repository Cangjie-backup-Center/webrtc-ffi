#ifndef WEBRTC4CJ_FFI_MEDIA_DEVICES_H
#define WEBRTC4CJ_FFI_MEDIA_DEVICES_H

#include <cstdint>
#include "api/media_stream_interface.h"
#include "ffi_media_stream.h"
#include "ffi_peer_connection_factory.h"
#include "pc/media_stream_observer.h"

#include "ffi_exception.h"
#include "peer_connection.h"
#include "async_work/uv_work.h"

struct FFI_videoGetDisplayMedia {
    int32_t width;
    int32_t height;
    char* cj_ohosScreenCaptureAudioFilter;
};


namespace webrtc {

    class MediaDevices  {
        public:
            MediaDevices() {
                factory_ = PeerConnectionFactoryWrapper::GetDefault();
                stream_ = factory_->GetFactory()->CreateLocalMediaStream(rtc::CreateRandomUuid());
            }
            ~MediaDevices () {
                delete ffiMediaStream_;
            }
            int64_t** enumerateDevices(); // return MediaDeviceInfo[]
            int64_t getSupportedConstraints(); // return MediaTrackSupportedConstraints*
            void getUserMedia(int64_t constraints); // return MediaStream*
            void getDisplayMedia(FFI_videoGetDisplayMedia video, bool audio, bool systemAudio, int64_t that,  
                                            void (*pe)(int64_t that, int64_t localVideoTrack));// return MediaStream*
            
        protected:
            
            MediaTrackConstraints audioConstraints_;
            MediaTrackConstraints systemAudioConstraints_;
            MediaTrackConstraints videoConstraints_;
    
            std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
            rtc::scoped_refptr<MediaStreamInterface> stream_;
            FFIMediaStream* ffiMediaStream_ = nullptr;
            
            int64_t that_;
            void (*post_event_)(int64_t that, int64_t localVideoTrack);
    };

} // namespace webrtc

#endif //WEBRTC4CJ_FFI_MEDIA_DEVICES_H

