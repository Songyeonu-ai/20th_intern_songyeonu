namespace SYU{
    class GetDist{
    public:
        struct coordinate
        {
            int x;
            int y;
        };

    private:
        coordinate* dot;
        int count;
        int min_value;
        int max_value;
        double MinDist;
        double MaxDist;
        double Dist;
        double p;
        int check;
        coordinate min1, min2, max1, max2;
    public:
        GetDist();
        ~GetDist();
        int GetCoord();
        void PrintResult();
        bool CinSecure(double p);

    };

}
