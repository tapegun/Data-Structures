
#include "maze.h"
#include <stdio.h>      
#include <math.h>       


SquareMaze::SquareMaze () {

	//default ctor
}


bool SquareMaze::canTravel ( int x, int y, int dir ) const {
	if (!isvalid(x,y)) return false;
	if (dir==0 && isvalid(x+1,y) && walls[x][y][0]==false) {
		return true;
		}
	else if (dir==1 && isvalid(x,y+1) && walls[x][y][1]==false) {
		return true;
		}
	else if (dir==2 && isvalid(x-1,y) && walls[x-1][y][0]==false) {
		return true;
		}
	else if (dir==3 && isvalid(x,y-1) && walls[x][y-1][1]==false) {
		return true;
		}
	return false;
}


void SquareMaze::setWall ( int x, int y, int dir, bool exists ) {
	if (isvalid(x,y))
	{
		walls[x][y][dir] = exists;
	}
}

vector<int> SquareMaze::solveMaze () {
	vector<int> path = bestPath();
	std::reverse(path.begin(),path.end());
	return path;
}

PNG * SquareMaze::drawMaze () const {
	int image_width = width*10+1;
	int image_height = height*10+1;
	PNG* Img = new PNG(image_width, image_height);

	HSLAPixel dark(0, 0, 0);

	for (int i = 0; i<image_width; i++) {
		if (i<1 || i>9) {					//edges
			HSLAPixel & pxl = Img->getPixel(i, 0);
			pxl.s = dark.s;
			pxl.h = dark.h;
			pxl.l = dark.l;
		}
	}
	for (int i = 0; i<image_height; i++) {		//inside
		HSLAPixel & pxl = Img->getPixel(0, i);
		pxl.s = dark.s;
		pxl.h = dark.h;
		pxl.l = dark.l;
	}
	for (int x=0; x<width; x++) {
		for (int y=0; y<height; y++) {
			if (walls[x][y][0]) {
				for (int k=0; k<=10; k++) {
					HSLAPixel & pxl = Img->getPixel((x+1)*10, y*10+k);
					pxl.s = dark.s;
					pxl.h = dark.h;
					pxl.l = dark.l;
				}
			}
			if (walls[x][y][1]) {
				for (int k=0; k<=10; k++) {
					HSLAPixel & pxl = Img->getPixel(x*10+k, (y+1)*10);
					pxl.s = dark.s;
					pxl.h = dark.h;
					pxl.l = dark.l;
				}
			}
		}
	}

	return Img;
}

int SquareMaze::location(int x, int y) const {
	return y + (x*height);
}



int SquareMaze::worstPath(vector<int>& lengthmap) {
	int y = height - 1;
	int max = location(0, y);
	for (int x=0; x<width; x++) {
		int position = location(x, y);
		if (lengthmap[position] > lengthmap[max]) {
			max = position;
		}
	}
	return max;
}


PNG * SquareMaze::drawMazeWithSolution () {
	PNG* Img = drawMaze();

	HSLAPixel red(0,1,0.5,1);

	vector<int> path = solveMaze();
	int x = 5;
	int y = 5;
	int i;
	for (int iter = 0; iter < (int)path.size(); iter++) {
		if (path[iter]==0) {
			for (i = 0; i <= 10; i++) {
				HSLAPixel & pxl = Img->getPixel(x+i, y);
				pxl.s = red.s;
				pxl.h = red.h;
				pxl.l = red.l;
			}
			x += 10;
		}
		else if (path[iter]==1) {
			for (i = 0; i <= 10; i++) {
				HSLAPixel & pxl = Img->getPixel(x, y+i);
				pxl.s = red.s;
				pxl.h = red.h;
				pxl.l = red.l;
			}
			y += 10;
		}
		else if (path[iter]==2) {
			for (i = 0; i <= 10; i++) {
				HSLAPixel & pxl = Img->getPixel(x-i, y);
				pxl.s = red.s;
				pxl.h = red.h;
				pxl.l = red.l;
			}
			x -= 10;
		}
		else if (path[iter]==3) {
			for (i = 0; i <= 10; i++) {
				HSLAPixel & pxl = Img->getPixel(x, y-i);
				pxl.s = red.s;
				pxl.h = red.h;
				pxl.l = red.l;
			}
			y -= 10;
		}
	}
	x -= 5;
	y += 5;
	for (i = 1; i < 10; i++) {
		HSLAPixel & pxl = Img->getPixel(x+i, y);
		pxl.l = 1;
	}
	return Img;
}

