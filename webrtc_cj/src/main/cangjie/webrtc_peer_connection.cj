/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */
package webrtc_cj

foreign func peerConnection_set_class_key(cpp_ptr: Int64, id: Int64): Unit
foreign func peerConnection_SetOnDataChannel_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: Int64) -> Unit>): Unit
foreign func peerConnection_SetOnSignalingChange_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_Event) -> Unit>): Unit
foreign func peerConnection_SetOnIceCandidateError_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_RTCPeerConnectionIceErrorEvent) -> Unit>): Unit
foreign func peerConnection_SetonTrack_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_RTCTrackEvent) -> Unit>): Unit
foreign func peerConnection_SetOnConnectionChange_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_Event) -> Unit>): Unit
foreign func peerConnection_SetOnRenegotiationNeeded_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_Event) -> Unit>): Unit
foreign func peerConnection_SetOnStandardizedIceConnectionChange_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_Event) -> Unit>): Unit
foreign func peerConnection_SetOnIceGatheringChange_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_Event) -> Unit>): Unit
foreign func peerConnection_SetOnIceCandidate_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_RTCPeerConnectionIceEvent) -> Unit>): Unit

foreign func peerConnection_GetCanTrickleIceCandidates(cpp_ptr: Int64): Bool
foreign func peerConnection_GetSignalingState(cpp_ptr: Int64): Int64
foreign func peerConnection_GetIceGatheringState(cpp_ptr: Int64): Int64
foreign func peerConnection_GetIceConnectionState(cpp_ptr: Int64): Int64
foreign func peerConnection_GetConnectionState(cpp_ptr: Int64): Int64
foreign func peerConnection_GetLocalDescription(cpp_ptr: Int64): CJ_RTCSessionDescription
foreign func peerConnection_GetRemoteDescription(cpp_ptr: Int64): CJ_RTCSessionDescription
foreign func peerConnection_GetCurrentLocalDescription(cpp_ptr: Int64): CJ_RTCSessionDescription
foreign func peerConnection_GetCurrentRemoteDescription(cpp_ptr: Int64): CJ_RTCSessionDescription
foreign func peerConnection_GetPendingLocalDescription(cpp_ptr: Int64): CJ_RTCSessionDescription
foreign func peerConnection_GetPendingRemoteDescription(cpp_ptr: Int64): CJ_RTCSessionDescription
foreign func peerConnection_GetSctp(cpp_ptr: Int64): Int64
foreign func peerConnection_static_GenerateCertificate(cpp_ptr: CString): Int64
foreign func peerConnection_CPP_FREE(cpp_ptr: Int64): Unit  // TODO


public class RTCPeerConnection <: WebrtcClass {

    var ondatachannel_: ?((pc: RTCPeerConnection, dc: RTCDataChannel) -> Unit) = None
    var onSignalingChange_: ?((pc: RTCPeerConnection, dc: Event) -> Unit) = None
    var onIceCandidateError_: ?((pc: RTCPeerConnection, dc: RTCPeerConnectionIceErrorEvent) -> Unit) = None
    var onTrack_: ?((pc: RTCPeerConnection, dc: RTCTrackEvent) -> Unit) = None
    var onConnectionChange_: ?((pc: RTCPeerConnection, dc: Event) -> Unit) = None
    var onRenegotiationNeeded_: ?((pc: RTCPeerConnection, dc: Event) -> Unit) = None
    var onStandardizedIceConnectionChange_: ?((pc: RTCPeerConnection, dc: Event) -> Unit) = None
    var onIceGatheringChange_: ?((pc: RTCPeerConnection, dc: Event) -> Unit) = None
    var onIceCandidate_: ?((pc: RTCPeerConnection, dc: RTCPeerConnectionIceEvent) -> Unit) = None
    var setLocalDescription_callback_: ((ErrorMessage) -> Unit) = {_=>}
    var setRemoteDescription_callback_: ((ErrorMessage) -> Unit) = {_=>}

    let queue = ExecutorService.new()

