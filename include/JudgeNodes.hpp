#pragma once
#include "Components/AutoNode.hpp"
#include "Systems/ControllerModule.hpp"

class DistanceJudgeNode : public JudgeNode {
public:
    DistanceJudgeNode(float distance, ControllerModule<float, float>& feedbackModule);
    bool judge() override;
private:
    float _distance;
    ControllerModule<float, float> _feedBackModule;
};