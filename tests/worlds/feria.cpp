#include "mrcore/mrcore.h"

Face calculateFace(Vector2D ini, Vector2D end, double h)
{
	double width=0, height=0;
	Transformation3D trans;
	
	if(ini.y==end.y)//paralela eje X
	{
		if(ini.x<end.x)
			trans=Transformation3D(ini.x,ini.y,0.0,X_AXIS,PI/2);
		else
			trans=Transformation3D(end.x,end.y,0.0,X_AXIS,PI/2);
		width=ini.distance(end);
		height=h;
	}
	else if(ini.x==end.x)//paralela eje Y
	{
		if(ini.y<end.y)
			trans=Transformation3D(end.x,end.y,0.0,Y_AXIS,-PI/2);
		else
			trans=Transformation3D(ini.x,ini.y,0.0,Y_AXIS,-PI/2);
		height=-ini.distance(end);
		width=h;
	}
	else
	{
		//pared diagonal
	}
	Face ret;
	ret.setBase(trans);
	ret.addVertex(0,0);
	ret.addVertex(width,0);
	ret.addVertex(width,height);
	ret.addVertex(0,height);
	//ret.setColor((float)0.9, (float)0.9, (float)0.5, (float)1);
	return ret;
}

void CreateBox(double height, double deep, double width, Vector2D origin, vector<Face>& box)
{
	box.resize(6);
	box[0].setBase(Transformation3D(origin.x,origin.y,0,X_AXIS,PI/2));
	box[0].addVertex(0.0,0.0);
	box[0].addVertex(0.0,height);
	box[0].addVertex(deep,height);
	box[0].addVertex(deep,0.0);

	box[1]=box[0];
	box[1].setBase(Transformation3D(origin.x,origin.y+width,0,X_AXIS,PI/2));

	box[2].setBase(Transformation3D(origin.x,origin.y,height));
	box[2].addVertex(0.0,0.0);
	box[2].addVertex(0.0,width);
	box[2].addVertex(deep,width);
	box[2].addVertex(deep,0.0);

	box[3].setBase(Transformation3D(origin.x,origin.y,0,Y_AXIS,-PI/2));
	box[3].addVertex(0.0,0.0);
	box[3].addVertex(height,0.0);
	box[3].addVertex(height,width);
	box[3].addVertex(0.0,width);

	box[4]=box[3];
	box[4].setBase(Transformation3D(origin.x+deep,origin.y,0,Y_AXIS,-PI/2));
}