    public mut prop ondatachannel: ((pc: RTCPeerConnection, dc: RTCDataChannel) -> Unit) {
        get() {ondatachannel_ ?? {_,_=>}}
        set(v) {
            if (this.ondatachannel_.isNone()) {
                unsafe {
                    peerConnection_SetOnDataChannel_(this.ID, { id: Int64, ptr: Int64 =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        ffipc.queue.execute({ =>
//                            if (ffipc.connectionState != FFIRTCPeerConnectionState.CLOSED) {
                                ffipc.ondatachannel(ffipc, RTCDataChannel(ptr, ffipc))
//                            }
                        })
                    })
                }
            }
            ondatachannel_ = v
        }
    }
    public mut prop onSignalingChange: ((pc: RTCPeerConnection, dc: Event) -> Unit) {
        get() {onSignalingChange_?? {_,_=>}}
        set(v) {
            if (this.onSignalingChange_.isNone()) {
                unsafe {
                    peerConnection_SetOnSignalingChange_(this.ID, { id: Int64, ptr: CJ_Event =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        let event = Event(ptr.eventType.toString())
                        ffipc.queue.execute({ =>
                            ffipc.onSignalingChange(ffipc, event)
                        })
                    })
                }
            }
            onSignalingChange_ = v
        }
    }
    public mut prop onIceCandidateError: ((pc: RTCPeerConnection, dc: RTCPeerConnectionIceErrorEvent) -> Unit) {
        get() {onIceCandidateError_?? {_,_=>}}
        set(v) {
            if (onIceCandidateError_.isNone()){
                unsafe {
                    peerConnection_SetOnIceCandidateError_(this.ID, { id: Int64, ptr: CJ_RTCPeerConnectionIceErrorEvent =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        let event = RTCPeerConnectionIceErrorEvent(
                                ptr.TYPE.toString(),
                                ptr.address.toString(),
                                ptr.port,
                                ptr.url.toString(),
                                ptr.errorCode,
                                ptr.errorText.toString()
                            )
                        ffipc.queue.execute({ =>
                            ffipc.onIceCandidateError(ffipc, event)
                        })
                    })
                }
            }
            onIceCandidateError_ = v
        }
    }

    public mut prop onTrack: ((pc: RTCPeerConnection, dc: RTCTrackEvent) -> Unit) {
        get() {onTrack_?? {_,_=>}}
        set(v) {
            if (onTrack_.isNone()) {
                unsafe {
                    peerConnection_SetonTrack_(this.ID, { id: Int64, ptr: CJ_RTCTrackEvent =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        let arr = Array<Int64> (ptr.streams_size, repeat: 0)
                        for(i in 0..ptr.streams_size) {
                            arr[i] = ptr.streams.read(i)
                        }
                        let event = RTCTrackEvent(
                                ptr.TYPE.toString(),
                                arr,
                                ptr.MediaStreamTrack_ptr,
                                ptr.RtpReceiver_ptr,
                                ptr.RtpTransceiver_ptr
                            )
                        ffipc.queue.execute({ =>
                            ffipc.onTrack(
                                ffipc,event
                            )
                        })
                    })
                }
            }
            onTrack_ = v
        }
    }
    public mut prop onconnectionstatechange: ((pc: RTCPeerConnection, dc: Event) -> Unit){
        get () {onConnectionChange_??{_,_=>}}
        set (v) {
            if (onConnectionChange_.isNone()) {
                unsafe {
                    peerConnection_SetOnConnectionChange_(this.ID, { id: Int64, ptr: CJ_Event =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        let event = Event(ptr.eventType.toString())
                        ffipc.queue.execute({ =>
                            ffipc.onconnectionstatechange( ffipc, event)
                        })
                    })
                }
            }
            onConnectionChange_ = v
        }
    }
    public mut prop onnegotiationneeded: ((pc: RTCPeerConnection, dc: Event) -> Unit){
        get () {onRenegotiationNeeded_??{_,_=>}}
        set (v) {
            if (onRenegotiationNeeded_.isNone()) {
                unsafe {
                    peerConnection_SetOnRenegotiationNeeded_(this.ID, { id: Int64, ptr: CJ_Event =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        let event = Event(ptr.eventType.toString())
                        ffipc.queue.execute({ =>
                            ffipc.onnegotiationneeded( ffipc, event)
                        })
                    })
                }
            }
            onRenegotiationNeeded_ = v
        }
    }
    public mut prop oniceconnectionstatechange: ((pc: RTCPeerConnection, dc: Event) -> Unit){
        get () {onStandardizedIceConnectionChange_??{_,_=>}}
        set (v) {
            if (onStandardizedIceConnectionChange_.isNone()) {
                unsafe {
                    peerConnection_SetOnStandardizedIceConnectionChange_(this.ID, { id: Int64, ptr: CJ_Event =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        let event = Event(ptr.eventType.toString())
                        ffipc.queue.execute({ =>
                            ffipc.oniceconnectionstatechange( ffipc, event)
                        })
                    })
                }
            }
            onStandardizedIceConnectionChange_ = v
        }
    }
    public mut prop onicegatheringstatechange: ((pc: RTCPeerConnection, dc: Event) -> Unit){
        get () {onIceGatheringChange_??{_,_=>}}
        set (v) {
            if (onIceGatheringChange_.isNone()) {
                unsafe {
                    peerConnection_SetOnIceGatheringChange_(this.ID, { id: Int64, ptr: CJ_Event =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        let event = Event(ptr.eventType.toString())
                        ffipc.queue.execute({ =>
                            ffipc.onicegatheringstatechange( ffipc, event)
                        })
                    })
                }
            }
        }
    }
    public mut prop onIceCandidate: ((pc: RTCPeerConnection, dc: RTCPeerConnectionIceEvent) -> Unit){
        get () {onIceCandidate_??{_,_=>}}
        set (v) {
            if (onIceCandidate_.isNone()) {
                unsafe {
                    peerConnection_SetOnIceCandidate_(this.ID, { id: Int64, ptr: CJ_RTCPeerConnectionIceEvent =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        let event = RTCPeerConnectionIceEvent(ptr)
                        ffipc.queue.execute({ =>
                            ffipc.onIceCandidate(ffipc, event)
                        })
                    })
                }
            }
            onIceCandidate_ = v
        }
    }
    public static func GenerateCertificate(keyname: String): Int64{
        return unsafe {
            let str = LibC.mallocCString(keyname)
            let ret = peerConnection_static_GenerateCertificate(str)
            LibC.free(str)
            return ret
        }
    }

