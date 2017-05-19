/********************************************************************************************************
* File:              ESSINode.h                                              
* Author:            hexiang6666                                     | Boris Jeremic,                       *
* Date:              2017-05-12 10:11:06                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-05-17 22:33:29                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#ifndef ESSI_NODE_H
#define ESSI_NODE_H

#include <iostream>
#include <vector>

using namespace std;

class ESSINode
{
	public:
		ESSINode();
		~ESSINode();
		ESSINode(int ID);
		ESSINode(std::vector<string> vs); 

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
		int ESSI_node_ID;  						//solid fluid interface node ID in solid model
		std::vector<double> ESSI_node_coord; 	//solid fluid interface node coordinate in solid model
		double nodal_pressure=0;    			//solid fluid interface node pressure in solid model
		std::vector<double> nodal_displacement; //solid fluid interface node displacement in solid model
		std::vector<double> nodal_velocity;  	//solid fluid interface node velocity in solid model



};

#endif