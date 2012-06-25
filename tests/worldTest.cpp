// PruebaMRcore.cpp : Defines the entry point for the console application.
//


#include "mrcore/mrcore.h"

#include "GL/glut.h"

#include <iostream>
#include "objects.h"


using namespace mr;
using namespace std;

void OnDraw(void);
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void OnMouseMove(int x,int y);
void OnMouseClick(int button,int state, int x,int y);


//The scene global object
GLScene scene;
World world;
PositionableEntity *paux;
//LaserSensor3DSim *pruebaLaser;
LaserSensorSim *pruebaLaser;
WheeledBaseSim *myrobot;
PowerCube70 *arm;
AdeptOneSim *manipulator;
QuadrotorSim *quadrotor;

//Implemented in "worlds" folder
void CreateWorldEuitiLab(string filename);
void CreateWorldBuilding(string filename);
void CreateWorldRobocityFair(string filename);

void InitWorld1();
void InitWorldColumns();
void InitWorldColumns2();
void InitWorld3();
void InitWorldSquaredRingNoWalls();
void InitWorldSquaredRingWalls();

int main(int argc, char* argv[])
{
	mrcoreInit();
	//GL Initialization stuff
	glutInit(&argc, argv);
	glutInitWindowSize(800,600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("GL");
	glutDisplayFunc(OnDraw);
	glutMotionFunc(OnMouseMove);
	glutMouseFunc(OnMouseClick);
	glutKeyboardFunc(OnKeyboardDown);
	glutTimerFunc(100,OnTimer,0);
	scene.init();

//		string filename="data/euitilab.world";
//	string filename="data/disamLab.world";
	string filename="data/robocity.world";
	CreateWorldRobocityFair(filename);
//	CreateWorldEuitiLab(filename);
//	string filename="building.world";
//	CreateWorldBuilding(filename);
	StreamFile myfile(filename,true);
	myfile.read(&world);
	
	
/*	if(1){
	StreamFile myfile("tmp.txt",false);
	myfile.write(&world);
	}*/

/*	PositionableEntity *test2=dynamic_cast<PositionableEntity *>(test1);
	
	if(test2){
		test2->LinkTo(mypart);
	}*/

//Adding objects to scene. As everything belongs to world, only world is added to the scene
//	scene.addObject(test2);

	/*WheeledBaseSim *prueba=dynamic_cast<WheeledBaseSim *>(test2->getObjectByName("Neo"));
	if(prueba)myrobot=prueba;*/
	scene.addObject(&world);	
	//scene.addObject(myrobot);
	//scene.addObject(pruebaLaser);
	glutMainLoop();
	world.destroyContent();
	cout<<"PULSE S PARA GRABAR EN TMP.TXT EL ENTORNO"<<std::endl;
	return 0;
}

void OnDraw(void)
{  

	scene.Draw();
	glutSwapBuffers();
}
void OnTimer(int value)
{
	world.simulate(0.05);//50 ms
	//pruebaLaser->updateSensorData();

	glutTimerFunc(50,OnTimer,0); //set again the timer
	glutPostRedisplay();	
	
}
void OnKeyboardDown(unsigned char key, int x, int y)
{
	LOG_INFO("ON keyboard down "<<key);
	scene.KeyDown(key);
	if(key=='s'){
		LOG_INFO("Writing world");
		StreamFile myfile("tmp.txt",false);
		myfile.write(&world);
		}


	static double angle=0;
/*	if(key=='0')
		pruebaLaser->setDrawGLMode(0);
	if(key=='1')
		pruebaLaser->setDrawGLMode(1);
	if(key=='2')
		pruebaLaser->setDrawGLMode(2);
	if(key=='3')
		pruebaLaser->setDrawGLMode(3);
	if(key=='4')
		pruebaLaser->setDrawGLMode(4);
	float pan,tilt;
	arm->GetPos(pan,tilt);
	if(key=='d')pan+=0.05;
	if(key=='a')pan-=0.05;
	if(key=='w')tilt+=0.05;
	if(key=='x')tilt-=0.05;
	arm->Move(pan,tilt);


	static double speed=0;
	static double rotspeed=0;
	static double altura=0.1;
	if(key=='t')speed+=0.1;
	if(key=='b')speed-=0.1;
	if(key=='h')rotspeed-=0.2;
	if(key=='f')rotspeed+=0.2;
	if(key==' ')rotspeed=speed=0;*/

	if(key=='S'){
		StreamFile myfile("tmp.txt",false);
		myfile.write(&world);
		}
/*
	
	if(key=='o'){
		manipulator->getJoint(0)->setTarget(0.5);
		manipulator->getJoint(0)->setSpeed(0.4);
		manipulator->getJoint(1)->setTarget(0.5);
		manipulator->getJoint(1)->setSpeed(0.4);
	}
	if(key=='p'){
		manipulator->getJoint(0)->setTarget(2.5);
		manipulator->getJoint(0)->setSpeed(0.4);
		manipulator->getJoint(1)->setTarget(2.5);
		manipulator->getJoint(1)->setSpeed(0.4);
	}
	
	myrobot->move(speed,rotspeed);
	pruebaLaser->updateSensorData();*/
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

void InitWorldSquaredRingWalls()
{
	//Intializing test environment Faces included in a FacePart
	Face suelo1(Transformation3D(0,0,0),-10,-10,-8,10);
	Face suelo2(Transformation3D(0,0,0),8,-10,10,10);
	Face suelo3(Transformation3D(0,0,0),-8,8,8,10);
	Face suelo4(Transformation3D(0,0,0),-8,-10,8,-8);
	suelo1.setColor(0.3f, 0.3f, 0.4f, 1);
	suelo2.setColor(0.3f, 0.3f, 0.4f, 1);
	suelo3.setColor(0.3f, 0.3f, 0.4f, 1);
	suelo4.setColor(0.3f, 0.3f, 0.4f, 1);
	
	Face paredexterna1(Transformation3D(-10,0,0,Y_AXIS,PI/2),-5,-10,0,10);
	Face paredexterna2(Transformation3D(10,0,0,Y_AXIS,PI/2),-5,-10,0,10);
	Face paredexterna3(Transformation3D(0,-10,0,X_AXIS,PI/2),-10,0,10,5);
	Face paredexterna4(Transformation3D(0,10,0,X_AXIS,PI/2),-10,0,10,5);
	paredexterna1.setColor(0.5f, 0.5f, 0.0f, 1);
	paredexterna2.setColor(0.5f, 0.5f, 0.0f, 1);
	paredexterna3.setColor(0.5f, 0.5f, 0.0f, 1);
	paredexterna4.setColor(0.5f, 0.5f, 0.0f, 1);
	
	Face paredinterna1(Transformation3D(-8,0,0,Y_AXIS,PI/2),-5,-8,0,8);
	Face paredinterna2(Transformation3D(8,0,0,Y_AXIS,PI/2),-5,-8,0,8);
	Face paredinterna3(Transformation3D(0,-8,0,X_AXIS,PI/2),-8,0,8,5);
	Face paredinterna4(Transformation3D(0,8,0,X_AXIS,PI/2),-8,0,8,5);
	paredinterna1.setColor(0.5f, 0.5f, 0.0f, 1);
	paredinterna2.setColor(0.5f, 0.5f, 0.0f, 1);
	paredinterna3.setColor(0.5f, 0.5f, 0.0f, 1);
	paredinterna4.setColor(0.5f, 0.5f, 0.0f, 1);

	FaceSetPart *building=new FaceSetPart; 
	building->addFace(suelo1);
	building->addFace(suelo2);
	building->addFace(suelo3);
	building->addFace(suelo4);
	
	building->addFace(paredexterna1);
	building->addFace(paredexterna2);
	building->addFace(paredexterna3);
	building->addFace(paredexterna4);
	
	building->addFace(paredinterna1);
	building->addFace(paredinterna2);
	building->addFace(paredinterna3);
	building->addFace(paredinterna4);

	world+=building;
}


void InitWorldSquaredRingNoWalls()
{
	//Intializing test environment Faces included in a FacePart
	Face suelo1(Transformation3D(0,0,0),-10,-10,-8,10);
	Face suelo2(Transformation3D(0,0,0),8,-10,10,10);
	Face suelo3(Transformation3D(0,0,0),-8,8,8,10);
	Face suelo4(Transformation3D(0,0,0),-8,-10,8,-8);
	suelo1.setColor(0.3f, 0.3f, 0.4f, 1);
	suelo2.setColor(0.3f, 0.3f, 0.4f, 1);
	suelo3.setColor(0.3f, 0.3f, 0.4f, 1);
	suelo4.setColor(0.3f, 0.3f, 0.4f, 1);
	
	Face paredexterna1(Transformation3D(-20,0,0,Y_AXIS,PI/2),-5,-10,0,10); //añadida por el problema con las glut
	paredexterna1.setColor(0.5f, 0.5f, 0.0f, 1);
	
	FaceSetPart *building=new FaceSetPart; 
	building->addFace(suelo1);
	building->addFace(suelo2);
	building->addFace(suelo3);
	building->addFace(suelo4);
	
	building->addFace(paredexterna1);

	world+=building;
}

void InitWorld3()
{
	//Intializing test environment Faces included in a FacePart
	Face suelo(Transformation3D(0,0,0),-10,-10,10,10);
	suelo.setColor(0.3f, 0.3f, 0.4f, 1);

	Face paredfondo1(Transformation3D(-10,0,0,Y_AXIS,PI/2),-3,-10,0,10);
	Face paredfondo2(Transformation3D(10,0,0,Y_AXIS,PI/2),-3,-10,0,10);
	Face paredfondo3(Transformation3D(-10,-10,0,X_AXIS,PI/2),0, 0, 20, 3);
	Face paredfondo4(Transformation3D(-10,10,0,X_AXIS,PI/2),0, 0, 20, 3);
	paredfondo1.setColor(0.5f, 0.5f, 0.0f, 1);
	paredfondo2.setColor(0.5f, 0.5f, 0.0f, 1);
	paredfondo3.setColor(0.5f, 0.5f, 0.0f, 1);
	paredfondo4.setColor(0.5f, 0.5f, 0.0f, 1);

	FaceSetPart *building=new FaceSetPart; 
	building->addFace(suelo);
	building->addFace(paredfondo1);
	building->addFace(paredfondo2);
	building->addFace(paredfondo3);
	building->addFace(paredfondo4);

	world+=building;
}

void InitWorldColumns()
{
	//Intializing test environment Faces included in a FacePart
	Face suelo(Transformation3D(0,0,0),-10,-10,15,10);
	suelo.setColor(0.3f, 0.3f, 0.4f, 1);

	Face paredfondo1(Transformation3D(-10,0,0,Y_AXIS,PI/2),-3,-10,0,10);
	Face paredfondo2(Transformation3D(15,0,0,Y_AXIS,PI/2),-3,-10,0,10);
	Face paredfondo3(Transformation3D(-10,-10,0,X_AXIS,PI/2),0, 0, 25, 3);
	Face paredfondo4(Transformation3D(-10,10,0,X_AXIS,PI/2),0, 0, 25, 3);
	Face paredmedio(Transformation3D(-10,0,0,X_AXIS,PI/2),2, 0, 23, 3);
	paredfondo1.setColor(0.5f, 0.5f, 0.0f, 1);
	paredfondo2.setColor(0.5f, 0.5f, 0.0f, 1);
	paredfondo3.setColor(0.5f, 0.5f, 0.0f, 1);
	paredfondo4.setColor(0.5f, 0.5f, 0.0f, 1);
	paredmedio.setColor(0.8f, 0.5f, 0.0f, 1);

	FaceSetPart *building=new FaceSetPart; 
	building->addFace(suelo);
	building->addFace(paredfondo1);
	building->addFace(paredfondo2);
	building->addFace(paredfondo3);
	building->addFace(paredfondo4);
	building->addFace(paredmedio);

	float sep=1.7;
	int cont=0;
	for(float x=-5;x<=10;x+=sep)
	{
		cont++;
		for(float y=-10;y<=0;y+=sep)
		{	
			PrismaticPart *mypart=new PrismaticPart;
			vector<Vector2D> list;
			list.push_back(Vector2D(0,0));
			list.push_back(Vector2D(0,.2));
			list.push_back(Vector2D(.2,.2));
			list.push_back(Vector2D(.2,0));
			mypart->setPolygonalBase(list);
			mypart->setRelativePosition(Vector3D(x,y+(cont%3)*sep/3,0));
			mypart->setRelativeOrientation(0,0,PI/2);
			mypart->setHeight(1);
			world+=mypart;
		}
	}

	world+=building;
}
void InitWorldColumns2()
{
	//Intializing test environment Faces included in a FacePart
	Face suelo(Transformation3D(0,0,0),-10,-10,15,10);
	suelo.setColor(0.3f, 0.3f, 0.4f, 1);

	Face paredfondo1(Transformation3D(-10,0,0,Y_AXIS,PI/2),-3,-10,0,10);
	Face paredfondo2(Transformation3D(15,0,0,Y_AXIS,PI/2),-3,-10,0,10);
	Face paredfondo3(Transformation3D(-10,-10,0,X_AXIS,PI/2),0, 0, 25, 3);
	Face paredfondo4(Transformation3D(-10,10,0,X_AXIS,PI/2),0, 0, 25, 3);
//	Face paredmedio(Transformation3D(-10,0,0,X_AXIS,PI/2),2, 0, 23, 3);
	paredfondo1.setColor(0.5f, 0.5f, 0.0f, 1);
	paredfondo2.setColor(0.5f, 0.5f, 0.0f, 1);
	paredfondo3.setColor(0.5f, 0.5f, 0.0f, 1);
	paredfondo4.setColor(0.5f, 0.5f, 0.0f, 1);
//	paredmedio.setColor(0.8f, 0.5f, 0.0f, 1);

	FaceSetPart *building=new FaceSetPart; 
	building->addFace(suelo);
	building->addFace(paredfondo1);
	building->addFace(paredfondo2);
	building->addFace(paredfondo3);
	building->addFace(paredfondo4);
//	building->addFace(paredmedio);

	float sep=1.7;
	float colWidth=0.3;
	int cont=0;
	for(float x=-8;x<=14;x+=sep)
	{
		cont++;
		for(float y=-10;y<=10;y+=sep)
		{	
			PrismaticPart *mypart=new PrismaticPart;
			vector<Vector2D> list;
			list.push_back(Vector2D(0,0));
			list.push_back(Vector2D(0,colWidth));
			list.push_back(Vector2D(colWidth,colWidth));
			list.push_back(Vector2D(colWidth,0));
			mypart->setPolygonalBase(list);
			mypart->setRelativePosition(Vector3D(x,y+(cont%3)*sep/3,0));
			mypart->setRelativeOrientation(0,0,PI/2);
			mypart->setHeight(1);
			world+=mypart;
		}
	}

	world+=building;
}
void InitWorld1()
{
	//Intializing test environment Faces included in a FacePart
	Face suelo(Transformation3D(0,0,0),0,-10,10,10);
	Face tablon_fino1(Transformation3D(8,3,2,X_AXIS,-0.53),0,0,0.2,3.95);
	Face tablon_fino2(Transformation3D(8.5,3,2,X_AXIS,-0.53),0,0,0.2,3.95);
	Face tablon_grueso(Transformation3D(2,3,2,X_AXIS,-0.53),0,0,1,3.95);
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

	FaceSetPart *paux2=new FaceSetPart(*building);
	paux2->setRelativeOrientation(0,0,PI);
	paux2->setRelativePosition(Vector3D(20,0,0));
	world+=paux2;
	
//probando el prismaticpart
	PrismaticPart *mypart=new PrismaticPart;
	vector<Vector2D> list;
	list.push_back(Vector2D(0,0));
	list.push_back(Vector2D(0,1));
	list.push_back(Vector2D(1,1));
	list.push_back(Vector2D(1.5,0.5));
	list.push_back(Vector2D(1,0));
	mypart->setPolygonalBase(list);
	mypart->setRelativePosition(Vector3D(7,7,3));
	mypart->setRelativeOrientation(PI/2,0,0);
	mypart->setHeight(4);

	SpherePart *esfera=new SpherePart;
	esfera->setRelativePosition(Vector3D(7,7,6));
	world+=mypart;
	world+=esfera;
//it works!!!

//probando el mesh

//	MeshPart *tmesh=createWoodBench();
//	tmesh->setRelativePosition(Vector3D(12,2,0));
//	world+=tmesh;	
	
//probando el robot
	myrobot=new Pioneer3ATSim;
	myrobot->setRelativePosition(Vector3D(2.0,8,0));
	myrobot->setName("Neo");
	world+=myrobot;

//probando el powercube + laser LMS
	arm=new PowerCube70Sim;
	((PowerCube70Sim *)arm)->setRelativePosition(Vector3D(0.1,0,0.285));
	((PowerCube70Sim *)arm)->LinkTo(myrobot); 
	pruebaLaser=new LMS100Sim;
	pruebaLaser->setColor(0,1,0);
	//para el LMS200 pruebaLaser->setRelativePosition(Vector3D(0,0,0.063));
	/*para el LMS100*/ pruebaLaser->setRelativePosition(Vector3D(0,0,0.1157));
	pruebaLaser->LinkTo(((PowerCube70Sim *)arm)->getTcp());//plug in the laser at the end of the arm

//probando el laser
/*	pruebaLaser=new NemoLaserSensor3DSim;
	pruebaLaser->setColor(0,1,0);
	pruebaLaser->LinkTo(myrobot);//lo fijo a mano al final del mecanismo
	pruebaLaser->setRelativePosition(Vector3D(0.1,0,0.285));
	pruebaLaser->updateSensorData(); //actualizo las medidas para la primera impresión

	arm=(dynamic_cast<NemoLaserSensor3DSim *>(pruebaLaser))->getPowerCube70();
*/
//probando el AdeptOne
	manipulator=new AdeptOneSim;
	manipulator->setRelativePosition(Vector3D(6,1,2));
	world+=manipulator;

//probando el Puma560
	Puma560Sim *puma=new Puma560Sim;
	puma->setRelativePosition(Vector3D(7,2,2));
	world+=puma;
//probando el aseaIrb2000
	AseaIRB2000Sim *asea=new AseaIRB2000Sim;
	asea->setRelativePosition(Vector3D(5,2,2));
	world+=asea;

//probando el quadrotor
	quadrotor=new QuadrotorSim(0.3);
	quadrotor->setRelativePosition(Vector3D(3,3,2));
	world+=quadrotor;
}
