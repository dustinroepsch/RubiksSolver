#include "cube_vision.h" 
using namespace std;

/* For each face, store color of face and color of face above */
static char const * const face_names[6][2] = 
{
  { "White", "Red"},
  {   "Red", "Yellow"},
  {  "Blue", "Red"},
  { "Green", "Red"},
  {"Yellow", "Red"},
  {"Orange", "White"}
};

static char const* const directions[2] =
  {"Clockwise", "Counter-clockwise"};

int main(int argc, char* argv[])
{
  int i, j, face;
  /* Input image */
  Mat original;
  /* Row-major matrix of colors on face */
  Color square_colors[3][3];
  /* Array for cube initializer */
  Color cube[6][3][3];
  /* String for image file name */
  char filename[NAME_LEN];
  /* Rubik's cube data structure */
  sp_rubiks_cube_t rubik;
  /* Solution */
  int num_steps, steps[20];

  /* Store each face */
  for(face = 0; face < 6; ++face)
  {
    cout << "Next face: " << face_names[face][0] << ","
         << " with " << face_names[face][1] << " above." << endl;
    cout << "Please enter the path/filename of the image:" << endl;
    //cin >> filename;
    sprintf(filename, "../b/f%d.jpg", face + 1);

    /* Read, resize and store original image */
    original = imread(filename);

    /* Run algorithm on image of one face */
    one_face(&original, square_colors, 0);
    square_colors[1][1] = (Color) face;

    /* Assign face to cube array */
    for(i = 0; i < 3; ++i)
    {
      for (j = 0; j < 3; ++j)
      {
        cube[face][i][j] = square_colors[i][j];
      }
    }
  }

  rubik = make_shared<Rubiks_Cube>(cube);
  
  num_steps = rubik->solve(steps);

  cout << "Number of required steps: " << num_steps << endl;

  for (i = 0; i < num_steps; ++ i)
  {
    printf("%d: Turn the %s face %s\n", (i + 1), face_names[(steps[i] > 0 ? steps[i] : -steps[i]) - 1][0], directions[steps[i] > 0 ? 0 : 1]);
  }

  return 0;
}
