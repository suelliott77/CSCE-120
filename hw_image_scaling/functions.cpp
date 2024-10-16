#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

void initializeImage(Pixel image[][MAX_HEIGHT]) {
  // iterate through columns
  for (unsigned int col = 0; col < MAX_WIDTH; col++) {
    // iterate through rows
    for (unsigned int row = 0; row < MAX_HEIGHT; row++) {
      // initialize pixel
      image[col][row] = {0, 0, 0};
    }
  }
}

void loadImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int& height) {
// TODO: implement image loading
ifstream ifs; // input file stream
string type;
short pixel_r; // red
short pixel_g; // green
short pixel_b; // blue 
int colorMax;
height = 0;
width = 0;

//ensures the file opened 
ifs.open(filename);
if (!ifs.is_open()) { 
  throw runtime_error("Failed to open " + filename);
}

// checks the type of the file 
ifs >> type;
if (type != "P3" && type != "p3") {
  throw runtime_error("Invalid type" + type);
}

// checking the dimensions
ifs >> width;
ifs >> height;
if (width > MAX_WIDTH || height > MAX_HEIGHT || height <= 0 || width <= 0) {
  throw runtime_error("Invalid Dimensions");
}

// checking the color value 
ifs >> colorMax;
if (colorMax > 255 || colorMax < 0) {
  throw runtime_error("Invalid color value");
}

unsigned int row = 0;
unsigned int col = 0;
// checking each indivdual color 
for (row = 0; height > row; ++row) { // row major so height is the 1d index aka height
    for(col = 0; width > col; ++col) {
      ifs >> pixel_r;
      ifs >> pixel_g;
      ifs >> pixel_b;
      if (!ifs.fail()) { // checks enough data for 3 pixels each
        if (pixel_r < 0 || pixel_r > colorMax) {
          throw runtime_error("Invalid color value");
        }
        if (pixel_g < 0 || pixel_g > colorMax) {
          throw runtime_error("Invalid color value");
        }
        if (pixel_b < 0 || pixel_b > colorMax) {
          throw runtime_error("Invalid color value");
        }
      }
      else { // if not enough data for pixel
        throw runtime_error("Invalid color value");
      }
      image[col][row].r = pixel_r;
      image[col][row].g = pixel_g;
      image[col][row].b = pixel_b;
    }
    col = 0;
  }
  int space;
  ifs >> space;
  if (!ifs.fail()) {
    throw runtime_error("Too many values");
  }
  ifs.close();
}

void outputImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height) {
  ofstream ofs(filename);

  if (!ofs.is_open()) { 
    throw runtime_error("Failed to open " + filename);
  }

  //output preamble
  ofs << "P3" << endl;
  ofs << width << " " << height << endl;
  ofs << 255 << endl;

  //output pixels
  unsigned int rows = 0;
  unsigned int cols = 0;
  for (rows = 0; height > rows; ++rows) {
    for (cols = 0; width > cols; ++cols) {
      ofs << image[cols][rows].r << " ";
      ofs << image[cols][rows].g << " ";
      ofs << image[cols][rows].b << " ";
      ofs << endl;
    }
    cols = 0;
  }

}

double map_coordinates(unsigned int source_dimension, unsigned int target_dimension, unsigned int pixel_coordinate){
  // TODO: implement mapping function.
  double source = source_dimension;
  double target = target_dimension;
  double pixel = pixel_coordinate;

  double final = ((source - 1) / (target - 1) * pixel);

  return final;
  
}

Pixel bilinear_interpolation(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, double x, double y) {
  // TODO: Implement bilinear interpolation
  int x_floor = floor(x);
  int x_ceil = ceil(x);
  int y_floor = floor(y);
  int y_ceil = ceil(y);

  width += 1;
  height += 1;

  Pixel Final;

  if (x_floor == x_ceil) {
    x_ceil += 1;
  }
  if (y_floor == y_ceil) {
    y_ceil += 1;
  }

  double red1 = (((x - x_floor) * image[x_ceil][y_floor].r) + ((x_ceil - x) * image[x_floor][y_floor].r));
  double green1 = (((x - x_floor) * image[x_ceil][y_floor].g) + ((x_ceil - x) * image[x_floor][y_floor].g));
  double blue1 = (((x - x_floor) * image[x_ceil][y_floor].b) + ((x_ceil - x) * image[x_floor][y_floor].b));

  double red2 = ((x - x_floor) * image[x_ceil][y_ceil].r) + ((x_ceil - x) * image[x_floor][y_ceil].r);
  double green2 = ((x - x_floor) * image[x_ceil][y_ceil].g) + ((x_ceil - x) * image[x_floor][y_ceil].g);
  double blue2 = ((x - x_floor) * image[x_ceil][y_ceil].b) + ((x_ceil - x) * image[x_floor][y_ceil].b);

  double red3 = round(((y_ceil - y) * red1) + ((y - y_floor) * red2));
  double green3 = round(((y_ceil - y) * green1) + ((y - y_floor) * green2));
  double blue3 = round(((y_ceil - y) * blue1) + ((y - y_floor) * blue2));
  Final = {short(red3), short(green3), short(blue3)};

  return Final;

}


void scale_image(Pixel sourceImage[][MAX_HEIGHT], unsigned int sourceWidth, unsigned int sourceHeight, Pixel targetImage[][MAX_HEIGHT], unsigned int targetWidth, unsigned int targetHeight){
    unsigned int i = 0;
    unsigned int j = 0;
    double w;
    double h;

    for (i = 0; targetHeight > i; ++i) {
      for (j = 0; targetWidth > j; ++j) {
        w = map_coordinates(sourceWidth, targetWidth, j); // use as double x
        h = map_coordinates(sourceHeight, targetHeight, i); // use as double y
        targetImage[j][i] = bilinear_interpolation(sourceImage, sourceWidth, sourceHeight, w, h);

      }
      j = 0;
    }   
}