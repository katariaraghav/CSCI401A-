#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <functional>
#include <set>
#include <cmath>
#include <algorithm>
#include <map>
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
	ofstream map;
	map.open ("example1_map.yaml");

	int numRows, numCols;
	cin>>numRows>>numCols;
	map<<"dimensions: ["<<numRows<<","<<numCols<<",1]"<<endl<<"obstacles: [";
	bool first = true;
	for(int i = 0; i < numRows; i++)
	{
		for(int j = 0; j<numCols; j++)
		{
			char c;
			cin>>c;
			if(c=='0')
			{
				if(!first)
				{
					map<<",";
				}
				first = false;
				map<<endl<<"    ["<<endl<<"        "<<i<<","<<endl<<"        "<<j<<","<<endl<<"        0"
					<<endl<<"    ]";
			}
		}
	}
	map<<endl<<"]"<<endl;

	ofstream agents;
	agents.open("example1_agents.yaml");

	agents<<"agents:"<<endl;
	int numAgents;
	int index = 0;
	int time = 0;
	while(cin>>numAgents)
	{
		for(int i = 0; i<numAgents; i++)
		{
			int startRow, startCol, endRow, endCol;
			cin>>startRow>>startCol>>endRow>>endCol;
			agents<<"  - name: agent"<<index+i<<endl;
			agents<<"    start: ["<<startRow<<","<<startCol<<",0]"<<endl;
			agents<<"    goal: ["<<endRow<<","<<endCol<<",0]"<<endl;
			agents<<"    type: fastAgent\n    enterTime: "<<time<<endl;
		}
		time++;
		index+=numAgents;
	}

}
