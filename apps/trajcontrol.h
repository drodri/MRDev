#pragma once
#include "mrcore/mrcore.h"

class TrajControl
{
public:	
	void drawGL()
	{
		path.drawGL();
	}
	void setPath(Path2D p)
	{
		path=p;
		path.setColor(255,0,255);
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
			Segment2D seg(points[i],points[i+1]);
			double dist=seg.distance(p);
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
			Vector2D v3=points[mini+1]-p;
			double roll,pitch,yaw;
			current.orientation.getRPY(roll,pitch,yaw);
			rot=6.0*Angle::difference(v3.argument(),yaw);
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
};

