#include "ActionNodes.hpp"
#include "Systems/CenterProcess.hpp"
#include "RobotConfig.hpp"

void MoveNode::complement() {
    if (_first) {
        chassisControllerModule.reset();
        chassisControllerModule.setTarget(_distance);
        _first = false;
    }
    
    if (andJudge()) _maxSpeed /= 2.0f;

    chassisControllerModule.update();
    auto value = chassisControllerModule.getOutput();
    value = fmin(fabs(value), 100) * sign(value) * _maxSpeed;
    chassis.setSpeed(value, _unit);
    _done = chassisControllerModule.targetArrived();
    timer.click();
    if (_done) chassis.stop();
    else chassis.move();

    if (timer.getTimeMsec() > _maxTime) {
        printf("Out Of Time");
        _timeOut = true;
        _done = true;
        chassis.stop();
    }
}

void RotateNode::complement() {
    if (_first) {
        chassisRotationModule.reset();
        chassisRotationModule.setTarget(_angle);
        _first = false;
    }
    
    if (andJudge()) _maxSpeed /= 2.0f;

    chassisRotationModule.update();
    auto value = chassisRotationModule.getOutput();
    value = fmin(fabs(value), 100) * sign(value) * _maxSpeed;
    chassis.setSpeed(value, _unit);
    _done = chassisRotationModule.targetArrived();
    timer.click();
    if (_done) chassis.stop();
    else chassis.rotate();

    if (timer.getTimeMsec() > _maxTime) {
        printf("Out Of Time");
        _timeOut = true;
        _done = true;
        chassis.stop();
    }
}

void DelayNode::complement() {
    if (CenterProcess::getNowTimeMsec() - _startTime > _time) {
        _done = true;
    }
}

DelayNode::DelayNode(float time):_time(time) {
    _startTime = CenterProcess::getNowTimeMsec();
}