    public init(id: Int64) {
        super(id, this)
        unsafe {
            peerConnection_set_class_key(this.ID, this.randomid)
        }
    }

    ~init() {
        queue.shutdown()
        DelObject(this.ID)
        unsafe {
            peerConnection_CPP_FREE(this.ID)
        }
    }


    public prop canTrickleIceCandidates: Bool {
        get() {unsafe{peerConnection_GetCanTrickleIceCandidates(this.ID)}}
    }
    public prop signalingState: FFIRTCSignalingState {
        get() {FFIRTCSignalingState.GET(unsafe{peerConnection_GetSignalingState(this.ID)})}
    }
    public prop iceGatheringState: FFIRTCIceGatheringState {
        get() {FFIRTCIceGatheringState.GET(unsafe{peerConnection_GetIceGatheringState(this.ID)})}
    }
    public prop iceConnectionState: FFIRTCIceConnectionState {
        get() {FFIRTCIceConnectionState.GET(unsafe{peerConnection_GetIceConnectionState(this.ID)})}
    }
    public prop connectionState: FFIRTCIceConnectionState {
        get() {FFIRTCIceConnectionState.GET(unsafe{peerConnection_GetConnectionState(this.ID)})}
    }
    public prop localDescription: RTCSessionDescription {
        get() {
            return unsafe{RTCSessionDescription(peerConnection_GetLocalDescription(this.ID))}
        }
    }
    public prop remoteDescription: RTCSessionDescription {
        get() {
            return unsafe{RTCSessionDescription(peerConnection_GetRemoteDescription(this.ID))}
        }
    }
    public prop currentLocalDescription: Option<CJ_RTCSessionDescription> {
        get() {
            let temp = unsafe{peerConnection_GetCurrentLocalDescription(this.ID)}
            if (temp.undefined) {
                return None
            } else {
                return temp
            }
        }
    }
    public prop currentRemoteDescription: Option<CJ_RTCSessionDescription> {
        get() {
            let temp = unsafe{peerConnection_GetCurrentRemoteDescription(this.ID)}
            if (temp.undefined) {
                return None
            } else {
                return temp
            }
        }
    }
    public prop pendingLocalDescription: Option<CJ_RTCSessionDescription> {
        get() {
            let temp = unsafe{peerConnection_GetPendingLocalDescription(this.ID)}
            if (temp.undefined) {
                return None
            } else {
                return temp
            }
        }
    }
    public prop pendingRemoteDescription: Option<CJ_RTCSessionDescription> {
        get() {
            let temp = unsafe{peerConnection_GetPendingRemoteDescription(this.ID)}
            if (temp.undefined) {
                return None
            } else {
                return temp
            }
        }
    }
    public prop sctp: Option<RTCSctpTransport> {
        get() {
            let c_id = unsafe{peerConnection_GetSctp(this.ID)}
            if (c_id > 0) {
                return RTCSctpTransport(c_id)
            } else {
                return None
            }
        }
    }

