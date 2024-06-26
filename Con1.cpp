#include "Con1.h"
Con1::Con1(short int vx, short int vy):Obj(1,0)
{
    x = vx;
    y = vy;
    vision = 7;
}
short int Con1::getX() const
{
    return x;
}
short int Con1::getY() const
{
    return y;
}
Con1::Con1(short int vx, short int vy, short int vis) :Obj(1,0)
{
    x = vx;
    y = vy;
    vision = vis;
}
void Con1::iter (short int n,short int m, std::vector<Obj> *pole,std::vector<short int> *pgrass, std::vector<Con1>& C1,short int it,std::set<short int> &D)
{
    short int minr=vision*vision;
    short int minrp=vision*vision;
    short int dan=vision*vision;
    short int xd,yd;
    bool danger=false;
    short int blx;
    short int blxp;
    short int blyp;
    short int bly;
    short int xes=0;
    for (short int i = x - vision; i <= x + vision; i++) {
        for (short int j = y -vision; j <= y + vision; j++) {
            if (!(i==x and y==j)) {
                short int xi = (n+i)%n;
                short int yj = (m+j)%m;
                short int rol=pole[xi][yj].getRole();
                //std::cout<<xi<<" "<<yj<<pole[xi][yj].getRole()<<" "<<satiety<<"\n";
                if (rol == 0) {
                    if (minr > abs(x - i) + abs(y - j)) {
                        minr = abs(x - i) + abs(y - j);
                        blx = xi;
                        bly = yj;
                    }
                }
                else if (rol == 2) {
                    danger = true;
                    if (dan > abs(x - i) + abs(y - j)) {
                        dan = abs(x - i) + abs(y - j);
                        xd = xi;
                        yd = yj;
                    }

                }
                else if (pole[x][y].getAge()>=2 and satiety >= 3 and rol == 1) {
                    xes = 1;
                    //std::cout<<"ABOBA\n";
                    if (minrp > abs(x - i) + abs(y - j) and pole[xi][yj].getAge()>=2) {
                        minrp = abs(x - i) + abs(y - j);
                        blxp = xi;
                        blyp = yj;
                    }
                }
            }
        }
    }

    short int xn=x;
    short int yn=y;
    short int xs=x;
    short int ys=y;
    short int rod=0;
    //std::cout<<xes<<" "<<x<<" "<<y<<" "<<minrp<<"\n";
    //std::cout<<x<<" "<<y<<" ";
    if (abs(x-xd)+abs(y-yd)<4 or abs(x-xd)+abs(y-yd)<6 and C1.size()<100)
    {
        if (xd<=x) xs=(n+x+1)%n;
        else if(xd>x) xs=(n+x-1)%n;
    }
    else if (xes and satiety>=2 and minrp<vision*vision)
    {
        if (minrp==1)
        {
            if(xs==blxp)
            {
                ys = (m+ys + (blyp - ys < 0) * 1 - (blyp - ys > 0) * 1)%m;
            }
            else
            {
                xs = (n+xs + (blxp - xs < 0) * 1 - (blxp - xs > 0) * 1)%n;
            }
            rod=1;
            //std::cout<<xs<<" "<<ys<<" ";
            //std::cout<<x<<" "<<y<<"\n";
        }
        else if (xs!=blxp) {
            xs = (n+xs - (blxp - xs < 0) * 1 + (blxp - xs > 0) * 1)%n;
        }
        else if (ys!=blyp) {
            ys = (m+ys - (blyp - ys < 0) * 1 + (blyp - ys > 0) * 1)%m;
        }
    }
    else if (minr<vision*vision and satiety<=4)
    {
        if (minr==1)
        {
            satiety+=4;
            pole[blx][bly].die();
            pgrass[blx][bly]=0;
            xs=blx;
            ys=bly;
        }
        if (xs!=blx) {
            xs = (xs - (blx - xs < 0) * 1 + (blx - xs > 0) * 1)%n;
        }
        else if (y!=bly) {
            ys = (ys - (bly - ys < 0) * 1 + (bly - ys > 0) * 1)%m;
        }
    }
    else
    {
        short int fac=rand()%4;
        if (fac==0 and pole[(n+x)%n][(m+y+1)%m].getRole()<=0){ys=(m+y+1)%m;}
        else if(fac==1 and pole[(n+x)%n][(m+y-1)%m].getRole()<=0){ys=(m+y-1)%m;}
        else if(fac==2 and pole[(n+x+1)%n][(m+y)%m].getRole()<=0){xs=(n+x+1)%n;}
        else if(fac==3 and pole[(n+x-1)%n][(m+y)%m].getRole()<=0){xs=(n+x-1)%n;}
    }
    //std::cout<<xs<<" "<<ys<<" "<<pole[xs][ys].getRole()<<"\n";
    if(pole[xs][ys].getRole()<=0) {
        pole[xs][ys] = pole[x][y];
        pole[x][y].die();
        x = xs;
        y = ys;
    }
    else if(ys==y)
    {
        if(pole[xs][(ys+1+m)%m].getRole()<=0)
        {
            ys=(m+y+1)%m;
            pole[xs][ys] = pole[x][y];
            pole[x][y].die();
            x = xs;
            y = ys;
        }
        else if(pole[xs][(ys-1+m)%m].getRole()<=0)
        {
            ys=(m+y-1)%m;
            pole[xs][ys] = pole[x][y];
            pole[x][y].die();
            x = xs;
            y = ys;

        }
    }
    else
    {
        if(pole[(xs+n+1)%n][ys].getRole()<=0)
        {
            xs=(xs+n+1)%n;
            pole[xs][ys] = pole[x][y];
            pole[x][y].die();
            x = xs;
            y = ys;
        }
        else if(pole[(xs+n-1)%n][ys].getRole()<=0)
        {
            xs=(xs+n-1)%n;
            pole[xs][ys] = pole[x][y];
            pole[x][y].die();
            x = xs;
            y = ys;
        }
    }
    satiety--;
    if (satiety<0 or (pole[x][y].getAge()>5 and C1.size()>100 or pole[x][y].getAge()>7 and C1.size()<=100))
    {
        D.insert(it);
    }
    //if (it==1) {x=1;y=4;}
    //std::cout<<x<<" "<<y<<"\n";
    if(rod and C1.size()<n*m/10*6) {
        //satiety--;
        pole[xn][yn].setObj(1, 0);
        C1.push_back(Con1(xn, yn));
    }
    //std::cout<<satiety<<"\n";
}