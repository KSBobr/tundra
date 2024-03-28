#include <iostream>
#include <vector>
#include <ctime>
#include "Obj.h"
#include "Reducent.h"
#include "Con1.h"
//60*80
using namespace std;
int Reducent::R = 0;
void NewGrass(int n, int m, vector<Obj>* pole);
bool GrassTrue(int x, int y,int n,int m, vector<Obj> *pole);
int main()
{
	vector <Con1> C1;
    int Vivod[10][10]={0};
	srand(time(0));
	int n = 10;
	int m = 10;
	vector <Obj> pole[10];
    vector <int> pgrass [10];
	for (int i = 0; i < n; i++){for (int j = 0; j < m; j++){pole[i].push_back(Obj()); pgrass[i].push_back(0);}}
	//NewGrass(n, m, pole);
    C1.push_back(Con1(1, 1));
    C1.push_back(Con1(1,5));
    pole[0][3].setObj(2,0);
    pole[1][1].setObj(1,3);
    pole[1][5].setObj(1,3);
    for (int i = 0; i < n; i++){for (int j = 0; j < m; j++)cout << pole[i][j].getRole() << " "; cout << "\n";}
    cout<<"\n";
	//cout << Reducent::R<<"\n";
    vector<int> DeathNote;
    for (int h=0;h<7;h++)
    {
        size_t S=C1.size();
        DeathNote.clear();
        if (h==1) pgrass[1][2]=1;
        for(int i=0;i<S;i++) cout<<C1[i].getX()<<" "<<C1[i].getY()<<"\n";cout<<"\n";
        for(int i=0;i<S;i++) C1[i].iter(n,m,pole,pgrass,C1,i,DeathNote);
        for (int i=0;i<DeathNote.size();i++) {pole[C1[DeathNote[i]].getX()][C1[DeathNote[i]].getY()].setObj(-1,0);C1.erase(C1.begin()+DeathNote[i]);}
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++)
            {
                if (pole[i][j].getRole()==0)Vivod[i][j]=1;
                else if (pgrass[i][j] and pole[i][j].getRole()==-1) {pole[i][j].setObj(0,0); Vivod[i][j]=1;}
                else if (pgrass[i][j] and pole[i][j].getRole()==1){Vivod[i][j]=3;}
                else if(pole[i][j].getRole()==1){Vivod[i][j]=2;}
                else if (pgrass[i][j] and pole[i][j].getRole()==2){Vivod[i][j]=5;}
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








bool GrassTrue(int x, int y,int n, int m, vector<int> *pole)
{
	int count = 0;
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
            int xi = (n+i)%m;
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
void NewGrass(int n, int m, vector<Obj>* pole, vector <int> *pgrass)
{
	for (int i = 0; i < 10; i++)
	{
		int x = rand() % 10;
		int y = rand() % 10;
		if (pole[x][y].getRole() == -1 and GrassTrue(x, y, n, m, pgrass))
		{
			pole[x][y].setObj(0,0);
            pgrass[x][y]=1;
			Reducent a;
		}
	}
}