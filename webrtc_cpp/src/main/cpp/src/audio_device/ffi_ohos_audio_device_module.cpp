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
    // std::lock_guard<std::mutex> lock(mutex_);
    // auto it = eventHandlers_.find(kEventNameCapturerSamplesReady);
    // if (it == eventHandlers_.end()) {
    //     return;
    // }

    // auto data = new rtc::CopyOnWriteBuffer((uint8_t*)buffer, length);

    // auto& tsfn = it->second.tsfn;
    // Reference<Napi::Value>* context = tsfn.GetContext();
    // napi_status status =
    //     tsfn.NonBlockingCall([context, sampleRate = input->GetSampleRate(), channelCount = input->GetChannelCount(),
    //                           data](Napi::Env env, Napi::Function jsCallback) {
    //         auto arrayBuffer = ArrayBuffer::New(
    //             env, static_cast<void*>(data->MutableData()), data->size(),
    //             [](Napi::Env /*env*/, void* /*data*/, rtc::CopyOnWriteBuffer* hint) {
    //                 RTC_DLOG(LS_VERBOSE) << "release rtc::CopyOnWriteBuffer";
    //                 delete hint;
    //             },
    //             data);

    //         auto jsAudioSamples = Object::New(env);
    //         jsAudioSamples.Set("sampleRate", Number::New(env, sampleRate));
    //         jsAudioSamples.Set("audioFormat", Number::New(env, AUDIOSTREAM_SAMPLE_S16LE));
    //         jsAudioSamples.Set("channelCount", Number::New(env, channelCount));
    //         jsAudioSamples.Set("data", arrayBuffer);

    //         auto jsEvent = Object::New(env);
    //         jsEvent.Set("samples", jsAudioSamples);
    //         jsCallback.Call(context ? context->Value() : env.Undefined(), {jsEvent});
    //     });
    // if (status != napi_ok) {
    //     RTC_LOG(LS_ERROR) << " tsfn call error: " << status;
    // }
}


void ffiAudioDeviceModule::OnAudioOutputError(AudioOutput* output, AudioErrorType type, const std::string& message) {


}

void ffiAudioDeviceModule::OnAudioOutputStateChange(AudioOutput* output, AudioStateType newState) {

}
 

}