# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(webrtc4cj)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

# 头文件
include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/../includes
                    )


# 生成的动态库 so文件
add_library(webrtc_cpp SHARED
                        napi_init.cpp

                        )

# so 文件 链接的so
target_link_libraries(webrtc_cpp PUBLIC
                                ${CMAKE_CURRENT_SOURCE_DIR}/libohos_webrtc.so # 除 ohos_webrtc arkts代码的 集合
                                libhilog_ndk.z.so
                                libohaudio.so
                                libohcamera.so
                                libohimage.so
                                libimage_receiver.so
                                libnative_buffer.so
                                libnative_window.so
                                libnative_image.so
                                libEGL.so
                                libGLESv3.so
                                libnative_media_codecbase.so
                                libnative_media_core.so
                                libnative_media_venc.so
                                libnative_media_vdec.so
                                libnative_avscreen_capture.so
                                libnative_drawing.so
                                libnative_display_manager.so
                                )
