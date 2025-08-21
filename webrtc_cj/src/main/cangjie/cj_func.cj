/*
 * @Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package webrtc_cj

import std.collection.concurrent.ConcurrentHashMap
import std.sync.*
import std.ast.Expr

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
    protected var ID: Int64 // ptr
    protected let randomid = WebRtcGlobal.getCurrentId()
    protected init(id: Int64, that: WebrtcClass) {
        if (WebRtcGlobal.OBJECT_POOL.contains(id)) {
            throw Webrtc4cjFFIException("The Cangjie mapping object of C++objects does not allow the creation of secondary objects.")
        }
        this.ID = id
        WebRtcGlobal.map.add(this.randomid, that)
        WebRtcGlobal.OBJECT_POOL.add(id, that)
    }

//   TODO 释放资源
//    ~init() {
//
//    }

    public func getID(): Int64{
        return ID
    }
}

public class AudioDeviceModule <: WebrtcClass {

    public init(useStereoInput: Bool, useStereoOutput: Bool) {
        super(unsafe {ffi_newAudioDeviceModule(useStereoInput, useStereoOutput)}, this)
    }

}

public class PeerConnectionFactory <: WebrtcClass {
    public init(adm: AudioDeviceModule) {
        super(unsafe {ffi_newPeerConnectionFactory(adm.ID, ffi_newHardwareVideoEncoderFactory() , ffi_newHardwareVideoDecoderFactory())}, this)
    }
//    public func createPeerConnectionFactoryID(adm: AudioDeviceModule) {
//        this.ID = cj_newPeerConnectionFactory(adm.ID, cj_newHardwareVideoEncoderFactory() , cj_newHardwareVideoDecoderFactory())
//    }

    public func createPeerConnection(config: CJ_RTCConfiguration): RTCPeerConnection {
        unsafe {
            RTCPeerConnection(ffiPeerConnectionFactory_ffiCreatePeerConnection(this.ID, config))
        }
    }

    public func SetDefault(){
        unsafe {
            ffi_SetDefault(this.ID)
        }
    }

    public func startAecDump(fd: Int32, max_size_bytes: Int32): Bool {
        return unsafe {ffi_StartAecDump(this.getID(), fd, max_size_bytes)}
    }
}

public class AudioSource <: WebrtcClass {
    public init(pcf: PeerConnectionFactory, options: FFIAudioOptions) {
        super(unsafe {ffi_createAudioSource(pcf.ID, options)}, this)
    }
//    public func createAudioSourceID(pcf: PeerConnectionFactory, options: FFIAudioOptions) {
//        this.ID = cj_createAudioSource(pcf.ID, options)
//    }
}

public class MediaTrack <: MediaStreamTrack {
    public init(id: Int64) {
        super(id, this)
    }
}

public class AudioTrack <: MediaStreamTrack {
    public init(pcf: PeerConnectionFactory, tag: String) {
        super(unsafe {ffi_createAudioTrack(pcf.ID, LibC.mallocCString(tag))}, this)
    }

}

public class VideoSource <: WebrtcClass {

    public init(pcf: PeerConnectionFactory, ffiCVSP: FFICreateVideoSourceParameters) {
        super(unsafe{ffi_createVideoSource(pcf.ID, ffiCVSP)}, this)
    }

//    public func createVideoSourceID(pcf: PeerConnectionFactory, ffiCVSP: FFICreateVideoSourceParameters) {
//        this.ID = cj_createVideoSource(pcf.ID, ffiCVSP)
//    }
}

public class VideoTrack <: WebrtcClass {

    public init(pcf: PeerConnectionFactory, tag: String) {
        super( unsafe {ffi_createVideoTrack(pcf.ID,LibC.mallocCString(tag))}, this)
    }

//    public func createVideoTrackID(pcf: PeerConnectionFactory, tag: CString) {
//        this.ID = cj_createVideoTrack(pcf.ID, tag)
//    }
}

public open class MediaStreamTrack <: WebrtcClass {
    protected  init(id: Int64, t:MediaStreamTrack) {
        super(id, t)
    }
}

public class RtpReceiver <: WebrtcClass {
    public init(id: Int64) {
        super(id, this)
    }
}

public class RtpTransceiver <: WebrtcClass {
    public init(id: Int64) {
        super(id, this)
    }
}

public class MediaStream <: WebrtcClass {
    public init(id: Int64) {
        super(id, this)
    }

    public func getTracks(): Array<MediaStreamTrack> {
        unsafe {
            let ret:CJ_ReturnArray = ffi_webrtc_FFIMediaStream_GetTracks(this.ID)
            let arr = Array<MediaStreamTrack>(ret.size, repeat: unsafe {zeroValue<MediaStreamTrack>()})
            for (i in 0..ret.size) {
                arr[i] = MediaTrack(ret.ptr.read(i))
            }
            return arr
        }
    }

    public func getAudioTracks(): Array<MediaStreamTrack> {
        unsafe {
            let ret:CJ_ReturnArray = ffi_webrtc_FFIMediaStream_GetAudioTracks(this.ID)
            let arr = Array<MediaStreamTrack>(ret.size, repeat: unsafe {zeroValue<MediaStreamTrack>()})
            for (i in 0..ret.size) {
                arr[i] = MediaTrack(ret.ptr.read(i))
            }
            return arr
        }
    }

    public func getVideoTracks(): Array<MediaStreamTrack> {
        unsafe {
            let ret:CJ_ReturnArray = ffi_webrtc_FFIMediaStream_GetVideoTracks(this.ID)
            let arr = Array<MediaStreamTrack>(ret.size, repeat: unsafe {zeroValue<MediaStreamTrack>()})
            for (i in 0..ret.size) {
                arr[i] = MediaTrack(ret.ptr.read(i))
            }
            return arr
        }
    }
}


public class MediaDevices <: WebrtcClass {
    var call: Option<(mediaStream: MediaStream) -> Unit> = None
    public init() {
        super(unsafe {ffi_webrtc_mediaDevices_create()}, this)
    }

    public func getDisplayMedia(video: CJ_TO_CPP_DisplayMediaStreamOptions,
                                audio:CJ_TO_CPP_DisplayMediaStreamOptions,
                                systemAudio:CJ_TO_CPP_DisplayMediaStreamOptions, callback: (mediaStream: MediaStream) -> Unit): Unit {
        this.call = callback
        let f : CFunc<(that: Int64, localVideoTrack: Int64) -> Unit> = {id: Int64, localVideoTrack: Int64 =>
            let that: MediaDevices = ((WebRtcGlobal.map.get(id) ?? return) as MediaDevices) ?? return
            let track = MediaStream(localVideoTrack)
            if (let Some(v) <- that.call) {
                v(track)
            }
        }
        unsafe {
            ffi_webrtc_mediaDevices_getDisplayMedia(this.ID, video, audio,systemAudio, this.randomid, f)
        }
    }
}

foreign {
    func ffiPeerConnectionFactory_ffiCreatePeerConnection(cpp_ptr: Int64, config: CJ_RTCConfiguration): Int64
    func ffi_newNativeVideoRenderer(surfaceId: Int64): Int64
    func ffi_setVideoTrack(ffiNVR: Int64, surfaceId: Int64): Unit
    func ffi_setMirror(ffiNVR: Int64, mirrorBool: Bool): Unit
    func ffi_setMirrorVertically(ffiNVR: Int64, mirrorVerticallyBool: Bool): Unit
    func ffi_setScalingMode(ffiNVR: Int64 , scalingMode: Int32): Unit
    func ffi_release(ffiNVR: Int64): Unit

    func ffi_newAudioDeviceModule(useStereoInput: Bool, useStereoOutput: Bool): Int64
    func ffi_newHardwareVideoEncoderFactory(): Int64
    func ffi_newHardwareVideoDecoderFactory(): Int64
    func ffi_newPeerConnectionFactory(ffiADM_int64: Int64, ffiHVEF_int64: Int64 , ffiHVDF_int64: Int64): Int64
    func ffi_createAudioSource(ffiPCF_int64: Int64, ffiao: FFIAudioOptions): Int64
    func ffi_createAudioTrack(ffiPCF_int64: Int64, ffi_audioId: CString): Int64
    func ffi_createVideoSource(ffiPCF_int64: Int64, ffiCVSP: FFICreateVideoSourceParameters): Int64
    func ffi_createVideoTrack(ffiPCF_int64: Int64, ffi_videoId: CString): Int64
    func ffi_SetDefault(ffiPCF_int64: Int64): Unit
    func ffi_StartAecDump(ffiPCF_int64: Int64, fd: Int32, max_size_bytes: Int32): Bool
    func ffi_StopAecDump(ffiPCF_int64: Int64): Unit

    func ffi_SetSurfaceId(surfaceId: Int64): Unit
    func ffi_ChangeSurface(surfaceId: Int64, width: Float64, height: Float64): Unit
    func ffi_DrawPattern(surfaceId: Int64):Unit
    func ffi_ChangeColor(surfaceId: Int64): Unit
    func ffi_DestroySurface(surfaceId: Int64): Unit
    func ffi_GetXComponentHasDraw(surfaceId: Int64): Bool;
    func ffi_XComponentHasChangeColor(surfaceId: Int64): Bool;

    // webrtc::MediaDevices
    func ffi_webrtc_mediaDevices_create(): Int64
    func ffi_webrtc_mediaDevices_getDisplayMedia(mediaDevicesPtr: Int64, video: CJ_TO_CPP_DisplayMediaStreamOptions,
                                                        audio:CJ_TO_CPP_DisplayMediaStreamOptions,
                                                        systemAudio:CJ_TO_CPP_DisplayMediaStreamOptions,
                                                        id: Int64, pe: CFunc<(that: Int64, localVideoTrack: Int64) -> Unit>): Int64
    func ffi_webrtc_mediaDevices_getUserMedia(mediaDevicesPtr: Int64, video: CJ_TO_CPP_DisplayMediaStreamOptions,
                                                        audio:CJ_TO_CPP_DisplayMediaStreamOptions,
                                                        id: Int64, pe: CFunc<(that: Int64, localVideoTrack: Int64) -> Unit>): Int64
    func ffi_webrtc_mediaDevices_enumerateDevices(mediaDevicesPtr: Int64): CJ_ReturnEnumerateDevicesInfo
    func ffi_webrtc_mediaDevices_getSupportedConstraints(mediaDevicesPtr: Int64): Int64
    // webrtc::FFIMediaStream
    func ffi_webrtc_FFIMediaStream_AddTrack(FFIMediaStreamPtr: Int64,mst: Int64): Unit
    func ffi_webrtc_FFIMediaStream_RemoveTrack(FFIMediaStreamPtr: Int64,mst: Int64): Unit
    func ffi_webrtc_FFIMediaStream_GetTrackById(FFIMediaStreamPtr: Int64,trackId: CString): Int64
    func ffi_webrtc_FFIMediaStream_GetTracks(FFIMediaStreamPtr: Int64): CJ_ReturnArray
    func ffi_webrtc_FFIMediaStream_GetAudioTracks(FFIMediaStreamPtr: Int64): CJ_ReturnArray
    func ffi_webrtc_FFIMediaStream_GetVideoTracks(FFIMediaStreamPtr: Int64): CJ_ReturnArray
    // webrtc::ffiMediaStreamTrack
    func ffi_webrtc_ffiMediaStreamTrack_ToJson(ffiMediaStreamTrackPtr: Int64): CJ_ffiMediaStreamTrackJson
    func ffi_webrtc_ffiMediaStreamTrack_GetSource(ffiMediaStreamTrackPtr: Int64): Int64
}
//
//public func cj_newNativeVideoRenderer(surfaceId: Int64): Int64 {
//    unsafe {
//        return ffi_newNativeVideoRenderer(surfaceId)
//    }
//}
//
//public func cj_setVideoTrack(nvrID: Int64, mstID: Int64): Unit {
//    unsafe {
//        ffi_setVideoTrack(nvrID , mstID)
//    }
//}
//
//public func cj_setMirror(nvrID: Int64, mirrorBool: Bool): Unit {
//    unsafe {
//        ffi_setMirror(nvrID , mirrorBool)
//    }
//}
//
//public func cj_setMirrorVertically(nvrID: Int64, mirrorVerticallyBool: Bool): Unit {
//    unsafe {
//        ffi_setMirrorVertically(nvrID , mirrorVerticallyBool)
//    }
//}
//
//public func cj_setScalingMode(nvrID: Int64, scalingMode: Int32): Unit {
//    unsafe {
//        ffi_setScalingMode(nvrID , scalingMode)
//    }
//}
//
//public func cj_release(nvrID: Int64): Unit {
//    unsafe {
//        ffi_release(nvrID)
//    }
//}
//
//public func cj_newAudioDeviceModule(useStereoInput: Bool, useStereoOutput: Bool): Int64{
//    unsafe {
//        return ffi_newAudioDeviceModule(useStereoInput, useStereoOutput)
//    }
//}
//
//public func cj_newHardwareVideoEncoderFactory(): Int64 {
//    unsafe {
//        return ffi_newHardwareVideoEncoderFactory()
//    }
//}
//
//public func cj_newHardwareVideoDecoderFactory(): Int64 {
//    unsafe {
//        return ffi_newHardwareVideoDecoderFactory()
//    }
//}
//
//public func cj_newPeerConnectionFactory(admID: Int64, hvefID: Int64 , hvdfID: Int64): Int64 {
//    unsafe {
//        return ffi_newPeerConnectionFactory(admID, hvefID, hvdfID)
//    }
//}
//
//private func cj_createAudioSource(pcfID: Int64, cjao: FFIAudioOptions): Int64 {
//    unsafe {
//        return ffi_createAudioSource(pcfID, cjao)
//    }
//}
//
//private func cj_createAudioTrack(pcfID: Int64, tag: CString): Int64 {
//    unsafe {
//        return ffi_createAudioTrack(pcfID, tag)
//    }
//}
//
//private func cj_createVideoSource(pcfID: Int64, cjCVSP: FFICreateVideoSourceParameters): Int64 {
//    unsafe {
//        return ffi_createVideoSource(pcfID, cjCVSP)
//    }
//}
//
//private func cj_createVideoTrack(pcfID: Int64, tag: CString): Int64 {
//    unsafe {
//        return ffi_createVideoTrack(pcfID, tag)
//    }
//}
//
//public func cj_SetDefault(pcfID: Int64) {
//    unsafe {
//        ffi_SetDefault(pcfID)
//    }
//}
//
//private func cj_StartAecDump(pcfID: Int64, fd: Int32, max_size_bytes: Int32): Bool {
//    unsafe {
//        return ffi_StartAecDump(pcfID, fd, max_size_bytes)
//    }
//}
//
//public func cj_StopAecDump(pcfID: Int64): Unit {
//    unsafe {
//        ffi_StopAecDump(pcfID)
//    }
//}
//
//public func cj_SetSurfaceId(surfaceId: Int64): Unit {
//    unsafe {
//        ffi_SetSurfaceId(surfaceId)
//    }
//}
//
//public func cj_ChangeSurface(surfaceId: Int64, width: Float64, height: Float64): Unit {
//    unsafe {
//        ffi_ChangeSurface(surfaceId, width, height)
//    }
//}
//
//public func cj_DrawPattern(surfaceId: Int64):Unit {
//    unsafe {
//        ffi_DrawPattern(surfaceId)
//    }
//}
//
//public func cj_ChangeColor(surfaceId: Int64): Unit {
//    unsafe {
//        ffi_ChangeColor(surfaceId)
//    }
//}
//
//public func cj_DestroySurface(surfaceId: Int64): Unit {
//    unsafe {
//        ffi_DestroySurface(surfaceId)
//    }
//}
//
//public func cj_GetXComponentHasDraw(surfaceId: Int64): Bool {
//    unsafe {
//        return ffi_GetXComponentHasDraw(surfaceId)
//    }
//}
//
//public func cj_XComponentHasChangeColor(surfaceId: Int64): Bool {
//    unsafe {
//        return ffi_XComponentHasChangeColor(surfaceId)
//    }
//}
