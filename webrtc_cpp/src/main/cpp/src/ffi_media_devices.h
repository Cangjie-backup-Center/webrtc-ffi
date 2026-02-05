#ifndef WEBRTC4CJ_FFI_MEDIA_DEVICES_H
#define WEBRTC4CJ_FFI_MEDIA_DEVICES_H

#include <cstdint>
#include "api/media_stream_interface.h"
#include "ffi_media_stream.h"
#include "ffi_peer_connection_factory.h"
#include "pc/media_stream_observer.h"
#define CLASS_FFIMEDIADEVICESASSIST class FFIMediaDevicesAssist

#include "ffi_exception.h"
#include "async_work/uv_work.h"
#include "screen_capture/screen_capturer.h"
#include "screen_capture/system_audio_receiver.h"
#include "user_media/media_constraints_util.h"
#include "camera/camera_enumerator.h"
#include "camera/camera_capturer.h"
#include "audio_device/audio_device_info.h"
#include "audio_device/audio_device_enumerator.h"
#include "ffi_define_struct.h"

namespace webrtc {
CLASS_FFIMEDIADEVICESASSIST;
class FFIMediaDevices : public CJ_CLASS_BASE::ffiCjClass {
public:
    FFIMediaDevices()
    {
        factory_ = PeerConnectionFactoryWrapper::GetDefault();
    }

    ~FFIMediaDevices () override
    {
        if (this->ffiUserMediaStream_) {
            delete this->ffiUserMediaStream_;
            this->ffiUserMediaStream_ = nullptr;
        }
        if (this->ffiDisplayMediaStream_) {
            delete this->ffiDisplayMediaStream_;
            this->ffiDisplayMediaStream_ = nullptr;
        }
    }

    CJ_ReturnEnumerateDevicesInfo enumerateDevices(); // return MediaDeviceInfo[]
    int64_t getSupportedConstraints(); // return MediaTrackSupportedConstraints*
    void getUserMedia(CJ_TO_CPP_DisplayMediaStreamOptions* video,
        CJ_TO_CPP_DisplayMediaStreamOptions* audio,
        int64_t id, void (*pe)(int64_t that, int64_t localVideoTrack));

    int64_t getDisplayMedia(const CJ_TO_CPP_DisplayMediaStreamOptions video,
        const CJ_TO_CPP_DisplayMediaStreamOptions audio,
        const CJ_TO_CPP_DisplayMediaStreamOptions systemAudio);

protected:
    rtc::scoped_refptr<AudioTrackInterface> CreateAudioTrack(std::string* errorMessage);
    rtc::scoped_refptr<AudioTrackInterface> CreateSystemAudioTrack(
        std::shared_ptr<SystemAudioReceiver> systemAudioReceiver,
        std::string* errorMessage);
    rtc::scoped_refptr<VideoTrackInterface> CreateVideoTrack1(
        std::shared_ptr<SystemAudioReceiver> systemAudioReceiver,
        std::string* errorMessage);
    rtc::scoped_refptr<VideoTrackInterface> CreateVideoTrack2(std::string* errorMessage);
    MediaTrackConstraints audioConstraints_;
    MediaTrackConstraints systemAudioConstraints_;
    MediaTrackConstraints videoConstraints_;
    
    std::vector<CameraDeviceInfo> cameraDevices_;
    std::vector<AudioDeviceInfo> audioDevices_;

    std::shared_ptr<PeerConnectionFactoryWrapper> factory_;
    std::shared_ptr<PeerConnectionFactoryWrapper> factoryDefault_;
    rtc::scoped_refptr<MediaStreamInterface> display_media_stream_;
    rtc::scoped_refptr<MediaStreamInterface> user_media_stream_;
    FFIMediaStream* ffiDisplayMediaStream_ = nullptr;
    FFIMediaStream* ffiUserMediaStream_ = nullptr;
    
    void (*cj_func_call_back1_)(int64_t that, int64_t localVideoTrack);
    void (*cj_func_call_back2_)(int64_t that, int64_t localVideoTrack);

private:
    void getUserMedia(MediaTrackConstraints video, MediaTrackConstraints audio, int64_t id,
                        void (*pe)(int64_t that, int64_t localVideoTrack));
    int64_t getDisplayMedia(MediaTrackConstraints video,
        MediaTrackConstraints audio,
        MediaTrackConstraints systemAudio);
    
    std::shared_ptr<FFIMediaDevicesAssist>ffiMDA_ = nullptr;
};

class FFIMediaDevicesAssist : public FFIMediaDevices {
public:
    FFIMediaDevicesAssist() = default;
    int64_t getDisplayMediaAssist(MediaTrackConstraints video,
                                  MediaTrackConstraints audio,
                                  MediaTrackConstraints systemAudio);

    ~FFIMediaDevicesAssist()
    {
        if (this->ffiDisplayMediaStream_) {
            delete this->ffiDisplayMediaStream_;
            this->ffiDisplayMediaStream_ = nullptr;
        }
    }
};

} // namespace webrtc

#endif // WEBRTC4CJ_FFI_MEDIA_DEVICES_H

