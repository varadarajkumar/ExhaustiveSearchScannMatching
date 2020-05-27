/***********************************************************************************************************/
/*                                                                                                         */
/* RangeFinderData class have interfaces for Generating Eucliean clound data based on User input data      */
/*                                                                                                         */
/***********************************************************************************************************/

#include "RangeFinderData.h"


RangeFinderData::RangeFinderData()
{
	m_MaxRangeVal = 20;
	m_fov = 0;
	m_res = 0.05f;
}

RangeFinderData::RangeFinderData(float fov, float res, float maxRange, UtilsSharedPtr UtilsPtr)
{
	m_fov = fov;
	m_MaxRangeVal = maxRange;
	m_res = res;
	m_UtilsPtr = UtilsPtr;

	//RangeFinder distances 10, 12, 14, 16,18, 20 meters
	m_RangeFinderRes.clear();	
	for (float resRange = 10; resRange<=20; resRange += 2.0)
	{
		m_RangeFinderRes.push_back(resRange);
	}

	//finding the range of all anglesn- -theta/2 to +theta/2
	for (float i = -(m_fov / 2); i < m_fov / 2; i = i + m_res)
	{
		m_Thetas.push_back(i);
	}
	
	GenerateRFEuclideanCloud();
}

RangeFinderData::FLOAT_VEC RangeFinderData::GetRangeFinderData()
{
	return m_Thetas;
}

void RangeFinderData::GenerateRFEuclideanCloud()
{
	cout << "Generating Range Finder Euclidean Cloud data..." << endl;
	for (int resIndex = 0; resIndex < GetRangeFinderResolutions().size(); ++resIndex)
	{
		for (int thetaIndex = 0; thetaIndex < GetRangeFinderData().size(); ++thetaIndex)
		{
			float thetaValue = GetRangeFinderData()[thetaIndex];
			float resValue = GetRangeFinderResolutions()[resIndex];
			float xValue = resValue * cos(thetaValue);
			float yValue = resValue * sin(thetaValue);

			//Transform into Grid Coordinates
			Pose poseInGridCoordindates;
			GetUtils()->ConvertToGridCoordinates(poseInGridCoordindates, xValue, yValue, thetaValue);
			m_RfEuclideanCloudData.push_back(poseInGridCoordindates);
		}
	}
	cout << "Done, Range Finder Euclidean Cloud data generation..." << endl;
}