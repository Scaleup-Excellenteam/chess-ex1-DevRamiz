#include "Benchmarker.hpp"

using clk = std::chrono::high_resolution_clock;
void Benchmarker::play(Board& b,int n,int p){
    for(int i=0;i<p;++i){
        MoveRecommender r(b,n);
        auto best=r.topMoves();
        if(best.empty())break;
        auto toStr=[](Position p){return std::string(1,'A'+p.col)+std::to_string(p.row+1);};
        b.move(toStr(best[0].from),toStr(best[0].to));
    }
}
std::vector<BenchRow> Benchmarker::run(const std::vector<int>& v){
    std::vector<BenchRow> out;
    for(int n:v){
        Board copy=proto;
        auto t0=clk::now();
        play(copy,n,depth);
        double ms=std::chrono::duration<double,std::milli>(clk::now()-t0).count();
        out.push_back({n,ms});
    }
    return out;
}