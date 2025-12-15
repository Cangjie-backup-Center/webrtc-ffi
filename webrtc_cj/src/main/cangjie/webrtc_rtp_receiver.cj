package webrtc_cj


public class RTCRtpReceiver <: WebrtcClass {

    public init(id: Int64) {
        super(id, this)
    }
    ~init(){
        DelObject(this.ID)
    }
}

