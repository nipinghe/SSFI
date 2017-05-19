/********************************************************************************************************
* File:              ESSISurface.cpp                                              
* Author:            hexiang                                     | Boris Jeremic,                       *
* Date:              2017-05-12 10:11:55                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-05-17 22:56:24                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#include <iostream>
#include <vector>
#include "ESSINode.h"
#include "ESSISurface.h"
#include <algorithm> 


using namespace std;

	// public:
	// 	ESSISurface();
	// 	~ESSISurface();
	// 	ESSISurface(int ID);  					//initia;ize with surface ID
	// 	ESSISurface(std::vector<int> node_ID);  //initialize with node ID vector consisting of the surface


	// 	ESSISurface(std::vector<string> vs, std::map<int, ESSINode*>  ESSI_nodes);   // initializer for reading surface_load_info.fei file and initialize ESSI_surfaces



	// 	void setSurfaceId(int ID);
	// 	void setSurfaceNodeId(std::vector<int> node_ID);
	// 	void setSurfaceVerticeId();
	//	void setESSIVerticeCoord(std::map<int, ESSINode*> ESSI_nodes);

	// 	int getSurfaceId();
	// 	std::vector<int> getSurfaceNodeId();
	// 	std::vector<int> getSurfaceVerticeId();
	// 	int getNumSurfaceNode();
	//	std::vector<std::vector<double>> getESSIVerticeCoord();


	// 	void printSurface();


	// private:
	// 	int ESSI_surface_ID;  					    // the surface ID of fluid solid interface surface in solid domain
	// 	std::vector<int> ESSI_surface_node_ID; 	    // the node id vector that consisting of the ESSI surface
	// 	std::vector<int> ESSI_surface_vertice_ID;   // the vertice id vector; the size is always 4.  
	//	std::vector<std::vector<double>> ESSI_vertice_coord;  	// the vertice coordinates: should be 4 element, each element has three components: x , y, z coordinate 



ESSISurface::ESSISurface(){};
ESSISurface::~ESSISurface(){};
ESSISurface::ESSISurface(int ID):ESSI_surface_ID{ID}{};
ESSISurface::ESSISurface(std::vector<int> node_ID):ESSI_surface_node_ID{node_ID}{};



ESSISurface::ESSISurface(std::vector<string> vs, std::map<int, ESSINode*>  ESSI_nodes)   // initializer for reading surface_load_info.fei file and initialize ESSI_surfaces
{
	ESSI_surface_ID=std::stoi(vs[0]);
	ESSI_surface_node_ID.clear();
	ESSI_surface_node_ID.push_back(std::stoi(vs[2]));
	ESSI_surface_node_ID.push_back(std::stoi(vs[3]));
	ESSI_surface_node_ID.push_back(std::stoi(vs[4]));
	ESSI_surface_node_ID.push_back(std::stoi(vs[5]));
	setSurfaceVerticeId();
	setESSIVerticeCoord(ESSI_nodes);
	setLimit();
}


void ESSISurface::setSurfaceId(int ID)
{
	this->ESSI_surface_ID=ID;
}

void ESSISurface::setSurfaceNodeId(std::vector<int> node_ID)
{
	this->ESSI_surface_node_ID=node_ID;
}

void ESSISurface::setSurfaceVerticeId()
{
	ESSI_surface_vertice_ID.clear();
	ESSI_surface_vertice_ID.push_back(ESSI_surface_node_ID[0]);
	ESSI_surface_vertice_ID.push_back(ESSI_surface_node_ID[1]);
	ESSI_surface_vertice_ID.push_back(ESSI_surface_node_ID[2]);
	ESSI_surface_vertice_ID.push_back(ESSI_surface_node_ID[3]);
}

void ESSISurface::setESSIVerticeCoord(std::map<int, ESSINode*> ESSI_nodes)
{
	ESSI_vertice_coord.clear();

	for (int i = 0; i < ESSI_surface_vertice_ID.size(); ++i)
	{
		int vertice_ID=ESSI_surface_vertice_ID[i];
		std::vector<double> vertice_coord=(ESSI_nodes[vertice_ID])->getNodeCoord();
		ESSI_vertice_coord.push_back(vertice_coord);
	}
}


void ESSISurface::setLimit()
{
	limit.clear();

	double x_pos=ESSI_vertice_coord[0][0];
	double x_neg=ESSI_vertice_coord[0][0];
	double y_pos=ESSI_vertice_coord[0][1];
	double y_neg=ESSI_vertice_coord[0][1];
	double z_pos=ESSI_vertice_coord[0][2];
	double z_neg=ESSI_vertice_coord[0][2];

	for (int i = 1; i < ESSI_vertice_coord.size(); ++i)
	{
		if (ESSI_vertice_coord[i][0]>x_pos)
		{
			x_pos=ESSI_vertice_coord[i][0];
		}
		if (ESSI_vertice_coord[i][0]<x_neg)
		{
			x_neg=ESSI_vertice_coord[i][0];
		}
		if (ESSI_vertice_coord[i][1]>y_pos)
		{
			y_pos=ESSI_vertice_coord[i][1];
		}
		if (ESSI_vertice_coord[i][1]<y_neg)
		{
			y_neg=ESSI_vertice_coord[i][1];
		}
		if (ESSI_vertice_coord[i][2]>z_pos)
		{
			z_pos=ESSI_vertice_coord[i][2];
		}
		if (ESSI_vertice_coord[i][2]<z_neg)
		{
			z_neg=ESSI_vertice_coord[i][2];
		}
	}

	limit.push_back(x_pos);
	limit.push_back(x_neg);
	limit.push_back(y_pos);
	limit.push_back(y_neg);
	limit.push_back(z_pos);
	limit.push_back(z_neg);

}


int ESSISurface::getSurfaceId()
{
	return this->ESSI_surface_ID;
}

std::vector<int> ESSISurface::getSurfaceNodeId()
{
	return this->ESSI_surface_node_ID;
}

std::vector<int> ESSISurface::getSurfaceVerticeId()
{
	return this->ESSI_surface_vertice_ID;
}

int ESSISurface::getNumSurfaceNode()
{
	return (this->ESSI_surface_node_ID).size(); 
}


std::vector<std::vector<double>> ESSISurface::getESSIVerticeCoord()
{
	return this->ESSI_vertice_coord;
}


void ESSISurface::printSurface()
{
	cout<<"ESSI surface No: "<<ESSI_surface_ID<<" with nodes (";
	for (int i = 0; i < ESSI_surface_node_ID.size()-1; ++i)
	{
		cout<<std::to_string(ESSI_surface_node_ID[i])<<", ";
	}
	cout<<std::to_string(ESSI_surface_node_ID[ESSI_surface_node_ID.size()-1])<<") \n";
}


std::vector<double> ESSISurface::getLimit()
{
	return limit;	
}


bool ESSISurface::Is_foam_node_inside(std::vector<double> foam_center_coord)
{
	if ( (foam_center_coord[0]>=limit[1]) && (foam_center_coord[0]<=limit[0]) && (foam_center_coord[1]<=limit[2]) && (foam_center_coord[1]>=limit[3]) && (foam_center_coord[2]<=limit[4]) && (foam_center_coord[2]>=limit[5]) )
		return true;
	else
		return false;
}