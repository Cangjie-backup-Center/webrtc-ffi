# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(webrtc4cj)

set(CMAKE_CXX_STANDARD 17)  # 全局启用C++17
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 强制要求标准支持
set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-int-conversion -Wl,-Bsymbolic")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-int-conversion -Wl,-Bsymbolic")

set(CHECK_DIR "${NATIVERENDER_ROOT_PATH}/include")

if(EXISTS ${CHECK_DIR})
    message(STATUS "目录 ${CHECK_DIR} 存在")
else()
    message(STATUS "目录 ${CHECK_DIR} 不存在")
    file(ARCHIVE_EXTRACT
      INPUT "${NATIVERENDER_ROOT_PATH}/include.zip"
      DESTINATION "${NATIVERENDER_ROOT_PATH}/"
    )
endif()


file(SIZE "${NATIVERENDER_ROOT_PATH}/libwebrtc.a" FILE_SIZE)
if(${FILE_SIZE} GREATER 10485760)
    message("libwebrtc.a Exist")
else()
    message("libwebrtc.a unExist")
    file(ARCHIVE_EXTRACT
            INPUT "${NATIVERENDER_ROOT_PATH}/libwebrtc.zip"
            DESTINATION "${NATIVERENDER_ROOT_PATH}/"
    )
endif()

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

# 头文件
include_directories(
                    ${NATIVERENDER_ROOT_PATH}/include
                    ${NATIVERENDER_ROOT_PATH}/include/api
                    ${NATIVERENDER_ROOT_PATH}/include/rtc_base
                    ${NATIVERENDER_ROOT_PATH}/include/api/video_codecs
                    ${NATIVERENDER_ROOT_PATH}/include/api/video
                    ${NATIVERENDER_ROOT_PATH}/include/third_party/abseil-cpp
                    ${NATIVERENDER_ROOT_PATH}/include/third_party/libyuv/include
                    ${NATIVERENDER_ROOT_PATH}/include/third_party/googletest/src/googletest/include
                    ${NATIVERENDER_ROOT_PATH}/include/third_party/googletest/src/googletest/include
                    ${NATIVERENDER_ROOT_PATH}/include/third_party/googletest/src/googletest/include
                    ${NATIVERENDER_ROOT_PATH}/src
                    ${NATIVERENDER_ROOT_PATH}/node-addon-api

                    )



file(GLOB_RECURSE CPP_FILES ${NATIVERENDER_ROOT_PATH}/src/*.cpp)

# 生成的动态库 so文件
add_library(cj_webrtc SHARED
                        ${CPP_FILES}
                        )

target_compile_definitions(cj_webrtc
    PUBLIC  NODE_ADDON_API_DISABLE_DEPRECATED             # 对当前目标及依赖目标可见
    PUBLIC  NAPI_DISABLE_CPP_EXCEPTIONS             # 对当前目标及依赖目标可见
    PUBLIC  NDK_HELPER_DISABLE_CPP_EXCEPTIONS             # 对当前目标及依赖目标可见
    PUBLIC  NODE_ADDON_API_ENABLE_TYPE_CHECK_ON_AS             # 对当前目标及依赖目标可见
    PUBLIC  DLOG_ALWAYS_ON             # 对当前目标及依赖目标可见
    PUBLIC  DCHECK_ALWAYS_ON             # 对当前目标及依赖目标可见
    PUBLIC  WEBRTC_POSIX             # 对当前目标及依赖目标可见
    PUBLIC  WEBRTC_OHOS             # 对当前目标及依赖目标可见
    PUBLIC  WEBRTC_LINUX             # 对当前目标及依赖目标可见
    PUBLIC  OHOS             # 对当前目标及依赖目标可见
    PUBLIC  WEBRTC_ENABLE_AVX2             # 对当前目标及依赖目标可见
    PUBLIC  WEBRTC_NON_STATIC_TRACE_EVENT_HANDLERS=1             # 对当前目标及依赖目标可见
)

# so 文件 链接的so
target_compile_options(cj_webrtc PRIVATE -fno-rtti) # 若 WebRTC 禁用 RTTI，则项目中需同步禁用

target_link_libraries(cj_webrtc PRIVATE
                                libace_napi.z.so
                                libhilog_ndk.z.so
                                libohaudio.so
                                libohcamera.so
                                libohimage.so
                                libimage_receiver.so
                                libnative_buffer.so
                                libnative_window.so
                                libnative_image.so
                                libEGL.so
                                libuv.so
                                libGLESv3.so
                                libnative_media_codecbase.so
                                libnative_media_core.so
                                libnative_media_venc.so
                                libnative_media_vdec.so
                                libnative_avscreen_capture.so
                                libnative_drawing.so
                                libnative_display_manager.so
                                librt.so
                                ${CMAKE_CURRENT_SOURCE_DIR}/libwebrtc.a # 除 ohos_webrtc arkts代码的 集合
                                )
