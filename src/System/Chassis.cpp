#include "Systems/Chassis.hpp"

void Chassis::setFreeSpeed(float x, float r, float y, vex::velocityUnits unit) {
    // for (size_t i = 0; i < motorGroups.size(); i++) {
    //     if (i & 1) motorGroups[i].setSpeed(x - r, unit);
    //     else motorGroups[i].setSpeed(x + r, unit);
    // }
    size_t len = motorGroups.size() / 2, i = 0;
    for (i = 0; i < len; i++) motorGroups[i].setSpeed(x - r, unit);
    for (; i < motorGroups.size(); i++) motorGroups[i].setSpeed(x + r, unit);
}

void Chassis::motorSpeedControl(vex::motor_group target, double expectedSpeed, vex::velocityUnits unit) {
    
}