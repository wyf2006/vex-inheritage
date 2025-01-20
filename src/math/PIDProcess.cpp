#include "_includes.h"

using namespace std;
using namespace vex;

MyTimer Timer;
const float braking_distance = 20.0;
int count = 0;
bool task_keep_flag = 0;
bool task_hook_flag = 0;
bool task_hook_flag2 = 0;
bool task_hook_flag3 = 0;
bool task_claw_flag = 0;

  double delta_t = 0.01; 
  Matrix F({{1, delta_t*100}, {0, 1}}); 
  Matrix H({{1, 0}}); 
  Matrix Q({{0.5, 0}, {0, 0.5}}); 
  Matrix B(vector<vector<double>>{{0.5*delta_t*delta_t*100},{1}}); 
  Matrix R({{1}}); 
  KalmanFilter KF(F, H, Q, R, B);




/// @brief 旋转到指定角度
/// @param 目标角度，最大时间 
void Act::Rotate(float deg, float speed, int MaxTimeMsec) {
    static PID pid_rotate;
    static bool used = false;
   
    printf("PIDRotate %f\n", deg);
    
    if (false == used) {
        pid.init(&pid_rotate, 0.6, 0.3, 0.4, speed, 6, 2, 0.8, 0.45);
    }
    Timer.reset();

    while (true) {
        float delta = pid.PID_Absolute(&pid_rotate, deg, MainData.Statedata.rotation_angle);
        float degree_to_target = delta * 3;
        int direction = sign(delta);
        if(fabs(degree_to_target) > 500)
        {
            delta = speed * direction;
        }
        chassis.Move_free(0, delta);
        //std::cout << Inertial.rotation() << std::endl;
        if (pid_rotate.targetArrived()) {
            chassis.Stop_brake();
            angle_sensor_init();
            std::cout << Inertial.rotation() <<"    done" << std::endl;
            wait(200,msec);
            break;
        }

        if (Timer.getTime() > MaxTimeMsec) 
        {
            chassis.Stop_brake();
            angle_sensor_init();
            std::cout << Inertial.rotation() <<"    time_out" << std::endl;
            break;
        }

        chassis.Move();
        task_hook();
        wait(10, msec);
        Timer.click();

    }
}

/// @brief 直行向前（长距离）
/// @param 目标距离
/// @param 速度
/// @param 修正角度 
/// @param 最大时间
void Act::Straight(float target, float speed, float target_deg, int MaxTimeMsec) {
    double SPEED = Chassis_velocity;
    printf("PIDStaright %f\n", target);
    
    pid.init(&pid_position, 1.0, 0.1, 20.0, speed, 4, 10, 1, 2);
    Timer.reset();
    \
    while (true) {
        float distance_to_target = pid.PID_Absolute(&pid_position, target, MainData.Statedata.position_y)* 2;
       
        if(fabs(distance_to_target) >= braking_distance)
        {
            SPEED = pid.PID_Absolute(&pid_position, target, MainData.Statedata.position_y);
        }
        else if(fabs(distance_to_target)< braking_distance)
        {
            SPEED = pid.PID_Absolute(&pid_position, target, MainData.Statedata.position_y)* 2;
        }
        else
        {
            float precise;
            precise = fmin(fabs(pid_position.getOutput()), 5) * sign(pid_position.getOutput());
            SPEED += speedcontrol.speed_up(precise);
        }
       
        
         chassis.Move_free(SPEED, 0);
         //chassis.Move_withfit(target_deg);
        std::cout<< Chassis_velocity << std::endl;
        if (pid_position.targetArrived()) {
            chassis.Stop_brake();
            std::cout << MainData.Statedata.position_y<<"   done" << std::endl;
            angle_sensor_init();
            break;
        }

        if (Timer.getTime() > MaxTimeMsec) {
            chassis.Stop_brake();
            std::cout << MainData.Statedata.position_y << "  Timeout" << std::endl;
            angle_sensor_init();
            break;
        }

        chassis.Move();
        task_claw();
        vex::wait(10, msec);
        Timer.click(); 
    }
}

