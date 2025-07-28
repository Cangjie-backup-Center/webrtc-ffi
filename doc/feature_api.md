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
     * 在首次创建surface后调用。
     * 
     * 参数 String - 需要传入XComponent创建的surfaceId。
     * 返回值 Unit - Unit
     */
    protected override func onSurfaceCreated(surfaceId: String): Unit

    /*
     * 在surface信息更改后调用。
     * 
     * 参数 String - 需要传入XComponent创建的surfaceId。
     * 参数 SurfaceRect - XComponent创建的曲面的矩形信息。
     * 返回值 Unit - Unit
     */  
    protected override func onSurfaceChanged(surfaceId: String, rect: SurfaceRect): Unit

    /*
     * 创建新的原生视频渲染器
     * 
     * 参数 Int64 - 需要传入XComponent创建的surfaceId。
     * 返回值 Int64 - 返回nativevideoRenderer的组件ID
     */
    public func newNativeVideoRenderer(surfaceId : Int64): Int64

    /*
     * 设置视频轨道
     * 
     * 参数 Int64 - 需要传入nativevideoRenderer的组件ID
     * 返回值 Unit - Unit
     */
    public func setVideoTrack(ffiNVR : Int64): Unit

    /*
     * 设置是否是镜像模式
     * 
     * 参数 Int64 - 需要传入nativevideoRenderer的组件ID
     * 参数 Bool - 是否是镜像模式
     * 返回值 Unit - Unit
     */
    public func setMirror(ffiNVR : Int64, mirrorVerticallyBool: Bool): Unit

    /*
     * 设置缩放模式
     * 
     * 参数 Int64 - 需要传入nativevideoRenderer的组件ID
     * 参数 Int64 - 缩放倍数
     * 返回值 Unit - Unit
     */
    public func setScalingMode(ffiNVR : Int64, scalingMode : Int64) : Unit

    /*
     * 当Surface即将被破坏时调用。
     * 
     * 参数 String - 需要传入XComponent创建的surfaceId。
     * 返回值 Unit - Unit
     */
    protected override func onSurfaceDestroyed(surfaceId: String): Unit
}
    
```

### 1.2 webrtc 提供 ffiCreateVideoSourceParameters
```cangjie

struct ffiCreateVideoSourceParameters{
    var width : Float64 = 0.00   // 宽度
    var height : Float64 = 0.00  // 高度
    var facingMode : CString = unsafe{LibC.mallocCString("")}  // 表示媒体轨道是否支持摄像头朝向模式约束条件
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

### 1.4 webrtc 提供 全局函数

```cangjie

    /*
     * 创建音频源
     * 
     * 参数 Int64 - 传入cj_newPeerConnectionFactory的返回值对等连接工厂id
     * 参数 ffiAudioOptions - 音频配置选项
     * 返回值 Int64 - 音频源id
     */
    public func cj_createAudioSource(cjPCF_int64 : Int64, cjao : ffiAudioOptions) : Int64
 
    /*
     * 创建音轨
     *
     * 参数 Int64 - 传入cj_newPeerConnectionFactory的返回值对等连接工厂id
     * 参数 Int64 - 音频源id
     * 返回值 Int64 - 音轨id
     */
    public func cj_createAudioTrack(cjPCF_int64 : Int64, cj_audioId : CString) : Int64
            
    /*
     * 创建视频源
     *
     * 参数 Int64 - 传入cj_newPeerConnectionFactory的返回值对等连接工厂id
     * 参数 ffiCreateVideoSourceParameters - 视频配置选项
     * 返回值 Int64 - 视频源id
     */
    public func cj_createVideoSource(cjPCF_int64 : Int64, cjCVSP : ffiCreateVideoSourceParameters) : Int64
 
    /*
     * 创建视频轨道
     *
     * 参数 Int64 - 传入cj_newPeerConnectionFactory的返回值对等连接工厂id
     * 参数 CString - 视频源id
     * 返回值 Int64 - 视频轨道id
     */
    public func cj_createVideoTrack(cjPCF_int64 : Int64, cj_videoId : CString) : Int64
            
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
     * 创建新音频设备模块
     * 参数 Bool - 是否使用立体声输入
     * 参数 Bool - 是否使用立体声输出
     * 返回值 Int64 - 新硬件视频编码器id
     */
    public func cj_newAudioDeviceModule(useStereoInput : Bool, useStereoOutput : Bool) : Unit


    /*
     * 创建新对等连接工厂
     * 参数 Int64 - 音频设备模块id
     * 参数 Int64 - 传入cj_newAudioDeviceModule的返回值(硬件视频编码器工厂id)
     * 参数 Int64 - 传入cj_newHardwareVideoDecoderFactory的返回值(硬件视频解码器工厂id)
     * 返回值 Int64 - 对等连接工厂id
     */
    public func cj_newPeerConnectionFactory(cjADM_int64 : Int64, cjHVEF_int64 : Int64 , cjHVDF_int64 : Int64) : Int64 
```