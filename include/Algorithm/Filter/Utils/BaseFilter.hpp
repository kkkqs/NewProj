#pragma once
#include "BaseInitializer.hpp"
#include "BasePredictor.hpp"

template <typename Initializer, typename Predictor>
class BaseFilter {
public:
    const Initializer* FilterInitializer;
    const Predictor* FilterPredictor;
    
    float virtual getResult() const = 0;
};