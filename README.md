<div align="center">
<h1>webrtc4cj</h1>
</div>

<p align="center">
<img alt="" src="https://img.shields.io/badge/release-v0.0.1-brightgreen" style="display: inline-block;" />
<img alt="" src="https://img.shields.io/badge/build-pass-brightgreen" style="display: inline-block;" />
<img alt="" src="https://img.shields.io/badge/cjc-v0.0.1-brightgreen" style="display: inline-block;" />
<img alt="" src="https://img.shields.io/badge/cjcov-0%25-red" style="display: inline-block;" />
<img alt="" src="https://img.shields.io/badge/project-open-brightgreen" style="display: inline-block;" />
</p>

## 介绍

webrtc4cj 是一个基于仓颉版终端提供WebRTC的接口封装，并在C++层适配了视频的采集、渲染及编解码等模块。


### 特性

- 相机相关模块
- 视频编解码相关模块
- 日志接口适配
- 视频相关模块
- 音频模块


## 软件架构

### 源码目录

```shell
├─AppScope
├─doc                         // 接口文档
├─entry                       // UI模块 
├─webrtc                      // 核心代码模块      
└─hvigor                      // 构建工具目录

```


### 接口说明

主要类和函数接口说明详见 [API](./doc/feature_api.md)

## 使用说明

### 编译运行

    使用DevEco Studio搭配com.huawei.cangjie-support-plugin插件用于
    构建工程项目, 生成 hap 包.

### 功能示例

用例代码在entry目录下 [功能示例](./cangjie/index_webrtc.cj)

## 约束与限制
1. 在下述版本验证通过：

- DevEco Studio 5.1.0 Release
- Cangjie support Plugin: 5.1.0.828


## 开源协议

本项目基于 [Apache License 2.0](/LICENSE) ，请自由的享受和参与开源。

## 参与贡献

欢迎给我们提交 PR，欢迎给我们提交 issue，欢迎参与任何形式的贡献。