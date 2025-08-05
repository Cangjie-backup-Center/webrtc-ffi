/**
 * Created on 2025/7/19
 */
package webrtc_cj

//
//foreign {
//
//}



foreign  func GetVideoTracks(): CPointer<Int64>


public class MediaStreamTrack {
    private var ptr: Int64

    public init(ptr: Int64) {
        this.ptr = ptr
    }

    public func toJson(): String {
        // TODO
        ""
    }

}


func cangjieGetVideoTracks(): Array<MediaStreamTrack> {
    unsafe {
        let arr = GetVideoTracks()
        let list = ArrayList<MediaStreamTrack> ()
        for (item in arr) {
            list.add(GetVideoTracks(item))
        }
        return list.toArray()
    }
}
