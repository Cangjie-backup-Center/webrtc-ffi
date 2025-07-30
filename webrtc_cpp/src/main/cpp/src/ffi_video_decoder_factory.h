#ifndef WEBRTC_FFI_VIDEO_DECODER_FACTORY_H_
#define WEBRTC_FFI_VIDEO_DECODER_FACTORY_H_

#include "render/egl_env.h"
#include <api/video_codecs/video_decoder_factory.h>

namespace webrtc {

class ffiHardwareVideoDecoderFactory{
public:
    std::shared_ptr<EglContext> GetSharedContext();
    explicit ffiHardwareVideoDecoderFactory();

protected:

private:
    std::shared_ptr<EglContext> sharedContext_;
};

std::unique_ptr<VideoDecoderFactory> createHardwareVideoDecoderFactory(ffiHardwareVideoDecoderFactory* ffiHVDF);

}

#endif