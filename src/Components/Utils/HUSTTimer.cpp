#include "Components/Utils/HUSTTimer.hpp"
#include "Systems/CenterProcess.hpp"

void HUSTTimer::click() {
    time += CenterProcess::deltaTimeMsec();
}