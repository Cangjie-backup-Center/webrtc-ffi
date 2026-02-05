#ifndef WEBRTC_FFI_VIDEO_ENCODER_FACTORY_H_
#define WEBRTC_FFI_VIDEO_ENCODER_FACTORY_H_

#include "api/video_codecs/video_encoder_factory.h"
#include "render/egl_env.h"

#include "hilog/log.h"

#define OHOS_LOG_DOMAIN 0xD001234

namespace webrtc {

class ffiHardwareVideoEncoderFactory {
public:
    explicit ffiHardwareVideoEncoderFactory();
    std::shared_ptr<EglContext> getSharedContext();
    bool getEnableH264HighProfile();
    ~ffiHardwareVideoEncoderFactory();

private:
    std::shared_ptr<EglContext> sharedContext_;
    bool enableH264HighProfile_{false};
};

class ffiSoftwareVideoEncoderFactory {
public:
    explicit ffiSoftwareVideoEncoderFactory();
    ~ffiSoftwareVideoEncoderFactory();

protected:

private:

};

std::unique_ptr<VideoEncoderFactory> createHardwareVideoEncoderFactory(ffiHardwareVideoEncoderFactory* ffiHVEF);
std::unique_ptr<VideoEncoderFactory> createSoftwareVideoEncoderFactory(ffiSoftwareVideoEncoderFactory* ffiSVEF);

std::unique_ptr<VideoEncoderFactory> CreateDefaultVideoEncoderFactory();
}

#endif // WEBRTC_FFI_VIDEO_ENCODER_FACTORY_H_