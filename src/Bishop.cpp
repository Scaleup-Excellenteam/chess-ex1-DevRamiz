#include "Bishop.hpp"
#include "Board.hpp"

Bishop::Bishop(bool white) : Piece(white) {}

char Bishop::getChar() const {
    return isWhite ? 'B' : 'b';
}

bool Bishop::isValidMove(Position from, Position to, const std::vector<std::vector<Piece*>>& board) {
    int rowDiff = abs(from.row - to.row);
    int colDiff = abs(from.col - to.col);

    if (rowDiff != colDiff)
        return false;

    int rowStep = (to.row - from.row) / rowDiff;
    int colStep = (to.col - from.col) / colDiff;

    int r = from.row + rowStep, c = from.col + colStep;
    while (r != to.row || c != to.col) {
        if (board[r][c] != nullptr)
            return false;
        r += rowStep;
        c += colStep;
    }

    return true;
}

std::vector<Position> Bishop::getLegalMoves(const Board& board, const Position& from) const {
    std::vector<Position> moves;
    const std::vector<std::pair<int,int>> dirs = {{1,1},{1,-1},{-1,1},{-1,-1}};
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