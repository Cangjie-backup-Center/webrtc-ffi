/**
 * Created on 2025/7/19
 */
package webrtc_cj

foreign func setThrowCangjieException(f: CFunc<(CString) -> Unit>): Unit

@C //see ffi_exception.h
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

@C // see ffi_define_struct.h
public struct CJ_EnumerateDevicesInfo {
    public let deviceId: CString = unsafe {zeroValue<CString>()}
    public let groupId: CString = unsafe {zeroValue<CString>()}
    public let label: CString = unsafe {zeroValue<CString>()}
    public let kind: CString = unsafe {zeroValue<CString>()}
}

@C // see ffi_define_struct.h
public struct CJ_ffiMediaStreamTrackJson {
    public let id: CString = unsafe {zeroValue<CString>()}
    public let kind: CString = unsafe {zeroValue<CString>()}
    public let readyState: CString = unsafe {zeroValue<CString>()}
    public let enabled: Bool = false
}

@C // see ffi_define_struct.h
public struct CJ_ReturnEnumerateDevicesInfo {
    public let ptr: CPointer<CJ_EnumerateDevicesInfo> = unsafe {zeroValue<CPointer<CJ_EnumerateDevicesInfo>>()}
    public let size: Int64 = 0
}

@C // see ffi_define_struct.h
public struct CJ_ReturnArray {
    public let ptr: CPointer<Int64> = unsafe {zeroValue<CPointer<Int64>>()}
    public let size: Int64 = 0
}

@C // see ffi_define_struct.h
public struct CJ_MediaTrackConstraintSet{
    public let width: Int64
    public let height: Int64
    public let aspectRatio: Float64
    public let frameRate: Float64
    public let facingMode: CString
    public let resizeMode: CString
    public let sampleRate: Int64
    public let sampleSize: Int64
    public let echoCancellation: Bool
    public let autoGainControl: Bool
    public let noiseSuppression: Bool
    public let latency: Float64
    public let channelCount: Int64
    public let deviceId: CString
    public let groupId: CString
    public let ohosScreenCaptureMode: CString
    public let ohosScreenCaptureDisplayId: Int64
    public let ohosScreenCaptureMissionId: CString
    public let ohosScreenCaptureWindowFilter: CString
    public let ohosScreenCaptureAudioFilter: CString
    public let ohosScreenCaptureSkipPrivacyMode: CString
    public let ohosScreenCaptureAutoRotation: Bool

    public init(width!: Int64 = 0, height!: Int64 = 0, aspectRatio!: Float64 = 0.0, frameRate!: Float64 = 0.0,
        facingMode!: String = "",
        resizeMode!: String = "",
        sampleRate!: Int64 = 0,
        sampleSize!: Int64 = 0,
        echoCancellation!: Bool = false,
        autoGainControl!: Bool = false,
        noiseSuppression!: Bool = false,
        latency!: Float64 = 0.0,
        channelCount!: Int64 = 0,
        deviceId!: String = "",
        groupId!: String = "",
        ohosScreenCaptureMode!: String = "",
        ohosScreenCaptureDisplayId!: Int64 = 0,
        ohosScreenCaptureMissionId!: String = "",
        ohosScreenCaptureWindowFilter!: String = "",
        ohosScreenCaptureAudioFilter!: String = "",
        ohosScreenCaptureSkipPrivacyMode!: String = "",
        ohosScreenCaptureAutoRotation!: Bool = false) {
        this.width = width
        this.height = height
        this.aspectRatio = aspectRatio
        this.frameRate = frameRate
        this.facingMode = unsafe {LibC.mallocCString(facingMode)}
        this.resizeMode = unsafe {LibC.mallocCString(resizeMode)}
        this.sampleRate = sampleRate
        this.sampleSize = sampleSize
        this.echoCancellation = echoCancellation
        this.autoGainControl = autoGainControl
        this.noiseSuppression = noiseSuppression
        this.latency = latency
        this.channelCount = channelCount
        this.deviceId = unsafe {LibC.mallocCString(deviceId)}
        this.groupId = unsafe {LibC.mallocCString(groupId)}
        this.ohosScreenCaptureMode = unsafe {LibC.mallocCString(ohosScreenCaptureMode)}
        this.ohosScreenCaptureDisplayId = ohosScreenCaptureDisplayId
        this.ohosScreenCaptureMissionId = unsafe {LibC.mallocCString(ohosScreenCaptureMissionId)}
        this.ohosScreenCaptureWindowFilter = unsafe {LibC.mallocCString(ohosScreenCaptureWindowFilter)}
        this.ohosScreenCaptureAudioFilter = unsafe {LibC.mallocCString(ohosScreenCaptureAudioFilter)}
        this.ohosScreenCaptureSkipPrivacyMode = unsafe {LibC.mallocCString(ohosScreenCaptureSkipPrivacyMode)}
        this.ohosScreenCaptureAutoRotation = ohosScreenCaptureAutoRotation
    }
}

@C // see ffi_define_struct.h
public struct CJ_SupportedConstraints {
    public let name: CString = unsafe {zeroValue<CString>()}
    public let isSupported: Bool = false
}

@C
public struct CJ_TO_CPP_DisplayMediaStreamOptions {
    let obj: CJ_MediaTrackConstraintSet
    let boolean: Bool
    let isBool: Bool
    public init(mtc: CJ_MediaTrackConstraintSet) {
        this.obj = mtc
        this.boolean = false
        this.isBool = false
    }
    public init(boolean: Bool) {
        this.obj = unsafe {zeroValue<CJ_MediaTrackConstraintSet>()}
        this.boolean = boolean
        this.isBool = true
    }
    public init() {
        this.obj = unsafe {zeroValue<CJ_MediaTrackConstraintSet>()}
        this.boolean = true
        this.isBool = true
    }
}

public class MediaTrackConstraints {
    var length: Int64 = 0
    var advanced: CPointer<CJ_MediaTrackConstraintSet> = unsafe {zeroValue<CPointer<CJ_MediaTrackConstraintSet>>()}
    public init(advanced: Array<CJ_MediaTrackConstraintSet>) {
        let arr = LibC.malloc<CJ_MediaTrackConstraintSet>(count: advanced.size)
        unsafe {
            for (i in 0..advanced.size) {
                arr.write(i, advanced[i])
            }
        }
        this.advanced = arr
        this.length = Int64(advanced.size)
    }
}



