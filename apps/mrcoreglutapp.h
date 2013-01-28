// CoordinadorPang.h: interface for the CoordinadorPang class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_mrcore_glut_app__included_)
#define _mrcore_glut_app__included_

#if _msc_ver > 1000
#pragma once
#endif // _msc_ver > 1000

#include "mrcore/mrcore.h"
#include "glutapp.h"

//singleton, do not create more than one per application
class MRCoreGlutApp : public GlutApp 
{
public:
	MRCoreGlutApp(string name);
	virtual ~MRCoreGlutApp(){}

	//Provide your own functions
	virtual void Key(unsigned char key);
	virtual void Draw();
	virtual void MouseMove(int x,int y);
	virtual void MouseClick(int button,int state, int x,int y);
	virtual void Reshape(int w,int h);


protected:
	GLScene scene;	
	

};

#endif

