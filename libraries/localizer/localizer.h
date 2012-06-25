#pragma once

#include "mrcore/mrcore.h"

#include <iostream>
#include <vector>
#include "particle.h"
#include "gaussian.h"

using namespace mr;
using namespace std;

class Localizer
{
public:
	Localizer(int num=100)
	{
		particles.resize(num);
		odomTraj.setColor(255,0,0);
		groundTraj.setColor(0,255,0);
		filterTraj.setColor(0,0,255);
		setOffset(Pose3D(0.1,0,0.4,0,0,0));
		neffThreshold=0.75;
		base=new Pioneer3ATSim(); 
		base->remove((*base)[5]);base->remove((*base)[4]);base->remove((*base)[3]);base->remove((*base)[2]);
		skipLaser=1;
	}
	//(0.1,0,0.4,0,0,0) for Neo robot
	void setOffset(Pose3D off){offset=off;}
	void setNeff(float n){neffThreshold=n;}//between 0 and 1.0
	void drawGL();
	bool loadMap(string filename);
	void initializeGaussian(Pose3D initPose,double noise);
	void observe(const LaserData& laser); //returns true if resampling applied
	void move(Odometry odom,double noise,Pose3D* groundTruth);
	bool checkResample();

	Pose3D getEstimatedPose(){return estimatedPose;}
	
//	Path3D odomTraj,groundTraj,filterTraj;
	void printInfo();
	void printParams(){
		LOG_INFO("Neff: "<<neffThreshold);
		LOG_INFO("Num: "<<particles.size());
		LOG_INFO("SkipLaser: "<<skipLaser);
	}

private:
	void computeDrawWeights();
	void log2linearWeights( );
	void computeEstimatedPose();
	void computeGroundLocations();
	void normalizeWeights();
	void resample() ;//systematic
	double neff();
	vector<Particle> particles;
	World map;
	Pose3D odomPose;
	Pose3D estimatedPose;
	Pose3D ground;
	Path3D odomTraj,groundTraj,filterTraj;
	Pose3D offset;
	LaserData laserD;
	float neffThreshold;
	int skipLaser;//still not used, must be integrated in worldSim
	WheeledBaseSim* base; 
};
