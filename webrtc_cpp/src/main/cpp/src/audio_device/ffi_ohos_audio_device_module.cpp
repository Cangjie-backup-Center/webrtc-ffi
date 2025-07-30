#include "ffi_ohos_audio_device_module.h"
#include "audio_common.h"
#include "modules/audio_device/audio_device_buffer.h"
#include "api/make_ref_counted.h"
#include "rtc_base/logging.h"

#include <memory>
#include <utility>

namespace webrtc{
ffiAudioDeviceModule::ffiAudioDeviceModule(bool ffiUseStereoInput,bool ffiUseStereoOutput){
    AudioInputOptions inputOptions;
    AudioOutputOptions outputOptions;
    
    // inputOptions.source = useStereoInput;

    bool useStereoInput = ffiUseStereoInput;
    inputOptions.channelCount = useStereoInput ? kAudioChannelCount_Stereo : kAudioChannelCount_Mono;

    bool useStereoOutput = ffiUseStereoOutput;
    outputOptions.channelCount = useStereoOutput ? kAudioChannelCount_Stereo : kAudioChannelCount_Mono;
 
    adm_ = rtc::make_ref_counted<OhosAudioDeviceModule>(
        std::move(inputOptions), std::move(outputOptions), AudioDeviceModule::kPlatformDefaultAudio);
    
    adm_->RegisterInputObserver(this);
    adm_->RegisterOutputObserver(this);
}

ffiAudioDeviceModule::~ffiAudioDeviceModule(){

}

rtc::scoped_refptr<OhosAudioDeviceModule> ffiAudioDeviceModule::getAdm(){
    return adm_;
}

void ffiAudioDeviceModule::OnAudioInputError(AudioInput* input, AudioErrorType type,const std::string& message) {
}

void ffiAudioDeviceModule::OnAudioInputStateChange(AudioInput* input, AudioStateType newState) {
}

void ffiAudioDeviceModule::OnAudioInputDataReady(AudioInput* input, void* buffer, 
                                                int32_t length, int64_t timestampUs, 
                                                int64_t deleyUs)
{
}


void ffiAudioDeviceModule::OnAudioOutputError(AudioOutput* output, AudioErrorType type, const std::string& message) {


}

void ffiAudioDeviceModule::OnAudioOutputStateChange(AudioOutput* output, AudioStateType newState) {

}
 

}