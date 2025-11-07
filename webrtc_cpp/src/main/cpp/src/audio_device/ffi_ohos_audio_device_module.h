/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC_FFI_OHOS_AUDIO_DEVICE_MODULE_H_
#define WEBRTC_FFI_OHOS_AUDIO_DEVICE_MODULE_H_

#include "ffi_cj_class.h"
#include "ohos_audio_device_module.h"
#include "audio_input.h"
#include "audio_output.h"
#include "event/ffi_event_target.h"

#include "modules/audio_device/include/audio_device.h"
#include "modules/audio_device/fine_audio_buffer.h"

#include <map>
#include <list>
#include <string>
#include <memory>

namespace webrtc{

typedef struct {
    int32_t sampleRate;
    int32_t audioFormat;
    int32_t channelCount;
    uint8_t* data;
    int32_t dataLength;
} CJ_AudioDataEvent;

typedef struct {
    int32_t type;
    char* message;
} CJ_AudioErrorEvent;

class ffiAudioDeviceModule : public AudioInput::Observer,
                            public AudioOutput::Observer ,
                            public FFIEventTarget<ffiAudioDeviceModule>,
                            public CJ_CLASS_BASE::FFICangjieClassID
{
public:
    ffiAudioDeviceModule(bool ffiUseStereoInput,bool ffiUseStereoOutput);
    ~ffiAudioDeviceModule();
    rtc::scoped_refptr<OhosAudioDeviceModule> getAdm();

    // 设置音频数据回调函数
    void SetOnAudioOutputStateChangeCallback(void (*callback)(int64_t id, int newState));
    void SetOnAudioInputStateChangeCallback(void (*callback)(int64_t id, int newState));
    void SetOnAudioInputDataReadyCallback(void (*callback)(int64_t id, CJ_AudioDataEvent event));
    void SetOnAudioOutputErrorCallback(void (*callback)(int64_t id, CJ_AudioErrorEvent event));
    void SetOnAudioInputErrorCallback(void (*callback)(int64_t id, CJ_AudioErrorEvent event));

protected:
    void OnAudioInputError(AudioInput* input, AudioErrorType type,const std::string& message) override;
    void OnAudioInputStateChange(AudioInput* input, AudioStateType newState) override;
    void OnAudioInputDataReady(
        AudioInput* input, void* buffer, int32_t length, int64_t timestampUs, int64_t deleyUs) override;

    void OnAudioOutputError(AudioOutput* output, AudioErrorType type, const std::string& message) override;
    void OnAudioOutputStateChange(AudioOutput* output, AudioStateType newState) override;

private:
    rtc::scoped_refptr<OhosAudioDeviceModule> adm_;
    std::unique_ptr<FineAudioBuffer> inputAudioBuffer_;

    // 音频数据回调函数指针
    void (*cj_func_call_OnAudioOutputStateChange_)(int64_t id, int newState) = nullptr;
    void (*cj_func_call_OnAudioInputStateChange_)(int64_t id, int newState) = nullptr;
    void (*cj_func_call_OnAudioInputDataReady_)(int64_t id, CJ_AudioDataEvent event) = nullptr;
    void (*cj_func_call_OnAudioOutputError_)(int64_t id, CJ_AudioErrorEvent event) = nullptr;
    void (*cj_func_call_OnAudioInputError_)(int64_t id, CJ_AudioErrorEvent event) = nullptr;

    mutable std::mutex mutex_;
};

}

#endif // WEBRTC_FFI_OHOS_AUDIO_DEVICE_MODULE_H_