#ifndef EncodingDisk_H_
#define EncodingDisk_H_

#include "vex.h"
#include <cmath>
#include <utility>

const float PI = 3.1415926;

class EncodingDisk {
private:
    vex::inertial* _imu;
    vex::rotation* _xEncoder;
    vex::rotation* _yEncoder;
    float _xEncoderAngleFromForward;
    float _angleBetweenXY;
    float _sizeOfWheel;

    float _posX, _posY;
    float _biasX, _biasY;

    bool _initialized;
    float _lastCodeX, _lastCodeY;
    float _nowCodeX, _nowCodeY;
    float _forward;
public:
    explicit EncodingDisk(vex::inertial& imu, vex::rotation& xEncoder, vex::rotation& yEncoder, const float sizeOfWheelInMM, const float xEncoderAngleFromForward = -45 , const float angleBetweenXY = 90):
    _imu(&imu), _xEncoder(&xEncoder), _yEncoder(&yEncoder), _xEncoderAngleFromForward(xEncoderAngleFromForward), _sizeOfWheel(sizeOfWheelInMM), _angleBetweenXY(angleBetweenXY), _initialized(bool(false)),
    _biasX(float(0)), _biasY(float(0))
    {}
    EncodingDisk();
    bool Initialized();
    void Init(float biasX = 0.f, float biasY = 0.f, float armLength = 0.f);
    void Update();
    std::pair<float, float> RawPosCM();
    std::pair<float, float> PosMM();
    std::pair<float, float> PosCM();
       
};

#endif