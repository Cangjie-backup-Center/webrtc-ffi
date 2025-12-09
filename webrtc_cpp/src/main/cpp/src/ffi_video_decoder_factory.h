/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC_FFI_VIDEO_DECODER_FACTORY_H_
#define WEBRTC_FFI_VIDEO_DECODER_FACTORY_H_

#include "render/egl_env.h"
#include <api/video_codecs/video_decoder_factory.h>

namespace webrtc {

class ffiVideoDecoderFactory {
public:
    std::shared_ptr<EglContext> GetSharedContext();
    explicit ffiVideoDecoderFactory();

protected:

private:
    std::shared_ptr<EglContext> sharedContext_;
};

std::unique_ptr<VideoDecoderFactory> createHardwareVideoDecoderFactory(ffiVideoDecoderFactory* ffiHVDF);

std::unique_ptr<VideoDecoderFactory> CreateDefaultVideoDecoderFactory();
}

#endif