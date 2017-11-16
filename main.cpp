#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <queue>


using namespace std;
using namespace cv;


int main() {
// Reading image
    Mat img = imread("/home/simone/CLionProjects/IPMiniProject/image/bridge2.jpg");

// Displaying image
imshow("Original Image",img);
waitKey(0);

// Converting to grayscale
    Mat img_gray, image_blur;
    GaussianBlur(img, image_blur, Size(5, 5), 3, 3);
    cvtColor(image_blur, img_gray, CV_RGB2GRAY);


// Displaying grayscale image
//imshow("Original Image",img_gray);
//waitKey(0);


    int cols = img_gray.cols;
    int rows = img_gray.rows;

// Creating sobel operator in y direction
/*    int sobel_y[3][3] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
// Creating sobel operator in x direction
    int sobel_x[3][3] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};*/

    int diagKernel[3][3] = {0,0,0, -1, 0, 1, 0,0,0};


    int radius = 1;

// Handle border issues
    Mat _src;
    copyMakeBorder(img_gray, _src, radius, radius, radius, radius, BORDER_REFLECT101);

// Create output matrix
    Mat gradient_diag = img_gray.clone();
  /*  Mat gradient_x = img_gray.clone();
    Mat gradient_f = img_gray.clone();*/

    int max = 0;

// Correlation loop in x direction

// Iterate on image
    for (int r = radius; r < _src.rows - radius; ++r) {
        for (int c = radius; c < _src.cols - radius; ++c) {
            int s = 0;

            // Iterate on kernel
            for (int i = -radius; i <= radius; ++i) {
                for (int j = -radius; j <= radius; ++j) {
                    s += _src.at<uchar>(r + i, c + j) * diagKernel[i + radius][j + radius];
                }
            }
            gradient_diag.at<uchar>(r - radius, c - radius) = s / 30;

            /*if(s>200)
                gradient.at<uchar>(r - radius, c - radius) = 255;
            else
                gradient.at<uchar>(r - radius, c - radius) = 0;
            */
        }
    }

/*    Mat absGrad_x;
    convertScaleAbs(gradient_x, absGrad_x);*/

// Conrrelation loop in y direction

// Iterate on image
/*    for (int r = radius; r < _src.rows - radius; ++r) {
        for (int c = radius; c < _src.cols - radius; ++c) {
            int s = 0;

            // Iterate on kernel
            for (int i = -radius; i <= radius; ++i) {
                for (int j = -radius; j <= radius; ++j) {
                    s += _src.at<uchar>(r + i, c + j) * sobel_y[i + radius][j + radius];
                }
            }

            gradient_diag.at<uchar>(r - radius, c - radius) = s / 30;

            *//*if(s>200)
                gradient.at<uchar>(r - radius, c - radius) = 255;
            else
                gradient.at<uchar>(r - radius, c - radius) = 0;
            *//*
        }
    }*/

   Mat absGrad_diag;
    convertScaleAbs(gradient_diag, absGrad_diag);

//Mat absGrad;
/*for(int i=0; i<gradient_f.rows; i++)
{
    for(int j=0; j<gradient_f.cols; j++)
    {
        absGrad.at<uchar>(i,j) = sqrt( pow(absGrad_x.at<uchar>(i,j),2) + pow(absGrad_y.at<uchar>(i,j),2) );

         if(absGrad.at<uchar>(i,j) >240)
            absGrad.at<uchar>(i,j) = 100;
        else
            absGrad.at<uchar>(i,j) = 0;
    }
}
*/


//Calculating gradient magnitude diagonal
/*    for (int i = 0; i < gradient_f.rows; i++) {
        for (int j = 0; j < gradient_f.cols; j++) {
            gradient_f.at<uchar>(i, j) = sqrt(pow(gradient_x.at<uchar>(i, j), 2) + pow(gradient_y.at<uchar>(i, j), 2));

            if (gradient_f.at<uchar>(i, j) > 240)
                gradient_f.at<uchar>(i, j) = 255;
            else
                gradient_f.at<uchar>(i, j) = 0;
        }
    }*/





/*imshow("grad x",gradient_x);
waitKey(0);*/


imshow("Diagonal edges",gradient_diag);
waitKey(0);

 /* imshow("Diagonal", gradient_f);
   waitKey(0);*/
}

//imshow("absolute grad magnitude",absGrad);
//  waitKey(0);

/*//Sobel edge detection function from OpenCV
    cv::Mat Gx, Gy; int ksize=3;
    Mat abs_grad_x, abs_grad_y;
    cv::Sobel(img_gray, Gx, CV_8U, 1, 0, ksize);
    convertScaleAbs( Gx, abs_grad_x );
    cv::Sobel(img_gray, Gy, CV_8U, 0, 1, ksize);
    convertScaleAbs( Gy, abs_grad_y );
    Mat grad;
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

    imshow("Sobel Image",grad);
    waitKey(0);

    return 0;

}*/


