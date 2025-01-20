#include "_includes.h"


//增量式PID控制电机速度（可用于自动实现串级PID防超调，可用于手动软启动/刹车，防翘头翘尾）
//由于加速，向前刹车，向后刹车的情况不同，参数应分别调节
//主要调节参数I，P抑制超调，D没啥用，置零即可

/// @brief 加速并维持期望速度
/// @param 期望速度（分正负）
/// @return 当前应输出到电机的速度增量
double Speedcontrol::speed_up(double speed)              
{
    pid.init(&pid_speed, 3.0, 4.0, 0 ,20);
    double speedDev = pid.PID_Incremental(&pid_speed, speed, Chassis_velocity);
    return speedDev;
}


double Speedcontrol::brake(double speed)
{
    pid.init(&pid_speed, 0.3, 0.55, 0, 10);    //0.038  0.055
    float speedDev = pid.PID_Incremental(&pid_speed, speed, Chassis_velocity);
    return speedDev;
}

/// @brief 往前速度的刹车
/// @param 期望速度（分正负）
/// @return 当前应输出到电机的速度增量
double Speedcontrol::brake_1(double speed)
{
    pid.init(&pid_speed, 0.5, 0.7, 0, 15);
    float speedDev = pid.PID_Incremental(&pid_speed, speed, Chassis_velocity);
    return speedDev;
}

/// @brief 往后速度的刹车
/// @param 期望速度（分正负）
/// @return 当前应输出到电机的速度
double Speedcontrol::brake_2(double speed)
{
    pid.init(&pid_speed, 0.3, 0.75, 0, 20);
    float speedDev = pid.PID_Incremental(&pid_speed, speed, Chassis_velocity);
    return speedDev;
}

/// @brief 调整曲线转向速度
/// @param 期望速度（分正负）
/// @return 当前应输出到电机的速度
double Speedcontrol::adjust(double speed)
{
    pid.init(&pid_speed, 0.3, 1, 0, 30);
    float speedDev = pid.PID_Incremental(&pid_speed, speed, Chassis_velocity);
    return speedDev;
}

/// @brief 软启动用，可控制单边速度
/// @param 期望速度（分正负）,左右侧选择(L为左，R为右)
/// @return 当前应输出到电机的速度增量
double Speedcontrol::soft_drive(double speed, char side)                 
{
    float side_speed = 0;
    pid.init(&pid_speed, 0.019, 0.04, 0 ,2);
    if (side == 'L')
    {
        side_speed = (Motor_BaseLB2.velocity(pct) + Motor_BaseLB1.velocity(pct) + Motor_BaseLF.velocity(pct)) / 3;
    }
    else if (side == 'R')
    {
        side_speed = (Motor_BaseRB2.velocity(pct) + Motor_BaseRB1.velocity(pct) + Motor_BaseRF.velocity(pct)) / 3;
    }
    double speedDev = pid.PID_Incremental(&pid_speed, speed, side_speed);
    return speedDev;
}