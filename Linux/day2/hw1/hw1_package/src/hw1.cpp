#include <iostream>
#include "hw1.hpp"

using namespace std;

namespace SYU{

Jungsu::Jungsu():n(0), p(nullptr), sum(0), max(0), min(0) {} //기본값설정..
Jungsu::~Jungsu() {delete [] p;}

void Jungsu::getElement(){
    cout<<"몇 개의 원소를 할당하겠습니까? :";
    cin>>n;
    if(!CinSecure(n)){
        cout<<"정수만 입력해주세요."<<endl;
        return;
    }
    if(n<=0){
        p=nullptr;
        cout<<"자연수만 입력해주세요."<<endl;
        return;
    }
    count=n;
    p=new double[count];
}

int Jungsu::getMemo(){
    if(!p){
            cout<<"메모리를 할당할 수 없습니다."<<endl;;
            return 0;
        }
    for(int i=0;i<count;i++){
            cout<<"정수형 데이터 입력:";
            cin>>p[i];
            if(!CinSecure(p[i])){
                cout<<"정수만을 입력할 수 있습니다. 다시 입력하세요"<<endl;
                i--;
                continue;
            }
        }
    return 1;
}

bool Jungsu::CinSecure(double p){
    check = p;
    if(check!=p){
        return false;
    }
    return true;
}

void Jungsu::Calculate(){
    sum=0;
    max=p[0];
    min=p[0];
    for(int i=0;i<n;i++){
        sum+=p[i];
        if(max<p[i]){
            max = p[i];
        }
        if(min>p[i]){
            min = p[i];
        }
    }
    cout<<"최댓값="<<max<<endl;
    cout<<"최소값="<<min<<endl;
    cout<<"전체합="<<sum<<endl;
    cout<<"평균="<<sum/n<<endl;
}
}
int main(){

    while(1){
    SYU::Jungsu num1;
    num1.getElement();
    if(num1.getMemo()==0)continue;
    num1.Calculate();
    break;
    }

    return 0;
        
    }
