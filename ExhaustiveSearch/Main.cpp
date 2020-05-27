#include "MatchFinder.h"
#include "Utils.h"
#include <iostream>

class Utils;

int main()
{
	int gridH, gridW;
	float rfFov, rfRes, rfMaxRange, aXPos, aYPos, aTheta, tXPos, tYPos, tTheta, gXPos, gYPos, gTheta;	
	cout << "Please enter values in WORLD coordinate format ..." << endl;
	
	cout <<"GRID DETAILS NEEDED..." << endl;
	cout <<" Enter Grid Height, Width (like 2 2) :";
	cin >> gridH;
	cin >> gridW;
	cout << endl;

	cout << " Enter GridXPos, GridYPos, GridTheta :";
	cin >> gXPos;
	cin >> gYPos;
	cin >> gTheta;
	cout << endl;
	
	cout <<"RANGE FINDER DETAILS NEEDED..." << endl;
	cout <<" Enter Range Finder FOV(In RADIANS), Resolution and MaxRange (Like 45, 0.05, 20) :";
	cin >> rfFov;
	cin >> rfRes;
	cin >> rfMaxRange;
	cout << endl;

	float searchRes; std::vector<float> searchResVec;
	cout << " Enter Search Resolutions (in Meters), separated with spaces and enter '9999' to end pushing values" << endl;
	while ((cin >> searchRes) && searchRes != 9999)
		searchResVec.push_back(searchRes);
		
	cout <<"APPROXIMATE RANGE FINDER DETAILS NEEDED...:"<<endl;
	cout <<" Enter Approx Range Finder X-Position, Y-Position, Theta (Can be Float values) :";
	cin >> aXPos;
	cin >> aYPos;
	cin >> aTheta;
	cout << endl;
	
	cout <<" Enter Tolerance Range Finder X-Position, Y-Position, Theta (Can be Float values) :";
	cin >> tXPos;
	cin >> tYPos;
	cin >> tTheta;
	cout << endl;

	Pose bestPose;
	UtilsSharedPtr ptrUtils= UtilsSharedPtr(new Utils(gXPos, gYPos, gTheta));

	MatchFinder* ptrMatchFinder = new MatchFinder(gridH, gridW, rfFov, rfRes, rfMaxRange, aXPos, aYPos, aTheta, tXPos, tYPos, tTheta, searchResVec, ptrUtils);
	ptrMatchFinder->GenerateApproxRFPosition();
	ptrMatchFinder->CalcuateRangeFinderPosition(bestPose);
	cout <<"Range finder pose X-Poistion : " << bestPose.getXPos()<<", Y-Position: "<< bestPose.getYPos()<<", Theta: "<< bestPose.getTheta()<<endl;
	
	return 0;
}