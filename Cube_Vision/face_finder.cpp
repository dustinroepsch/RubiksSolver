#include "cube_vision.h"

#define MINIMUM(A,B) ((A) < (B) ? (A) : (B))
#define ABS(A) ((A) > 0 ? (A) : (-(A)))
#define DX(LINE) ((LINE)[2] - (LINE)[0])
#define DY(LINE) ((LINE)[3] - (LINE)[1])

#define THRESH       70
#define GAUSS_KER     3
#define MIN_LINE_LEN 10
#define MAX_LINE_GAP  3
#define SLOPE_TOL   0.1

/* Function to run probabilistic Hough, and output result with drawn lines */
void PHough(Mat* edges, int thresh, const string output_name, Mat* phough, int* num_lines, int best_lines[MAX_LINES][4]);

/* Given a set of lines (some roughly horizonatal, some roughly vertical), find horizontal (dy/dx) slope */
double horizontal_slope(int lines[MAX_LINES][4], int* num_lines);

/* Given the set of lines and a slope, finds the top-left, top-right, and bottom-right corners */
void find_corners(int lines[MAX_LINES][4], int num_lines, double slope, int width, int height, int corners[3][2]);

/* Given the original image, return three corner points */
int face_finder(Mat* image, int corner_coords[3][2])
{
  int i;
  /* Smoothed input */
  Mat smoothed;
  /* Grayscale copy of input */
  Mat image_gs;
  /* Edge-detection output */
  Mat edges;
  /* Hough output image */
  Mat phough;
  /* Corner output image */
  Mat corners;
  /* Array of longest lines, in form {x1, y1, x2, y2} */
  int long_lines[MAX_LINES][4];
  int num_lines;
  /* Slope (dy/dx) of roughly horizontal axis */
  double slope;

  /* Blur the image to favor outer edges? */
  //GaussianBlur(*image, smoothed, Size(GAUSS_KER, GAUSS_KER), 0, 0);
  //bilateralFilter(*image, smoothed, 10, 20, -1);
  blur(*image, smoothed, Size(3, 3));
  imwrite(SMOOTH_OUTPUT, smoothed); 

  /* Convert image to grayscale */
  cvtColor(smoothed, image_gs, COLOR_RGB2GRAY);

  /* Run edge detection and Hough */
  Canny(image_gs, edges, 50, 200, 3);
  PHough(&edges, THRESH, HOUGH_OUTPUT, &phough, &num_lines, long_lines);

  if (num_lines < MIN_LINES)
  {
    fprintf(stderr, "Error: too few lines found. Number found: %d\n", num_lines);
    return 1;
  }

  /* Find slope of "horizontal" cube axis */
  slope = horizontal_slope(long_lines, &num_lines);

  /* Find three necessary corner points */
  find_corners(long_lines, num_lines, slope, edges.cols, edges.rows, corner_coords);

  /* Plot three found points on result */
  corners = image->clone();
  for (i = 0; i < 3; ++i)
  {
    circle(
        corners,
        Point(corner_coords[i][0], corner_coords[i][1]),
        20,
        Scalar(255 * (i == 0), 255 * (i == 1), 255 * (i == 2)),
        10
    );

#if DEBUG
    /* Print what points are found for debugging */
    printf("Point %d: (%d, %d)\n", i, corner_coords[i][0], corner_coords[i][1]);
#endif
  }

  /* Save image with labeled corners */
  imwrite(CORNER_OUTPUT, corners);

  return 0;
}

void PHough(Mat* edges, int thresh, const string output_name, Mat* phough, int* num_lines, int best_lines[MAX_LINES][4])
{
  vector<Vec4i> p_lines;

  /* convert back to color and run Hough */
  cvtColor(*edges, *phough, COLOR_GRAY2BGR);
  HoughLinesP(*edges, p_lines, 1, CV_PI/360, thresh, MIN_LINE_LEN, MAX_LINE_GAP);

  /* sort lines by length */
  sort(p_lines.begin(), p_lines.end(),
      [](const Vec4i &a, const Vec4i &b)
      {
        return (bool) ((a[2]-a[0])*(a[2]-a[0]) + (a[3]-a[1])*(a[3]-a[1])
        > (b[2]-b[0])*(b[2]-b[0]) + (b[3]-b[1])*(b[3]-b[1]));
      }
  );

  /* Determine the number of stored best lines */
  *num_lines = MINIMUM(MAX_LINES, p_lines.size());

  /* Draw the lines onto the image, and save them into the array */
  for( size_t i = 0; (int)i < *num_lines; i++ )
     {
       Vec4i l = p_lines[i];
       line(*phough, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 7, LINE_AA);
       /* store x1, y1, x2, y2, respectively */
       best_lines[i][0] = l[0];
       best_lines[i][1] = l[1];
       best_lines[i][2] = l[2];
       best_lines[i][3] = l[3];
     }

   /* Save image with found lines to output */
   imwrite(output_name, *phough);
}

