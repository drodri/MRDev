#include "mrcore/mrcore.h"

void CreateWorldBuilding(string filename)
{
	World world;

	float w=15;
	float h=5;
	float r=1.5;
	int pisos=3;
	//Intializing test environment Faces included in a FacePart
	Face suelo(Transformation3D(0,0,0),0,0, w,w);
	Face::setDefaultColor(0.9,0.9,0,0.1);
	Face pared1(Transformation3D(0,0,0,Y_AXIS,PI/2),-h,0,0,w);
	Face pared2(Transformation3D(w,0,0,Y_AXIS,PI/2),-h,0,0,w);
	Face pared3(Transformation3D(0,0,0,X_AXIS,PI/2),w,0,0,h);
	Face pared4(Transformation3D(0,w,0,X_AXIS,PI/2),w,0,0,h);

	Face::setDefaultColor(0.2,0.2,0.9,1);
	Face plataforma(Transformation3D(0,0,h/2),0,0,r,r);
	float ang=atan2(h/2,w/2-r);
	float len=sqrt(h*h/4+(w/2-r)*(w/2-r));
	Face rampa1(Transformation3D(0,r,h/2,X_AXIS,ang),0,0,r,len);
	Face rampa2(Transformation3D(r,0,h/2,Y_AXIS,ang),0,0,len,r);
	
	float r2=3;
	float h2=h/4;
	Face::setDefaultColor(0.2,0.9,0.2,1);
	Face obs(Transformation3D(w/2,w/2,h2),-r2/2,-r2/2,r2/2,r2/2);
	
	float ang2=atan2(h2,r2);
	float len2=sqrt(h2*h2+r2*r2);

	Face obsrampa1(Transformation3D(w/2-r2/2, w/2+r2/2,h2,X_AXIS,-ang2),0,0,r2,len2);
	Face obsrampa2(Transformation3D(w/2-r2/2, w/2-r2/2,h2,X_AXIS,ang2+PI),0,0,r2,len2);
	Face obsrampa3(Transformation3D(w/2+r2/2, w/2-r2/2,h2,Y_AXIS,ang2),0,0,len2,r2);
	Face obsrampa4(Transformation3D(w/2-r2/2, w/2-r2/2,h2,Y_AXIS,-ang2+PI),0,0,len2,r2);
	

	Face techo;
	techo.setBase(Transformation3D(0,0,h));
	techo.addVertex(r,0);
	techo.addVertex(r,w/2);
	techo.addVertex(0,w/2);
	techo.addVertex(0,w);
	techo.addVertex(w,w);
	techo.addVertex(w,0);
	techo.setColor(1,0.3,0.3,1);
	
	Face barandilla(Transformation3D(r,0,h,Y_AXIS,-PI/2),1,0,0,w/2);
//	Face rampa2(Transformation3D(0,0,h/2),0,0,r,r);

/*
	Face tablon_fino1(Transformation3D(8,3,2,X_AXIS,-0.53),0,0,0.2,3.95);
	Face tablon_fino2(Transformation3D(8.5,3,2,X_AXIS,-0.53),0,0,0.2,3.95);
	Face tablon_grueso(Transformation3D(2,3,2,X_AXIS,-0.53),0,0,1,3.95);
	Face plataforma(Transformation3D(2,0,2),0,0,8,3);
	plataforma.setColor(0.2,0.7,0.2,1);
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
	paredfondo2.setColor(0.5,0,0,1);

	FaceSetPart *building=new FaceSetPart; 
	building->addFace(suelo);
	building->addFace(tablon_fino1);
	building->addFace(tablon_fino2);
	building->addFace(tablon_grueso);
	building->addFace(plataforma);
	building->addFace(paredfondo1);
	building->addFace(paredfondo2);*/
	
	FaceSetPart *floor=new FaceSetPart; 
	floor->addFace(suelo);
	world+=floor;
		
	FaceSetPart *building=new FaceSetPart; 
	building->addFace(pared1);
	building->addFace(pared2);
	building->addFace(pared3);
	building->addFace(pared4);
	building->addFace(plataforma);
	building->addFace(rampa1);
	building->addFace(rampa2);
	building->addFace(obs);
	building->addFace(obsrampa1);
	building->addFace(obsrampa2);
	building->addFace(obsrampa3);
	building->addFace(obsrampa4);
	building->addFace(techo);
	building->addFace(barandilla);
//	building->setAbsoluteT3D(Transformation3D(0,0,0,0,0,PI));
	world+=building;


	for(int i=1;i<pisos;i++){
		FaceSetPart *paux2=new FaceSetPart(*building);
		paux2->setRelativePosition(Vector3D(0,0,h*i));
		world+=paux2;
	}

	Face::setDefaultColor(0.2,0.2,0.8,1);
	Face b1(Transformation3D(0,0,0,Y_AXIS,PI/2),-1,0,0,w);
	Face b2(Transformation3D(w,0,0,Y_AXIS,PI/2),-1,0,0,w);
	Face b3(Transformation3D(0,0,0,X_AXIS,PI/2),w,0,0,1);
	Face b4(Transformation3D(0,w,0,X_AXIS,PI/2),w,0,0,1);
	FaceSetPart *terr=new FaceSetPart; 
	terr->addFace(b1);
	terr->addFace(b2);
	terr->addFace(b3);
	terr->addFace(b4);
	terr->setRelativePosition(Vector3D(0,0,h*pisos));
	world+=terr;

	StreamFile myfile(filename,false);
	myfile.write(&world);
}