#ifndef Speedcontrol_H
#define Speedcontrol_H


class Speedcontrol
{
    private:

    public:
        double speed_up(double speed);
        double adjust(double speed);
        double soft_drive(double speed,char side);
        double brake_1(double speed);
        double brake_2(double speed);
        double brake(double speed);
};
#endif