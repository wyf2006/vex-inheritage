#ifndef PID_H
#define PID_H
class PID {
protected:
    float errorCurt, errorLast, errorPrev, errorDev, errorInt;
    float P, I, D;
    bool firstTime;
    bool arrived;
    float kp, ki, kd;
    float target, errorTol, DTol;
    float IMax, IRange;
    float Outputmax;
    float output;
    float jumpTime;
private:
    float error;
public:
    PID();
    void refresh();
    float getOutput();
    void update(float input);
    void setTarget(float _Target);
    void setIMax(float _IMax);
    void setIRange(float _IRange);
    void setOutputmax(float _Outputmax);
    void setErrorTolerance(float _errorTol);
    void setDTolerance(float _DTol);
    void setJumpTime(float _jumptime);
    bool targetArrived();
    void setCoefficient(float kp, float ki, float kd);
    void init(PID *pid, float kp, float ki, float kd, float limit_value, float IMax = 5, float IRange = 10, float errorTol = 1, float DTol = 0.5);
    double PID_Incremental(PID *pid, float target, float now);
    double PID_Absolute(PID *pid, float target, float now);
};
#endif