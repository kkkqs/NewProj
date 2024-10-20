#include "Algorithm/ControllerAlgorithm/PIDControllerAlgorithm.hpp"

void PIDControllerAlgorithm::update(float input) {
    errorCurt = target - input;
    P = kp * errorCurt;
    if (firstTime) {
        firstTime = false;
        errorPrev = errorCurt;
        errorInt = 0;
    }
    errorDev = errorCurt - errorPrev;
    errorPrev = errorCurt;
    D = kd * errorDev;
    if (fabs(P) >= IRange) {
        errorInt = 0;
    } else {
        errorInt += errorCurt;
        if (fabs(errorInt) * ki > IMax)
            errorInt = sign(errorInt) * IMax / ki;
    }
    if (sign(errorInt) != sign(errorCurt) || fabs(errorCurt) <= errorTol) errorInt = 0;
    I = ki * errorInt;
    if (fabs(errorCurt) <= errorTol && fabs(D) <= DTol) {
        arrived = true;
    } else {
        arrived = false;
    }
    output = P + I + D;
}