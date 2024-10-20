#include "Components/AutoNode.hpp"

void AutoNode::addNextNodes() {
    for (auto node : _nextNodes) {
        StateMachine::addAutoNode(node);
    }
}

void AutoNode::setNextNode(AutoNode *next) {
    _nextNodes.push_back(next);
}

bool AutoNode::orJudge() {
    bool ret = false;
    for (auto node : _judgeList) {
        ret |= node->judge();
    }
    return ret;
}

bool AutoNode::andJudge() {
    bool ret = true;
    for (auto node : _judgeList) {
        ret &= node->judge();
    }
    return ret;
}

void AutoNode::addJuedgeNode(JudgeNode* node) {
    _judgeList.push_back(node);
}