namespace SYU{
    class Jungsu{
private:
    double n;
    double *p;
    int count;
    int sum;
    int max;
    int min;
    int check;


public:
    Jungsu(); //생성자
    ~Jungsu();
    void getElement(); //다른 함수
    int getMemo();
    void Calculate();
    bool CinSecure(double p);
};
}