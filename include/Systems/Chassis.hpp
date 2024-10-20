#pragma once
#include "Components/BaseChassis.hpp"

class Chassis : public BaseChassis {
public:
    /// @brief Build Motor
    /// @param L Left Motor
    /// @param R Right Motor
    Chassis (vex::motor_group& L, 
    vex::motor_group& R
    ): BaseChassis(L, R) {
    };
    /// @brief Build Motor
    /// @param L Left Motor
    /// @param R Right Motor
    Chassis (vex::motor& L, 
    vex::motor& R
    ): BaseChassis(L, R) {
    };
    /// @brief Build Motor
    /// @param LF Left Front Motor
    /// @param LB Left Back Motor
    /// @param RF Right Front Motor
    /// @param RB Right Back Motor
    Chassis (vex::motor_group& LF, 
    vex::motor_group& LB, 
    vex::motor_group& RF, 
    vex::motor_group& RB
    ): BaseChassis(LF, LB, RF, RB) {
    };

    /// @brief Build Motor
    /// @param LF Left Front Motor
    /// @param LB Left Back Motor
    /// @param RF Right Front Motor
    /// @param RB Right Back Motor
    Chassis (vex::motor& LF, 
    vex::motor& LB,
    vex::motor& RF,
    vex::motor& RB
    ): BaseChassis(LF, LB, RF, RB) {
    };

    Chassis() {};

    void setSpeed(float speed, vex::velocityUnits unit = vex::velocityUnits::pct) override {setFreeSpeed(speed, 0, 0, unit);}
    void setFreeSpeed(float x, float r, float y = 0, vex::velocityUnits unit = vex::velocityUnits::pct) override;
    void motorSpeedControl(vex::motor_group target, double expectedSpeed, vex::velocityUnits unit = vex::velocityUnits::pct) override;
private:
    Chassis(Chassis& rhs);
    Chassis(Chassis&& rhs);
};