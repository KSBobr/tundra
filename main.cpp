#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include "Obj.h"
#include <algorithm>
#include <set>
#include "Reducent.h"
#include "Con1.h"
#include "Con2.h"
//60*80
using namespace std;
void NewGrass(short int n, short int m, vector<Obj>* pole, vector< short int>* pgrass);
bool GrassTrue(short int x,short int y,short int n,short int m, vector<short int> *pole);
int main()
{
    int cit=0;
    sf::RenderWindow window(sf::VideoMode(1280, 880), "SFML works!");
    window.setFramerateLimit(3);
    sf::Time elapsedTime;
    sf::Clock clock;

    sf::Texture Background;
    Background.loadFromFile("textures/background.png");
    sf::Sprite background(Background);

    sf::Texture Fon;
    Fon.loadFromFile("textures/fon.png");
    sf::Sprite fon(Fon);

    sf::Texture Mox;
    Mox.loadFromFile("textures/moxx.png");
    sf::Sprite mox(Mox);

    sf::Texture Lem;
    Lem.loadFromFile("textures/Lem.png");
    sf::Sprite lem(Lem);

    sf::Texture Lem_fon;
    Lem_fon.loadFromFile("textures/Lem-fon.png");
    sf::Sprite lem_fon(Lem_fon);

    sf::Texture Lem_mox;
    Lem_mox.loadFromFile("textures/Lem-mox.png");
    sf::Sprite lem_mox(Lem_mox);

    sf::Texture Pec;
    Pec.loadFromFile("textures/Pec.png");
    sf::Sprite pec(Pec);

    sf::Texture Pec_fon;
    Pec_fon.loadFromFile("textures/Pec-fon.png");
    sf::Sprite pec_fon(Pec_fon);

    sf::Texture Pec_mox;
    Pec_mox.loadFromFile("textures/Pec-mox.png");
    sf::Sprite pec_mox(Pec_mox);

    vector <Con1> C1;
    vector <Con2> C2;
    short int Vivod[80][55]={0};
	srand(time(0));
	short int n = 80;
	short int m = 55;
	vector <Obj> pole[80];
    vector <short int> pgrass [80];
	for (int i = 0; i < n; i++){for (int j = 0; j < m; j++){pole[i].push_back(Obj(-1,0)); pgrass[i].push_back(0);}}
    //for (int i = 0; i < n; i++){for (int j = 0; j < m; j++)cout << pole[i][j].getRole() << " "; cout << "\n";}
    cout<<"\n";
    set <short int> DeathNote;
    set <short int> DeathNote2;
    for(int i=0;i<n*m/24;i++)NewGrass(n, m, pole, pgrass);
    for(int i=0;i<n*m/6;i++)
    {
       short int x=rand()%n;
       short int y=rand()%m;
       if(pole[x][y].getRole()==-1)
       {
           pole[x][y].setObj(1,0);
           C1.push_back(Con1(x,y));
       }
       else
       {
           x=rand()%n;
           y=rand()%m;
           if(pole[x][y].getRole()==-1)
           {
               pole[x][y].setObj(1,0);
               C1.push_back(Con1(x,y));
           }
       }
    }
    for(int i=0;i<m*n/24;i++)
    {
        short int x=rand()%n;
        short int y=rand()%m;
        if(pole[x][y].getRole()==-1)
        {
            pole[x][y].setObj(2,0);
            C2.push_back(Con2(x,y));
        }
        else
        {
            x=rand()%n;
            y=rand()%m;
            if(pole[x][y].getRole()==-1)
            {
                pole[x][y].setObj(2,0);
                C2.push_back(Con2(x,y));
            }
        }
    }
    /*pole[4][7].setObj(2,4);
    C2.push_back(Con2(4,7));
    pole[8][9].setObj(2,4);
    C2.push_back(Con2(8,9));*/
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //shape.move(0.3, 0.3);

        while(C1.size()>1 and C1.size()<n*m/10*6 and C2.size()>1 and C2.size()<n*m/10*6)
        {
            cit++;
            size_t S=C1.size();
            size_t S2=C2.size();
            DeathNote.clear();
            DeathNote2.clear();
            //for(int i=0;i<S;i++) cout<<C1[i].getX()<<" "<<C1[i].getY()<<"\n";cout<<"\n";
            //for(int i=0;i<S2;i++) cout<<C2[i].getX()<<" "<<C2[i].getY()<<"\n";cout<<"\n";
            for(int i=0;i<S;i++) {C1[i].iter(n,m,pole,pgrass,C1,i,DeathNote);pole[C1[i].getX()][C1[i].getY()].ageincrease();}
            for(int i=0;i<S2;i++) {C2[i].iter(n,m,pole,pgrass,C2,i,DeathNote2,C1,DeathNote);pole[C2[i].getX()][C2[i].getY()].ageincrease();}
            int cnt=0;
            for (int i:DeathNote) {
                if(pole[C1[i-cnt].getX()][C1[i-cnt].getY()].getRole()==1)
                {pole[C1[i-cnt].getX()][C1[i-cnt].getY()].setObj(-1,0);}
                C1.erase(C1.begin()+i-cnt);
                cnt++;
            }
            cnt=0;
            for (int i:DeathNote2) {
                if(pole[C2[i-cnt].getX()][C2[i-cnt].getY()].getRole()==2)
                {pole[C2[i-cnt].getX()][C2[i-cnt].getY()].setObj(-1,0);}
                C2.erase(C2.begin()+i-cnt);
                cnt++;
            }
            cnt=0;
            window.clear();
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++)
                {
                    if(pole[i][j].getRole()==2)pole[i][j].setObj(-1,pole[i][j].getAge());
                }
            }
            for(int i=0;i<C2.size();i++)
            {
                pole[C2[i].getX()][C2[i].getY()].setObj(2,pole[C2[i].getX()][C2[i].getY()].getAge());
            }
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++)
                {
                    if (pole[i][j].getRole() == 0){
                        Vivod[i][j] = 1;
                        sf::RectangleShape rect(sf::Vector2f(16, 16));
                        rect.setPosition(i * 16, j * 16);

                        rect.setTexture(&Mox);
                        rect.setTextureRect(sf::IntRect(0, 0, 16, 16));
                        window.draw(rect);
                    }
                    else if (pgrass[i][j] and pole[i][j].getRole() == -1) {
                        pole[i][j].setObj(0, 0);
                        Vivod[i][j] = 1;
                        sf::RectangleShape rect(sf::Vector2f(16, 16));
                        rect.setPosition(i * 16, j * 16);

                        rect.setTexture(&Mox);
                        rect.setTextureRect(sf::IntRect(0, 0, 16, 16));
                        window.draw(rect);
                    }
                    else if (pgrass[i][j] and pole[i][j].getRole() == 1) {
                        Vivod[i][j] = 3;
                        sf::RectangleShape rect(sf::Vector2f(16, 16));
                        rect.setPosition(i * 16, j * 16);

                        rect.setTexture(&Lem_mox);
                        rect.setTextureRect(sf::IntRect(0, 0, 16, 16));
                        window.draw(rect);
                    }
                    else if (pole[i][j].getRole() == 1) {
                        Vivod[i][j] = 2;
                        sf::RectangleShape rect(sf::Vector2f(16, 16));
                        rect.setPosition(i * 16, j * 16);

                        rect.setTexture(&Lem_fon);
                        rect.setTextureRect(sf::IntRect(0, 0, 16, 16));
                        window.draw(rect);
                    }
                    else if (pgrass[i][j] and pole[i][j].getRole() == 2) {
                        Vivod[i][j] = 5;
                        sf::RectangleShape rect(sf::Vector2f(16, 16));
                        rect.setPosition(i * 16, j * 16);

                        rect.setTexture(&Pec_mox);
                        rect.setTextureRect(sf::IntRect(0, 0, 16, 16));
                        window.draw(rect);
                    }
                    else if (pole[i][j].getRole() == 2) {
                        Vivod[i][j] = 4;
                        sf::RectangleShape rect(sf::Vector2f(16, 16));
                        rect.setPosition(i * 16, j * 16);

                        rect.setTexture(&Pec_fon);
                        rect.setTextureRect(sf::IntRect(0, 0, 16, 16));
                        window.draw(rect);
                    }
                    else {
                        Vivod[i][j] = 0;
                        sf::RectangleShape rect(sf::Vector2f(16, 16));
                        rect.setPosition(i * 16, j * 16);

                        rect.setTexture(&Fon);
                        rect.setTextureRect(sf::IntRect(0, 0, 16, 16));
                        window.draw(rect);
                    }
                }
            }
            //for (int i = 0; i < n; i++){for (int j = 0; j < m; j++)cout << pgrass[i][j]<< " "; cout << "\n";}
            //for (int i = 0; i < n; i++){for (int j = 0; j < m; j++)cout << pole[i][j].getRole() << " "; cout << "\n";}
            //for (int i = 0; i < n; i++){for (int j = 0; j < m; j++)cout << Vivod[i][j] << " "; cout << "\n";}
            //for(int i=0;i<S;i++) cout<<C1[i].getX()<<" "<<C1[i].getY()<<"\n";cout<<"\n";
            cout<<"\n";
            NewGrass(n, m, pole, pgrass);
            cout<<C1.size()<<" "<<C2.size()<<' '<<cit<<'\n';
            window.display();
        }
        window.close();
    }
    return 0;
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
	for (int i = 0; i < 30; i++)
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