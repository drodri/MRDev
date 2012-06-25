#include "controlmanager.h"
#include <float.h>
ControlManager::ControlManager()
{
	manualControl=true;
	rot=speed=0;
	maxSpeed=2;
	maxRot=1;
}
void ControlManager::getSpeed(float& forward,float& turn)
{
	if(speed>maxSpeed)speed=maxSpeed;
	if(speed<-maxSpeed)speed=-maxSpeed;
	if(rot>maxRot)rot=maxRot;
	if(rot<-maxRot)rot=-maxRot;

	forward=speed;
	turn=rot;
}
void ControlManager::keyDown(unsigned char key)
{
	if(key=='a')
		rot+=0.05;
	else if(key=='d')
		rot-=0.05;
	else if(key=='s')
		speed-=0.05;
	else if(key=='w')
		speed+=0.05;
	else 
	{
		speed=rot=0;
	}
}
	