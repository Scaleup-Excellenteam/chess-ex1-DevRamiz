#pragma once
#include <vector>
#include <string>
#include "Position.hpp"

class Board;

class Piece {
protected:
    bool isWhite;
public:
    Piece(bool white);
    virtual ~Piece();
    virtual char getChar() const = 0;
    virtual bool isValidMove(Position from, Position to,
                             const std::vector<std::vector<Piece*>>& board) = 0;

    bool getColor() const;
    virtual std::vector<Position> getLegalMoves(const Board& board, const Position& from) const = 0;
};