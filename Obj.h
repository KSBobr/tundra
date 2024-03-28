#pragma once
#include <iostream>
class Obj
{
private:
    int age=0;
    int role;
public:
    Obj() { role = -1; }
    Obj(int r, int g)
    {
        role = r;
        age=g;
    }
    ~Obj()=default;
    int getRole() const
    {
        return role;
    }
    void setObj(int r,int a)
    {
        role = r;
        age=a;
    }
    void die()
    {
        role = -1;
        age=0;
    }
    void it(){age++;}
    int getAge(){return age;}
};
/*std::ostream& operator<<(std::ostream& out, const Obj& O)
{
	out << O.getRole();
	return out;
};*/



