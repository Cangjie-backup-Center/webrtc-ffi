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
struct FFICreateVideoSourceParameters{
    public var width: Float64
    public var height: Float64
    public var facingMode: CString
    public var isScreencast: Bool
    public init(width: Float64, height: Float64, facingMode: CString, isScreencast: Bool) {
        this.width = width
        this.height = height
        this.facingMode = facingMode
        this.isScreencast = isScreencast
    }
}

sealed abstract class WebrtcClass {
    protected var ID: Int64 // ptr
    protected let randomid = WebRtcGlobal.getCurrentId()

    protected init() {
        this.ID = -1
    }

    protected init(id: Int64, that: WebrtcClass) {
        if (WebRtcGlobal.OBJECT_POOL.contains(id)) {
            throw Webrtc4cjFFIException("The Cangjie mapping object of C++objects does not allow the creation of secondary objects.")
        }
        this.ID = id
        WebRtcGlobal.map.add(this.randomid, that)
        WebRtcGlobal.OBJECT_POOL.add(id, that)
    }

    protected init(that: WebrtcClass) {
        this.ID = -1
    }

    public func getID(): Int64{
        return ID
    }

    public func isNone(): Bool {
        return this.ID == -1
    }

    protected func checkThis():Unit {
        if (isNone()) {
            throw NoneValueException("The C++class corresponding to class is empty")
        }
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

    public func createPeerConnection(config: RTCConfiguration): RTCPeerConnection {
        unsafe {
            RTCPeerConnection(ffiPeerConnectionFactory_ffiCreatePeerConnection(this.ID, config.cpp))
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

    public func stopAecDump() {
        unsafe {
            ffi_StopAecDump(this.getID())
        }
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

public class VideoTrack <: MediaStreamTrack {

    public init(pcf: PeerConnectionFactory, tag: String) {
        super( unsafe {ffi_createVideoTrack(pcf.ID,LibC.mallocCString(tag))}, this)
    }

    public init(ffiMST: CJ_MediaStreamTrack) {
        super(ffiMST)
    }

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
    public init(pcf: PeerConnectionFactory, ffiCVSP: CJ_TO_CPP_DisplayMediaStreamOptions, isScreen: Bool) {
        super(unsafe{ffi_createVideoSource(pcf.ID, ffiCVSP, isScreen)}, this)
    }

}

public open class MediaStreamTrack <: WebrtcClass {
    public var kind: String = ""
    public var id: String = ""
    public var enabled: Bool = false
    public var readyState: String = ""

    protected init() {}

    protected init(id: Int64, t:MediaStreamTrack) {
        super(id, t)
        this.kind = unsafe {ffiMediaStreamTrack_getKind(id).toString()}
        this.id = unsafe {ffiMediaStreamTrack_getId(id).toString()}
        this.readyState = unsafe {ffiMediaStreamTrack_getReadyState(id).toString()}
        this.enabled = unsafe {ffiMediaStreamTrack_getEnabled(id)}
    }

    protected init(ffiMST: CJ_MediaStreamTrack) {
        this.kind = ffiMST.kind.toString()
        this.ID = ffiMST.ptr_id
        this.enabled = ffiMST.enabled
        this.readyState = ffiMST.readyState.toString()
        this.id = ffiMST.id.toString()
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

    public init() {
        super(this)
    }

    public func getTracks(): Array<MediaStreamTrack> {
        checkThis()
        unsafe {
            let ret:CJ_ReturnArray = ffi_webrtc_FFIMediaStream_GetTracks(this.ID)
            let arr = Array<MediaStreamTrack>(ret.size, repeat: unsafe {zeroValue<MediaStreamTrack>()})
            for (i in 0..ret.size) {
                arr[i] = VideoTrack(ret.ptr.read(i))
            }
            return arr
        }
    }

    public func getAudioTracks(): Array<MediaStreamTrack> {
        checkThis()
        unsafe {
            let ret:CJ_ReturnArray = ffi_webrtc_FFIMediaStream_GetAudioTracks(this.ID)
            let arr = Array<MediaStreamTrack>(ret.size, repeat: unsafe {zeroValue<MediaStreamTrack>()})
            for (i in 0..ret.size) {
                arr[i] = VideoTrack(ret.ptr.read(i))
            }
            return arr
        }
    }

    public func getVideoTracks(): Array<MediaStreamTrack> {
        unsafe {
            let ret:CJ_ReturnArray = ffi_webrtc_FFIMediaStream_GetVideoTracks(this.ID)
            let arr = Array<MediaStreamTrack>(ret.size, repeat: unsafe {zeroValue<MediaStreamTrack>()})
            for (i in 0..ret.size) {
                arr[i] = VideoTrack(ret.ptr.read(i))
            }
            return arr
        }
    }
}


public class MediaDevices <: WebrtcClass {
    public init() {
        super(unsafe {ffi_webrtc_mediaDevices_create()}, this)
    }

    public func getDisplayMedia(video: CJ_TO_CPP_DisplayMediaStreamOptions,
                                audio: Bool,
                                systemAudio: Bool): MediaStream {
        var captureAudio: CJ_TO_CPP_DisplayMediaStreamOptions = CJ_TO_CPP_DisplayMediaStreamOptions(audio)
        var captureohosSystemAudio: CJ_TO_CPP_DisplayMediaStreamOptions = CJ_TO_CPP_DisplayMediaStreamOptions(systemAudio)

        unsafe {
             return MediaStream(ffi_webrtc_mediaDevices_getDisplayMedia(this.ID, video, captureAudio, captureohosSystemAudio))
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
    func ffi_createVideoSource(ffiPCF_int64: Int64, ffiCVSP: CJ_TO_CPP_DisplayMediaStreamOptions, isScreen: Bool): Int64
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
                                                        systemAudio:CJ_TO_CPP_DisplayMediaStreamOptions): Int64
    func ffi_webrtc_mediaDevices_getUserMedia(mediaDevicesPtr: Int64, video: CJ_TO_CPP_DisplayMediaStreamOptions,
                                                        audio:CJ_TO_CPP_DisplayMediaStreamOptions): Int64  // TODO
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

    func peerConnection_addTrack(cpp_ptr: Int64, ffiMST_ptr: Int64, streamVec: CJ_ArrayMediaStream): Int64
    func peerConnection_setLocalDescription(cpp_ptr: Int64, description: CJ_RTCSessionDescription, pe: CFunc<(Int64, CJ_ErrorMessage) -> Unit>): Unit
    func peerConnection_setRemoteDescription(cpp_ptr: Int64, description: CJ_RTCSessionDescription, pe: CFunc<(Int64, CJ_ErrorMessage) -> Unit>): Unit
    func peerConnection_createOffer(cpp_ptr: Int64, iceRestart: Bool): CJ_FFICreateSdpObserver_result
    func peerConnection_createAnswer(cpp_ptr: Int64): CJ_FFICreateSdpObserver_result
    func peerConnection_addIceCandidate(cpp_ptr: Int64, candidate: CJ_RTCIceCandidateInit): Unit
    func peerConnection_createDataChannel(cpp_ptr: Int64, label: CString, dataChannelDict: CJ_RTCDataChannelInit): Int64
    func peerConnection_getSenders(cpp_ptr: Int64): CPointer<Int64>
    func peerConnection_getTransceivers(cpp_ptr: Int64): CPointer<Int64>
    func peerConnection_restartIce(cpp_ptr: Int64): Unit
    func peerConnection_setConfiguration(cpp_ptr: Int64, configuration: CJ_RTCConfiguration): Unit
    func peerConnection_close(cpp_ptr: Int64): Unit
    func peerConnection_setAudioRecording(cpp_ptr: Int64, recording: Bool): Unit
    func peerConnection_setAudioPlayout(cpp_ptr: Int64, playout: Bool): Unit

    func ffiMediaStreamTrack_getKind(cpp_ptr: Int64): CString
    func ffiMediaStreamTrack_getEnabled(cpp_ptr: Int64): Bool
    func ffiMediaStreamTrack_getReadyState(cpp_ptr: Int64): CString
    func ffiMediaStreamTrack_getId(cpp_ptr: Int64): CString

    func deleteChar(ch: CString): Unit
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
