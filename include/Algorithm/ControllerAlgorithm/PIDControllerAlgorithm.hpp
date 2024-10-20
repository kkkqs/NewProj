#pragma once
#include <cmath>
#include "Algorithm/Tools.hpp"
#include "BaseControllerAlgorithm.hpp"

class PIDControllerAlgorithm: public BaseControllerAlgorithm<float, float> {
protected:
    float errorCurt, errorPrev, errorDev, errorInt;
    float P, I, D;
    float kp, ki, kd;
    float errorTol, DTol;
    float IMax, IRange;
public:
    PIDControllerAlgorithm(): BaseControllerAlgorithm(true, false), IMax(20), IRange(50), errorTol(5), DTol(2) {}
    PIDControllerAlgorithm(float kp, float ki, float kd): BaseControllerAlgorithm(true, false), kp(kp), ki(ki), kd(kd), IMax(20), IRange(50), errorTol(5), DTol(2) {}
    void setIMax(float _IMax) {IMax = _IMax;}
    void setIRange(float _IRange) {IRange = _IRange;}
    void setErrorTolerance(float _errorTol) {errorTol = _errorTol;}
    void setDTolerance(float _DTol){DTol = _DTol;}
    void setCoefficient(float _kp, float _ki, float _kd) {kp = _kp; ki = _ki; kd = _kd;}

    void update(float input) override;
};