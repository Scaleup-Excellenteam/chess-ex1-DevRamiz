#pragma once
#include "Position.hpp"

inline std::string squareToUI(const Position& p)
{
    return { char('A' + p.row), char('1' + p.col) };
}
