#include "mrcore/mrcore.h"
#include <iostream>

using namespace mr;
using namespace std;

class Particle
{
public:
	Particle()
	{
		
	}
	void drawGL(void)
	{
		glColor3f(255,0,0);
		glPushMatrix();
			pose.transformGL();
			glTranslatef(0,0,drawWeight);
			glBegin(GL_LINES);
				glVertex3f(0.,0.,0.);
				glVertex3f(0.2,0.,0.);
			glEnd();

			glPointSize(3);
			glColor3f(weight*255,weight*255,0);
			//glutSolidSphere(.02,8,8);
			GLUquadric* quad =gluNewQuadric();
			gluSphere	(quad , 0.02,8,8);
			gluDeleteQuadric(quad);
			glBegin(GL_POINTS);
				glVertex3f(0.,0.,0.);
			glEnd();
			offset.transformGL();
			
			laser.drawGLMode=4;
			laser.drawGL();
		glPopMatrix();
	}
//protected:
	Pose3D pose;
	double weight;
	double drawWeight;
	LaserData laser;
	Pose3D offset;
};
