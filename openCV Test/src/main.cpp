#include "main.h"
/*
int main( int argc, char** argv )
{
    //Init camera
    cv::VideoCapture vcap(0);
    if (!vcap.isOpened())
    {
        std::cout << "Error opening video stream\n";
        return -1;
    }

    //Init variables
    bool quitFlag = false; //quitFlag for program
    cv::Mat frame0; //reference frame
    vcap >> frame0;
    int cols = frame0.cols; int rows = frame0.rows;

    while (!quitFlag)
    {
        cv::Mat frame1;
        vcap >> frame1;

        //init difference Frame
        cv::Mat diffFrame = abs(frame1 - frame0); //sets size
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                int b1 = (int)diffFrame.at<cv::Vec3b>(r, c)[0];
                int g1 = (int)diffFrame.at<cv::Vec3b>(r, c)[1];
                int r1 = (int)diffFrame.at<cv::Vec3b>(r, c)[2];
                int curVal = b1*b1 + g1*g1 + r1*r1;
                if (curVal < 5000)//experimentally determined threshhold
                {
                    diffFrame.at<cv::Vec3b>(r, c)[0] = 0;
                    diffFrame.at<cv::Vec3b>(r, c)[1] = 0;
                    diffFrame.at<cv::Vec3b>(r, c)[2] = 0;
                }
                else
                {
                    diffFrame.at<cv::Vec3b>(r,c) = frame1.at<cv::Vec3b>(r,c);
                }

            }
        }


        imshow( "Frame", diffFrame);
        char c = (char)cv::waitKey(33);
        if (c == 27) //escape
        {
            quitFlag = true;
        }
    }

    return 0;
}
*/

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <string>
#include <stdio.h>

using namespace cv;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
const std::string window_name = "Edge Map";

void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );

  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);

  src.copyTo( dst, detected_edges);
  imshow( window_name, dst );
 }


int main( int argc, char** argv )
{
  /// Load an image
  src = imread( "img.jpg" );

  if( !src.data )
  { return -1; }

  /// Create a matrix of the same type and size as src (for dst)
  dst.create( src.size(), src.type() );

  /// Convert the image to grayscale
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Create a window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Create a Trackbar for user to enter threshold
  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

  /// Show the image
  CannyThreshold(0, 0);

  /// Wait until user exit program by pressing a key
  waitKey(0);

  return 0;
  }
