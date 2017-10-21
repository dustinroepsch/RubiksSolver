#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "../Shared/RubiksCube.h"
#include <iostream>

/* General defines */
#define ORIG_OUTPUT  "../images/last_run/1_original.jpg"

/* Face-finding defines */
#define HOUGH_OUTPUT  "../images/last_run/2_hough_output.jpg"
#define CORNER_OUTPUT "../images/last_run/3_corner_output.jpg"
#define THRESH     70
#define GAUSS_KER   3
#define MAX_LINES  12
#define MIN_LINES   4

/* Affine transform defines */
#define AFFINE_OUTPUT "../images/last_run/4_affine_output.jpg"
#define AFFINE_OUTPUT_SIZE 100

using namespace cv;
using namespace std;

int face_finder(Mat* image, int corner_coords[3][2]);

int face_affine(Mat* cube, int coords[3][2], Mat* face);

int face_colors(Mat* face, Color face_colors[3][3]);
