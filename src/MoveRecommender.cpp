#include "MoveRecommender.hpp"
#include "Position.hpp"
#include <algorithm>
#include <thread>

MoveRecommender::MoveRecommender(Board& b, int depth)
        : board(b), maxDepth(depth) {}

int MoveRecommender::materialValue(char p) const {
    switch (tolower(p)) {
        case 'p': return 1;
        case 'n': return 3;
        case 'b': return 3;
        case 'r': return 5;
        case 'q': return 9;
        case 'k': return 100;
        default: return 0;
    }
}

int MoveRecommender::evaluateMove(const std::string& from, const std::string& to, int depth) {
    Piece* captured = board.execute(from, to);
    int score = 0;

    score += materialValue(captured ? captured->getChar() : 0);
    score += centreBonus(Position(to));
    score += coveredSquaresDiff(!board.whiteToMove());

    if (depth < maxDepth) {
        std::vector<std::pair<std::string, std::string>> replies;
        collectMoves(board.whiteToMove(), replies);
        for (const auto& mv : replies) {
            int replyScore = evaluateMove(mv.first, mv.second, depth + 1);
            score -= replyScore;
        }
    }

    board.undo(from, to, captured);
    return score;
}

void MoveRecommender::collectMoves(bool white, std::vector<std::pair<std::string, std::string>>& moves) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* piece = board.getPiece(r, c);
            if (!piece || piece->getColor() != white) continue;

            Position from(r, c);
            auto legalMoves = piece->getLegalMoves(board, from);
            for (Position to : legalMoves) {
                moves.emplace_back(from.toString(), to.toString());
            }
        }
    }
}

Move MoveRecommender::recommend() {
    top5 = {};
    std::vector<std::pair<std::string, std::string>> moves;
    collectMoves(board.whiteToMove(), moves);

    for (const auto& mv : moves) {
        int s = evaluateMove(mv.first, mv.second, 0);
        top5.push({ Position(mv.first), Position(mv.second), s });
        if (top5.size() > 5) top5.poll();
    }

    return top5.empty() ? Move() : top5.top();
}

std::vector<Move> MoveRecommender::topMoves() {
    std::vector<Move> out;
    while (!top5.empty()) out.push_back(top5.poll());
    return out;
}

int MoveRecommender::centreBonus(Position p) const
{
    if (p.row >= 3 && p.row <= 4 && p.col >= 3 && p.col <= 4) return 20;
    if (p.row >= 2 && p.row <= 5 && p.col >= 2 && p.col <= 5) return 10;
    return 0;
}

int MoveRecommender::coveredSquaresDiff(bool white) const
{
    int score = 0;
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c) {
            Piece* pc = board.getPiece(r, c);
            if (!pc || pc->getColor() != white) continue;
            score += static_cast<int>(pc->getLegalMoves(board, {r,c}).size());
        }
    return score;
}