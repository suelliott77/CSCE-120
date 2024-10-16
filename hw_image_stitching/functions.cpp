#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

void loadCorners(std::string filename, Corner imageCorners[MAX_CORNERS], unsigned int& numberOfCorners){
    // Read load corners file
    ifstream ifs;
    numberOfCorners = 0;
    unsigned int x = 0;
    unsigned int y = 0;

    ifs.open(filename);
        if (!ifs.is_open()) { 
            throw runtime_error("Failed to open " + filename);
        }
    
    for (unsigned int i = 0; i < 100; i++) {
        ifs >> x >> y;
        if (!ifs.fail()) {
            imageCorners[i].x = x;
            imageCorners[i].y = y;
            numberOfCorners++;
        }
    }

    if (numberOfCorners >= MAX_CORNERS) {
        throw runtime_error("Too many corners in " + filename);
    }

}

double errorCalculation(Pixel image1[][MAX_HEIGHT], const unsigned int width1, const unsigned int height1,
                      Corner image1corner,
                      Pixel image2[][MAX_HEIGHT], const unsigned int width2, const unsigned int height2,
                      Corner image2corner){
            
    // Error calculation
    double error = 0;
    double r;
    double g;
    double b;

    int x1 = image1corner.x - ERROR_NEIGHBORHOOD_SIZE / 2;
    int y1 = image1corner.y - ERROR_NEIGHBORHOOD_SIZE / 2;
    int x2 = image2corner.x - ERROR_NEIGHBORHOOD_SIZE / 2;
    int y2 = image2corner.y - ERROR_NEIGHBORHOOD_SIZE / 2;

    //checking for infinity 
    if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) {
        return INFINITY;
    }

    // checking if values are greater than given width and height
    if (x1 + ERROR_NEIGHBORHOOD_SIZE > width1 || y1 + ERROR_NEIGHBORHOOD_SIZE > height1 ||
        x2 + ERROR_NEIGHBORHOOD_SIZE > width2 || y2 + ERROR_NEIGHBORHOOD_SIZE > height2) {
            return INFINITY;
    }

    // after checking for infinity 
    for (unsigned int i = 0; ERROR_NEIGHBORHOOD_SIZE > i; i++) {
        for (unsigned int j = 0; ERROR_NEIGHBORHOOD_SIZE > j; j++) {
            int onex = i + x1;
            int oney = j + y1;
            int twox = i + x2;
            int twoy = j + y2;

            r = abs(image1[onex][oney].r - image2[twox][twoy].r);
            g = abs(image1[onex][oney].g - image2[twox][twoy].g);
            b = abs(image1[onex][oney].b - image2[twox][twoy].b);

            error += (r+g+b);
        }
    } 
    return error;
    
}

void matchCorners(CornerPair matchedPairs[MAX_CORNERS], unsigned int &matched_count,
                  Pixel image1[][MAX_HEIGHT], const unsigned int width1, const unsigned int height1,
                  Corner image1corners[], unsigned int image1CornerCount,
                  Pixel image2[][MAX_HEIGHT], const unsigned int width2, const unsigned int height2,
                  Corner image2corners[], unsigned int image2CornerCount){

    // Greedy corner matching goes here
    matched_count = 0;

    // An array to keep track of used corners in image2
    bool usedCorners[MAX_CORNERS] = {false};

    // Loop over corners in image1
    for (unsigned int i = 0; i < image1CornerCount; ++i) {
        double minError = std::numeric_limits<double>::infinity();
        int minErrorCornerIndex = -1;

        // Calculate error with all corners in image2
        for (unsigned int j = 0; j < image2CornerCount; ++j) {
            if (!usedCorners[j]) {
                double error = errorCalculation(image1, width1, height1, image1corners[i],
                                                image2, width2, height2, image2corners[j]);
                // Keep track of the minimum error and the corresponding corner
                if (error < minError) {
                    minError = error;
                    minErrorCornerIndex = j;
                }
            }
        }

        // Test the minimum error
        if (minError < std::numeric_limits<double>::infinity()) {
            // Add the matched pair and mark the corner from image2 as used
            matchedPairs[matched_count].image1Corner = image1corners[i];
            matchedPairs[matched_count].image2Corner = image2corners[minErrorCornerIndex];
            matchedPairs[matched_count].error = minError;
            ++matched_count;
            usedCorners[minErrorCornerIndex] = true;
        }
    }
    
}

void mapCoordinates(const double H[3][3], unsigned int x, unsigned int y,
                    double& mapped_x, double& mapped_y){

    // Mapping function for this week
    double w = H[2][0] * x + H[2][1] * y + H[2][2];
    mapped_x = (H[0][0] * x + H[0][1] * y + H[0][2]) / w;
    mapped_y = (H[1][0] * x + H[1][1] * y + H[1][2]) / w;
    
}

void mergeImages( Pixel image1[][MAX_HEIGHT], unsigned int &width1, unsigned int &height1,
                  Pixel image2[][MAX_HEIGHT], const unsigned int width2, const unsigned int height2,
                  double H[3][3] ) {
        
    // Similar to image scaling function from last week with some additional steps.
    double mappedX = 0;
    double mappedY = 0;

    Pixel I1_pixel = {0,0,0};
    Pixel I2_pixel = {0,0,0};
    Pixel newPixel = {0,0,0};

    // iterate through entire buffer 
    for (unsigned int currCol = 0; currCol < MAX_WIDTH; currCol++) {
        for (unsigned int currRow = 0; currRow < MAX_HEIGHT; currRow++) {

            // each iteration assign the IX_pixels with an impossible r value to check if they've been changed
            I1_pixel.r = INT16_MAX;
            I2_pixel.r = INT16_MAX;

            // check if mapped coordinates is in bound of image 2
            mapCoordinates(H, currCol, currRow, mappedX, mappedY);
            if (mappedX >= 0 && mappedX < width2 && mappedY >= 0 && mappedY < height2) {
                I2_pixel = bilinear_interpolation(image2, width2, height2, mappedX, mappedY);
            }

            // chekcs if current pixel is within bounds of image 1
            if (currCol < width1 && currRow < height1) {
                I1_pixel = {image1[currCol][currRow].r, image1[currCol][currRow].g, image1[currCol][currRow].b};
            }

            // if both pixels have good values 
            if (I1_pixel.r != INT16_MAX && I2_pixel.r != INT16_MAX) {
                newPixel = {static_cast<short>((I1_pixel.r + I2_pixel.r) / 2), static_cast<short>((I1_pixel.g + I2_pixel.g) / 2), static_cast<short>((I1_pixel.b + I2_pixel.b) / 2) };
            }
            
            // if both pixels have bad r values 
            else if (I1_pixel.r == INT16_MAX && I2_pixel.r == INT16_MAX) {
                newPixel = {0,0,0};
            }

            // if only one of them has good values 
            else if (I1_pixel.r != INT16_MAX) {
                newPixel = {I1_pixel.r, I1_pixel.g, I1_pixel.b};
            }
            
            else {
                newPixel = {I2_pixel.r, I2_pixel.g, I2_pixel.b};
            }

            image1[currCol][currRow] = newPixel;
        }
    }

    width1 = MAX_WIDTH;
    height1 = MAX_HEIGHT;
}