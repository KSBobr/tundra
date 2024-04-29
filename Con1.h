#pragma once
#include "Obj.h"
#include <vector>
#include <set>
class Con1 :public Obj
{
private:
    short int x=0;
    short int y=0;
    short int vision=7;
    short int satiety=6;
public:
    Con1():Obj(1,0){};
    Con1(short int vx, short int vy);
    Con1(short int vx, short int vy, short int vis);
    short int getX() const;
    short int getY() const;
    void iter (short int n,short int m, std::vector<Obj> *pole,std::vector<short int> *pgrass,std::vector<Con1> &C1,short int it,std::set<short int>&D);
    //void do1 (short int x, short int y,short int n,short int m, std::vector<Obj> *pole);
};