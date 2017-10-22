#include "cube_vision.h"

using namespace std;

int main(int argc, char* argv[])
{
  /* Input image */
  Mat original;
  /* Row-major matrix of colors on face */
  Color square_colors[3][3];

  if (argc < 2){
    cout << "Please give an input image filename" << endl;
    return 1;
  }

  /* Read the original image */
  original = imread(argv[1]);

  /* Run the complete one-face vision algorithm on this image */
  one_face(&original, square_colors, CALIBRATE);

  return 0;
}
