#pragma once
#include <vector>
#include "PriorityQueue.hpp"
#include "Board.hpp"
#include "Move.hpp"

class MoveRecommender {
    Board&                            board;
    int                               maxDepth;    // 1–3
    PriorityQueue<Move,MoveComparator> top5;

    int  evaluateMove(const std::string& from,const std::string& to,int depth);
    int  materialValue(char piece) const;

    // heuristics helpers
    int  centreBonus(Position p) const;
    int  coveredSquaresDiff(bool side) const;
    bool leavesPieceHanging (const std::string& from,const std::string& to,bool side);
    bool threatensStronger  (const std::string& from,const std::string& to,bool side);

    void collectMoves(bool white,
                      std::vector<std::pair<std::string,std::string>>& out);
public:
    explicit MoveRecommender(Board& b,int depth=2);

    Move recommend();        // single best move
    void printTop3() const;  // show 3 best from current top5
};
