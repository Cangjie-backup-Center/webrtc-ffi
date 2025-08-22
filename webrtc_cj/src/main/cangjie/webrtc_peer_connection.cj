/**
 * Created on 2025/8/13
 */
package webrtc_cj

foreign func peerConnection_set_class_key(cpp_ptr: Int64, id: Int64): Unit
foreign func peerConnection_set_cj_func_call_OnDataChannel_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: Int64) -> Unit>): Unit
foreign func peerConnection_set_cj_func_call_OnSignalingChange_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_Event) -> Unit>): Unit
foreign func peerConnection_set_cj_func_call_OnIceCandidateError_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_RTCPeerConnectionIceErrorEvent) -> Unit>): Unit
foreign func peerConnection_set_cj_func_call_onTrack_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_RTCTrackEvent) -> Unit>): Unit
foreign func peerConnection_set_cj_func_call_SetOnConnectionChange_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_Event) -> Unit>): Unit
foreign func peerConnection_set_cj_func_call_SetOnRenegotiationNeeded_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_Event) -> Unit>): Unit
foreign func peerConnection_set_cj_func_call_SetOnStandardizedIceConnectionChange_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_Event) -> Unit>): Unit
foreign func peerConnection_set_cj_func_call_SetOnIceGatheringChange_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_Event) -> Unit>): Unit
foreign func peerConnection_set_cj_func_call_SetOnIceCandidate_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_OnIceCandidateEvent) -> Unit>): Unit
//foreign func peerConnection_set_cj_func_call_SetCallBackCreateOffer_(cpp_ptr: Int64, fn: CFunc<(id: Int64, isSuccess: Bool, ptr: CJ_RTCSessionDescription, msg: CString) -> Unit>): Unit
//foreign func peerConnection_set_cj_func_call_SetCallBackCreateAnswer_(cpp_ptr: Int64, fn: CFunc<(id: Int64, isSuccess: Bool, ptr: CJ_RTCSessionDescription, msg: CString) -> Unit>): Unit

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


public class RTCPeerConnection <: WebrtcClass {

    var ondatachannel_: ?((pc: RTCPeerConnection, dc: RTCDataChannel) -> Unit) = None
    var onSignalingChange_: ?((pc: RTCPeerConnection, dc: Event) -> Unit) = None
    var onIceCandidateError_: ?((pc: RTCPeerConnection, dc: RTCPeerConnectionIceErrorEvent) -> Unit) = None
    var onTrack_: ?((pc: RTCPeerConnection, dc: RTCTrackEvent) -> Unit) = None
    var onConnectionChange_: ?((pc: RTCPeerConnection, dc: Event) -> Unit) = None
    var onRenegotiationNeeded_: ?((pc: RTCPeerConnection, dc: Event) -> Unit) = None
    var onStandardizedIceConnectionChange_: ?((pc: RTCPeerConnection, dc: Event) -> Unit) = None
    var onIceGatheringChange_: ?((pc: RTCPeerConnection, dc: Event) -> Unit) = None
    var onIceCandidate_: ?((pc: RTCPeerConnection, dc: OnIceCandidateEvent) -> Unit) = None


    public mut prop ondatachannel: ((pc: RTCPeerConnection, dc: RTCDataChannel) -> Unit) {
        get() {ondatachannel_ ?? {_,_=>}}
        set(v) {
            if (this.ondatachannel_.isNone()) {
                unsafe {
                    peerConnection_set_cj_func_call_OnDataChannel_(this.ID, { id: Int64, ptr: Int64 =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        ffipc.ondatachannel(ffipc, RTCDataChannel(ptr))
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
                    peerConnection_set_cj_func_call_OnSignalingChange_(this.ID, { id: Int64, ptr: CJ_Event =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        ffipc.onSignalingChange(ffipc, Event(ptr.eventType.toString()))
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
                    peerConnection_set_cj_func_call_OnIceCandidateError_(this.ID, { id: Int64, ptr: CJ_RTCPeerConnectionIceErrorEvent =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        ffipc.onIceCandidateError(ffipc, RTCPeerConnectionIceErrorEvent(
                            ptr.TYPE.toString(),
                            ptr.address.toString(),
                            ptr.port,
                            ptr.url.toString(),
                            ptr.errorCode,
                            ptr.errorText.toString()
                        ))
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
                    peerConnection_set_cj_func_call_onTrack_(this.ID, { id: Int64, ptr: CJ_RTCTrackEvent =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        let arr = Array<Int64> (ptr.streams_size, repeat: 0)
                        for(i in 0..ptr.streams_size) {
                            arr[i] = ptr.streams.read(i)
                        }
                        ffipc.onTrack(
                            ffipc, RTCTrackEvent(
                                ptr.TYPE.toString(),
                                arr,
                                ptr.MediaStreamTrack_ptr,
                                ptr.RtpReceiver_ptr,
                                ptr.RtpTransceiver_ptr
                            )
                        )
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
                    peerConnection_set_cj_func_call_SetOnConnectionChange_(this.ID, { id: Int64, ptr: CJ_Event =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        ffipc.onconnectionstatechange( ffipc, Event(ptr.eventType.toString()) )
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
                    peerConnection_set_cj_func_call_SetOnConnectionChange_(this.ID, { id: Int64, ptr: CJ_Event =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        ffipc.onnegotiationneeded( ffipc, Event(ptr.eventType.toString()) )
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
                    peerConnection_set_cj_func_call_SetOnConnectionChange_(this.ID, { id: Int64, ptr: CJ_Event =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        ffipc.oniceconnectionstatechange( ffipc, Event(ptr.eventType.toString()) )
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
                    peerConnection_set_cj_func_call_SetOnConnectionChange_(this.ID, { id: Int64, ptr: CJ_Event =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                        ffipc.onicegatheringstatechange( ffipc, Event(ptr.eventType.toString()) )
                    })
                }
            }
        }
    }
    public mut prop onIceCandidate: ((pc: RTCPeerConnection, dc: OnIceCandidateEvent) -> Unit){
        get () {onIceCandidate_??{_,_=>}}
        set (v) {
            if (onIceCandidate_.isNone()) {
                unsafe {
                    peerConnection_set_cj_func_call_SetOnConnectionChange_(this.ID, { id: Int64, ptr: CJ_Event =>
                        let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
//                        ffipc.onIceCandidate( ffipc, Event(ptr.eventType.toString()) ) // TODO
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

    public prop canTrickleIceCandidates: Bool {
        get() {unsafe{peerConnection_GetCanTrickleIceCandidates(this.ID)}}
    }
    public prop signalingState: Int64 {
        get() {unsafe{peerConnection_GetSignalingState(this.ID)}}
    }
    public prop iceGatheringState: Int64 {
        get() {unsafe{peerConnection_GetIceGatheringState(this.ID)}}
    }
    public prop iceConnectionState: Int64 {
        get() {unsafe{peerConnection_GetIceConnectionState(this.ID)}}
    }
    public prop connectionState: Int64 {
        get() {unsafe{peerConnection_GetConnectionState(this.ID)}}
    }
    public prop localDescription: Option<CJ_RTCSessionDescription> {
        get() {
            let temp = unsafe{peerConnection_GetLocalDescription(this.ID)}
            if (temp.undefined) {
                return None
            } else {
                return temp
            }
        }
    }
    public prop remoteDescription: Option<CJ_RTCSessionDescription> {
        get() {
            let temp = unsafe{peerConnection_GetRemoteDescription(this.ID)}
            if (temp.undefined) {
                return None
            } else {
                return temp
            }
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



}
