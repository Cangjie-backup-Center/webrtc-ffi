/**
 * Created on 2025/8/13
 */
package webrtc_cj

foreign func peerConnection_set_class_key(cpp_ptr: Int64, id: Int64): Unit
foreign func peerConnection_set_cj_func_call_OnDataChannel_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: Int64) -> Unit>): Unit
foreign func peerConnection_set_cj_func_call_OnSignalingChange_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_Event) -> Unit>): Unit
foreign func peerConnection_set_cj_func_call_OnIceCandidateError_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_RTCPeerConnectionIceErrorEvent) -> Unit>): Unit
foreign func peerConnection_set_cj_func_call_onTrack_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_RTCTrackEvent) -> Unit>): Unit
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

    var ondatachannel_: ((pc: RTCPeerConnection, dc: RTCDataChannel) -> Unit) = {_,_ => }
    var ondatachannel_use: Bool = false
    var onSignalingChange_: ((pc: RTCPeerConnection, dc: Event) -> Unit) = {_,_ => }
    var onSignalingChange_use: Bool = false
    var onIceCandidateError_: ((pc: RTCPeerConnection, dc: RTCPeerConnectionIceErrorEvent) -> Unit) = {_,_ => }
    var onIceCandidateError_use: Bool = false
    var onTrack_: ((pc: RTCPeerConnection, dc: RTCTrackEvent) -> Unit) = {_,_ => }
    var onTrack_use: Bool = false


    public mut prop ondatachannel: ((pc: RTCPeerConnection, dc: RTCDataChannel) -> Unit) {
        get() {ondatachannel_}
        set(v) {
            ondatachannel_ = v
            if (ondatachannel_use) {
                return
            }
            unsafe {
                peerConnection_set_cj_func_call_OnDataChannel_(this.ID, { id: Int64, ptr: Int64 =>
                    let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                    ffipc.ondatachannel(ffipc, RTCDataChannel(ptr))
                })
            }
            ondatachannel_use = true
        }
    }
    public mut prop onSignalingChange: ((pc: RTCPeerConnection, dc: Event) -> Unit) {
        get() {onSignalingChange_}
        set(v) {
            onSignalingChange_ = v
            if (onSignalingChange_use) {
                return
            }
            unsafe {
                peerConnection_set_cj_func_call_OnSignalingChange_(this.ID, { id: Int64, ptr: CJ_Event =>
                    let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                    ffipc.onSignalingChange(ffipc, Event(ptr.eventType.toString()))
                })
            }
            onSignalingChange_use = true
        }
    }
    public mut prop onIceCandidateError: ((pc: RTCPeerConnection, dc: RTCPeerConnectionIceErrorEvent) -> Unit) {
        get() {onIceCandidateError_}
        set(v) {
            onIceCandidateError_ = v
            if (onIceCandidateError_use) {
                return
            }
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
            onIceCandidateError_use = true
        }
    }

    public mut prop onTrack: ((pc: RTCPeerConnection, dc: RTCTrackEvent) -> Unit) {
        get() {onTrack_}
        set(v) {
            onTrack_ = v
            if (onTrack_use) {
                return
            }
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
            onTrack_use = true
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
