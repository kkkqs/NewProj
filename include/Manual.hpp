#pragma once
#include "RobotConfig.hpp"
#include "Components/Utils/HUSTTimer.hpp"

namespace Manual {
    void ManualMove(float speedX, float speedY);
    void ManualInput();
    void ManualCircle();
    void ManualCatchPlant();

    class ManualConfig {
    public:
        static int pressInputIn;
        static int pressInputOut;
        static int pressCircle;
        static int pressCatchPlant;
        static int pressChange;

        static void OrderUpdate() {
            pressInputIn = int(Controller.ButtonA.PRESSED);
            pressInputOut = int(Controller.ButtonB.PRESSED);
            pressCircle = int(Controller.ButtonX.PRESSED);
            pressCatchPlant = int(Controller.ButtonL1.PRESSED);
            pressChange = int(Controller.ButtonY.PRESSED);
        }
        
        static int circleReverseTime;
        static float circleReverseTorque;
        static float circleForwardSpeed;
        static float circleReverseSpeed;

        static int clawUpTime;
        static int clawDownTime;
        static float clawUpSpeed;
        static float clawDownSpeed;
        static float clawDownStopTorque;
        static float clawUpStopTorque;

        static int changeif;
    };
}