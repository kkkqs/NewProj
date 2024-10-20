#pragma once
#include "vex.h"
class HUSTMotorGroup {
private:
    vex::motor_group* _motorGroup;
    vex::velocityUnits _units;
    float _speedPercent;
public:
    explicit HUSTMotorGroup (vex::motor_group& motorGroup, int speedPercent):
    _motorGroup(&motorGroup), _speedPercent(speedPercent)
    {}
    explicit HUSTMotorGroup (vex::motor& motor, int speedPercent):
    _motorGroup(new vex::motor_group(motor)), _speedPercent(speedPercent)
    {}

    void setSpeed(float speed, vex::velocityUnits units = vex::velocityUnits::pct) {_speedPercent = speed, _units = units;};
    void move() {_motorGroup->setVelocity(_speedPercent, _units); _motorGroup->spin(vex::forward);};
    void revs() {_motorGroup->setVelocity(_speedPercent, _units); _motorGroup->spin(vex::reverse);};
    void stop() {_motorGroup->stop();}
    void setBrakeMode(vex::brakeType brakeType) {_motorGroup->setStopping(brakeType);}
    int getMotorAngle(vex::rotationUnits units) {return _motorGroup->position(units);}
};