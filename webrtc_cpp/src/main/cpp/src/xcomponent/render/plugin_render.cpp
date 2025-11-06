/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

#include <cstdint>
#include "plugin_render.h"
#include <cstdint>

#include "plugin_render.h"

namespace NativeXComponentSample {

PluginRender::PluginRender(int64_t& id)
{
    this->id_ = id;
    this->eglCore_ = new EGLCore();
    hasDraw_ = 0;
    hasChangeColor_ = 0;
}

void PluginRender::ChangeColor()
{
    eglCore_->ChangeColor(hasChangeColor_);
}

void PluginRender::DrawPattern()
{
    eglCore_->Draw(hasDraw_);
}

void PluginRender::InitNativeWindow(OHNativeWindow *window)
{
    eglCore_->EglContextInit(window);
}

void PluginRender::UpdateNativeWindowSize(int width, int height)
{
    eglCore_->UpdateSize(width, height);
    if (!hasChangeColor_ && !hasDraw_) {
        eglCore_->Background();
    }
}

int32_t PluginRender::HasDraw()
{
    return hasDraw_;
}

int32_t PluginRender::HasChangedColor()
{
    return hasChangeColor_;
}
} // namespace NativeXComponentSample
