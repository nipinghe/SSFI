/********************************************************************************************************
* File:              FoamSurface.cpp                                              
* Author:            hexiang6666                                 | Boris Jeremic,                       *
* Date:              2017-05-11 22:36:05                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-05-18 21:27:56                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#include <iostream>
#include <vector>
#include "FoamNode.h"
#include "FoamSurface.h"


// using namespace std;

	// public:
	// 	FoamSurface();
	// 	~FoamSurface();
	// 	FoamSurface(int ID);  //initia;ize with surface ID
	// 	FoamSurface(std::vector<int> node_ID);  //initialize with node ID vector consisting of the surface
	//  FoamSurface(int ID, std::vector<int> node_ID, std::map<int, FoamNode*>  foam_nodes);
	//  FoamSurface(std::vector<string> vs, std::map<int, FoamNode*>  foam_nodes);   // initializer for reading foam_faces.fei file and initialize foam_surfaces



	// 	void setSurfaceId(int ID);
	// 	void setSurfaceNodeId(std::vector<int> node_ID);
	// 	void setSurfacePressure(double p);
	// 	void setSurfaceVel(std::vector<double> vel);
	//  void setSurfaceCenterCoord(std::map<int, FoamNode*>  foam_nodes);


	// 	int getSurfaceId();
	// 	std::vector<int> getSurfaceNodeId();
	// 	double getSurfacePressure();
	// 	std::vector<double> getSurfaceVel();
	// 	int getNumSurfaceNode();
	// 	std::vector<double> getSurfaceCenterCoord();

	// 	void printSurface();

		
	// private:
	// 	int foam_surface_ID;  					    // the surface ID of fluid solid interface surface in fluid domain
	// 	std::vector<int> foam_surface_node_ID; 	    // the node id vector that consisting of the foam surface
	// 	double surface_pressure; 				    //surface pressure getting from Openfoam output
	// 	std::vector<double> surface_velocity;       //surface velocity of surface center point getting from ESSI output 
	// 	std::vector<double> surface_center_coord;	// the coordinate of surface center

FoamSurface::FoamSurface(){};
FoamSurface::~FoamSurface(){};
FoamSurface::FoamSurface(int ID):foam_surface_ID{ID}{};
FoamSurface::FoamSurface(std::vector<int> node_ID):foam_surface_node_ID{node_ID}{};

FoamSurface::FoamSurface(int ID,std::vector<int> node_ID,std::map<int, FoamNode*>  foam_nodes):foam_surface_ID{ID}
{

	foam_surface_node_ID=node_ID;
	setSurfaceCenterCoord(foam_nodes);
}


FoamSurface::FoamSurface(std::vector<string> vs, std::map<int, FoamNode*>  foam_nodes)
{
	foam_surface_ID=std::stoi(vs[0]);
	for (int i = 1; i < vs.size(); ++i)
	{
		foam_surface_node_ID.push_back(std::stoi(vs[i]));
	}
	setSurfaceCenterCoord(foam_nodes);
}



void FoamSurface::setSurfaceId(int ID)
{
	this->foam_surface_ID=ID;
}

void FoamSurface::setSurfaceNodeId(std::vector<int> node_ID)
{
	this->foam_surface_node_ID=node_ID;
}


void FoamSurface::setSurfacePressure(double p)
{
	this->surface_pressure=p;
}

void FoamSurface::setSurfaceVel(std::vector<double> vel)
{
	this->surface_velocity=vel;
}

void FoamSurface::setSurfaceCenterCoord(std::map<int, FoamNode*>  foam_nodes)
{
	surface_center_coord={0.0,0.0,0.0};

	int Numvertice=getNumSurfaceNode();

	for (int i = 0; i < Numvertice; ++i)
	{
		int NodeID=foam_surface_node_ID[i];
		FoamNode* node=foam_nodes[NodeID];
		surface_center_coord[0]=surface_center_coord[0]+(node->getNodeCoord())[0];
		surface_center_coord[1]=surface_center_coord[1]+(node->getNodeCoord())[1];
		surface_center_coord[2]=surface_center_coord[2]+(node->getNodeCoord())[2];
	}
	surface_center_coord[0]=surface_center_coord[0]/(1.0*Numvertice);
	surface_center_coord[1]=surface_center_coord[1]/(1.0*Numvertice);
	surface_center_coord[2]=surface_center_coord[2]/(1.0*Numvertice);

}

bool FoamSurface::IsFoamNodeContained(int node_ID)
{
	std::vector<int>::iterator it=find(foam_surface_node_ID.begin(), foam_surface_node_ID.end(), node_ID);
	if (it!=foam_surface_node_ID.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}


int FoamSurface::getSurfaceId()
{
	return this->foam_surface_ID;
}

std::vector<int> FoamSurface::getSurfaceNodeId()
{
	return this->foam_surface_node_ID;
}

double FoamSurface::getSurfacePressure()
{
	return this->surface_pressure;
}

std::vector<double> FoamSurface::getSurfaceVel()
{
	return this->surface_velocity;
}

int FoamSurface::getNumSurfaceNode()
{
	return (this->foam_surface_node_ID).size(); 
}

std::vector<double> FoamSurface::getSurfaceCenterCoord()
{
	return this->surface_center_coord;
}


void FoamSurface::printSurface()
{
	cout<<"Foam surface No: "<<foam_surface_ID<<" with nodes (";
	for (int i = 0; i < foam_surface_node_ID.size()-1; ++i)
	{
		cout<<std::to_string(foam_surface_node_ID[i])<<", ";
	}
	cout<<std::to_string(foam_surface_node_ID[foam_surface_node_ID.size()-1])<<")"<<" surface center at ("<<surface_center_coord[0]<<", "<<surface_center_coord[1]<<", "<<surface_center_coord[2]<<"). Surface pressure is "<<surface_pressure<<" Pa\n";
}