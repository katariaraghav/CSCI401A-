#include "GridPathPlanner.h"

GridPathPlanner::GridPathPlanner(PartiallyKnownGrid* grid, bool use_adaptive_a_star) {
	height=grid->GetHeight();
	width=grid->GetWidth();
	adaptiveStar=use_adaptive_a_star;
	numExpansions=0;
	totalExpansions=0;
	targetLoc=grid->GetGoalLocation();
	totalExpansions=0;
	targetLoc=grid->GetGoalLocation();
	steps=0;
	firstExpansion=0;
	secondExpansion=0;

	//Initializing Adaptive Star h values
	
	for(int i=0; i<width; i++)
	{
		for(int j=0; j<height; j++)
		{
			hvals [i] [j] = abs(i-targetLoc.x) + abs(j-targetLoc.y);
		}
	}


}
GridPathPlanner::~GridPathPlanner(){

	//std::cout<<"NumofExpanisons: "<<totalExpansions;
	averageExpansions=totalExpansions/steps;

	std::cout<<"Number of Expansions in Search 1: "<<firstExpansion<<"\nNumber of Expansions in search 2: "<<secondExpansion<<"\n Average Number of Expansions: "<<averageExpansions<<"\n";

}

xyLoc GridPathPlanner::GetNextMove(PartiallyKnownGrid* grid) {
	

	steps++;

	std::vector<node> openList;
	std::vector<node> closedList;
	/*xyLoc** parents= new xyLoc*[width];
	for (int i = 0; i < width; ++i)
	{
		parents[i]=new xyLoc [height];
	}
	*///dynamic memory crashing too often. Possibly because of fragmentation
	xyLoc parents [150] [150]; //static works fine

	xyLoc startLoc=grid->GetCurrentLocation();
	xyLoc nullLoc;
	nullLoc.x=-1;
	nullLoc.y=-1;

	node homeNode;
	homeNode.loc=startLoc;
	homeNode.g=0;
	homeNode.f=0;
	homeNode.h=0;
	parents [homeNode.loc.x] [homeNode.loc.y] = nullLoc;
	openList.push_back(homeNode);

	

	node targetNode;

	bool targetFound=0;

	while(openList.size()>0 && targetFound==0)
	{


		node q=openList[0];

		int i=0;
		int popThis=0;
		while(i<openList.size())
		{
			if(grid->IsBlocked(openList[i].loc))
			{
				openList.erase(openList.begin()+i);
				continue;
			}
			if(openList[i].f<q.f)
				{
					q=openList[i];
					popThis=i;
				}

			else if(openList[i].f==q.f)
			{
				if(openList[i].g>q.g)
				{
					q=openList[i];
					popThis=i;
				}
				else if(openList[i].g<q.g)
				{
					;
				}
				else{
					if(openList[i].loc<q.loc)
					{
						q=openList[i];
						popThis=i;
					}
				}
				
			}
			i++;
		}
		//popping off openlist
		openList.erase(openList.begin()+popThis);

		//FOUND THE LOWEST Q OFF THE OPEN LIST AND POPPED IT

		xyLoc curr=q.loc;		

		std::vector<xyLoc> neighbors;
		neighbors.push_back(xyLoc(curr.x+1, curr.y));
		neighbors.push_back(xyLoc(curr.x-1, curr.y));
		neighbors.push_back(xyLoc(curr.x, curr.y+1));
		neighbors.push_back(xyLoc(curr.x, curr.y-1));

		for (int i = 0; i < neighbors.size(); i++) {
			xyLoc n = neighbors[i];
			if (!grid->IsValidLocation(n) || grid->IsBlocked(n)) {
				neighbors[i] = neighbors.back();
				neighbors.pop_back();
				i--;
			}
		}

		//GENERATED ALL POSSIBLE NEIGHBORS OF Q!!

		//FOR EACH SUCCESSOR
		for(int i=0; i<neighbors.size(); i++)
		{
			
			if(neighbors[i]==targetLoc)
			{

				targetFound=1;
				parents [neighbors[i].x] [neighbors[i].y] = q.loc;
				break;

			}

			
			node potentialNode;
			potentialNode.loc=neighbors[i];
			potentialNode.g=q.g+1;
			if(adaptiveStar==0)	//non adaptive search
				potentialNode.h= abs(neighbors[i].x-targetLoc.x) + abs(neighbors[i].y-targetLoc.y);
			else if(adaptiveStar==1)	//adaptive search
			{
				potentialNode.h= hvals [potentialNode.loc.x] [potentialNode.loc.y];
			}
			potentialNode.f= potentialNode.g + potentialNode.h ; 
			

			

			int check=1;
			// checks to add on openlist
			for(int j=0; j<openList.size(); j++)
			{
				if(openList[j].loc==potentialNode.loc)
				{
					check=0;
					if(potentialNode.f<openList[j].f)
					{
						openList.erase(openList.begin()+j);
						check=1;
						break;

					}
					
				}
			}
			for(int j=0; j<closedList.size(); j++)
			{
				if(closedList[j].loc==potentialNode.loc)
				{
					check=0;
					if (potentialNode.f<closedList[i].f)
					{
						check=1;
						break;
					}
					


				}
				
			}
			if(check==1)
			{
				openList.push_back(potentialNode);
				parents [potentialNode.loc.x] [potentialNode.loc.y] = q.loc;
				//std::cout<<"pushing";
			}

		}


		closedList.push_back(q);

	}


	if(targetFound==0)
		return kInvalidXYLoc;
	//	TARGET HAS BEEN FOUND!! BACKTRACKING NOW TO FIND FIRST STEP
	xyLoc returnThis;
	returnThis=targetLoc;

	int cost=1;
	while(parents[returnThis.x] [returnThis.y]!=startLoc)
	{	
				cost++;
				returnThis=parents[returnThis.x] [returnThis.y];

	}

	//std::cout<<"Cost is: "<<cost;
	numExpansions=closedList.size();


	//ADAPTIVE STAR IMPLEMENTATION!! updating h values
	if(adaptiveStar==1)
	{
		for(int index=0; index< numExpansions; index++)
		{
			hvals [closedList[index].loc.x] [closedList[index].loc.y] = cost - closedList[index].g;
			//std::cout<<"H Values are being updated!!: "<<hvals [closedList[index].loc.x] [closedList[index].loc.y];
		}
	}
	totalExpansions+=numExpansions;
	if(steps==1)
	{
		firstExpansion=	numExpansions;
	}
	if(steps==2)
	{
		secondExpansion=numExpansions;
	}

	/*for (int i = 0; i < width; ++i)
	{
		delete [] parents[i];	
	}
	delete [] parents;
	*///dynamic memory crashing too often
	//std::cout<<"NumofExpanisons: "<<numExpansions<<"\n";
	return returnThis;


}

int GridPathPlanner::GetNumExpansions() {
	// TODO
	return numExpansions;
}
