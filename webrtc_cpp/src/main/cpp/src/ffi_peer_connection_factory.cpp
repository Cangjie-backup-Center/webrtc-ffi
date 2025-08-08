#include "ffi_peer_connection_factory.h"
#include "user_media/media_constraints_util.h"

#include "api/audio_codecs/builtin_audio_decoder_factory.h"
#include "api/audio_codecs/builtin_audio_encoder_factory.h"
#include "api/video_codecs/video_decoder_factory.h"
#include "video/video_track_source.h"
#include "audio_device/ohos_audio_device_module.h"

#include "api/create_peerconnection_factory.h"
#include "api/scoped_refptr.h"
#include "rtc_base/physical_socket_server.h"

#include "configuration.h"
#include "media_track_constraints.h"
#include "media_source.h"
#include "media_stream_track.h"
#include "peer_connection.h"
#include "audio_device/ohos_audio_device_module.h"
#include "audio_device/ohos_local_audio_source.h"
#include "camera/camera_enumerator.h"
#include "camera/camera_capturer.h"
#include "screen_capture/screen_capturer.h"
#include "video/video_track_source.h"
#include "user_media/media_constraints_util.h"
#include "video_encoder_factory.h"
#include "video_decoder_factory.h"
#include "audio_processing_factory.h"
#include "utils/marcos.h"


namespace webrtc{
ffiPeerConnectionFactory::ffiPeerConnectionFactory(
                        ffiAudioDeviceModule* ffiADM,
                        ffiHardwareVideoEncoderFactory* ffiHVEF,
                        ffiHardwareVideoDecoderFactory* ffiHVDF)

{
    audioSourcePtr_ = nullptr;
    audioTrackPtr_ = nullptr;
    videoSourcePtr_ = nullptr;
    videoTrackPtr_ = nullptr;
    ffiMST_ = nullptr;

    rtc::scoped_refptr<OhosAudioDeviceModule> adm;
    std::unique_ptr<VideoEncoderFactory> videoEncoderFactory;
    std::unique_ptr<VideoDecoderFactory> videoDecoderFactory;
    rtc::scoped_refptr<AudioProcessing> audioProcessing;

    adm = ffiADM->getAdm();

    videoEncoderFactory = createHardwareVideoEncoderFactory(ffiHVEF);
    if (videoEncoderFactory == nullptr){
        OH_LOG_Print(LOG_APP, LOG_ERROR, OHOS_LOG_DOMAIN,"webrtc", "videoEncoderFactory create fail");
        return ;
    }
    
    videoDecoderFactory = createHardwareVideoDecoderFactory(ffiHVDF);
    if (videoDecoderFactory == nullptr){
        OH_LOG_Print(LOG_APP, LOG_ERROR, OHOS_LOG_DOMAIN,"webrtc", "videoDecoderFactory create fail");
        return ;
    }

    wrapper_ = PeerConnectionFactoryWrapper::Create(
    adm, std::move(videoEncoderFactory), std::move(videoDecoderFactory), audioProcessing);
}

ffiPeerConnectionFactory::~ffiPeerConnectionFactory(){
    delete audioSourcePtr_;
    delete audioTrackPtr_;
    delete videoSourcePtr_;
    delete videoTrackPtr_;
    delete ffiMST_;
}

void ffiPeerConnectionFactory::copyVauleCreateAudioSource(ffiAudioOptions ffi_audioOptions){
    audioOptions_.echo_cancellation = ffi_audioOptions.echo_cancellation;
    audioOptions_.noise_suppression = ffi_audioOptions.noise_suppression;
}

void ffiPeerConnectionFactory::copyVauleCreateAudioTrack(std::string ffi_audioId){
    audioId_ = ffi_audioId;
}

void ffiPeerConnectionFactory::copyVauleCreateVideoTrack(std::string ffi_videoId){
    videoId_ = ffi_videoId;
}

void ffiPeerConnectionFactory::copyVauleCreateVideoSource(ffiCreateVideoSourceParameters ffi_videoSource){
    createVideosSource_.width = ffi_videoSource.width;
    createVideosSource_.height = ffi_videoSource.height;
    createVideosSource_.facingMode = ffi_videoSource.facingMode;
    createVideosSource_.isScreencast = ffi_videoSource.isScreencast;
}

ffiCreateVideoSourceParameters ffiPeerConnectionFactory::getCreateVideosSource(){
    return createVideosSource_; 
}

rtc::scoped_refptr<OhosVideoTrackSource> ffiPeerConnectionFactory::getVideoSource(){
    return videoSource_;
}

rtc::scoped_refptr<VideoTrackInterface> ffiPeerConnectionFactory::getVideoTrack(){
    return videoTrack_;
}

int64_t ffiPeerConnectionFactory::ffiCreateAudioSource(ffiAudioOptions ffi_audioOptions){
    copyVauleCreateAudioSource(ffi_audioOptions);
    cricket::AudioOptions options;
    options.echo_cancellation = audioOptions_.echo_cancellation;
    options.noise_suppression = audioOptions_.noise_suppression;

    audioSource_ = wrapper_->CreateAudioSource(options);
    audioSourcePtr_ = &audioSource_;
    if (audioSourcePtr_) {
        return (int64_t)audioSourcePtr_;
    }

    return 0;
}


int64_t ffiPeerConnectionFactory::ffiCreateAudioTrack(std::string ffi_audioId_str){
    copyVauleCreateAudioTrack(ffi_audioId_str);
    audioTrack_ = wrapper_->CreateAudioTrack(audioId_,audioSource_);
    audioTrackPtr_ = &audioTrack_;

    if (audioTrackPtr_) {
        return (int64_t)audioTrackPtr_; 
    }

    return 0;
}

int64_t ffiPeerConnectionFactory::ffiCreateVideoSource(ffiCreateVideoSourceParameters ffi_videoSource){
    copyVauleCreateVideoSource(ffi_videoSource);

    std::unique_ptr<VideoCapturer> videoCapturer;
    CameraCaptureSettings selectedSetting;
    std::string failedConstraintName;
    MediaTrackConstraints video;

    bool isScreencast = false;
    ffiVideoReceiveParameters(this->getCreateVideosSource(),video);

    if (!SelectSettingsForVideo(CameraEnumerator::GetDevices(), 
                                video, kDefaultWidth, kDefaultHeight, kDefaultFrameRate,
                                selectedSetting, failedConstraintName))
    {
        OH_LOG_Print(LOG_APP, LOG_ERROR, OHOS_LOG_DOMAIN,"webrtc", "SelectSettingsForVideo fail");
        return 0;
    }

    videoCapturer = CameraCapturer::Create(selectedSetting.deviceId, selectedSetting.profile);
    videoSource_ = wrapper_->CreateVideoSource(std::move(videoCapturer));
    videoSourcePtr_ = &videoSource_;

    if (videoSourcePtr_) {
        return (int64_t)videoSourcePtr_;
    }

    return 0;
}

int64_t ffiPeerConnectionFactory::ffiCreateVideoTrack(std::string ffi_videoId_str){
    copyVauleCreateVideoTrack(ffi_videoId_str);
    videoTrack_ = wrapper_->CreateVideoTrack(videoId_,videoSource_);

    videoTrackPtr_ = &videoTrack_;
    ffiMST_ = new ffiMediaStreamTrack(wrapper_,videoTrack_);

    if (ffiMST_) {
        return (int64_t)ffiMST_;
    }

    return 0;
}

bool ffiPeerConnectionFactory::StartAecDump(int fd, int max_size_bytes){
    
    FILE* file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return false;
    }

