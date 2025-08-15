/**
 * Created on 2025/8/13
 */
package webrtc_cj

foreign func set_peerConnection_class_key(cpp_ptr: Int64, id: Int64): Unit
foreign func set_peerConnection_cj_func_call_OnDataChannel_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: Int64) -> Unit>): Unit
foreign func set_peerConnection_cj_func_call_OnSignalingChange_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_Event) -> Unit>): Unit
foreign func set_peerConnection_cj_func_call_OnIceCandidateError_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_RTCPeerConnectionIceErrorEvent) -> Unit>): Unit
foreign func set_peerConnection_cj_func_call_onTrack_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_RTCTrackEvent) -> Unit>): Unit

public class ffiDataChannelObserverTemp <: WebrtcClass {
    public init(id: Int64) {
        super(id, this)
    }
}

public class RTCPeerConnection <: WebrtcClass {

    public var ondatachannel: ((pc: RTCPeerConnection, dc: ffiDataChannelObserverTemp) -> Unit) = {_,_ => }
    public var onSignalingChange: ((pc: RTCPeerConnection, dc: Event) -> Unit) = {_,_ => }
    public var onIceCandidateError: ((pc: RTCPeerConnection, dc: RTCPeerConnectionIceErrorEvent) -> Unit) = {_,_ => }
    public var onTrack: ((pc: RTCPeerConnection, dc: RTCTrackEvent) -> Unit) = {_,_ => }


    public init(id: Int64) {
        super(id, this)
        unsafe {
            set_peerConnection_class_key(this.ID, this.randomid)
            set_peerConnection_cj_func_call_OnDataChannel_(this.ID, { id: Int64, ptr: Int64 =>
                let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                ffipc.ondatachannel(ffipc, ffiDataChannelObserverTemp(ptr))
            })
            set_peerConnection_cj_func_call_OnSignalingChange_(this.ID, { id: Int64, ptr: CJ_Event =>
                let ffipc: RTCPeerConnection = GetObject<RTCPeerConnection>(id)
                ffipc.onSignalingChange(ffipc, Event(ptr.eventType.toString()))
            })
            set_peerConnection_cj_func_call_OnIceCandidateError_(this.ID, { id: Int64, ptr: CJ_RTCPeerConnectionIceErrorEvent =>
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
            set_peerConnection_cj_func_call_onTrack_(this.ID, { id: Int64, ptr: CJ_RTCTrackEvent =>
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


}
