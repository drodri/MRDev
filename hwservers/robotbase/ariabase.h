/**********************************************************************
 *
 * This code is part of the MRcore projec
 * Author:  the MRCore group
 *
 * MRcore is licenced under the Common Creative License,
 * Attribution-NonCommercial-ShareAlike 3.0
 *
 * You are free:
 *   - to Share - to copy, distribute and transmit the work
 *   - to Remix - to adapt the work
 *
 * Under the following conditions:
 *   - Attribution. You must attribute the work in the manner specified
 *     by the author or licensor (but not in any way that suggests that
 *     they endorse you or your use of the work).
 *   - Noncommercial. You may not use this work for commercial purposes.
 *   - Share Alike. If you alter, transform, or build upon this work,
 *     you may distribute the resulting work only under the same or
 *     similar license to this one.
 *
 * Any of the above conditions can be waived if you get permission
 * from the copyright holder.  Nothing in this license impairs or
 * restricts the author's moral rights.
 *
 * It is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  
 **********************************************************************/

#ifndef __ARIABASE_H_
#define __ARIABASE_H_

//long int abs(long int v){if(v>0)return v;return -v;}
using namespace std;
#include <cstdlib>
#include "Aria.h"
#include "mrcore/mrcore.h"

namespace mr
{
enum{PIONEER,PATROLBOT};
class AriaBase : public WheeledBase, public LaserSensor
{
public:
	AriaBase(int argc, char** argv);
	~AriaBase();
	//Wheeled robot interface realization
	bool getOdometry(Odometry& pose);
	bool move(double speed, double rot);
	bool getData(LaserData& laserData);
	bool getPose3D(Pose3D& pose){return false;}
	
	void watchdog();

protected:
	int robotType;
 	//ArSimpleConnector connector;
	ArRobotConnector* robotConnector;
   	ArLaserConnector* laserConnector;
	ArArgumentParser* argParser;
    ArRobot robot;
   	ArLaser* laser;
    int moveCount;
};

}; //end namespace mr

#endif
