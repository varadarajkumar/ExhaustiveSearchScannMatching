#include "OccupancyGrid.h"
#include <cstdlib>
#include <math.h>
#include <algorithm>
#include <vector>

Grid::Grid(int height, int width, UtilsSharedPtr utilPtr)
	: m_Utils(utilPtr)
{
	//Assuming Grid is of 10x10 cells each of which height and width would be res(0.05 meters)
	m_GridResolution = 0.05f;
	m_GridHeight = height/m_GridResolution;
	m_GridWidth = width/ m_GridResolution;

	std::vector<std::pair<int, int>> gridFillers = m_Utils->GetGridValues();
	cout <<"Generating Cells(0.05x0.05) with in the Grid ..."<< endl;
	// Fill the Grid with Cells
	int id = 0, gfIndex =0, secondVal;
	for (auto row = m_GridResolution; row <= m_GridWidth; row+= 1)
	{
		for (auto col = m_GridResolution; col <= m_GridHeight; col += 1)
		{
			float cellXPos = col;
			float cellYPos = row; 
			float cellTheta=  atan(cellYPos / cellXPos); //Inverse Tan(y/x) gives Theta

			//Pose of the Cell
			Pose p(id, cellXPos, cellYPos, cellTheta);
		
			// Cell is filled randomly with the obstacle details
			//255 - represents Cell is filled with Obstacle
			//0 - represents Cell is not free
			//auto randNum = []() {return ((rand() % 255) + 1) > 200 ? 0 : 255; };

			//Filling Cells Occupancy from the Configuration 
			if (gfIndex < gridFillers.size() && id >= gridFillers[gfIndex].first && id <= gridFillers[gfIndex].second)
			{
				secondVal = gridFillers[gfIndex].second;
				m_Cells[p] = 255;
					cout << "1 ";
			}
			else
			{
				m_Cells[p] = 0;
				cout << "0  ";
			}

			if (gfIndex < gridFillers.size() &&  id == gridFillers[gfIndex].second)
			{
				gfIndex++;
			}
			++id; //Cell index
		}
		cout << endl;
	}
	cout << "Total Cells are : " << m_Cells.size() << endl;;
}

bool Grid::IsCellOccupied(Pose pose)
{
	if (GetCells().find(pose) != GetCells().end())
		return true;
	else return false;
}


int Grid::GetCellOccupancy(Pose pose)
{
	auto it = m_Cells.find(pose);
	if (it != m_Cells.end())
		return it->second;
	else 
		return 0; //not found proper Pose, So return as empty		
}