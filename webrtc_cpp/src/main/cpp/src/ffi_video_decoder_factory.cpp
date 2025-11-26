/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "ffi_video_decoder_factory.h"
#include "video_codec/hardware_video_decoder_factory.h"

namespace webrtc {

ffiVideoDecoderFactory::ffiVideoDecoderFactory()
{
    sharedContext_ = EglEnv::GetDefault().GetContext();
}

std::shared_ptr<EglContext> ffiVideoDecoderFactory::GetSharedContext()
{
    return sharedContext_;
}

std::unique_ptr<VideoDecoderFactory> createHardwareVideoDecoderFactory(ffiVideoDecoderFactory* ffiHVDF)
{
    if (ffiHVDF != nullptr) {
        auto sharedContext = ffiHVDF->GetSharedContext();
        return std::make_unique<adapter::HardwareVideoDecoderFactory>(sharedContext);
    }
    return nullptr;
}

}

