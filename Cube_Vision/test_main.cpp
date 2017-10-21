#include "cube_vision.h"

using namespace std;

int main(int argc, char* argv[])
{
  /* Input image */
  Mat original;
  /* Other images */
  Mat finder_input, affine_input, affine_output;
  /* (x,y) for each of 3 corners */
  int corner_coords[3][2];
  /* Row-major matrix of colors on face */
  Color square_colors[3][3];

  if (argc < 2){
    cout << "Please give an input image filename" << endl;
    return 1;
  }

  /* Read an store original image */
  original = imread(argv[1]);
  imwrite(ORIG_OUTPUT, original);

  /* Copy input to be used later */ 
  finder_input = original.clone();
  affine_input = original.clone();

  /* Find the face in the image */
  face_finder(&finder_input, corner_coords);
  
  /* Affine tranform the face to a square image */
  face_affine(&affine_input, corner_coords, &affine_output);

  /* Sample face image to get square colors */
  face_colors(&affine_output, square_colors);

  return 0;
}
