/**
 * Created on 2025/8/13
 */
package webrtc_cj

import std.collection.concurrent.ConcurrentHashMap
import std.sync.*


class WebRtcGlobal {

    public static let OBJECT_POOL: ConcurrentHashMap<Int64, WebrtcClass> = ConcurrentHashMap<Int64, WebrtcClass>()
    public static let map: ConcurrentHashMap<Int64, WebrtcClass> = ConcurrentHashMap<Int64, WebrtcClass>()
    public static var currentID: AtomicInt64 = AtomicInt64(0)

    public static func getCurrentId(): Int64 {
        return currentID.fetchAdd(1)
    }
}

func GetObject<T>(id: Int64): T  where T <: WebrtcClass {
    return ((WebRtcGlobal.map.get(id) ?? throw Webrtc4cjException("class not found")) as T) ?? throw Webrtc4cjException("class not found")
}


