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
			glBegin(GL_LINES);
				glVertex3f(0.,0.,0.);
				glVertex3f(0.2,0.,0.);
			glEnd();

			glPointSize(2);
			glColor3f(255,255,0);
			glBegin(GL_POINTS);
				glVertex3f(0.,0.,0.);
			glEnd();
		glPopMatrix();
	}
//protected:
	Pose3D pose;
	double weight;
};
