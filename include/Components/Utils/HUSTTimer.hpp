#pragma once

class HUSTTimer
{
private:
    int time;

public:
    HUSTTimer(): time(int(0)) {};
    void reset() {time = 0;};
    void click();
    int getTimeMsec() const {return time;};
    float getTimeSec() const {return time / 1000.0f;}
    void subClick(int delta) {time -= delta;}
};