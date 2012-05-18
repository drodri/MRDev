#include "localizer.h"
#include <float.h>

void Localizer::drawGL(void)
{
	map.drawGL();
	for(unsigned int i=0;i<particles.size();i++)
		particles[i].drawGL();

	estimatedPose.drawGL();
	glPushMatrix();
		estimatedPose.transformGL();
		offset.transformGL();
		laserD.drawGL();
	glPopMatrix();

	//odomPose.drawGL();

	glPushMatrix();
	groundTraj.drawGL();
	glTranslatef(0,0,0.1);
	odomTraj.drawGL();

	glTranslatef(0,0,0.1);
	filterTraj.drawGL();
	glPopMatrix();
}
void Localizer::printInfo()
{
	for(unsigned int i=0;i<particles.size();i++)
	{
	//	double dist=(Pose3D(2.4,7,0).inverted()*particles[i].pose).module();
		LOG_INFO("W: "<<particles[i].weight<<" pose: "<<particles[i].pose);
	}
}
bool Localizer::loadMap(string filename)
{
	StreamFile worldFile(filename,true);
	if(!worldFile.good())
	{
		LOG_ERROR("Bad world file "<<filename);
		return false;
	}
	worldFile.read(&map);
	//map.readFromStream(worldFile);
	return true;
}
void Localizer::computeDrawWeights()
{
	double max=0;
	for(unsigned int i=0;i<particles.size();i++)
	{
		if(max<particles[i].weight)
			max=particles[i].weight;
	}
//	LOG_INFO("Max: "<<max);

	for(unsigned int i=0;i<particles.size();i++)
	{
		particles[i].drawWeight=particles[i].weight/max;
	}
}
void Localizer::initializeGaussian(Pose3D initPose,double noise)
{
	odomPose=initPose;

//	static WheeledBaseSim* base=new Pioneer3ATSim(); //FIXME, select robot model as parameter
	int num=0,cont=0;
	while(num<particles.size() && cont<particles.size()*1000)
	{
		cont++;
	//	Pose3D noisePose(sampleGaussian(0,noise),sampleGaussian(0,noise),sampleGaussian(0,noise),
	//					sampleGaussian(0,noise),sampleGaussian(0,noise),sampleGaussian(0,noise));
		Pose3D noisePose(sampleGaussian(0,noise),sampleGaussian(0,noise),sampleGaussian(0,noise),
						sampleGaussian(0,0),sampleGaussian(0,0),sampleGaussian(0,0));
		Pose3D p=initPose*noisePose;
		base->setAbsoluteT3D(p);
		if(base->dropWheeledBase(p,&map))
		{
			particles[num].pose=p;
			particles[num].weight=1.0;//weights
			num++;
		}
	}
	normalizeWeights();
	computeDrawWeights();
//	delete base;
	if(num<particles.size())
		LOG_ERROR("unable to generate particles with given init pose");
}
void Localizer::computeGroundLocations()
{
//	static WheeledBaseSim* base=new Pioneer3ATSim(); //FIXME, select robot model as parameter
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
//	delete base;
}
void Localizer::log2linearWeights( )
{
	double max=-DBL_MAX;int maxi=-1;
	for(unsigned int i=0;i<particles.size();i++)
	{
		double w=particles[i].weight;
		if(max<w){max=w;maxi=i;}
	}
	double sumW = 0;
	for (size_t i=0;i<particles.size();i++)
		sumW += particles[i].weight = exp( particles[i].weight -max);

	for (size_t i=0;i<particles.size();i++)
	{
		particles[i].weight/= sumW;
	cout<<particles[i].weight<<endl;
	}
}
void Localizer::observe(const LaserData& laser)
{
	LaserSensorSim lms;
	lms.setLaserProperties(laser.getStartAngle(), laser.getStep()*skipLaser, laser.size(), laser.getMaxRange(), laser.getSigma());
	laserD=laser;
	vector<double> obs=laser.getRanges();
//	cout<<"Particles-------------------------------------------------------"<<endl;

	vector<double> errors(particles.size(),1);
	for(unsigned int i=0;i<particles.size();i++)
	{
		lms.setAbsoluteT3D(particles[i].pose*offset);
		LaserData predict;
		lms.updateSensorData(&map);
		lms.getData(predict);
	//	particles[i].offset=offset;
	//	particles[i].laser=predict;

		vector<double> pred=predict.getRanges();
		//cout << "obs size " << obs.size() << endl;
		//cout << "pred size " << pred.size()<< endl;
		assert(pred.size()==obs.size());
		double maxRange=laser.getMaxRange();
		double stdsqrt2=sqrt(2.0)*10.0f;//FIXME: replace with laser.getSigma();
		for(unsigned int j=0;j<pred.size();j+=skipLaser)
		{
			if(obs[j]>=maxRange-1)continue;
			double diff=min(2.0, fabs(obs[j]-pred[j]))/stdsqrt2;
			diff*=diff;//square
		//	double W=0.1/maxRange+0.9*exp(-diff);
			double W=-diff;
		//	errors[i]+=log(W);
			errors[i]+=W;
		//	LOG_INFO("OBS: "<<j<<" values: "<<obs[j]<<" ... "<<pred[j]<<" W: "<<W<<" log: "<<log(W));
		}

		//particles[i].weight*=(1-error/(predict.size()*2.0));
	//	particles[i].weight*=exp(error);
	//	LOG_INFO("Error: "<<errors[i]);
//		cout<<"W: "<<particles[i].weight<<endl;

//		if(particles[i].weight<0)particles[i].weight=0;
//		cout<<"W: "<<particles[i].weight<<" E: "<<error<<" F: "<<(1-error/(predict.size()*1.0))<<endl;
		//cout<<"W: "<<particles[i].weight<<" E: "<<(ground.inverted()*particles[i].pose).position.module()<<endl;
//			particles[i].laser=predict;
//			particles[i].offset=offset;
	}
	double maxError=-DBL_MAX;
	for(unsigned int i=0;i<particles.size();i++)
	{
		if(maxError<errors[i])
			maxError=errors[i];
	}
//	LOG_INFO("MaxError: "<<maxError);
	for(unsigned int i=0;i<particles.size();i++)
	{
		particles[i].weight*=exp(errors[i]-maxError);
	}
	normalizeWeights(); //Check if necessary
//	printInfo();
}
bool Localizer::checkResample()
{
	double nef=neff();
	bool r = false;
	//if(nef<particles.size()/2)
	if(nef<neffThreshold*particles.size())
	{
		resample();
		r = true;
	}
	computeDrawWeights();
	computeEstimatedPose();
	return r;
}
void Localizer::normalizeWeights()
{
	double sum=0;
	for(unsigned int i=0;i<particles.size();i++)
	{
		sum+=particles[i].weight;
		//cout << "weight " << particles[i].weight << endl;

	}

	if (sum == 0)
	{
	    cout << "sum is 0 " << endl;

	}

//	LOG_INFO("Sum: "<<sum);
	for(unsigned int i=0;i<particles.size();i++)
	{
		particles[i].weight/=sum;
		//cout << "normalized weight " << particles[i].weight << endl;
		//if (particles[i].weight != particles[i].weight)
        //    cout << "normalized weight is nan " << endl;
	}
}
void Localizer::move(Odometry odom,double noise,Pose3D* groundTruth)
{
	//static //FIXME, select robot model as parameter
	//Remove Wheels here

	static Pose3D lastOdom=odom.pose;
	Pose3D inc=lastOdom.inverted()*odom.pose;
	lastOdom=odom.pose;
	odomPose*=inc;
	odomTraj.push_back(odomPose.position);

	if(groundTruth)
	{
		ground=(*groundTruth);
		groundTraj.push_back(ground.position);
	}
	for(unsigned int i=0;i<particles.size();i++)
	{
		Pose3D oldPose=particles[i].pose;
		particles[i].pose*=inc;
		double r,p,y;
		inc.orientation.getRPY(r,p,y);
		double d=inc.module();
		Pose3D noisePose(d*sampleGaussian(0,noise),d*sampleGaussian(0,noise),d*sampleGaussian(0,noise),
						d*sampleGaussian(0,noise),d*sampleGaussian(0,noise),d*sampleGaussian(0,noise));
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
				particles[i].weight*= max(0,(1.0- inc.position.module()*4));
			//	cout<<"P: "<<i<<" collide "<<base->getClassName()<<endl;
			}
		}
		else
		{
			particles[i].weight*=0.5;
		}
	}
