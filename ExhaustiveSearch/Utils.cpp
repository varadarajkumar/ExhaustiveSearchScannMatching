/*************************************************************/
/* Utils class will provide few of the conversion API's      */
/* Such as Parsing INPUT.txt and gather important information*/
/*************************************************************/

#include "Utils.h"

Utils::Utils(float x_g, float y_g, float theta_g)
	:m_GridXPos(x_g)
	,m_GridYPos(y_g)
	,m_GridTheta(theta_g)
{
	ParseInputFile();
}

Pose& Utils::ConvertToWorldCoordinates(Pose &pose, float x_g, float y_g, float theta_g)
{
	pose.m_xPos = cos(m_GridTheta) * x_g - sin(m_GridTheta) * y_g + m_GridXPos;
	pose.m_yPos = sin(m_GridTheta) * x_g + cos(m_GridTheta) * y_g + m_GridYPos;
	pose.m_theta = theta_g + m_GridTheta;

	return pose;
}

Pose& Utils::ConvertToGridCoordinates(Pose& pose, float x_w, float y_w, float theta_w)
{
	pose.m_xPos = cos(m_GridTheta) * (x_w-m_GridXPos) + sin(m_GridTheta) * (y_w - m_GridYPos);
	pose.m_yPos = sin(m_GridTheta) * (x_w-m_GridXPos) + cos(m_GridTheta) * (y_w - m_GridYPos);
	pose.m_theta = theta_w - m_GridTheta;

	return pose;
}

void Utils::ParseInputFile()
{
	std::ifstream file("INPUT.txt");

	std::string line;
	while (getline(file, line))
	{
		std::istringstream iss(line);

		string result;
		if (getline(iss, result, '='))
		{
			if (result == "GridInput")
			{
				string line;
				while (std::getline(iss, line, ','))
				{
					int i = 0, first, second=0;
				
					string delimiter = "-";
					size_t pos = 0;
					if ((pos = line.find(delimiter)) != std::string::npos)
					{
						first = atoi(line.substr(0, pos).c_str());
						line.erase(0, pos + delimiter.length());
					}
					else
					{
						first = atoi(line.c_str());
					}
					second = atoi(line.c_str());

					if (second == 0)
						second = first;
					m_GridFiller.push_back(std::pair<int, int>(first, second));
				}
			}
		}
	}
}