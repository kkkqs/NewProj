#include "Mannual.hpp"

namespace Mannual {
    int MannualConfig::pressInputIn = 0;
    int MannualConfig::pressInputOut = 0;
    int MannualConfig::pressCircle = 0;
    int MannualConfig::pressCatchPlant = 0;
    int MannualConfig::pressChange = 0;
    
    int MannualConfig::circleReverseTime = 400;
    float MannualConfig::circleReverseTorque = 0.6f;
    float MannualConfig::circleForwardSpeed = 200.0f;
    float MannualConfig::circleReverseSpeed = 50.0f;

    int MannualConfig::clawUpTime = 2500;
    int MannualConfig::clawDownTime = 2000;
    float MannualConfig::clawUpSpeed = 15.0f;
    float MannualConfig::clawDownSpeed = 15.0f;
    float MannualConfig::clawUpStopTorque = 0.5f;
    float MannualConfig::clawDownStopTorque = 0.35f;
    int MannualConfig::changeif = 0;

    void MannualMove(float speedX, float speedY) {
        if (std::abs(speedX) < 5.0 && std::abs(speedY) < 5.0) {
            chassis.stop();
            return;
        }
        enum Status {
            Forward,
            Reverse
        };
        static Status status = Status::Forward;
        static int A = 0;
        A = MannualConfig::pressChange;
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
        chassis.setFreeSpeed(speedX, speedY);
        chassis.move();
    }
    void MannualInput() {
        enum Status {
            Idle,
            Forward,
            Reverse
        };
        static Status status = Status::Idle;
        static bool A = 0, B = 0;
        A = MannualConfig::pressInputIn;
        B = MannualConfig::pressInputOut;
        Input.setVelocity(200, vex::percentUnits::pct);
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
    void MannualCircle() {
        enum Status {
            Idle,
            Input,
            Back,
        };
        static Status status = Status::Idle;
        static HUSTTimer timer;
        static int A = 0;
        A = MannualConfig::pressCircle;
        switch (status) {
            case Status::Idle:
                if (A) {
                    status = Status::Input;

                    Circle.setVelocity(Mannual::MannualConfig::circleForwardSpeed, vex::percentUnits::pct);
                    Circle.spin(vex::directionType::fwd);
                }
                break;
            case Status::Input:
                if (A) {
                    status = Status::Idle;
                    Circle.stop();
                } else {
                    if (Circle.torque(vex::torqueUnits::Nm) > MannualConfig::circleReverseTorque) {
                        timer.reset();
                        Circle.setVelocity(MannualConfig::circleReverseSpeed, vex::percentUnits::pct);
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
                    if (timer.getTimeMsec() >= MannualConfig::circleReverseTime) {
                        timer.reset();
                        Circle.setVelocity(MannualConfig::circleForwardSpeed, vex::percentUnits::pct);
                        Circle.spin(vex::directionType::fwd);
                        status = Status::Input;
                    }
                }
        }
    }
    void MannualCatchPlant() {
        enum Status {
            Idle,
            Catching,
            Hold,
            Leaving
        };
        static Status status = Status::Idle;
        static int A = 0;
        static HUSTTimer timer;
        A = MannualConfig::pressCatchPlant;
        printf("%d\n", timer.getTimeMsec());
        switch (status) {
            case Status::Idle:
                if (A) {
                    status = Status::Catching;
                    ClawSwitchL.set(true);
                    ClawSwitchR.set(true);
                    Claw.setVelocity(MannualConfig::clawUpSpeed, vex::percentUnits::pct);
                    Claw.spin(forward);
                }
                break;
            case Status::Catching:
                if (timer.getTimeMsec() >= MannualConfig::clawUpTime || Claw.torque() > MannualConfig::clawUpStopTorque) {
                    Claw.stop();
                    status = Status::Hold;
                }
                break;
            case Status::Hold:
                if (A) {
                    status = Status::Leaving;
                    ClawSwitchL.set(false);
                    ClawSwitchR.set(false);
                    Claw.setVelocity(MannualConfig::clawDownSpeed, vex::percentUnits::pct);
                    Claw.spin(reverse);

                    timer.reset();
                }
                break;
            case Status::Leaving:
                timer.click();
                if (timer.getTimeMsec() >= MannualConfig::clawDownTime || Claw.torque() > MannualConfig::clawDownStopTorque) {
                    Claw.stop();
                    status = Status::Idle;
                }
                break;
        }
    }
}