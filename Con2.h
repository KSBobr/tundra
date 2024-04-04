#pragma once
#include "Obj.h"
#include "Con1.h"
#include <vector>
class Con2 :public Obj
{
private:
    short int x=0;
    short int y=0;
    short int vision=5;
    short int satiety=12;
public:
    Con2():Obj(1,0){};
    Con2(short int vx, short int vy);
    Con2(short int vx, short int vy, short int vis);
    short int getX() const;
    short int getY() const;
    void iter (short int n,short int m, std::vector<Obj> *pole,std::vector<short int> *pgrass,std::vector<Con2> &C1,short int it,std::vector<short int>&D,std::vector<Con1>& C,std::vector<short int>&Dz);

};