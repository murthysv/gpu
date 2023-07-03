#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "top.h"


int main() {
  std::cout << "GPU Time!" << std::endl;
  top gpu; 
  gpu.readStruct();
  std::cout << gpu.vertices[0][0] << " " << gpu.vertices[0][1] << " " <<
   gpu.vertices[1][0] << " " << gpu.vertices[1][1] << " " <<
   gpu.vertices[2][0] << " " << gpu.vertices[2][1] << " " <<
   gpu.fillColor << std::endl;
  std::cout << "Done" << std::endl;
  gpu.parseImage();
  gpu.writeImage();
  return 0;
}

int top::readStruct() {
  std::ifstream inFile;
  std::string word;

  inFile.open("../tmp.txt");
  if (!inFile) {
    std::cout << "Unable to open file";
    exit(1); // terminate with error
  }

  for(int v = 0; v < 3; v++){
    for(int x = 0; x < 2; x++){
      getline(inFile, word, ' ');
      std::cout << word << std::endl;
      vertices[v][x] = stoi(word);
    } 
  }
  getline(inFile, word, ' ');
  fillColor = stoi(word, 0, 16); 
  return 0;
}

int top::parseImage() {
  for (int y = 0; y < FRAME_HEIGHT; y++) {
    for (int x = 0; x < FRAME_WIDTH; x++) {
      frame[x][y] = checkPixel(x,y);
    }
  }
  return 0;
}

int top::checkPixel(int x, int y) {
  int color;
  if(isPointInTriangle(x,y)) {
    color = fillColor;
  } else {
    color = 0x0;
  }
  return color;
}

bool top::isPointInTriangle(int x, int y){
    // Calculate barycentric coordinates
    float denominator = ((vertices[1][1] - vertices[2][1]) * (vertices[0][0] - vertices[2][0]) + (vertices[2][0] - vertices[1][0]) * (vertices[0][1] - vertices[2][1]));
    float w1 = ((vertices[1][1] - vertices[2][1]) * (x - vertices[2][0]) + (vertices[2][0] - vertices[1][0]) * (y - vertices[2][1])) / denominator;
    float w2 = ((vertices[2][1] - vertices[0][1]) * (x - vertices[2][0]) + (vertices[0][0] - vertices[2][0]) * (y - vertices[2][1])) / denominator;
    float w3 = 1.0f - w1 - w2;

    // Check if point is inside the triangle
    return (w1 >= 0 && w1 <= 1 && w2 >= 0 && w2 <= 1 && w3 >= 0 && w3 <= 1);
}


int top::writeImage() {
  std::ofstream outFile("image_tmp.txt");
  outFile << FRAME_WIDTH << " " << FRAME_WIDTH << std::endl;

  for (int y = 0; y < FRAME_HEIGHT; y++) {
    for (int x = 0; x < FRAME_WIDTH; x++) {
        outFile << frame[x][y] << std::endl;
    }
  }
  outFile.close();

  return 0;
}