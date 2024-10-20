/**
  ******************************************************************************
  * @file           : robot-config.cpp
  * @brief          : ??????????????????????��??????????????????????????
  ******************************************************************************
  * @attention     :
  *
  *
  ******************************************************************************
  */

#include "RobotConfig.hpp"
#include "HUST.hpp"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen
// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::controller Controller;
vex::rotation r1(vex::PORT6, true);
vex::rotation r2(vex::PORT5);
vex::inertial imu(vex::PORT7);

vex::motor LFU(vex::PORT20, true);
vex::motor LFD(vex::PORT15, false);
vex::motor RFU(vex::PORT13, false);
vex::motor RFD(vex::PORT14, true);

vex::motor LBU(vex::PORT7, true);
vex::motor LBD(vex::PORT6, false);
vex::motor RBU(vex::PORT4, false);
vex::motor RBD(vex::PORT5, true);

vex::motor_group LF(LFU, LFD);
vex::motor_group LB(LBU, LBD);
vex::motor_group RF(RFU, RFD);
vex::motor_group RB(RBU, RBD);

vex::motor InputL(vex::PORT1, true);
vex::motor InputR(vex::PORT11, false);
vex::motor_group Input(InputL, InputR);

vex::motor CircleMain(vex::PORT12, true);
vex::motor_group Circle(CircleMain);

vex::motor ClawL(vex::PORT2, true);
vex::motor ClawR(vex::PORT3, false);
vex::digital_out ClawSwitchL(Brain.ThreeWirePort.A);
vex::digital_out ClawSwitchR(Brain.ThreeWirePort.B);
vex::motor_group Claw(ClawL, ClawR); // forward -> up, recerse -> down

#pragma region Chassis
Chassis chassis(LF, LB, RF, RB);
PIDControllerAlgorithm chassisPID(0.8f, 0.2f, 0.01f);
RotationFeedback chassisFeedback(r1);
ControllerModule<float, float> chassisControllerModule(chassisPID, chassisFeedback);
// KalmanFilter chassisKFilter;
#pragma endregion

// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;