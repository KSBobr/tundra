#pragma once
#include "Obj.h"
#include <vector>
class Con1 :public Obj
{
private:
    int x=0;
    int y=0;
    int vision=3;
    int satiety=6;
public:
    Con1():Obj(1,0){};
    Con1(int vx, int vy);
    Con1(int vx, int vy, int vis);
    int getX() const;
    int getY() const;
    void iter (int n,int m, std::vector<Obj> *pole,std::vector<int> *pgrass,std::vector<Con1> &C1,int it,std::vector<int>&D);
    //void do1 (int x, int y,int n,int m, std::vector<Obj> *pole);
};