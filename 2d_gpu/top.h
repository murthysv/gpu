#pragma once
#include <queue>


#define FRAME_HEIGHT 256
#define FRAME_WIDTH 256


class top {

  typedef struct 
  {
    int vertices[3][2];
    int fillColor;
  } shape;

public:
  int frame[FRAME_WIDTH][FRAME_HEIGHT];
  std::queue<shape> shapes;
  shape currentShape;
  int parseShape();
  int checkPixel(int x, int y);
  int readStruct();
  int printVertices();
  int writeImage();
  int initFrameBuffer();
  bool isPointInTriangle(int x, int y);


  
  

private:

};
