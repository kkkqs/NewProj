/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       suffix                                                    */
/*    Created:      8/25/2024, 9:45:45 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include "HUST.hpp"
#include "vex.h"
#include "RobotConfig.hpp"

// A global instance of competition
vex::competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // auto move1 = new MoveNode(500, 20000);
  // auto move2 = new MoveNode(-500, 20000);
  // auto move3 = new RotateNode();
  // move1->setNextNode(move2);

  // auto delay1 = new DelayNode(3000);
  // auto move3 = new MoveNode(400, 20000);
  // delay1->setNextNode(move3);

  // #pragma region JudgeNodeTest
  // auto move4 = new MoveNode(500, 20000);
  // auto distanceJudge = new DistanceJudgeNode(300, chassisControllerModule);
  // move4->addJuedgeNode(distanceJudge);
  // #pragma endregion

  // StateMachine::addAutoNode(move4);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

//
// Main will set up the competition functions and callbacks.
//

void mannualFuncs() {
  using namespace Mannual;
  MannualConfig::OrderUpdate();
  MannualMove(Controller.Axis3.position(), Controller.Axis1.position());
  MannualInput();
  MannualCircle();
  MannualCatchPlant();
}

int main() {
  CenterProcess::init();
  Input.setVelocity(100, vex::percentUnits::pct);
  // pre_auton();
  while (true) {
    CenterProcess::update();
    // StateMachine::handleNode();
    mannualFuncs();

    vex::wait(15, vex::timeUnits::msec);
  }
}
