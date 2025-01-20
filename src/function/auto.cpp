#include "_includes.h"
#define REDSIDE
// #define BLUESIDE
// #define CALIBRATION_ROTATE
// #define CALIBRATION_STRAIGHT
// #define CALIBRATION_DISTANCE

void rotate_pid_test()
{
    act.Rotate(90, 10);
    act.Rotate(270, 60);
    act.Rotate(0, 50);
}

/// @brief 设置陀螺仪角度
/// @param Heading,Rotation 
void set_angle(int Heading, int Rotation)
{
    Inertial.setHeading(Heading,degrees);
    Inertial.setRotation(Rotation,degrees);
}


// #define FILE_RECORD
// #define DEBUG
int default_time = 1500;
/// @brief 自动模式的任务
void autonomous_task()
{   
    auto_init();
    thread debug(Thread_DataAnalyse);
    thread Filtrate(Thread_FiltrateTask_BLUE);
    //thread Kasi(Thread_Kasi);

    #ifdef REDSIDE
    wait(10,msec);

    //开始钩桩
    task_hook_flag = 1;
    act.Straight_2(105, 95, 15, 920);//前进钩桩
    task_hook_flag2 = 1;
    act.Straight_2(-60, 55, 15, 1300);//拉桩倒退
    task_hook_flag2 = 0;
    task_Hook();
    task_hook_flag3 = 1;
    act.Rotate(170, 70, 1500);//旋转且收回钩子
    act.Straight_2(-63, 40, 200 , 1300);//反向夹桩
    CATCH();//夹
    act.Rotate(147, 70, 2000);   //160,70,1400
    Ringin();//收
    act.Straight_2(132, 30, 175, 3000);//开始收环

    //开始清理角落环
    int angle_coner = 240;//角落角度
    act.Rotate(angle_coner, 60, 1200);
    act.Straight(80, 35 , angle_coner, 1600);
    act.Straight(-20, 25 , angle_coner, 1400);
    act.Straight(30, 45 , angle_coner, 1000);
    act.Straight(-20, 25 , angle_coner, 1400);
    act.Straight(30, 45 , angle_coner, 1000);
    act.Straight(-20, 25 , angle_coner, 1400);
    act.Straight(30, 45 , angle_coner, 1000);
    act.Straight(-20, 25 , angle_coner, 1400);
    act.Straight(30, 45 , angle_coner, 1000);
    act.Straight(-40, 25 , angle_coner, 1400);

    //开始挂联队桩
    act.Rotate(90, 50, 1300);
    act.distance(160, 70, 90, 2500);
    act.Rotate(180, 40, 2000);
    act.Straight(45, 40, 180, 1600);
    Motor_Claw.spinTo(-750,deg,true);
    act.Straight(-50, 50, 180, 1100);
    act.Rotate(0, 50, 1100);
    task_claw_flag = 1;
    act.Straight(60, 30, 0, 2000);

    
    printf("DONE\n");
    #endif

    #ifdef BLUESIDE
    wait(10,msec);
    Motor_Hook.spinTo(-700,deg,false);
    Motor_Get.spin(reverse, 40, pct);   
    #endif

    #ifdef CALIBRATION_ROTATE
    wait(10,msec);
    act.Rotate(90, 60 ,1500);
    #endif

    #ifdef CALIBRATION_STRAIGHT
    wait(10,msec);
    CATCH();
    Ringin();
    wait(100,msec);
    act.Straight(30, 40 , 0, 1000);
    act.Straight(-20, 40 , 0, 1000);
    act.Straight(30, 40 , 0, 1000);
    act.Straight(-20, 40 , 0, 1000);
    act.Straight(30, 40 , 0, 1000);
    act.Straight(-20, 40 , 0, 1000);
    act.Straight(30, 40 , 0, 1000);
    act.Straight(-20, 40 , 0, 1000);
    act.Straight(30, 40 , 0, 1000);
    act.Straight(-20, 40 , 0, 1000);
    act.Straight(30, 40 , 0, 1000);
    act.Straight(-20, 40 , 0, 1000);
    #endif

    #ifdef CALIBRATION_DISTANCE
    wait(10,msec);
    act.distance(160, 70, 0, 2500);
    #endif

  

#ifdef FILE_RECORD
    Brain.Timer.reset();
    chassis.Move_forward(20.0);
    chassis.Move();
    printf("%f\n", Brain.Timer.time(seconds));
    std::ofstream My_file("data.csv", std::ios::out);
    printf("%d\n", My_file.is_open());
    if (!My_file.is_open())
    {
        std::cout << "Unable to open file";
        exit(1);
        while (Brain.Timer.time(seconds) < 10.0)
        {
            My_file << static_cast<float>(chassis_distance()) << ","
                    << static_cast<float>(Brain.Timer.time(seconds)) << "\n";
            printf("%f\n", Brain.Timer.time(seconds));
        }
        // 将数据写入文件;
        wait(10, msec);
    }
    My_file.close();
    chassis.Move_hold();
    chassis.Move();
#endif

#ifdef DEBUG
    thread debug(Inertial_DataShow);
    while (1)
    {
        TEST_rotate(6.0, 5);
        wait(3, sec);
    }
#endif

    
}

    //act.Straight_2(-38, 25, 0,1500);    
    // CATCH();
    // Ringin();
    // Motor_Claw.spinTo(100,deg,false);
    // wait(500,msec);
    // act.Rotate(-35,30);
    // act.Straight_2(27, 30, -35,1500);

    // act.Rotate(76,50);
    // act.Straight(130, 70, 76,2000);
    // act.Straight_2(35, 35, 76, 1200);
    // act.Straight_2(-25, 35, 76, 1500);

    // act.Rotate(-45, 40, 1000);
    // act.Straight(75, 70, -45,1800);

    // Motor_Claw.spinTo(600,deg,false);
    // Motor_Hook.spinTo(200,deg,false);
    // act.Rotate(10,40,1300);    

    // hand.set(true);
    // act.Straight_fast2slow(52, 70, 35,1200);
    
    // act.Rotate(135, 40,2000);
    // hand.set(false);
    // act.Rotate(0, 40, 1000);
    // act.Straight_2(30, 40, 0,800);
    // act.Rotate(45, 20, 800);
    // wait(800,msec);
    // act.Straight_2(-20, 50, 35, 800);
    // act.Straight_2(30, 40, 35,800);
    // wait(800,msec);

    // act.Rotate(180, 40, 1500);
    // act.Straight_2(-18, 30, 180,1000);   
    // Filtrate.interrupt();
    // Kasi.interrupt();

    // CATCH();
    // Ringout();
    // wait(300,msec);
    // Ringin();
    // wait(200,msec);
    // Ringin();
    // Motor_Claw.spinTo(0,deg,false);
    // Motor_Hook.spinTo(0,deg,false);
    // act.Straight(100, 90, 110, 1200);
    // Ringout();



void DebugEnd()
{
    exit(0);
}


