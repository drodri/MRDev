#pragma once
#include "mrcore/mrcore.h"

class ReactiveControl //: public GLObject
{
	//DECLARE_MR_OBJECT(ReactiveControl)
public:	
	void drawGL()
	{
	}
	void setData(const LaserData& laser)
	{
		speed=speedCommand;
		rot=rotCommand;

		vector<double> ranges=laser.getRanges();
		vector<Angle> angles=laser.getAngles();
		float min=1;
		int mini=-1;
		for(int i=0;i<ranges.size();i++)
		{
			if(fabs(angles[i].getValue())<90*DEG2RAD && ranges[i]<min)
			{
				min=ranges[i];
				mini=i;
			}
		}
		if(mini>0)
		{
			//cout<<"Obstacle at: "<<angles[mini].getValue()<<" min: "<<min<<endl;
			//cout<<"Command: "<<speed<<" "<<rot<<endl;
			//cout<<"Obstacle at: "<<angles[mini].getValue()<<" min: "<<min<<endl;
			if(speed>0)speed*=max(min-0.45,0);
			rot=-0.7*sgn(angles[mini].getValue());
			//cout<<"Control: "<<speed<<" "<<rot<<endl;
		}

	}
	void setCommand(float va, float vg)
	{
		speedCommand=va;
		rotCommand=vg;
	}
	void getSpeed(float& va, float& vg)
	{
		va=speed;
		vg=rot;
	}
protected:
	float speed,rot;
	float speedCommand, rotCommand;


//	virtual void writeToStream(Stream& stream);
//	virtual void readFromStream(Stream& stream);
};

//IMPLEMENT_MR_OBJECT(ReactiveControl);