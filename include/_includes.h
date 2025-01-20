/**
  ******************************************************************************
  * @file           : include.h
  * @brief          : 所有头文件的集合，大部分参数调整都在这里
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INCLUDES_H
#define __INCLUDES_H

/* 内部引用 ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <cmath>
#include <string.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <cassert>
#include <vector>
#include "v5.h"
#include "v5_vcs.h"
/* 用户引用 ------------------------------------------------------------------*/
#include "auto.h"
#include "manual.h"
#include "chassis.h"
#include "controller.h"
#include "user-math.h"
#include "PID.h"
#include "PIDProcess.h"
#include "robot-config.h"
#include "tools.h"
#include "initialize.h"
#include "KalmanFilter.h"
#include "Matrix.h"
#include "EncodingDisk.h"
#include "Speedcontrol.h"
#include "serial.h"

// Add missing includess
#include <stddef.h>

/* 控制参数   ---------------------------------------------------------------------------*/
#define USE_MOTOR_ENCODER             //定义此处就是用电机自带编码器，否则则用角度传感器
// #define CASE_1
 #define CASE_2                     //选择策略
/* 宏定义   ------------------------------------------------------------------*/


/* 结构定义   ------------------------------------------------------------------*/


typedef struct MotionData{
 double position_x;                          //x位置
 double position_y;                          //y位置
 double heading_angle;                           //车辆朝向角(0~360)
 double rotation_angle;                      //车辆旋转角（-∞ ~~ +∞）
 double current_forward;                     //角度传感器（编码器）的当前角度
 MotionData():position_x(0.0),position_y(0.0),heading_angle(0.0),rotation_angle(0.0),current_forward(0.0){};
}MotionData;

typedef struct MainDataSTR{
  MotionData Statedata;                     //存放车辆的位置姿态信息
}MainDataSTR;

/* 全局变量声明   ------------------------------------------------------------------*/
 
extern SpeedControlMode SpeedControlConfig;              //速度控制模式
extern MainDataSTR MainData;                             //存放主要数据
extern KalmanFilter KF;                                  //卡尔曼滤波器
extern const int DefaultMaxTimeMsec;                     //PID默认最大运行时间
extern double ANGLE;                                     //全向移动底盘用，坐标系偏转角
extern float Chassis_velocity;                           //底盘速度

/* 函数全局接口声明   ------------------------------------------------------------------*/

void DataAnalyse();                                       //数据分析函数
void check(float _delta);                                 //查看单个数据函数，可在终端查看数据
void Thread_DataAnalyse();

#endif