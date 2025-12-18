/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */
package webrtc_cj

import std.collection.concurrent.ConcurrentHashMap
import std.collection.concurrent.BlockingQueue
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

func DelObject(id: Int64): Bool {
    WebRtcGlobal.map.remove(id).isSome()
}

public class ExecutorService {
    var thread = Option<Future<Unit>>.None
    let isShutdown = AtomicBool(false)
    let TASK = BlockingQueue<Option<() -> Unit>>()

    private init() {}
    public static func new(): ExecutorService {
        let service = ExecutorService()
        service.reset()
        return service
    }

    func reset() {
        thread = spawn {
            while (true) {
                if (let Some(fn) <- this.TASK.dequeue()) {
                    spawn {fn()}
                } else {
                    break
                }
            }
        }
    }

    public func execute(fn: () -> Unit): Unit {
        this.TASK.enqueue(fn)
    }

    public func shutdown(self!: Bool = false) {
        isShutdown.store(true)
        this.TASK.enqueue(Option<() -> Unit>.None)
        if (self) {
            return
        }
        if (let Some(v) <- this.thread) {
            v.cancel()
            v.get() // Wait for the thread to finish
        }
    }
}

