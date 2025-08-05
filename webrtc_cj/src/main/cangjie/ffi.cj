/**
 * Created on 2025/7/19
 */
package webrtc_cj

foreign func setThrowCangjieException(f: CFunc<(CString) -> Unit>): Unit

@C
func throwCJ(str: CString):Unit {
    throw Webrtc4cjFFIException(str.toString())
}

public class Webrtc4cjFFIException <: Exception {

    static init () {
        unsafe {
            setThrowCangjieException(throwCJ)
        }
    }

    public init(message: String) {
        super(message)
    }

    public override func toString(): String {
        if (message == "") {
            return "Webrtc4cjFFIException"
        } else {
            return "Webrtc4cjFFIException: ${message}"
        }
    }
}

@C
struct CJ_MediaTrackConstraintSet{
    var width: Int64
    var height: Int64
    var aspectRatio: Float64
    var frameRate: Float64
    var facingMode: CString
    var resizeMode: CString
    var sampleRate: Int64
    var sampleSize: Int64
    var echoCancellation: Bool
    var autoGainControl: Bool
    var noiseSuppression: Bool
    var latency: Float64
    var channelCount: Int64
    var deviceId: CString
    var groupId: CString
    var ohosScreenCaptureMode: CString
    var ohosScreenCaptureDisplayId: Int64
    var ohosScreenCaptureMissionId: CString
    var ohosScreenCaptureWindowFilter: CString
    var ohosScreenCaptureAudioFilter: CString
    var ohosScreenCaptureSkipPrivacyMode: CString
    var ohosScreenCaptureAutoRotation: Bool

    public init(width!: Int64 = 0, height!: Int64 = 0, aspectRatio!: Float64 = 0.0, frameRate!: Float64 = 0.0, facingMode!: CString = unsafe {LibC.mallocCString("")}, resizeMode!: CString = unsafe {LibC.mallocCString("")}, sampleRate!: Int64 = 0, sampleSize!: Int64 = 0, echoCancellation!: Bool = false, autoGainControl!: Bool = false, noiseSuppression!: Bool = false, latency!: Float64 = 0.0, channelCount!: Int64 = 0, deviceId!: CString = unsafe {LibC.mallocCString("")}, groupId!: CString = unsafe {LibC.mallocCString("")}, ohosScreenCaptureMode!: CString = unsafe {LibC.mallocCString("")}, ohosScreenCaptureDisplayId!: Int64 = 0, ohosScreenCaptureMissionId!: CString = unsafe {LibC.mallocCString("")}, ohosScreenCaptureWindowFilter!: CString = unsafe {LibC.mallocCString("")}, ohosScreenCaptureAudioFilter!: CString = unsafe {LibC.mallocCString("")}, ohosScreenCaptureSkipPrivacyMode!: CString = unsafe {LibC.mallocCString("")}, ohosScreenCaptureAutoRotation!: Bool = false) {
        this.width = width
        this.height = height
        this.aspectRatio = aspectRatio
        this.frameRate = frameRate
        this.facingMode = facingMode
        this.resizeMode = resizeMode
        this.sampleRate = sampleRate
        this.sampleSize = sampleSize
        this.echoCancellation = echoCancellation
        this.autoGainControl = autoGainControl
        this.noiseSuppression = noiseSuppression
        this.latency = latency
        this.channelCount = channelCount
        this.deviceId = deviceId
        this.groupId = groupId
        this.ohosScreenCaptureMode = ohosScreenCaptureMode
        this.ohosScreenCaptureDisplayId = ohosScreenCaptureDisplayId
        this.ohosScreenCaptureMissionId = ohosScreenCaptureMissionId
        this.ohosScreenCaptureWindowFilter = ohosScreenCaptureWindowFilter
        this.ohosScreenCaptureAudioFilter = ohosScreenCaptureAudioFilter
        this.ohosScreenCaptureSkipPrivacyMode = ohosScreenCaptureSkipPrivacyMode
        this.ohosScreenCaptureAutoRotation = ohosScreenCaptureAutoRotation
    }
}


//foreign func GetVideoTracks(): CPointer<Int64>
//
//
//public class MediaStreamTrack {
//    private var ptr: Int64
//
//    public init(ptr: Int64) {
//        this.ptr = ptr
//    }
//
//    public func toJson(): String {
//        // TODO
//        ""
//    }
//
//}
//
//
//func cangjieGetVideoTracks(): Array<MediaStreamTrack> {
//    unsafe {
//        let arr = GetVideoTracks()
//        let list = ArrayList<MediaStreamTrack> ()
//        for (item in arr) {
//            list.add(GetVideoTracks(item))
//        }
//        return list.toArray()
//    }
//}
