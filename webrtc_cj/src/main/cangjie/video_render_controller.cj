/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package webrtc_cj

import kit.UIKit.*
import ohos.state_macro_manage.*
import std.convert.*

let XComponentController1_TAG: String = "[XComponentController1]"

public class VideoRenderController <: XComponentController {
    private var renderer : Int64 = 0
    public var mySurfaceId: String = ""

    protected override func onSurfaceCreated(surfaceId: String) {
        mySurfaceId = surfaceId
        unsafe {
//            ffi_SetSurfaceId(Int64.parse(surfaceId))
            renderer = unsafe {ffi_newNativeVideoRenderer(LibC.mallocCString(mySurfaceId))}
        }
    }

//    protected override func onSurfaceChanged(surfaceId: String, rect: SurfaceRect) {
//        // 在onSurfaceChanged中调用ChangeSurface绘制内容
//        unsafe {
//            ffi_ChangeSurface(Int64.parse(surfaceId), 1134.0, 1002.0)
//        }
//    }

    public func setVideoTrack(mst : MediaStreamTrack): Unit {
        unsafe {ffi_setVideoTrack(renderer, mst.getID())}
    }

    public func setMirror(mirrorVerticallyBool: Bool): Unit {
        unsafe  {ffi_setMirror(renderer, mirrorVerticallyBool)}
    }

    public func setScalingMode(scalingMode : FFIScalingModeEnum): Unit {
        let FFISme = FFIScalingModeEnum.GET(scalingMode)
        unsafe {ffi_setScalingMode(renderer, FFIScalingModeEnum.GET(scalingMode))}
    }

   protected override func onSurfaceDestroyed(surfaceId: String) {
   }
}
