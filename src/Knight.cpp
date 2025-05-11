#include "Knight.hpp"
#include "Board.hpp"

Knight::Knight(bool white) : Piece(white) {}

char Knight::getChar() const {
    return isWhite ? 'N' : 'n';
}

bool Knight::isValidMove(Position from, Position to, const std::vector<std::vector<Piece*>>& board) {
    int rowDiff = abs(from.row - to.row);
    int colDiff = abs(from.col - to.col);
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}

std::vector<Position> Knight::getLegalMoves(const Board& board, const Position& from) const {
    std::vector<Position> moves;
    const std::vector<std::pair<int,int>> jumps = {
            {-2, -1}, {-2, +1}, {-1, -2}, {-1, +2},
            {+1, -2}, {+1, +2}, {+2, -1}, {+2, +1}
    };
    for (auto [dr, dc] : jumps) {
        int r = from.row + dr, c = from.col + dc;
        if (Board::inBounds(r, c)) {
            Piece* p = board.getPiece(r, c);
            if (!p || p->getColor() != this->getColor())
                moves.emplace_back(r, c);
        }
    }
    return moves;
}