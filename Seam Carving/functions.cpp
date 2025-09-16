#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using std::cout, std::endl, std::string;

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
  std::ifstream image_file;
  Pixel image_pixel;
  string type;
  int max_color;
  unsigned int width_input;
  unsigned int height_input;
  unsigned int more;

  image_file.open(filename); // Open file and check if it opened
  if (!image_file.is_open()) {
    throw std::runtime_error("Failed to open " + filename); 
  }

  image_file >> type; // Make sure correct type

  if ((type[0] == 'P' || type[0] == 'p') && type[1] == '3') {}
  else {
    throw std::runtime_error("Invalid type " + type);
  }

  image_file >> width_input; // Make sure dimensions are ok
  image_file >> height_input;
  if ((width_input > MAX_WIDTH) || (height_input > MAX_HEIGHT) || (width_input <= 0) || (height_input <= 0)) {
    throw std::runtime_error("Invalid dimensions");
  }
  width = width_input;
  height = height_input;

  image_file >> max_color; // Make sure max color is ok
  if (max_color != 255) {
    throw std::runtime_error("Invalid max color value");
  }
  
  for (unsigned int i = 0; i < height; ++i) {
    for (unsigned int j = 0; j < width; ++j) {
        image_file >> image_pixel.r; // Get each pixel and check for not enough
        if (image_file.fail()) {
          throw std::runtime_error("Not enough values");}
        image_file >> image_pixel.g;
        if (image_file.fail()) {
          throw std::runtime_error("Not enough values");}
        image_file >> image_pixel.b;
        if (image_file.fail()) {
          throw std::runtime_error("Not enough values");}
        if (image_pixel.r < 0 || image_pixel.r > 255) { // Checking for invalid
          throw std::runtime_error("Invalid color value");}
        if (image_pixel.g < 0 || image_pixel.g > 255) {
          throw std::runtime_error("Invalid color value");}
        if (image_pixel.b < 0 || image_pixel.b > 255) {
          throw std::runtime_error("Invalid color value");}

        image[j][i].r = image_pixel.r;
        image[j][i].g = image_pixel.g;
        image[j][i].b = image_pixel.b;
      }
    }
  while (!image_file.eof()) {
    image_file >> more;
    if (image_file.fail()) {
      break;
    }
    throw std::runtime_error("Too many values");
    
  }

  image_file.close();
}

void outputImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height) {
  std::ofstream image_file;
  image_file.open(filename);

  if (!image_file.is_open()) { // Check for error
    throw std::runtime_error("Failed to open " + filename); 
  }

  image_file << "P3" << endl; // Initial file components
  image_file << width << endl;
  image_file << height << endl;
  image_file << "255" << endl;

  for (unsigned int i = 0; i < height; ++i) { // Pixels
    for (unsigned int j = 0; j < width; ++j) {
      image_file << image[j][i].r << " " << image[j][i].g << " " << image[j][i].b << " ";
    }
    image_file << endl;
  }

  image_file.close();

}

unsigned int energy(Pixel image[][MAX_HEIGHT], unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
  unsigned int energy = 0;
  unsigned int x_energy = 0;
  unsigned int y_energy = 0;

  if (x == 0) { // Calculate x energy
    x_energy += pow(image[x+1][y].r - image[width-1][y].r, 2); // Left edge
    x_energy += pow(image[x+1][y].g - image[width-1][y].g, 2);
    x_energy += pow(image[x+1][y].b - image[width-1][y].b, 2);
  }

  else if (x == width-1) {
    x_energy += pow(image[0][y].r - image[x-1][y].r, 2); // Right edge
    x_energy += pow(image[0][y].g - image[x-1][y].g, 2);
    x_energy += pow(image[0][y].b - image[x-1][y].b, 2);
  }
  
  else {
    x_energy += pow(image[x+1][y].r - image[x-1][y].r, 2);
    x_energy += pow(image[x+1][y].g - image[x-1][y].g, 2);
    x_energy += pow(image[x+1][y].b - image[x-1][y].b, 2);
  }


  // Y energy
  if (y == height-1) {
    y_energy += pow(image[x][0].r - image[x][y-1].r, 2); // Bottom edge
    y_energy += pow(image[x][0].g - image[x][y-1].g, 2);
    y_energy += pow(image[x][0].b - image[x][y-1].b, 2);
  }

  else if (y == 0) {
    y_energy += pow(image[x][y+1].r - image[x][height-1].r, 2); // Top edge
    y_energy += pow(image[x][y+1].g - image[x][height-1].g, 2);
    y_energy += pow(image[x][y+1].b - image[x][height-1].b, 2);
  }
  else {
    y_energy += pow(image[x][y+1].r - image[x][y-1].r, 2); 
    y_energy += pow(image[x][y+1].g - image[x][y-1].g, 2);
    y_energy += pow(image[x][y+1].b - image[x][y-1].b, 2);
  }

  // Calculate total energy
  energy = y_energy + x_energy; 


  return energy;
}

// uncomment functions as you implement them (part 2)

