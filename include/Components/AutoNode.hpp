#pragma once
#include <vector>
#include "Systems/StateMachine.hpp"
#include "Utils/HUSTTimer.hpp"

class JudgeNode {
public:
    bool virtual judge() = 0;
};

class AutoNode {
public:
    AutoNode(): _judgeList(std::vector<JudgeNode*>()), timer(HUSTTimer()), _done(false), _timeOut(false) {}
    AutoNode(int maxTime): _maxTime(maxTime), _judgeList(std::vector<JudgeNode*>()), timer(HUSTTimer()), _done(false), _timeOut(false) {}
    void virtual complement() = 0;
    void setNextNode(AutoNode* next);
    bool andJudge();
    bool orJudge();
    void addJuedgeNode(JudgeNode *node);
    bool timeOut() {return _timeOut;}
    bool done() {return _done;}
    void addNextNodes();
    ~AutoNode() {for (auto judgeNode : _judgeList) delete judgeNode;}
protected:
    bool _done;
    bool _timeOut;
    float _maxTime;
    HUSTTimer timer;
    std::vector<AutoNode*> _nextNodes;
    std::vector<JudgeNode*> _judgeList;
};