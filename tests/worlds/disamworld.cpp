#include "mrcore/mrcore.h"

void CreateWorldDisamLab(string filename)
{
	World world;
	//Intializing test environment Faces included in a FacePart
	//laboratorio
	Face suelo;
	suelo.setBase(Transformation3D(0,0,0));
	//suelo.setBase(Transformation3D(0,0,1.0,X_AXIS,PI/2));
	suelo.addVertex(0,0);
	suelo.addVertex(9.30,0.00);
	suelo.addVertex(9.30,3.20);
	suelo.addVertex(9.45,3.20);
	suelo.addVertex(9.45,3.10);
	suelo.addVertex(9.75,3.10);
	suelo.addVertex(9.75,0.30);
	suelo.addVertex(10.95,0.30);
	suelo.addVertex(10.95,3.25);
	suelo.addVertex(11.05,3.25);
	suelo.addVertex(11.05,4.05);
	suelo.addVertex(10.95,4.05);
	suelo.addVertex(10.95,4.20);
	suelo.addVertex(10.75,4.20);
	suelo.addVertex(10.75,4.40);
	suelo.addVertex(9.95,4.40);
	suelo.addVertex(9.95,4.20);
	suelo.addVertex(9.75,4.20);
	suelo.addVertex(9.75,4.10);
	suelo.addVertex(9.45,4.10);
	suelo.addVertex(9.45,4.00);
	suelo.addVertex(9.30,4.00);
	suelo.addVertex(9.30,4.15);
	suelo.addVertex(9.00,4.15);
	suelo.addVertex(9.00,4.55);
	suelo.addVertex(9.20,4.55);
	//seguir aqui
	suelo.addVertex(0.00,4.55);
	suelo.addVertex(7.60,4.55);
	suelo.addVertex(7.60,4.15);
	suelo.addVertex(0.0,4.15);
	suelo.setColor(0.6, 0.4, 0.4, 1);
	


	FaceSetPart *building=new FaceSetPart; 
	building->addFace(suelo);
	world+=building;
	StreamFile myfile(filename,false);
	myfile.write(&world);
}