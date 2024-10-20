#include "Systems/StateMachine.hpp"

std::vector<AutoNode*> StateMachine::_list = std::vector<AutoNode*>();
std::vector<AutoNode*> StateMachine::_nextAddList = std::vector<AutoNode*>();

void StateMachine::handleNode() {
    std::vector<AutoNode*>::iterator _nextDel = _list.end();
    for (auto it = _list.begin(); it != _list.end(); it++) {
        auto node = *it;
        node->complement();
        if (node->done()) _nextDel = it;
    }
    if (_nextDel != _list.end()) {
        auto node = *_nextDel;
        node->addNextNodes();
        delete node;
        _list.erase(_nextDel);
    }
    while (!_nextAddList.empty()) {
        _list.push_back(_nextAddList.back());
        _nextAddList.erase(_nextAddList.begin());
    }
}


void StateMachine::addAutoNode(AutoNode* node) {
    _nextAddList.push_back(node);
}