#pragma once
#include "Algorithm/ControllerAlgorithm/BaseControllerAlgorithm.hpp"
#include "Components/Utils/HUSTFeedback.hpp"
#include "vex.h"

template<typename FeedbackType, typename OutputType>
class ControllerModule {
public:
    BaseControllerAlgorithm<FeedbackType, OutputType> *contorller;

    ControllerModule(BaseControllerAlgorithm<FeedbackType, OutputType> &contorller, HUSTFeedback<FeedbackType> &feedback):
    contorller(&contorller), _feedback(&feedback), _done(false) {}

    void reset() {
        feedbackReset();
        contorller->refresh();
        _done = false;
    }
    void setController(BaseControllerAlgorithm<FeedbackType, OutputType>& controller) {this->contorller = &controller;}
    void setTarget(float target) {contorller->setTarget(target);reset();}
    bool targetArrived() {return _done;}

    void virtual update() {
        FeedbackType nowFeedBack = getFeedback();
        contorller->update(nowFeedBack);
        OutputType value = contorller->getOutput();
        if (contorller->targetArrived()) _done = true;
    }
    
    FeedbackType getFeedback() {return _feedback->feedback();}
    OutputType getOutput() {return contorller->getOutput();}
protected:
    bool _done;
    HUSTFeedback<FeedbackType>* _feedback;
    void feedbackReset() {_feedback->reset();}
};