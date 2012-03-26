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
		for(unsigned int i=0;i<particles.size();i++)
		{
			Pose3D p=initPose;
			Pose3D noisePose(sampleGaussian(0,noise),sampleGaussian(0,noise),sampleGaussian(0,noise),
							sampleGaussian(0,noise),sampleGaussian(0,noise),sampleGaussian(0,noise));
			p=p*noisePose;
			particles[i].pose=p;
			particles[i].weight=1.0;
		}
		computeGroundLocations();
		resample();
	}
	void computeGroundLocations()
	{
		WheeledBaseSim* base=new Pioneer3ATSim(); //FIXME, select robot model as parameter
		for(unsigned int i=0;i<particles.size();i++)
		{
			Pose3D newPose=particles[i].pose;
			base->setAbsoluteT3D(newPose);
			if(base->dropWheeledBase(newPose,&map))
			{
				particles[i].pose=newPose;
			}
			else
			{
				cout<<"initial pose not right, making w=0"<<endl;
				particles[i].weight=0;
			}
		}
		delete base;
	}
	void drawGL(void)
	{
		map.drawGL();
		for(unsigned int i=0;i<particles.size();i++)
			particles[i].drawGL();
	}
	void observe(const LaserData& laser)
	{
		Neo* base=new Neo(); //FIXME, select robot model as parameter
		base->remove((*base)[5]);base->remove((*base)[4]);base->remove((*base)[3]);base->remove((*base)[2]);
		for(unsigned int i=0;i<particles.size();i++)
		{
			base->setAbsoluteT3D(particles[i].pose);
			base->laser.simulate()
		}

	}
	void move(Odometry odom,double noise)
	{
		WheeledBaseSim* base=new Pioneer3ATSim(); //FIXME, select robot model as parameter
		base->remove((*base)[5]);base->remove((*base)[4]);base->remove((*base)[3]);base->remove((*base)[2]);
		
		static Pose3D lastOdom=odom.pose;
		Pose3D inc=lastOdom.inverted()*odom.pose;
		lastOdom=odom.pose;
		for(unsigned int i=0;i<particles.size();i++)
		{
			Pose3D oldPose=particles[i].pose;
			particles[i].pose*=inc;
			double r,p,y;
			inc.orientation.getRPY(r,p,y);
			Pose3D noisePose(inc.position.x*sampleGaussian(0,noise),inc.position.y*sampleGaussian(0,noise),inc.position.z*sampleGaussian(0,noise),
							r*sampleGaussian(0,noise),p*sampleGaussian(0,noise),y*sampleGaussian(0,noise));
			particles[i].pose*=noisePose;
			Pose3D newPose=particles[i].pose;

			base->setAbsoluteT3D(oldPose);
			if(base->computeGroundedLocation(newPose,&map))
			{
			//	cout<<"Old pose: "<<particles[i].pose<<endl;
			//	cout<<"New pose: "<<newPose<<endl;
				particles[i].pose=newPose;
				base->setAbsoluteT3D(newPose);

				if(map.checkCollisionWith(*base))
				{
					//FIXME: check why collide with ramps
				//	particles[i].weight*=0.9;
				//	cout<<"P: "<<i<<" collide "<<base->getClassName()<<endl;
					particles[i].pose=oldPose;
					particles[i].weight*= (1.0- inc.position.module()/0.5);
				}
			}
			else
			{
				particles[i].weight=0;
			}
		}
		delete base;
	}
	void resample() //systematic
	{
		int num=particles.size();
		vector<double> accum(num);
		double total=0;
		cout<<"W: "<<endl;
		for(unsigned int i=0;i<num;i++)
		{
			double w=particles[i].weight;
			cout<<w<<endl;
			accum[i]=total+w;
			total=accum[i];
		}
		double step=total/num;
		double init=step*(rand()/(double)RAND_MAX);
		int current=0;
		vector<Particle> aux(num);
		for(unsigned int i=0;i<num;i++)
		{
			double v=init+step*i;
					
			while(v>accum[current])
				current++;

			aux[i]=particles[current];
			aux[i].weight=1;
		}
		particles=aux;
	}
	Pose3D getEstimatedPose()
	{
		Vector3D average;
		vector<double> roll,pitch,yaw;
		double r,p,y;
		for(unsigned int i=0;i<particles.size();i++)
		{
			average+=particles[i].pose.position;		
			particles[i].pose.orientation.getRPY(r,p,y);
			roll.push_back(r);pitch.push_back(p);yaw.push_back(y);
		}
		r=Angle::average(roll);
		y=Angle::average(yaw);
		p=Angle::average(pitch);
		Pose3D result(average/particles.size());
		result.orientation.setRPY(r,p,y);
		return result;
	}
	
private:
	vector<Particle> particles;
	World map;

};
