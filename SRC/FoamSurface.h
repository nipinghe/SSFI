/********************************************************************************************************
* File:              FoamSurface.h                                              
* Author:            hexiang6666                                     | Boris Jeremic,                       *
* Date:              2017-05-11 22:36:15                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-05-18 21:25:51                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#ifndef FOAM_SURFACE_H
#define FOAM_SURFACE_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm> 
#include "FoamNode.h"

// using namespace std;

class FoamSurface
{
	public:
		FoamSurface();
		~FoamSurface();
		FoamSurface(int ID);  					//initia;ize with surface ID
		FoamSurface(std::vector<int> node_ID);  //initialize with node ID vector consisting of the surface
		FoamSurface(int ID, std::vector<int> node_ID, std::map<int,FoamNode*>  foam_nodes);
		FoamSurface(std::vector<string> vs, std::map<int, FoamNode*>  foam_nodes);   // initializer for reading foam_faces.fei file and initialize foam_surfaces



		void setSurfaceId(int ID);
		void setSurfaceNodeId(std::vector<int> node_ID);
		void setSurfacePressure(double p);
		void setSurfaceVel(std::vector<double> vel);
		void setSurfaceCenterCoord(std::map<int, FoamNode*>  foam_nodes);

		int getSurfaceId();
		std::vector<int> getSurfaceNodeId();
		double getSurfacePressure();
		std::vector<double> getSurfaceVel();
		int getNumSurfaceNode();
		std::vector<double> getSurfaceCenterCoord();

		bool IsFoamNodeContained(int node_ID);



		void printSurface();


	private:
		int foam_surface_ID;  					    // the surface ID of fluid solid interface surface in fluid domain
		std::vector<int> foam_surface_node_ID; 	    // the node id vector that consisting of the foam surface
		double surface_pressure=0; 				    //surface pressure getting from Openfoam output
		std::vector<double> surface_velocity;       //surface velocity of surface center point getting from ESSI output 
		std::vector<double> surface_center_coord;	// the coordinate of surface center
};

#endif