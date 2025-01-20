/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Description: use a controller to controll                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "_includes.h"

using namespace vex;
//¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ªÊÖ±ú¿ØÖÆº¯Êý£¬ÓÃÓÚ¿ØÖÆÉÏ²ã½á¹¹£¬Çë×ÔÐÐÅäÖÃ¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª//
void controller_task()
{  
    double angle=Motor_Claw.position(deg);
    Controller.Screen.setCursor(3,2);
    Controller.Screen.print(angle);
    int32_t angleBegin = -155;                             
    if(Controller.ButtonR1.pressing()&&Controller.ButtonR2.pressing())
    {
        Motor_Collect.spin(forward,80,pct);
        Motor_Get.spin(forward,80,pct);
        if(Motor_Claw.position(deg)>angleBegin)
        {
            Motor_Claw.spin(reverse,45,rpm);
        }
        else if(Motor_Claw.position(deg)<(angleBegin-30))
        {
            Motor_Claw.spin(forward,185,rpm);
        }
        else if (Motor_Claw.position(deg)<(angleBegin-15))
        {
            Motor_Claw.spin(forward,45,rpm);
        }
        else
        {
            Motor_Claw.stop(brake);
            Motor_Collect.spin(forward,190,rpm);
        }
    }
    else if(Controller.ButtonR1.pressing())
    {
        Motor_Get.spin(forward,85,pct);
        if(Motor_Claw.position(deg)>(angleBegin-30)&&Motor_Claw.position(deg)<-20)
        {
            Motor_Collect.stop();
            Motor_Claw.spin(forward,50,pct);
        }
        else
        {
            Motor_Claw.stop(brake);
            Motor_Collect.spin(forward,80,pct);
        }
    }
    else if(Controller.ButtonR2.pressing())
    {
        if(Motor_Claw.position(deg)<(angleBegin-30))
        Motor_Claw.spin(forward, 180, rpm);
        else if(Motor_Claw.position(deg)<-20)
        Motor_Claw.spin(forward, 45, rpm);
        else
        Motor_Claw.stop(brake);
    }
    else if(Controller.ButtonL2.pressing())
    {
      if(Motor_Claw.position(deg) <(angleBegin-30))
      {
        Motor_Collect.stop();
        Motor_Claw.spin(reverse, 185, rpm);
      }
      else if(Motor_Claw.position(deg) <0)
      {
        Motor_Collect.stop();
        Motor_Claw.spin(reverse, 50, rpm);
      }
      else
      {
        Motor_Claw.stop(brake);
      }
    }
    else if(Controller.ButtonL1.pressing())
    {
        Motor_Collect.spin(reverse, 45, pct);
        Motor_Get.spin(reverse, 45, pct);
    }
    else
    {
        Motor_Claw.stop(brake);
        Motor_Collect.stop();
        Motor_Get.stop();
    }

    if(Controller.ButtonDown.PRESSED)
    {
        GOT();
    }
    else if(Controller.ButtonA.PRESSED)
    {
       CATCH();
    }
    if (Controller.ButtonY.PRESSED)
    {
        Keep();
    }
#ifdef DEBUG

#endif
}






