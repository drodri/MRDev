//
//////////////////////////////////////////////////////////////////////

#include "mrcoreglutapp.h" 
#include <iostream>

using namespace std;

MRCoreGlutApp::MRCoreGlutApp(string name):GlutApp(name)
{

}
void MRCoreGlutApp::MouseMove(int x,int y)
{
	scene.MouseMove(x,y);
	glutPostRedisplay();
}
void MRCoreGlutApp::Draw()
{
	scene.Draw();
}
void MRCoreGlutApp::MouseClick(int b,int state, int x,int y)
{
	bool down=(state==GLUT_DOWN);
	int button;
	if(b==GLUT_LEFT_BUTTON)
		button=MOUSE_LEFT_BUTTON;
	if(b==GLUT_RIGHT_BUTTON)
		button=MOUSE_RIGHT_BUTTON;
		
	int specialKey = glutGetModifiers();
	bool ctrlKey= (specialKey & GLUT_ACTIVE_CTRL)?true:false ;
	bool sKey= specialKey&GLUT_ACTIVE_SHIFT ;
	
	scene.MouseButton(x,y,b,down,sKey,ctrlKey);
	glutPostRedisplay();
}
void MRCoreGlutApp::Reshape(int w,int h)
{
	scene.setViewSize(0,0,w,h);
}
void MRCoreGlutApp::Key(unsigned char key)
{
	scene.KeyDown(key);
}
