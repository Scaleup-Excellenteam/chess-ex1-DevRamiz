#include "Queen.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Board.hpp"

Queen::Queen(bool white) : Piece(white) {}

char Queen::getChar() const {
    return isWhite ? 'Q' : 'q';
}

bool Queen::isValidMove(Position from, Position to, const std::vector<std::vector<Piece*>>& board) {
    Rook rookLike(isWhite);
    Bishop bishopLike(isWhite);
    return rookLike.isValidMove(from, to, board) || bishopLike.isValidMove(from, to, board);
}

std::vector<Position> Queen::getLegalMoves(const Board& board, const Position& from) const {
    std::vector<Position> moves;
    const std::vector<std::pair<int,int>> dirs = {
            {1,1},{1,-1},{-1,1},{-1,-1}, {1,0},{-1,0},{0,1},{0,-1}
    };
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