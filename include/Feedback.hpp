#pragma once
#include "vex.h"
#include "Components/Utils/HUSTFeedback.hpp"

class DistanceFeedback: public HUSTFeedback<int> {
private:
    vex::distance* _distance;
    bool _reverse;
public:
    DistanceFeedback(vex::distance& distance, bool reverse = false): _distance(&distance), _reverse(reverse) {}

    int feedback() override {return float(_distance->value());}
    void reset() override {}
    bool reverse() {return _reverse;}
};

class RotationFeedback: public HUSTFeedback<float> {
private:
    vex::rotation* _rotation;
public:
    RotationFeedback(vex::rotation& rotation): _rotation(&rotation) {}
    float feedback() override {return float(_rotation->position(vex::rotationUnits::deg));}
    void reset() override {_rotation->resetPosition();}
};


class MotorFeedback : public HUSTFeedback<float> {
private:
    vex::motor* _motor;
public:
    MotorFeedback(vex::motor motor): _motor(&motor) {}
    float feedback() override {return float(_motor->position(vex::rotationUnits::deg));}
    void reset() override {_motor->resetPosition();}
};

class IMUFeedBack : public HUSTFeedback<float> {
private:
    vex::inertial* _imu;
public:
    IMUFeedBack(vex::inertial imu):_imu(&imu) {}
    float feedback() override {return float(_imu->heading());}
    void reset() override {_imu->resetHeading();}
};


//class OpticalFeedback : public HUSTFeedback<int> 