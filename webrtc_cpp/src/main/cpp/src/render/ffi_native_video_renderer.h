/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#ifndef WEBRTC_FFI_WINDOW_RENDER_H
#define WEBRTC_FFI_WINDOW_RENDER_H

#include "render/native_window_renderer_gl.h"
#include "render/native_window_renderer_raster.h"
#include "native_window_renderer.h"
#include "../render/egl_env.h"
#include "../ffi_media_stream_track.h"
#include "rtc_base/logging.h"
#include "api/scoped_refptr.h"
#include "api/media_stream_track.h"

#include <optional>
#include <string>
#include <memory>

namespace webrtc {

class ffiNativeVideoRenderer {
public: 
    ffiNativeVideoRenderer();
    ~ffiNativeVideoRenderer();

    void ffiNativeVideoRendererInit(int64_t surfaceId);
    void setVideoTrack(int64_t ffiMST);
    void setMirror(bool mirrorBool);
    void setMirrorVertically(bool mirrorVerticallyBool);
    void setScalingMode(int32_t scalingMode);

    void release();

protected:
    void removeSink();
    void addSink();

private:
    std::unique_ptr<adapter::NativeWindowRenderer> renderer_;
    std::shared_ptr<EglContext> sharedContext_;
    ffiMediaStreamTrack* ffiMST_;

    std::optional<std::string> surfaceId_;
};

}

#endif // WEBRTC_FFI_WINDOW_RENDER_H