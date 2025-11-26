/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC_FFI_VIDEO_ENCODER_FACTORY_H_
#define WEBRTC_FFI_VIDEO_ENCODER_FACTORY_H_

#include "api/video_codecs/video_encoder_factory.h"
#include "render/egl_env.h"

#include "hilog/log.h"

#define OHOS_LOG_DOMAIN 0xD001234

namespace webrtc {

class ffiVideoEncoderFactory {
public:
    explicit ffiVideoEncoderFactory();
    std::shared_ptr<EglContext> getSharedContext();
    bool getEnableH264HighProfile();
    ~ffiVideoEncoderFactory();

private:
    std::shared_ptr<EglContext> sharedContext_;
    bool enableH264HighProfile_{false};
};

std::unique_ptr<VideoEncoderFactory> createHardwareVideoEncoderFactory(ffiVideoEncoderFactory* ffiHVEF);

}

#endif // WEBRTC_FFI_VIDEO_ENCODER_FACTORY_H_