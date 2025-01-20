#ifndef TOOLS_H
#define TOOLS_H
#include "robot-config.h"
int sign(float);

bool Red();                     //Optical相关函数
bool Blue();
void keep_red();
void keep_blue();
void wait_ring();

void Ringin();                  //电机相关函数
void Ringout();
void Collect_stop();
void Keep();

void Filtrate();                //气缸相关函数
void CATCH();
void GOT();

void Arm_return();              //机械臂相关函数（中立桩）
void Arm_up();
void Arm_down();
void Remove();
void Wall_set();
void Team_set();

void Catch_lamp();              //车尾灯函数
void Collect_shift();           //履带换速函数

void Thread_FiltrateTask();     //线程函数   
void Thread_FiltrateTask_RED();
void Thread_FiltrateTask_BLUE();
void Thread_Keep();
void Thread_Kasi();



#endif