#pragma region 抢桩距离直线
/// @brief 直行向前（抢桩距离，走路线）
/// @param 目标距离
/// @param 速度0
/// @param 修正角度 
/// @param 最大时间
void Act::Straight_2(float target, float speed, float target_deg, int MaxTimeMsec) {
    double SPEED = Chassis_velocity;
    printf("PIDStaright %f\n", target);
    
    pid.init(&pid_position,1.2, 0.02, 0.8, speed, 4, 10, 1, 2);//pidRot, kp, ki, kd, 输出限幅, 积分开始范围, 积分上限, 误差容忍度, 微分容忍度 
    Timer.reset();
    
    while (true) {
        float distance_to_target = pid.PID_Absolute(&pid_position, target, MainData.Statedata.position_y)* 2;
       
        if(fabs(distance_to_target) >= 0)
        {
            SPEED = pid.PID_Absolute(&pid_position, target, MainData.Statedata.position_y);
        }
        else if(10 < fabs(distance_to_target) &&fabs(distance_to_target)< braking_distance)
        {
            SPEED += speedcontrol.brake(5*sign(distance_to_target));
        }
        else
        {
            float precise;
            precise = fmin(fabs(pid_position.getOutput()), 5) * sign(pid_position.getOutput());
            SPEED += speedcontrol.speed_up(precise);
        }
         std::cout<< Chassis_velocity << std::endl;
         //std::cout << MainData.Statedata.position_y<< std::endl;
         chassis.Move_free(SPEED, 0);
         chassis.Move_withfit(target_deg);

        if (pid_position.targetArrived()) {
            chassis.Stop_brake();
            std::cout << MainData.Statedata.position_y<<"   done" << std::endl;
            angle_sensor_init();
            break;
        }

        if (Timer.getTime() > MaxTimeMsec) {
            chassis.Stop_brake();
            std::cout << MainData.Statedata.position_y << "  Timeout" << std::endl;
            angle_sensor_init();
            break;
        }

        chassis.Move();
        vex::wait(10, msec);
        Timer.click(); 

        task_keep();
        task_hook();
        task_Hook();
    }
}
#pragma endregion


/// @brief 使用激光传感器作为反馈的PID
/// @param 目标距离，速度，目标角度，最大时间
void Act::distance(float target, float speed, float target_deg, int MaxTimeMsec)
{
    printf("disStaright %f\n", target);
    pid.init(&pid_position, 1.0, 0.5, 0.1, speed, 4, 10, 0.5, 1);
    Timer.reset();
    
    while (true) 
    {
        float delta = pid.PID_Absolute(&pid_position, target, Distance.objectDistance(distanceUnits::cm));
        chassis.Move_free(delta,0);
        if(target_deg == 0) chassis.Move_withfit(MainData.Statedata.rotation_angle);
        else chassis.Move_withfit(target_deg);
        std::cout<< Distance.objectDistance(distanceUnits::cm) << std::endl;

        if (pid_position.targetArrived()) {
            chassis.Stop_brake();
            std::cout << Distance.objectDistance(distanceUnits::cm)<<"   done" << std::endl;
            angle_sensor_init();
            break;
        }

        if (Timer.getTime() > MaxTimeMsec) {
            chassis.Stop_brake();
            std::cout << Distance.objectDistance(distanceUnits::cm) << "  Timeout" << std::endl;
            angle_sensor_init();
            break;
        }
        chassis.Move();
        vex::wait(10, msec);
        Timer.click();
    }
}

/// @brief 控制电机用
/// @param target 
void Act::Drunk(float target)
{
    static bool used = false;

    if (false == used) {
        pid.init(&pid_drunk, 0.2, 0.2, 2, 100, 1, 3);
        used = true;
    }
        float delta = pid.PID_Absolute(&pid_drunk, target, Motor_Hook.position(rotationUnits::deg));
        Motor_Hook.spin(vex::forward, delta, pct);
}


//——————————————————————————————————————————————直行应用任务区——————————————————————————————————————————//
void task_keep()
{
    if(task_keep_flag)
    {
        if(Blue())
        {
            Motor_Collect.stop();
            task_keep_flag = 0;
        }
    }
}

void task_hook()
{
    if(task_hook_flag)
    {
        if(Timer.getTime() == 650)
        {
            Motor_Hook.spinTo(-380, deg, false);
            wait(350, msec);
            Motor_Hook.stop(brake);
            task_hook_flag = 0;
        }
    }
    if(task_hook_flag3)
    {
        Motor_Hook.spinTo(0, deg, false);
        task_hook_flag3 = 0;
    }
}

void task_Hook()
{
    if(task_hook_flag2)
    {
        Motor_Hook.spin(reverse, 30, pct);
    }
    else 
    {
        Motor_Hook.stop();
    }
}

void task_claw()
{
    if(task_claw_flag)
    {
        Motor_Claw.spinTo(0, deg, false);
        task_claw_flag = 0;
    }
}

//————————————————————————————————————————————————旋转应用任务区————————————————————————————————————————//