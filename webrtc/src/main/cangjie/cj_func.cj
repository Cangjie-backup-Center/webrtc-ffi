/*
 * @Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package webrtc

@C
public struct FFIAudioOptions{
    public var echo_cancellation: Bool = false
    public var noise_suppression: Bool = false
}

@C
public struct FFICreateVideoSourceParameters{
    public var width: Float64 = 0.00
    public var height: Float64 = 0.00
    public var facingMode: CString = unsafe{LibC.mallocCString("")}
    public var isScreencast: Bool = false;
}

sealed abstract class WebrtcClass {
    protected var ID: Int64 = 0 // ptr

    public init() {
        this.ID = 0
    }

    public func getID(): Int64{
        return ID
    }

    public func createID(id: Int64) {
        this.ID = id
    }
}

public class AudioDeviceModule <: WebrtcClass {
    public func createAudioDeviceModuleID(useStereoInput: Bool, useStereoOutput: Bool) {
        this.ID = cj_newAudioDeviceModule(useStereoInput, useStereoOutput)
    }
}

public class PeerConnectionFactory <: WebrtcClass {
    public func createPeerConnectionFactoryID(adm: AudioDeviceModule) {
        this.ID = cj_newPeerConnectionFactory(adm.ID, cj_newHardwareVideoEncoderFactory() , cj_newHardwareVideoDecoderFactory())
    }
}

public class AudioSource <: WebrtcClass {
    public func createAudioSourceID(pcf: PeerConnectionFactory, options: FFIAudioOptions) {
        this.ID = cj_createAudioSource(pcf.ID, options)
    }
}

public class AudioTrack <: WebrtcClass {
    public func createAudioTrackID(pcf: PeerConnectionFactory, tag: CString) {
        this.ID = cj_createAudioTrack(pcf.ID, tag)
    }
}

public class VideoSource <: WebrtcClass {
    public func createVideoSourceID(pcf: PeerConnectionFactory, ffiCVSP: FFICreateVideoSourceParameters) {
        this.ID = cj_createVideoSource(pcf.ID, ffiCVSP)
    }
}

public class VideoTrack <: WebrtcClass {
    public func createVideoTrackID(pcf: PeerConnectionFactory, tag: CString) {
        this.ID = cj_createVideoTrack(pcf.ID, tag)
    }
}

foreign {
    func ffi_newNativeVideoRenderer(surfaceId: Int64): Int64
    func ffi_setVideoTrack(nvrID: Int64, surfaceId: Int64): Unit
    func ffi_setMirror(nvrID: Int64, mirrorBool: Bool): Unit
    func ffi_setMirrorVertically(nvrID: Int64, mirrorVerticallyBool: Bool): Unit
    func ffi_setScalingMode(nvrID: Int64 , scalingMode: Int32): Unit
    func ffi_release(nvrID: Int64): Unit
    
    func ffi_newAudioDeviceModule(useStereoInput: Bool, useStereoOutput: Bool): Int64
    func ffi_newHardwareVideoEncoderFactory(): Int64
    func ffi_newHardwareVideoDecoderFactory(): Int64
    func ffi_newPeerConnectionFactory(admID: Int64, hvefID: Int64, hvdfID: Int64): Int64
    func ffi_createAudioSource(pcfID: Int64, ffiao: FFIAudioOptions): Int64
    func ffi_createAudioTrack(pcfID: Int64, tag: CString): Int64
    func ffi_createVideoSource(pcfID: Int64, ffiCVSP: FFICreateVideoSourceParameters): Int64
    func ffi_createVideoTrack(pcfID: Int64, tag: CString): Int64
    func ffi_StopAecDump(pcfID: Int64): Unit

    func ffi_SetSurfaceId(surfaceId: Int64): Unit
    func ffi_ChangeSurface(surfaceId: Int64, width: Float64, height: Float64): Unit
    func ffi_DrawPattern(surfaceId: Int64):Unit
    func ffi_ChangeColor(surfaceId: Int64): Unit
    func ffi_DestroySurface(surfaceId: Int64): Unit 
    func ffi_GetXComponentHasDraw(surfaceId: Int64): Bool;
    func ffi_XComponentHasChangeColor(surfaceId: Int64): Bool;    
}

public func cj_newNativeVideoRenderer(surfaceId: Int64): Int64 {
    unsafe {
        return ffi_newNativeVideoRenderer(surfaceId)
    }
}

public func cj_setVideoTrack(nvrID: Int64, mstID: Int64): Unit {
    unsafe {
        ffi_setVideoTrack(nvrID , mstID)
    }
}

public func cj_setMirror(nvrID: Int64, mirrorBool: Bool): Unit {
    unsafe {
        ffi_setMirror(nvrID , mirrorBool)
    }
}

public func cj_setMirrorVertically(nvrID: Int64, mirrorVerticallyBool: Bool): Unit {
    unsafe {
        ffi_setMirrorVertically(nvrID , mirrorVerticallyBool)
    }
}

public func cj_setScalingMode(nvrID: Int64, scalingMode: Int32): Unit {
    unsafe {
        ffi_setScalingMode(nvrID , scalingMode)
    }
}

public func cj_release(nvrID: Int64): Unit {
    unsafe {
        ffi_release(nvrID)
    }
}

public func cj_newAudioDeviceModule(useStereoInput: Bool, useStereoOutput: Bool): Int64{
    unsafe {
        return ffi_newAudioDeviceModule(useStereoInput, useStereoOutput)
    }
}

public func cj_newHardwareVideoEncoderFactory(): Int64 {
    unsafe {
        return ffi_newHardwareVideoEncoderFactory()
    }
}

public func cj_newHardwareVideoDecoderFactory(): Int64 {
    unsafe {
        return ffi_newHardwareVideoDecoderFactory()
    }
}

public func cj_newPeerConnectionFactory(admID: Int64, hvefID: Int64 , hvdfID: Int64): Int64 {
    unsafe {
        return ffi_newPeerConnectionFactory(admID, hvefID, hvdfID)
    }
}

private func cj_createAudioSource(pcfID: Int64, cjao: FFIAudioOptions): Int64 {
    unsafe {
        return ffi_createAudioSource(pcfID, cjao)
    }
}

private func cj_createAudioTrack(pcfID: Int64, tag: CString): Int64 {
    unsafe {
        return ffi_createAudioTrack(pcfID, tag)
    }
}

private func cj_createVideoSource(pcfID: Int64, cjCVSP: FFICreateVideoSourceParameters): Int64 {
    unsafe {
        return ffi_createVideoSource(pcfID, cjCVSP)
    }
}
 
private func cj_createVideoTrack(pcfID: Int64, tag: CString): Int64 {
    unsafe {
        return ffi_createVideoTrack(pcfID, tag)
    }
}

public func cj_StopAecDump(pcfID: Int64): Unit {
    unsafe {
        ffi_StopAecDump(pcfID)
    }
}

public func cj_SetSurfaceId(surfaceId: Int64): Unit {
    unsafe {
        ffi_SetSurfaceId(surfaceId)
    }
}

public func cj_ChangeSurface(surfaceId: Int64, width: Float64, height: Float64): Unit {
    unsafe {
        ffi_ChangeSurface(surfaceId, width, height)
    }
}

public func cj_DrawPattern(surfaceId: Int64):Unit {
    unsafe {
        ffi_DrawPattern(surfaceId)
    }
}

public func cj_ChangeColor(surfaceId: Int64): Unit {
    unsafe {
        ffi_ChangeColor(surfaceId)
    }
}

public func cj_DestroySurface(surfaceId: Int64): Unit {
    unsafe {
        ffi_DestroySurface(surfaceId)
    }
}

public func cj_GetXComponentHasDraw(surfaceId: Int64): Bool {
    unsafe {
        return ffi_GetXComponentHasDraw(surfaceId)
    }
}

public func cj_XComponentHasChangeColor(surfaceId: Int64): Bool {
    unsafe {
        return ffi_XComponentHasChangeColor(surfaceId)
    }
}
