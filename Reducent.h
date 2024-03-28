#pragma once
#include "Obj.h"
class Reducent : public Obj
{
private:
public:
    static int R;
    Reducent() :Obj(0,0)
    {
        R++;
    }
};