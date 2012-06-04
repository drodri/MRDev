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
void createTable(double height, double widht, double deep, Vector2D origin, vector<Face> &table, bool tablon=false)
{
	table.resize(3);
	table[0].setBase(Transformation3D(origin.x,origin.y,height));
	table[0].addVertex(0.0,0.0);
	table[0].addVertex(0.0,widht);
	table[0].addVertex(deep,widht);
	table[0].addVertex(deep,0.0);
	table[1].setBase(Transformation3D(origin.x,origin.y,0,X_AXIS,PI/2));
	table[1].addVertex(0.0,0.0);
	table[1].addVertex(0.0,height);
	table[1].addVertex(deep,height);
	table[1].addVertex(deep,0.0);
	table[2]=table[1];
	table[2].setBase(Transformation3D(origin.x,origin.y+widht,0,X_AXIS,PI/2));

	table[0].setColor(0.6,0.6,0.15,1);
	table[1].setColor(0.6,0.6,0.15,1);
	table[2].setColor(0.6,0.6,0.15,1);
	if (tablon)
	{
		table.push_back(Face());
		table[3].setBase(Transformation3D(origin.x+deep-0.10,origin.y,0.20,Y_AXIS,-PI/2));
		table[3].addVertex(0.0,0.0);
		table[3].addVertex(height-0.20,0.0);
		table[3].addVertex(height-0.20,widht);
		table[3].addVertex(0.0,widht);
		table[3].setColor(0.6,0.6,0.15,1);
	}
}

void rotateTable(vector<Face> &table)
{
	double widht=(table[0].getMaxVertex()-table[0].getMinVertex()).y;
	table[0].setBase(table[0].getBase()*Transformation3D(0,0,0,Z_AXIS,PI/2));
	table[1].setBase(table[1].getBase()*Transformation3D(0,0,0,Y_AXIS,PI/2));
	table[2].setBase(table[2].getBase()*Transformation3D(-widht,0,widht,Y_AXIS,PI/2));
}

