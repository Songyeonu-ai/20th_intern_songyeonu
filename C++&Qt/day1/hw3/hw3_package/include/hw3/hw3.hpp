#include <iostream>

using namespace std;

namespace SYU{
class Monster;

class Player
{

    public:
        int x, y, HP, MP;
        Player();
        Player(int x, int y);
        void Attack(Monster &target);
        void Show_Status();
        void X_move(int move);
        void Y_move(int move);
};
class Monster
{

    public:
       int HP, x, y;
       Monster();
       Monster(int x, int y, int HP);
       int Be_Attacked();
};
int strlenn(char *str);
bool CinSecure(double p);
double p;
}
 