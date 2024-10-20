#pragma once
#include "vex.h"
#include "Algorithm/ControllerAlgorithm/PIDControllerAlgorithm.hpp"
#include "Algorithm/Filter/KalmanFilter.hpp"
#include "Systems/Chassis.hpp"
#include "Systems/ControllerModule.hpp"

using namespace vex;

extern vex::brain       Brain;
extern vex::controller Controller;
extern vex::rotation r1;
extern vex::rotation r2;
extern vex::inertial imu;

extern vex::motor_group Input;
extern vex::motor_group Circle;

extern vex::digital_out ClawSwitchL;
extern vex::digital_out ClawSwitchR;
extern vex::motor_group Claw; // forward -> up, recerse -> down

extern Chassis chassis;
extern ControllerModule<float, float> chassisControllerModule;
extern KalmanFilter KFilter;