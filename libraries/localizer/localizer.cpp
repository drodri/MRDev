#include "localizer.h"

void Localizer::drawGL(void)
{
	map.drawGL();
	for(unsigned int i=0;i<particles.size();i++)
		particles[i].drawGL();

	odomPose.drawGL();

	glPushMatrix();
	odomTraj.drawGL();
	glTranslatef(0,0,0.1);
	groundTraj.drawGL();
	glTranslatef(0,0,0.1);
	filterTraj.drawGL();
	glPopMatrix();
}
bool Localizer::loadMap(string filename)
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

void Localizer::initializeGaussian(Pose3D initPose,double noise)
{
	odomPose=initPose;

	WheeledBaseSim* base=new Pioneer3ATSim(); //FIXME, select robot model as parameter
	int num=0,cont=0;
	while(num<particles.size() && cont<particles.size()*100)
	{
		cont++;
		Pose3D noisePose(sampleGaussian(0,noise),sampleGaussian(0,noise),sampleGaussian(0,noise),
						sampleGaussian(0,noise),sampleGaussian(0,noise),sampleGaussian(0,noise));
	//	Pose3D noisePose(sampleGaussian(0,noise),sampleGaussian(0,noise),sampleGaussian(0,noise),
	//					sampleGaussian(0,0),sampleGaussian(0,0),sampleGaussian(0,0));
		Pose3D p=initPose*noisePose;
		base->setAbsoluteT3D(p);
		if(base->dropWheeledBase(p,&map))
		{
			particles[num].pose=p;
			particles[num].weight=1.0;
			num++;
		}
	}
	delete base;
	if(num<particles.size())
		LOG_ERROR("unable to generate particles with given init pose");
}
void Localizer::computeGroundLocations()
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
	
void Localizer::observe(const LaserData& laser)
{
	LMS100Sim lms;
	Pose3D offset(0.1,0,0.4,0,0,0);
	vector<double> obs=laser.getRanges();
	cout<<"Particles-------------------------------------------------------"<<endl;
	for(unsigned int i=0;i<particles.size();i++)
	{
		lms.setAbsoluteT3D(particles[i].pose*offset);
		LaserData predict;
		lms.updateSensorData(&map);
		lms.getData(predict);

		vector<double> pred=predict.getRanges();
		assert(pred.size()==obs.size());
		double error=0;
		for(unsigned int j=0;j<pred.size();j++)
		{
			double diff=fabs(obs[j]-pred[j]);
			error+=diff;
		//	cout<<obs[j]<<" ... "<<pred[j]<<" Diff: "<<diff<<endl;
		}
		particles[i].weight*=(1-error/(predict.size()*2.0));

		if(particles[i].weight<0)particles[i].weight=0;
//		cout<<"W: "<<particles[i].weight<<" E: "<<error<<" F: "<<(1-error/(predict.size()*1.0))<<endl;
		//cout<<"W: "<<particles[i].weight<<" E: "<<(ground.inverted()*particles[i].pose).position.module()<<endl;
//			particles[i].laser=predict;
//			particles[i].offset=offset;
	}
	normalizeWeights();
	double nef=neff();
	if(nef<particles.size()/2)
		resample();
}
void Localizer::normalizeWeights()
{
	double max=0;
	for(unsigned int i=0;i<particles.size();i++)
	{
		if(particles[i].weight>max)
			max=particles[i].weight;
	}
	for(unsigned int i=0;i<particles.size();i++)
		particles[i].weight/=max;
}
void Localizer::move(Odometry odom,double noise,Odometry* groundTruth)
{
	WheeledBaseSim* base=new Pioneer3ATSim(); //FIXME, select robot model as parameter
	base->remove((*base)[5]);base->remove((*base)[4]);base->remove((*base)[3]);base->remove((*base)[2]);
	
	static Pose3D lastOdom=odom.pose;
	Pose3D inc=lastOdom.inverted()*odom.pose;
	lastOdom=odom.pose;
	odomPose*=inc;
	odomTraj.push_back(odomPose.position);

	if(groundTruth)
	{
		ground=(*groundTruth).pose;
		groundTraj.push_back(ground.position);
	}
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
	//	cout<<"Old: "<<oldPose;
	//	cout<<"New: "<<newPose;
		if(base->computeGroundedLocation(newPose,&map))
		{
	//		cout<<"Grounded: "<<newPose;
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
			//	cout<<"P: "<<i<<" collide "<<base->getClassName()<<endl;
			}
		}
		else
		{
			particles[i].weight=0;
		}
	}
	delete base;
}
double Localizer::neff()
{
	double neff=0,sum=0;
	for(unsigned int i=0;i<particles.size();i++)
	{
		sum+=particles[i].weight;
		neff+=particles[i].weight*particles[i].weight;
	}

	return sum*sum/neff;
}
void Localizer::resample() //systematic
{
	int num=particles.size();
	vector<double> accum(num);
	double total=0;
	for(unsigned int i=0;i<num;i++)
	{
		double w=particles[i].weight;
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
Pose3D Localizer::getEstimatedPose()
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

	filterTraj.push_back(result.position);

	return result;
}
