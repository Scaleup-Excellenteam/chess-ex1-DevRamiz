#pragma once
#include "Position.hpp"

struct Move {
    Position from;
    Position to;
    int      score;          // higher is better
};

struct MoveComparator {
    bool operator()(const Move& a, const Move& b) const {
        return a.score > b.score;
    }
};