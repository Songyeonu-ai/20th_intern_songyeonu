#include "hw3.hpp" 


namespace SYU{
    
    Monster::Monster(): x(5), y(4), HP(50) {};
    Monster::Monster(int x, int y, int HP): x(x), y(y), HP(HP) {};
    int Monster::Be_Attacked(){
        if(this->HP<=0){
                cout<<"Monster Die!!"<<endl;
                return 0;
            }
        return this->HP;

    }
    
    Player::Player(): x(0), y(0), HP(100), MP(10) {};
    Player::Player(int x, int y): x(x) ,y(y) {};
    void Player::Attack(Monster &target){
        if(target.x==this->x&&target.y==this->y&&MP>0){
            target.HP-=10;
            cout<<"공격 성공!"<<endl;
            cout<<"남은 체력:"<<target.HP<<endl;
        }
        else if(this->MP<=1){
            cout<<"MP부족! 게임 종료..."<<endl;
        }
        else{
            cout<<"공격 실패!"<<endl;
        }
        MP--;

    }
    void Player::Show_Status(){
        cout<<"HP:"<<this->HP<<endl;
        cout<<"MP:"<<this->MP<<endl;
        cout<<"Position:"<<this->x<<','<<this->y<<endl;
    }
    void Player::X_move(int move){
        this->x+=move;
        cout<<"X Position "<<move<<" moved!"<<endl;
    }
    void Player::Y_move(int move){
        this->y+=move;
        cout<<"Y Position "<<move<<" moved!"<<endl;
    }

    int strlenn(char *str){
    int len=0;
    while(*str){
        len++;
        str++;
    }
    return len;
    }

    bool CinSecure(double p){
        int check=p;
        if(check!=p){
            return false;
        }
        return true;
    }

}

int main(){
    using namespace SYU;
   
    Player player(0, 0);
    Monster monster(5, 4, 50);

    char command[100];
    while(1){
    cout<<"사용자 스탯 설정-HP: ";
        cin>>p;
        if(!CinSecure(p)){
            cout<<"정수만을 입력할 수 있습니다. 다시 입력하세요"<<endl;
            continue;
        }
        player.HP=p;
        if(p<=0){
            cout<<"다시 입력해 주세요."<<endl;
            continue;
        }
        cout<<"사용자 스탯 설정-MP: ";
        cin>>p;
        if(!CinSecure(p)){
            cout<<"정수만을 입력할 수 있습니다. 다시 입력하세요"<<endl;
            continue;
        }
        player.MP=p;
        if(p<=0){
            cout<<"다시 입력해 주세요."<<endl;
            continue;
        }
        break;
    }

    while(1){
        cout<<"Type Command(A/U/D/R/L/S)"<<endl;
        cin>>command;
        if(strlenn(command)>1){cout<<"Please Enter One Command at Once.";continue;}
        if(command[0]=='A'){player.Attack(monster);monster.Be_Attacked();}
        else if(command[0]=='U')player.Y_move(1);
        else if(command[0]=='D')player.Y_move(-1);
        else if(command[0]=='R')player.X_move(1);
        else if(command[0]=='L')player.X_move(-1);
        else if(command[0]=='S')player.Show_Status();
        else{
            cout<<"Wrong Access";continue;
        }
        if(monster.HP<=0||player.MP<=0)break;

    }

    return 0;
}