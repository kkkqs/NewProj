#include "Manual.hpp"

namespace Manual {
    int ManualConfig::pressInputIn = 0;
    int ManualConfig::pressInputOut = 0;
    int ManualConfig::pressCircle = 0;
    int ManualConfig::pressCatchPlant = 0;
    int ManualConfig::pressChange = 0;
    
    int ManualConfig::circleReverseTime = 400;
    float ManualConfig::circleReverseTorque = 0.6f;
    float ManualConfig::circleForwardSpeed = 200.0f;
    float ManualConfig::circleReverseSpeed = 50.0f;

    int ManualConfig::clawUpTime = 2500;
    int ManualConfig::clawDownTime = 2000;
    float ManualConfig::clawUpSpeed = 15.0f;
    float ManualConfig::clawDownSpeed = 15.0f;
    float ManualConfig::clawUpStopTorque = 0.5f;
    float ManualConfig::clawDownStopTorque = 0.35f;
    int ManualConfig::changeif = 0;

    void ManualMove(float speedX, float speedY) {
        enum Status {
            Forward,
            Reverse
        };
        static Status status = Status::Forward;
        static int A = 0;
        A = ManualConfig::pressChange;
        printf("%d\n", status);
        switch (status){
            case Status::Forward:
                if (A) status = Status::Reverse;
                break;
            case Status::Reverse:
                speedX = -speedX;
                if (A) status = Status::Forward;
                break;
            default:
                break;
        }
        if (std::abs(speedX) < 5.0 && std::abs(speedY) < 5.0) {
            chassis.stop();
            return;
        }
        chassis.setFreeSpeed(speedX, speedY);
        chassis.move();
    }
    void ManualInput() {
        enum Status {
            Idle,
            Forward,
            Reverse
        };
        static Status status = Status::Idle;
        static bool A = 0, B = 0;
        A = ManualConfig::pressInputIn;
        B = ManualConfig::pressInputOut;
        // printf("x\n");
        switch (status) {
            case Status::Idle:
                if (A) {
                    Input.spin(vex::directionType::fwd);
                    status = Status::Forward;
                } else if (B) {
                    Input.spin(vex::directionType::rev);
                    status = Status::Reverse;
                }
                break;
            case Status::Forward:
                if (A) {
                    Input.stop();
                    status = Status::Idle;
                } else if (B) {
                    Input.spin(vex::directionType::rev);
                    status = Status::Reverse;
                }
                break;
            case Status::Reverse:
                // printf("3", status);
                if (A) {
                    Input.spin(vex::directionType::fwd);
                    status = Status::Forward;
                } else if (B) {
                    Input.stop();
                    status = Status::Idle;
                }
                break;
            default:
                printf("?");
        }
    }
    void ManualCircle() {
        enum Status {
            Idle,
            Input,
            Back,
        };
        static Status status = Status::Idle;
        static HUSTTimer timer;
        static int A = 0;
        A = ManualConfig::pressCircle;
        switch (status) {
            case Status::Idle:
                if (A) {
                    status = Status::Input;

                    Circle.setVelocity(Manual::ManualConfig::circleForwardSpeed, vex::percentUnits::pct);
                    Circle.spin(vex::directionType::fwd);
                }
                break;
            case Status::Input:
                if (A) {
                    status = Status::Idle;
                    Circle.stop();
                } else {
                    if (Circle.torque(vex::torqueUnits::Nm) > ManualConfig::circleReverseTorque) {
                        timer.reset();
                        Circle.setVelocity(ManualConfig::circleReverseSpeed, vex::percentUnits::pct);
                        Circle.spin(vex::directionType::rev);
                        status = Status::Back;
                    }
                }
                break;
            case Status::Back:
                timer.click();
                if (A) {
                    status = Status::Idle;
                    Circle.stop();
                } else {
                    if (timer.getTimeMsec() >= ManualConfig::circleReverseTime) {
                        timer.reset();
                        Circle.setVelocity(ManualConfig::circleForwardSpeed, vex::percentUnits::pct);
                        Circle.spin(vex::directionType::fwd);
                        status = Status::Input;
                    }
                }
        }
    }
    void ManualCatchPlant() {
        enum Status {
            Idle,
            Catching,
            Hold,
            Leaving
        };
        static Status status = Status::Idle;
        static int A = 0;
        static HUSTTimer timer;
        A = ManualConfig::pressCatchPlant;
        // printf("%d\n", timer.getTimeMsec());
        switch (status) {
            case Status::Idle:
                if (A) {
                    status = Status::Catching;
                    ClawSwitchL.set(true);
                    ClawSwitchR.set(true);
                    Claw.setVelocity(ManualConfig::clawUpSpeed, vex::percentUnits::pct);
                    Claw.spin(forward);
                }
                break;
            case Status::Catching:
                if (timer.getTimeMsec() >= ManualConfig::clawUpTime || Claw.torque() > ManualConfig::clawUpStopTorque) {
                    Claw.stop();
                    status = Status::Hold;
                }
                break;
            case Status::Hold:
                if (A) {
                    status = Status::Leaving;
                    ClawSwitchL.set(false);
                    ClawSwitchR.set(false);
                    Claw.setVelocity(ManualConfig::clawDownSpeed, vex::percentUnits::pct);
                    Claw.spin(reverse);

                    timer.reset();
                }
                break;
            case Status::Leaving:
                timer.click();
                if (timer.getTimeMsec() >= ManualConfig::clawDownTime || Claw.torque() > ManualConfig::clawDownStopTorque) {
                    Claw.stop();
                    status = Status::Idle;
                }
                break;
        }
    }
}