<div align="center">
<h1>webrtc-ffi</h1>
</div>

<p align="center">
<img alt="" src="https://img.shields.io/badge/release-v1.0.0-brightgreen" style="display: inline-block;" />
<img alt="" src="https://img.shields.io/badge/build-pass-brightgreen" style="display: inline-block;" />
<img alt="" src="https://img.shields.io/badge/cjc-v1.0.3-brightgreen" style="display: inline-block;" />
<img alt="" src="https://img.shields.io/badge/cjcov-0%25-red" style="display: inline-block;" />
<img alt="" src="https://img.shields.io/badge/project-open-brightgreen" style="display: inline-block;" />
</p>

## 介绍

webrtc-ffi 是一个基于仓颉版终端提供WebRTC的接口封装，并在C++层适配了视频的采集、渲染及编解码等模块。


### 特性

实时音频、视频的采集与显示功能


## 软件架构

### 源码目录

```shell
├─AppScope
├─doc                           # 接口文档
├─entry                         # 示例代码文件夹 
├─webrtc_cj                     # 核心代码模块
│  └─src
│      └─main
│          ├─cangjie
│          │  └─src             # 框架仓颉代码目录
│          └─resources
├─webrtc_cpp
│  └─src
│      └─main
│          ├─cpp
│          │  └─src             # 底层C++代码目录
│          └─resources
└─hvigor                        # 构建工具目录

```

- `AppScope` 全局资源存放目录和应用全局信息配置目录
- `doc` API文档和使用手册存放目录
- `entry` 工程模块 - 编译生成一个HAP
- `entry src` APP代码目录
- `entry src main` APP项目目录
- `entry src main cangjie` 仓颉代码目录
- `entry src main resources` 资源文件目录
- `webrtc_cj` 工程模块 - 编译生成一个har包
- `webrtc_cj` src` 模块代码目录
- `webrtc_cj` src main` 模块项目目录
- `webrtc_cj` src main cangjie` 仓颉代码目录
- `webrtc_cj` src main resources` 资源文件目录
- `webrtc_cpp` 工程模块 - 编译生成一个har包
- `webrtc_cpp` src` 模块代码目录
- `webrtc_cpp` src main` 模块项目目录
- `webrtc_cpp` src main cangjie` c++代码目录
- `webrtc_cpp` src main resources` 资源文件目录
- `hvigor` 构建工具目录

### 接口说明

主要类和函数接口说明详见 [API](./doc/feature_api.md)

## 使用说明

### 编译运行

1. 通过 module 引入

   1. 克隆下载项目

   2. 将 webrtc 模块拷贝到应用项目下

   3. 修改自身应用 entry 下的 oh-package.json5 文件，在 dependencies 字段添加 "webrtc": "file:../webrtc"

   ```shell
   {
     "name": "entry",
     "version": "1.0.0",
     "description": "Please describe the basic information.",
     "main": "",
     "author": "",
     "license": "",
     "dependencies": {
       "@cangjie-tpc/webrtc": "file:../webrtc_cj"
     }
   }
   ```

   4.   在项目中使用 import webrtc.* 引用 webrtc项目 

   ```cangjie
   import webrtc.*
   ```

2. 把 webrtc-ffi作为三方库依赖引入 

   1. 目标工程把 webrtc-ffi依赖库作为 git submodule 引入

   ```shell
   > cd $工程根目录
   > mkdir third-party
   > cd third-party
   > git submodule add "https://gitcode.com/Cangjie-TPC/webrtc-ffi.git"
   ```

   2. 修改自身应用 entry 下的 cjpm.toml 文件，添加依赖

   ```
   [dependencies]
   	webrtc = {path = "../third-party/webrtc-ffi/webrtc/src/main/cangjie", version = "1.0.0"}
   ```

   3.  在项目中使用 webrtc 组件 

   ```cangjie
   import banner.*
   ```

3. 通过中心仓下载安装

   ```shell
   ohpm install @cangjie-tpc/webrtc_hybrid
   ohpm install @cangjie-tpc/webrtc
   ```

### 功能示例

用例代码在entry目录下 [功能示例](./entry/src/main/cangjie/index.cj)

## 约束与限制
1. 在下述版本验证通过：

- DevEco Studio 5.1.1 Release(5.1.1.840)


## 开源协议

本项目基于 [Apache License 2.0](/LICENSE) ，请自由的享受和参与开源。

## 参与贡献

欢迎给我们提交 PR，欢迎给我们提交 issue，欢迎参与任何形式的贡献。