    return GetFactory()->StartAecDump(file, max_size_bytes);
}

void ffiPeerConnectionFactory::StopAecDump(){
   GetFactory()->StopAecDump();
   return ;
}

void ffiPeerConnectionFactory::SetDefault(ffiPeerConnectionFactory* pcf){
    PeerConnectionFactoryWrapper::SetDefault(pcf->GetWrapper());
}


void ffiVideoReceiveParameters(ffiCreateVideoSourceParameters createVideosSource,MediaTrackConstraints& video){
    std::string errorMessage;
    MediaTrackConstraintSet basic;
    ffiValidateAndCopyConstraintSet(createVideosSource, NakedValueDisposition::kTreatAsIdeal , basic , errorMessage);

    std::vector<MediaTrackConstraintSet> advanced; 
    video.Initialize(basic, advanced);
    return ;
}

bool ffiValidateAndCopyConstraint(char* ffiCreateVideoSourceChar, NakedValueDisposition nakedTreatment, StringConstraint& constraint,std::string& errorMessage){
    std::string ffiCreateVideoSourceString(ffiCreateVideoSourceChar);

    if(ffiCreateVideoSourceString.compare("") && NapiMediaConstraints::IsConstraintSupported(constraint.GetName())){
        if(!ffiValidateAndCopyStringConstraint(ffiCreateVideoSourceChar,nakedTreatment,constraint,errorMessage)){
            return false;
        }
    }
    return true;
}

void ffiValidateAndCopyConstraint(double ffiCreateVideoSourceDouble, NakedValueDisposition nakedTreatment, LongConstraint& constraint){
    if(ffiCreateVideoSourceDouble != 0 && NapiMediaConstraints::IsConstraintSupported(constraint.GetName())){
        ffiCopyLongConstraint(ffiCreateVideoSourceDouble,nakedTreatment,constraint);
    }
}

