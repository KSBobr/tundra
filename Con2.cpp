#include "Con2.h"
Con2::Con2(int vx, int vy):Obj(1,0)
{
    x = vx;
    y = vy;
    vision = 3;
}
int Con2::getX() const
{
    return x;
}
int Con2::getY() const
{
    return y;
}
Con2::Con2(int vx, int vy, int vis) :Obj(1,0)
{
    x = vx;
    y = vy;
    vision = vis;
}
void Con2::iter (int n,int m, std::vector<Obj> *pole,std::vector<int> *pgrass, std::vector<Con2>& C1,int it,std::vector<int> &D)
{
    int minr=vision*vision;
    int minrp=vision*vision;
    bool danger=false;
    int blx;
    int blxp;
    int blyp;
    int bly;
    int xes=0;
    for (int i = x - vision; i <= x + vision; i++) {
        for (int j = y -vision; j <= y + vision; j++) {
            if (!(i==x and y==j)) {
                int xi = (n+i)%m;
                int yj = (m+j)%m;
                //std::cout<<xi<<" "<<yj<<pole[xi][yj].getRole()<<" "<<satiety<<"\n";
                if (pole[xi][yj].getRole() == 1) {
                    if (minr > abs(x - i) + abs(y - j)) {
                        minr = abs(x - i) + abs(y - j);
                        blx = xi;
                        bly = yj;
                    }
                }
                else if (pole[x][y].getAge()>=3 and satiety >= 3 and pole[xi][yj].getRole() == 2) {
                    xes = 1;
                    //std::cout<<"ABOBA\n";
                    if (minrp > abs(x - i) + abs(y - j) and pole[xi][yj].getAge()>=3) {
                        minrp = abs(x - i) + abs(y - j);
                        blxp = xi;
                        blyp = yj;
                    }
                }
            }
        }
    }
    int xn=x;
    int yn=y;
    int xs=x;
    int ys=y;
    int rod=0;
    std::cout<<xes<<" "<<x<<" "<<y<<" "<<minrp<<"\n";
    //std::cout<<x<<" "<<y<<" ";
    if (xes and satiety>=3 and minrp<vision*vision)
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
            if (xs!=blxp) {
                xs = (n+xs - (blxp - xs < 0) * 1 + (blxp - xs > 0) * 1)%n;
            }
            else if (ys!=blyp) {
                ys = (m+ys - (blyp - ys < 0) * 1 + (blyp - ys > 0) * 1)%m;
            }
        }
        else if (ys!=blyp) {
            ys = (m+ys - (blyp - ys < 0) * 1 + (blyp - ys > 0) * 1)%m;
        }
    }
    else if (minr<vision*vision)
    {
        if (minr==1)
        {
            satiety+=3;
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
        int fac=rand()%4;
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
    if (satiety<0)
    {
        D.push_back(it);
    }
    //if (it==1) {x=1;y=4;}
    //std::cout<<x<<" "<<y<<"\n";
    if(rod) {
        pole[xn][yn].setObj(1, 0);
        C1.push_back(Con2(xn, yn));
    }
}