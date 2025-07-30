#ifndef NATIVE_XCOMPONENT_PLUGIN_RENDER_H
#define NATIVE_XCOMPONENT_PLUGIN_RENDER_H

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <native_window/external_window.h>
#include "egl_core.h"

namespace NativeXComponentSample {
class PluginRender {
public:
    explicit PluginRender(int64_t& id);
    ~PluginRender()
    {
        if (eglCore_ != nullptr) {
            eglCore_->Release();
            delete eglCore_;
            eglCore_ = nullptr;
        }
    }
    void ChangeColor();
    void DrawPattern();
    int32_t HasDraw();
    int32_t HasChangedColor();
    void InitNativeWindow(OHNativeWindow* window);
    void UpdateNativeWindowSize(int width, int height);
private:
    EGLCore* eglCore_;
    int64_t id_;
    int32_t hasDraw_;
    int32_t hasChangeColor_;
};
} // namespace NativeXComponentSample
#endif // NATIVE_XCOMPONENT_PLUGIN_RENDER_H
