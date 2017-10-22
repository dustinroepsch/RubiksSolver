#include "cube_vision.h"

int face_affine(Mat* cube, int coords[3][2], Mat* face)
{
  Point2f srcTri[3];
  Point2f dstTri[3];

  Mat warp_mat(2, 3, CV_32FC1);

  /* Make the output image a small square */
  *face = Mat::zeros(AFFINE_OUTPUT_SIZE, AFFINE_OUTPUT_SIZE, face->type());

  /* Points are top-left, top-right, and bottom-right, respectively */
  dstTri[0] = Point2f(0 ,0);
  dstTri[1] = Point2f(face->cols - 1.f, 0);
  dstTri[2] = Point2f(face->cols - 1.f, face->rows - 1.f);

  /* Set source triangle from input coordinates */
  srcTri[0] = Point2f(coords[0][0], coords[0][1]);
  srcTri[1] = Point2f(coords[1][0], coords[1][1]);
  srcTri[2] = Point2f(coords[2][0], coords[2][1]);

  /* Get the Affine Transform */
  warp_mat = getAffineTransform(srcTri, dstTri);

  /* Affine transform image to be just cube face */
  warpAffine(*cube, *face, warp_mat, face->size());

  /* Output face image to use later */
  imwrite(AFFINE_OUTPUT, *face);

  return 0;
}

