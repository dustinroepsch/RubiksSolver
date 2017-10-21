#include "cube_vision.h"

Color get_color(int bgr[3]);

int face_colors(Mat* face, Color face_colors[3][3])
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

      /* Print color for debugging */
      printf("(%3d, %3d, %3d), ",
          (int) face_bgr[row][col][0],
          (int) face_bgr[row][col][1],
          (int) face_bgr[row][col][2]
      );
    }
    printf("\b\b\n");
  }

  return 0;
}

Color get_color(int bgr[3])
{
  return Blue;
}
