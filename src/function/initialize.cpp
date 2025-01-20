/**
  ******************************************************************************
  * @file           : initialize.cpp
  * @brief          : 初始化硬件,以及将硬件重置到初始状态
  ******************************************************************************
  * @attention      ：
  *
  *
  ******************************************************************************
  */
#include "_includes.h"



/// @brief 总初始化
void vexcodeInit(void){
    serial_init();
    Inertial.calibrate();
    std::cout << "calibrated!" << std::endl;
    while (Inertial.isCalibrating());
    std::cout << "calibrated2!" << std::endl;
    Controller.Screen.print("GO!");

    angle_sensor_init();
    Motor_Get.setStopping(vex::brakeType::coast);
    Motor_Get.setVelocity(85,vex::velocityUnits::pct);
}


/// @brief 自动模式初始化
void auto_init(){
    angle_sensor_init();
    inertial_init();
    Motor_BaseL.setStopping(brakeType::brake);    
    Motor_BaseR.setStopping(brakeType::brake);
    Motor_Hook.setStopping(brakeType::hold);
    Motor_Claw.setStopping(brakeType::brake);

    Motor_Collect.setVelocity(90,pct);
    Motor_Get.setVelocity(80,pct);
    Motor_Claw.setVelocity(100,pct);
    Motor_Hook.setVelocity(70,pct);

    Motor_Claw.resetPosition();

   

    std::vector<double> x0 = {0, 0}; // 初始状态向量
    Matrix P0({{1, 0}, {0, 1}}); // 初始协方差矩阵
    KF.initialize(x0,P0);
}

/// @brief 手动模式初始化
void manual_init(){
    angle_sensor_init();
    inertial_init();
    Drunk_rotation.resetPosition();
    Motor_Claw.setPosition(0,deg);
    Motor_Hook.setPosition(0,deg);

    Motor_BaseL.setStopping(brakeType::coast);    
    Motor_BaseR.setStopping(brakeType::coast);
    Motor_Hook.setStopping(brakeType::hold);

    Motor_Collect.setVelocity(80,pct);
    Motor_Get.setVelocity(100,pct);
    Motor_Claw.setVelocity(70,pct);
    Motor_Hook.setVelocity(100,pct);

    Motor_Hook.setStopping(brakeType::hold);
    Motor_Claw.setStopping(brakeType::hold);
} 

/// @brief 初始化角度传感器
void angle_sensor_init(){
    Motor_BaseL.resetPosition();
    Motor_BaseR.resetPosition();
}

/// @brief 初始化陀螺仪
void inertial_init()
{
    Inertial.resetRotation();
    Inertial.resetHeading();
}

/// @brief 串口初始化
void serial_init(){
    int BAUDRATE = 19200;
    vexGenericSerialEnable(Serial.index(), 0);
    vexGenericSerialBaudrate(Serial.index(), BAUDRATE);
}