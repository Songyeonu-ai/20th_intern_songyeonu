#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class HW1
{
    public:
    HW1();
    void make_binary();
    void showimage();
    private:
    Mat img;
    Mat img_hsv, img_blured, img_b;
    Scalar lower_red_1;
    Scalar upper_red_1; 
    Scalar lower_red_2;
    Scalar upper_red_2;
    Scalar lower_green;
    Scalar upper_green;
    Scalar lower_blue;
    Scalar upper_blue;
    Mat red_mask, red_image, red_blured, red_image_b;  //검출할 색 설정
    Mat green_mask, green_image, green_blured; 
    Mat blue_mask, blue_image, blue_blured; 

};