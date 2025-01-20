#include "_includes.h"

PID::PID():firstTime(true), arrived(false), IMax(20), IRange(50), jumpTime(100) {
}

void PID::setTarget(float _target) {target = _target;}                  //设置目标值
void PID::setIMax(float _IMax) {IMax = _IMax;}                          //设置积分上限，防止积分饱和
void PID::setOutputmax(float _Outputmax){Outputmax = _Outputmax;}       //设置输出值上限
void PID::setIRange(float _IRange) {IRange = _IRange;}                  //设置积分开始范围                
void PID::setErrorTolerance(float _errorTol) {errorTol = _errorTol;}    //设置误差容忍度，达到此误差即认为到达目标,值越小误差越小
void PID::setDTolerance(float _DTol){DTol = _DTol;}                     //设置微分容忍度，D小于此值即认为到达目标，值越小停止时的速度越小
void PID::setJumpTime(float _jumpTime) {jumpTime = _jumpTime;}          //没啥用
bool PID::targetArrived() {return arrived;}                             //返回是否到达目标
void PID::setCoefficient(float _kp, float _ki, float _kd) {kp = _kp; ki = _ki; kd = _kd;}  //设置PID参数

void PID::refresh() {                       //初始化
    firstTime = true;
    arrived = false;
}

void PID::update(float input) {             //位置式PID的更新计算
    errorCurt = target - input;
    P = kp * errorCurt;
    if (firstTime) {
        firstTime = false;
        errorLast = errorCurt;
        errorInt = 0;
    }
    errorDev = errorCurt - errorLast;
    errorLast = errorCurt;
    D = kd * errorDev;
    if (fabs(P) >= IRange) {
        errorInt = 0;
    } else {
        errorInt += errorCurt;
        if (fabs(errorInt) * ki > IMax)
            errorInt = sign(errorInt) * IMax / ki;
    }
    if (sign(errorInt) != sign(errorCurt) || fabs(errorCurt) <= errorTol) errorInt = 0;
    I = ki * errorInt;
    if (fabs(errorCurt) <= errorTol && fabs(D) <= DTol) {
        arrived = true;
    } else {
        arrived = false;
    }
    output = P + I + D;
    int direction = sign(output);
    output = fmin(fabs(output), fabs(Outputmax)) * direction;
}

float PID::getOutput() {return output;}         //返回输出值

/// @brief 位置式PID，计算得到相对于整个过程绝对值
/// @param pid计算器地址（&pidRot） 
/// @param 期望值
/// @param 当前值
/// @return 输出值
double PID::PID_Absolute(PID *pidRot, float target_val, float now_val)
{
    pidRot->target = target_val;
    pidRot->update(now_val);
    return pidRot->output;
}

/// @brief pid运算器初始化
/// @param &pidRot, kp, ki, kd, 输出限幅, 积分开始范围, 积分上限, 误差容忍度, 微分容忍度 
void PID::init(PID *pidRot, float kp, float ki, float kd, float limit_value, float IRange, float IMax, float ErrorTol, float DTol)
{
    pidRot->setCoefficient(kp, ki, kd);
    pidRot->errorPrev = pidRot->errorLast = pidRot->errorCurt = pidRot->output = 0;
    pidRot->setOutputmax(limit_value);
    pidRot->setIRange(IRange);
    pidRot->setIMax(IMax);
    pidRot->setErrorTolerance(ErrorTol);
    pidRot->setDTolerance(DTol);
    pidRot->refresh();
}

/// @brief 增量式pid，计算得到的是增量
/// @param pid计算器的地址（&pidRot） 
/// @param 期望值
/// @param 当前实际值 
/// @return 增量
double PID::PID_Incremental(PID *pidRot, float target_val, float now_val)   
{
    pidRot->errorCurt = target_val - now_val;
    pidRot->P = pidRot->kp * (pidRot->errorCurt - pidRot->errorLast);

    pidRot->errorDev = pidRot->errorCurt + pidRot->errorPrev - 2 * pidRot->errorLast;
    pidRot->D = pidRot->kd * pidRot->errorDev;

    pidRot->I = pidRot->ki * pidRot->errorCurt;
    
    pidRot->errorPrev = pidRot->errorLast;
    pidRot->errorLast = pidRot->errorCurt;
    
    pidRot->output = -pidRot->P + pidRot->I - pidRot->D;
    int direction = sign(pidRot->output);
    pidRot->output = fmin(fabs(pidRot->output), fabs(pidRot->Outputmax)) * direction;
    return pidRot->output;
}
