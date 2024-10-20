#pragma once

template<typename InputType, typename OutputType>
class BaseControllerAlgorithm {
protected:
    bool firstTime;
    bool arrived;
    OutputType output;
    OutputType target;

public:
    BaseControllerAlgorithm(bool firstTime = true, bool arrived = false): firstTime(true), arrived(false) {}
    void refresh() {firstTime = true, arrived = false;}    
    void setTarget(OutputType _target) {target = _target;}
    bool targetArrived() {return arrived;}
    OutputType getOutput() {return output;}

    void virtual update(InputType input) = 0;
};