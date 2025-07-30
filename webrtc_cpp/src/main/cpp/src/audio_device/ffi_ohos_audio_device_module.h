#ifndef WEBRTC_FFI_OHOS_AUDIO_DEVICE_MODULE_H_
#define WEBRTC_FFI_OHOS_AUDIO_DEVICE_MODULE_H_

#include "ohos_audio_device_module.h"
#include "audio_input.h"
#include "audio_output.h"

#include "modules/audio_device/include/audio_device.h"
#include "modules/audio_device/fine_audio_buffer.h"

#include <map>
#include <list>
#include <string>
#include <memory>

namespace webrtc{

class ffiAudioDeviceModule : public AudioInput::Observer,
                            public AudioOutput::Observer 
{
public:
    ffiAudioDeviceModule(bool ffiUseStereoInput,bool ffiUseStereoOutput);
    ~ffiAudioDeviceModule();
    rtc::scoped_refptr<OhosAudioDeviceModule> getAdm();

protected:
    void OnAudioInputError(AudioInput* input, AudioErrorType type,const std::string& message) override;
    void OnAudioInputStateChange(AudioInput* input, AudioStateType newState) override;
    void OnAudioInputDataReady(
        AudioInput* input, void* buffer, int32_t length, int64_t timestampUs, int64_t deleyUs) override;

    void OnAudioOutputError(AudioOutput* output, AudioErrorType type, const std::string& message) override;
    void OnAudioOutputStateChange(AudioOutput* output, AudioStateType newState) override;

private:
    rtc::scoped_refptr<OhosAudioDeviceModule> adm_;

};

}

#endif // WEBRTC_FFI_OHOS_AUDIO_DEVICE_MODULE_H_