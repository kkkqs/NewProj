#include "JudgeNodes.hpp"

DistanceJudgeNode::DistanceJudgeNode(float distance, ControllerModule<float, float>& feedbackModule):
_distance(distance), _feedBackModule(feedbackModule) {}

bool DistanceJudgeNode::judge() {
    return _feedBackModule.getFeedback() > _distance;
}