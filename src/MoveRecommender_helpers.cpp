#include "MoveRecommender.hpp"
#include <array>

static std::string squareToUI(const Position& p) {
    return { char('a' + p.col), char('8' - p.row) };
}

static const std::array<std::pair<int,int>,4> centre4 = {{{3,3},{3,4},{4,3},{4,4}}};

int MoveRecommender::centreBonus(Position p) const
{
    for(auto cc:centre4)
        if(p.row==cc.first && p.col==cc.second) return 2;
    return 0;
}

bool MoveRecommender::leavesPieceHanging(const std::string&,
                                         const std::string& to,bool side)
{
    Position p(to);
    int myVal = materialValue(board.getPiece(p.row,p.col)->getChar());
    for(int dr=-1;dr<=1;++dr)
        for(int dc=-1;dc<=1;++dc){
            int r=p.row+dr, c=p.col+dc;
            if(r<0||r>7||c<0||c>7) continue;
            if(Piece* pc = board.getPiece(r,c))
                if(pc->getColor()!=side &&
                   materialValue(pc->getChar())>myVal)
                    return true;
        }
    return false;
}

bool MoveRecommender::threatensStronger(const std::string&,
                                        const std::string& to,bool side)
{
    Position p(to);
    int myVal = materialValue(board.getPiece(p.row,p.col)->getChar());
    for(int dr=-1;dr<=1;++dr)
        for(int dc=-1;dc<=1;++dc){
            int r=p.row+dr, c=p.col+dc;
            if(r<0||r>7||c<0||c>7) continue;
            if(Piece* pc = board.getPiece(r,c))
                if(pc->getColor()!=side &&
                   materialValue(pc->getChar())>myVal)
                    return true;
        }
    return false;
}
