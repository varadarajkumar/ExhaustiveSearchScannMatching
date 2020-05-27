/********************************************************************************************/
/* Grid class represents the Occupancy Grid which contains Cells.                           */
/* Number of Cells in the grid depends on the Width and Height of the Grid given by user    */
/* Cells will added to Grid in ordered manner based on Id value.                             */
/* By giving Pose of the Cell as Key, Occupancy Information given as Value of Key-Value pair */
/*********************************************************************************************/

#ifndef __GRID_H___
#define __GRID_H___

#include "Utils.h"
#include "Pose.h"
#include <map>

class Grid
{
	//Pose as Key and Occupancy Information as Value in the OccupancyGrid
	using POSE_MAP_TYPE = std::map<Pose, unsigned _int8, PoseComparator>;
public:	
	Grid();
	Grid(int h, int w, UtilsSharedPtr);
	POSE_MAP_TYPE GetCells() { return m_Cells; }
	bool IsCellOccupied(Pose p);
	int GetCellOccupancy(Pose p);
	UtilsSharedPtr GetUtils() { m_Utils; }
	POSE_MAP_TYPE m_Cells;
private:
	UtilsSharedPtr m_Utils;
	float m_GridHeight;
	float m_GridWidth; 
	float m_GridResolution;
};

#endif