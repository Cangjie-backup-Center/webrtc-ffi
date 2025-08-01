/*
 * @Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package webrtc

import kit.UIKit.*
import ohos.state_macro_manage.*
import std.convert.*

let XComponentController1_TAG: String = "[XComponentController1]"

public struct ScalingMode {
    public let fill: Int32 = 0
    public let aspectFill: Int32 = 1
    public let aspectFit: Int32 = 2
}

public class VideoRenderController <: XComponentController {
    private var renderer : Int64 = 0
    public var mySurfaceId: String = ""

    protected override func onSurfaceCreated(surfaceId: String) {
        mySurfaceId = surfaceId
        cj_SetSurfaceId(Int64.parse(surfaceId))
    }

    protected override func onSurfaceChanged(surfaceId: String, rect: SurfaceRect) {
        // 在onSurfaceChanged中调用ChangeSurface绘制内容
        cj_ChangeSurface(Int64.parse(surfaceId), 1134.0, 1002.0)
    }

    public func newNativeVideoRenderer(): Unit {
        renderer = cj_newNativeVideoRenderer(Int64.parse(mySurfaceId))
    }

    public func setVideoTrack(mstID : Int64) {
        cj_setVideoTrack(renderer, mstID)
    }

    public func setMirror(mirrorVerticallyBool: Bool) {
        cj_setMirror(renderer, mirrorVerticallyBool)
    }

    public func setScalingMode(scalingMode : Int32) {
        cj_setScalingMode(renderer, scalingMode)
    }

   protected override func onSurfaceDestroyed(surfaceId: String) {
   }
}
