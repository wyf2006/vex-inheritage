# small_car 项目文件结构

## 根目录
- **makefile**: 项目构建配置文件，定义编译规则
- **.gitignore**: Git 忽略文件配置
- **.vscode/**: VS Code 配置目录
  - **c_cpp_properties.json**: C/C++ 编译器和头文件路径配置
  - **extensions.json**: 推荐的 VS Code 扩展
  - **launch.json**: 调试配置
  - **settings.json**: VS Code 设置
  - **vex_project_settings.json**: VEX 项目特定设置

## 构建系统
- **vex/**: VEX 构建系统文件
  - **mkenv.mk**: 构建环境配置（编译器路径、平台等）
  - **mkrules.mk**: 编译规则定义

## 源代码
- **src/**: 源代码目录
  - **main.cpp**: 程序入口点，包含 `main()` 函数
  - **data.csv**: 数据文件（空）
  - **note.md**: 笔记文件（空）

  - **function/**: 功能模块
    - **manual.cpp**: 手动控制模式实现
    - **initialize.cpp**: 系统初始化实现
    - **auto.cpp**: 自动控制模式实现
    - **analyse.cpp**: 数据分析功能
    - **serial.cpp**: 串口通信（空文件）
    - **Speedcontrol.cpp**: 速度控制功能（空文件）
    - **Interrupt.cpp**: 中断处理功能（空文件）
    - **tools.cpp**: 工具函数（空文件）
  
  - **math/**: 数学算法模块
    - **my-timer.cpp**: 定时器实现
    - **PID.cpp**: PID 控制器实现
    - **PIDProcess.cpp**: PID 控制过程实现
    - **KalmanFilter.cpp**: 卡尔曼滤波器实现
    - **Matrix.cpp**: 矩阵运算实现
    - **EncodingDisk.cpp**: 编码盘实现
  
  - **components/**: 硬件组件模块
    - **controller.cpp**: 控制器任务实现
    - **chassis.cpp**: 底盘控制实现
  
  - **config/**: 配置模块
    - **robot-config.cpp**: 机器人硬件配置

## 头文件
- **include/**: 头文件目录
  - **_includes.h**: 主包含文件，包含所有项目需要的头文件
  - **auto.h**: 自动模式声明
  - **manual.h**: 手动模式声明
  - **chassis.h**: 底盘控制声明
  - **controller.h**: 控制器任务声明
  - **initialize.h**: 初始化函数声明
  - **tools.h**: 工具函数声明
  - **PID.h**: PID 控制器类声明
  - **PIDProcess.h**: PID 过程控制声明
  - **Matrix.h**: 矩阵类声明
  - **EncodingDisk.h**: 编码盘类声明
  - **Speedcontrol.h**: 速度控制类声明
  - **Interrupt.h**: 中断处理声明
  - **serial.h**: 串口通信声明
  - **robot-config.h**: 硬件设备配置声明
  - **user-math.h**: 用户数学工具声明
  - **vex.h**: VEX 系统头文件
  - **KalmanFilter.h**: 卡尔曼滤波器声明（空文件）

此项目是一个基于 VEX 机器人系统的小车控制程序，集成了 PID 控制、卡尔曼滤波等算法，支持手动和自动控制模式。
