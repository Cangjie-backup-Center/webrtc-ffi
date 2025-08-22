#ifndef WEBRTC_FFI_PEER_CONNECTION_FACTORY_H_
#define WEBRTC_FFI_PEER_CONNECTION_FACTORY_H_

#include <memory>

#include "audio_device/ohos_audio_device_module.h"
#include "audio_device/ffi_ohos_audio_device_module.h"
#include "api/audio_options.h"
#include "peer_connection_factory.h"
#include "ffi_video_decoder_factory.h"
#include "ffi_video_encoder_factory.h"
#include "ffi_media_stream_track.h"
#include "user_media/media_constraints.h"
#include "media_track_constraints.h"

#include "api/peer_connection_interface.h"
#include "rtc_base/socket_server.h"
#include "video/video_track_source.h"
#include "hilog/log.h"
#include "ffi_define_struct.h"
#include "ffi_peer_connection.h"

#define OHOS_LOG_DOMAIN 0xD001234




namespace webrtc{
enum class NakedValueDisposition {
    kTreatAsIdeal,
    kTreatAsExact
};

// using NVD = NakedValueDisposition;

class ffiPeerConnectionFactory{
public:
    ffiPeerConnectionFactory(ffiAudioDeviceModule* ffiADM,
                        ffiHardwareVideoEncoderFactory* ffiHVEF,
                        ffiHardwareVideoDecoderFactory* ffiHVDF);
    ~ffiPeerConnectionFactory();

    void copyVauleCreateAudioSource(FFIAudioOptions ffi_audioOptions);
    void copyVauleCreateAudioTrack(std::string ffi_id);
    void copyVauleCreateVideoSource(FFICreateVideoSourceParameters ffi_videoSource);
    void copyVauleCreateVideoTrack(std::string ffi_videoId);

    FFICreateVideoSourceParameters getCreateVideosSource();
    rtc::scoped_refptr<OhosVideoTrackSource> getVideoSource();
    rtc::scoped_refptr<VideoTrackInterface> getVideoTrack();

    int64_t ffiCreatePeerConnection(CJ_RTCConfiguration config);
    int64_t ffiCreateAudioSource(FFIAudioOptions ffi_audioOptions);
    int64_t ffiCreateAudioTrack(std::string ffi_audioId_str);
    int64_t ffiCreateVideoSource(FFICreateVideoSourceParameters ffi_videoSource);
    int64_t ffiCreateVideoTrack(std::string ffi_videoId_str);

    std::shared_ptr<PeerConnectionFactoryWrapper> GetWrapper() const
    {
        return wrapper_;
    }


    static void SetDefault(ffiPeerConnectionFactory* pcf);
    bool StartAecDump(int fd, int max_size_bytes);
    void StopAecDump();

    rtc::scoped_refptr<OhosLocalAudioSource>* audioSourcePtr_;
    rtc::scoped_refptr<AudioTrackInterface>* audioTrackPtr_;
    rtc::scoped_refptr<OhosVideoTrackSource>* videoSourcePtr_;
    rtc::scoped_refptr<VideoTrackInterface>* videoTrackPtr_;
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> pcFactory_;
    //rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface>
    ffiPeerConnection* ffipc_ = nullptr;
    ffiMediaStreamTrack* ffiMST_;

    std::shared_ptr<PeerConnectionFactoryWrapper> GetPeerConnectionFactoryWrapper () const {
        return wrapper_;
    }

private:
    std::shared_ptr<PeerConnectionFactoryWrapper> wrapper_;
    rtc::scoped_refptr<OhosLocalAudioSource> audioSource_;
    rtc::scoped_refptr<OhosVideoTrackSource> videoSource_;

    rtc::scoped_refptr<VideoTrackInterface> videoTrack_;
    rtc::scoped_refptr<AudioTrackInterface> audioTrack_;

    FFICreateVideoSourceParameters createVideosSource_;
    std::string audioId_;
    std::string videoId_;
    FFIAudioOptions audioOptions_;

    PeerConnectionFactoryInterface* GetFactory() const{
        return wrapper_->GetFactory();
    }

};

void ffiVideoReceiveParameters(FFICreateVideoSourceParameters createVideosSource,MediaTrackConstraints& nativeTrackConstraints);
bool ffiValidateAndCopyConstraintSet(FFICreateVideoSourceParameters createVideosSource, NakedValueDisposition nakedTreatment , MediaTrackConstraintSet& trackConstraints,std::string& errorMessage);

bool ffiValidateAndCopyConstraint(char* ffiCreateVideoSourceChar, NakedValueDisposition nakedTreatment, StringConstraint& constraint,std::string& errorMessage);
void ffiValidateAndCopyConstraint(double ffiCreateVideoSourceDouble, NakedValueDisposition nakedTreatment, LongConstraint& constraint);

void ffiCopyLongConstraint(double value,NakedValueDisposition nakedTreatment, LongConstraint& constraint);
bool ffiValidateAndCopyStringConstraint(char* ffiCreateVideoSourceChar, NakedValueDisposition nakedTreatment, StringConstraint& constraint,std::string& errorMessage);
bool ffiValidateStringConstraint(char* ffiCreateVideoSourceChar, std::string& errorMessage);

bool ffiValidateAndCopyConstraintSetExtension(CJ_MediaTrackConstraintSet cjMediaTrackConstraintSet, NakedValueDisposition nakedTreatment, MediaTrackConstraintSet& trackConstraints, std::string& errorMessage);
bool ffiValidateAndCopyConstraintSet(CJ_MediaTrackConstraintSet cjMediaTrackConstraintSet, NakedValueDisposition nakedTreatment, MediaTrackConstraintSet& trackConstraints, std::string& errorMessage);
void ffiValidateAndCopyConstraint(bool ffiCreateVideoSourceBool, NakedValueDisposition nakedTreatment, BooleanConstraint& constraint);
void ffiValidateAndCopyBooleanConstraint(bool ffiCreateVideoSourceBool, NakedValueDisposition nakedTreatment, BooleanConstraint& constraint);

}

#endif // WEBRTC_FFI_PEER_CONNECTION_FACTORY_H_