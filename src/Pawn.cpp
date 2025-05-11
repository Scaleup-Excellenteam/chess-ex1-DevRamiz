#include "Pawn.hpp"
#include "Position.hpp"
#include "Board.hpp"

Pawn::Pawn(bool white) : Piece(white) {}

char Pawn::getChar() const {
    return isWhite ? 'P' : 'p';  // White = uppercase, Black = lowercase
}

bool Pawn::isValidMove(Position from, Position to, const std::vector<std::vector<Piece*>>& board) {
    int dir = isWhite ? 1 : -1;
    int startRow = isWhite ? 1 : 6;

    // Move forward one square
    if (from.col == to.col && to.row == from.row + dir && board[to.row][to.col] == nullptr)
        return true;

    // Move forward two squares from starting row
    if (from.col == to.col &&
        from.row == startRow &&
        to.row == from.row + 2 * dir &&
        board[from.row + dir][to.col] == nullptr &&
        board[to.row][to.col] == nullptr)
        return true;

    // Capture diagonally
    if (abs(from.col - to.col) == 1 &&
        to.row == from.row + dir &&
        board[to.row][to.col] &&
        board[to.row][to.col]->getColor() != isWhite)
        return true;

    return false;
}

std::vector<Position> Pawn::getLegalMoves(const Board& board, const Position& from) const {
    std::vector<Position> moves;
    int dir = isWhite ? 1 : -1;
    int startRow = isWhite ? 1 : 6;
    int r = from.row + dir;

    if (Board::inBounds(r, from.col) && !board.getPiece(r, from.col))
        moves.emplace_back(r, from.col);

    if (from.row == startRow && Board::inBounds(r + dir, from.col)
        && !board.getPiece(r, from.col)
        && !board.getPiece(r + dir, from.col))
        moves.emplace_back(r + dir, from.col);

    for (int dc : {-1, +1}) {
        int c = from.col + dc;
        if (Board::inBounds(r, c)) {
            Piece* p = board.getPiece(r, c);
            if (p && p->getColor() != this->getColor())
                moves.emplace_back(r, c);
        }
    }

    return moves;
}