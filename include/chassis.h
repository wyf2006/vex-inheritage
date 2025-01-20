#ifndef CHASSIS_H_
#define CHASSIS_H_

//底盘综合性代码位于此处，包括但不限于操作，宏定义，参数
#include "PID.h"
#include "PIDProcess.h"
#include "robot-config.h"


void chassis_task();           //底盘任务
void Thread_ChassisTask();     //底盘线程 
class Chassis
{
private:
    double Motor_speed[2];//LF、LB、RF、RB,值为百分比
public:
    Chassis();//底盘初始化
    double angle = 0;
    double speed_x = 0;
    double speed_y = 0;
    double speed_r = 0;

    void Move_free(double x, double r);//底盘移动写入期望速度
    
    int stop_Monitor();//手柄底盘停止信号检测

    void Move();//运动执行函数

    void Stop_brake();
    void Stop_coast();
    void Stop_hold();//停止
    
    void Move_withfit(float angle);//可以边走边调整车身姿态
    void Move_withfit2(float angle);//保持当前速度
};

typedef enum
{
    SPEED_CONTROL,//速度控制底盘
    VOLT_CONTROL,//电压控制底盘
    SOFT_CONTROL//(软启动)速度-电压控制底盘
} SpeedControlMode;//底盘运动控制模式

#endif