#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main(void)
{
    Mat grayIm(600, 800, CV_8UC1);

    for (int i = 0; i < grayIm.rows; ++i)
        for (int j = 0; j < grayIm.cols; ++j)
            grayIm.at<uchar>(i, j) = (i + j) % 255;

    imshow("grayIm", grayIm);
    waitKey(0);

    return 0;
}
