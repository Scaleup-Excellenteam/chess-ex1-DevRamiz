#pragma once
#include <string>

struct Position {
    int row, col;
    Position(std::string pos);
    Position(int r, int c);
    std::string toString() const {
        return std::string{char('a' + col)} + char('1' + row);
    }
};