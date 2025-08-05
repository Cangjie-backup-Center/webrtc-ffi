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
#include "screen_capture/screen_capturer.h"
#include "screen_capture/system_audio_receiver.h"
#include "user_media/media_constraints_util.h"
#include "camera/camera_enumerator.h"
#include "camera/camera_capturer.h"
#include "audio_device/audio_device_info.h"
#include "audio_device/audio_device_enumerator.h"

struct FFI_videoGetDisplayMedia {
    int32_t width;
    int32_t height;
    char* cj_ohosScreenCaptureAudioFilter;
};

typedef struct {
    int64_t width;
    int64_t height;
    double aspectRatio;
    double frameRate;
    char* facingMode;
    char* resizeMode;
    int64_t sampleRate;
    int64_t sampleSize;
    bool echoCancellation;
    bool autoGainControl;
    bool noiseSuppression;
    double latency;
    int64_t channelCount;
    char* deviceId;
    char* groupId;
    char* ohosScreenCaptureMode;
    int64_t ohosScreenCaptureDisplayId;
    char* ohosScreenCaptureMissionId;
    char* ohosScreenCaptureWindowFilter;
    char* ohosScreenCaptureAudioFilter;
    char* ohosScreenCaptureSkipPrivacyMode;
    bool ohosScreenCaptureAutoRotation;
} CJ_MediaTrackConstraintSet;

typedef struct {
    const char* deviceId;
    const char* groupId;
    const char* label;
    const char* kind;
} EnumerateDevicesInfo;


typedef struct {
    const char* name;
    const bool isSupported;
} SupportedConstraints;

namespace webrtc {

    class MediaDevices  {
        public:
            MediaDevices() {
                factory_ = PeerConnectionFactoryWrapper::GetDefault();
                
                
            }
            ~MediaDevices () {
                delete ffiUserMediaStream_;
                delete ffiDisplayMediaStream_;
            }
            EnumerateDevicesInfo* enumerateDevices(); // return MediaDeviceInfo[]
            int64_t getSupportedConstraints(); // return MediaTrackSupportedConstraints*
            void getUserMedia(FFI_videoGetDisplayMedia video, bool audio, int64_t id, void (*pe)(int64_t that, int64_t localVideoTrack)); // return MediaStream*
            
    
            void getDisplayMedia(bool video, bool audio, bool systemAudio, int64_t id,  
                                            void (*pe)(int64_t that, int64_t localVideoTrack));
            void getDisplayMedia(CJ_MediaTrackConstraintSet video, CJ_MediaTrackConstraintSet audio, CJ_MediaTrackConstraintSet systemAudio, int64_t that,  
                                            void (*pe)(int64_t that, int64_t localVideoTrack));            
            void getDisplayMedia(MediaTrackConstraints video, MediaTrackConstraints audio, MediaTrackConstraints systemAudio, int64_t that,  
                                            void (*pe)(int64_t that, int64_t localVideoTrack));// return MediaStream*
            
        protected:
            rtc::scoped_refptr<AudioTrackInterface> CreateAudioTrack(std::string* errorMessage);
            rtc::scoped_refptr<AudioTrackInterface> CreateSystemAudioTrack(std::shared_ptr<SystemAudioReceiver> systemAudioReceiver, std::string* errorMessage);
            rtc::scoped_refptr<VideoTrackInterface> CreateVideoTrack1(std::shared_ptr<SystemAudioReceiver> systemAudioReceiver, std::string* errorMessage);
            rtc::scoped_refptr<VideoTrackInterface> CreateVideoTrack2(std::string* errorMessage);
            MediaTrackConstraints audioConstraints_;
            MediaTrackConstraints systemAudioConstraints_;
            MediaTrackConstraints videoConstraints_;
            
            std::vector<CameraDeviceInfo> cameraDevices_;
            std::vector<AudioDeviceInfo> audioDevices_; 
    
            std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
            rtc::scoped_refptr<MediaStreamInterface> display_media_stream_;
            rtc::scoped_refptr<MediaStreamInterface> user_media_stream_;
            FFIMediaStream* ffiDisplayMediaStream_ = nullptr;
            FFIMediaStream* ffiUserMediaStream_ = nullptr;
            
            void (*cj_func_call_back1_)(int64_t that, int64_t localVideoTrack);
            void (*cj_func_call_back2_)(int64_t that, int64_t localVideoTrack);
    };

} // namespace webrtc

#endif //WEBRTC4CJ_FFI_MEDIA_DEVICES_H

