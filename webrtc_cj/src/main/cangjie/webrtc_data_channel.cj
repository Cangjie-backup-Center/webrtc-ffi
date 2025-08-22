/**
 * Created on 2025/8/15
 */
package webrtc_cj

foreign {
    func dataConnection_set_class_key(cpp_ptr: Int64, id: Int64): Unit
    func dataConnection_set_cj_func_Onopen_(cpp_ptr: Int64, fn: CFunc<(id: Int64, event: CJ_Event) -> Unit>): Unit
    func dataConnection_set_cj_func_Onclosing_(cpp_ptr: Int64, fn: CFunc<(id: Int64, event: CJ_Event) -> Unit>): Unit
    func dataConnection_set_cj_func_Onclose_(cpp_ptr: Int64, fn: CFunc<(id: Int64, event: CJ_Event) -> Unit>): Unit
    func dataConnection_set_cj_func_Onmessage_(cpp_ptr: Int64, fn: CFunc<(id: Int64, event: CJ_MessageEvent) -> Unit>): Unit

    // read only {
    func dataConnection_get_label_(cpp_ptr: Int64): CString
    func dataConnection_get_ordered_(cpp_ptr: Int64): Bool
    func dataConnection_get_maxPacketLifeTime_(cpp_ptr: Int64): Int64
    func dataConnection_get_maxRetransmits_(cpp_ptr: Int64): Int64
    func dataConnection_get_protocol_(cpp_ptr: Int64): CString
    func dataConnection_get_negotiated_(cpp_ptr: Int64): Bool
    func dataConnection_get_id_(cpp_ptr: Int64): Int64
    func dataConnection_get_readyState_(cpp_ptr: Int64): Int64
    func dataConnection_get_bufferedAmount_(cpp_ptr: Int64): Int64
    // } read only
    func dataConnection_get_bufferedAmountLowThreshold_(cpp_ptr: Int64): Int64
    func dataConnection_set_bufferedAmountLowThreshold_(cpp_ptr: Int64, value: Int64): Unit
    func dataConnection_get_binaryType_(cpp_ptr: Int64): Int64
    func dataConnection_set_binaryType_(cpp_ptr: Int64, value: Int64): Unit

    func dataConnection_Send_String(cpp_ptr: Int64, value: CString): Unit
    func dataConnection_Send_binary(cpp_ptr: Int64, value: CPointer<Byte>, size: Int64): Unit
    func dataConnection_Close(cpp_ptr: Int64): Unit
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

public class RTCDataChannel <: WebrtcClass & Resource {
    var onopen_: ?((pc: RTCDataChannel, dc: Event) -> Unit) = None
    var onclosing_: ?((pc: RTCDataChannel, dc: Event) -> Unit) = None
    var onclose_: ?((pc: RTCDataChannel, dc: Event) -> Unit) = None
    var onmessage_: ?((pc: RTCDataChannel, dc: MessageEvent) -> Unit) = None
    var onerror_: ?((pc: RTCDataChannel, dc: RTCErrorEvent) -> Unit) = None
    var closed: Bool = false

    public init(id: Int64) {
        super(id, this)
        unsafe {dataConnection_set_class_key(this.ID, this.randomid)}
    }

    public mut prop onopen: ((pc: RTCDataChannel, dc: Event) -> Unit) {
        get (){onopen_ ?? {_,_=>}}
        set(value) {
            if (onopen_.isNone()){
                unsafe {
                    dataConnection_set_cj_func_Onopen_(this.ID, { id: Int64, event: CJ_Event =>
                        let obj: RTCDataChannel = GetObject<RTCDataChannel>(id)
                        obj.onopen(obj, Event(event.eventType.toString()))
                    })
                }
            }
            onopen_ = value
        }
    }

    public mut prop onclosing: ((pc: RTCDataChannel, dc: Event) -> Unit) {
        get (){onclosing_ ?? {_,_=>}}
        set(value) {
            if (onclosing_.isNone()) {
                unsafe {
                     dataConnection_set_cj_func_Onclosing_(this.ID, { id: Int64, event: CJ_Event =>
                        let obj: RTCDataChannel = GetObject<RTCDataChannel>(id)
                        obj.onclosing(obj, Event(event.eventType.toString()))
                    })
                }
            }
            onclosing_ = value
        }
    }

    public mut prop onclose: ((pc: RTCDataChannel, dc: Event) -> Unit) {
        get (){onclose_ ?? {_,_=>}}
        set(value) {
            if(onclose_.isNone()) {
                unsafe {
                     dataConnection_set_cj_func_Onclose_(this.ID, { id: Int64, event: CJ_Event =>
                        let obj: RTCDataChannel = GetObject<RTCDataChannel>(id)
                        obj.onclose(obj, Event(event.eventType.toString()))
                    })
                }
            }
            onclose_ = value
        }
    }

    public mut prop onmessage: ((pc: RTCDataChannel, dc: MessageEvent) -> Unit) {
        get (){onmessage_ ?? {_,_=>}}
        set(value) {
            if (onmessage_.isNone()) {
                unsafe {
                    dataConnection_set_cj_func_Onmessage_(this.ID, { id: Int64, event: CJ_MessageEvent =>
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
            onmessage_ = value
        }
    }

    public mut prop onerror: ((pc: RTCDataChannel, dc: RTCErrorEvent) -> Unit) {
        get(){onerror_??{_,_=>}}
        set(v) {
            // TODO
            onerror_ = v
        }
    }

    public prop label: String
    {
        get() {
            unsafe {dataConnection_get_label_(this.ID)}.toString()
        }
    }
    public prop ordered: Bool
    {
        get(){
            unsafe {dataConnection_get_ordered_(this.ID)}
        }
    }
    public prop maxPacketLifeTime: ?Int64
    {
        get() {
            let i = unsafe {dataConnection_get_maxPacketLifeTime_(this.ID)}
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
            let i = unsafe {dataConnection_get_maxRetransmits_(this.ID)}
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
            unsafe {dataConnection_get_protocol_(this.ID)}.toString()
        }
    }
    public prop negotiated: Bool
    {
        get(){
            unsafe {dataConnection_get_negotiated_(this.ID)}
        }
    }
    public prop id: ?Int64
    {
        get() {
            let i = unsafe {dataConnection_get_id_(this.ID)}
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
            DataChannelState.GET(unsafe {dataConnection_get_readyState_(this.ID)})
        }
    }
    public prop bufferedAmount: Int64
    {
        get() {
            unsafe {dataConnection_get_bufferedAmount_(this.ID)}
        }
    }
    public mut prop bufferedAmountLowThreshold: DataChannelState
    {
        get() {
            DataChannelState.GET(unsafe {dataConnection_get_bufferedAmountLowThreshold_(this.ID)})
        }
        set(v) {
            unsafe {dataConnection_set_bufferedAmountLowThreshold_(this.ID,DataChannelState.GET(v))}
        }
    }
    public mut prop binaryType: BinaryType
    {
        get() {
            BinaryType.GET(unsafe {dataConnection_get_binaryType_(this.ID)})
        }
        set(v) {
            unsafe {dataConnection_set_binaryType_(this.ID, BinaryType.GET(v))}
        }
    }

    public func send(data: String): Unit {
        unsafe {
            dataConnection_Send_String(this.ID, LibC.mallocCString(data))
        }
    }

    public func send(data: Array<Byte>): Unit {
        unsafe {
            let ptr = acquireArrayRawData(data)
            dataConnection_Send_binary(this.ID, ptr.pointer, data.size)
            releaseArrayRawData(ptr)
        }
    }

    public func close(): Unit {
        unsafe {
            if (!this.closed){
                dataConnection_Close(this.ID)
                this.closed = true
            }
        }
    }

    public func isClosed(): Bool {
        this.closed
    }

}