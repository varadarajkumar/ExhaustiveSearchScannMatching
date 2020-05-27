/***********************************************************************************************************/
/*                                                                                                         */
/* RangeFinderData class have interfaces for Generating Eucliean clound data based on User input data      */
/*                                                                                                         */
/***********************************************************************************************************/

#ifndef __RANGEFINDERDATA_H___
#define __RANGEFINDERDATA_H___


#include <vector>
#include "Pose.h"
#include "Utils.h"

using namespace std;

class RangeFinderData
{
	typedef vector<float> FLOAT_VEC;
public: 
	RangeFinderData();
	RangeFinderData(float fov, float res, float maxRange, UtilsSharedPtr uPtr);
	FLOAT_VEC GetRangeFinderData();
	FLOAT_VEC GetRangeFinderResolutions() {	return m_RangeFinderRes;}
	vector<Pose> GetRFEuclideanCloud() { return m_RfEuclideanCloudData; }
	void GenerateRFEuclideanCloud();
	int GetRangeFinderResSize() const { return m_RangeFinderRes.size(); }	
	UtilsSharedPtr GetUtils() { return m_UtilsPtr; }
private: 

	float m_fov; 
	float m_MaxRangeVal;
	float m_res;
	UtilsSharedPtr m_UtilsPtr;
	FLOAT_VEC m_Thetas;
	FLOAT_VEC m_RangeFinderRes;
	std::vector<Pose> m_RfEuclideanCloudData;
};

#endif