#include "mrcore/mrcore.h"

#include <iostream>
#include <list>
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
	}
	bool loadMap(string filename)
	{
		StreamFile worldFile(filename,true);
		if(!worldFile.good())
		{
			LOG_ERROR("Bad world file "<<filename);
			return false;
		}
		map.readFromStream(worldFile);
		return true;
	}
	void initializeGaussian(Pose3D initPose,double noise)
	{
		for(list<Particle>::iterator it=particles.begin();it!=particles.end();it++)
		{
			Pose3D p=initPose;
			Pose3D noisePose(sampleGaussian(0,noise),sampleGaussian(0,noise),sampleGaussian(0,noise),
							sampleGaussian(0,noise),sampleGaussian(0,noise),sampleGaussian(0,noise));
			p=p*noisePose;
			(*it).pose=p;
		}
		computeGroundLocations();
	}
	void computeGroundLocations()
	{
		WheeledBaseSim* base=new Pioneer3ATSim(); //FIXME, select robot model as parameter
		for(list<Particle>::iterator it=particles.begin();it!=particles.end();it++)
		{
			Pose3D newPose;
			base->setAbsoluteT3D(it->pose);
			cout<<"Old loc: "<<base->getAbsoluteT3D();
			if(base->dropWheeledBase(newPose,&map))
			{
				cout<<"New loc: "<<newPose;
				it->pose=newPose;
			}
		}
		delete base;
	}
	void drawGL(void)
	{
		map.drawGL();
		for(list<Particle>::iterator it=particles.begin();it!=particles.end();it++)
			it->drawGL();
	}
	
private:
	list<Particle> particles;
	World map;
};
