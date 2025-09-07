#include "ffi_media_devices.h"
#include <cstdint>

using namespace webrtc;

typedef struct {
    FFIMediaDevices* md;
    int64_t id;
} CallbackData;


CJ_ReturnEnumerateDevicesInfo FFIMediaDevices::enumerateDevices() {
    cameraDevices_ = CameraEnumerator::GetDevices();
    audioDevices_ = AudioDeviceEnumerator::GetDevices();
  
    CJ_EnumerateDevicesInfo* result = new CJ_EnumerateDevicesInfo[cameraDevices_.size() + audioDevices_.size()];
    for (uint32_t index = 0; index < cameraDevices_.size(); index++) {
        CJ_EnumerateDevicesInfo ed;
        ed.deviceId = (const char*)cameraDevices_[index].deviceId.c_str();
        ed.groupId = (const char*)cameraDevices_[index].groupId.c_str();
        ed.label = (const char*)cameraDevices_[index].label.c_str();
        ed.kind = "videoinput";
        result[index] = ed;
    }
    
    for (uint32_t index = 0; index < audioDevices_.size(); index++) {
        CJ_EnumerateDevicesInfo ed;
        ed.deviceId = (const char*)audioDevices_[index].deviceId.c_str();
        ed.groupId = (const char*)audioDevices_[index].groupId.c_str();
        ed.label = (const char*)audioDevices_[index].label.c_str();
        if (audioDevices_[index].role == AudioDeviceRole::Input) {
            ed.kind = "videoinput";
        } else if (audioDevices_[index].role == AudioDeviceRole::Output) {
            ed.kind = "audiooutput";
        } else {
            ed.kind = "";
        }
        result[cameraDevices_.size() + index] = ed;
    }
    return (CJ_ReturnEnumerateDevicesInfo){result, (int64_t)(cameraDevices_.size() + audioDevices_.size())};
} 


int64_t FFIMediaDevices::getSupportedConstraints() {
    std::vector<CJ_SupportedConstraints>* list = new std::vector<CJ_SupportedConstraints>();
    
#define CANGJIE_SET_ATTRIBUTE(name)   \
    list->push_back(CJ_SupportedConstraints{name, true});

    CANGJIE_SET_ATTRIBUTE("width");
    CANGJIE_SET_ATTRIBUTE("height");
    CANGJIE_SET_ATTRIBUTE("aspectRatio");
    CANGJIE_SET_ATTRIBUTE("frameRate");
    CANGJIE_SET_ATTRIBUTE("facingMode");
    CANGJIE_SET_ATTRIBUTE("resizeMode");
    CANGJIE_SET_ATTRIBUTE("sampleRate");
    CANGJIE_SET_ATTRIBUTE("sampleSize");
    CANGJIE_SET_ATTRIBUTE("echoCancellation");
    CANGJIE_SET_ATTRIBUTE("autoGainControl");
    CANGJIE_SET_ATTRIBUTE("noiseSuppression");
    CANGJIE_SET_ATTRIBUTE("latency");
    CANGJIE_SET_ATTRIBUTE("ChannelCount");
    CANGJIE_SET_ATTRIBUTE("deviceId");
    CANGJIE_SET_ATTRIBUTE("groupId");
#undef CANGJIE_SET_ATTRIBUTE
    return (int64_t)list;  // TODO 资源释放?? 
}

