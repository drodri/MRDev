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
	}
	//(0.1,0,0.4,0,0,0) for Neo robot
	void setOffset(Pose3D off){offset=off;}
	void drawGL();
	bool loadMap(string filename);
	void initializeGaussian(Pose3D initPose,double noise);
	void observe(const LaserData& laser);
	void move(Odometry odom,double noise,Pose3D* groundTruth);
	Pose3D getEstimatedPose(){return estimatedPose;}
	
private:
	void printInfo();
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
};