//	delete base;
	normalizeWeights(); //Check if necessary
}
double Localizer::neff()
{
	double neff=0;
	for(unsigned int i=0;i<particles.size();i++)
	{
		neff+=particles[i].weight*particles[i].weight;
	}

	return 1.0/neff;
}
void Localizer::resample() //systematic
{
	LOG_INFO("Resampling");
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
//	cout<<"Step: "<<step<<" init "<<init<<endl;
	int current=0;
	vector<Particle> aux(num);
	double newW=1.0/num;
	for(unsigned int i=0;i<num;i++)
	{
		double v=init+step*i;

		while(v>accum[current])
			current++;

	//	cout<<current<<" ";
		aux[i]=particles[current];
		aux[i].weight=newW;
	}
//	cout<<endl;
	particles=aux;
//	normalizeWeights();
	computeEstimatedPose();
}
void Localizer::computeEstimatedPose()
{
	Vector3D average;
	vector<double> roll,pitch,yaw;
	double r,p,y;
	double max=0;int maxi=-1;
	for(unsigned int i=0;i<particles.size();i++)
	{
		double w=particles[i].weight;
		if(max<w){max=w;maxi=i;}
		average+=particles[i].pose.position*w;
		//cout << " w" << w << endl;
		//cout << "average x" << average.x << endl;
		//cout << "average y" << average.y << endl;
		//cout << "average z" << average.z << endl;
		particles[i].pose.orientation.getRPY(r,p,y);
		//cout << "r, p, y " << r << " " << p << " " << y << " " << endl;
		roll.push_back(r);pitch.push_back(p);yaw.push_back(y);
	}
	/*cout << "roll size " << roll.size() << endl;
	cout << "pitch size " << roll.size() << endl;
	cout << "yaw size " << roll.size() << endl;*/

	r=Angle::average(roll);
	y=Angle::average(yaw);
	p=Angle::average(pitch);
	Pose3D result(average);
	result.orientation.setRPY(r,p,y);

	if (result.position.x != result.position.x)
		cout << "nan " << endl;

	estimatedPose=result;
//	if(maxi!=-1)
//		estimatedPose=particles[maxi].pose;
	filterTraj.push_back(result.position);
}
