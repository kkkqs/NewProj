#pragma once

template<typename... Args>
class BasePredictor {
public:
    void virtual predict(const Args&... args) const = 0;
};
