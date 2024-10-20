#pragma once
#include "Components/AutoNode.hpp"
#include "Components/Singleton.hpp"

class AutoNode;

class StateMachine: Singleton<StateMachine> {
public:
    static void addAutoNode(AutoNode* node);
    static void handleNode();
private:
    static std::vector<AutoNode*> _list;
    static std::vector<AutoNode*> _nextAddList;
};