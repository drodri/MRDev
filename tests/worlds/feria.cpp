#include "mrcore/mrcore.h"
void CreateBox(double height, double width, double deep, Vector2D origin, vector<Face>& box)
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

	box[0].setColor(0.5,0.5,0.5,1);
	box[1].setColor(0.5,0.5,0.5,1);
	box[2].setColor(0.5,0.5,0.5,1);
	box[3].setColor(0.5,0.5,0.5,1);
	box[4].setColor(0.5,0.5,0.5,1);
}

void CreateWorldFeria(string filename)
{
	unsigned int i=0;
	World world;
	FaceSetPart *building=new FaceSetPart;
	double height=5.0, width=30.0, deep=25.0;
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
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(5,5), column1);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(10,5), column2);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(15,5), column3);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(20,5), column4);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(20,10), column5);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(20,20), column6);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(20,25), column7);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(15,25), column8);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(10,25), column9);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(5,25), column10);
	CreateBox(columnHeight, columnWidth, columnDeep, Vector2D(5,20), column11);
	
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
	//Altura imaginaria de los stands
	double standHeight=0.1;
	vector<Face> stand1,stand2,stand3,stand4,stand5,stand6,stand7,stand8,stand9,stand10,stand12,
				 stand13,stand14,stand16,stand17,stand18,stand19,stand20,stand21,stand22;
	CreateBox(standHeight,4.0,2.5,Vector2D(7,18),stand1);
	CreateBox(standHeight,4.0,2.5,Vector2D(7,14),stand2);
	CreateBox(standHeight,4.0,2.5,Vector2D(7,10),stand3);
	CreateBox(standHeight,2.5,4.0,Vector2D(9.5,10),stand4);
	CreateBox(standHeight,4.0,2.5,Vector2D(13.5,18),stand5);
	CreateBox(standHeight,4.0,2.5,Vector2D(13.5,14),stand6);
	CreateBox(standHeight,4.0,2.5,Vector2D(13.5,10),stand7);
	CreateBox(standHeight,2.5,4.0,Vector2D(9.5,19.5),stand8);
	CreateBox(standHeight,2.5,4.0,Vector2D(0,20),stand9);
	CreateBox(standHeight,2.5,4.0,Vector2D(0,22.5),stand10);
	CreateBox(standHeight,4.0,4.0,Vector2D(8.5,26),stand12);
	CreateBox(standHeight,4.0,2.5,Vector2D(12.5,26),stand13);
	CreateBox(standHeight,4.0,4.0,Vector2D(15,26),stand14);
	CreateBox(standHeight,4.0,4.0,Vector2D(21,15),stand16);
	CreateBox(standHeight,2.5,4.0,Vector2D(21,10),stand17);
	CreateBox(standHeight,2.5,4.0,Vector2D(21,7.5),stand18);
	CreateBox(standHeight,2.5,4.0,Vector2D(21,5),stand19);
	CreateBox(standHeight,4.0,2.5,Vector2D(15,0),stand20);
	CreateBox(standHeight,4.0,6.0,Vector2D(9,0),stand21);
	CreateBox(standHeight,4.0,4.0,Vector2D(5,0),stand22);

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
	
	world+=building;
	StreamFile myfile(filename,false);
	myfile.write(&world);
}