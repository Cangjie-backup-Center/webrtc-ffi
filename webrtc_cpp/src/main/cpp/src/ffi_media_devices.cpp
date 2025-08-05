#include "ffi_media_devices.h"

/*
    class MediaDevices  {
        public:
            explicit MediaDevices();
            int64_t** EnumerateDevices(); // return MediaDeviceInfo[]
            int64_t* GetSupportedConstraints(); // return MediaTrackSupportedConstraints*
            int64_t* GetUserMedia(int64_t* constraints); // return MediaStream*
            int64_t* GetDisplayMedia(int64_t* options);// return MediaStream*
        private:
    };
*/

using namespace webrtc;


int64_t** MediaDevices::enumerateDevices() {
    
} 


void MediaDevices::getUserMedia(int64_t constraints) {
//        audioConstraints_ = std::move(audio);
//    videoConstraints_ = std::move(video);
    
}


void MediaDevices::getDisplayMedia(FFI_videoGetDisplayMedia video, bool audio, bool systemAudio, int64_t that,  
                                            void (*pe)(int64_t that, int64_t localVideoTrack)){
// TODO 
    /*
    MediaTrackConstraints audioConstraints_;
    MediaTrackConstraints systemAudioConstraints_;
    MediaTrackConstraints videoConstraints_;
    */
//    if (video) {
//    if (audio) {
//    if (systemAudio) {
    that_ = that;
    post_event_ = pe;
    Cangjie_CallBack(this,
                     [](uv_work_t *work) {
        MediaDevices* that = static_cast<MediaDevices *>(work->data);
        that->ffiMediaStream_ = new FFIMediaStream(that->factory_, that->stream_);
        that->post_event_((int64_t)that, (int64_t)that->ffiMediaStream_);
    }, [](uv_work_t *work, int status) {});
    return;
}