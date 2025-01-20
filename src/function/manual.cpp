/**
  ******************************************************************************
  * @file           : manual.cpp
  * @brief          : 手动模式
  ******************************************************************************
  * @attention      ：
  *
  *
  ******************************************************************************
  */

#include "_includes.h"

void manual_init();

void manual_task()          //手动模式函数
{
    manual_init();
    thread controller_thread = thread(Thread_ControllerTask);//开辟一个My_Controller线程
    thread keep_thread = thread(Thread_Keep); 
    thread analyse_thread = thread(Thread_DataAnalyse);//开辟一个My_Chassis线程
    thread chassis_thread = thread(Thread_ChassisTask);//开辟一个My_Chassis线程
    thread filtrate = thread(Thread_FiltrateTask_BLUE);
    while (true)
    {
        chassis_task();
        this_thread::sleep_for(10);
    }
}

