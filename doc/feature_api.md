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

### 1.5 webrtc 提供 全局函数

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

    
            
```