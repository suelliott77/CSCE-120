# include <iostream>
# include <fstream>
# include <string>
# include <cmath>
# include "Image.h"
# include "Pixel.h"

using std::cout, std::endl, std::string, std::ifstream, std::ofstream;

// TODO: implement rule of three functions

Image::Image() : image(nullptr), width(0), height(0) {}

Image::Image(std::string filename) : image(nullptr), width(0), height(0) {
    load(filename);
}

Image::Image(unsigned int width, unsigned int height) : image(nullptr), width(0), height(0) {
    allocateImage(width, height);
}

Image::Image (const Image& oImage) : image(nullptr), width(0), height(0) {
    allocateImage(oImage.width, oImage.height);
    for(unsigned int i = 0; i < oImage.height; i++) {
        for(unsigned int j = 0; j < oImage.width; j++) {
            image[j][i].setRed(oImage.image[j][i].getRed());
            image[j][i].setGreen(oImage.image[j][i].getGreen());
            image[j][i].setBlue(oImage.image[j][i].getBlue());
        }
    }
}

Image& Image::operator=(const Image& copy){
    if(this != nullptr) {
        allocateImage(copy.width, copy.height);
        for(unsigned int i = 0; i < copy.height; i++) {
            for(unsigned int j = 0; j < copy.width; j++) {
                image[j][i].setRed(copy.image[j][i].getRed());
                image[j][i].setGreen(copy.image[j][i].getGreen());
                image[j][i].setBlue(copy.image[j][i].getBlue());
            }
        }
    }
    return *this;
}
Image::~Image(){clear();}

void Image::allocateImage(unsigned int width, unsigned int height) {
    clear();
    if (width > 1 && height > 1) {
        this->width = width;
        this->height = height;
        image = new Pixel*[width];

        for (unsigned int col = 0; col < width; col++) {
            image[col] = new Pixel[height];
        }
    }
}

void Image::clear() {
    // TODO: update for rule of three
    if(image == nullptr) { 
        width = 0;
        height = 0;
        return;
    }
    
    for(unsigned int i = 0; i < width; i++) {
        if(image[i]!=nullptr) {
            delete[] image[i];
            image[i] = nullptr;
            }
        }

    delete [] image;
    width = 0;
    height = 0;
    image = nullptr;
    
}

Pixel*& Image::operator[](unsigned int column) { return image[column]; }

const Pixel* Image::operator[](unsigned int column) const { return image[column]; }

unsigned int Image::getWidth() { return width; }

unsigned int Image::getHeight() { return height; }

void Image::load(string filename) {
    clear();

    cout << "Loading image..." << endl;
    ifstream ifs(filename);

    if (!ifs.is_open()) {
        cout << "Error: failed to open input file " << filename << endl;
        return;
    }

    string type;
    ifs >> type;
    if ((toupper(type.at(0)) != 'P') || (type.at(1) != '3')) {
        cout << "Error: type is " << type << "instead of P3" << endl;
        return;
    }

    int w = 0, h = 0;
    ifs >> w >> h;
    if (w < 1 || h < 1) {
        return;
    }

    int colorMax = 0;
    ifs >> colorMax;
    if (colorMax != 255) {
        cout << "Error: file is not using RGB color values." << endl;
        return;
    }

    allocateImage(w, h);

    if (width > 0 && height > 0) {
        for (unsigned int row = 0; row < height; row++) {
            for (unsigned int col = 0; col < width; col++) {
                int r, g, b;
                ifs >> r >> g >> b;
                image[col][row].setRed(r);
                image[col][row].setGreen(g);
                image[col][row].setBlue(b);
            }
        }
    }
}

void Image::output(string filename) {
    cout << "Outputting image..." << endl;
    ofstream ofs (filename);
  
    if (!ofs.is_open()) {
        cout << "Error: failed to open output file " << filename << endl;
        return;
    }
  
    ofs << "P3" << endl;
    ofs << width << " " << height << endl;
    ofs << 255 << endl;

    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int col = 0; col < width; col++) {
            ofs << image[col][row].getRed() << " ";
            ofs << image[col][row].getGreen() << " ";
            ofs << image[col][row].getBlue() << " ";
        }
        ofs << endl;
    }
}

void Image::makeGreyscale() {
    cout << "Making grayscale image... " << endl;
    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int col = 0; col < width; col++) {
            int greyColor = round((image[col][row].getRed() + image[col][row].getGreen() + image[col][row].getBlue()) / 3.0);
            image[col][row] = Pixel(greyColor, greyColor, greyColor);
        }
    }  
}

void Image::makeSepia() {
    cout << "Making sepia image... " << endl;
    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int col = 0; col < width; col++) {
            int newRed = round(0.393 * image[col][row].getRed() + 0.769 * image[col][row].getGreen() + 0.189 * image[col][row].getBlue());
            if (newRed > 255) newRed = 255;
            int newGreen = round((0.349 * image[col][row].getRed() + 0.686 * image[col][row].getGreen() + 0.168 * image[col][row].getBlue()));
            if (newGreen > 255) newGreen = 255;
            int newBlue = round((0.272 * image[col][row].getRed() + 0.534 * image[col][row].getGreen() + 0.131 * image[col][row].getBlue()));
            if (newBlue > 255) newBlue = 255;
            
            image[col][row] = Pixel(newRed, newGreen, newBlue);
        }
    }  
}

void Image::addColor(Pixel p) {
    for (unsigned int row = 0; row < height; row++) {
        for (unsigned int col = 0; col < width; col++) {
            image[col][row] = image[col][row] + p;
        }
    }  
}
