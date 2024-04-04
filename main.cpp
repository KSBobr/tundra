#include <iostream>
#include <vector>
#include <ctime>
#include "Obj.h"
#include <algorithm>
#include "Reducent.h"
#include "Con1.h"
#include "Con2.h"
//60*80
using namespace std;
void NewGrass(short int n, short int m, vector<Obj>* pole, vector< short int>* pgrass);
bool GrassTrue(short int x,short int y,short int n,short int m, vector<short int> *pole);
int main()
{
	vector <Con1> C1;
    vector <Con2> C2;
    short int Vivod[40][60]={0};
	srand(time(0));
	short int n = 40;
	short int m = 60;
	vector <Obj> pole[40];
    vector <short int> pgrass [40];
	for (int i = 0; i < n; i++){for (int j = 0; j < m; j++){pole[i].push_back(Obj(-1,0)); pgrass[i].push_back(0);}}
    C1.push_back(Con1(4, 7));
    pole[4][7].setObj(1,0);
    //for (int i = 0; i < n; i++){for (int j = 0; j < m; j++)cout << pole[i][j].getRole() << " "; cout << "\n";}
    cout<<"\n";
    vector<short int> DeathNote;
    vector<short int> DeathNote2;
    for(int i=0;i<n*m/20;i++)NewGrass(n, m, pole, pgrass);
    for(int i=0;i<n*m/4;i++)
    {
       short int x=rand()%n;
       short int y=rand()%m;
       if(pole[x][y].getRole()==-1)
       {
           pole[x][y].setObj(1,0);
           C1.push_back(Con1(x,y));
       }
    }
    for(int i=0;i<n*m/8;i++)
    {
        short int x=rand()%n;
        short int y=rand()%m;
        if(pole[x][y].getRole()==-1)
        {
            pole[x][y].setObj(2,0);
            C2.push_back(Con2(x,y));
        }
    }
    while(C1.size()>1 and C2.size()>1 and C1.size()<n*m/10*6 and C2.size()<n*m/10*6)
    {
        size_t S=C1.size();
        size_t S2=C2.size();
        DeathNote.clear();
        DeathNote2.clear();
        //for(int i=0;i<S;i++) cout<<C1[i].getX()<<" "<<C1[i].getY()<<"\n";cout<<"\n";
        //for(int i=0;i<S2;i++) cout<<C2[i].getX()<<" "<<C2[i].getY()<<"\n";cout<<"\n";
        for(int i=0;i<S;i++) {C1[i].iter(n,m,pole,pgrass,C1,i,DeathNote);C1[i].ageincrease();}
        for(int i=0;i<S2;i++) {C2[i].iter(n,m,pole,pgrass,C2,i,DeathNote2,C1,DeathNote);C1[i].ageincrease();}
        for (int i=0;i<DeathNote.size();i++) {
            if(pole[C1[DeathNote[i]].getX()][C1[DeathNote[i]].getY()].getRole()==1)
            {pole[C1[DeathNote[i]].getX()][C1[DeathNote[i]].getY()].setObj(-1,0);}
            C1.erase(C1.begin()+DeathNote[i]-i);
        }
        sort(DeathNote.begin(),DeathNote.end());
        for (int i=0;i<DeathNote.size();i++) {
            if(pole[C1[DeathNote[i]].getX()][C1[DeathNote[i]].getY()].getRole()==1)
            {pole[C1[DeathNote[i]].getX()][C1[DeathNote[i]].getY()].setObj(-1,0);}
            C1.erase(C1.begin()+DeathNote[i]-i);
        }
        sort(DeathNote2.begin(),DeathNote2.end());
        for (int i=0;i<DeathNote2.size();i++) {
            if(pole[C2[DeathNote2[i]-i].getX()][C2[DeathNote2[i]-i].getY()].getRole()==2)
            {pole[C2[DeathNote2[i]-i].getX()][C2[DeathNote2[i]-i].getY()].setObj(-1,0);}
            C2.erase(C2.begin()+DeathNote2[i]-i);
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++)
            {
                if (pole[i][j].getRole()==0)Vivod[i][j]=1;
                else if (pgrass[i][j] and pole[i][j].getRole()==-1) {pole[i][j].setObj(0,0); Vivod[i][j]=1;}
                else if (pgrass[i][j] and pole[i][j].getRole()==1){Vivod[i][j]=3;}
                else if(pole[i][j].getRole()==1){Vivod[i][j]=2;}
                else if (pgrass[i][j] and pole[i][j].getRole()==2){Vivod[i][j]=6;}
                else if(pole[i][j].getRole()==2){Vivod[i][j]=5;}
                else Vivod[i][j]=0;
            }
        }
        //for (int i = 0; i < n; i++){for (int j = 0; j < m; j++)cout << pgrass[i][j]<< " "; cout << "\n";}
        //for (int i = 0; i < n; i++){for (int j = 0; j < m; j++)cout << pole[i][j].getRole() << " "; cout << "\n";}
        for (int i = 0; i < n; i++){for (int j = 0; j < m; j++)cout << Vivod[i][j] << " "; cout << "\n";}
        //for(int i=0;i<S;i++) cout<<C1[i].getX()<<" "<<C1[i].getY()<<"\n";cout<<"\n";
        cout<<"\n";

    }
}

/*0-nothing
 * 1-grass
 * 2-con1
 * 3-con1+grass
 * 4-con2
 * 5 - con2+grass*/








bool GrassTrue(short int x,short int y,short int n,short int m, vector<short int> *pole)
{
	int count = 0;
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
            int xi = (n+i)%n;
            int yj = (m+j)%m;
			if (pole[xi][yj] == 1)
			{
				count++;
				if (count >= 6)
				{
					//cout << "ferff" << "\n";
					return false;
				}

			}
		}
	}
	return true;
}
void NewGrass(short int n,short int m, vector<Obj>* pole, vector <short int> *pgrass)
{
	for (int i = 0; i < 10; i++)
	{
		short int x = rand() % n;
		short int y = rand() % m;
		if (pole[x][y].getRole() == -1 and GrassTrue(x, y, n, m,pgrass))
		{
			pole[x][y].setObj(0,0);
            pgrass[x][y]=1;
			Reducent a;
		}
	}
}