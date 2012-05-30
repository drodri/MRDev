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
void createTable(double height, double widht, double deep, Vector2D origin,
					Face &lat1, Face &lat2, Face &plank)
{
	plank.setBase(Transformation3D(origin.x,origin.y,height));
	plank.addVertex(0.0,0.0);
	plank.addVertex(0.0,widht);
	plank.addVertex(deep,widht);
	plank.addVertex(deep,0.0);
	lat1.setBase(Transformation3D(origin.x,origin.y,0,X_AXIS,PI/2));
	lat1.addVertex(0.0,0.0);
	lat1.addVertex(0.0,height);
	lat1.addVertex(deep,height);
	lat1.addVertex(deep,0.0);
	lat2=lat1;
	lat2.setBase(Transformation3D(origin.x,origin.y+widht,0,X_AXIS,PI/2));
	lat1.setColor(0.6,0.6,0.15,1);
	lat2.setColor(0.6,0.6,0.15,1);
	plank.setColor(0.6,0.6,0.15,1);
}

void createWardrobe(double height, double widht, double deep, Vector2D origin,
					Face &lat1, Face &lat2, Face &lat3, Face &lat4, Face &lat5)
{
	lat1.setBase(Transformation3D(origin.x,origin.y,0,X_AXIS,PI/2));
	lat1.addVertex(0.0,0.0);
	lat1.addVertex(0.0,height);
	lat1.addVertex(deep,height);
	lat1.addVertex(deep,0.0);

	lat2=lat1;
	lat2.setBase(Transformation3D(origin.x,origin.y+widht,0,X_AXIS,PI/2));

	lat3.setBase(Transformation3D(origin.x,origin.y,height));
	lat3.addVertex(0.0,0.0);
	lat3.addVertex(0.0,widht);
	lat3.addVertex(deep,widht);
	lat3.addVertex(deep,0.0);

	lat4.setBase(Transformation3D(origin.x,origin.y,0,Y_AXIS,-PI/2));
	lat4.addVertex(0.0,0.0);
	lat4.addVertex(height,0.0);
	lat4.addVertex(height,widht);
	lat4.addVertex(0.0,widht);

	lat5=lat4;
	lat5.setBase(Transformation3D(origin.x+deep,origin.y,0,Y_AXIS,-PI/2));

	lat1.setColor(0.5,0.5,0.5,1);
	lat2.setColor(0.5,0.5,0.5,1);
	lat3.setColor(0.5,0.5,0.5,1);
	lat4.setColor(0.5,0.5,0.5,1);
	lat5.setColor(0.5,0.5,0.5,1);
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

	vector<Face> table1(3);
	createTable(1.0, 1.20, 0.80,Vector2D(0.0,0.0),table1[0], table1[1], table1[2]);
	building->addFace(table1[0]);
	building->addFace(table1[1]);
	building->addFace(table1[2]);

	vector<Face> wardrobe1(5);
	createWardrobe(2.0, 1.20, 0.80,Vector2D(0.0,0.0),wardrobe1[0], wardrobe1[1], wardrobe1[2],
					wardrobe1[3], wardrobe1[4]);
	building->addFace(wardrobe1[0]);
	building->addFace(wardrobe1[1]);
	building->addFace(wardrobe1[2]);
	building->addFace(wardrobe1[3]);
	building->addFace(wardrobe1[4]);
	
	world+=building;
	StreamFile myfile(filename,false);
	myfile.write(&world);
}