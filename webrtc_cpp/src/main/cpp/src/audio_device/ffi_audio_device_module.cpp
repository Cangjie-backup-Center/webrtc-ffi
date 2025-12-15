#include "ffi_audio_device_module.h"
#include "audio_common.h"
#include "modules/audio_device/audio_device_buffer.h"
#include "api/make_ref_counted.h"
#include "rtc_base/logging.h"

#include <memory>
#include <utility>

namespace webrtc {
ffiAudioDeviceModule::ffiAudioDeviceModule(CJ_AudioDeviceModuleOptions options)
{
    AudioInputOptions inputOptions;
    AudioOutputOptions outputOptions; 
    
    inputOptions.source = options.inputOptionsSource;
    inputOptions.sampleRate = options.inputOptionsSampleRate;
    inputOptions.useLowLatency = options.inputOptionsUseLowLatency;
    
    outputOptions.sampleRate = options.outputOptionsSampleRate;
    outputOptions.usage = options.outputOptionsUsage;
    outputOptions.useLowLatency = options.outputOptionsUseLowLatency;
    
    bool useStereoInput = options.useStereoInput;
    inputOptions.channelCount = useStereoInput ? kAudioChannelCount_Stereo : kAudioChannelCount_Mono;

    bool useStereoOutput = options.useStereoOutput;
    outputOptions.channelCount = useStereoOutput ? kAudioChannelCount_Stereo : kAudioChannelCount_Mono;
 
    adm_ = rtc::make_ref_counted<OhosAudioDeviceModule>(
        std::move(inputOptions), std::move(outputOptions), AudioDeviceModule::kPlatformDefaultAudio);
    if (!adm_) {
        CANGJIE_THROW("Failed to create audio device module");
    }
    
    adm_->RegisterInputObserver(this);
    adm_->RegisterOutputObserver(this);
}

ffiAudioDeviceModule::~ffiAudioDeviceModule() {
}

rtc::scoped_refptr<OhosAudioDeviceModule> ffiAudioDeviceModule::getAdm()
{
    return adm_;
}

void ffiAudioDeviceModule::SetOnAudioInputErrorCallback(void (*callback)(int64_t id, CJ_AudioErrorEvent event))
{
    cj_func_call_OnAudioInputError_ = callback;
}

void ffiAudioDeviceModule::OnAudioInputError(AudioInput* input, AudioErrorType type, const std::string& message)
{
    RTC_LOG(LS_INFO) << __FUNCTION__ << "Audio input error: " << type << " " << message;
    std::lock_guard<std::mutex> lock(mutex_);
    this->Dispatch(CallbackEvent<ffiAudioDeviceModule>::Create(
        [this, type, message]
        (ffiAudioDeviceModule& target) {
            RTC_DCHECK_EQ(this, &target);
            if (this->cj_func_call_OnAudioInputError_) {
                this->cj_func_call_OnAudioInputError_(this->cj_class_key, CJ_AudioErrorEvent {
                        type : (int32_t)type,
                        message : strdup(message.c_str()),
                    }
                );
            }
        }
    ));
}

void ffiAudioDeviceModule::SetOnAudioInputStateChangeCallback(void (*callback)(int64_t id, int newState))
{
    cj_func_call_OnAudioInputStateChange_ = callback;
}

void ffiAudioDeviceModule::OnAudioInputStateChange(AudioInput* input, AudioStateType newState)
{
    RTC_LOG(LS_INFO) << __FUNCTION__ << "Audio output state change: " << newState;
    std::lock_guard<std::mutex> lock(mutex_);
    this->Dispatch(CallbackEvent<ffiAudioDeviceModule>::Create(
        [this, newState](ffiAudioDeviceModule& target) {
            RTC_DCHECK_EQ(this, &target);
            if (this->cj_func_call_OnAudioInputStateChange_) {
                this->cj_func_call_OnAudioInputStateChange_(this->cj_class_key, (int)newState);
            }
        }
    ));
}

void ffiAudioDeviceModule::SetOnAudioInputDataReadyCallback(void (*callback)(int64_t id, CJ_AudioDataEvent event))
{
    cj_func_call_OnAudioInputDataReady_ = callback;
}

void ffiAudioDeviceModule::OnAudioInputDataReady(AudioInput* input, void* buffer,
    int32_t length, int64_t timestampUs, int64_t deleyUs)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto copyData = new rtc::CopyOnWriteBuffer((uint8_t*)buffer, length);

    this->Dispatch(CallbackEvent<ffiAudioDeviceModule>::Create(
        [this, input, length, copyData]
        (ffiAudioDeviceModule& target) {
            RTC_DCHECK_EQ(this, &target);
            if (this->cj_func_call_OnAudioInputDataReady_) {
                this->cj_func_call_OnAudioInputDataReady_(this->cj_class_key, CJ_AudioDataEvent{
                        sampleRate : input->GetSampleRate(),
                        audioFormat : AUDIOSTREAM_SAMPLE_S16LE,
                        channelCount : input->GetChannelCount(),
                        data : copyData->MutableData(),
                        dataLength : length,
                    }
                );
            }
        }
    ));
}

void ffiAudioDeviceModule::SetOnAudioOutputErrorCallback(void (*callback)(int64_t id, CJ_AudioErrorEvent event))
{
    cj_func_call_OnAudioOutputError_ = callback;
}

void ffiAudioDeviceModule::OnAudioOutputError(AudioOutput* output, AudioErrorType type, const std::string& message)
{
    RTC_LOG(LS_INFO) << __FUNCTION__ << "Audio output error: " << type << " " << message;
    std::lock_guard<std::mutex> lock(mutex_);
    this->Dispatch(CallbackEvent<ffiAudioDeviceModule>::Create(
        [this, type, message]
        (ffiAudioDeviceModule& target) {
            RTC_DCHECK_EQ(this, &target);

            if (this->cj_func_call_OnAudioOutputError_) {
                this->cj_func_call_OnAudioOutputError_(this->cj_class_key, CJ_AudioErrorEvent{
                        type : (int32_t)type,
                        message : strdup(message.c_str()),
                    }
                );
            }
        }
    ));
}

void ffiAudioDeviceModule::SetOnAudioOutputStateChangeCallback(void (*callback)(int64_t id, int newState))
{
    cj_func_call_OnAudioOutputStateChange_ = callback;
}

void ffiAudioDeviceModule::OnAudioOutputStateChange(AudioOutput* output, AudioStateType newState)
{
    RTC_LOG(LS_INFO) << __FUNCTION__ << "Audio output state change: " << newState;
    std::lock_guard<std::mutex> lock(mutex_);
    this->Dispatch(CallbackEvent<ffiAudioDeviceModule>::Create(
        [this, newState]
        (ffiAudioDeviceModule& target) {
            RTC_DCHECK_EQ(this, &target);
            if (this->cj_func_call_OnAudioOutputStateChange_) {
                this->cj_func_call_OnAudioOutputStateChange_(this->cj_class_key, (int)newState);
            }
        }
    ));
}

}