void FFIMediaDevices::getUserMedia(CJ_TO_CPP_DisplayMediaStreamOptions* video, 
                                   CJ_TO_CPP_DisplayMediaStreamOptions* audio, 
                                   int64_t id, void (*pe)(int64_t that, int64_t localVideoTrack)) {
    MediaTrackConstraints audio_;
    MediaTrackConstraints video_;
    if (video->isBool) {
        if (video->boolean) {
            MediaTrackConstraints constraints;
            constraints.Initialize();
            video_ = constraints;
        } else {
            video_ = MediaTrackConstraints();
        }
    } else {
        std::string errorMessage;
        MediaTrackConstraintSet basic;
        if (!ffiValidateAndCopyConstraintSet(*video,  NakedValueDisposition::kTreatAsIdeal, basic, errorMessage)) {
            LOGI("Failed to parse track constraints: ", errorMessage.c_str());
            video_ = MediaTrackConstraints();
        }
        std::vector<MediaTrackConstraintSet> advanced;
        MediaTrackConstraints constraints;
        constraints.Initialize(basic, advanced);
        video_ = constraints;
    }

    if (video->isBool) {
        if (audio->boolean) {
            MediaTrackConstraints constraints;
            constraints.Initialize();
            audio_ = constraints;
        } else {
            audio_ = MediaTrackConstraints();
        }
    } else { 
        std::string errorMessage;
        MediaTrackConstraintSet basic;
        if (!ffiValidateAndCopyConstraintSet(*audio,  NakedValueDisposition::kTreatAsIdeal, basic, errorMessage)) {
            LOGI("Failed to parse track constraints: ", errorMessage.c_str());
            audio_ = MediaTrackConstraints();
        }
        std::vector<MediaTrackConstraintSet> advanced;
        MediaTrackConstraints constraints;
        constraints.Initialize(basic, advanced);
        audio_ = constraints;
    }
    getUserMedia(video_, audio_, id, pe);
}


void FFIMediaDevices::getUserMedia(MediaTrackConstraints video, MediaTrackConstraints audio, int64_t id, void (*pe)(int64_t that, int64_t localVideoTrack)) {
    audioConstraints_ = std::move(audio);
    videoConstraints_ = std::move(video);
    user_media_stream_ = factory_->GetFactory()->CreateLocalMediaStream(rtc::CreateRandomUuid());
    if (!user_media_stream_) {
        CANGJIE_THROW("Failed to create media stream");
        return;
    }
    if (!audioConstraints_.IsNull()) {
        std::string errorMessage;
        auto audioTrack = CreateAudioTrack(&errorMessage);
        if (audioTrack) {
            user_media_stream_->AddTrack(audioTrack);
        } else {
            CANGJIE_THROW(errorMessage);
            return;
        }
    }

    if (!videoConstraints_.IsNull()) {
        std::string errorMessage;
        auto videoTrack = CreateVideoTrack2(&errorMessage);
        if (videoTrack) {
            user_media_stream_->AddTrack(videoTrack);
        } else {
            CANGJIE_THROW(errorMessage);
            return;
        }
    }
    cj_func_call_back2_ = pe;
    Cangjie_CallBack(new CallbackData{this, id},
        [](uv_work_t *work) {
            CallbackData* t = static_cast<CallbackData *>(work->data);
            FFIMediaDevices* that = t->md;
            that->ffiUserMediaStream_ = new FFIMediaStream(that->factory_, that->user_media_stream_);
            if(that->cj_func_call_back2_) {
                that->cj_func_call_back2_(t->id, (int64_t)that->ffiUserMediaStream_);
            } 
        },
        [](uv_work_t *work, int status) {
            free(work->data);
        }
    );
    
}


