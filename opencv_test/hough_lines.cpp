// Yet another modified demo from docs.opencv.org

/**
 * @file HoughLines_Demo.cpp
 * @brief Demo code for Hough Transform
 * @author OpenCV team
 */

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

#define LEQ_4(L) (((L) > 8) ? 8 : (L))

using namespace cv;
using namespace std;

/// Global variables

/** General variables */
Mat src, edges;
Mat src_gray;
Mat phough;
int min_threshold = 50;
int max_trackbar = 150;

void PHough(int thresh, char*);

int main( int argc, char** argv )
{
  if (argc < 3)
  {
    fprintf(stderr, "Not enough args");
  }
  src = imread(argv[1], IMREAD_COLOR);

  /// Pass the image to gray
  cvtColor( src, src_gray, COLOR_RGB2GRAY );

  /* Blur the image to favour outer edges */
  //blur(src_gray, src_gray, Size(atoi(argv[4]), atoi(argv[4])));
  GaussianBlur(src_gray, src_gray, Size(atoi(argv[4]), atoi(argv[4])), 0, 0);


  /// Apply Canny edge detector
  Canny( src_gray, edges, 50, 200, 3 );

  /// Initialize
  PHough(atoi(argv[3]), argv[2]);
  return 0;
}

void PHough(int thresh, char* output_name)
{
  vector<Vec4i> p_lines;
  cvtColor( edges, phough, COLOR_GRAY2BGR );

  /// 2. Use Probabilistic Hough Transform
  HoughLinesP( edges, p_lines, 1, CV_PI/180, thresh, 30, 10 );

  sort(p_lines.begin(), p_lines.end(),
      [](const Vec4i &a, const Vec4i &b)
      {
        return (bool) ((a[2]-a[0])*(a[2]-a[0]) + (a[3]-a[1])*(a[3]-a[1])
        > (b[2]-b[0])*(b[2]-b[0]) + (b[3]-b[1])*(b[3]-b[1]));
      }
  );

  /* Draw the lines onto the image */
  for( size_t i = 0; i < LEQ_4(p_lines.size()); i++ )
     {
       Vec4i l = p_lines[i];
       line( phough, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
     }

   imwrite(output_name, phough);
}
