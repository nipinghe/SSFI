/********************************************************************************************************
* File:              ESSINode.cpp                                              
* Author:            hexiang6666                                     | Boris Jeremic,                       *
* Date:              2017-05-12 10:11:26                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-05-17 22:34:06                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#include <iostream>
#include <iostream>
#include "ESSINode.h"
#include <string> 

using namespace std;

ESSINode::ESSINode(){};
ESSINode::~ESSINode(){};

ESSINode::ESSINode(int ID):ESSI_node_ID{ID}{};

ESSINode::ESSINode(std::vector<string> vs) // initializer used for reading ESSI_nodes.fei and initialize essi_nodes variable: first component is node ID, next three components are x,y,z coordinates
{
	ESSI_node_ID=std::stoi(vs[0]);
	ESSI_node_coord.push_back(std::stod(vs[1]));
	ESSI_node_coord.push_back(std::stod(vs[2]));
	ESSI_node_coord.push_back(std::stod(vs[3]));
}

void ESSINode::setNodeId(int ID)
{
	this->ESSI_node_ID=ID;
}

void ESSINode::setNodeCoord(std::vector<double> coord)
{
	this->ESSI_node_coord=coord;
}

void ESSINode::setNodePressure(double p)
{
	this->nodal_pressure=p;
}

void ESSINode::setNodeDisp(std::vector<double> dis)
{
	this->nodal_displacement=dis;
}

void ESSINode::setNodeVel(std::vector<double> vel)
{
	this->nodal_velocity=vel;
}

int ESSINode::getNodeId()
{
	return this->ESSI_node_ID;
}

std::vector<double> ESSINode::getNodeCoord()
{
	return this->ESSI_node_coord;
}

double ESSINode::getNodePressure()
{
	return this->nodal_pressure;
}

std::vector<double> ESSINode::getNodeVel()
{
	return this->nodal_velocity;
}

std::vector<double> ESSINode::getNodeDisp()
{
	return this->nodal_displacement;
}


void ESSINode::printNode()
{
	cout<<"ESSI node No: "<<ESSI_node_ID<<" at ("<<ESSI_node_coord[0]<<", "<<ESSI_node_coord[1]<<", "<<ESSI_node_coord[2]<<"), nodal pressure is "<<nodal_pressure<<" Pa\n";
}
