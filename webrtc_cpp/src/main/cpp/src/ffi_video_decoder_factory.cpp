/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include "ffi_video_decoder_factory.h"
#include "video_codec/hardware_video_decoder_factory.h"
#include "render/egl_env.h"
#include "video_codec/default_video_decoder_factory.h"
#include "video_codec/software_video_decoder_factory.h"

namespace webrtc {

ffiHardwareVideoDecoderFactory::ffiHardwareVideoDecoderFactory()
{
    sharedContext_ = EglEnv::GetDefault().GetContext();
}

std::shared_ptr<EglContext> ffiHardwareVideoDecoderFactory::GetSharedContext()
{
    return sharedContext_;
}

ffiHardwareVideoDecoderFactory::~ffiHardwareVideoDecoderFactory() = default;

ffiSoftwareVideoDecoderFactory::ffiSoftwareVideoDecoderFactory()
{

}

ffiSoftwareVideoDecoderFactory::~ffiSoftwareVideoDecoderFactory() = default;

std::unique_ptr<VideoDecoderFactory> createHardwareVideoDecoderFactory(ffiHardwareVideoDecoderFactory* ffiHVDF)
{
    if (ffiHVDF != nullptr) {
        auto sharedContext = ffiHVDF->GetSharedContext();
        return std::make_unique<adapter::HardwareVideoDecoderFactory>(sharedContext);
    }
    return nullptr;
}

std::unique_ptr<VideoDecoderFactory> createSoftwareVideoDecoderFactory(ffiSoftwareVideoDecoderFactory* ffiSVDF)
{
    if (ffiSVDF != nullptr) {
        return std::make_unique<adapter::SoftwareVideoDecoderFactory>();
    }
    return nullptr;
}


std::unique_ptr<VideoDecoderFactory> CreateDefaultVideoDecoderFactory()
{
    return std::make_unique<adapter::DefaultVideoDecoderFactory>(EglEnv::GetDefault().GetContext());
}

}

