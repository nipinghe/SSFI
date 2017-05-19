/********************************************************************************************************
* File:              SSFI.h                                              
* Author:            hexiang                                     | Boris Jeremic,                       *
* Date:              2017-03-14 18:19:09                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-05-17 23:48:53                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#ifndef SSFI_H
#define SSFI_H 

#include <iostream>
#include <vector>
#include "FoamNode.h"
#include "FoamSurface.h"
#include "ESSINode.h"
#include "ESSISurface.h"
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include "string_operator.h"
#include <cstddef>
#include <math.h> 
#include <sstream>
#include <fstream>
#include <streambuf>


#ifdef _WIN32 
    #include <direct.h>
    #define GetCurrentDir _getcwd
    #define slash "\\"
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
	#define slash "/"
#endif

#ifndef OPENFOAM_INFO_FILE_NAME
	#define OPENFOAM_INFO_FILE_NAME
	#define foam_nodes_file "foam_nodes.fei"
	#define foam_surfaces_file "foam_faces.fei"
	#define ESSI_nodes_file "ESSI_nodes.fei"
	#define ESSI_surface_load_info_file "surface_load_info.fei"
	#define ModelName "box"   // just temporary for outside debug 
#endif


using namespace std;


class SSFI    													// SSFI like a broker do data transfermation, geometry mapping, data interpolation between ESSI interface surface and Foam interface surface
{
	public:
		SSFI();
		~SSFI();
		SSFI(double t);
		void setFoamNodes();
		void setFoamSurfaces();
		void setESSINodes();
		void setESSISurfaces();
		void setTime(double t);
		void setTolerance(double r);

		std::map<int, FoamNode*> getFoamNodes();
		std::map<int, FoamSurface*> getFoamSurfaces();
		std::map<int, ESSINode*> getESSINodes();
		std::map<int, ESSISurface*> getESSISurfaces(); 
		FoamNode* getFoamNode(int foam_node_ID);
		FoamSurface* getFoamSurface(int foam_surface_ID);
		ESSINode* getESSINode(int ESSI_node_ID);
		ESSISurface* getESSISurface(int ESSI_surface_ID);

		std::map<int, std::vector<int>> getFoamNodeToFoamSurfacesMapping();
		std::map<int, std::vector<int>> getESSINodeToFoamNodesMapping();
		std::map<int, std::vector<int>> getFoamSurfaceToESSINodesMapping();

		double getTime();
		
		std::map<int, int> FoamInterfaceIDInfo(); 					//This will return map contains the startFace ID (first element in the map) and number of faces (second element in the map) in each solid-fluid interface. Inside each interface the surface_ID is consecutive. 
		std::vector<double> readFoamSurfacePressure();              //From Openfoam output file to read current interface pressure in fluid domain.

		void FoamNodeMapToFoamSurfaces(); 							//build the FoamNode to FoamSurfaces map: the first element of the map is the Foam Node ID. second element of the map is a vector has all IDs of Foam surfaces that contain this node. 
		void ESSINodeMapToFoamNodes();								//build the ESSINode to FoamNodes map: the first element of the mapp is the ESSI Node ID. second element of the map is a vector has all IDs of Foam Nodes that surrounds the ESSI node within a sphere of radius tolerance. 					
		void FoamSurfaceMapToESSINodes(); 							// Foam surface center located at certain ESSI surface. This function build the FoamSurface to ESSINode map: the first element of the map is the Foam_surface_ID. The second element of the map is ESSI node ID of vertices of ESSI surface that Foam surface center located at.

		void setFoamSurfacePressure();
		void setFoamNodePressure();									//each node take the average pressure value of the surrounding surfaces
		void setESSINodePressure();									//each ESSI node will take the average pressure values of surrounding Foam nodes


		// void setESSINodeDisp();
		// void setESSINodeVel();

		void FoamToESSIUpdate(double t);							// This is to update t time surface pressure info from Openfoam to ESSI nodal pressure. 



		string getFilePath();					// this function will return current working directory as string
		string getUpperDirectory();  			// this function return the upper directory of current directory so that we can easily switch between ESSI simulation folder and Openfoam simulation folder.

		void printFoamNodes();
		void printFoamSurfaces();
		void printESSINodes();
		void printESSISurfaces();
		void printFoamNode(int Node_ID);
		void printFoamSurface(int Surface_ID);
		void printESSINode(int Node_ID);
		void printESSISurface(int Surface_ID);
		void printFoamNodeToFoamSurfacesMapping();
		void printESSINodeToFoamNodesMapping();
		void printFoamSurfaceToESSINodesMapping();

		void vectorPrint(std::vector<int> vec);


	protected:
		bool Is_foam_nodes_determined=false;
		bool Is_foam_surfaces_determined=false;
		bool Is_ESSI_nodes_determined=false;
		bool Is_ESSI_surfaces_determnined=false;
		bool Is_FoamNode_map_to_FoamSurfaces=false;
		bool Is_ESSINode_map_to_FoamNodes=false;
		bool Is_FoamSurface_map_to_ESSINodes=false;



	private:
		std::map<int, FoamNode*>  foam_nodes;              			  // The collection of solid fluid interface nodes in fluid domain. First element is node ID. Seocnd element is pointer to foam_node.
		std::map<int, FoamSurface*> foam_surfaces;  	   			  // The collection of solid fluid interfce surfaces in fluid domain. First element is surface ID. Second element is pointer to foam surface
 		std::map<int, ESSINode*> ESSI_nodes;              			  // The collection of ESSI nodes in solid domain
 		std::map<int, ESSISurface*>  ESSI_surfaces;        			  // The collection of ESSI surfaces in solid domain
 		double current_time;                           			 	  // current simulation time
 		double tolerance=0.1;                              			 // for each ESSI node we conduct radial search to find its corresponding foam nodes. The tolerance is control the radius of our searching sphere.
		std::vector<string> interface_name={"bottom_fluid_surface","lateral_surface_1","lateral_surface_2","lateral_surface_3","lateral_surface_4"};	   // temporary used here for debugging. Will decided how to handle with this later;	
 		std::map<int, std::vector<int>> FoamNodeToFoamSurfacesMapping;   // FoamNodeToFoamSurfacesMapping contains mapping from Foam_node_ID to Foam_surface_IDs of Foam Surfaces that contain this Foam node 
 		std::map<int, std::vector<int>> ESSINodeToFoamNodesMapping;		//ESSINodeToFoamsMapping contains mapping from ESSI_node_ID to Foam_node_IDs of Foam nodes that surrounding this ESSI node
 		std::map<int, std::vector<int>> FoamSurfaceToESSINodesMapping;  //FoamSurfaceToESSINodesMapping contains mapping from Foam_surface_ID to ESSI_node_IDs that are four vertices of ESSI surface that contains that FoamSurface center;
};

#endif