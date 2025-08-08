# webrtc4cj特性转测文档

## 1 主要接口

### 1.1 webrtc 提供 VideoRenderController

```cangjie

public class VideoRenderController <: XComponentController {
    /*
     * 构造函数, 创建新的VideoRenderController
     */
    public init()

    /*
     * 创建视频渲染器
     * 返回值 Unit - Unit
     */
    public func newNativeVideoRenderer(): Unit

    /*
     * 设置视频轨
     * 
     * 参数 VideoTrack - 传入ID赋值成功的VideoTrack类
     * 返回值 Unit - Unit
     */
    public func setVideoTrack(mst : VideoTrack): Unit

    /*
     * 设置是否是镜像模式
     *
     * 参数 Bool - 是否是镜像模式
     * 返回值 Unit - Unit
     */
    public func setMirror(mirrorVerticallyBool: Bool): Unit

    /*
     * 视频填充模式选择
     *
     * 参数 Int32 - 传入结构体ScalingMode中元素用以视频显示的设置
     * 返回值 Unit - Unit
     */
    public func setScalingMode(scalingMode : Int32): Unit

}
    
```

### 1.2 webrtc 提供 ffiCreateVideoSourceParameters
```cangjie

struct ffiCreateVideoSourceParameters{
    var width : Float64 = 0.00   // 宽度
    var height : Float64 = 0.00  // 高度
    var facingMode : CString = unsafe{LibC.mallocCString("")}  // 表示媒体轨道是否支持摄像头朝向模式约束条件，user为前置摄像头，非user为后置摄像头
    var isScreencast : Bool = false;   // 是否是屏幕录像，true：使用屏幕录像作为视频源（当前仅支持 width、height约束条件，且不支持 advanced 属性）；false：使用相机作为视频源（当前支持 width、height、aspectRatio、framRate、facingMode、deviceId约束条件）。
}
```

### 1.3 webrtc 提供 ffiAudioOptions
```cangjie
struct ffiAudioOptions{
    var echo_cancellation : Bool = false   // 表示媒体轨道是否支持回声消除约束条件
    var noise_suppression : Bool = false   // 表示媒体轨道是否支持噪音抑制约束条件
}

```

### 1.4  webrtc 提供 ScalingMode

``` cangjie
/*
* 该结构体中参数值已初始化，根据需要传值即可，不必再自行赋值
*/
public struct ScalingMode {
    public let fill: Int32 = 0 // 视频显示填充
    public let aspectFill: Int32 = 1 // 视频拉伸填充
    public let aspectFit: Int32 = 2 // 视频自适应
}
```

### 1.5 webrtc 提供 CJ_MediaTrackConstraintSet和CJ_TO_CPP_DisplayMediaStreamOptions

```cangjie
// 该结构体中保存有桌面共享时video的各项参数，结构体不单独使用而是搭配CJ_TO_CPP_DisplayMediaStreamOptions使用

public struct CJ_MediaTrackConstraintSet{
    public var width: Float64
    public var height: Float64
    public var aspectRatio: Float64
    public var frameRate: Float64
    public var facingMode: CString
    public var resizeMode: CString
    public var sampleRate: Int64
    public var sampleSize: Int64
    public var echoCancellation: Bool
    public var autoGainControl: Bool
    public var noiseSuppression: Bool
    public var latency: Float64
    public var channelCount: Int64
    public var deviceId: CString
    public var groupId: CString
    public var ohosScreenCaptureMode: CString
    public var ohosScreenCaptureDisplayId: Int64
    public var ohosScreenCaptureMissionId: CString
    public var ohosScreenCaptureWindowFilter: CString
    public var ohosScreenCaptureAudioFilter: CString
    public var ohosScreenCaptureSkipPrivacyMode: CString
    public var ohosScreenCaptureAutoRotation: Bool

    public init(width!: Float64 = 0.0, height!: Float64 = 0.0, aspectRatio!: Float64 = 0.0, frameRate!: Float64 = 0.0,
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
```

```cangjie
// 根据自己需要构建CJ_MediaTrackConstraintSet
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
```



### 1.6 webrtc 提供 全局函数