void ffiCopyLongConstraint(double value,NakedValueDisposition nakedTreatment, LongConstraint& constraint){
    switch (nakedTreatment){
        case NakedValueDisposition::kTreatAsIdeal:
            constraint.SetIdeal(value);
            break;
    
        case NakedValueDisposition::kTreatAsExact:
            constraint.SetExact(value);
            break;
    }
}

bool ffiValidateAndCopyStringConstraint(char* ffiCreateVideoSourceChar, NakedValueDisposition nakedTreatment, StringConstraint& constraint,std::string& errorMessage){
    if (!ffiValidateStringConstraint(ffiCreateVideoSourceChar, errorMessage)) {
        return false;
    }

    std::string ffiCreateVideoSourceString(ffiCreateVideoSourceChar);

    switch (nakedTreatment) {
    case NakedValueDisposition::kTreatAsIdeal:
        constraint.SetIdeal(ffiCreateVideoSourceString);
        break;
    case NakedValueDisposition::kTreatAsExact:
        constraint.SetExact(ffiCreateVideoSourceString);
        break;
    }

    return true;
}

bool ffiValidateStringConstraint(char* ffiCreateVideoSourceChar, std::string& errorMessage){
    std::string ffiCreateVideoSourceString(ffiCreateVideoSourceChar);
    auto ret_ValidateString = ValidateString(ffiCreateVideoSourceString, errorMessage);
    return ret_ValidateString;
}

bool ffiValidateAndCopyConstraintSet(ffiCreateVideoSourceParameters createVideosSource, NakedValueDisposition nakedTreatment , MediaTrackConstraintSet& trackConstraints,std::string& errorMessage){
    ffiValidateAndCopyConstraint(createVideosSource.width,nakedTreatment,trackConstraints.width);
    ffiValidateAndCopyConstraint(createVideosSource.height,nakedTreatment,trackConstraints.height);
    if (!ffiValidateAndCopyConstraint(createVideosSource.facingMode,nakedTreatment,trackConstraints.facingMode,errorMessage)){
        return false;
    }

    return true;
}

void ffiValidateAndCopyBooleanConstraint(bool ffiCreateVideoSourceBool, NakedValueDisposition nakedTreatment, BooleanConstraint& constraint){
    switch (nakedTreatment) {
        case NakedValueDisposition::kTreatAsIdeal:
            constraint.SetIdeal(ffiCreateVideoSourceBool);
            break;
        case NakedValueDisposition::kTreatAsExact:
            constraint.SetExact(ffiCreateVideoSourceBool);
            break;
    }
}


void ffiValidateAndCopyConstraint(bool ffiCreateVideoSourceBool, NakedValueDisposition nakedTreatment, BooleanConstraint& constraint){
    if(NapiMediaConstraints::IsConstraintSupported(constraint.GetName())){
        ffiValidateAndCopyBooleanConstraint(ffiCreateVideoSourceBool, nakedTreatment, constraint);
    }
}

bool ffiValidateAndCopyConstraintSetExtension(CJ_MediaTrackConstraintSet cjMediaTrackConstraintSet, NakedValueDisposition nakedTreatment, MediaTrackConstraintSet& trackConstraints, std::string& errorMessage){
    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.ohosScreenCaptureDisplayId, nakedTreatment, trackConstraints.ohosScreenCaptureDisplayId);
    if (!ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.ohosScreenCaptureMode, nakedTreatment,
                                   trackConstraints.ohosScreenCaptureMode, errorMessage)) {
        return false;
    }

    if (!ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.ohosScreenCaptureMissionId, nakedTreatment,
                                   trackConstraints.ohosScreenCaptureMissionId, errorMessage)) {
        return false;
    }

    if (!ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.ohosScreenCaptureWindowFilter, nakedTreatment,
                                   trackConstraints.ohosScreenCaptureWindowFilter, errorMessage)) {
        return false;
    }

    if (!ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.ohosScreenCaptureAudioFilter, nakedTreatment,
                                   trackConstraints.ohosScreenCaptureAudioFilter, errorMessage)) {
        return false;
    }

    if (!ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.ohosScreenCaptureSkipPrivacyMode, nakedTreatment,
                                   trackConstraints.ohosScreenCaptureSkipPrivacyMode, errorMessage)) {
        return false;
    }

    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.ohosScreenCaptureAutoRotation, nakedTreatment, trackConstraints.ohosScreenCaptureAutoRotation);

    return true;
}


bool ffiValidateAndCopyConstraintSet(CJ_MediaTrackConstraintSet cjMediaTrackConstraintSet, NakedValueDisposition nakedTreatment, MediaTrackConstraintSet& trackConstraints, std::string& errorMessage){
    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.width, nakedTreatment, trackConstraints.width);
    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.height, nakedTreatment, trackConstraints.width); 

    if (!ffiValidateAndCopyConstraintSetExtension(cjMediaTrackConstraintSet, nakedTreatment, trackConstraints, errorMessage)){
        return false;
    }
    return true;
}


}
