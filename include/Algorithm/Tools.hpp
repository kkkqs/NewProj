#pragma once

inline int sign(float x) {
    return x < 0 ? -1 : x == 0 ? 0 : 1;
}