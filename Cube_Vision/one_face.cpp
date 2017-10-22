#include "cube_vision.h"

int one_face(Mat* image, Color face[3][3])
{
  /* Output of Affine Transformation */
  Mat affine_output;
  /* (x,y) for each of 3 corners */
  int corner_coords[3][2];
  /* Iterator variables for debug prints */
  int i, j;

  /* Store original image */
  imwrite(ORIG_OUTPUT, *image);

  /* Find the face in the image */
  face_finder(image, corner_coords);
  
  /* Affine tranform the face to a square image */
  face_affine(image, corner_coords, &affine_output);

  /* Sample face image to get square colors */
  face_colors(&affine_output, face);

  for(i = 0; i < 3; ++i)
  {
    for (j = 0; j < 3; ++j)
    {
      cout << face[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}
