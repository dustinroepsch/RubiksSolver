// From samples from online:
// http://answers.opencv.org/question/1/how-can-i-get-frames-from-my-webcam/
// https://stackoverflow.com/questions/14424325/opencv-cannot-acces-my-webcam


#include "opencv2/opencv.hpp"

using namespace cv;

int main(int argc, char** argv)
{
VideoCapture cap;
Mat frame;
// open the default camera, use something different from 0 otherwise;
// Check VideoCapture documentation.
if(!cap.open(0))
{
std::cout << "Camera open() failed" << std::endl;
return 0;
}

cap >> frame;
std::cout << "Is frame empty? " << frame.empty() << std::endl;
imwrite("../images/webcam.jpg", frame);

return 0;
}


/*
#include "cv.h" 
#include "highgui.h" 
#include <stdio.h>  
// A Simple Camera Capture Framework 
int main() {
  CvCapture* capture = cvCaptureFromCAM( CV_CAP_ANY );
  if ( !capture ) {
    fprintf( stderr, "ERROR: capture is NULL \n" );
    getchar();
    return -1;
  }
  // Create a window in which the captured images will be presented
  cvNamedWindow( "mywindow", CV_WINDOW_AUTOSIZE );
  // Show the image captured from the camera in the window and repeat
  while ( 1 ) {
    // Get one frame
    IplImage* frame = cvQueryFrame( capture );
    if ( !frame ) {
      fprintf( stderr, "ERROR: frame is null...\n" );
      getchar();
      break;
    }
    cvShowImage( "mywindow", frame );
    // Do not release the frame!
    //If ESC key pressed, Key=0x10001B under OpenCV 0.9.7(linux version),
    //remove higher bits using AND operator
    if ( (cvWaitKey(10) & 255) == 27 ) break;
  }
  // Release the capture device housekeeping
  cvReleaseCapture( &capture );
  cvDestroyWindow( "mywindow" );
  return 0;
}
*/
