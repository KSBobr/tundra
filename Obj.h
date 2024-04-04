#pragma once
#include <iostream>
class Obj
{
private:
    short int age=0;
    short int role=-1;
public:
    Obj() { role = -1; }
    Obj(short int r, short int g)
    {
        role = r;
        age=g;
    }
    ~Obj()=default;
    [[nodiscard]] short int getRole() const {
        short int ro=role;
        return ro;
    }
    void setObj(short int r, short int a)
    {
        role = r;
        age=a;
    }
    void die()
    {
        role = -1;
        age=0;
    }
    void ageincrease()
    {
        age++;
    }
    [[nodiscard]] short int getAge() const { return age; }
};




