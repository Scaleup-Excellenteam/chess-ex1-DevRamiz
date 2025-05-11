#include "MoveRecommender.hpp"
#include "ChessExceptions.hpp"
#include <limits>
#include <iostream>
#include <algorithm>

// Convert internal Position to board notation using your flipped layout
static std::string squareToUI(const Position& p) {
    return { char('a' + p.col), char('A' + p.row) };
}

MoveRecommender::MoveRecommender(Board& b, int depth)
        : board(b), maxDepth(depth) {}

int MoveRecommender::materialValue(char p) const {
    switch(std::tolower(p)){
        case 'p': return 1;
        case 'n': return 3;
        case 'b': return 3;
        case 'r': return 5;
        case 'q': return 9;
        case 'k': return 1000;
        default : return 0;
    }
}

void MoveRecommender::collectMoves(bool white,
                                   std::vector<std::pair<std::string,std::string>>& out)
{
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* piece = board.getPiece(r, c);
            if (!piece || piece->getColor() != white) continue;

            Position from(r, c);
            auto legalMoves = piece->getLegalMoves(board, from);
            for (const Position& to : legalMoves) {
                out.emplace_back(from.toString(), to.toString());
            }
        }
    }
}

int MoveRecommender::evaluateMove(const std::string& from, const std::string& to, int depth) {
    Piece* captured = nullptr;
    try {
        captured = board.execute(from, to);
    } catch (...) {
        return std::numeric_limits<int>::min(); // illegal move
    }

    int score = 0;
    if (captured) score += materialValue(captured->getChar()) * 10;

    // Depth-0 heuristic bonus
    score += centreBonus(Position(to));
    score += coveredSquaresDiff(!board.whiteToMove());

    // Recursively simulate opponent move
    if (depth < maxDepth) {
        std::vector<std::pair<std::string, std::string>> replies;
        collectMoves(board.whiteToMove(), replies);
        int worst = std::numeric_limits<int>::min();
        for (const auto& reply : replies) {
            try {
                int replyScore = evaluateMove(reply.first, reply.second, depth + 1);
                worst = std::max(worst, replyScore);
            } catch (...) {}
        }
        score -= worst;
    }

    board.undo(from, to, captured);
    return score;
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

    if (top5.empty()) throw ChessException("No legal moves");

    std::vector<Move> top;
    while (!top5.empty()) top.push_back(top5.poll());
    return *std::max_element(top.begin(), top.end(), [](const Move& a, const Move& b) {
        return a.score < b.score;
    });
}

int MoveRecommender::coveredSquaresDiff(bool side) const
{
    int mine = 0, his = 0;
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c) {
            if (r < 0 || r >= 8 || c < 0 || c >= 8)
                continue;

            Piece* pc = board.getPiece(r, c);
            if (!pc)
                continue;

            if (pc->getColor() == side)
                mine += materialValue(pc->getChar());
            else
                his += materialValue(pc->getChar());
        }
    return (mine - his) / 2;
}

void MoveRecommender::printTop3() const {
    if (top5.empty()) {
        std::cout << " >> No legal moves\n";
        return;
    }
    auto tmp = top5;
    std::cout << " >> Recommended moves:\n";
    for (int i = 0; i < 3 && !tmp.empty(); ++i) {
        Move m = tmp.poll();
        std::cout << "    " << squareToUI(m.from) << " → " << squareToUI(m.to)
                  << "  (score " << m.score << ")\n";
    }
    std::cout << '\n';
}