#include "Systems/CenterProcess.hpp"

vex::brain* CenterProcess::_brain = &Brain;
const int CenterProcess::_outputDeltaTimeMsec = 100;
int CenterProcess::_nowTimeMsec = 0;
int CenterProcess::_lstTimeMsec = 0;