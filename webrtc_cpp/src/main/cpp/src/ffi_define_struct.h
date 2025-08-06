//
// Created on 2025/8/6.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef WEBRTC4CJ_FFI_DEFINE_STRUCT_H
#define WEBRTC4CJ_FFI_DEFINE_STRUCT_H

#include <cstdint>

typedef struct {
    int64_t width;
    int64_t height;
    double aspectRatio;
    double frameRate;
    char* facingMode;
    char* resizeMode;
    int64_t sampleRate;
    int64_t sampleSize;
    bool echoCancellation;
    bool autoGainControl;
    bool noiseSuppression;
    double latency;
    int64_t channelCount;
    char* deviceId;
    char* groupId;
    char* ohosScreenCaptureMode;
    int64_t ohosScreenCaptureDisplayId;
    char* ohosScreenCaptureMissionId;
    char* ohosScreenCaptureWindowFilter;
    char* ohosScreenCaptureAudioFilter;
    char* ohosScreenCaptureSkipPrivacyMode;
    bool ohosScreenCaptureAutoRotation;
} CJ_MediaTrackConstraintSet;


typedef struct
{
    CJ_MediaTrackConstraintSet obj;
    bool boolean;
    bool isBool;
} CJ_TO_CPP_DisplayMediaStreamOptions;


typedef struct {
    const char* deviceId;
    const char* groupId;
    const char* label;
    const char* kind;
} CJ_EnumerateDevicesInfo;

typedef struct {
    const char* id;
    const char* kind;
    const char* readyState;
    bool enabled;
} CJ_ffiMediaStreamTrackJson;

typedef struct {
    const char* name;
    const bool isSupported;
} CJ_SupportedConstraints;

// c侧数组需要返回长度, 结构体
typedef struct {
    CJ_EnumerateDevicesInfo* ptr;
    int64_t size;
} CJ_ReturnEnumerateDevicesInfo;

typedef struct {
    int64_t* ptr;
    int64_t size;
} CJ_ReturnArray;

#endif //WEBRTC4CJ_FFI_DEFINE_STRUCT_H
