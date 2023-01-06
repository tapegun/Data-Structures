/* Your code here! */
/**
 * @file maze.h
 */


#include <cstdlib>
#include <vector>
#include <queue>
#include <time.h>       /* time */
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
using namespace std;
using namespace cs225;
#pragma once

class SquareMaze
{
	public:
		SquareMaze();
		void makeMaze (int width, int height);
		bool canTravel (int x, int y, int dir) const;
		void setWall (int x, int y, int dir, bool exists);
		vector<int> solveMaze ();
		PNG * drawMaze () const;
		PNG * drawMazeWithSolution ();


	private:
		vector<vector<vector<bool>>> walls;
		int width;
		int height;
		//Helper functions

		bool isvalid (int x, int y) const ;
		int location(int x, int y) const ;
		pair<int,int> translateLocation(int position) const ;
		vector<int> bestPath() ;
		vector<int> getneighbor(int vertex) ;
		int worstPath(vector<int>& distance_map) ;
		int getdirection(int parent, int vertex) ;

};