#include "cube_vision.h"
#include "calibration.h"

Color get_color(int bgr[3]);

int face_colors(Mat* face, Color face_colors[3][3], int calibrate)
{
  /* row/column of rubik's cube face */
  int row, col;
  /* (x,y, channel) coordinates corresponding to image */
  int x, y, chan;
  /* Color channel pointer */
  unsigned char* row_ptr;
  /* Side length of face (number of squares) */
  int const S = 3;
  /* BGR values of face cells */
  int face_bgr[3][3][3];
  /* Image of isolated samples */
  Mat isolated;
  /* We need a generic iterator variable for calibration */
  int i;

  /* Blur input image; prepare isolated sample output */
  blur(*face, *face, Size(8, 8));
  isolated = Mat::zeros(face->rows, face->cols, face->type());

  /* For each of the three rows of squares */
  for (row = 0; row < S; ++row)
  {
    /* Compute the y coordinate and get a pointer for the row */
    y = (int) ((row + 0.5) / S * face->rows);
    row_ptr = face->ptr<unsigned char>(y);

    /* For each of the three squares in the row */
    for (col = 0; col < S; ++col)
    {
      /* Compute the x coordinate */
      x = (int) ((col + 0.5) / S * face->cols);

      /* Get each of the channel values */
      for (chan = 0; chan < 3; ++chan)
      {
        face_bgr[row][col][chan] = (int) row_ptr[3*x + chan];
      }

      /* Convert BGR to enum color for this square */
      face_colors[row][col] = get_color(face_bgr[row][col]);

      /* Add circle to isolated output image */
      circle(
          isolated,
          Point(x, y),
          15,
          Scalar(
            face_bgr[row][col][0],
            face_bgr[row][col][1],
            face_bgr[row][col][2]
          ),
          -1
      );
    }
  }

  /* Save output image */
  imwrite(COLOR_OUTPUT, isolated);

#if DEBUG
  /* Print color for debugging */
  for (row = 0; row < S; ++row)
  {
    for (col = 0; col < S; ++col)
    {
      printf("(%3d, %3d, %3d), ",
          (int) face_bgr[row][col][0],
          (int) face_bgr[row][col][1],
          (int) face_bgr[row][col][2]
      );
    }
    printf("\b\b\n");
  }
#endif

  if (calibrate){
    /* Print the calibration .h file */
    printf("int const exp_color[6][3] = \n{\n");
    for (i = 0; i < 6; ++i)
    {
      row = i / 3;
      col = i % 3;
      printf(
          "  { %3d, %3d, %3d}%c\n",
          face_bgr[row][col][0],
          face_bgr[row][col][1],
          face_bgr[row][col][2],
          i != 5 ? ',' : ' '
          );
    }
    printf("};\n");
  }

  return 0;
}

Color get_color(int bgr[3])
{
  int i;
  Color result;
  int square, best_square;

  best_square = INT_MAX;

  /* Find distance to each of the calibrated colors */
  for (i = 0; i < (int) Num_Colors; ++i)
  {
    square = (bgr[0]-exp_color[i][0])*(bgr[0]-exp_color[i][0])
           + (bgr[1]-exp_color[i][1])*(bgr[1]-exp_color[i][1])
           + (bgr[2]-exp_color[i][2])*(bgr[2]-exp_color[i][2]);

    if (square < best_square)
    {
      best_square = square;
      result = (Color) i;
    }
  }

  return result;
}
