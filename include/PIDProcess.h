#ifndef PIDPROCESS_H_
#define PIDPROCESS_H_

const int DefaultMaxTimeMsec = 1500;//最大延时时间
extern bool task_keep_flag;
extern bool task_hook_flag;
extern bool task_hook_flag2;
extern bool task_hook_flag3;
extern bool hook_keep_flag;
extern bool task_claw_flag;
class Act
{
private:
    /* data */
public:
   void Straight(float target, float speed, float target_deg, int MaxTimeMse = DefaultMaxTimeMsec);
   void Straight_2(float target, float speed, float target_deg, int MaxTimeMse = DefaultMaxTimeMsec);
   void Rotate(float target, float speed = 70, int MaxTimeMsec = DefaultMaxTimeMsec);
   void distance( float target, float speed = 50, float target_deg = 0, int MaxTimeMsec = DefaultMaxTimeMsec);
   void Drunk(float target);
};

void task_keep();
void task_hook();
void task_Hook(); 
void task_claw();

    
#endif