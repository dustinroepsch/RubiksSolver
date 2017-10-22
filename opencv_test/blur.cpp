#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define DIAMETER     40
#define SIGMA_COLOR 100
#define SIGMA_SPACE  40

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
  Mat orig, blur;

  if (argc < 6){
    fprintf(stderr,
        "Please give input and output filenames through command line.\n");
    return 1;
  }

  /* Read in the image of the first argument */
  orig = imread(argv[1]);

  /* Copy space for the second image */
  //blur = orig.clone();

  /* Perform image blurring with bilateral filter */
  bilateralFilter(orig, blur, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

  imwrite(argv[2], blur);

  return 0;
}
