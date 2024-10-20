#pragma once

template<typename T>
class HUSTFeedback {
public:
    HUSTFeedback() {}
    T virtual feedback() = 0;
    void virtual reset() = 0;
};