unsigned int loadVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_col, unsigned int width, unsigned int height, unsigned int seam[]) {
  unsigned int seam_energy = 0;
  unsigned int forward;
  unsigned int right;
  unsigned int left;

  seam_energy += energy(image, start_col, 0, width, height); // Initialize
  seam[0] = start_col;

  for (unsigned int i = 1; i < height; ++i) { // For the whole picture

    if (start_col == 0) { // Left edge
      forward = energy(image, start_col, i, width, height);
      left = energy(image, start_col+1, i, width, height);

      if (forward <= left) { // Forward is the least
        seam_energy += forward; // Update total energy
        seam[i] = start_col; // Update array
      }
      else { // Left is the only other option
        start_col += 1;
        seam_energy += left; // Update total energy
        seam[i] = start_col; // Update array
      }
    }

    else if (start_col == width-1) { // Right edge
      forward = energy(image, start_col, i, width, height);
      right = energy(image, start_col-1, i, width, height);

      if (forward <= right) { // Forward is the least
        seam_energy += forward; // Update total energy
        seam[i] = start_col; // Update array
      }
      else { // Right is the only other option
        start_col -= 1;
        seam_energy += right; // Update total energy
        seam[i] = start_col; // Update array
      }
    }

    else { // Middle cases
      forward = energy(image, start_col, i, width, height);
      right = energy(image, start_col-1, i, width, height);
      left = energy(image, start_col+1, i, width, height);

      if ((forward <= left) && (forward <= right)) { // Forward is the least
        seam_energy += forward; // Update total energy
        seam[i] = start_col; // Update array
      }
      else if (left <= right) { // Left is the least
        start_col += 1; // Update column
        seam_energy += left;
        seam[i] = start_col;
      }
      else { // Right is the least
        start_col -= 1; // Update column
        seam_energy += right;
        seam[i] = start_col;
      }
    }
  }

  return seam_energy;
}

unsigned int loadHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_row, unsigned int width, unsigned int height, unsigned int seam[]) {
  unsigned int seam_energy = 0;
  unsigned int forward;
  unsigned int right;
  unsigned int left;

  seam_energy += energy(image, 0, start_row, width, height); // Initialize
  seam[0] = start_row;

  for (unsigned int i = 1; i < width; ++i) { // For the whole picture

    if (start_row == 0) { // Top edge
      forward = energy(image, i, start_row, width, height);
      right = energy(image, i, start_row+1, width, height);

      if (forward <= right) { // Forward is the least
        seam_energy += forward; // Update total energy
        seam[i] = start_row; // Update array
      }
      else { // Right is the only other option
        start_row += 1;
        seam_energy += right; // Update total energy
        seam[i] = start_row; // Update array
      }
    }

    else if (start_row == height-1) { // Bottom edge
      forward = energy(image, i, start_row, width, height);
      left = energy(image, i, start_row-1, width, height);

      if (forward <= left) { // Forward is the least
        seam_energy += forward; // Update total energy
        seam[i] = start_row; // Update array
      }
      else { // Left is the only other option
        start_row -= 1;
        seam_energy += left; // Update total energy
        seam[i] = start_row; // Update array
      }
    }

    else { // Middle cases
      forward = energy(image, i, start_row, width, height);
      left = energy(image, i, start_row-1, width, height);
      right = energy(image, i, start_row+1, width, height);

      if ((forward <= left) && (forward <= right)) { // Forward is the least
        seam_energy += forward; // Update total energy
        seam[i] = start_row; // Update array
      }
      else if (left <= right) { // Left is the least
        start_row -= 1; // Update column
        seam_energy += left;
        seam[i] = start_row;
      }
      else { // Right is the least
        start_row += 1; // Update column
        seam_energy += right;
        seam[i] = start_row;
      }
    }
  }

  return seam_energy;
}

void findMinVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
  unsigned int minimum; // Initialize
  unsigned int minimum_index;
  unsigned int next;

  minimum = loadVerticalSeam(image, 0, width, height, seam);
  minimum_index = 0;

  for (unsigned int i = 1; i < width; ++i) { // Go through whole picture
    next = loadVerticalSeam(image, i, width, height, seam);
    if (next < minimum) { // If new minimum
      minimum = next; // Update minimum
      minimum_index = i;
    }
  }
  loadVerticalSeam(image, minimum_index, width, height, seam);

}

void findMinHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
  unsigned int minimum; // Initialize
  unsigned int minimum_index;
  unsigned int next;

  minimum = loadHorizontalSeam(image, 0, width, height, seam);
  minimum_index = 0;

  for (unsigned int i = 1; i < height; ++i) { // Go through whole picture
    next = loadHorizontalSeam(image, i, width, height, seam);
    if (next < minimum) { // If new minimum
      minimum = next; // Update minimum
      minimum_index = i;
    }
  }
  loadHorizontalSeam(image, minimum_index, width, height, seam);

}

void removeVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int height, unsigned int verticalSeam[]) {

  unsigned int column;

  for (unsigned int j = 0; j < height; ++j) { // For each column
    column = verticalSeam[j];

    for (unsigned int i = column; i < width-1; ++i) { // For each number in each row

        image[i][j] = image[i+1][j]; // Shift right

    }
  }

  width -= 1; // Decrease width
}

void removeHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int& height, unsigned int horizontalSeam[]) {
  unsigned int row;

  for (unsigned int j = 0; j < width; ++j) { // For each row
    row = horizontalSeam[j];

    for (unsigned int i = row; i < height-1; ++i) { // For each number in each column

        image[j][i] = image[j][i+1]; // Shift down

    }
  }

  height -= 1; // Decrease height
}
