#include "Rook.hpp"
#include "Board.hpp"

Rook::Rook(bool white) : Piece(white) {}

char Rook::getChar() const {
    return isWhite ? 'R' : 'r';
}

bool Rook::isValidMove(Position from, Position to, const std::vector<std::vector<Piece*>>& board) {
    if (from.row != to.row && from.col != to.col)
        return false;

    int rowStep = (to.row - from.row) != 0 ? (to.row - from.row) / abs(to.row - from.row) : 0;
    int colStep = (to.col - from.col) != 0 ? (to.col - from.col) / abs(to.col - from.col) : 0;

    int r = from.row + rowStep, c = from.col + colStep;
    while (r != to.row || c != to.col) {
        if (board[r][c] != nullptr)
            return false;
        r += rowStep;
        c += colStep;
    }
    return true;
}

std::vector<Position> Rook::getLegalMoves(const Board& board, const Position& from) const {
    std::vector<Position> moves;
    const std::vector<std::pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
    for (auto [dr, dc] : dirs) {
        int r = from.row + dr, c = from.col + dc;
        while (Board::inBounds(r, c)) {
            Piece* p = board.getPiece(r, c);
            if (!p) {
                moves.emplace_back(r, c);
            } else {
                if (p->getColor() != this->getColor())
                    moves.emplace_back(r, c);
                break;
            }
            r += dr;
            c += dc;
        }
    }
    return moves;
}