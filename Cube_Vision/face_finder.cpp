#include "cube_vision.h"

/* Function to run probabilistic Hough, and output result with drawn lines */
void PHough(Mat* edges, int thresh, const string output_name, Mat* phough);

/* Given the original image, return three corner points */
int face_finder(Mat* image, int corner_coords[3][2])
{
  /* Grayscale copy of input */
  Mat image_gs;
  /* Edge-detection output */
  Mat edges;
  /* Hough output image */
  Mat phough;

  /* Convert image to grayscale */
  cvtColor(*image, image_gs, COLOR_RGB2GRAY);

  /* Blur the image to favor outer edges? */
  GaussianBlur(image_gs, image_gs, Size(GAUSS_KER, GAUSS_KER), 0, 0);

  /* Run edge detection and Hough */
  Canny(image_gs, edges, 50, 200, 3);
  PHough(&edges, THRESH, HOUGH_OUTPUT, &phough);

  corner_coords[0][0] = 320;
  corner_coords[0][1] = 245;
  corner_coords[1][0] = 495;
  corner_coords[1][1] = 330;
  corner_coords[2][0] = 497;
  corner_coords[2][1] = 552;

  return 0;
}

void PHough(Mat* edges, int thresh, const string output_name, Mat* phough)
{
  vector<Vec4i> p_lines;

  /* convert back to color and run Hough */
  cvtColor(*edges, *phough, COLOR_GRAY2BGR);
  HoughLinesP(*edges, p_lines, 1, CV_PI/180, thresh, 30, 10 );

  /* sort lines by length */
  /*
  sort(p_lines.begin(), p_lines.end(),
      [](const Vec4i &a, const Vec4i &b)
      {
        return (bool) ((a[2]-a[0])*(a[2]-a[0]) + (a[3]-a[1])*(a[3]-a[1])
        > (b[2]-b[0])*(b[2]-b[0]) + (b[3]-b[1])*(b[3]-b[1]));
      }
  );
  */

  /* Draw the lines onto the image */
  for( size_t i = 0; i < p_lines.size(); i++ )
     {
       Vec4i l = p_lines[i];
       line(*phough, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 3, LINE_AA);
     }

   imwrite(output_name, *phough);
}
