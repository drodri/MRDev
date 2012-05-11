#include "mrcore/mrcore.h"

void CreateWorldEuitiLab(string filename)
{
	World world;
	//Intializing test environment Faces included in a FacePart
	//laboratorio
	Face suelo;
	suelo.setBase(Transformation3D(0,0,0));
	suelo.addVertex(0,0);
	suelo.addVertex(0,3.43);
	suelo.addVertex(-2.17,3.43);
	suelo.addVertex(-2.17,3.96);
	suelo.addVertex(-3.04,3.96);
	suelo.addVertex(-3.04,5.42);
	suelo.addVertex(-2.17,5.42);
	suelo.addVertex(-2.17,6.96);
	suelo.addVertex(-3.04,6.96);
	suelo.addVertex(-3.04,8.42);
	suelo.addVertex(-2.17,8.42);
	suelo.addVertex(-2.17,9.96);
	suelo.addVertex(-3.04,9.96);
	suelo.addVertex(-3.04,11.42);
	suelo.addVertex(-2.17,11.42);
	suelo.addVertex(-2.17,12.96);
	suelo.addVertex(-3.04,12.96);
	suelo.addVertex(-3.04,14.42);
	suelo.addVertex(-2.17,14.42);
	suelo.addVertex(-2.17,15.96);
	suelo.addVertex(-3.04,15.96);
	suelo.addVertex(-3.04,17.42);
	suelo.addVertex(-2.17,17.42);
	suelo.addVertex(-2.17,18.96);
	suelo.addVertex(-3.04,18.96);
	suelo.addVertex(-3.04,20.42);
	suelo.addVertex(-2.17,20.42);
	suelo.addVertex(-2.17,21.96);
	suelo.addVertex(-3.04,21.96);
	suelo.addVertex(-3.04,23.42);
	suelo.addVertex(-2.17,23.42);
	suelo.addVertex(-2.17,24.96);
	
	
	suelo.addVertex(4.99,24.96);
	suelo.addVertex(4.99,23.42);
	suelo.addVertex(5.86,23.42);
	suelo.addVertex(5.86,21.96);
	suelo.addVertex(4.99,21.96);
	suelo.addVertex(4.99,20.42);
	suelo.addVertex(5.86,20.42);
	suelo.addVertex(5.86,18.96);
	suelo.addVertex(4.99,18.96);
	suelo.addVertex(4.99,17.42);
	suelo.addVertex(5.86,17.42);
	suelo.addVertex(5.86,15.96);
	suelo.addVertex(4.99,15.96);
	suelo.addVertex(4.99,14.42);
	suelo.addVertex(5.86,14.42);
	suelo.addVertex(5.86,12.96);
	suelo.addVertex(4.99,12.96);
	suelo.addVertex(4.99,11.42);
	suelo.addVertex(5.86,11.42);
	suelo.addVertex(5.86,9.96);
	suelo.addVertex(4.99,9.96);
	suelo.addVertex(4.99,8.42);
	suelo.addVertex(5.86,8.42);
	suelo.addVertex(5.86,6.96);
	suelo.addVertex(4.99,6.96);
	suelo.addVertex(4.99,5.42);
	suelo.addVertex(5.86,5.42);
	suelo.addVertex(5.86,3.96);
	suelo.addVertex(4.99,3.96);
	suelo.addVertex(4.99,3.43);
	suelo.addVertex(2.82,3.43);
	suelo.addVertex(2.82,0.4);
	suelo.addVertex(2.2,0.4);
	suelo.addVertex(2.2,0);

	suelo.setColor(0.6, 0.4, 0.4, 1);
	
	Face puerta;
	Face::setDefaultColor(0.8,0.8,0.2,1);
	puerta.setBase(Transformation3D(0,0,0,X_AXIS,PI/2));
	puerta.addVertex(0,0);
	puerta.addVertex(0.67,0);
	puerta.addVertex(0.67,2);
	puerta.addVertex(2.1,2);
	puerta.addVertex(2.1,0);
	puerta.addVertex(2.2,0);
	puerta.addVertex(2.2,2.5);
	puerta.addVertex(0,2.5);
	
	Face pared1;
	pared1.setBase(Transformation3D(0,0,0,Y_AXIS,-PI/2));
	pared1.addVertex(0,0);
	pared1.addVertex(0,3.43);
	pared1.addVertex(2.5,3.43);
	pared1.addVertex(2.5,0);
	Face pared2;
	pared2.setBase(Transformation3D(2.2,0,0,Y_AXIS,-PI/2));
	pared2.addVertex(0,0);
	pared2.addVertex(0,0.4);
	pared2.addVertex(2.5,0.4);
	pared2.addVertex(2.5,0);
	Face pared3;
	pared3.setBase(Transformation3D(2.2,0.4,0,X_AXIS,PI/2));
	pared3.addVertex(0,0);
	pared3.addVertex(0.62,0);
	pared3.addVertex(0.62,2.5);
	pared3.addVertex(0,2.5);
	Face pared4;
	pared4.setBase(Transformation3D(2.82,0.4,0,Y_AXIS,-PI/2));
	pared4.addVertex(0,0);
	pared4.addVertex(0,3.03);
	pared4.addVertex(2.5,3.03);
	pared4.addVertex(2.5,0);
	
	Face pared1_s;
	pared1_s.setBase(Transformation3D(-2.17,3.43,0,X_AXIS,PI/2));
	pared1_s.addVertex(0,0);
	pared1_s.addVertex(2.17,0);
	pared1_s.addVertex(2.17,2.5);
	pared1_s.addVertex(0,2.5);
	Face pared2_s;
	pared2_s.setBase(Transformation3D(-2.17,3.43,0,Y_AXIS,-PI/2));
	pared2_s.addVertex(0,0);
	pared2_s.addVertex(0,0.53);
	pared2_s.addVertex(2.5,0.53);
	pared2_s.addVertex(2.5,0);
	
	Face pared3_s;
	pared3_s.setBase(Transformation3D(-3.04,3.96,0,X_AXIS,PI/2));
	pared3_s.addVertex(0,0);
	pared3_s.addVertex(0.85,0);
	pared3_s.addVertex(0.85,2.5);
	pared3_s.addVertex(0,2.5);
	Face pared4_s;
	pared4_s.setBase(Transformation3D(-3.04,3.96,0,Y_AXIS,-PI/2));
	pared4_s.addVertex(0,0);
	pared4_s.addVertex(0,1.46);
	pared4_s.addVertex(2.5,1.46);
	pared4_s.addVertex(2.5,0);
	
	Face pared5_s;
	pared5_s.setBase(Transformation3D(-3.04,5.42,0,X_AXIS,PI/2));
	pared5_s.addVertex(0,0);
	pared5_s.addVertex(0.85,0);
	pared5_s.addVertex(0.85,2.5);
	pared5_s.addVertex(0,2.5);
	Face pared6_s;
	pared6_s.setBase(Transformation3D(-2.17,5.42,0,Y_AXIS,-PI/2));
	pared6_s.addVertex(0,0);
	pared6_s.addVertex(0,1.54);
	pared6_s.addVertex(2.5,1.54);
	pared6_s.addVertex(2.5,0);
	
	Face pared7_s;
	pared7_s.setBase(Transformation3D(-3.04,6.96,0,X_AXIS,PI/2));
	pared7_s.addVertex(0,0);
	pared7_s.addVertex(0.85,0);
	pared7_s.addVertex(0.85,2.5);
	pared7_s.addVertex(0,2.5);
	Face pared8_s;
	pared8_s.setBase(Transformation3D(-3.04,6.96,0,Y_AXIS,-PI/2));
	pared8_s.addVertex(0,0);
	pared8_s.addVertex(0,1.46);
	pared8_s.addVertex(2.5,1.46);
	pared8_s.addVertex(2.5,0);
	
	Face pared9_s;
	pared9_s.setBase(Transformation3D(-3.04,8.42,0,X_AXIS,PI/2));
	pared9_s.addVertex(0,0);
	pared9_s.addVertex(0.85,0);
	pared9_s.addVertex(0.85,2.5);
	pared9_s.addVertex(0,2.5);
	Face pared10_s;
	pared10_s.setBase(Transformation3D(-2.17,8.42,0,Y_AXIS,-PI/2));
	pared10_s.addVertex(0,0);
	pared10_s.addVertex(0,1.54);
	pared10_s.addVertex(2.5,1.54);
	pared10_s.addVertex(2.5,0);
	
	Face pared11_s;
	pared11_s.setBase(Transformation3D(-3.04,9.96,0,X_AXIS,PI/2));
	pared11_s.addVertex(0,0);
	pared11_s.addVertex(0.85,0);
	pared11_s.addVertex(0.85,2.5);
	pared11_s.addVertex(0,2.5);
	Face pared12_s;
	pared12_s.setBase(Transformation3D(-3.04,9.96,0,Y_AXIS,-PI/2));
	pared12_s.addVertex(0,0);
	pared12_s.addVertex(0,1.46);
	pared12_s.addVertex(2.5,1.46);
	pared12_s.addVertex(2.5,0);
	
	Face pared13_s;
	pared13_s.setBase(Transformation3D(-3.04,11.42,0,X_AXIS,PI/2));
	pared13_s.addVertex(0,0);
	pared13_s.addVertex(0.85,0);
	pared13_s.addVertex(0.85,2.5);
	pared13_s.addVertex(0,2.5);
	Face pared14_s;
	pared14_s.setBase(Transformation3D(-2.17,11.42,0,Y_AXIS,-PI/2));
	pared14_s.addVertex(0,0);
	pared14_s.addVertex(0,1.54);
	pared14_s.addVertex(2.5,1.54);
	pared14_s.addVertex(2.5,0);
	
	Face pared15_s;
	pared15_s.setBase(Transformation3D(-3.04,12.96,0,X_AXIS,PI/2));
	pared15_s.addVertex(0,0);
	pared15_s.addVertex(0.85,0);
	pared15_s.addVertex(0.85,2.5);
	pared15_s.addVertex(0,2.5);
	Face pared16_s;
	pared16_s.setBase(Transformation3D(-3.04,12.96,0,Y_AXIS,-PI/2));
	pared16_s.addVertex(0,0);
	pared16_s.addVertex(0,1.46);
	pared16_s.addVertex(2.5,1.46);
	pared16_s.addVertex(2.5,0);
	
	Face pared17_s;
	pared17_s.setBase(Transformation3D(-3.04,14.42,0,X_AXIS,PI/2));
	pared17_s.addVertex(0,0);
	pared17_s.addVertex(0.85,0);
	pared17_s.addVertex(0.85,2.5);
	pared17_s.addVertex(0,2.5);
	Face pared18_s;
	pared18_s.setBase(Transformation3D(-2.17,14.42,0,Y_AXIS,-PI/2));
	pared18_s.addVertex(0,0);
	pared18_s.addVertex(0,1.54);
	pared18_s.addVertex(2.5,1.54);
	pared18_s.addVertex(2.5,0);
	
	Face pared19_s;
	pared19_s.setBase(Transformation3D(-3.04,15.96,0,X_AXIS,PI/2));
	pared19_s.addVertex(0,0);
	pared19_s.addVertex(0.85,0);
	pared19_s.addVertex(0.85,2.5);
	pared19_s.addVertex(0,2.5);
	Face pared20_s;
	pared20_s.setBase(Transformation3D(-3.04,15.96,0,Y_AXIS,-PI/2));
	pared20_s.addVertex(0,0);
	pared20_s.addVertex(0,1.46);
	pared20_s.addVertex(2.5,1.46);
	pared20_s.addVertex(2.5,0);
	
	Face pared21_s;
	pared21_s.setBase(Transformation3D(-3.04,17.42,0,X_AXIS,PI/2));
	pared21_s.addVertex(0,0);
	pared21_s.addVertex(0.85,0);
	pared21_s.addVertex(0.85,2.5);
	pared21_s.addVertex(0,2.5);
	Face pared22_s;
	pared22_s.setBase(Transformation3D(-2.17,17.42,0,Y_AXIS,-PI/2));
	pared22_s.addVertex(0,0);
	pared22_s.addVertex(0,1.54);
	pared22_s.addVertex(2.5,1.54);
	pared22_s.addVertex(2.5,0);
	
	Face pared23_s;
	pared23_s.setBase(Transformation3D(-3.04,18.96,0,X_AXIS,PI/2));
	pared23_s.addVertex(0,0);
	pared23_s.addVertex(0.85,0);
	pared23_s.addVertex(0.85,2.5);
	pared23_s.addVertex(0,2.5);
	Face pared24_s;
	pared24_s.setBase(Transformation3D(-3.04,18.96,0,Y_AXIS,-PI/2));
	pared24_s.addVertex(0,0);
	pared24_s.addVertex(0,1.46);
	pared24_s.addVertex(2.5,1.46);
	pared24_s.addVertex(2.5,0);
	
	Face pared25_s;
	pared25_s.setBase(Transformation3D(-3.04,20.42,0,X_AXIS,PI/2));
	pared25_s.addVertex(0,0);
	pared25_s.addVertex(0.85,0);
	pared25_s.addVertex(0.85,2.5);
	pared25_s.addVertex(0,2.5);
	Face pared26_s;
	pared26_s.setBase(Transformation3D(-2.17,20.42,0,Y_AXIS,-PI/2));
	pared26_s.addVertex(0,0);
	pared26_s.addVertex(0,1.54);
	pared26_s.addVertex(2.5,1.54);
	pared26_s.addVertex(2.5,0);
	
	Face pared27_s;
	pared27_s.setBase(Transformation3D(-3.04,21.96,0,X_AXIS,PI/2));
	pared27_s.addVertex(0,0);
	pared27_s.addVertex(0.85,0);
	pared27_s.addVertex(0.85,2.5);
	pared27_s.addVertex(0,2.5);
	Face pared28_s;
	pared28_s.setBase(Transformation3D(-3.04,21.96,0,Y_AXIS,-PI/2));
	pared28_s.addVertex(0,0);
	pared28_s.addVertex(0,1.46);
	pared28_s.addVertex(2.5,1.46);
	pared28_s.addVertex(2.5,0);
	
	Face pared29_s;
	pared29_s.setBase(Transformation3D(-3.04,23.42,0,X_AXIS,PI/2));
	pared29_s.addVertex(0,0);
	pared29_s.addVertex(0.85,0);
	pared29_s.addVertex(0.85,2.5);
	pared29_s.addVertex(0,2.5);
	Face pared30_s;
	pared30_s.setBase(Transformation3D(-2.17,23.42,0,Y_AXIS,-PI/2));
	pared30_s.addVertex(0,0);
	pared30_s.addVertex(0,1.54);
	pared30_s.addVertex(2.5,1.54);
	pared30_s.addVertex(2.5,0);
	
	Face pared31_s;
	pared31_s.setBase(Transformation3D(-2.17,24.96,0,X_AXIS,PI/2));
	pared31_s.addVertex(0,0);
	pared31_s.addVertex(3.58,0);
	pared31_s.addVertex(3.58,2.5);
	pared31_s.addVertex(0,2.5);
	
	Face::setDefaultColor(0.6,0.5,0.8,1);
	//Pasillo
	Face suelo_pasillo;
	suelo_pasillo.setBase(Transformation3D(0,0,0));
	suelo_pasillo.addVertex(0,0);
	suelo_pasillo.addVertex(0,-4.4);
	suelo_pasillo.addVertex(9.85,-4.4);
	suelo_pasillo.addVertex(9.85,-4.89);
	suelo_pasillo.addVertex(13.35,-4.89);
	suelo_pasillo.addVertex(13.35,-4.4);
	suelo_pasillo.addVertex(33.37,-4.4);
	suelo_pasillo.addVertex(33.37,-7.3);
	suelo_pasillo.addVertex(36.07,-7.3);
	suelo_pasillo.addVertex(36.07,-10);
	suelo_pasillo.addVertex(38.77,-10);
	suelo_pasillo.addVertex(38.77,-4.4);
	suelo_pasillo.addVertex(53.17,-4.4);
	suelo_pasillo.addVertex(53.17,0);
	
	Face suelo_pasillo2;
	suelo_pasillo2.setBase(Transformation3D(0,0,0.36));
	suelo_pasillo2.addVertex(-3.53,-0.21);
	suelo_pasillo2.addVertex(-4.5,-0.21);
	suelo_pasillo2.addVertex(-4.5,-3.98);
	suelo_pasillo2.addVertex(-3.53,-3.98);
	
	Face rampa1;
	rampa1.setBase(Transformation3D(0,0,0,Y_AXIS,0.099));
	rampa1.addVertex(0,0);
	rampa1.addVertex(-3,0);
	rampa1.addVertex(-3,-0.21);
	rampa1.addVertex(-3.53,-0.21);
	rampa1.addVertex(-3.53,-3.98);
	rampa1.addVertex(-3,-3.98);
	rampa1.addVertex(-3,-4.4);
	rampa1.addVertex(0,-4.4);
	
	Face::setDefaultColor(0.2,0.2,0.9,1);
	Face pared1_p;
	pared1_p.setBase(Transformation3D(2.2,0,0,X_AXIS,PI/2));
	pared1_p.addVertex(0,0);
	pared1_p.addVertex(50.97,0);
	pared1_p.addVertex(50.97,2.5);
	pared1_p.addVertex(0,2.5);
	
	Face pared2_p;
	pared2_p.setBase(Transformation3D(53.07,-4.4,0,Y_AXIS,-PI/2));
	pared2_p.addVertex(0,0);
	pared2_p.addVertex(2.5,0);
	pared2_p.addVertex(2.5,4.4);
	pared2_p.addVertex(0,4.4);
	
	Face pared3_p;
	pared3_p.setBase(Transformation3D(38.77,-4.4,0,X_AXIS,PI/2));
	pared3_p.addVertex(0,0);
	pared3_p.addVertex(14.4,0);
	pared3_p.addVertex(14.4,2.5);
	pared3_p.addVertex(0,2.5);
	
	Face pared4_p;
	pared4_p.setBase(Transformation3D(38.77,-10,0,Y_AXIS,-PI/2));
	pared4_p.addVertex(0,0);
	pared4_p.addVertex(2.5,0);
	pared4_p.addVertex(2.5,5.6);
	pared4_p.addVertex(0,5.6);
	
	Face pared5_p;
	pared5_p.setBase(Transformation3D(36.07,-10,0,X_AXIS,PI/2));
	pared5_p.addVertex(0,0);
	pared5_p.addVertex(2.7,0);
	pared5_p.addVertex(2.7,2.5);
	pared5_p.addVertex(0,2.5);
	
	Face pared6_p;
	pared6_p.setBase(Transformation3D(36.07,-10,0,Y_AXIS,-PI/2));
	pared6_p.addVertex(0,0);
	pared6_p.addVertex(2.5,0);
	pared6_p.addVertex(2.5,2.7);
	pared6_p.addVertex(0,2.7);
	
	Face pared7_p;
	pared7_p.setBase(Transformation3D(33.37,-7.3,0,X_AXIS,PI/2));
	pared7_p.addVertex(0,0);
	pared7_p.addVertex(2.7,0);
	pared7_p.addVertex(2.7,2.5);
	pared7_p.addVertex(0,2.5);
	
	Face pared8_p;
	pared8_p.setBase(Transformation3D(33.37,-7.3,0,Y_AXIS,-PI/2));
	pared8_p.addVertex(0,0);
	pared8_p.addVertex(2.5,0);
	pared8_p.addVertex(2.5,2.9);
	pared8_p.addVertex(0,2.9);
	
	Face pared9_p;
	pared9_p.setBase(Transformation3D(13.35,-4.4,0,X_AXIS,PI/2));
	pared9_p.addVertex(0,0);
	pared9_p.addVertex(20.02,0);
	pared9_p.addVertex(20.02,2.5);
	pared9_p.addVertex(0,2.5);
	
	Face pared10_p;
	pared10_p.setBase(Transformation3D(13.35,-4.89,0,Y_AXIS,-PI/2));
	pared10_p.addVertex(0,0);
	pared10_p.addVertex(2.5,0);
	pared10_p.addVertex(2.5,0.49);
	pared10_p.addVertex(0,0.49);
	
	Face pared11_p;
	pared11_p.setBase(Transformation3D(9.85,-4.89,0,X_AXIS,PI/2));
	pared11_p.addVertex(0,0);
	pared11_p.addVertex(3.5,0);
	pared11_p.addVertex(3.5,2.5);
	pared11_p.addVertex(0,2.5);
	
	Face pared12_p;
	pared12_p.setBase(Transformation3D(9.85,-4.89,0,Y_AXIS,-PI/2));
	pared12_p.addVertex(0,0);
	pared12_p.addVertex(2.5,0);
	pared12_p.addVertex(2.5,0.49);
	pared12_p.addVertex(0,0.49);
	
	Face pared13_p;
	pared13_p.setBase(Transformation3D(0,-4.4,0,X_AXIS,PI/2));
	pared13_p.addVertex(0,0);
	pared13_p.addVertex(9.85,0);
	pared13_p.addVertex(9.85,2.5);
	pared13_p.addVertex(0,2.5);
	
	Face pared14_p;
	pared14_p.setBase(Transformation3D(0,-4.4,0,Y_AXIS,PI+0.099)*Transformation3D(0,0,0,X_AXIS,-PI/2));
	pared14_p.addVertex(0,0);
	pared14_p.addVertex(3,0);
	pared14_p.addVertex(3,2.5);
	pared14_p.addVertex(0.215,2.5);
	
	Face pared15_p;
	pared15_p.setBase(Transformation3D(0,0,0,Y_AXIS,PI+0.099)*Transformation3D(0,0,0,X_AXIS,-PI/2));
	pared15_p.addVertex(0,0);
	pared15_p.addVertex(3,0);
	pared15_p.addVertex(3,2.5);
	pared15_p.addVertex(0.215,2.5);
	
	Face pared16_p;
	pared16_p.setBase(Transformation3D(-3,-4.4,0.3,Y_AXIS,PI+0.099)*Transformation3D(0,0,0,Y_AXIS,PI/2));
	pared16_p.addVertex(0,0);
	pared16_p.addVertex(2.5,0);
	pared16_p.addVertex(2.5,0.42);
	pared16_p.addVertex(0,0.42);
	
	Face pared17_p;
	pared17_p.setBase(Transformation3D(-3,-0.21,0.3,Y_AXIS,PI+0.099)*Transformation3D(0,0,0,Y_AXIS,PI/2));
	pared17_p.addVertex(0,0);
	pared17_p.addVertex(2.5,0);
	pared17_p.addVertex(2.5,0.21);
	pared17_p.addVertex(0,0.21);
	
	Face pared18_p;
	pared18_p.setBase(Transformation3D(-3,-0.21,0.3,Y_AXIS,PI+0.099)*Transformation3D(0,0,0,X_AXIS,-PI/2));
	pared18_p.addVertex(0,0);
	pared18_p.addVertex(0,2.5);
	pared18_p.addVertex(0.53,2.5);
	pared18_p.addVertex(0.53,0);
	
	Face pared19_p;
	pared19_p.setBase(Transformation3D(-3,-4.4,0.3,Y_AXIS,PI+0.099)*Transformation3D(0,0,0,X_AXIS,-PI/2));
	pared18_p.addVertex(0,0);
	pared18_p.addVertex(0,2.5);
	pared18_p.addVertex(0.53,2.5);
	pared18_p.addVertex(0.53,0);
	
	Face pared20_p;
	pared20_p.setBase(Transformation3D(-3,-3.98,0.3,Y_AXIS,PI+0.099)*Transformation3D(0,0,0,X_AXIS,-PI/2));
	pared20_p.addVertex(0,0);
	pared20_p.addVertex(0.53,0);
	pared20_p.addVertex(0.53,2.5);
	pared20_p.addVertex(0,2.5);	
	
	Face pared21_p;
	pared21_p.setBase(Transformation3D(-4.5,-3.98,0.36,X_AXIS,PI/2));
	pared21_p.addVertex(0,0);
	pared21_p.addVertex(0,2.5);
	pared21_p.addVertex(1.245,2.5);
	pared21_p.addVertex(1.03,0);
	
	Face pared22_p;
	pared22_p.setBase(Transformation3D(-4.5,-0.21,0.36,X_AXIS,PI/2));
	pared22_p.addVertex(0,0);
	pared22_p.addVertex(0,2.5);
	pared22_p.addVertex(1.245,2.5);
	pared22_p.addVertex(1.03,0);		
	
	Face pared23_p;
	pared23_p.setBase(Transformation3D(-4.5,-3.98,0.36,Y_AXIS,-PI/2));
	pared23_p.addVertex(0,0);
	pared23_p.addVertex(2.5,0);
	pared23_p.addVertex(2.5,3.77);
	pared23_p.addVertex(0,3.77);	
	
	FaceSetPart *building=new FaceSetPart,*building_s=new FaceSetPart; 
	building->addFace(suelo);
	building->addFace(puerta);
	building->addFace(pared1);
	building->addFace(pared2);
	building->addFace(pared3);
	building->addFace(pared4);
	building->addFace(suelo_pasillo);
	building->addFace(suelo_pasillo2);
	building->addFace(pared1_p);
	building->addFace(pared2_p);
	building->addFace(pared3_p);
	building->addFace(pared4_p);
	building->addFace(pared5_p);
	building->addFace(pared6_p);
	building->addFace(pared7_p);
	building->addFace(pared8_p);
	building->addFace(pared9_p);
	building->addFace(pared10_p);
	building->addFace(pared11_p);
	building->addFace(pared12_p);
	building->addFace(pared13_p);
	building->addFace(pared14_p);
	building->addFace(pared15_p);
	building->addFace(pared16_p);
	building->addFace(pared17_p);
	building->addFace(pared18_p);
	building->addFace(pared19_p);
	building->addFace(pared20_p);
	building->addFace(pared21_p);
	building->addFace(pared22_p);
	building->addFace(pared23_p);
	building->addFace(rampa1);
	world+=building;
	
	building_s->addFace(pared1_s);
	building_s->addFace(pared2_s);
	building_s->addFace(pared3_s);
	building_s->addFace(pared4_s);
	building_s->addFace(pared5_s);
	building_s->addFace(pared6_s);
	building_s->addFace(pared7_s);
	building_s->addFace(pared8_s);
	building_s->addFace(pared9_s);
	building_s->addFace(pared10_s);
	building_s->addFace(pared11_s);
	building_s->addFace(pared12_s);
	building_s->addFace(pared13_s);
	building_s->addFace(pared14_s);
	building_s->addFace(pared15_s);
	building_s->addFace(pared16_s);
	building_s->addFace(pared17_s);
	building_s->addFace(pared18_s);
	building_s->addFace(pared19_s);
	building_s->addFace(pared20_s);
	building_s->addFace(pared21_s);
	building_s->addFace(pared22_s);
	building_s->addFace(pared23_s);
	building_s->addFace(pared24_s);
	building_s->addFace(pared25_s);
	building_s->addFace(pared26_s);
	building_s->addFace(pared27_s);
	building_s->addFace(pared28_s);
	building_s->addFace(pared29_s);
	building_s->addFace(pared30_s);
	building_s->addFace(pared31_s);
	world+=building_s;

	//The symmetric part of the robot lab
	FaceSetPart *paux2=new FaceSetPart(*building_s);
	paux2->setRelativeOrientation(0,PI,0);
	paux2->setRelativePosition(Vector3D(2.83,0,2.5));
	world+=paux2;
	
	StreamFile myfile(filename,false);
	myfile.write(&world);
}