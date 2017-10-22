#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "../Shared/RubiksCube.h"
#include <iostream>
#include <cstdio>

/* General defines */
#define ORIG_OUTPUT  "../images/last_run/1_original.jpg"
#define NAME_LEN  128
#define DEBUG 1

/* Face-finding defines */
#define SMOOTH_OUTPUT "../images/last_run/2_smooth_output.jpg"
#define HOUGH_OUTPUT  "../images/last_run/3_hough_output.jpg"
#define CORNER_OUTPUT "../images/last_run/4_corner_output.jpg"
#define MAX_LINES  12
#define MIN_LINES   4

/* Affine transform defines */
#define AFFINE_OUTPUT "../images/last_run/5_affine_output.jpg"
#define AFFINE_OUTPUT_SIZE 100

/* Color detection defines */
#define COLOR_OUTPUT  "../images/last_run/6_color_output.jpg"


using namespace cv;
using namespace std;

int one_face(Mat* image, Color face[3][3], int calibrate);

int face_finder(Mat* image, int corner_coords[3][2]);

int face_affine(Mat* cube, int coords[3][2], Mat* face);

int face_colors(Mat* face, Color face_colors[3][3], int calibrate);
