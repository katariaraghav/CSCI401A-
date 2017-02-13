#ifndef ASTAR_H
#define ASTAR_H

#include "AStar.h"


struct node
{
	//xyLoc parent;
	xyLoc loc;
	float f, g, h;
};

class AStar{
public:
	AStar(PartiallyKnownGrid* grid, bool use_adaptive_a_star = false);
	~AStar();

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
