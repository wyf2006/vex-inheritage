small_car/
├── .vscode/                # VS Code 配置目录
├── include/                # 头文件目录
│   ├── _includes.h         # 主包含文件
│   ├── auto.h              # 自动模式相关声明
│   ├── chassis.h           # 底盘控制相关声明
│   ├── controller.h        # 控制器任务声明
│   ├── EncodingDisk.h      # 编码盘类声明
│   ├── initialize.h        # 初始化函数声明
│   ├── Interrupt.h         # 中断处理声明
│   ├── KalmanFilter.h      # 卡尔曼滤波器声明
│   ├── manual.h            # 手动模式声明
│   ├── Matrix.h            # 矩阵类声明
│   ├── PID.h               # PID控制器声明
│   ├── PIDProcess.h        # PID过程控制声明
│   ├── robot-config.h      # 硬件设备配置
│   ├── serial.h            # 串口通信声明
│   ├── Speedcontrol.h      # 速度控制声明
│   ├── tools.h             # 工具函数声明
│   ├── user-math.h         # 用户数学工具
│   └── vex.h               # VEX系统头文件
│
├── src/                    # 源代码目录
│   ├── components/         # 硬件组件模块
│   │   ├── chassis.cpp     # 底盘控制实现
│   │   └── controller.cpp  # 控制器任务实现
│   │
│   ├── config/             # 配置模块
│   │   └── robot-config.cpp# 机器人硬件配置
│   │
│   ├── function/           # 功能模块
│   │   ├── analyse.cpp     # 数据分析功能
│   │   ├── auto.cpp        # 自动控制模式
│   │   ├── initialize.cpp  # 系统初始化
│   │   ├── Interrupt.cpp   # 中断处理(空)
│   │   ├── manual.cpp      # 手动控制模式
│   │   ├── serial.cpp      # 串口通信(空)
│   │   ├── Speedcontrol.cpp# 速度控制(空)
│   │   └── tools.cpp       # 工具函数(空)
│   │
│   ├── math/               # 数学算法模块
│   │   ├── EncodingDisk.cpp# 编码盘实现
│   │   ├── KalmanFilter.cpp# 卡尔曼滤波器
│   │   ├── Matrix.cpp      # 矩阵运算
│   │   ├── my-timer.cpp    # 定时器实现
│   │   ├── PID.cpp         # PID控制器
│   │   └── PIDProcess.cpp  # PID控制过程
│   │
│   ├── main.cpp            # 程序入口点
│   ├── data.csv            # 数据文件
│   └── note.md             # 项目笔记
│
├── vex/                    # VEX构建系统文件
│   ├── mkenv.mk            # 构建环境配置
│   └── mkrules.mk          # 编译规则定义
│
├── .gitignore              # Git忽略配置
└── makefile                # 项目构建文件
