/**************************************************************************************************/
/* MatchFinder Class will have matching algorithm implemented, which will give exact Range Finder */
/*  position by taking Approximate position details and Tolerance values given by user.           */
/*  Deviation class will used for Finding the nearest values from the approximate values          */
/**************************************************************************************************/

#ifndef __MATCHFINDER_H___
#define __MATCHFINDER_H___

#include "Pose.h"
#include "OccupancyGrid.h"
#include "RangeFinderData.h"
#include "Utils.h"
#include <algorithm>

		
class Deviation
{
public:
	void SetPose(Pose& pose) { m_Pose = pose; }
	void SetDistance(float distance) { m_Distance = distance; }
	float GetDistance() { return m_Distance; }
	Pose& GetPose() { return m_Pose; }

private: 
	Pose m_Pose;
	float m_Distance;
};



//MatchFinder Class
class MatchFinder
{
	public:

		MatchFinder(int gridH, int gridW, float rfFov, float rfRes, float rfMr, float aXPos, float aYPos, float aTheta, float tXPos, float tYPos, float tTheta, UtilsSharedPtr utilsPtr);
		void CalcuateRangeFinderPosition(Pose&);
		void GenerateApproxRFPosition();
		std::vector<float> GetRangeFinderDataResolutions() { m_RangeFinderData.GetRangeFinderResolutions(); }
		void FindClosestFromActual(const std::vector<Pose>& rfPoses, Pose& bestPose);
		float CalculateDistance(const Pose& pt1);
		bool CloseDistance(Deviation&, Deviation&);
		UtilsSharedPtr GetUtils() {	return m_UtilsPtr;}
	private:
		Grid m_OccupancyGrid;
		RangeFinderData m_RangeFinderData;
		UtilsSharedPtr m_UtilsPtr;
		std::vector<Pose> m_ApproxRFPosInGrid;
		std::vector<float> m_ApprxXVals, m_ApprxYVals, m_ApprxTVals;
		float m_ApproxXVal, m_ApproxYVal, m_ApproxTheta, m_TolXVal, m_TolYVal, m_TolTheta;
		std::vector<Deviation> m_Deviation;
};
#endif