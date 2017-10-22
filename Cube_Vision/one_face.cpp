#include "cube_vision.h"

int one_face(Mat* image, Color face[3][3], int calibrate)
{
  /* Output of Affine Transformation */
  Mat affine_output, small;
  /* (x,y) for each of 3 corners */
  int corner_coords[3][2];
  /* Iterator variables for debug prints */
  int i, j;

  /* Store original image */
  imwrite(ORIG_OUTPUT, *image);

  /* Make image smaller for easier computation */
  resize(*image, small, Size(1000, 1000));

  /* Find the face in the image */
  face_finder(&small, corner_coords);
  
  /* Affine tranform the face to a square image */
  face_affine(&small, corner_coords, &affine_output);

  /* Sample face image to get square colors */
  face_colors(&affine_output, face, calibrate);

  if (!calibrate){
    for(i = 0; i < 3; ++i)
    {
      for (j = 0; j < 3; ++j)
      {
        cout << face[i][j] << " ";
      }
      cout << endl;
    }
  }

  return 0;
}
