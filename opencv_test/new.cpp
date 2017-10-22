#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define DIAMETER     40
#define SIGMA_COLOR 100
#define SIGMA_SPACE  40

#define S 3

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
  Mat orig, blurred, edges_big, edges_fin;

  if (argc < 6){
    fprintf(stderr,
        "Please give input and output filenames through command line.\n");
    return 1;
  }

  /* Read in the image of the first argument */
  orig = imread(argv[1]);

  /* Perform image blurring with bilateral filter */
  bilateralFilter(orig, blur, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
  //blur(orig, blurred, Size(3,3));
  imwrite("temp_blur.jpg", blurred);

  /* Do Sobel for edge detection */
  Sobel(blurred, edges_big, CV_16S, 1, 1, 5);
  convertScaleAbs(edges_big, edges_fin);

  imwrite(argv[2], edges_fin);
  
  return 0;
}

