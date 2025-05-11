#include <iostream>
#include <string>
// Chess
#include "Chess.h"
#include "Board.hpp"
#include "MoveRecommender.hpp"
#include "Move.hpp"
#include "ChessExceptions.hpp"
#include "PriorityQueue.hpp"


int main() {
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
//	string board = "##########K###############################R#############r#r#####";
    Chess a(board);
    int codeResponse = 0;
    string res = a.getInput();
    while (res != "exit") {
        /*
        codeResponse value :
        Illegal movements :
        11 - there is not piece at the source
        12 - the piece in the source is piece of your opponent
        13 - there one of your pieces at the destination
        21 - illegal movement of that piece
        31 - this movement will cause you checkmate
        legal movements :
        41 - the last movement was legal and cause check
        42 - the last movement was legal, next turn
        */


        {   // only this block is allowed to change
            static Board gameBoard;                 // default ctor builds start-position

            try {
                if (res.size() == 4) {              // human move “e2e4”
                    std::string from = res.substr(0, 2);
                    std::string to   = res.substr(2, 2);

                    codeResponse = gameBoard.move(from, to);
                    a.setCodeResponse(codeResponse);
                }
                else if (res == "ai" || res == "AI") {          // let the engine move
                    MoveRecommender engine(gameBoard, 2);       // depth-2 search
                    Move best = engine.recommend();

                    std::string from, to;
                    from += char('a' + best.from.col);
                    from += char('1' + best.from.row);
                    to   += char('a' + best.to.col);
                    to   += char('1' + best.to.row);

                    std::cout << "Engine plays " << from << to << '\n';

                    codeResponse = gameBoard.move(from, to);    // use the same validated path
                    a.setCodeResponse(codeResponse);
                }
                else {
                    std::cout << "Invalid input !!\n";
                    a.setCodeResponse(21);                    // illegal movement
                }
            }
            catch (const InvalidMoveException&)        { a.setCodeResponse(21); }
            catch (const EmptyPriorityQueueException&) { a.setCodeResponse(31); }
            catch (const PawnPromotionException&)      { a.setCodeResponse(11); }
            catch (const ChessException&)              { a.setCodeResponse(31); }

            res = a.getInput();
        }

    }


    cout << endl << "Exiting " << endl;
    return 0;
}
