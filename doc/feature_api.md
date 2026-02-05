# webrtc4cj特性文档

## 1 主要接口

### 1.1 webrtc 提供 VideoRenderController

```cangjie

public class VideoRenderController <: XComponentController {
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
     * 参数 scalingMode - 传入枚举FFIScalingModeEnum
     * 返回值 Unit - Unit
     */
    public func setScalingMode(scalingMode : FFIScalingModeEnum): Unit

}
    
```

### 1.2  webrtc 提供 FFIScalingModeEnum

``` cangjie
/*
* 该枚举为视频显示参数
*/
public enum FFIScalingModeEnum {
	// 分别为：视频显示填充 视频拉伸填充 视频自适应
    FILL | ASPECTFILL | ASPECTFIT
}
```

### 1.3 webrtc 提供 CJ_MediaTrackConstraintSet和CJ_TO_CPP_DisplayMediaStreamOptions

```cangjie
// 该结构体中保存有桌面共享时video的各项参数，结构体不单独使用而是搭配CJ_TO_CPP_DisplayMediaStreamOptions使用

public struct CJ_MediaTrackConstraintSet{
    /*
    * 参数 width - 视频宽度（像素）
    * 参数 height - 视频高度（像素）
    * 参数 aspectRatio - 宽高比
    * 参数 frameRate	- 帧率（fps）
    * 参数 facingMode - 摄像头朝向（如 "user" 前置/"environment" 后置）
    * 参数 resizeMode - 视频尺寸调整模式
    * 参数 sampleRate - 音频采样率（Hz）	    
    * 参数 sampleSize - 音频采样位数（如 16 位）
    * 参数 echoCancellation 	- 是否启用回声消除
    * 参数 autoGainControl - 是否启用自动增益控制
    * 参数 noiseSuppression - 是否启用噪声抑制
    * 参数 latency - 音频延迟（秒）
    * 参数 channelCount 	- 声道数（如 1 单声道/2 立体声）
    * 参数 deviceId	- 媒体设备 ID（用于指定特定摄像头/麦克风）
    * 参数 groupId - 设备组 ID（用于关联同一物理设备的多个媒体轨道）
    * 参数 ohosScreenCaptureMode - 指定屏幕捕获模式，如：窗口捕获、区域捕获或全屏捕获等可选值：'home-screen'，'specified-screen'，'specified-window'，默认为 'home-screen'
    * 参数 ohosScreenCaptureDisplayId - 指定要捕获的显示设备 ID（多显示器场景下使用），当 ohosScreenCaptureMode 为 'specified-screen' 时有效
    * 参数 ohosScreenCaptureMissionId - 指定要捕获的应用程序任务 ID，当 ohosScreenCaptureMode 为 'specified-window' 时有效
    * 参数 ohosScreenCaptureWindowFilter - 窗口过滤条件
    * 参数 ohosScreenCaptureAudioFilter - 音频过滤条件，可选值：'current-app'，'notification'
    * 参数 ohosScreenCaptureSkipPrivacyMode - 是否跳过隐私模式（控制敏感内容显示）
    * 参数 ohosScreenCaptureAutoRotation - 是否启用自动旋转适配
    * 返回值 - CJ_MediaTrackConstraintSet 实例
    */
    
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
        ohosScreenCaptureAutoRotation!: Bool = false) 
}
```

### 1.5 webrtc 提供重要功能类

