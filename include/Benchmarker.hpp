#pragma once
#include "Board.hpp"
#include "MoveRecommender.hpp"
#include <chrono>
#include <vector>
struct BenchRow { int threads; double ms; };
class Benchmarker {
public:
    Benchmarker(const Board& b, int plies = 8) : proto(b), depth(plies) {}
    std::vector<BenchRow> run(const std::vector<int>& tCounts);
private:
    Board proto; int depth;
    void play(Board& b, int nThreads, int plies);
};