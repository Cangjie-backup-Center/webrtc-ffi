/**
 * Created on 2025/8/15
 */
package webrtc_cj

foreign {
    func set_dataConnection_class_key(cpp_ptr: Int64, id: Int64): Unit
    func set_dataConnection_cj_func_Onopen_(cpp_ptr: Int64, fn: CFunc<(id: Int64, event: CJ_Event) -> Unit>): Unit
    func set_dataConnection_cj_func_Onclosing_(cpp_ptr: Int64, fn: CFunc<(id: Int64, event: CJ_Event) -> Unit>): Unit
    func set_dataConnection_cj_func_Onclose_(cpp_ptr: Int64, fn: CFunc<(id: Int64, event: CJ_Event) -> Unit>): Unit
    func set_dataConnection_cj_func_Onmessage_(cpp_ptr: Int64, fn: CFunc<(id: Int64, event: CJ_MessageEvent) -> Unit>): Unit

    // read only {
    func get_dataConnection_label_(cpp_ptr: Int64): CString
    func get_dataConnection_ordered_(cpp_ptr: Int64): Bool
    func get_dataConnection_maxPacketLifeTime_(cpp_ptr: Int64): Int64
    func get_dataConnection_maxRetransmits_(cpp_ptr: Int64): Int64
    func get_dataConnection_protocol_(cpp_ptr: Int64): CString
    func get_dataConnection_negotiated_(cpp_ptr: Int64): Bool
    func get_dataConnection_id_(cpp_ptr: Int64): Int64
    func get_dataConnection_readyState_(cpp_ptr: Int64): Int64
    func get_dataConnection_bufferedAmount_(cpp_ptr: Int64): Int64
    // } read only
    func get_dataConnection_bufferedAmountLowThreshold_(cpp_ptr: Int64): Int64
    func set_dataConnection_bufferedAmountLowThreshold_(cpp_ptr: Int64, value: Int64): Unit
    func get_dataConnection_binaryType_(cpp_ptr: Int64): Int64
    func set_dataConnection_binaryType_(cpp_ptr: Int64, value: Int64): Unit

}

public enum DataChannelState {
    CLOSED | CLOSING | CONNECTING | OPEN

    static func GET(id: Int64): DataChannelState {
        return match (id) {
            case 0=> CLOSED
            case 1=> CLOSING
            case 2=> CONNECTING
            case 3=> OPEN
            case _ => throw Webrtc4cjException("")
        }
    }
    static func GET(id: DataChannelState) {
        return match (id) {
            case CLOSED=> 0
            case CLOSING=> 1
            case CONNECTING=> 2
            case OPEN=> 3
        }
    }
}
public enum BinaryType {
    BLOB | ARRAYBUFFER

    static func GET(id: Int64) {
        return match (id) {
            case 0=> BLOB
            case 1=> ARRAYBUFFER
            case _ => throw Webrtc4cjException("")
        }
    }
    static func GET(id: BinaryType) {
        return match (id) {
            case BLOB=> 0
            case ARRAYBUFFER=> 1
        }
    }
}

public class RTCDataChannel <: WebrtcClass {
    public var onopen: ((pc: RTCDataChannel, dc: Event) -> Unit) = {_,_ => }
    public var onclosing: ((pc: RTCDataChannel, dc: Event) -> Unit) = {_,_ => }
    public var onclose: ((pc: RTCDataChannel, dc: Event) -> Unit) = {_,_ => }
    public var onmessage: ((pc: RTCDataChannel, dc: MessageEvent) -> Unit) = {_,_ => }
//    public var onerror: ((pc: RTCDataChannel, dc: Event) -> Unit) = {_,_ => }

    public init(id: Int64) {
        super(id, this)
        unsafe {
            set_dataConnection_class_key(this.ID, this.randomid)
            set_dataConnection_cj_func_Onopen_(this.ID, { id: Int64, event: CJ_Event =>
                let obj: RTCDataChannel = GetObject<RTCDataChannel>(id)
                obj.onopen(obj, Event(event.eventType.toString()))
            })
            set_dataConnection_cj_func_Onclosing_(this.ID, { id: Int64, event: CJ_Event =>
                let obj: RTCDataChannel = GetObject<RTCDataChannel>(id)
                obj.onclosing(obj, Event(event.eventType.toString()))
            })
            set_dataConnection_cj_func_Onclose_(this.ID, { id: Int64, event: CJ_Event =>
                let obj: RTCDataChannel = GetObject<RTCDataChannel>(id)
                obj.onclose(obj, Event(event.eventType.toString()))
            })
            set_dataConnection_cj_func_Onmessage_(this.ID, { id: Int64, event: CJ_MessageEvent =>
                let obj: RTCDataChannel = GetObject<RTCDataChannel>(id)
                if (event.binary) {
                    let arr = Array<Byte>(event.data_arr_size, repeat: 0)
                    for(i in 0..event.data_arr_size) {
                        arr[i] = event.data_arr.read(i)
                    }
                    obj.onmessage(obj, MessageEvent(event.TYPE.toString(), ARRAY_BUFFER(arr)))
                } else{
                    obj.onmessage(obj, MessageEvent(event.TYPE.toString(), STRING(event.data_str.toString())))
                }
            })
        }
    }

    public prop label: String
    {
        get() {
            unsafe {get_dataConnection_label_(this.ID)}.toString()
        }
    }
    public prop ordered: Bool
    {
        get(){
            unsafe {get_dataConnection_ordered_(this.ID)}
        }
    }
    public prop maxPacketLifeTime: ?Int64
    {
        get() {
            let i = unsafe {get_dataConnection_maxPacketLifeTime_(this.ID)}
            if (i>=0) {
                return i
            } else {
                None
            }
        }
    }
    public prop maxRetransmits: ?Int64
    {
        get() {
            let i = unsafe {get_dataConnection_maxRetransmits_(this.ID)}
            if (i>=0) {
                return i
            } else {
                None
            }
        }
    }
    public prop protocol: String
    {
        get() {
            unsafe {get_dataConnection_protocol_(this.ID)}.toString()
        }
    }
    public prop negotiated: Bool
    {
        get(){
            unsafe {get_dataConnection_negotiated_(this.ID)}
        }
    }
    public prop id: ?Int64
    {
        get() {
            let i = unsafe {get_dataConnection_id_(this.ID)}
            if (i>=0) {
                return i
            } else {
                None
            }
        }
    }
    public prop readyState: DataChannelState
    {
        get() {
            DataChannelState.GET(unsafe {get_dataConnection_readyState_(this.ID)})
        }
    }
    public prop bufferedAmount: Int64
    {
        get() {
            unsafe {get_dataConnection_bufferedAmount_(this.ID)}
        }
    }
    public mut prop bufferedAmountLowThreshold: DataChannelState
    {
        get() {
            DataChannelState.GET(unsafe {get_dataConnection_bufferedAmountLowThreshold_(this.ID)})
        }
        set(v) {
            unsafe {set_dataConnection_bufferedAmountLowThreshold_(this.ID,DataChannelState.GET(v))}
        }
    }
    public mut prop binaryType: BinaryType
    {
        get() {
            BinaryType.GET(unsafe {get_dataConnection_binaryType_(this.ID)})
        }
        set(v) {
            unsafe {set_dataConnection_binaryType_(this.ID, BinaryType.GET(v))}
        }
    }

}