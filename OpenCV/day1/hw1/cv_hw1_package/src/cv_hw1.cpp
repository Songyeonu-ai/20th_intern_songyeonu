#include "../include/cv_hw1/cv_hw1.hpp"


HW1::HW1(){
    img = imread("/home/yu/colcon_ws/src/cv_hw1/homework1.jpg");
    cvtColor(img, img_hsv, COLOR_BGR2HSV); //채널 변환
    GaussianBlur(img, img_b, Size( ), (double)3);
    GaussianBlur(img_hsv, img_blured, Size( ), (double)3);

    lower_red_1 = Scalar(0, 50, 50); 
    upper_red_1 = Scalar(10, 255, 255);
    lower_red_2 = Scalar(160, 100, 100);
    upper_red_2 = Scalar(180, 255, 255);
    lower_green = Scalar(35, 50, 50);
    upper_green = Scalar(85, 255, 255);
    lower_blue = Scalar(100, 10, 100);
    upper_blue = Scalar(130, 255, 255);

}

void HW1::make_binary(){
    inRange(img_hsv, lower_red_1, upper_red_1, red_mask);
    inRange(img_hsv, lower_red_2, upper_red_2, red_image);
    inRange(img_hsv, lower_green, upper_green, green_mask);
    inRange(img_hsv, lower_blue, upper_blue, blue_mask);

    inRange(img_blured, lower_red_1, upper_red_1, red_blured);
    inRange(img_blured, lower_red_2, upper_red_2, red_image_b);
    inRange(img_blured, lower_green, upper_green, green_blured);
    inRange(img_blured, lower_blue, upper_blue, blue_blured);
}


void HW1::showimage(){
    imshow("img", img);
    imshow("red_mask", red_image + red_mask);
    imshow("green_mask", green_mask);
    imshow("blue_mask", blue_mask);

    imshow("img_b", img_b);
    imshow("red_blured", red_image_b + red_blured);
    imshow("green_blured", green_blured);
    imshow("blue_blured", blue_blured);

    waitKey(0); 
}

int main(int ac, char** av){

    HW1 hw;
    hw.make_binary();
    hw.showimage();
    return 0;
}
