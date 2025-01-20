#include "_includes.h"

using namespace vex;
SpeedControlMode SpeedControlConfig = SPEED_CONTROL; 
double ANGLE = M_PI / 4; // 45度
float speedL = 0, speedR = 0;       //储存软启动模式双边轮速
float forward_ratio = 1;
float rotate_ratio = 0.5;  


void Chassis::Move_free(double x, double r)
{
    Motor_speed[0] = x + r ;
    Motor_speed[1] = x - r ;
}   

void Chassis::Move() // 运动合成执行
{
    if (SpeedControlConfig == VOLT_CONTROL)      //启用电压控制模式(VOLT_CONTROL)
    {
        Motor_BaseL.spin(vex::forward, Motor_speed[0] * 12.0 / 100.0, vex::volt);
        Motor_BaseR.spin(vex::forward, Motor_speed[1] * 12.0 / 100.0, vex::volt);
    }
    else if(SpeedControlConfig == SOFT_CONTROL) //启用软启动控制模式（SOFT_CONTROL）
    {
        int temp = 0;
        temp = speedcontrol.soft_drive(Motor_speed[0], 'L');
        speedL += temp;
        temp = speedcontrol.soft_drive(Motor_speed[1], 'R');
        speedR += temp;
        Motor_BaseL.spin(vex::forward, speedL , vex::pct);
        Motor_BaseR.spin(vex::forward, speedR , vex::pct);
        
    }
    else                                         //启用速度控制模式(SPEED_CONTROL)
    {
        Motor_BaseL.spin(vex::forward, Motor_speed[0] , vex::pct);
        Motor_BaseR.spin(vex::forward, Motor_speed[1] , vex::pct);
    }
}


void chassis_task()             //底盘任务
{
    float brake_speed = 0;                                  //储存刹车时的底盘速度
    double speed_y = Controller.Axis4.position(pct);        //读取手柄值
    double speed_x = Controller.Axis3.position(pct);
    double speed_r = Controller.Axis1.position(pct);
    if (
        fabs(speed_x) >= 10 || 
        fabs(speed_y) >= 10 ||
        fabs(speed_r) >= 10)                                 //设置摇杆死区，防止摇杆在无操作状态下漂移
    {
        if (fabs(speed_r) > 90) rotate_ratio = 0.7;         //右摇杆拉满提高转向系数，可根据操作手习惯使用               
        else rotate_ratio = 0.45;
        
        chassis.Move_free(speed_x * forward_ratio,
                          speed_r * rotate_ratio);          //期望速度写入速度数组
    }
    else
    {     
        if(Chassis_velocity > 30)
        {
            brake_speed = Chassis_velocity;
            brake_speed +=speedcontrol.brake_1(0);
            chassis.Move_free(brake_speed ,0);
        }
        else if(Chassis_velocity < -30)
        {
            brake_speed = Chassis_velocity;
            brake_speed +=speedcontrol.brake_2(0);
            chassis.Move_free(brake_speed ,0);
        }
        else 
        {
             chassis.Stop_brake();
        }
    }
    chassis.Move(); // 运动执行
}



/// @brief 以下是三种停止模式的强制刹车
void Chassis::Stop_brake()
{
    Motor_BaseL.stop(brake);
    Motor_BaseR.stop(brake);
    Motor_speed[0] = 0;
    Motor_speed[1] = 0;
}

void Chassis::Stop_hold()
{
    Motor_BaseL.stop(hold);
    Motor_BaseR.stop(hold);
    Motor_speed[0] = 0;
    Motor_speed[1] = 0;
}

void Chassis::Stop_coast()
{
    Motor_BaseL.stop(coast);
    Motor_BaseR.stop(coast);
    Motor_speed[0] = 0;
    Motor_speed[1] = 0;
}


/// @brief 附带有路线修正的底盘运动函数，可用于直线修正，或走出贴墙曲线（曲线每次走的不一样）   
/// @param 方向，目标角度
//相较以前版本加入了速度环，希望可以实现调节转向的快慢，未测试
void Chassis::Move_withfit(float angle)
{
    double hope = 0;
    double fit_value = 0;                                                                                            // 修正值
    pid.init(&pid_pose, 0.5, 0.2, 1, 70, 3, 1, 1, 0.5);
    hope = pid.PID_Absolute(&pid_pose, angle, Inertial.rotation(rotationUnits::deg));                           //计算修正值
    fit_value = hope;//+= speedcontrol.adjust(hope);
    Motor_speed[0] += fit_value;
    Motor_speed[1] -= fit_value;
}

void Chassis::Move_withfit2(float angle)
{
    double hope = 0;
    double fit_value = 0;                                                                                            // 修正值
    pid.init(&pid_pose, 0.5, 0.2, 0.6, 70, 3, 1, 1, 0.5);
    hope = pid.PID_Absolute(&pid_pose, angle, Inertial.rotation(rotationUnits::deg));                           //计算修正值
    fit_value = hope;//+= speedcontrol.adjust(hope);
    Motor_speed[0] += fit_value;
    Motor_speed[1] -= fit_value;
}


int Chassis::stop_Monitor()             //没啥用？
{
    if (Controller.ButtonUp.RELEASED == 0 && Controller.ButtonDown.RELEASED == 0 && Controller.ButtonLeft.RELEASED == 0 && Controller.ButtonRight.RELEASED == 0)
    {
        return 1;
    }
    return 0;
}
Chassis::Chassis()  //底盘初始化
{
    Motor_speed[0] = 0;
    Motor_speed[1] = 0;
}

void Thread_ChassisTask()
{
    while (true)
    {
        chassis_task();
        this_thread::sleep_for(10);
    }
}