void createWardrobe(double height, double widht, double deep, Vector2D origin, vector <Face> &wardrobe)
					//Face &lat1, Face &lat2, Face &lat3, Face &lat4, Face &lat5)
{
	wardrobe.resize(5);
	wardrobe[0].setBase(Transformation3D(origin.x,origin.y,0,X_AXIS,PI/2));
	wardrobe[0].addVertex(0.0,0.0);
	wardrobe[0].addVertex(0.0,height);
	wardrobe[0].addVertex(deep,height);
	wardrobe[0].addVertex(deep,0.0);

	wardrobe[1]=wardrobe[0];
	wardrobe[1].setBase(Transformation3D(origin.x,origin.y+widht,0,X_AXIS,PI/2));

	wardrobe[2].setBase(Transformation3D(origin.x,origin.y,height));
	wardrobe[2].addVertex(0.0,0.0);
	wardrobe[2].addVertex(0.0,widht);
	wardrobe[2].addVertex(deep,widht);
	wardrobe[2].addVertex(deep,0.0);

	wardrobe[3].setBase(Transformation3D(origin.x,origin.y,0,Y_AXIS,-PI/2));
	wardrobe[3].addVertex(0.0,0.0);
	wardrobe[3].addVertex(height,0.0);
	wardrobe[3].addVertex(height,widht);
	wardrobe[3].addVertex(0.0,widht);

	wardrobe[4]=wardrobe[3];
	wardrobe[4].setBase(Transformation3D(origin.x+deep,origin.y,0,Y_AXIS,-PI/2));

	wardrobe[0].setColor(0.5,0.5,0.5,1);
	wardrobe[1].setColor(0.5,0.5,0.5,1);
	wardrobe[2].setColor(0.5,0.5,0.5,1);
	wardrobe[3].setColor(0.5,0.5,0.5,1);
	wardrobe[4].setColor(0.5,0.5,0.5,1);
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
	//double a=8.45,b=29.33;
	double a=0.0,b=0.0;
	vector<Face> stairs(1);
	stairs[0].setBase(Transformation3D(8.45-a,29.33-b,0,Y_AXIS,-PI/2));
	stairs[0].addVertex(0.00,0.00);
	stairs[0].addVertex(0.17,0.00);
	stairs[0].addVertex(0.17,0.30);
	stairs[0].addVertex(0.34,0.30);
	stairs[0].addVertex(0.34,0.60);
	stairs[0].addVertex(0.51,0.60);
	stairs[0].addVertex(0.51,0.90);
	stairs[0].addVertex(0.68,0.90);
	stairs[0].addVertex(0.68,1.20);
	stairs[0].addVertex(0.85,1.20);
	stairs[0].addVertex(0.85,1.50);
	stairs[0].addVertex(1.02,1.50);
	stairs[0].addVertex(1.02,1.80);
	stairs[0].addVertex(1.19,1.80);
	stairs[0].addVertex(1.19,2.10);
	stairs[0].addVertex(1.36,2.10);
	stairs[0].addVertex(1.36,2.40);
	stairs[0].addVertex(1.53,2.40);
	stairs[0].addVertex(1.53,2.70);
	stairs[0].addVertex(1.70,2.70);
	stairs[0].addVertex(1.70,3.00);
	stairs[0].addVertex(1.87,3.00);
	stairs[0].addVertex(1.87,3.30);
	stairs[0].addVertex(0.0,3.30);
	int tam=stairs.size();
	for(i=0;i<=10;i++)
	{
		stairs.push_back(Face());
		stairs[i+tam].setBase(Transformation3D(8.45-a,29.33+(i*0.30)-b,(i+1)*0.17));
		stairs[i+tam].addVertex(0.0,0.0);
		stairs[i+tam].addVertex(1.1,0.0);
		stairs[i+tam].addVertex(1.1,0.30);
		stairs[i+tam].addVertex(0.0,0.30);
	}
	tam=stairs.size();
	for(i=0;i<=10;i++)
	{
		stairs.push_back(Face());
		stairs[i+tam].setBase(Transformation3D(8.45-a,29.33+(i*0.30)-b,i*0.17,X_AXIS,PI/2));
		stairs[i+tam].addVertex(0.0,0.0);
		stairs[i+tam].addVertex(1.1,0.0);
		stairs[i+tam].addVertex(1.1,0.17);
		stairs[i+tam].addVertex(0.0,0.17);
	}

	stairs.push_back(Face());
	tam=stairs.size();
	stairs[tam-1].setBase(Transformation3D(8.45,32.63,0,X_AXIS,PI/2));
	stairs[tam-1].addVertex(0.0,0.0);
	stairs[tam-1].addVertex(-1.55,0.0);
	stairs[tam-1].addVertex(-1.55,1.87);
	stairs[tam-1].addVertex(0.0,1.87);

	stairs.push_back(Face());
	stairs[tam].setBase(Transformation3D(9.55,33.75,1.87));
	stairs[tam].addVertex(0.0,0.0);
	stairs[tam].addVertex(-2.65,0.0);
	stairs[tam].addVertex(-2.65,-1.10);
	stairs[tam].addVertex(0.0,-1.10);

	for(i=0;i<stairs.size();i++)
		building->addFace(stairs[i]);

	vector<Face> table1(3);	//Paloma's table
	createTable(1.0, 1.20, 0.95,Vector2D(1.30,0.0),table1,true);

	vector<Face> table2(3);	//Diego's table
	createTable(1.0, 1.20, 0.95,Vector2D(1.30,1.20),table2,true);

	vector<Face> table3(3);
	createTable(1.0, 1.10, 0.95,Vector2D(1.30,3.05),table3,true);

	vector<Face> table4(3);	//Julio's table
	createTable(1.0, 1.20, 0.70,Vector2D(3.27,0.0),table4,true);

	vector<Face> table5(3);	//Paloma's table
	createTable(1.0, 1.10, 0.70,Vector2D(3.27,3.05),table5,true);

	vector<Face> table6(3);	//Julian's table
	createTable(1.0, 1.20, 0.70,Vector2D(4.91,0.0),table6,true);

	vector<Face> table7(3);	//Urbano's table
	createTable(1.0, 0.66, 0.70,Vector2D(4.91,1.20),table7,true);

	vector<Face> table8(3);	//Alvaro's table
	createTable(1.0, 1.10, 0.70,Vector2D(4.91,3.05),table8,true);

	vector<Face> table9(3);
	createTable(1.0, 1.80, 0.85,Vector2D(8.45,0.0),table9);

	vector<Face> table10(3);
	createTable(1.0, 1.20, 0.80,Vector2D(6.7,4.55),table10);

	vector<Face> table11(3);
	createTable(1.0, 1.20, 0.80,Vector2D(6.7,5.80),table11);

	vector<Face> table12(3);
	createTable(1.0, 1.20, 0.80,Vector2D(6.7,7.05),table12);

	vector<Face> table13(3);
	createTable(1.0, 1.20, 0.80,Vector2D(5.2,4.55),table13);

	vector<Face> table14(3);
	createTable(1.0, 1.20, 0.80,Vector2D(5.2,5.80),table14);

	vector<Face> table15(3);
	createTable(1.0, 1.20, 0.80,Vector2D(5.2,7.05),table15);

	vector<Face> table16(3);
	createTable(1.0, 1.50, 0.80,Vector2D(6.7,10.70),table16);
	
	vector<Face> table17(3);
	createTable(1.0, 1.20, 0.80,Vector2D(6.7,12.25),table17);

	vector<Face> table18(3);
	createTable(1.0, 2.0, 0.80,Vector2D(6.5,9.65),table18);
	rotateTable(table18);

	vector<Face> table19(3);
	createTable(1.0, 2.0, 0.80,Vector2D(2.90,9.65),table19);
	rotateTable(table19);

	vector<Face> table20(3);
	createTable(1.0, 1.20, 0.80,Vector2D(3.2,4.55),table20);

	vector<Face> table21(3);
	createTable(1.0, 1.20, 0.80,Vector2D(3.2,5.80),table21);

	vector<Face> table22(3);
	createTable(1.0, 1.20, 0.80,Vector2D(3.2,7.05),table22);

	vector<Face> table23(3);
	createTable(1.0, 1.20, 0.80,Vector2D(2.35,4.55),table23);

	vector<Face> table24(3);
	createTable(1.0, 1.20, 0.80,Vector2D(2.35,5.80),table24);

	vector<Face> table25(3);
	createTable(1.0, 1.20, 0.80,Vector2D(2.35,7.05),table25);

	for (int i=0; i<3; i++)
	{
		building->addFace(table1[i]);
		building->addFace(table2[i]);
		building->addFace(table3[i]);
		building->addFace(table4[i]);
		building->addFace(table5[i]);
		building->addFace(table6[i]);
		building->addFace(table7[i]);
		building->addFace(table8[i]);
		building->addFace(table9[i]);
		building->addFace(table10[i]);
		building->addFace(table11[i]);
		building->addFace(table12[i]);
		building->addFace(table13[i]);
		building->addFace(table14[i]);
		building->addFace(table15[i]);
		building->addFace(table16[i]);
		building->addFace(table17[i]);
		building->addFace(table18[i]);
		building->addFace(table19[i]);
		building->addFace(table20[i]);
		building->addFace(table21[i]);
		building->addFace(table22[i]);
		building->addFace(table23[i]);
		building->addFace(table24[i]);
		building->addFace(table25[i]);
	}
	building->addFace(table1[3]);
	building->addFace(table2[3]);
	building->addFace(table3[3]);
	building->addFace(table4[3]);
	building->addFace(table5[3]);
	building->addFace(table6[3]);
	building->addFace(table7[3]);
	building->addFace(table8[3]);
	//building->addFace(table1[3]);
	
	vector<Face> wardrobe1(5);
	createWardrobe(2.0, 1.00, 0.50,Vector2D(8.80,1.82),wardrobe1);
	
	vector<Face> wardrobe2(5);	//lockers
	createWardrobe(2.20, 0.50, 1.35,Vector2D(5.66,3.65),wardrobe2);
	
	vector<Face> wardrobe3(5);
	createWardrobe(2.20, 0.85, 0.45,Vector2D(9.75,2.20),wardrobe3);
	
	vector<Face> wardrobe4(5);
	createWardrobe(2.20, 0.90, 0.45,Vector2D(9.75,1.25),wardrobe4);

	vector<Face> wardrobe5(5);
	createWardrobe(2.20, 0.85, 0.5,Vector2D(8.7,6.5),wardrobe5);

	vector<Face> wardrobe6(5);
	createWardrobe(2.20, 0.85, 0.5,Vector2D(8.7,7.4),wardrobe6);

	vector<Face> wardrobe7(5);
	createWardrobe(2.20, 0.85, 0.5,Vector2D(8.7,8.3),wardrobe7);

	vector<Face> wardrobe8(5);
	createWardrobe(2.20, 1.20, 0.5,Vector2D(8.7,9.2),wardrobe8);

	vector<Face> wardrobe9(5);
	createWardrobe(2.20, 0.8, 0.5,Vector2D(8.7,10.45),wardrobe9);

	vector<Face> wardrobe10(5);
	createWardrobe(2.20, 0.95, 0.5,Vector2D(8.7,11.30),wardrobe10);

	vector<Face> wardrobe11(5);
	createWardrobe(2.20, 0.95, 0.5,Vector2D(8.7,12.30),wardrobe11);

	vector<Face> wardrobe12(5);
	createWardrobe(2.20, 0.85, 0.5,Vector2D(8.7,13.30),wardrobe12);

	vector<Face> wardrobe13(5);
	createWardrobe(2.20, 0.50, 0.5,Vector2D(8.7,14.20),wardrobe13);

	vector<Face> wardrobe14(5);
	createWardrobe(2.50, 0.75, 1.90,Vector2D(5.8,15.30),wardrobe14);

	vector<Face> wardrobe15(5);	//robot
	createWardrobe(1.20, 1.0, 1.0,Vector2D(6.5,9.65),wardrobe15);

	vector<Face> wardrobe16(5);
	createWardrobe(1.50, 0.45, 1.20,Vector2D(6.3,13.5),wardrobe16);
	
	vector<Face> wardrobe17(5);
	createWardrobe(1.0, 0.50, 1.65,Vector2D(2.35,8.3),wardrobe17);

	vector<Face> wardrobe18(5);
	createWardrobe(1.20, 0.80, 1.50,Vector2D(2.95,9.65),wardrobe18);

	vector<Face> wardrobe19(5);
	createWardrobe(2.20, 1.20, 0.50,Vector2D(8.90,16.20),wardrobe19);

	vector<Face> wardrobe20(5);
	createWardrobe(2.20, 0.95, 0.50,Vector2D(8.90,17.95),wardrobe20);

	vector<Face> wardrobe21(5);
	createWardrobe(2.20, 0.95, 0.50,Vector2D(8.90,18.95),wardrobe21);

	vector<Face> wardrobe22(5);
	createWardrobe(1.70, 0.80, 0.70,Vector2D(8.90,19.95),wardrobe22);

	vector<Face> wardrobe23(5);
	createWardrobe(2.20, 0.74, 0.50,Vector2D(6.9,29.81),wardrobe23);

	vector<Face> wardrobe24(5);
	createWardrobe(1.0, 0.54, 0.15,Vector2D(6.9,28.71),wardrobe24);

	for (int i=0; i<5; i++)
	{
		building->addFace(wardrobe1[i]);
		building->addFace(wardrobe2[i]);
		building->addFace(wardrobe3[i]);
		building->addFace(wardrobe4[i]);
		building->addFace(wardrobe5[i]);
		building->addFace(wardrobe6[i]);
		building->addFace(wardrobe7[i]);
		building->addFace(wardrobe8[i]);
		building->addFace(wardrobe9[i]);
		building->addFace(wardrobe10[i]);
		building->addFace(wardrobe11[i]);
		building->addFace(wardrobe12[i]);
		building->addFace(wardrobe13[i]);
		building->addFace(wardrobe14[i]);
		building->addFace(wardrobe15[i]);
		building->addFace(wardrobe16[i]);
		building->addFace(wardrobe17[i]);
		building->addFace(wardrobe18[i]);
		building->addFace(wardrobe19[i]);
		building->addFace(wardrobe20[i]);
		building->addFace(wardrobe21[i]);
		building->addFace(wardrobe22[i]);
		building->addFace(wardrobe23[i]);
		building->addFace(wardrobe24[i]);
	}
	
	world+=building;
	StreamFile myfile(filename,false);
	myfile.write(&world);
}