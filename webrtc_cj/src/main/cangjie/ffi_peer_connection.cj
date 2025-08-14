/**
 * Created on 2025/8/13
 */
package webrtc_cj


foreign func set_peerConnection_class_key(cpp_ptr: Int64, id: Int64): Unit
foreign func set_cj_func_call_OnDataChannel_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: Int64) -> Unit>): Unit
foreign func set_cj_func_call_OnSignalingChange_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_Event) -> Unit>): Unit
foreign func set_cj_func_call_OnIceCandidateError_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_RTCPeerConnectionIceErrorEvent) -> Unit>): Unit
foreign func set_cj_func_call_onTrack_(cpp_ptr: Int64, fn: CFunc<(id: Int64, ptr: CJ_RTCTrackEvent) -> Unit>): Unit



public class ffiDataChannelObserverTemp <: WebrtcClass {
    public init(id: Int64) {
        super(id, this)
    }
}

public class ffiPeerConnection <: WebrtcClass {

    public var ondatachannel: ((pc: ffiPeerConnection, dc: ffiDataChannelObserverTemp) -> Unit) = {_,_ => }
    public var onSignalingChange: ((pc: ffiPeerConnection, dc: Event) -> Unit) = {_,_ => }
    public var onIceCandidateError: ((pc: ffiPeerConnection, dc: RTCPeerConnectionIceErrorEvent) -> Unit) = {_,_ => }
    public var onTrack: ((pc: ffiPeerConnection, dc: RTCTrackEvent) -> Unit) = {_,_ => }


    public init(id: Int64) {
        super(id, this)
        unsafe {
            set_peerConnection_class_key(this.ID, this.randomid)
            set_cj_func_call_OnDataChannel_(this.ID, cj_func_call_OnDataChannel_)
            set_cj_func_call_OnSignalingChange_(this.ID, cj_func_call_OnSignalingChange_)
            set_cj_func_call_OnIceCandidateError_(this.ID, cj_func_call_OnIceCandidateError_)
            set_cj_func_call_onTrack_(this.ID, cj_func_call_OnTrack_)
//            set_cj_func_call_OnDataChannel_(this.ID, cj_func_call_OnDataChannel_)
//            set_cj_func_call_OnDataChannel_(this.ID, cj_func_call_OnDataChannel_)
//            set_cj_func_call_OnDataChannel_(this.ID, cj_func_call_OnDataChannel_)
//            set_cj_func_call_OnDataChannel_(this.ID, cj_func_call_OnDataChannel_)
//            set_cj_func_call_OnDataChannel_(this.ID, cj_func_call_OnDataChannel_)
//            set_cj_func_call_OnDataChannel_(this.ID, cj_func_call_OnDataChannel_)
//            set_cj_func_call_OnDataChannel_(this.ID, cj_func_call_OnDataChannel_)
        }
    }
}

@C
func cj_func_call_OnDataChannel_(id: Int64, ptr: Int64): Unit {
    let ffipc: ffiPeerConnection = ((WebRtcGlobal.map.get(id) ?? return) as ffiPeerConnection).getOrThrow()
    ffipc.ondatachannel(ffipc, ffiDataChannelObserverTemp(ptr))
}

@C
func cj_func_call_OnSignalingChange_(id: Int64, ptr: CJ_Event): Unit {
    let ffipc: ffiPeerConnection = ((WebRtcGlobal.map.get(id) ?? return) as ffiPeerConnection).getOrThrow()
    ffipc.onSignalingChange(ffipc, Event(unsafe {ptr.eventType.toString()}))
}

@C
func cj_func_call_OnIceCandidateError_(id: Int64, ptr: CJ_RTCPeerConnectionIceErrorEvent): Unit {
    let ffipc: ffiPeerConnection = ((WebRtcGlobal.map.get(id) ?? return) as ffiPeerConnection).getOrThrow()
    unsafe {ffipc.onIceCandidateError(ffipc, RTCPeerConnectionIceErrorEvent(
        ptr.TYPE.toString(),
        ptr.address.toString(),
        ptr.port,
        ptr.url.toString(),
        ptr.errorCode,
        ptr.errorText.toString()
    ))}
}


@C
func cj_func_call_OnTrack_(id: Int64, ptr: CJ_RTCTrackEvent): Unit {
    let ffipc: ffiPeerConnection = ((WebRtcGlobal.map.get(id) ?? return) as ffiPeerConnection).getOrThrow()
    unsafe {
        let arr = Array<Int64> (ptr.streams_size, repeat: 0)
        for(i in 0..ptr.streams_size) {
            arr[i] = ptr.streams.read(i)
        }

        ffipc.onTrack(ffipc, RTCTrackEvent(
                ptr.TYPE.toString(),
                arr,
                ptr.MediaStreamTrack_ptr,
                ptr.RtpReceiver_ptr,
                ptr.RtpTransceiver_ptr
            )
        )
    }
}

