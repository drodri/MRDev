#include "mrcore/mrcore.h"

void calculateTransformation(Vector2D ini, Vector2D end, double& width, double& height, Transformation3D& trans)
{
	
	if(ini.y==end.y)//paralela eje X
	{
		if(ini.x<end.x)
			trans=Transformation3D(ini.x,ini.y,0.0,X_AXIS,PI/2);
		else
			trans=Transformation3D(end.x,end.y,0.0,X_AXIS,PI/2);
		width=ini.distance(end);
		height=3.0;
	}
	else if(ini.x==end.x)//paralela eje Y
	{
		if(ini.y<end.y)
			trans=Transformation3D(end.x,end.y,0.0,Y_AXIS,-PI/2);
		else
			trans=Transformation3D(ini.x,ini.y,0.0,Y_AXIS,-PI/2);
		height=-ini.distance(end);
		width=3.0;
	}
	else
	{
		//pared diagonal
	}
}


void CreateWorldDisamLab(string filename)
{
	unsigned int i=0;
	World world;
	FaceSetPart *building=new FaceSetPart;
	vector<Vector2D> vertex;
	double x=0.0, y=0.0;
	
	//Find vertex on 'vertex.txt'
	FILE *fp;
	fp = fopen("data\\vertex.txt", "r");
	while(!feof(fp))
	{
		fscanf(fp,"%lf %lf\n",&x,&y);
		vertex.push_back(Vector2D(x,y));
	}
	fclose(fp);

	Face ground;
	ground.setBase(Transformation3D(0,0,0));
	for(i=0;i<vertex.size();i++)
		ground.addVertex(vertex[i].x,vertex[i].y);
	ground.setColor((float)0.6, (float)0.4, (float)0.4, 1);
	building->addFace(ground);
	
	Transformation3D trans;
	vector<Face> listWall;
	listWall.resize(vertex.size());
	double height=0.0, width=0.0;
	for(i=0;i<vertex.size()-1;i++)
	{
		calculateTransformation(vertex[i], vertex[i+1], width, height, trans);
		listWall[i].setBase(trans);
		listWall[i].addVertex(0,0);
		listWall[i].addVertex(width,0);
		listWall[i].addVertex(width,height);
		listWall[i].addVertex(0,height);
		listWall[i].setColor((float)0.9, (float)0.9, (float)0.5, (float)0.5);
	}
	
	//The last wall is between the first vertex and last vertex
	calculateTransformation(vertex[i], vertex[0], width, height, trans);
	listWall[i].setBase(trans);
	listWall[i].addVertex(0,0);
	listWall[i].addVertex(width,0);
	listWall[i].addVertex(width,height);
	listWall[i].addVertex(0,height);
	listWall[i].setColor((float)0.9, (float)0.9, (float)0.5, (float)1);

	//Some walls are actually doors then the colour has to change
	listWall[6].setColor((float)0.5, (float)0.5, (float)0.5, (float)1);
	listWall[9].setColor((float)0.5, (float)0.5, (float)0.5, (float)1);
	listWall[14].setColor((float)0.5, (float)0.5, (float)0.5, (float)1);
	listWall[27].setColor((float)0.5, (float)0.5, (float)0.5, (float)1);
	listWall[34].setColor((float)0.5, (float)0.5, (float)0.5, (float)1);
	listWall[43].setColor((float)0.5, (float)0.5, (float)0.5, (float)1);
	listWall[47].setColor((float)0.5, (float)0.5, (float)0.5, (float)1);
	


	//Add the walls to the building
	for (i=0; i<listWall.size();i++)
		building->addFace(listWall[i]);
	world+=building;
	StreamFile myfile(filename,false);
	myfile.write(&world);
}