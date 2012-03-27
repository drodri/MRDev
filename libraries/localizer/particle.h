#include "mrcore/mrcore.h"
#include "gl/glut.h"
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
			glTranslatef(0,0,weight);
			glBegin(GL_LINES);
				glVertex3f(0.,0.,0.);
				glVertex3f(0.2,0.,0.);
			glEnd();

			glPointSize(3);
			glColor3f(weight*255,weight*255,0);
			glutSolidSphere(.02,8,8);
			glBegin(GL_POINTS);
				glVertex3f(0.,0.,0.);
			glEnd();
		//	offset.transformGL();
		//	laser.drawGL();
		glPopMatrix();
	}
//protected:
	Pose3D pose;
	double weight;
//	LaserData laser;
//	Pose3D offset;
};
