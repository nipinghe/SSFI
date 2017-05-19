/********************************************************************************************************
* File:              FoamNode.cpp                                              
* Author:            hexiang6666                                     | Boris Jeremic,                       *
* Date:              2017-05-11 21:28:51                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-05-18 21:29:19                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/




	// public:
	// 	FoamNode();
	// 	~FoamNode();
	// 	FoamNode(int ID);
	//	FoamNode(std::vector<string> vs);  // initializer used for reading foam_nodes.fei and initialize foam_nodes variable: first component is node ID, next three components are x,y,z coordinates
	// 	void setNodeId(int ID);
	// 	void setNodeCoord(std::vector<double> coord);
	// 	void setNodePressure(double p);
	// 	void setNodeDisp(std::vector<double> dis);
	// 	void setNodeVel(std::vector<double> vel);
	// 	int getNodeId();
	// 	std::vector<double> getNodeCoord();
	// 	double getNodePressure();
	// 	std::vector<double> getNodeDisp();
	// 	std::vector<double> getNodeVel();

	// void printNode();

	// private:
	// 	int foam_node_ID;  						//solid fluid interface node ID in fluid model
	// 	std::vector<double> foam_node_coord; 	//solid fluid interface node coordinate in fluid model
	// 	double nodal_pressure;    				//solid fluid interface node pressure in fluid model
	// 	std::vector<double> nodal_displacement; //solid fluid interface node displacement in fluid model
	// 	std::vector<double> nodal_velocity;  	//solid fluid interface node velocity in fluid model



#include <iostream>
#include "FoamNode.h"
#include <string> 

using namespace std;

FoamNode::FoamNode(){};
FoamNode::~FoamNode(){};
FoamNode::FoamNode(int ID):foam_node_ID{ID}{};

FoamNode::FoamNode(std::vector<string> vs) // initializer used for reading foam_nodes.fei and initialize foam_nodes variable: first component is node ID, next three components are x,y,z coordinates
{
	foam_node_ID=std::stoi(vs[0]);
	foam_node_coord.push_back(std::stod(vs[1]));
	foam_node_coord.push_back(std::stod(vs[2]));
	foam_node_coord.push_back(std::stod(vs[3]));
}


void FoamNode::setNodeId(int ID)
{
	this->foam_node_ID=ID;
}

void FoamNode::setNodeCoord(std::vector<double> coord)
{
	this->foam_node_coord=coord;
}

void FoamNode::setNodePressure(double p)
{
	this->nodal_pressure=p;
}

void FoamNode::setNodeDisp(std::vector<double> dis)
{
	this->nodal_displacement=dis;
}

void FoamNode::setNodeVel(std::vector<double> vel)
{
	this->nodal_velocity=vel;
}

int FoamNode::getNodeId()
{
	return this->foam_node_ID;
}

std::vector<double> FoamNode::getNodeCoord()
{
	return this->foam_node_coord;
}

double FoamNode::getNodePressure()
{
	return this->nodal_pressure;
}

std::vector<double> FoamNode::getNodeVel()
{
	return this->nodal_velocity;
}

std::vector<double> FoamNode::getNodeDisp()
{
	return this->nodal_displacement;
}


void FoamNode::printNode()
{
	cout<<"Foam node No: "<<foam_node_ID<<" at ("<<foam_node_coord[0]<<", "<<foam_node_coord[1]<<", "<<foam_node_coord[2]<<") with nodal pressure "<<nodal_pressure<<" Pa;\n";
}
