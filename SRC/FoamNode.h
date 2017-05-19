/********************************************************************************************************
* File:              FoamNode.h                                              
* Author:            hexiang6666                                 | Boris Jeremic,                       *
* Date:              2017-05-11 21:15:53                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-05-18 21:28:31                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#ifndef FOAM_NODE_H
#define FOAM_NODE_H

#include <iostream>
#include <vector>
#include <string> 

using namespace std;

class FoamNode
{
	public:
		FoamNode();
		~FoamNode();
		FoamNode(int ID);
		FoamNode(std::vector<string> vs);  // initializer used for reading foam_nodes.fei and initialize foam_nodes variable: first component is node ID, next three components are x,y,z coordinates

		void setNodeId(int ID);
		void setNodeCoord(std::vector<double> coord);
		void setNodePressure(double p);
		void setNodeDisp(std::vector<double> dis);
		void setNodeVel(std::vector<double> vel);
		int getNodeId();
		std::vector<double> getNodeCoord();
		double getNodePressure();
		std::vector<double> getNodeDisp();
		std::vector<double> getNodeVel();

		void printNode();

		
	private:
		int foam_node_ID;  						//solid fluid interface node ID in fluid model
		std::vector<double> foam_node_coord; 	//solid fluid interface node coordinate in fluid model
		double nodal_pressure=0;    				//solid fluid interface node pressure in fluid model
		std::vector<double> nodal_displacement; //solid fluid interface node displacement in fluid model
		std::vector<double> nodal_velocity;  	//solid fluid interface node velocity in fluid model

};

#endif