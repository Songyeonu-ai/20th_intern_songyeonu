// #include "opencv2/imgproc.hpp"
// #include "opencv2/highgui.hpp"
// #include "opencv2/videoio.hpp"
// #include <iostream>
// using namespace cv;
// const int max_value_H = 360/2;
// const int max_value = 255;
// const String window_capture_name = "Video Capture";
// const String window_detection_name = "Object Detection";
// int low_H = 0, low_S = 0, low_V = 0;
// int high_H = max_value_H, high_S = max_value, high_V = max_value;
// static void on_low_H_thresh_trackbar(int, void *)
// {
//     low_H = min(high_H-1, low_H);
//     setTrackbarPos("Low H", window_detection_name, low_H);
// }
// static void on_high_H_thresh_trackbar(int, void *)
// {
//     high_H = max(high_H, low_H+1);
//     setTrackbarPos("High H", window_detection_name, high_H);
// }
// static void on_low_S_thresh_trackbar(int, void *)
// {
//     low_S = min(high_S-1, low_S);
//     setTrackbarPos("Low S", window_detection_name, low_S);
// }
// static void on_high_S_thresh_trackbar(int, void *)
// {
//     high_S = max(high_S, low_S+1);
//     setTrackbarPos("High S", window_detection_name, high_S);
// }
// static void on_low_V_thresh_trackbar(int, void *)
// {
//     low_V = min(high_V-1, low_V);
//     setTrackbarPos("Low V", window_detection_name, low_V);
// }
// static void on_high_V_thresh_trackbar(int, void *)
// {
//     high_V = max(high_V, low_V+1);
//     setTrackbarPos("High V", window_detection_name, high_V);
// }
// int main(int argc, char* argv[])
// {
//     VideoCapture cap(argc > 1 ? atoi(argv[1]) : 0);
//     namedWindow(window_capture_name);
//     namedWindow(window_detection_name);
//     // Trackbars to set thresholds for HSV values
//     createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
//     createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
//     createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
//     createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
//     createTrackbar("Low V", window_detection_name, &low_V, max_value, on_low_V_thresh_trackbar);
//     createTrackbar("High V", window_detection_name, &high_V, max_value, on_high_V_thresh_trackbar);
//     Mat frame, frame_HSV, frame_threshold;
//     while (true) {
//         cap >> frame;
//         if(frame.empty())
//         {
//             break;
//         }
//         // Convert from BGR to HSV colorspace
//         cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
//         // Detect the object based on HSV Range Values
//         inRange(frame_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);
//         // Show the frames
//         imshow(window_capture_name, frame);
//         imshow(window_detection_name, frame_threshold);
//         char key = (char) waitKey(30);
//         if (key == 'q' || key == 27)
//         {
//             break;
//         }
//     }
//     return 0;
// }

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int ac, char** av){
    Mat img = imread("homework1.jpg");
    Mat img_hsv, img_blured, img_b;
    
    cvtColor(img, img_hsv, COLOR_BGR2HSV); //채널 변환
    GaussianBlur(img, img_b, Size( ), (double)3);
    
    GaussianBlur(img_hsv, img_blured, Size( ), (double)3);

    Mat red_mask, red_image, red_blured, red_image_b;  //검출할 색 설정
    Mat green_mask, green_image, green_blured; 
    Mat blue_mask, blue_image, blue_blured; 

    Scalar lower_red_1 = Scalar(0, 50, 50); //red를 둘로 나누는 이유는 hue값이 너무나 광범위하기 때문
    Scalar upper_red_1 = Scalar(10, 255, 255);
   
    Scalar lower_red_2 = Scalar(160, 100, 100);
    Scalar upper_red_2 = Scalar(180, 255, 255);


    Scalar lower_green = Scalar(35, 50, 50);
    Scalar upper_green = Scalar(85, 255, 255);

    Scalar lower_blue = Scalar(100, 10, 100);
    Scalar upper_blue = Scalar(130, 255, 255);



    inRange(img_hsv, lower_red_1, upper_red_1, red_mask);
    inRange(img_hsv, lower_red_2, upper_red_2, red_image);
    inRange(img_hsv, lower_green, upper_green, green_mask);
    inRange(img_hsv, lower_blue, upper_blue, blue_mask);
    //bitwise_and(img, img, yellow_image, yellow_mask);

    inRange(img_blured, lower_red_1, upper_red_1, red_blured);
    inRange(img_blured, lower_red_2, upper_red_2, red_image_b);
    inRange(img_blured, lower_green, upper_green, green_blured);
    inRange(img_blured, lower_blue, upper_blue, blue_blured);

    imshow("img", img);
    //imshow("yellow_img", yellow_image);
    imshow("red_mask", red_image + red_mask);
    imshow("green_mask", green_mask);
    imshow("blue_mask", blue_mask);

    imshow("img_b", img_b);
    imshow("red_blured", red_image_b + red_blured);
    imshow("green_blured", green_blured);
    imshow("blue_blured", blue_blured);

    waitKey(0);
    return 0;
}
