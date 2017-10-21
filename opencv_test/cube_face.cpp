// Modified from a published demo; given below:

/**
 * @function Geometric_Transforms_Demo.cpp
 * @brief Demo code for Geometric Transforms
 * @author OpenCV team
 */

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

#define S 3

using namespace cv;
using namespace std;

int get_colors(Mat* face);

int main( int, char** argv )
{
  Point2f srcTri[3];
  Point2f dstTri[3];

  Mat rot_mat( 2, 3, CV_32FC1 );
  Mat warp_mat( 2, 3, CV_32FC1 );
  Mat src, warp_dst, warp_rotate_dst;

  // Load the image
  src = imread( argv[1], IMREAD_COLOR );

  // Set the dst image the same type and size as src
  warp_dst = Mat::zeros( src.rows, src.cols, src.type() );

  // Set your 3 points to calculate the  Affine Transform
  dstTri[0] = Point2f( 0,0 );
  dstTri[1] = Point2f( src.cols - 1.f, 0 );
  dstTri[2] = Point2f( src.cols - 1.f, src.rows - 1.f );

  srcTri[0] = Point2f( 320, 245);
  srcTri[1] = Point2f( 495, 330);
  srcTri[2] = Point2f( 497, 552);

  // Get the Affine Transform
  warp_mat = getAffineTransform( srcTri, dstTri );

  // Apply the Affine Transform just found to the src image
  warpAffine( src, warp_dst, warp_mat, warp_dst.size() );

  imwrite(argv[2], warp_dst);

  get_colors(&warp_dst);

  return 0;
}

/* If image is a scaled Rubik's cube face, pull and print the center colors */
int get_colors(Mat* face)
{
  int row, col;     /* row/column of rubik's cube face */
  int x, y;         /* (x,y) coordinates corresponding to image */
  unsigned char* row_ptr; /* Color channel pointer */
  
  for (row = 0; row < S; ++row)
  {
    /* Compute the y coordinate and get a pointer for the row */
    y = (int) ((row + 0.5) / S * face->rows);
    row_ptr = face->ptr<unsigned char>(y);
    for (col = 0; col < S; ++col)
    {
      x = (int) ((col + 0.5) / S * face->cols);
      printf("(%3d, %3d, %3d), ",
          (int) row_ptr[3*x + 0],
          (int) row_ptr[3*x + 1],
          (int) row_ptr[3*x + 2]
      );
    }
    printf("\b\b\n");
  }
  
  return 0;
}