double horizontal_slope(int lines[MAX_LINES][4], int* num_lines)
{
  double horz, vert;
  int num_horz, num_vert;
  int i;
  int remove;

  /* Initialize variables for sum */
  horz = vert = 0.0;
  num_horz = num_vert = 0;

  /* Initially compute line counts and slope values */
  for (i = 0; i < *num_lines; ++i)
  {
    if (ABS(DX(lines[i])) > ABS(DY(lines[i])))
    {
      /* Add to horizontal slope */
      horz += DY(lines[i]) / (double) DX(lines[i]);
      num_horz++;
    }
    else 
    {
      /* Add to vertical slope */
      vert += DX(lines[i]) / (double) DY(lines[i]);
      num_vert++;
    }
  }

#if DEBUG
  printf("H: %lf, num_horz: %d\n", horz, num_horz);
  printf("V: %lf, num_vert: %d\n", vert, num_vert);
#endif

  /* Average all slopes */
  horz /= num_horz;
  vert /= num_vert;

  /* Check for and remove outlying lines */
  for (i = 0; i < *num_lines; ++i)
  {
    remove = 0;

    if (ABS(DX(lines[i])) > ABS(DY(lines[i])))
    {
      /* Remove horizontal outliers */
      if (ABS(horz - DY(lines[i]) / (double) DX(lines[i])) > SLOPE_TOL)
      {
        horz -= DY(lines[i]) / (double) DX(lines[i]) / num_horz;
        if (num_horz > 1)
          horz *= (num_horz) / (double) (num_horz - 1);
        num_horz--;
        remove = 1;
      }
    }
    else 
    {
      /* Remove vertical outliers */
      if (ABS(vert - DX(lines[i]) / (double) DY(lines[i])) > SLOPE_TOL)
      {
        vert -= DX(lines[i]) / (double) DY(lines[i]) / num_vert;
        if (num_vert > 1)
          vert *= (num_vert) / (double) (num_vert - 1);
        num_vert--;
        remove = 1;
      }
    }

    if (remove)
    {
      lines[i][0] = lines[*num_lines - 1][0];
      lines[i][1] = lines[*num_lines - 1][1];
      lines[i][2] = lines[*num_lines - 1][2];
      lines[i][3] = lines[*num_lines - 1][3];
      --(*num_lines);
    }
  }

  if (!num_vert || !num_horz)
  {
    fprintf(stderr, "Error: Only one direction of line found!\n");
    return 2;
  }

#if DEBUG
  /* Are slopes perpendicular? */
  printf("Horizontal: %lf\n", horz);
  printf("  Vertical: %lf\n", vert);
#endif

  return horz;
}

inline double x_intcpt(int x, int y, double m)
{
  return m * y + x;
}

inline double y_intcpt(int x, int y, double m)
{
  return y - m * x;
}

void find_corners(int lines[MAX_LINES][4], int num_lines, double slope, int width, int height, int corners[3][2])
{
  int i, j;
  /* Axis intercepts */
  double x_int, y_int;
  /* These store the point farthest in the given direction along the cube axis */
  int best_left[2]  = { width, height/2};
  int best_right[2] = {     0, height/2};
  int best_top[2]   = { width/2, height};
  int best_bot[2]   = { width/2,      0};
  double left, right, top, bot;

  /* LEFT and RIGHT are scored with photo x-intercept when extrapolated along the cube y-axis (-1/slope) */
  /* TOP AND BOTTOM are scored with photo y-intercept when extrapolated along the cube x-axis (slope) */
  left  = x_intcpt(best_left[0],  best_left[1],  slope);
  right = x_intcpt(best_right[0], best_right[1], slope);
  top   = y_intcpt(best_top[0],   best_top[1],   slope);
  bot   = y_intcpt(best_bot[0],   best_bot[1],   slope);

#if DEBUG
  printf("Number of lines we have: %d\n", num_lines);
  printf("Our horizontal slope is %lf\n", slope);
#endif

  /* For each line segment */
  for (i = 0; i < num_lines; ++i)
  {
    /* For each point (x, y) */
    for (j = 0; j < 4; j += 2)
    {
      x_int = x_intcpt(lines[i][j + 0], lines[i][j + 1], slope);
      y_int = y_intcpt(lines[i][j + 0], lines[i][j + 1], slope);

#if DEBUG
      /* Print all points and their respective Cartesian intercepts when debugging */
      printf("(%4d, %4d) -> x_int: %8.2lf, y_int: %8.2lf\n", lines[i][j + 0], lines[i][j + 1], x_int, y_int);
#endif

      /* Check if a new extreme left has been found */
      if (x_int < left)
      {
        best_left[0] = lines[i][j + 0];
        best_left[1] = lines[i][j + 1];
        left = x_int;
      }
      
      /* Check if a new extreme right has been found */
      if (x_int > right)
      {
        best_right[0] = lines[i][j + 0];
        best_right[1] = lines[i][j + 1];
        right = x_int;
      }

      /* Check if a new extreme top has been found */
      if (y_int < top)
      {
        best_top[0] = lines[i][j + 0];
        best_top[1] = lines[i][j + 1];
        top = y_int;
      }

      /* Check if a new extreme bottom has been found */
      if (y_int > bot)
      {
        best_bot[0] = lines[i][j + 0];
        best_bot[1] = lines[i][j + 1];
        bot = y_int;
      }

      /* Note: the first point should trigger all four of the above IFs */
    }
  }

#if DEBUG
  /* Print intercept extrema after checking all points */
  printf("(left, right, top, bot) = (%lf, %lf, %lf, %lf)\n", left, right, top, bot);
#endif

  /* Build the final three points: top-left, top-right, and bottom-right */
  /* These are points where the intercepts match the optimal */

  /* Top-Left corner, x then y */
  corners[0][0] = (int) ((left - slope * top)/(1 + slope*slope));
  corners[0][1] = (int) (slope * corners[0][0] + top);

  /* Top-Right corner, x then y */
  corners[1][0] = (int) ((right - slope * top)/(1 + slope * slope));
  corners[1][1] = (int) (slope * corners[1][0] + top);

  /* Bottom-Right corner, x then y */
  corners[2][0] = (int) ((right - slope * bot)/(1 + slope * slope));
  corners[2][1] = (int) (slope * corners[2][0] + bot);

  return;
}
