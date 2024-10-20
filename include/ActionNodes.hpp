#pragma once
#include "Components/AutoNode.hpp"
#include "Systems/ControllerModule.hpp"

class MoveNode : public AutoNode {
public:
    MoveNode(float distance, float maxSpeed = 50.0, int maxTime = 2000):
    AutoNode(maxTime), _distance(distance), _maxSpeed(maxSpeed), _first(true) {}
    void complement() override;
private:
    float _distance;
    float _maxSpeed;
    vex::velocityUnits _unit;
    bool _first;
};

class DelayNode : public AutoNode {
public:
    DelayNode(float time);
    void complement() override;
private:
    float _time;
    float _startTime;
};