int64_t FFIMediaDevices::getDisplayMedia(CJ_TO_CPP_DisplayMediaStreamOptions* video, 
                                      CJ_TO_CPP_DisplayMediaStreamOptions* audio, 
                                      CJ_TO_CPP_DisplayMediaStreamOptions* systemAudio){
    MediaTrackConstraints audio_;
    MediaTrackConstraints systemAudio_;
    MediaTrackConstraints video_;
    if (video->isBool) {
        if (video->boolean) {
            MediaTrackConstraints constraints;
            constraints.Initialize();
            video_ = constraints;
        } else {
            video_ = MediaTrackConstraints();
        }
    } else {
        std::string errorMessage;
        MediaTrackConstraintSet basic;
        if (!ffiValidateAndCopyConstraintSet(*video,  NakedValueDisposition::kTreatAsIdeal, basic, errorMessage)) {
            LOGI("Failed to parse track constraints: ", errorMessage.c_str());
            video_ = MediaTrackConstraints();
        }
        std::vector<MediaTrackConstraintSet> advanced;
        MediaTrackConstraints constraints;
        constraints.Initialize(basic, advanced);
        video_ = constraints;
    }
    if (audio->isBool) {
        if (audio->boolean) {
            MediaTrackConstraints constraints;
            constraints.Initialize();
            audio_ = constraints;
        } else {
            audio_ = MediaTrackConstraints();
        }
    } else {
        std::string errorMessage;
        MediaTrackConstraintSet basic;
        if (!ffiValidateAndCopyConstraintSet(*audio,  NakedValueDisposition::kTreatAsIdeal, basic, errorMessage)) {
            LOGI("Failed to parse track constraints: ", errorMessage.c_str());
            audio_ = MediaTrackConstraints();
        }
        std::vector<MediaTrackConstraintSet> advanced;
        MediaTrackConstraints constraints;
        constraints.Initialize(basic, advanced);
        audio_ = constraints;
    }
    if (systemAudio->isBool) {
        if (systemAudio->boolean) {
            MediaTrackConstraints constraints;
            constraints.Initialize();
            systemAudio_ = constraints;
        } else {
            systemAudio_ = MediaTrackConstraints();
        }
    } else {
        std::string errorMessage;
        MediaTrackConstraintSet basic;
        if (!ffiValidateAndCopyConstraintSet(*systemAudio,  NakedValueDisposition::kTreatAsIdeal, basic, errorMessage)) {
            LOGI("Failed to parse track constraints: ", errorMessage.c_str());
            systemAudio_ = MediaTrackConstraints();
        }
        std::vector<MediaTrackConstraintSet> advanced;
        MediaTrackConstraints constraints;
        constraints.Initialize(basic, advanced);
        systemAudio_ = constraints;
    }
    return getDisplayMedia(video_, audio_, systemAudio_);
}


int64_t FFIMediaDevices::getDisplayMedia(MediaTrackConstraints video, MediaTrackConstraints audio, MediaTrackConstraints systemAudio){

    audioConstraints_ = std::move(audio);
    systemAudioConstraints_ = std::move(systemAudio);
    videoConstraints_ = std::move(video);
    
    display_media_stream_ = factory_->GetFactory()->CreateLocalMediaStream(rtc::CreateRandomUuid());
    
    std::shared_ptr<SystemAudioReceiver> systemAudioReceiver;
    if (!systemAudioConstraints_.IsNull()) {
        if (videoConstraints_.IsNull()) {
            CANGJIE_THROW("System audio should not be enabled individually");
            return 0;
        }

        // Use default options
        systemAudioReceiver = SystemAudioReceiver::Create();
        std::string errorMessage;
        auto audioTrack = CreateSystemAudioTrack(systemAudioReceiver, &errorMessage);
        if (audioTrack) {
            display_media_stream_->AddTrack(audioTrack);
        } else {
            CANGJIE_THROW(errorMessage);
            return 0;
        }
    }

    if (!videoConstraints_.IsNull()) {
        std::string errorMessage;
        auto videoTrack = CreateVideoTrack1(systemAudioReceiver, &errorMessage);
        if (videoTrack) {
            display_media_stream_->AddTrack(videoTrack);
        } else {
            CANGJIE_THROW(errorMessage);
        }
    }
    
//    cj_func_call_back1_ = pe; // cangjie func
//    Cangjie_CallBack(new CallbackData{this, id},
//                     [](uv_work_t *work) {
//        CallbackData* t = static_cast<CallbackData *>(work->data);
//        FFIMediaDevices* that = t->md;
//        that->ffiDisplayMediaStream_ = new FFIMediaStream(that->factory_, that->display_media_stream_);
//        if(that->cj_func_call_back1_) {
//            that->cj_func_call_back1_(t->id, (int64_t)that->ffiDisplayMediaStream_); // call cangjie func 
//        }
//    }, 
//    [](uv_work_t *work, int status) {
//        free(work->data);
//    });
    this->ffiDisplayMediaStream_ = new FFIMediaStream(this->factory_, this->display_media_stream_);
    return (int64_t)this->ffiDisplayMediaStream_;
}

