/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{


    vector<Point<3>> LUVPoints;
	LUVPoints.resize(theTiles.size());
	map<Point<3>,int> mapPoints;
	for (unsigned i=0; i<LUVPoints.size(); i++)
	{
		LUVPoints[i] = convertToXYZ(theTiles[i].getAverageColor());
        mapPoints[LUVPoints[i]] = i;
	}
	KDTree<3> tree(LUVPoints);
	// output

	MosaicCanvas* mosaic = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
	for (int i=0; i<theSource.getRows(); i++){
        for (int j=0; j<theSource.getColumns(); j++)
        {
            LUVAPixel source_color = theSource.getRegionColor(i, j);
            // query point
            Point<3> query = convertToXYZ(source_color);
            Point<3> foundpoint = tree.findNearestNeighbor(query);
            int index = mapPoints[foundpoint];
            mosaic->setTile(i, j, &theTiles[index]);
        }
    }
    return mosaic;
}

