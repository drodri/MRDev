#pragma once
#include "mrcore/mrcore.h"

class TrajControl //: public GLObject
{
	//DECLARE_MR_OBJECT(ReactiveControl)
public:	
	void drawGL()
	{
		path.drawGL();
	}
	void setPath(Path2D p)
	{
		path=p;
		path.setRGB(255,0,255);
	}
	void setData(const Odometry& odom)
	{
		current=odom.pose;
		vector<Vector2D> points=path.points;
		Vector2D p(current.position.x,current.position.y);
		float min=1000;
		int mini=-1;
		for(int i=0;i<points.size()-1;i++)
		{
			Segment2d seg(points[i],points[i+1]);
			double dist=pointDistanceToSegment(p, seg);
		//	cout<<"Dist to : "<<i<<" is: "<<dist<<endl;
			if(dist<min)
			{
				min=dist;
				mini=i;
			}
		}
		if(mini>=0)
		{
			cout<<"Current segm: "<<mini<<endl;
			speed=2;
		//	Vector2D v1=p-points[mini];
		//	Vector2D v2=points[mini+1]-points[mini];
			Vector2D v3=points[mini+1]-p;
		//	float sign=sgn((		Angle(v1.argument())	-	Angle(v2.argument())	).getValue());
		//	rot=-2.7*sign*min;

			double roll,pitch,yaw;
			current.orientation.getRPY(roll,pitch,yaw);
			rot=6.0*(Angle(v3.argument())-Angle(yaw)).getValue();
		}

	}

	void getSpeed(float& va, float& vg)
	{
		va=speed;
		vg=rot;
	}
protected:
	float speed,rot;
	Transformation3D current;
	Path2D path;
	

//	virtual void writeToStream(Stream& stream);
//	virtual void readFromStream(Stream& stream);
};

//IMPLEMENT_MR_OBJECT(ReactiveControl);