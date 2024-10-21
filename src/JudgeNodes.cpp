#include "JudgeNodes.hpp"

DistanceJudgeNode::DistanceJudgeNode(float distance, ControllerModule<float, float>& feedbackModule):
_distance(distance), _feedBackModule(feedbackModule) {}

bool DistanceJudgeNode::judge() {
    return _feedBackModule.getFeedback() > _distance;
}


ColorJudgeNode::ColorJudgeNode(int color, ControllerModule<int, int>& feedbackModule):
_color(color), _feedBackModule(feedbackModule) {}

bool ColorJudgeNode::judge() {
    return ( (_feedBackModule.getFeedback() >= (_color - 30)) && (_feedBackModule.getFeedback() <= (_color + 30)) );
}
