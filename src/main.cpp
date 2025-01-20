#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include "_includes.h"

using namespace vex;
using std::endl;
using std::cout;
using std::fstream;


competition Competition;

int main()
{
  vexcodeInit();
// Initializing Robot Configuration. DO NOT REMOVE!
#ifdef TO_AUTO // 定义TO_AUTO则进入自动模式
  autonomous_task();
  manual_task();
#endif



#ifndef TO_AUTO
  Competition.autonomous(autonomous_task);
  Competition.drivercontrol(manual_task);
#endif
  while (true)
  {
    // std::cout << MainData.Statedata.position_y << std::endl;                 //输出当前位置信息
    // std::cout << Chassis_velocity << std::endl;                 //输出当前速度信息
    // std::cout << "Angle= " << Inertial.rotation()  << std::endl;       //输出当前角度信息
    //std::cout << "hue= " << Optical.hue() << std::endl;       //输出当前角度信息
    //std::cout << "Distance = "<<Distance.objectDistance(vex::distanceUnits::mm)<< std::endl;       //输出当前角度信息
    // std::cout << "Drunk = " << Drunk_rotation.position(deg) << std::endl; //输出当前角度信息
    // check(Motor_Claw.position(deg));
    // check(Optical.isNearObject());
    Serial_Send( MainData.Statedata.position_y);

    wait(100, msec);
  }


}   