#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include "hw2.hpp"

using namespace std;

namespace SYU{

    GetDist::GetDist(): dot(nullptr), count(0), min_value(0), max_value(0), MinDist(0), MaxDist(0), Dist(0) {}
    GetDist::~GetDist() {delete[] dot;}
   
    bool GetDist::CinSecure(double p){
        check = p;
        if(check!=p){
        return false;
        }
        return true;
    }
    int GetDist::GetCoord(){
        cout<<"Please define the number of points: ";
        cin>>p;
        if(!CinSecure(p)){
            cout<<"정수만을 입력할 수 있습니다."<<endl;
            return 0;
        }
        count=p;

        cout<<"Please define minimum of coor. value: ";
        cin>>p;
        if(!CinSecure(p)){
            cout<<"정수만을 입력할 수 있습니다."<<endl;
            return 0;
        }
        min_value=p;

        cout<<"Please define maximum of coor. value: ";
        cin>>p;
        if(!CinSecure(p)){
            cout<<"정수만을 입력할 수 있습니다."<<endl;
            return 0;
        }
        max_value=p;

        if(count<=0||(min_value>=max_value)){
            cout<<"잘못된 값을 입력했습니다."<<endl;
            return 0;
        }

        srand(time(NULL));
        dot=new coordinate[count];

        for(int i=0;i<count;i++){
         
        int num1 = rand()%max_value;
        int num2 = rand()%max_value;
        
        if(num1<min_value||num2<min_value){
            i--;
            continue;
        }
        dot[i].x = num1;
        dot[i].y = num2;
        cout<<"Point "<<i+1<<'.'<< "nX="<<num1<<','<<"nY="<<num2<<endl;
    }
}

    void GetDist::PrintResult(){
        MinDist=((double)dot[0].x-(double)dot[1].x)*((double)dot[0].x-(double)dot[1].x)+((double)dot[0].y-(double)dot[1].y)*((double)dot[0].y-(double)dot[1].y);
        MinDist=sqrt(MinDist);
        MaxDist=MinDist;
        min1=dot[0];min2=dot[1];
        max1=min1;max2=min2;
        for (int i=0;i<count;i++){
        for(int j=0;j<count;j++){
            if(i==j)continue;
            Dist=((double)dot[i].x-(double)dot[j].x)*((double)dot[i].x-(double)dot[j].x)+((double)dot[i].y-(double)dot[j].y)*((double)dot[i].y-(double)dot[j].y);
            Dist = sqrt(Dist);
            if(Dist<MinDist){MinDist=Dist;min1=dot[i];min2=dot[j];}
            if(Dist>MaxDist){MaxDist=Dist;max1=dot[i];max2=dot[j];}
        }
        }

        cout << fixed << setprecision(6);

        cout<<"-------- Result --------"<<endl;
        cout<<"MinDist="<<MinDist<<endl;
        cout<<"Pair of Min Coor.(x,y): P1("<<min1.x<<','<<min1.y<<") & P2("<<min2.x<<','<<min2.y<<')'<<endl;

        cout<<"MaxDist="<<MaxDist<<endl;
        cout<<"Pair of Max Coor.(x,y): P1("<<max1.x<<','<<max1.y<<") & P2("<<max2.x<<','<<max2.y<<')'<<endl;

        cout<<"************* Completed ***************"<<endl;

    }
}

int main(){
    using namespace SYU;
    while(1){
    GetDist d;
    if(d.GetCoord()==0)continue;
    d.PrintResult();
    break;
    }
    return 0;
}

