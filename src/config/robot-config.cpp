/**
  ******************************************************************************
  * @file           : robot-config.cpp
  * @brief          : 配置机器人的硬件设备
  ******************************************************************************
  * @attention      ：
  *
  *
  ******************************************************************************
  */

#include "_includes.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;                  //主板Brain
Chassis chassis;              //底盘chassis
Act act;                      //调用自动函数act（action）
Speedcontrol speedcontrol;    //调用增量式pid计算速度
PID pid_speed;                //速度环pid计算器
PID pid_position;             //位置环pid计算器
PID pid_rotate;               //旋转pid计算器
PID pid_pose;                 //姿态控制pid计算器
PID pid_drunk;                //机械臂二级电机pid计算器
PID pid;                      //用于调用pid函数

motor Serial = motor(PORT20, ratio18_1, false);               //串口

// VEXcode device constructors
digital_out Catch = digital_out(Brain.ThreeWirePort.C);       //展开
digital_out filtrate = digital_out(Brain.ThreeWirePort.A);    //筛选
digital_out load = digital_out(Brain.ThreeWirePort.D);        //车尾灯
digital_out hand = digital_out(Brain.ThreeWirePort.E);        //（未用上）前伸钩子


inertial Inertial = inertial(PORT17);                          //陀螺仪

vision::signature redRing = vision::signature(2, 7801, 10473, 9137, -1365, -815, -1090, 2.1, 0);
vision::signature blueRing = vision::signature (1, -4831, -3993, -4412, 3775, 5313, 4544, 2.2, 0);
vision vis = vision(PORT3, 50, redRing, blueRing);                      //视觉识别

distance Distance = distance(PORT5);                         //红外测距

optical Optical = optical(PORT11);                             //光学传感器
rotation Drunk_rotation = rotation(PORT5, false);             //编码器

motor Motor_Get = motor(PORT1, ratio18_1, true);            //收集滚轮
motor Motor_Claw = motor(PORT21, ratio18_1, true);            //中立桩爪子

motor Motor_Collect = motor(PORT16, ratio18_1, false);        //套环履带
motor Motor_Hook = motor(PORT8, ratio18_1, false);          //钩桩结构

motor Motor_BaseRF = motor(PORT10, ratio18_1, false);           //右排轮电机
motor Motor_BaseRB1 = motor(PORT19, ratio18_1, true);
motor Motor_BaseRB2 = motor(PORT18, ratio18_1, false);

motor Motor_BaseLF = motor(PORT15, ratio18_1, true);            //左排轮电机
motor Motor_BaseLB1 = motor(PORT12, ratio18_1, false);
motor Motor_BaseLB2 = motor(PORT13, ratio18_1, true);

motor_group Motor_BaseL(Motor_BaseLF, Motor_BaseLB1, Motor_BaseLB2);//底盘左排轮
motor_group Motor_BaseR(Motor_BaseRF, Motor_BaseRB1, Motor_BaseRB2);//底盘右排轮
      

controller Controller = controller(primary);                    //遥控配置

// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

