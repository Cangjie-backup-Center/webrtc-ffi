/**
 * Created on 2025/8/18
 */
package webrtc_cj

@C
public struct RTCRtpEncodingParameters {
    var active: Bool
    var maxBitrate: Int64
    var maxFramerate: Int64
    var scaleResolutionDownBy: Int64
    public init(active!: Bool = false, maxBitrate!: Int64 = -1, maxFramerate!: Int64 = -1, scaleResolutionDownBy!: Int64 = -1) {
        this.active = active
        this.maxBitrate = maxBitrate
        this.maxFramerate = maxFramerate
        this.scaleResolutionDownBy = scaleResolutionDownBy
    }
}

@C
public struct RTCRtpSendParameters {
    var encodings: CPointer<RTCRtpEncodingParameters>
    var encodings_size: Int64
    var transactionId: CString

    public init(transactionId: String, encodings!: Array<RTCRtpEncodingParameters> = Array<RTCRtpEncodingParameters>()) {
        unsafe {
            this.transactionId = LibC.mallocCString(transactionId)
            this.encodings_size = encodings.size
            this.encodings = acquireArrayRawData(encodings).pointer
        }
    }

}