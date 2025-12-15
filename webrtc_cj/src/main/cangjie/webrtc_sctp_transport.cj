package webrtc_cj


public class RTCSctpTransport <: WebrtcClass {
    public init(id: Int64) {
        super(id, this)
    }
    ~init(){
        DelObject(this.ID)
    }
}
