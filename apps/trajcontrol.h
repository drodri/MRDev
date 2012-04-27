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
	void setData(const Pose2D& pose)
	{
		vector<Vector2D> points=path.points;
		float min=1000;
		int mini=-1;
		for(int i=0;i<points.size()-1;i++)
		{
			Segment2D seg(points[i],points[i+1]);
			double dist=seg.distance(pose.position());
			if(dist<min)
			{
				min=dist;
				mini=i;
			}
		}
		if(mini>=0)
		{
			cout<<"Current segm: "<<mini<<endl;
			Vector2D v3=points[mini+1]-pose.position();
			float angDiff=Angle::difference(v3.argument(),pose.angle());
			//if(min>3)
			//{
			//	cout<<"Too far"<<endl;
			//	speed=0.5;
			//	rot=25.0*Angle::difference(v3.argument(),pose.angle());
			//}
			//else
			{
				speed=2;
				if(fabs(angDiff)>25*DEG2RAD)
					speed=1;
				rot=6.0*Angle::difference(v3.argument(),pose.angle());
			}
		}

	}

	void getSpeed(float& va, float& vg)
	{
		va=speed;
		vg=rot;
	}
protected:
	float speed,rot;
	Path2D path;
};

