/********************************************************************************************************
* File:              ESSISurface.h                                              
* Author:            hexiang                                     | Boris Jeremic,                       *
* Date:              2017-05-12 10:11:41                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-05-17 22:48:55                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#ifndef ESSI_SURFACE_H
#define ESSI_SURFACE_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "ESSINode.h"

using namespace std;

class ESSISurface
{
	public:
		ESSISurface();
		~ESSISurface();
		ESSISurface(int ID);  					//initia;ize with surface ID
		ESSISurface(std::vector<int> node_ID);  //initialize with node ID vector consisting of the surface
		ESSISurface(std::vector<string> vs, std::map<int,ESSINode*> ESSI_nodes);   // initializer for reading surface_load_info.fei file and initialize ESSI_surfaces


		void setSurfaceId(int ID);
		void setSurfaceNodeId(std::vector<int> node_ID);
		void setSurfaceVerticeId();
		void setESSIVerticeCoord(std::map<int, ESSINode*> ESSI_nodes);
		void setLimit();

		int getSurfaceId();
		std::vector<int> getSurfaceNodeId();
		std::vector<int> getSurfaceVerticeId();
		int getNumSurfaceNode();
		std::vector<std::vector<double>> getESSIVerticeCoord();
		std::vector<double> getLimit();


		bool Is_foam_node_inside(std::vector<double> foam_center_coord);    // This function is to determine whether a foam_surface_center belong to this ESSI surface or not. 
		void printSurface();


	private:
		int ESSI_surface_ID;  					    // the surface ID of fluid solid interface surface in solid domain
		std::vector<int> ESSI_surface_node_ID; 	    // the node id vector that consisting of the ESSI surface
		std::vector<int> ESSI_surface_vertice_ID;   // the vertice id vector; the size is always 4.  
		std::vector<std::vector<double>> ESSI_vertice_coord;  	// the vertice coordinates: should be 4 element, each element has three components: x , y, z coordinate 
		std::vector<double> limit;					// limit has 6 elements: first two elements are the positive and negative limits of x coord and next two elements are positive and negative limits of y coord. The last two element are limits for z coord.  
};


#endif