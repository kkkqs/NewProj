#pragma once

template<typename... Args>
class BaseInitializer {
public:
    void virtual initialize(const Args&... args) const = 0;
};