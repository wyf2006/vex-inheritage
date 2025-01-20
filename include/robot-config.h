#ifndef ROBOT_CONFIG_H_
#define ROBOT_CONFIG_H_
#include "chassis.h"
#include "EncodingDisk.h"

using namespace vex;

class Chassis;
class Act;
class EncodingDisk;
class Speedcontrol;

extern brain Brain;

extern motor Serial;


extern inertial Inertial;
extern optical Optical;
extern vision vis;
extern vision::signature redRing;
extern vision::signature blueRing;

extern distance Distance;
extern rotation Drunk_rotation;

extern motor Motor_BaseLF;
extern motor Motor_BaseLB1; 
extern motor Motor_BaseLB2;

extern motor Motor_BaseRF;
extern motor Motor_BaseRB1;
extern motor Motor_BaseRB2;

extern motor Motor_Get;
extern motor Motor_Collect;
extern motor Motor_Claw;
extern motor Motor_Hook;


extern motor_group Motor_BaseL;
extern motor_group Motor_BaseR;

extern controller Controller;

extern digital_out Catch;
extern digital_out filtrate;
extern digital_out load;
extern digital_out hand;

extern Chassis chassis;
extern Act act;
extern Speedcontrol speedcontrol;
extern PID pid_speed;
extern PID pid_position;
extern PID pid_rotate;
extern PID pid_pose;
extern PID pid_drunk;
extern PID pid;



#endif
