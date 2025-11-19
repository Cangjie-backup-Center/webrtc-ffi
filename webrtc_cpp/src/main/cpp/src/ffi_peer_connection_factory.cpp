/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

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
#include <cstdint>


namespace webrtc {
ffiPeerConnectionFactory::ffiPeerConnectionFactory(
                        ffiAudioDeviceModule* ffiADM,
                        ffiHardwareVideoEncoderFactory* ffiHVEF,
                        ffiHardwareVideoDecoderFactory* ffiHVDF) {
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
        LOGI("videoEncoderFactory create fail");
        return ;
    }
    
    videoDecoderFactory = createHardwareVideoDecoderFactory(ffiHVDF);
    if (videoDecoderFactory == nullptr){
        LOGI("videoDecoderFactory create fail");
        return ;
    }

    wrapper_ = PeerConnectionFactoryWrapper::Create(
    adm, std::move(videoEncoderFactory), std::move(videoDecoderFactory), audioProcessing);
}

template <typename T>
void releasePtr(T* ffipc_) {
    if (ffipc_) {
        delete ffipc_;
        ffipc_ = nullptr;
    }
}


ffiPeerConnectionFactory::~ffiPeerConnectionFactory(){
    releasePtr(ffipc_);
    audioSourcePtr_->release();
    audioTrackPtr_->release();
    videoSourcePtr_->release();
    videoTrackPtr_->release();
    releasePtr(ffiMST_);
}

void ffiPeerConnectionFactory::copyVauleCreateAudioSource(FFIAudioOptions ffi_audioOptions){
    audioOptions_.echo_cancellation = ffi_audioOptions.echo_cancellation;
    audioOptions_.noise_suppression = ffi_audioOptions.noise_suppression;
}

void ffiPeerConnectionFactory::copyVauleCreateAudioTrack(std::string ffi_audioId){
    audioId_ = ffi_audioId;
}

void ffiPeerConnectionFactory::copyVauleCreateVideoTrack(std::string ffi_videoId){
    videoId_ = ffi_videoId;
}



rtc::scoped_refptr<OhosVideoTrackSource> ffiPeerConnectionFactory::getVideoSource(){
    return videoSource_;
}

rtc::scoped_refptr<VideoTrackInterface> ffiPeerConnectionFactory::getVideoTrack(){
    return videoTrack_;
}

int64_t ffiPeerConnectionFactory::ffiCreatePeerConnection(CJ_RTCConfiguration config){
    
    ffipc_ = new ffiPeerConnection(config, wrapper_);
    
    return (int64_t) ffipc_;
}

int64_t ffiPeerConnectionFactory::ffiCreateAudioSource(FFIAudioOptions ffi_audioOptions){
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
    auto ffiMST = new ffiMediaStreamTrack(wrapper_, audioTrack_);
    return (int64_t)ffiMST;
}

int64_t ffiPeerConnectionFactory::ffiCreateVideoSource(CJ_TO_CPP_DisplayMediaStreamOptions ffi_videoSource, bool isScreencast){
    MediaTrackConstraints video;
    if (true) {
        ffiVideoReceiveParameters(ffi_videoSource,video);
    } else {
        video.Initialize();
    }

    std::unique_ptr<VideoCapturer> videoCapturer;
    if (isScreencast) {
        ScreenCaptureOptions options;
        GetScreenCaptureOptionsFromConstraints(video, options);
        videoCapturer = ScreenCapturer::Create(std::move(options));
        if (!videoCapturer){
            CANGJIE_THROW("Create ScreenCapturer fail");
        }
    } else {
        CameraCaptureSettings selectedSetting;
        std::string failedConstraintName;
        if (!SelectSettingsForVideo(CameraEnumerator::GetDevices(), 
                                video, kDefaultWidth, kDefaultHeight, kDefaultFrameRate,
                                selectedSetting, failedConstraintName))
        {
            CANGJIE_THROW("SelectSettingsForVideo fail");
            return 0;
        }

        videoCapturer = CameraCapturer::Create(selectedSetting.deviceId, selectedSetting.profile);
        if (!videoCapturer) {
            CANGJIE_THROW("Create CameraCapturer fail");
        }
    }
    
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


void ffiVideoReceiveParameters(CJ_TO_CPP_DisplayMediaStreamOptions createVideosSource,MediaTrackConstraints& video){
    std::string errorMessage;
    MediaTrackConstraintSet basic;
    ffiValidateAndCopyConstraintSet(createVideosSource, NakedValueDisposition::kTreatAsIdeal, basic, errorMessage);

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
    if(ffiCreateVideoSourceDouble != 0.0 && NapiMediaConstraints::IsConstraintSupported(constraint.GetName())){
        ffiCopyLongConstraint(ffiCreateVideoSourceDouble,nakedTreatment,constraint);
    }
}

void ffiValidateAndCopyConstraint(double ffiCreateVideoSourceDouble, NakedValueDisposition nakedTreatment,DoubleConstraint& constraint){
    if(ffiCreateVideoSourceDouble != 0.0 && NapiMediaConstraints::IsConstraintSupported(constraint.GetName())){
        ffiCopyDoubleConstraint(ffiCreateVideoSourceDouble,nakedTreatment,constraint);
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

void ffiCopyDoubleConstraint(double value,NakedValueDisposition nakedTreatment, DoubleConstraint& constraint){
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


bool ffiValidateAndCopyConstraintSet(const CJ_TO_CPP_DisplayMediaStreamOptions cjMediaTrackConstraintSet, NakedValueDisposition nakedTreatment, MediaTrackConstraintSet& trackConstraints, std::string& errorMessage){
    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.width, nakedTreatment, trackConstraints.width);
    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.height, nakedTreatment, trackConstraints.width); 
    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.aspectRatio, nakedTreatment, trackConstraints.aspectRatio);
    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.frameRate, nakedTreatment, trackConstraints.frameRate);
    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.sampleRate, nakedTreatment, trackConstraints.sampleRate);
    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.sampleSize, nakedTreatment, trackConstraints.sampleSize);
    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.echoCancellation, nakedTreatment, trackConstraints.echoCancellation);
    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.autoGainControl, nakedTreatment, trackConstraints.autoGainControl);
    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.noiseSuppression, nakedTreatment, trackConstraints.noiseSuppression);
    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.latency, nakedTreatment, trackConstraints.latency);
    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.channelCount, nakedTreatment, trackConstraints.channelCount);
    ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.ohosScreenCaptureDisplayId, nakedTreatment, trackConstraints.ohosScreenCaptureDisplayId);

    if (!ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.facingMode, nakedTreatment, trackConstraints.facingMode, errorMessage)) {
        return false;
    }
    
    if (!ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.resizeMode, nakedTreatment, trackConstraints.resizeMode, errorMessage)) {
        return false;
    }

    if (!ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.deviceId, nakedTreatment, trackConstraints.deviceId, errorMessage)) {
        return false;
    }

    if (!ffiValidateAndCopyConstraint(cjMediaTrackConstraintSet.obj.groupId, nakedTreatment, trackConstraints.groupId, errorMessage)) {
        return false;
    }

    if (!ffiValidateAndCopyConstraintSetExtension(cjMediaTrackConstraintSet.obj, nakedTreatment, trackConstraints, errorMessage)){
        return false;
    }

    return true;
}


}
