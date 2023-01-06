#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

#include <cstdlib>
#include <cmath>

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2

  PNG * input = new PNG();
  PNG * out = new PNG();
  (*input).readFromFile(inputFile);
  (*out).readFromFile(inputFile); // frankly dont wanna look up how to set height and width 
  unsigned width = input->width();
  unsigned height = input->height();
  for (unsigned r = 0; r < height; r++){
    for (unsigned c = 0; c < width; c++){
      HSLAPixel& currOutPixel = (*out).getPixel(width - c - 1, height - r - 1);
      HSLAPixel& currInputPixel = (*input).getPixel(c, r);
      currOutPixel = currInputPixel;   //we wanna make a copy of the pixel here so as to not tamper the original

    }
  }
  out->writeToFile(outputFile);
  delete out;
  delete input;

}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  //cs225::PNG png(width, height);
  PNG * png = new PNG(width, height);
  // TODO: Part 3
  if(width >= 3){  // making sure that I can make 3 colors next to each other
    for (unsigned int r = 0; r < height; r++){
      for (unsigned int c = 0; c < width; c++){
          HSLAPixel& pixel = png->getPixel(c,r);
          unsigned int third = width/3;
          pixel = HSLAPixel(190, .8, .5);
          if(c < 2 *third){
            pixel = HSLAPixel(60, .8, .5);
          }
          if(c < third){
            pixel = HSLAPixel(110, .8, .5);
          }

      }
    }
  }
  else{ // if it is a 2x2 image
    (png->getPixel(0,0)) =  HSLAPixel(190, .8, .5);
    (png->getPixel(0,1)) =  HSLAPixel(60, .8, .5);
    (png->getPixel(1,0)) =  HSLAPixel(110, .8, .5);
    (png->getPixel(1,1)) =  HSLAPixel(70, .8, .5);
  }

  return * png;
}
