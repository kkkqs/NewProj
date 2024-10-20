#pragma once
#include <vector>
#include "vex.h"
#include "Utils/HUSTMotorGroup.hpp"
class BaseChassis
{
protected:
    std::vector<HUSTMotorGroup> motorGroups;
public:
    explicit BaseChassis(vex::motor_group& L, 
                        vex::motor_group& R
    ): motorGroups{
        HUSTMotorGroup(L, 0),
        HUSTMotorGroup(R, 0),
    } {};

    explicit BaseChassis(vex::motor& L, 
                        vex::motor& R 
    ): motorGroups{
        HUSTMotorGroup(L, 0),
        HUSTMotorGroup(R, 0),
    } {};

    explicit BaseChassis(vex::motor_group& LF, 
                        vex::motor_group& LB, 
                        vex::motor_group& RF, 
                        vex::motor_group& RB
    ): motorGroups{
        HUSTMotorGroup(LF, 0),
        HUSTMotorGroup(LB, 0),
        HUSTMotorGroup(RF, 0),
        HUSTMotorGroup(RB, 0)
    } {};
    
    explicit BaseChassis(vex::motor& LF, 
                        vex::motor& LB, 
                        vex::motor& RF, 
                        vex::motor& RB
    ): motorGroups{
        HUSTMotorGroup(LF, 0),
        HUSTMotorGroup(LB, 0),
        HUSTMotorGroup(RF, 0),
        HUSTMotorGroup(RB, 0)
    } {};

    BaseChassis() {}

    
    void stop() {for (auto& motorGroup : motorGroups) motorGroup.stop();}
    void move() {for (auto& motorGroup : motorGroups) motorGroup.move();}

    virtual void setSpeed(float speed, vex::velocityUnits unit = vex::velocityUnits::pct) = 0;
    virtual void setFreeSpeed(float x, float r, float y = 0, vex::velocityUnits unit = vex::velocityUnits::pct) = 0;
    virtual void motorSpeedControl(vex::motor_group target,double expected_speed, vex::velocityUnits unit = vex::velocityUnits::pct) = 0;
};