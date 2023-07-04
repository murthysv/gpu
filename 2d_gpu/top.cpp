#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "top.h"

int main() {

  std::cout << "GPU Time!" << std::endl;
  top gpu; 
  
  gpu.initFrameBuffer();
  gpu.readStruct();

  while(gpu.shapes.size()) {
    gpu.currentShape = gpu.shapes.front();
    gpu.shapes.pop();
    gpu.printVertices();
    gpu.parseShape();
  }

  gpu.writeImage();
  std::cout << "Done" << std::endl;
  return 0;
}

int top::printVertices() {
  std::cout << currentShape.vertices[0][0] << " " << currentShape.vertices[0][1] << " " <<
   currentShape.vertices[1][0] << " " << currentShape.vertices[1][1] << " " <<
   currentShape.vertices[2][0] << " " << currentShape.vertices[2][1] << " " <<
   currentShape.fillColor << std::endl;
   return 0;
}

int top::readStruct() {
  std::ifstream inFile;
  std::string word;

  inFile.open("tmp/tmp.txt");
  if (!inFile) {
    std::cout << "Unable to open file";
    exit(1); // terminate with error
  }
  
  while(!inFile.eof()) {
    shape s; 

    for(int v = 0; v < 3; v++){
      for(int x = 0; x < 2; x++){
        getline(inFile, word, ' ');
        std::cout << word << std::endl;
        s.vertices[v][x] = stoi(word);
      } 
    }
    getline(inFile, word, ' ');
    s.fillColor = stoi(word, 0, 16); 

    shapes.push(s);
  }
  
  return 0;
}

int top::initFrameBuffer() {
  for (int y = 0; y < FRAME_HEIGHT; y++) {
    for (int x = 0; x < FRAME_WIDTH; x++) {
      frame[x][y] = 0x0;
    }
  }
  return 0;
}

int top::parseShape() {
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
    color = currentShape.fillColor;
  } else {
    color = frame[x][y];
  }
  return color;
}

bool top::isPointInTriangle(int x, int y){
    // Calculate barycentric coordinates
    float denominator = ((currentShape.vertices[1][1] - currentShape.vertices[2][1]) * (currentShape.vertices[0][0] - currentShape.vertices[2][0]) + (currentShape.vertices[2][0] - currentShape.vertices[1][0]) * (currentShape.vertices[0][1] - currentShape.vertices[2][1]));
    float w1 = ((currentShape.vertices[1][1] - currentShape.vertices[2][1]) * (x - currentShape.vertices[2][0]) + (currentShape.vertices[2][0] - currentShape.vertices[1][0]) * (y - currentShape.vertices[2][1])) / denominator;
    float w2 = ((currentShape.vertices[2][1] - currentShape.vertices[0][1]) * (x - currentShape.vertices[2][0]) + (currentShape.vertices[0][0] - currentShape.vertices[2][0]) * (y - currentShape.vertices[2][1])) / denominator;
    float w3 = 1.0f - w1 - w2;

    // Check if point is inside the triangle
    return (w1 >= 0 && w1 <= 1 && w2 >= 0 && w2 <= 1 && w3 >= 0 && w3 <= 1);
}

int top::writeImage() {
  std::ofstream outFile("tmp/image_tmp.txt");
  outFile << FRAME_WIDTH << " " << FRAME_WIDTH << std::endl;

  for (int y = 0; y < FRAME_HEIGHT; y++) {
    for (int x = 0; x < FRAME_WIDTH; x++) {
        outFile << "#" << std::setfill('0') << std::hex <<  std::setw(6) << frame[x][y] << std::endl;
    }
  }
  outFile.close();

  return 0;
}