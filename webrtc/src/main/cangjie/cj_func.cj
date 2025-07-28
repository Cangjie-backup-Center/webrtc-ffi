/*
 * @Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package webrtc

@C
public struct ffiAudioOptions{
    public var echo_cancellation : Bool = false
    public var noise_suppression : Bool = false
}

@C
public struct ffiCreateVideoSourceParameters{
    public var width : Float64 = 0.00
    public var height : Float64 = 0.00
    public var facingMode : CString = unsafe{LibC.mallocCString("")}
    public var isScreencast : Bool = false;
}

foreign {
    func ffi_newNativeVideoRenderer(surfaceId : Int64) : Int64
    func ffi_setVideoTrack(ffiNVR : Int64, surfaceId : Int64) : Unit
    func ffi_setMirror(ffiNVR : Int64, mirrorBool : Bool) : Unit
    func ffi_setMirrorVertically(ffiNVR : Int64, mirrorVerticallyBool : Bool) : Unit
    func ffi_setScalingMode(ffiNVR : Int64 , scalingMode : Int32) : Unit
    func ffi_release(ffiNVR : Int64) : Unit
    
    func ffi_newAudioDeviceModule(useStereoInput : Bool, useStereoOutput : Bool) : Int64
    func ffi_newHardwareVideoEncoderFactory() : Int64
    func ffi_newHardwareVideoDecoderFactory() : Int64
    func ffi_newPeerConnectionFactory(ffiADM_int64 : Int64, ffiHVEF_int64 : Int64 , ffiHVDF_int64 : Int64) : Int64
    func ffi_createAudioSource(ffiPCF_int64 : Int64, ffiao : ffiAudioOptions) : Int64
    func ffi_createAudioTrack(ffiPCF_int64 : Int64, ffi_audioId : CString) : Int64
    func ffi_createVideoSource(ffiPCF_int64 : Int64, ffiCVSP : ffiCreateVideoSourceParameters) : Int64
    func ffi_createVideoTrack(ffiPCF_int64 : Int64, ffi_videoId : CString) : Int64
    func ffi_StopAecDump(ffiPCF_int64 : Int64) : Unit

    func ffi_SetSurfaceId(surfaceId : Int64) : Unit
    func ffi_ChangeSurface(surfaceId : Int64, width : Float64, height : Float64) : Unit
    func ffi_DrawPattern(surfaceId : Int64) :Unit
    func ffi_ChangeColor(surfaceId : Int64) : Unit
    func ffi_DestroySurface(surfaceId : Int64) : Unit 
    func ffi_GetXComponentHasDraw(surfaceId : Int64) : Bool;
    func ffi_XComponentHasChangeColor(surfaceId : Int64) : Bool;    
}

public func cj_newNativeVideoRenderer(surfaceId : Int64) : Int64 {
    unsafe {
        return ffi_newNativeVideoRenderer(surfaceId)
    }
}

public func cj_setVideoTrack(ffiNVR : Int64, ffiMST : Int64) : Unit {
    unsafe {
        ffi_setVideoTrack(ffiNVR , ffiMST)
    }
}

public func cj_setMirror(cjNVR : Int64, mirrorBool : Bool) : Unit {
    unsafe {
        ffi_setMirror(cjNVR , mirrorBool)
    }
}

public func cj_setMirrorVertically(cjNVR : Int64, mirrorVerticallyBool : Bool) : Unit {
    unsafe {
        ffi_setMirrorVertically(cjNVR , mirrorVerticallyBool)
    }
}

public func cj_setScalingMode(cjNVR : Int64, scalingMode : Int32) : Unit {
    unsafe {
        ffi_setScalingMode(cjNVR , scalingMode)
    }
}

public func cj_release(cjNVR : Int64) : Unit {
    unsafe {
        ffi_release(cjNVR)
    }
}

public func cj_newAudioDeviceModule(useStereoInput : Bool, useStereoOutput : Bool) : Int64{
    unsafe {
        return ffi_newAudioDeviceModule(useStereoInput , useStereoOutput)
    }
}

public func cj_newHardwareVideoEncoderFactory() : Int64 {
    unsafe {
        return ffi_newHardwareVideoEncoderFactory()
    }
}

public func cj_newHardwareVideoDecoderFactory() : Int64 {
    unsafe {
        return ffi_newHardwareVideoDecoderFactory()
    }
}

public func cj_newPeerConnectionFactory(cjADM_int64 : Int64, cjHVEF_int64 : Int64 , cjHVDF_int64 : Int64) : Int64 {
    unsafe {
        return ffi_newPeerConnectionFactory(cjADM_int64, cjHVEF_int64, cjHVDF_int64)
    }
}

public func cj_createAudioSource(cjPCF_int64 : Int64, cjao : ffiAudioOptions) : Int64 {
    unsafe {
        return ffi_createAudioSource(cjPCF_int64, cjao)
    }
}

public func cj_createAudioTrack(cjPCF_int64 : Int64, cj_audioId : CString) : Int64 {
    unsafe {
        return ffi_createAudioTrack(cjPCF_int64, cj_audioId)
    }
}

public func cj_createVideoSource(cjPCF_int64 : Int64, cjCVSP : ffiCreateVideoSourceParameters) : Int64 {
    unsafe {
        return ffi_createVideoSource(cjPCF_int64, cjCVSP)
    }
}
 
public func cj_createVideoTrack(cjPCF_int64 : Int64, cj_videoId : CString) : Int64 {
    unsafe {
        return ffi_createVideoTrack(cjPCF_int64, cj_videoId)
    }
}

public func cj_StopAecDump(cjPCF_int64 : Int64) : Unit {
    unsafe {
        ffi_StopAecDump(cjPCF_int64)
    }
}

public func cj_SetSurfaceId(surfaceId : Int64) : Unit {
    unsafe {
        ffi_SetSurfaceId(surfaceId)
    }
}

public func cj_ChangeSurface(surfaceId : Int64, width : Float64, height : Float64) : Unit {
    unsafe {
        ffi_ChangeSurface(surfaceId, width, height)
    }
}

public func cj_DrawPattern(surfaceId : Int64) :Unit {
    unsafe {
        ffi_DrawPattern(surfaceId)
    }
}

public func cj_ChangeColor(surfaceId : Int64) : Unit {
    unsafe {
        ffi_ChangeColor(surfaceId)
    }
}

public func cj_DestroySurface(surfaceId : Int64) : Unit {
    unsafe {
        ffi_DestroySurface(surfaceId)
    }
}

public func cj_GetXComponentHasDraw(surfaceId : Int64) : Bool {
    unsafe {
        return ffi_GetXComponentHasDraw(surfaceId)
    }
}

public func cj_XComponentHasChangeColor(surfaceId : Int64) : Bool {
    unsafe {
        return ffi_XComponentHasChangeColor(surfaceId)
    }
}
