#include "Chess.h"
#include "MoveRecommender.hpp"
#include "Benchmarker.hpp"
#include <iomanip>
#include <iostream>

using std::string; using std::cout; using std::cin; using std::endl;

static string toStr(Position p){return string(1,'A'+p.col)+std::to_string(p.row+1);}

int main(){
    string init="RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    Chess a(init);                // template handles IO
    Board aiBoard;                // our board for AI/bench
    int code=0; string res=a.getInput();

    while(res!="exit"){
        /**/ { // allowed snippet
            static bool once=false;
            if(!once){
                Benchmarker bm(aiBoard,8);
                auto rows=bm.run({0,2,4,8});
                cout<<"\nBenchmark (8 plies)\nthreads | time [ms]\n";
                for(auto& r:rows)
                    cout<<std::setw(7)<<r.threads<<" | "
                        <<std::setw(9)<<std::fixed<<std::setprecision(1)<<r.ms<<endl;
                cout<<endl; once=true;
            }
            MoveRecommender rec(aiBoard);
            auto best=rec.topMoves();
            if(!best.empty()){
                cout<<"AI suggests: "<<toStr(best[0].from)<<" -> "<<toStr(best[0].to)
                    <<"  (score "<<best[0].score<<")\n";
                aiBoard.move(toStr(best[0].from),toStr(best[0].to)); // mirror
            }
            cout<<"code response >> "; cin>>code;
        } /**/
        a.setCodeResponse(code);
        res=a.getInput();
    }
    cout<<"\nExiting\n";
    return 0;
}