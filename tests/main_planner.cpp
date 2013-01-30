// PruebaMRcore.cpp : Defines the entry point for the console application.
//


#include <mrcore.h>

#include <GL/glut.h>

#include <iostream>


using namespace mr;
using namespace std;

void createEnvironment(); //experimentto rampa


void OnDraw(void);

void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void OnMouseMove(int x,int y);
void OnMouseClick(int button,int state, int x,int y);

//The scene global object
GLScene scene;
World world;
WheeledBaseSim *myrobot;
Sampler *sampler;
PathPlanner *planner;
RobotPath solution;



int main(int argc, char* argv[])
{
	//GL Initialization stuff
	glutInit(&argc, argv);
	glutInitWindowSize(800,600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("GL");
	glutDisplayFunc(OnDraw);
	glutMotionFunc(OnMouseMove);
	glutMouseFunc(OnMouseClick);
	glutKeyboardFunc(OnKeyboardDown);
	
	scene.init();
	

	//Intializing test environment Faces included in a FacePart
	createEnvironment();
    scene.addObject(&world);	


   //creo el robot
	myrobot=new Pioneer3ATSim;
	myrobot->setRelativePosition(Vector3D(2.0,8,0));
	world+=myrobot;
	
	//creo un planificador y su sistema de muestreo
	sampler=new RandomSampler(&world);
	planner=new RDTplanner;
	(dynamic_cast<SBPathPlanner *>(planner))->setSampler(sampler); //solo especifico de los basados en muestreo
	
	
	glutMainLoop();
	world.destroyContent();
	return 0;
}

void OnDraw(void)
{  



	scene.Draw();
	planner->drawGL();

	solution.drawGL();


	glutSwapBuffers();
}




void OnKeyboardDown(unsigned char key, int x, int y)
{

	if(key=='+') {
		WBState gen(myrobot,&world);
		WBState *start=gen.createStateFromPoint3D(2.0,-8,0);
		WBState *goal=gen.createStateFromPoint3D(8.0,1.5,2);
		solution.path.clear();
		planner->setStartAndGoalStates(start, goal); //generico a cualquier planificador
		delete start;
		delete goal;
		if(planner->computePlan(3000))solution.path=(planner->getPlan())->path;
			
		}
	

	if(key=='f')
	{
		cout<<"FILTRADO: "<<solution.path.size()<<"-->";
		solution.filter();
		cout<<solution.path.size()<<endl;
	}

	

	glutPostRedisplay();	

}
void OnMouseClick(int b,int state, int x,int y)
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
void OnMouseMove(int x,int y)
{
	scene.MouseMove(x,y);
	
	glutPostRedisplay();
}



void createEnvironment()
{



	//Intializing test environment Faces included in a FacePart
	Face suelo(Transformation3D(0,0,0),0,-10,10,10);
	Face tablon_fino1(Transformation3D(8,3,2,X_AXIS,-0.53),0,0,0.2,3.95);
	Face tablon_fino2(Transformation3D(8.5,3,2,X_AXIS,-0.53),0,0,0.2,3.95);
	Face tablon_grueso(Transformation3D(2,3,2,X_AXIS,-0.53),0,0,1.4,3.95);
	Face plataforma(Transformation3D(2,0,2),0,0,8,3);
	Face paredfondo1(Transformation3D(0,0,0,Y_AXIS,PI/2),-4,-10,0,10);
	Face paredfondo2;

	paredfondo2.setBase(Transformation3D(0,0,0,X_AXIS,-PI/2));
	paredfondo2.addVertex(0,-4);
	paredfondo2.addVertex(10,-4);
	paredfondo2.addVertex(10,0);
	paredfondo2.addVertex(6,0);
	paredfondo2.addVertex(6,-1.5);
	paredfondo2.addVertex(4,-1.5);
	paredfondo2.addVertex(4,0);
	paredfondo2.addVertex(0,0);

	FaceSetPart *building=new FaceSetPart; 
	building->addFace(suelo);
	building->addFace(tablon_fino1);
	building->addFace(tablon_fino2);
	building->addFace(tablon_grueso);
	building->addFace(plataforma);
	building->addFace(paredfondo1);
	building->addFace(paredfondo2);
	
	world+=building;

}


