#pragma once
#include "Components/Singleton.hpp"
#include "RobotConfig.hpp"

class CenterProcess: Singleton<CenterProcess> {
public:
    static void init() {
        _nowTimeMsec = _brain->timer(vex::timeUnits::msec);
        _lstTimeMsec = _nowTimeMsec;
    }
    static void update() {
        _lstTimeMsec = _nowTimeMsec;
        _nowTimeMsec = _brain->timer(vex::timeUnits::msec);
    }
    static int deltaTimeMsec() {
        return _nowTimeMsec - _lstTimeMsec;
    }
    static int outputDeltaTimeMsec() {
        return _outputDeltaTimeMsec;
    }
    static int getNowTimeMsec() {
        return _nowTimeMsec;
    }
private:
    static int _nowTimeMsec;
    static int _lstTimeMsec;
    const static int _outputDeltaTimeMsec;
    static vex::brain* _brain;
};