void CreateWorldFeria(string filename)
{
	unsigned int i=0;
	World world;
	FaceSetPart *building=new FaceSetPart;
	double height=5.0, width=23.95, deep=20.55;
	Face ground;
	ground.setBase(Transformation3D(0,0,0));
	ground.addVertex(0,0);
	ground.addVertex(deep,0);
	ground.addVertex(deep,width);
	ground.addVertex(0,width);
	ground.setColor((float)0.6, (float)0.4, (float)0.4, 1);
	building->addFace(ground);

	vector<Face> listWall(4);
	listWall[0].setBase(Transformation3D(0,0,0,X_AXIS,PI/2));
	listWall[0].addVertex(0,0);
	listWall[0].addVertex(deep,0);
	listWall[0].addVertex(deep,height);
	listWall[0].addVertex(0,height);
	listWall[1]=listWall[0];
	listWall[1].setBase(Transformation3D(0,width,0,X_AXIS,PI/2));
	listWall[2].setBase(Transformation3D(0,0,0,Y_AXIS,-PI/2));
	listWall[2].addVertex(0,0);
	listWall[2].addVertex(height,0);
	listWall[2].addVertex(height,width);
	listWall[2].addVertex(0,width);
	listWall[3]=listWall[2];
	listWall[3].setBase(Transformation3D(deep,0,0,Y_AXIS,-PI/2));
	for(i=0;i<listWall.size();i++)
	{
		listWall[i].setColor((float)0.9, (float)0.9, (float)0.5, (float)0.5);
		building->addFace(listWall[i]);
	}

	double columnWidth=0.50, columnDeep=0.50, columnHeight=height;
	vector<Face> column1,column2,column3,column4,column5,column6,column7,column8,column9,column10,column11;
	listWall[0].setDefaultColor(0.5,0.5,0.5,1.0);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(3.80,4.00), column1);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(7.90,4.00), column2);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(12.00,4.00), column3);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(16.10,4.00), column4);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(16.10,8.10), column5);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(16.10,14.35), column6);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(16.10,18.45), column7);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(12.00,18.45), column8);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(7.90,18.45), column9);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(3.80,18.45), column10);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(3.80,14.35), column11);
	
	for(i=0; i<column1.size();i++)
	{
		building->addFace(column1[i]);
		building->addFace(column2[i]);
		building->addFace(column3[i]);
		building->addFace(column4[i]);
		building->addFace(column5[i]);
		building->addFace(column6[i]);
		building->addFace(column7[i]);
		building->addFace(column8[i]);
		building->addFace(column9[i]);
		building->addFace(column10[i]);
		building->addFace(column11[i]);
	}
	vector<Face> mueble;
	column1[0].setDefaultColor(0.6,0.6,0.2,1.0);
	CreateBox(2.0,4.50,1.0,Vector2D(7.6,0.0),mueble);
	for(i=0;i<mueble.size();i++)
		building->addFace(mueble[i]);

	//Altura imaginaria de los stands
	double standHeight=0.0;
	mueble[0].setDefaultColor(0.2,0.4,0.8,1.0);
	vector<Face> stand1,stand2,stand3,stand4,stand5,stand6,stand7,stand8,stand9,stand10,stand12,
				 stand13,stand14,stand16,stand17,stand18,stand19,stand20,stand21,stand22;
	CreateBox(standHeight,2,3.05,Vector2D(6.3,13.3),stand1);
	CreateBox(standHeight,2,3.05,Vector2D(6.3,10.25),stand2);
	CreateBox(standHeight,2,3.05,Vector2D(6.3,7.2),stand3);
	CreateBox(standHeight,4.30,2,Vector2D(8.3,7.2),stand4);
	CreateBox(standHeight,2,3.05,Vector2D(12.6,7.2),stand5);
	CreateBox(standHeight,2,3.05,Vector2D(12.6,10.25),stand6);
	CreateBox(standHeight,2,3.05,Vector2D(12.6,13.3),stand7);
	CreateBox(standHeight,4.30,2,Vector2D(8.3,14.35),stand8);
	CreateBox(standHeight,4.3,2.35,Vector2D(0,14.35),stand9);
	CreateBox(standHeight,4.3,2.35,Vector2D(0,16.7),stand10);
	CreateBox(standHeight,3.95,3.95,Vector2D(6.05,20.0),stand12);
	CreateBox(standHeight,2.5,3.95,Vector2D(10.0,20.0),stand13);
	CreateBox(standHeight,3.95,3.95,Vector2D(12.5,20.0),stand14);
	CreateBox(standHeight,4.45,2.05,Vector2D(16.10,12.80),stand16);
	CreateBox(standHeight,4.45,2.05,Vector2D(16.10,8.1),stand17);
	CreateBox(standHeight,4.45,2.05,Vector2D(16.10,6.05),stand18);
	CreateBox(standHeight,4.45,2.05,Vector2D(16.10,4.0),stand19);
	CreateBox(standHeight,2.5,3.95,Vector2D(12.2,0),stand20);
	CreateBox(standHeight,4.6,2.95,Vector2D(7.6,1.0),stand21);
	CreateBox(standHeight,3.80,3.95,Vector2D(3.80,0.0),stand22);

	for(i=0; i<stand1.size();i++)
	{
		building->addFace(stand1[i]);
		building->addFace(stand2[i]);
		building->addFace(stand3[i]);
		building->addFace(stand4[i]);
		building->addFace(stand5[i]);
		building->addFace(stand6[i]);
		building->addFace(stand7[i]);
		building->addFace(stand8[i]);
		building->addFace(stand9[i]);
		building->addFace(stand10[i]);
		building->addFace(stand12[i]);
		building->addFace(stand13[i]);
		building->addFace(stand14[i]);
		building->addFace(stand16[i]);
		building->addFace(stand17[i]);
		building->addFace(stand18[i]);
		building->addFace(stand19[i]);
		building->addFace(stand20[i]);
		building->addFace(stand21[i]);
		building->addFace(stand22[i]);
	}
	stand1[1].setDefaultColor(1.0,1.0,1.0,1.0);
	double wallHeight=3.0, tableHeight=1.2;
	
	vector<Face> paredes;
	paredes.push_back(calculateFace(Vector2D(7.60,0), Vector2D(7.60,3.95), wallHeight));
	paredes.push_back(calculateFace(Vector2D(12.2,0), Vector2D(12.2,3.95), wallHeight));
	paredes.push_back(calculateFace(Vector2D(20.55,6.05), Vector2D(16.05,6.05), wallHeight));
	paredes.push_back(calculateFace(Vector2D(20.55,8.1), Vector2D(16.05,8.1), wallHeight));
	paredes.push_back(calculateFace(Vector2D(20.55,12.8), Vector2D(19.55,12.8), wallHeight));
	paredes.push_back(calculateFace(Vector2D(20.55,14.85), Vector2D(19.55,14.85), wallHeight));
	paredes.push_back(calculateFace(Vector2D(12.5,20), Vector2D(12.5,23.95), wallHeight));
	paredes.push_back(calculateFace(Vector2D(10,20), Vector2D(10,23.95), wallHeight));
	paredes.push_back(calculateFace(Vector2D(0,16.7), Vector2D(4.3,16.7), wallHeight));
	paredes.push_back(calculateFace(Vector2D(6.3,10.25), Vector2D(8.3,10.25), wallHeight));
	paredes.push_back(calculateFace(Vector2D(6.3,13.3), Vector2D(8.3,13.3), wallHeight));
	paredes.push_back(calculateFace(Vector2D(12.6,10.25), Vector2D(14.6,10.25), wallHeight));
	paredes.push_back(calculateFace(Vector2D(12.6,13.3), Vector2D(14.6,13.3), wallHeight));
	paredes.push_back(calculateFace(Vector2D(8.3,9.2), Vector2D(12.6,9.2), wallHeight));
	paredes.push_back(calculateFace(Vector2D(8.3,9.2), Vector2D(8.3,14.35), wallHeight));
	paredes.push_back(calculateFace(Vector2D(8.3,14.35), Vector2D(12.6,14.35), wallHeight));
	paredes.push_back(calculateFace(Vector2D(12.65,9.2), Vector2D(12.65,14.35), wallHeight));
	for(i=0;i<paredes.size();i++)
		building->addFace(paredes[i]);

	paredes[0].setDefaultColor((float)0.9, (float)0.9, (float)0.5, (float)0.5);
	vector<Face> mesa1,mesa2,mesa3,mesa4,mesa5,mesa6,mesa7,mesa8,mesa9,mesa10,mesa11,mesa12,mesa13,mesa14;
	double tableWidth=1.0, tableDeep=0.5;
	CreateBox(tableHeight, tableWidth, tableDeep, Vector2D(8.4,3.95-tableDeep), mesa1);
	CreateBox(tableHeight, tableWidth, tableDeep, Vector2D(12.5,3.95-tableDeep), mesa2);
	CreateBox(tableHeight, tableDeep, tableWidth, Vector2D(17.1,8-tableWidth), mesa3);
	CreateBox(tableHeight, tableWidth, tableDeep, Vector2D(17.1,9.6), mesa4);
	CreateBox(tableHeight, tableDeep, tableWidth, Vector2D(16.1,13.3), mesa5);
	CreateBox(tableHeight, tableWidth, tableDeep, Vector2D(15.45,20), mesa6);
	CreateBox(tableHeight, tableWidth, tableDeep, Vector2D(10,20), mesa7);
	CreateBox(tableHeight, tableDeep, tableWidth, Vector2D(6.05,22), mesa8);

	for(i=0;i<mesa1.size();i++)
	{
		building->addFace(mesa1[i]);
		building->addFace(mesa2[i]);
		building->addFace(mesa3[i]);
		building->addFace(mesa4[i]);
		building->addFace(mesa5[i]);
		building->addFace(mesa6[i]);
		building->addFace(mesa7[i]);
		building->addFace(mesa8[i]);
	}

	
	world+=building;
	StreamFile myfile(filename,false);
	myfile.write(&world);
}