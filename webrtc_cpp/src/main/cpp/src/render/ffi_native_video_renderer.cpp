#include "ffi_native_video_renderer.h"
#define OHOS_LOG_DOMAIN 0xD001234

namespace webrtc {
ffiNativeVideoRenderer::ffiNativeVideoRenderer()
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    ffiMST_ = nullptr;
}

ffiNativeVideoRenderer::~ffiNativeVideoRenderer()
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    this->removeSink();
//    delete ffiMST_;
}

void ffiNativeVideoRenderer::removeSink()
{
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    if (!renderer_) {
        return;
    }

    if (ffiMST_ == nullptr) {
        return;
    }
    ffiMST_->RemoveSink(renderer_.get());
}

void ffiNativeVideoRenderer::addSink()
{
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    if (!renderer_) {
        return;
    }
    if (ffiMST_ == nullptr) {
        return;
    }
    ffiMST_->AddSink(renderer_.get());
}

void ffiNativeVideoRenderer::ffiNativeVideoRendererInit(char* surfaceId)
{
    surfaceId_ = std::string(surfaceId);
    delete[] surfaceId;
    sharedContext_ = EglEnv::GetDefault().GetContext();
    auto nativeWindow = ohos::NativeWindow::CreateFromSurfaceId(std::stoull(*surfaceId_));
    if (nativeWindow.IsEmpty()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, OHOS_LOG_DOMAIN, "webrtc", "CreateFromSurfaceId failed");
    }
    renderer_ = adapter::NativeWindowRendererGl::Create(nativeWindow, sharedContext_, "native-window-renderer");
}

void ffiNativeVideoRenderer::setVideoTrack(int64_t ffiMST)
{
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    removeSink();
    if (ffiMST_){
        delete ffiMST_;
        ffiMST_ = nullptr;
    }
    ffiMST_ = reinterpret_cast<ffiMediaStreamTrack*>(ffiMST);
    addSink();
}

void ffiNativeVideoRenderer::setMirror(bool mirrorBool)
{
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    if (renderer_) {
        renderer_->SetMirrorHorizontally(mirrorBool);
    }
}

void ffiNativeVideoRenderer::setMirrorVertically(bool mirrorVerticallyBool)
{
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    if (renderer_) {
        renderer_->SetMirrorVertically(mirrorVerticallyBool);
    }
}

void ffiNativeVideoRenderer::setScalingMode(int32_t scalingMode)
{
    RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    if (renderer_) {
        renderer_->SetScalingMode(
            static_cast<adapter::NativeWindowRenderer::ScalingMode>(scalingMode));
    }
}

void ffiNativeVideoRenderer::release()
{
    RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
    surfaceId_.reset();
     
    renderer_.reset();
}

}