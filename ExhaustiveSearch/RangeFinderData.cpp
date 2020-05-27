/***********************************************************************************************************/
/*                                                                                                         */
/* RangeFinderData class have interfaces for Generating Eucliean clound data based on User input data      */
/*                                                                                                         */
/***********************************************************************************************************/

#include "RangeFinderData.h"


RangeFinderData::RangeFinderData()
{
	m_MaxRangeVal = 20;
	m_FieldOfView = 0;
	m_Resolution = 0.05f;
}

RangeFinderData::RangeFinderData(float fov, float res, float maxRange, std::vector<float> searchRes, UtilsSharedPtr UtilsPtr)
	:m_RangeFinderRes(searchRes)
{
	m_FieldOfView = fov;
	m_MaxRangeVal = maxRange;
	m_Resolution = res;
	m_UtilsPtr = UtilsPtr;

	//finding the range of all angles fromn- -theta/2 to +theta/2
	for (float i = -(m_FieldOfView / 2); i < m_FieldOfView / 2; i = i + m_Resolution)
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
	for (size_t resIndex = 0; resIndex < GetRangeFinderResolutions().size(); ++resIndex)
	{
		for (size_t thetaIndex = 0; thetaIndex < GetRangeFinderData().size(); ++thetaIndex)
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