// DisplayMedia
rtc::scoped_refptr<VideoTrackInterface> FFIMediaDevices::CreateVideoTrack1(
    std::shared_ptr<SystemAudioReceiver> systemAudioReceiver, std::string* errorMessage)
{
    ScreenCaptureOptions options;
    GetScreenCaptureOptionsFromConstraints(videoConstraints_, options);
    RTC_DLOG(LS_INFO) << "Screen capture options: " << options.ToString();

    auto screenCapturer = ScreenCapturer::Create(options, std::move(systemAudioReceiver));
    if (!screenCapturer) {
        if (errorMessage) {
            *errorMessage = "Failed to create screen capturer";
        }
        return nullptr;
    }

    auto videoSource = factory_->CreateVideoSource(std::move(screenCapturer));
    if (!videoSource) {
        if (errorMessage) {
            *errorMessage = "Failed to create video source";
        }
        return nullptr;
    }

    auto videoTrack = factory_->CreateVideoTrack(rtc::CreateRandomUuid(), videoSource);
    if (!videoTrack) {
        if (errorMessage) {
            *errorMessage = "Failed to create video track";
        }
        return nullptr;
    }

    return videoTrack;
}

rtc::scoped_refptr<VideoTrackInterface> FFIMediaDevices::CreateVideoTrack2(std::string* errorMessage)
{
    auto cameraDevices = CameraEnumerator::GetDevices();

    CameraCaptureSettings selectedSetting;
    std::string failedConstraintName;
    if (SelectSettingsForVideo(cameraDevices, videoConstraints_, kDefaultWidth, kDefaultHeight,
                               kDefaultFrameRate, selectedSetting, failedConstraintName)) {
        RTC_DLOG(LS_INFO) << "Selected camera device: " << selectedSetting.deviceId
                          << ", resolution = " << selectedSetting.profile.resolution.width << "x"
                          << selectedSetting.profile.resolution.height
                          << ", format = " << selectedSetting.profile.format
                          << ", framerate = " << selectedSetting.profile.frameRateRange.min << "-"
                          << selectedSetting.profile.frameRateRange.max;
    } else {
        RTC_LOG(LS_ERROR) << "Failed to select settings for video: " << failedConstraintName;
        if (errorMessage) {
            *errorMessage = std::string("Unsatisfied constraint: ") + failedConstraintName;
        }
    }

    auto capturer = CameraCapturer::Create(selectedSetting.deviceId, selectedSetting.profile);
    if (!capturer) {
        if (errorMessage) {
            *errorMessage = "Failed to create camera capturer";
        }
        return nullptr;
    }

    auto videoSource = factory_->CreateVideoSource(std::move(capturer));
    if (!videoSource) {
        if (errorMessage) {
            *errorMessage = "Failed to create video source";
        }
        return nullptr;
    }

    auto videoTrack = factory_->CreateVideoTrack(rtc::CreateRandomUuid(), videoSource);
    if (!videoTrack) {
        if (errorMessage) {
            *errorMessage = "Failed to create video track";
        }
        return nullptr;
    }

    return videoTrack;
}

rtc::scoped_refptr<AudioTrackInterface> FFIMediaDevices::CreateAudioTrack(std::string* errorMessage)
{
    cricket::AudioOptions options;
    CopyConstraintsIntoAudioOptions(audioConstraints_, options);

    auto audioSource = factory_->CreateAudioSource(options);
    if (!audioSource) {
        if (errorMessage) {
            *errorMessage = "Failed to create audio source";
        }
        return nullptr;
    }
    auto audioTrack = factory_->CreateAudioTrack(rtc::CreateRandomUuid(), audioSource);
    if (!audioTrack) {
        if (errorMessage) {
            *errorMessage = "Failed to create audio track";
        }
        return nullptr;
    }

    return audioTrack;
}

rtc::scoped_refptr<AudioTrackInterface> FFIMediaDevices::CreateSystemAudioTrack(
     std::shared_ptr<SystemAudioReceiver> systemAudioReceiver, std::string* errorMessage)
{
    cricket::AudioOptions options;
    CopyConstraintsIntoAudioOptions(systemAudioConstraints_, options);

    auto audioSource = factory_->CreateAudioSource(options, std::move(systemAudioReceiver));
    if (!audioSource) {
        if (errorMessage) {
            *errorMessage = "Failed to create system audio source";
        }
        return nullptr;
    }

    auto audioTrack = factory_->CreateAudioTrack(rtc::CreateRandomUuid(), audioSource);
    if (!audioTrack) {
        if (errorMessage) {
            *errorMessage = "Failed to create system audio track";
        }
        return nullptr;
    }

    return audioTrack;
}