vector<int> SquareMaze::getneighbor(int vertex) {
	vector<int> neighbor;
	pair<int,int> coord = translateLocation(vertex);
	int x = coord.first;
	int y = coord.second;
	if (isvalid(x-1, y) && !walls[x-1][y][0]) 
		neighbor.push_back(location(x-1,y));
	
	if (isvalid(x+1, y) && !walls[x][y][0]) 
		neighbor.push_back(location(x+1,y));
	
	if (isvalid(x, y-1) && !walls[x][y-1][1]) 
		neighbor.push_back(location(x,y-1));
	
	if (isvalid(x, y+1) && !walls[x][y][1]) 
		neighbor.push_back(location(x,y+1));
	
	return neighbor;
}

bool SquareMaze::isvalid (int x, int y) const {
	return (y<height)&&(x<width)&&(y>=0)&&(x>=0);
}


vector<int> SquareMaze::bestPath() {
	vector<int> lengthmap = vector<int>(width*height, 0);
	vector<bool> beenHere = vector<bool>(width*height, false);
	vector<int> parents = vector<int>(width*height, 0);
	beenHere[0] = true;
	queue<int> q;
	q.push(0);
	while (!q.empty())
	{
		int vertex = q.front();
		q.pop();
		for (auto & neigh : getneighbor(vertex)) {

			if (beenHere[neigh] == false)
			{
				beenHere[neigh] = true;
				q.push(neigh);
				parents[neigh] = vertex;
				lengthmap[neigh] = lengthmap[vertex] + 1;
			}

		}
	}
	int endLoc = worstPath(lengthmap);
	vector<int> path;
	while (parents[endLoc]!=endLoc)
	{
		int direction = getdirection(parents[endLoc], endLoc);
		path.push_back(direction);
		endLoc = parents[endLoc];
	}
	return path;
}


pair<int,int> SquareMaze::translateLocation(int position) const {
	return pair<int,int>( position / height , position % height );
}

int SquareMaze::getdirection(int parent, int vertex) {
	pair<int,int> parentLoc = translateLocation(parent);
	int x = parentLoc.first;
	int y = parentLoc.second;
	pair<int,int> vert = translateLocation(vertex);
	int xVert = vert.first;
	int yVert = vert.second;
	if (x == xVert-1) {
		return 0;
		}
	if (x == xVert+1) {
		return 2;
		}
	if (y == yVert-1) {
		return 1;
		}
	if (y == yVert+1) {
		return 3;
		}
	return int();
}


void SquareMaze::makeMaze (	int w, int h ) {


	width = w;
	height = h;
	walls = vector<vector<vector<bool>>>(width);
	for (int i=0; i<width; i++) {
		walls[i] = vector<vector<bool>>(height);
		for (int j=0; j<height; j++) {
			vector<bool> temp = vector<bool>(2);
			temp[0] = true;
			temp[1] = true;
			walls[i][j] = temp;
		}
	}
	DisjointSets family;
	family.addelements(width*height);
	int countindep = width*height;		//cancel em out as we go
	while (countindep>1) {
		int x = rand() % (width);
		int y = rand() % (height);
		int direction = rand() % 2;
		if (walls[x][y][direction] == true) {
		int firstInd = location(x, y);
			if (direction==1 && y<height-1) {
				int scndInd = location(x, y+1);
				if (family.find(firstInd)!=family.find(scndInd)) {
					countindep--;						//not indep
					family.setunion(firstInd, scndInd);
					walls[x][y][direction] = false;
				}
			}
			else if (direction==0 && x<width-1) {
				int scndInd = location(x+1, y);
				if (family.find(firstInd)!=family.find(scndInd)) {
					countindep--;					
					family.setunion(firstInd, scndInd);
					walls[x][y][direction] = false;
				}
			}
		}
	}

}