```cangjie
	/*
     * 创建新音频设备模块
     *
     * 参数 Bool - 是否使用立体声输入
     * 参数 Bool - 是否使用立体声输出
     * 返回值 Int64 - 新硬件视频编码器id
     */
    public func cj_newAudioDeviceModule(useStereoInput : Bool, useStereoOutput : Bool) : Unit


    /*
     * 创建新对等连接工厂
     *
     * 参数 Int64 - 音频设备模块id
     * 参数 Int64 - 传入cj_newAudioDeviceModule的返回值(硬件视频编码器工厂id)
     * 参数 Int64 - 传入cj_newHardwareVideoDecoderFactory的返回值(硬件视频解码器工厂id)
     * 返回值 Int64 - 对等连接工厂id
     */
    public func cj_newPeerConnectionFactory(cjADM_int64 : Int64, cjHVEF_int64 : Int64 , cjHVDF_int64 : Int64) : Int64 
     
     /*
     * 创建音频源
	 *
     * 参数 pcf:PeerConnectionFactory - 传入连接工厂
     * 参数 options:ffiAudioOptions - 音频配置选项
     */
     public class AudioSource <: webrtcClass {
    	public func createAudioSourceID(pcf: PeerConnectionFactory, options: ffiAudioOptions) 
     }
     
    /*
     * 创建音轨
     *
     * 参数 pcf:PeerConnectionFactory - 传入连接工厂
	 * 参数 tag:CString - 音轨标签(自定)
     */
     public class VideoTrack <: webrtcClass {
        public func createVideoTrackID(pcf: PeerConnectionFactory, tag: CString) 
     }
            
    /*
     * 创建视频源
     *
     * 参数 pcf: PeerConnectionFactory - 传入连接工厂
     * 参数 ffiCVSP: ffiCreateVideoSourceParameters - 视频配置
     */
    public class VideoSource <: webrtcClass {
    	public func createVideoSourceID(pcf: PeerConnectionFactory, ffiCVSP: ffiCreateVideoSourceParameters) 
    }
 
    /*
     * 创建视频轨道
     *
     * 参数 pcf: PeerConnectionFactory - 传入连接工厂
     * 参数 tag: CString - 视频源标签
     */
    public class VideoTrack <: webrtcClass {
    	public func createVideoTrackID(pcf: PeerConnectionFactory, tag: CString)
    }
    
    /*
     * 创建新硬件视频编码器厂
     * 
     * 返回值 Int64 - 新硬件视频编码器id
     */
    public func cj_newHardwareVideoEncoderFactory() : Int64

    /*
     * 创建硬件视频解码器工厂
     * 
     * 返回值 Int64 - 硬件视频解码器id
     */
    public func cj_newHardwareVideoDecoderFactory() : Int64


	/*
	* MediaDevices类用以管理共享屏幕功能
	* getDisplayMedia 用以传入共享屏幕所需要的参数
	*/
	public class MediaDevices <: WebrtcClass {
    private let randomid = WebRtcGlobal.getCurrentId()
    var call: Option<(mediaStream: MediaStream) -> Unit> = None
    public init() {
        this.ID = cj_webrtc_mediaDevices_create()
        WebRtcGlobal.map.add(this.randomid, this)
    }

    public func getDisplayMedia(video: CJ_TO_CPP_DisplayMediaStreamOptions,
                                audio:CJ_TO_CPP_DisplayMediaStreamOptions,
                                systemAudio:CJ_TO_CPP_DisplayMediaStreamOptions, callback: (mediaStream: MediaStream) -> Unit): Unit {
        this.call = callback
        let f : CFunc<(that: Int64, localVideoTrack: Int64) -> Unit> = {id: Int64, localVideoTrack: Int64 =>
            let that: MediaDevices =  WebRtcGlobal.map.get(id) ?? return
            let track = MediaStream(localVideoTrack)
            if (let Some(v) <- that.call) {
                v(track)
            }
        }
        cj_webrtc_mediaDevices_getDisplayMedia(this.ID, video, audio,systemAudio, this.randomid, f)
    }
}
    
    /*
    * MediaStream 用以管理共享屏幕功能返回的音、频流
    * getAudioTracks 获取音频流
    * getVideoTracks 获取视频流
    */
    
    public class MediaStream <: WebrtcClass {
    public init(id: Int64) {
    	this.ID = id
    }

    public func getAudioTracks(): Array<MediaStreamTrack> {
        return cj_getAudioTracks(this.ID)
    }

    public func getVideoTracks(): Array<MediaStreamTrack> {
        return cj_getVideoTracks(this.ID)
    }

}
    
            
```