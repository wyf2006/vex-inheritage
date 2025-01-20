#include "_includes.h"
#include <cmath>

using namespace std;
using std::pair;


 EncodingDisk::EncodingDisk()
 {
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
 }

 bool EncodingDisk::Initialized() {
       
        return _initialized;
    }

void EncodingDisk::Init(float biasX , float biasY , float armLength ) {
        _biasX = _posX = biasX * cos(0) + biasY * cos(90 * PI / 180.f);
        _biasY = _posY = biasX * sin(0) + biasY * sin(90 * PI / 180.f);
        _lastCodeX = 0;
        _lastCodeY = 0;
        _nowCodeX = 0;
        _nowCodeY = 0;

        _imu->resetHeading();
        _xEncoder->resetPosition();
        _yEncoder->resetPosition();
    }

    void EncodingDisk::Update() {
        _forward = _imu->heading();
        _nowCodeX = _xEncoder->position(vex::rotationUnits::deg);
        _nowCodeY = _yEncoder->position(vex::rotationUnits::deg);

        // printf("%f--%f\n", _nowCodeX, _nowCodeY);

        float deltaCodeX = _nowCodeX - _lastCodeX;
        float deltaCodeY = _nowCodeY - _lastCodeY;

        float forwardX = _forward + _xEncoderAngleFromForward;
        float forwardY = forwardX + _angleBetweenXY;

        // printf("%f-%f\n", forwardX,) 

        // float deltaXPos = -deltaCodeX * std::cos((180 - forwardX) * PI / 180.f) + deltaCodeY * std::cos(forwardY * PI / 180.f);
        // float deltaYPos = -deltaCodeX * std::sin((180 - forwardX) * PI / 180.f) + deltaCodeY * std::sin(forwardY * PI / 180.f);

        float deltaXPos = -deltaCodeX * cos((forwardX - 180) * PI / 180.f) + deltaCodeY * cos(forwardY * PI / 180.f);
        float deltaYPos = -deltaCodeX * sin((forwardX - 180) * PI / 180.f) + deltaCodeY * sin(forwardY * PI / 180.f);

        _posX += deltaXPos * PI * _sizeOfWheel / 360.f;
        _posY += deltaYPos * PI * _sizeOfWheel / 360.f;

        _lastCodeX = _nowCodeX;
        _lastCodeY = _nowCodeY;
    }

    pair<float, float> EncodingDisk::RawPosCM() {
        return make_pair(_posX / 10.f, _posY / 10.f);
    }

    pair<float, float> EncodingDisk::PosMM() {
        _forward = _imu->heading();
        float nowPosX = _posX - (_biasX * cos(_forward * PI / 180.f) + _biasY * cos((_forward + 90) * PI / 180.f));
        float nowPosY = _posY - (_biasX * sin(_forward * PI / 180.f) + _biasY * sin((_forward + 90) * PI / 180.f));
        // printf("pos: %f %f \n", _posX, _posY);
        return make_pair(nowPosX, nowPosY);
    }

    pair<float, float> EncodingDisk::PosCM() {
        auto nowPos = PosMM();
        
        return make_pair(nowPos.first / 10.f, nowPos.second / 10.f);
    }
