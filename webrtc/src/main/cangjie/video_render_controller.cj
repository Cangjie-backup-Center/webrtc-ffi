package webrtc

import kit.UIKit.*
import ohos.state_macro_manage.*
import std.convert.*

let XComponentController1_TAG: String = "[XComponentController1]"

public struct ScalingMode {
    let fill: Int32 = 0
    let aspectFill: Int32 = 1
    let aspectFit: Int32 = 2
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

    public func newNativeVideoRenderer(): Int64 {
        renderer = cj_newNativeVideoRenderer(Int64.parse(mySurfaceId))
        return renderer
    }

    public func setVideoTrack(ffiNVR : Int64) {
        cj_setVideoTrack(ffiNVR, Int64.parse(mySurfaceId))
    }

    public func setMirror(ffiNVR : Int64, mirrorVerticallyBool: Bool) {
        cj_setMirror(ffiNVR, mirrorVerticallyBool)
    }

    public func setScalingMode(ffiNVR : Int64, scalingMode : Int64) {
        cj_setScalingMode(ffiNVR, scalingMode)
    }

   protected override func onSurfaceDestroyed(surfaceId: String) {
   }
}
