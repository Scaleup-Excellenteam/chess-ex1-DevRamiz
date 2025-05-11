#pragma once
#include "Piece.hpp"

class Bishop : public Piece {
public:
    Bishop(bool white);
    char getChar() const override;
    bool isValidMove(Position from, Position to, const std::vector<std::vector<Piece*>>& board) override;
    std::vector<Position> getLegalMoves(const Board& board, const Position& from) const override;
};