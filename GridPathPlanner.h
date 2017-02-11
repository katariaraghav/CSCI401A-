#ifndef GRID_PATH_PLANNER_H
#define GRID_PATH_PLANNER_H

#include "PartiallyKnownGrid.h"


struct node
{
	//xyLoc parent;
	xyLoc loc;
	float f, g, h;
};

class GridPathPlanner{
public:
	GridPathPlanner(PartiallyKnownGrid* grid, bool use_adaptive_a_star = false);
	~GridPathPlanner();

	xyLoc GetNextMove(PartiallyKnownGrid* grid);
	int GetNumExpansions();

private:

	int height;
	int width;
	bool adaptiveStar;
	int numExpansions;
	int totalExpansions;
	float hvals [150] [150];
	xyLoc targetLoc;
	int steps;
	double averageExpansions;
	int firstExpansion;
	int secondExpansion;

};

#endif
