/*************************************************************/
/* Utils class will provide few of the conversion API's      */
/* Such as Parsing INPUT.txt and gather important information*/
/*************************************************************/

#ifndef __UTILS_H__
#define __UTILS_H__

#include "Pose.h"
#include <stdio.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <string.h>
#include <sstream>

class Utils
{
	private: 
		float m_GridXPos, m_GridYPos, m_GridTheta;
		vector<std::pair<int, int>> m_GridFiller;
	public:
		Utils(float gridXPos, float gridYPos, float gridTheta);
		~Utils() { m_GridFiller.clear(); }
		Pose& ConvertToWorldCoordinates(Pose&, float x_g, float y_g, float theta_g);
		Pose& ConvertToGridCoordinates(Pose&, float x_w, float y_w, float theta_w);
		void ParseInputFile();
		vector<std::pair<int, int>> GetGridValues() {return m_GridFiller;}
};

typedef shared_ptr<Utils> UtilsSharedPtr;
#endif