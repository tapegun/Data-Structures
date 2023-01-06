#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  image = png;
  startLoc = start;
  tol = tolerance;
  if(start.x < image.width() && start.y < image.height()){
    startLoc = start;
  }else{
    startLoc = Point(0,0);
  }
  visit.push_back(Point(start.x, start.y));
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  BFS* bfs = new BFS(image,startLoc,tol);
	return ImageTraversal::Iterator(*bfs, startLoc, image, tol);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}


/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  // if(point.x<image.width()&&point.y<image.height() && point.x>=0 && point.y >= 0){
    // if(visited[point.x][point.y] == false){
      visit.push_back(Point(point.x, point.y));
    
    // }
  // }
  // else{
  //   std::cout<<"not within bounds of image"<<std::endl;
  // }

}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point temp = Point(0,0);
  if(!visit.empty()){
  temp = visit.front();
  visit.erase(visit.begin());
  }
  return temp;

}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  if(!visit.empty()){
    return visit.front();
  }
  return Point(0, 0);
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return visit.empty();
}
