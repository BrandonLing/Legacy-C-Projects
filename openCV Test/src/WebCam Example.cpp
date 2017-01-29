/*#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(){

    VideoCapture vcap(0);
      if(!vcap.isOpened()){
             cout << "Error opening video stream or file" << endl;
             return -1;
      }

   //int frame_width=   vcap.get(CV_CAP_PROP_FRAME_WIDTH);
   //int frame_height=   vcap.get(CV_CAP_PROP_FRAME_HEIGHT);
   //VideoWriter video("out.avi",CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height),true);

   for(;;){

       Mat frame;
       vcap >> frame;
       //video.write(frame);
       imshow( "Frame", frame );
       //imwrite("frame.jpg", frame);
       //break;

       //std::cout << frame.rows << "," << frame.cols << "\n";
       //std::cout << frame.total() << "\n";
       //std::cout << frame.channels() << "\n";
       //std::cout << frame.at<Vec3b>(0,0) << "\n";

       char c = (char)waitKey(33);
       if( c == 27 ) break;
    }
  return 0;
}


*/