    public func setLocalDescription(description: RTCSessionDescription, pe!: (ErrorMessage) -> Unit = { error => }): Unit {
        unsafe {
            this.setLocalDescription_callback_ = pe;
            peerConnection_setLocalDescription(this.ID, description.cpp.getOrThrow(), {id: Int64, msg: CJ_ErrorMessage =>
                let obj = GetObject<RTCPeerConnection>(id)
                obj.setLocalDescription_callback_(ErrorMessage(msg))
            })
        }
    }
    public func setRemoteDescription(description: RTCSessionDescription, pe: (ErrorMessage) -> Unit): Unit {
        unsafe {
            this.setRemoteDescription_callback_ = pe;
            peerConnection_setRemoteDescription(this.ID, description.cpp.getOrThrow(), {id: Int64, msg: CJ_ErrorMessage =>
                let obj = GetObject<RTCPeerConnection>(id)
                obj.setRemoteDescription_callback_(ErrorMessage(msg))
            })
        }
    }

    public func createDataChannel(label: String, dataChannelDict!: CJ_RTCDataChannelInit = CJ_RTCDataChannelInit()): RTCDataChannel {
        unsafe {
            let str = LibC.mallocCString(label)
            let ptr = peerConnection_createDataChannel(this.ID, str, dataChannelDict)
            LibC.free(str)
            return RTCDataChannel(ptr, this)
        }
    }

    public func addIceCandidate(candidate: ?RTCIceCandidateInit): Unit {
        if (let Some(v) <- candidate) {
            unsafe {
                let c = LibC.mallocCString(v.candidate)
                let m = LibC.mallocCString(v.sdpMid)
                let f =  LibC.mallocCString(v.usernameFragment)
                peerConnection_addIceCandidate(this.ID, CJ_RTCIceCandidateInit(true, c, v.sdpMLineIndex, m, f))
                LibC.free(c)
                LibC.free(m)
                LibC.free(f)
            }
        } else {
            unsafe {
                let cpp = CJ_RTCIceCandidateInit(false, LibC.mallocCString(""), 0, LibC.mallocCString(""), LibC.mallocCString(""))
                peerConnection_addIceCandidate(this.ID, cpp)
            }
        }
    }
    public func close(): Unit {
        unsafe {
            peerConnection_close(this.getID())
        }
    }

    public func setAudioPlayout(playout: Bool): Unit{
        unsafe {
            peerConnection_setAudioPlayout(this.getID(), playout)
        }

    }

    public func setAudioRecording(recording: Bool): Unit{
        unsafe {
            peerConnection_setAudioRecording(this.getID(), recording)
        }
    }

    public func addTrack(track: MediaStreamTrack, streamVec!: CJ_ArrayMediaStream = CJ_ArrayMediaStream()): Int64 {
        unsafe {
            return peerConnection_addTrack(this.getID(), track.getID(), streamVec)
        }
    }

    public func getTransceivers(): CPointer<Int64> {
        unsafe {
            return peerConnection_getTransceivers(this.getID())
        }
    }


    public func createOffer(iceRestart!: Bool = false): WebrtcResult<RTCSessionDescription> {
        unsafe {
            let cpp = peerConnection_createOffer(this.getID(), iceRestart)
            let result = if (cpp.isFail) {
                WebrtcResult<RTCSessionDescription>.Error(cpp.msg.toString())
            } else {
                WebrtcResult<RTCSessionDescription>.Ok(RTCSessionDescription(cpp.sdp.toString(), cpp.RTCSdpType.toString()))
            }
            if (cpp.isFail) {
                LibC.free(cpp.msg)
            } else {
                LibC.free(cpp.sdp)
                LibC.free(cpp.RTCSdpType)
            }
            return result
        }
    }


    public func createAnswer(iceRestart!: Bool = false): WebrtcResult<RTCSessionDescription>  {
        unsafe {
            let cpp = peerConnection_createAnswer(this.getID())
            let result = if (cpp.isFail) {
                WebrtcResult<RTCSessionDescription>.Error(cpp.msg.toString())
            } else {
                WebrtcResult<RTCSessionDescription>.Ok(RTCSessionDescription(cpp.sdp.toString(), cpp.RTCSdpType.toString()))
            }
            if (cpp.isFail) {
                LibC.free(cpp.msg)
            } else {
                LibC.free(cpp.sdp)
                LibC.free(cpp.RTCSdpType)
            }
            return result
        }
    }

}
