#include "King.hpp"
#include "Board.hpp"

King::King(bool white) : Piece(white) {}

char King::getChar() const {
    return isWhite ? 'K' : 'k';
}

bool King::isValidMove(Position from, Position to, const std::vector<std::vector<Piece*>>& board) {
    int rowDiff = abs(from.row - to.row);
    int colDiff = abs(from.col - to.col);
    return rowDiff <= 1 && colDiff <= 1;
}

std::vector<Position> King::getLegalMoves(const Board& board, const Position& from) const {
    std::vector<Position> moves;
    for (int dr = -1; dr <= 1; ++dr)
        for (int dc = -1; dc <= 1; ++dc)
            if (dr != 0 || dc != 0) {
                int r = from.row + dr, c = from.col + dc;
                if (Board::inBounds(r, c)) {
                    Piece* p = board.getPiece(r, c);
                    if (!p || p->getColor() != this->getColor())
                        moves.emplace_back(r, c);
                }
            }
    return moves;
}