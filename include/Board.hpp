#pragma once
#include <vector>
#include <string>
#include "Piece.hpp"
#include "Position.hpp"

class Board {
    std::vector<std::vector<Piece*>> board;
    bool whiteTurn;
    void setupPieces();
    bool isCheck(bool white) const;
    Position findKing(bool white) const;
    bool whiteToMove_ = true;
public:
    Board();
    ~Board();
    int move(const std::string& fromStr, const std::string& toStr);
    void printBoard() const;
    Piece* getPiece(int r, int c)         const { return board[r][c]; }
    bool   whiteToMove()                  const { return whiteTurn;   }
    Piece* execute(const std::string& from, const std::string& to);
    void   undo(const std::string& from, const std::string& to, Piece* captured);
    static bool inBounds(int row, int col);
};