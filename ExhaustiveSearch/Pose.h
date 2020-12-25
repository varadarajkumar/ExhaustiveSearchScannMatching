/****************************************************************************************************************/
/*                                                                                                              */
/* Pose class represents Pose in either World or Grid Coordinates system. Pose is key for each cell in the Grid */
/* This class will have x, y, theta as memeber variables.                                                       */ 
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __POSE_H___
#define __POSE_H___

#include <iostream>
using namespace std; 



class Pose
{
public:
	Pose()
	{
		m_Id = 0;
		m_xPos = 0;
		m_yPos = 0;
		m_theta = 0;
	}
	
	Pose(int id, float xPos, float yPos, float theta)
	{
		m_Id = id;
		m_xPos = xPos;
		m_yPos = yPos;
		m_theta = theta;
	}
	bool operator == (const Pose& rhs)
	{
		if (this->m_xPos == rhs.m_xPos && this->m_yPos == rhs.m_yPos && this->m_theta == rhs.m_theta)
			return true;
		return false;
	}

	float getXPos() { return m_xPos; }
	float getYPos() { return m_yPos; }
	float getTheta() { return m_theta; }
	int getId() { return m_Id; }

	float m_xPos;
	float m_yPos;
	float m_theta; //in radians
	int m_Id; //only used while inserting POSE into grid
};


//PoseComparator maintains ordered values while inserting into the m_Cells map
struct PoseComparator
{
	bool operator() (const Pose& lhs, const Pose& rhs) const
	{
		//find a m_Cells map key formed with xPos, yPos and Theta values combination
		//if (lhs.m_xPos + lhs.m_yPos + lhs.m_theta < rhs.m_xPos + rhs.m_yPos+ rhs.m_theta )
		if(lhs.m_Id < rhs.m_Id)
			return true; 

		return false;
	}
};

#endif