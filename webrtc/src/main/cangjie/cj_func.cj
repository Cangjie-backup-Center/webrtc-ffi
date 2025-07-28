/**
 * Created on 2025/7/15
 */
package webrtc

@C
struct ffiAudioOptions{
    var echo_cancellation : Bool = false
    var noise_suppression : Bool = false
}

@C
struct ffiCreateVideoSourceParameters{
    var width : Float64 = 0.00
    var height : Float64 = 0.00
    var facingMode : CString = unsafe{LibC.mallocCString("")}
    var isScreencast : Bool = false;
}

foreign {
    func ffi_newNativeVideoRenderer(surfaceId : Int64) : Int64
    func ffi_setVideoTrack(ffiNVR : Int64, surfaceId : Int64) : Unit
    func ffi_setMirror(ffiNVR : Int64, mirrorBool : Bool) : Unit
    func ffi_setMirrorVertically(ffiNVR : Int64, mirrorVerticallyBool : Bool) : Unit
    func ffi_setScalingMode(ffiNVR : Int64 , scalingMode : Int64) : Unit
    func ffi_release(ffiNVR : Int64) : Unit
    
    func ffi_newAudioDeviceModule(useStereoInput : Bool, useStereoOutput : Bool) : Unit
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

func cj_newNativeVideoRenderer(surfaceId : Int64) : Int64 {
    unsafe {
        return ffi_newNativeVideoRenderer(surfaceId)
    }
}

func cj_setVideoTrack(ffiNVR : Int64, surfaceId : Int64) : Unit {
    unsafe {
        ffi_setVideoTrack(ffiNVR , surfaceId)
    }
}

func cj_setMirror(cjNVR : Int64, mirrorBool : Bool) : Unit {
    unsafe {
        ffi_setMirror(cjNVR , mirrorBool)
    }
}

func cj_setMirrorVertically(cjNVR : Int64, mirrorVerticallyBool : Bool) : Unit {
    unsafe {
        ffi_setMirrorVertically(cjNVR , mirrorVerticallyBool)
    }
}

func cj_setScalingMode(cjNVR : Int64, scalingMode : Int64) : Unit {
    unsafe {
        ffi_setScalingMode(cjNVR , scalingMode)
    }
}

func cj_release(cjNVR : Int64) : Unit {
    unsafe {
        ffi_release(cjNVR)
    }
}

func cj_newAudioDeviceModule(useStereoInput : Bool, useStereoOutput : Bool) : Unit{
    unsafe {
        ffi_newAudioDeviceModule(useStereoInput , useStereoOutput)
    }
}

func cj_newHardwareVideoEncoderFactory() : Int64 {
    unsafe {
        return ffi_newHardwareVideoEncoderFactory()
    }
}

func cj_newHardwareVideoDecoderFactory() : Int64 {
    unsafe {
        return ffi_newHardwareVideoDecoderFactory()
    }
}

func cj_newPeerConnectionFactory(cjADM_int64 : Int64, cjHVEF_int64 : Int64 , cjHVDF_int64 : Int64) : Int64 {
    unsafe {
        return ffi_newPeerConnectionFactory(cjADM_int64, cjHVEF_int64, cjHVDF_int64)
    }
}

func cj_createAudioSource(cjPCF_int64 : Int64, cjao : ffiAudioOptions) : Int64 {
    unsafe {
        return ffi_createAudioSource(cjPCF_int64, cjao)
    }
}

func cj_createAudioTrack(cjPCF_int64 : Int64, cj_audioId : CString) : Int64 {
    unsafe {
        return ffi_createAudioTrack(cjPCF_int64, cj_audioId)
    }
}

func cj_createVideoSource(cjPCF_int64 : Int64, cjCVSP : ffiCreateVideoSourceParameters) : Int64 {
    unsafe {
        return ffi_createVideoSource(cjPCF_int64, cjCVSP)
    }
}
 
func cj_createVideoTrack(cjPCF_int64 : Int64, cj_videoId : CString) : Int64 {
    unsafe {
        return ffi_createVideoTrack(cjPCF_int64, cj_videoId)
    }
}

func cj_StopAecDump(cjPCF_int64 : Int64) : Unit {
    unsafe {
        ffi_StopAecDump(cjPCF_int64)
    }
}

func cj_SetSurfaceId(surfaceId : Int64) : Unit {
    unsafe {
        ffi_SetSurfaceId(surfaceId)
    }
}

func cj_ChangeSurface(surfaceId : Int64, width : Float64, height : Float64) : Unit {
    unsafe {
        ffi_ChangeSurface(surfaceId, width, height)
    }
}

func cj_DrawPattern(surfaceId : Int64) :Unit {
    unsafe {
        ffi_DrawPattern(surfaceId)
    }
}

func cj_ChangeColor(surfaceId : Int64) : Unit {
    unsafe {
        ffi_ChangeColor(surfaceId)
    }
}

func cj_DestroySurface(surfaceId : Int64) : Unit {
    unsafe {
        ffi_DestroySurface(surfaceId)
    }
}

func cj_GetXComponentHasDraw(surfaceId : Int64) : Bool {
    unsafe {
        return ffi_GetXComponentHasDraw(surfaceId)
    }
}

func cj_XComponentHasChangeColor(surfaceId : Int64) : Bool {
    unsafe {
        return ffi_XComponentHasChangeColor(surfaceId)
    }
}
