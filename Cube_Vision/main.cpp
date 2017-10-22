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

int main(int argc, char* argv[])
{
  int i, j, face;
  /* Input image */
  Mat original;
  /* Other images */
  Mat finder_input, affine_input, affine_output;
  /* (x,y) for each of 3 corners */
  int corner_coords[3][2];
  /* Row-major matrix of colors on face */
  Color square_colors[3][3];
  /* Array for cube initializer */
  Color cube[6][3][3];
  /* String for image file name */
  char filename[NAME_LEN];
  /* Rubik's cube data structure */
  sp_rubiks_cube_t rubik;

  /* Store each face */
  for(face = 0; face < 6; ++face)
  {
    cout << "Next face: " << face_names[face][0] << ","
         <<  "with " << face_names[face][1] << " above." << endl;
    cout << "Please enter the path/filename of the image:" << endl;
    cin >> filename;

    /* Read an store original image */
    original = imread(filename);
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

    for(i = 0; i < 3; ++i)
    {
      for (j = 0; j < 3; ++j)
      {
        cube[face][i][j] = square_colors[i][j];
        cout << square_colors[i][j] << " ";
      }
      cout << endl;
    }
  }

  cout << cube;

  rubik = make_shared<Rubiks_Cube>(cube);

  return 0;
}
