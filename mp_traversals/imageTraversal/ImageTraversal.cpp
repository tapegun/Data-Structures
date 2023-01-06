#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"
#include <vector>
#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 
 */

double ImageTraversal::calculateDeltaHelper(const HSLAPixel & p1, const HSLAPixel & p2) {
  return calculateDelta(p1, p2);
}

double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() : traversal(NULL){
  /** @todo [Part 1] */
  visited.resize(image.height(), std::vector<bool>(image.width(), false));

}

ImageTraversal::Iterator::Iterator(ImageTraversal & traversal, const Point start, const PNG photo, double tolerance)
	:traversal(&traversal),init(start), tol(tolerance){
	curr = init;
  image = photo;
  visited.resize(image.height(), std::vector<bool>(image.width(), false));
  testVisit = PNG(image.width(), image.height());
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(!(traversal->empty())){
    curr = traversal->pop();
    // visited[curr.x][curr.y] = true;
    testVisit.getPixel(curr.x, curr.y).h = 100;
    // std::cout << curr << std::endl;

      // if(calculateDelta(image.getPixel(init.x, init.y),image.getPixel(curr.x + 1, curr.y))<tol){
    if(curr.x+1 < image.width()){
      traversal->add(Point(curr.x + 1, curr.y));
      // std::cout << curr.x + 1 << " " << curr.y << std::endl;
    }  
    if(curr.y+1 < image.height()){
      traversal->add(Point(curr.x, curr.y + 1));
      // std::cout << curr.x << " " << curr.y + 1<< std::endl;
    }  
    if(curr.x >= 1){
      traversal->add(Point(curr.x - 1, curr.y));
      // std::cout << curr.x - 1 << " " << curr.y << std::endl;
    }  
    if(curr.y >= 1){
      traversal->add(Point(curr.x, curr.y - 1));
      // std::cout << curr.x << " " << curr.y  - 1<< std::endl;
    } 
    bool mt = traversal->empty();
    bool inTolerance = true;
    bool visitHappened = true;
    while (!mt && (inTolerance || visitHappened))
    {
      curr = traversal->peek();
      if(curr.x<image.width() && curr.y<image.height() && curr.x >=0 && curr.y >= 0){
        inTolerance = calculateDelta(image.getPixel(curr.x, curr.y),image.getPixel(init.x, init.y)) >= tol;
        visitHappened = testVisit.getPixel(curr.x, curr.y).h == 100;
      }
      // std::cout <<" loop: " <<curr << " "<< visitHappened<< std::endl;
      if(inTolerance || visitHappened){
        traversal->pop();
      }
      mt = traversal->empty();
    }

  }
  if(traversal->empty()){
    traversal = NULL;
  }

  return *this;


}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool empty1; 
	bool empty2;

	if (traversal == NULL) { empty1 = true; }
  else{empty1 = false;}
	if (other.traversal == NULL) { empty2 = true; }
  else{empty2 = false;}
				
	if (!empty1)  { 
    empty1 = traversal->empty(); 
  }
	if (!empty2) { 
    empty2 = other.traversal->empty(); 
    }
			
	if (empty1 && empty2) 
    return false; 
	else if ((!empty1)&&(!empty2))
   return (traversal != other.traversal); 
	return true; 
}

