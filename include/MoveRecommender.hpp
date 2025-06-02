#pragma once
#include "Board.hpp"
#include "Move.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <string>

struct BetterMove {
    bool operator()(const Move& a, const Move& b) const {
        return a.score > b.score;
    }
};

class MoveRecommender {
    Board& board;
    int maxDepth;
    PriorityQueue<Move, BetterMove> top5;

    int materialValue(char p) const;
    int centreBonus(Position p) const;
    bool leavesPieceHanging(const std::string& from, const std::string& to) const;
    bool threatensStronger(const std::string& from, const std::string& to) const;

    void collectMoves(bool whiteTurn, std::vector<std::pair<std::string, std::string>>& moves);
    int evaluateMove(const std::string& from, const std::string& to, int depth);
    int coveredSquaresDiff(bool white) const;

public:
    MoveRecommender(Board& b, int depth = 3);
    Move recommend();
    std::vector<Move> topMoves();
};