```cangjie
	/*
     * 音频设备管理模块
     *
     */
    public class AudioDeviceModule <: WebrtcClass {
    	/*
         * 创建音频设备模块
         *
         * 参数 admOption - admOptions包含音频构建的初始化参数
         * 返回值 - AudioDeviceModule实例
         */
    	public init(admOption: admOptions)
	}
	
	/*
     * 构建音频设备管理模块初始化参数
     *
     */
	public struct admOptions {
		/*
		* 参数 input - 音频输入参数
		* 参数 output - 音频输出参数
		* 参数 audioSampleFormat - 音频采样格式
		* 参数 useStereoInput - 是否使用立体声输入，默认为false，即单声道
		* 参数 useStereoOutput - 是否使用立体声输出，默认为false，即单声道
		*/

        public init(
            input!: inputOptions = inputOptions(),
            output!: outputOptions = outputOptions(),
            audioSampleFormat!: AudioSampleFormat = AudioSampleFormat.SAMPLE_FORMAT_S16LE,
            useStereoInput!: Bool = false,
            useStereoOutput!: Bool = false
        )
	}

	/*
     * 构建音频设备管理模块初始化音频输入参数
     *
     */
	public struct inputOptions {
	/*
	* 参数 Source - 音频输入参数，参见ohos.multimedia.audio.cj.SourceType，默认为 SOURCE_TYPE_VOICE_COMMUNICATION
	* 参数 SampleRate - 音频输入格式
    * 参数 UseLowLatency - 控制是否使用低延迟输入输出，默认为 false
    */
	
    public var Source : SourceType
    public var SampleRate : Int32
    public var UseLowLatency : Bool
    public init(Source!: SourceType = SourceType.SOURCE_TYPE_VOICE_COMMUNICATION,
        SampleRate!: Int32 = 48000,
        UseLowLatency!: Bool = false
        ) {
    	this.Source = Source
        this.SampleRate = SampleRate
        this.UseLowLatency = UseLowLatency
    	}
	}
	
	/*
     * 构建音频设备管理模块初始化音频输出参数
     *
     */
     public struct outputOptions {
     /*
	* 参数 Usage - 音频输出参数，参见ohos.multimedia.audio.cj.StreamUsage, 默认为 STREAM_USAGE_VOICE_COMMUNICATION
	* 参数 SampleRate - 音频输出格式
    * 参数 UseLowLatency - 控制是否使用低延迟输入输出，默认为 false
    */
    
    public init(Usage!: StreamUsage = StreamUsage.STREAM_USAGE_VOICE_COMMUNICATION,
            SampleRate!: Int32 = 48000,
            UseLowLatency!: Bool = false
            ) {
            this.Usage = Usage
            this.SampleRate = SampleRate
            this.UseLowLatency = UseLowLatency
        }
    }

    public class PeerConnectionFactory <: WebrtcClass {
    	/*
         * 创建对等连接工厂
         *
         * 参数 AudioDeviceModule - 传入AudioDeviceModule的初始化(硬件视频编码器工厂id)
         * 参数 videoMode - 选择使用硬解/软解
         * 返回值 - PeerConnectionFactory实例
         */
        public init(adm: AudioDeviceModule, videoMode: VideoEncoderAndDecoderMode) 
        
        /*
         * 创建连接管理实例
         *
         * 参数 config - RTCConfiguration类
         * 返回值 - RTCPeerConnection实例
         */
        public func createPeerConnection(config: RTCConfiguration): RTCPeerConnection

		/*
         * 创建音频源
         *
         * 参数 audioOptions - CJ_MediaTrackConstraintSet只需要修改echoCancellation、autoGainControl、noiseSuppression以控制音频
         * 返回值 - AudioSource实例
         */
    	public func createAudioSource(audioOptions: CJ_MediaTrackConstraintSet): AudioSource 
    
    	/*
         * 创建音频轨
         *
         * 参数 id - 实例标签
         * 参数 source - AudioSource
         * 返回值 - AudioTrack实例
         */
    	public func createAudioTrack(id: String, source: AudioSource): AudioTrack
    
    	/*
         * 创建音频源
         *
         * 参数 ffiCVSP - CJ_MediaTrackConstraintSet类
         * 参数 isScreen - 屏幕捕获器是否开启
         * 返回值 - VideoSource实例
         */
    	public func createVideoSource(ffiCVSP: CJ_MediaTrackConstraintSet, isScreen: Bool): VideoSource
    	
    	/*
         * 创建音频轨
         *
         * 参数 id - 实例标签
         * 参数 source - 音频源
         * 返回值 - VideoTrack实例
         */
    	public func createVideoTrack(id: String, source: VideoSource): VideoTrack
	}
     
     /*
     * 音频源管理类
     *
     */
     public class AudioSource <: webrtcClass {
        /*
         * 创建音频源
         *
         * 参数 pcf - 传入连接工厂
         * 参数 audioOptions - 音频配置选项
         */
    	 public init(pcf: PeerConnectionFactory, audioOptions: CJ_MediaTrackConstraintSet)
     }
     
    /*
     * 音轨管理类
     *
     */
     public class AudioTrack <: MediaStreamTrack {
         /*
         * 创建音轨
         *
         * 参数 pcf - 传入连接工厂
         * 参数 tag - 音轨标签
         * 参数 ffiVideoSource - 音频源
         * 返回值 - AudioTrack实例
         */
        public init(pcf: PeerConnectionFactory, tag: String, ffiVideoSource: VideoSource) 
	}
	
    /*
     * 视频源管理类
     *
     */
    public class VideoSource <: webrtcClass {
     /*
      * 创建视频源
      *
      * 参数 pcf - 传入连接工厂
      * 参数 ffiCVSP - 视频配置
      * 参数 isScreen - true:创建屏幕捕获器;false:创建摄像头捕获器
      */
		public init(pcf: PeerConnectionFactory, ffiCVSP: CJ_MediaTrackConstraintSet, isScreen: Bool)
    }
 
    /*
     * 视频轨管理类
     *
     */
    public class VideoTrack <: MediaStreamTrack {
    	/*
         * 创建视频轨id
         * 参数 pcf - 传入连接工厂
     	 * 参数 tag - 视频源标签 
         * 返回值 - VideoTrack实例
         */
        public init(pcf: PeerConnectionFactory, tag: String) 
        
	}
    
	/*
	* MediaDevices类用以管理共享屏幕功能
	*/
	public class MediaDevices <: WebrtcClass {
		public init()

		/*
		* 用以传入共享屏幕所需要的参数
		*
		* 参数 video - 视频控制参数
		* 参数 audio - 麦克风音频开/关
		* 参数 systemAudio - 系统音频开/关
		* 返回值 MediaStream - 返回MediaStream（管理共享屏幕功能返回的音、频流）
		*/
    	public func getDisplayMedia(video: CJ_MediaTrackConstraintSet,
                                    audio: Bool,
                                    systemAudio: Bool): MediaStream
	}
    
    /*
    * MediaStream 用以管理共享屏幕功能返回的音、频流
    */
    public class MediaStream <: WebrtcClass {
    	/*
    	* 有MediaStream实例时，可以传入MediaStream的成员ID
    	*
    	* 参数 id - 成员变量id
    	* 返回值 - 返回MediaStream实例
    	*/
    	public init(id: Int64)
    	
    	/*
    	* 无MediaStream实例时，默认id为-1
    	*
		* 返回值 - 返回MediaStream实例
    	*/
    	public init() 

		/*
		* 获取音频流
		*
		* 返回值 - 返回MediaStreamTrack数组
		*/
        public func getAudioTracks(): Array<MediaStreamTrack> 
        
        /*
		* 获取视频流
		*
		* 返回值 - 返回MediaStreamTrack数组
		*/
        public func getVideoTracks(): Array<MediaStreamTrack> 
	}
    
  public class RTCPeerConnection <: WebrtcClass{
  		/*
  		* 控制接收音频流的播放状态。默认情况下处于启用状态。即使启用了播放功能，只有当应用了相应的 SDP 时，		 * 流才会被播放出来。将“playout”设置为“false”将停止底层音频设备的播放，但会启动一个任务，该任务每 		   * 10 毫秒就会检查音频数据一次，以确保音频处理得以进行并更新音频统计数据。
  		* 
  		* 参数 playout - 控制是否开启音频
  		*/
  		public func setAudioPlayout(playout: Bool): Unit
  		
  		/*
  		* 控制传输音频流的录制功能。默认情况下该功能处于开启状态。即便录制功能已开启，只有在应用了相应的 			* SDP 文件的情况下，音频流才会被录制。
  		*
  		* 参数 recording - 控制是否开启音频录制
  		*/
  		public func setAudioRecording(recording: Bool): Unit
  		
  		/*
  		* 关闭连接
  		*
  		*/
  		public func close(): Unit
  		
  		/*
  		* 生成SDP offer
  		*
  		* 参数 iceRestart - 控制是否控制是否重新启动ICE，默认为false
  		* 
  		* 返回值 WebrtcResult<RTCSessionDescription> - 获取返回值为OK还是ERROR
  		*/
  		public func createOffer(iceRestart!: Bool = false): WebrtcResult<RTCSessionDescription>
  		
  		/*
  		* 播放对端传来的音视频信息
  		*
  		* 参数 pc - RTCPeerConnection类实例
        * 参数 dc - 接收回调的事件
  		*/
  		public mut prop onTrack: ((pc: RTCPeerConnection, dc: RTCTrackEvent) -> Unit)
  		
  		/*
  		* 
  		*
  		* 参数 pc - RTCPeerConnection类实例
  		* 参数 dc - 接收回调的事件
  		*/
  		public mut prop onSignalingChange: ((pc: RTCPeerConnection, dc: Event) -> Unit)
  	
    	/*
  		* 连接状态捕获，连接断开则关闭
  		*
  		* 参数 pc - RTCPeerConnection类实例
  		* 参数 dc - 接收回调的事件
  		*/
  		public mut prop onconnectionstatechange: ((pc: RTCPeerConnection, dc: Event) -> Unit)
  		
  		/*
  		* 向发送数据信息
  		*
  		* 参数 pc - RTCPeerConnection类实例
  		* 参数 dc - 接收回调的事件
  		*/
  		public mut prop onIceCandidate: ((pc: RTCPeerConnection, dc: RTCPeerConnectionIceEvent) -> Unit)
  		
  		/*
  		* 监控 WebRTC 连接中 ICE 候选地址收集过程的状态变化，并在状态改变时执行相应的打印
  		*
  		* 参数 pc - RTCPeerConnection类实例
  		* 参数 dc - 接收回调的事件
  		*/
  		 public mut prop onicegatheringstatechange: ((pc: RTCPeerConnection, dc: Event) -> Unit)
  		 
  		 /*
  		 * WebRTC 连接中接收由远程对等方发起创建的数据通道，并为该通道注册必要的事件监听器以便后续通信
  		 *
  		 * 参数 pc - RTCPeerConnection类实例
  		 * 参数 dc - 接收回调的事件
  		 */
  		 public mut prop ondatachannel: ((pc: RTCPeerConnection, dc: RTCDataChannel) -> Unit)
  		 
  		 /*
  		 * WebRTC 双端通信中将本地采集的音视频信息添加到发送队列
  		 *
  		 * 参数 track - MediaStreamTrack类，用以传递音视频流
  		 * 参数 streamVec - 可选参数，CJ_ArrayMediaStream结构体
  		 */
  		 public func addTrack(track: MediaStreamTrack, streamVec!: CJ_ArrayMediaStream = CJ_ArrayMediaStream()): Int64
  		 
  		 /*
  		 * 在当前的 WebRTC 连接中创建一个名为"send"的数据通道，用于实现与远程对等方之间的任意数据传输。
  		 *
  		 * 参数 label - 用来为数据通道命名
  		 * 参数 dataChannelDict - 可缺省参数
  		 *
  		 * 返回值 RTCDataChannel - 返回创建成功的数据通道实例
  		 */
  		 public func createDataChannel(label: String, dataChannelDict!: CJ_RTCDataChannelInit = CJ_RTCDataChannelInit()): RTCDataChannel
  }
  
  public class RTCDataChannel <: WebrtcClass & Resource {
         /*
         * 在本地数据通道成功建立连接后，自动发送一些初始数据用于测试数据通道的功能
         *
         * 参数 pc - RTCDataChannel类
         * 参数 dc - 接收回调的事件
         */
		public mut prop onopen: ((pc: RTCDataChannel, dc: Event) -> Unit)
		
		/*
		* 发送一些初始数据测试数据通道
		* 
		* 参数 data - 可自定义发送的数据
		*/
		public func send(data: String): Unit 
		
		/*
		* 为本地创建的发送数据通道注册一个消息监听器，以便能够处理从远程对等方通过该通道发送过来的数据。
		*
		* 参数 pc - RTCDataChannel类
		*/
		public mut prop onmessage: ((pc: RTCDataChannel, dc: MessageEvent) -> Unit)
 }
            
```





 