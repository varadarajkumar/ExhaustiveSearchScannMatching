/**************************************************************************************************/
/* MatchFinder Class will have matching algorithm implemented, which will give exact Range Finder */
/*  position by taking Approximate position details and Tolerance values given by user.           */
/*  Deviation class will used for Finding the nearest values from the approximate values          */
/**************************************************************************************************/

#include "MatchFinder.h"

MatchFinder::MatchFinder(int gridH, int gridW, float rfFov, float rfRes, float rfMr, float aXPos, float aYPos, float aTheta, float tXPos, float tYPos, float tTheta, UtilsSharedPtr utilsPtr)
: m_ApproxXVal(aXPos)
, m_ApproxYVal(aYPos)
, m_ApproxTheta(aTheta)
, m_TolXVal(tXPos)
, m_TolYVal(tYPos)
, m_TolTheta(tTheta)
, m_UtilsPtr(utilsPtr)
{
	m_OccupancyGrid = Grid(gridH, gridW, utilsPtr);
	m_RangeFinderData = RangeFinderData(rfFov, rfRes, rfMr, utilsPtr);
}

void MatchFinder::GenerateApproxRFPosition()
{
	for (auto x = m_ApproxXVal - m_TolXVal; x <= m_ApproxXVal + m_TolXVal; x++)
		m_ApprxXVals.push_back(x);

	for (auto y = m_ApproxYVal - m_TolYVal; y <= m_ApproxYVal + m_TolYVal; y++)
		m_ApprxYVals.push_back(y);

	for (auto t = m_ApproxTheta - m_TolTheta; t <= m_ApproxTheta + m_TolTheta; t++)
		m_ApprxTVals.push_back(t);
}

//Search Algorithm
void MatchFinder::CalcuateRangeFinderPosition(Pose &pose)
{
	float r_x, r_y, finalHypoSum = 0;
	std::vector<Pose> rfCoordinates, finalRFPoses;

	for(auto t : m_ApprxTVals)
	{
		for(auto x : m_ApprxXVals)
		{
			float hypSumForEachX = 0;
			for(auto y : m_ApprxYVals)
			{				
				r_x = cos(t) * x - sin(t) * y;
				r_y = sin(t) * r_x + cos(t) * y;
				Pose posInGrid;
				GetUtils()->ConvertToGridCoordinates(posInGrid, r_x, r_y, t);
				auto OccupancyStatus = m_OccupancyGrid.GetCellOccupancy(posInGrid);
				if (OccupancyStatus == 255)
				{
					rfCoordinates.push_back(posInGrid);
					hypSumForEachX += OccupancyStatus;
				}
			}
			if (hypSumForEachX > 0 && finalHypoSum == hypSumForEachX )
			{
				finalRFPoses.insert(finalRFPoses.end(), rfCoordinates.begin(), rfCoordinates.end());
				finalHypoSum = hypSumForEachX;				
			}
			else if (hypSumForEachX > 0 && finalHypoSum < hypSumForEachX)
			{
				//Replace with high score
				finalRFPoses.clear();
				finalRFPoses = rfCoordinates;
				finalHypoSum = hypSumForEachX;
			}
		}
	}

	if (!finalRFPoses.size())
	{
		cout << "Nothing found, So approximate can be actual !!" << endl;
		GetUtils()->ConvertToWorldCoordinates(pose,m_ApproxXVal, m_ApproxYVal, m_ApproxTheta);
	}
	else
	{
		//still need to compare with approximate Pose and find the best pose
		FindClosestFromActual(finalRFPoses, pose);
		pose = finalRFPoses[0];
	}
}

void MatchFinder::FindClosestFromActual(const std::vector<Pose> &rfPoses, Pose &bestPose)
{
	std::vector<Deviation> AllDistances;
	for(auto p : rfPoses) 
	{
		Deviation deviation;
		deviation.SetPose(p);
		deviation.SetDistance(CalculateDistance(p));
		AllDistances.push_back(deviation);
	}

	auto min_deviation = std::min_element(begin(AllDistances), end(AllDistances),
		[&](Deviation& a, Deviation& b) {
			return a.GetDistance() < b.GetDistance();
		});

	GetUtils()->ConvertToWorldCoordinates(bestPose, min_deviation->GetPose().getXPos(), min_deviation->GetPose().getYPos(), min_deviation->GetPose().getTheta());
	
	//std::sort(AllDistances.begin(), AllDistances.end(), CloseDistance);
	//bestPose = std::min_element(AllDistances.begin(), AllDistances.end())->GetPose();
	//bestPose = AllDistances[0].GetPose();
}

float MatchFinder::CalculateDistance(const Pose& pt1)
{
	float deltaX = pt1.m_xPos - m_ApproxXVal;
	float deltaY = pt1.m_yPos - m_ApproxYVal;
	return (deltaX * deltaX) + (deltaY * deltaY);
}

bool MatchFinder::CloseDistance(Deviation& lhs, Deviation& rhs)
{
	return lhs.GetDistance() < rhs.GetDistance();
}