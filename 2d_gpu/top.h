#pragma once

#define FRAME_HEIGHT 256
#define FRAME_WIDTH 256


class top {

public:
  int parseImage();
  int checkPixel(int x, int y);
  bool isPointInTriangle(int x, int y);
  int readStruct();
  int writeImage();
  int frame[FRAME_WIDTH][FRAME_HEIGHT];
  int vertices[3][2];
  int fillColor;

private:

};
