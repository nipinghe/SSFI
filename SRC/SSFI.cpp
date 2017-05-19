/********************************************************************************************************
* File:              SSFI.cpp                                              
* Author:            hexiang                                     | Boris Jeremic,                       *
* Date:              2017-03-14 18:19:09                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-05-18 21:22:27                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#include <iostream>
#include <iostream>
#include <vector>
#include "FoamNode.h"
#include "FoamSurface.h"
#include "ESSINode.h"
#include "ESSISurface.h"
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include "SSFI.h"
#include "string_operator.h"
#include <cstddef>
#include <math.h> 
#include <sstream>
#include <fstream>
#include <streambuf>

using namespace std;

// class SSFI    													// SSFI like a broker do data transfermation, geometry mapping, data interpolation between ESSI interface surface and Foam interface surface
// {
// 	public:
// 		SSFI();
// 		~SSFI();
// 		SSFI(double t);
// 		void setFoamNodes();
// 		void setFoamSurfaces();
// 		void setESSINodes();
// 		void setESSISurfaces();
// 		void setTime(double t);
// 		void setTolerance();

// 		std::vector<FoamNode> getFoamNodes();
// 		std::vector<FoamSurface> getFoamSurfaces();
// 		double getTime();
// 		FoamNode getFoamNode(int foam_node_ID);
// 		FoamSurface getFoamSurface(int foam_surface_ID);
		
// 		void readFoamSurfacePressure();
// 		void setFoamSurfacePressure();
// 		void setFoamNodePressure();
// 		void setESSINodePressure();

// 		void setESSINodeDisp();
// 		void setESSINodeVel();

// 		void NodeMapping();
		
// 		void printFoamNodes();
//		void printFoamSurfaces();
//		void printFoamNode(int Node_ID);
//		void printFoamSurface(int Surface_ID);

// protected:
		// bool Is_foam_nodes_determined;
		// bool Is_foam_surfaces_determined;
		// bool Is_ESSI_surfaces_determnined;

// 	private:
// 		std::map<int, FoamNode*>  foam_nodes;              			  // The collection of solid fluid interface nodes in fluid domain. First element is node ID. Seocnd element is pointer to foam_node.
// 		std::map<int, FoamSurface*> foam_surfaces;  	   			  // The collection of solid fluid interfce surfaces in fluid domain. First element is surface ID. Second element is pointer to foam surface
//  		// std::vector<*ESSINode> ESSI_nodes;              			  // The collection of ESSI nodes in solid domain
//  		// std::vector<*ESSISurface> ESSI_surfaces;        			  // The collection of ESSI surfaces in solid domain
//  		double current_time;                           			  // current simulation time
//  		double tolerance;                              			  // The tolerance control we map ESSI node to Foam node 
//  		std::map<int, std::vector<int>> interface_node_mapping;   // The solid fluid interface ndoe mapping info: the first colummn is ESSI node ID; The seocnd vector is a set the Foam nodes surrounding ESSI node within tolerance
 		
//  		bool Is_interface_node_mapping_determined;




// }

SSFI::SSFI(){};
SSFI::~SSFI(){};
SSFI::SSFI(double t):current_time{t}{};

void SSFI::setFoamNodes()    // read foam_nodes.fei file and initialize foam_nodes
{
	Is_foam_nodes_determined=false;

	string DIR=getFilePath();
	DIR=DIR+"/"+foam_nodes_file;
	ifstream foam_nodes_ifs(DIR);
	string current_line;
	string separator=" ";

	if(foam_nodes_ifs.is_open())
	{
		while(std::getline(foam_nodes_ifs,current_line))
		{
			string_operator so=string_operator(current_line);
			std::vector<string> current_line_component=so.string_separator(current_line,separator);
			int Foam_node_ID=std::stoi(current_line_component[0]);
			FoamNode *foam_node_component=new FoamNode(current_line_component);
			if(foam_node_component==0)
			{
				cerr<< ("SSFI::setFoamNodes() -out of memory\n");
				return;
			}
			foam_nodes[Foam_node_ID]=foam_node_component;
		}

		Is_foam_nodes_determined=true;
		cout<<("SSFI::setFoamNodes()-Finish initializing FoamNodes\n");
	}
	else
	{
		cout<<"SSFI:: setFoamNodes()-Cannot open file"<<foam_nodes_file<<endl;
		return;
	}

}

void SSFI::setFoamSurfaces()
{
	Is_foam_surfaces_determined=false;
	string DIR=getFilePath();
	
	DIR=DIR+"/"+foam_surfaces_file;
	ifstream foam_surfaces_ifs(DIR);
	string current_line;
	string separator=" ";

	if(foam_surfaces_ifs.is_open())
	{
		while(std::getline(foam_surfaces_ifs,current_line))
		{
			string_operator so=string_operator(current_line);
			std::vector<string> current_line_component=so.string_separator(current_line,separator);
			int Foam_surface_ID=std::stoi(current_line_component[0]);
			FoamSurface *foam_surface_component=new FoamSurface(current_line_component,foam_nodes);
			if(foam_surface_component==0)
			{
				cerr<<("SSFI::setFoamSurfaces() -out of memeory\n");
				return;
			}
			foam_surfaces[Foam_surface_ID]=foam_surface_component;
		}
		Is_foam_surfaces_determined=true;
		cout<<("SSFI::setFoamSurfaces() -Finish initializing FoamSurfaces\n");
	}
	else
	{
		cout<<"Cannot open file"<<foam_surfaces_file<<endl;
		return;
	}
}


void SSFI::setESSINodes()
{
	Is_ESSI_nodes_determined=false;

	string DIR=getFilePath();
	DIR=DIR+"/"+ESSI_nodes_file;
	ifstream ESSI_nodes_ifs(DIR);
	string current_line;
	string separator=" ";

	if(ESSI_nodes_ifs.is_open())
	{
		while(std::getline(ESSI_nodes_ifs,current_line))
		{
			string_operator so=string_operator(current_line);
			std::vector<string> current_line_component=so.string_separator(current_line,separator);
			int ESSI_node_ID=std::stoi(current_line_component[0]);
			ESSINode *essi_node_component=new ESSINode(current_line_component);
			if(essi_node_component==0)
			{
				cerr<< ("SSFI::setESSINodes() -out of memory\n");
				return;
			}
			ESSI_nodes[ESSI_node_ID]=essi_node_component;
		}

		Is_ESSI_nodes_determined=true;
		cout<<("SSFI::setESSINodes()-Finish initializing ESSINodes\n");
	}
	else
	{
		cout<<"SSFI::setESSINodes()-Cannot open file"<<ESSI_nodes_file<<endl;
		return;
	}
}

void SSFI::setESSISurfaces()
{
	Is_ESSI_surfaces_determnined=false;

	string DIR=getFilePath();

	DIR=DIR+"/"+ESSI_surface_load_info_file;
	ifstream ESSI_surfaces_ifs(DIR);
	string current_line;
	string separator=" ";
	if(ESSI_surfaces_ifs.is_open())
	{
		while(std::getline(ESSI_surfaces_ifs,current_line))
		{
			string_operator so=string_operator(current_line);

			std::vector<string> current_line_component=so.string_separator(current_line,separator);

			// cout<<current_line_component.size();

			int ESSI_surface_ID=std::stoi(current_line_component[0]);

			ESSISurface *essi_surface_component=new ESSISurface(current_line_component,ESSI_nodes);

			if(essi_surface_component==0)
			{
				cerr<< ("SSFI::setESSISurfaces() -out of memory\n");
				return;
			}
			ESSI_surfaces[ESSI_surface_ID]=essi_surface_component;
		}

		Is_ESSI_surfaces_determnined=true;
		cout<<("SSFI::setESSISurfaces()-Finish initializing ESSINodes\n");
	}
	else
	{
		cout<<"SSFI::setESSISurfaces()-Cannot open file"<<ESSI_surface_load_info_file<<endl;
		return;
	}

}

void SSFI::setTime(double t)
{
	current_time=t;
}

void SSFI::setTolerance(double r)
{
	tolerance=r;
}

std::map<int, FoamNode*> SSFI::getFoamNodes()
{
	return foam_nodes;
}


std::map<int, FoamSurface*> SSFI::getFoamSurfaces()
{
	return foam_surfaces;
}


double SSFI::getTime()
{
	return current_time;
}

FoamNode* SSFI::getFoamNode(int foam_node_ID)
{
	return foam_nodes[foam_node_ID];
}

FoamSurface* SSFI::getFoamSurface(int foam_surface_ID)
{
	return foam_surfaces[foam_surface_ID];
}

std::map<int, ESSINode*> SSFI::getESSINodes()
{
	return ESSI_nodes;
}


std::map<int, ESSISurface*> SSFI::getESSISurfaces()
{
	return ESSI_surfaces;
} 

ESSINode* SSFI::getESSINode(int ESSI_node_ID)
{
	return ESSI_nodes[ESSI_node_ID];
}

ESSISurface* SSFI::getESSISurface(int ESSI_surface_ID)
{
	return ESSI_surfaces[ESSI_surface_ID];
}



string SSFI::getFilePath()
{

	char filePath[256];	
	if(!GetCurrentDir(filePath, sizeof(filePath)))
	{

		cout<<"SSFI::getFilePath() -Something wrong happened to get current running directory\n";
		return " ";
	}
	
	string FilePath(filePath);
	return FilePath;

}


string SSFI::getUpperDirectory()
{
	string currentDir=getFilePath();
	std::size_t found=currentDir.find_last_of("/\\");
	return currentDir.substr(0,found);
}  

void SSFI::printFoamNodes()
{
	for (std::map<int, FoamNode*>::iterator it=foam_nodes.begin(); it!=foam_nodes.end(); ++it)
	{
		(it->second)->printNode();
	}
}

void SSFI::printFoamSurfaces()
{
	for (std::map<int, FoamSurface*>::iterator it=foam_surfaces.begin(); it!=foam_surfaces.end(); ++it)
	{
		(it->second)->printSurface();
	}	
}


void SSFI::printESSINodes()
{
	for (std::map<int, ESSINode*>::iterator it=ESSI_nodes.begin(); it!=ESSI_nodes.end(); ++it)
	{
		(it->second)->printNode();
	}
}

void SSFI::printESSISurfaces()
{
	for (std::map<int, ESSISurface*>::iterator it=ESSI_surfaces.begin(); it!=ESSI_surfaces.end(); ++it)
	{
		(it->second)->printSurface();
	}
}

void SSFI::printFoamNode(int Node_ID)
{
	(foam_nodes[Node_ID])->printNode();	
}


void SSFI::printFoamSurface(int Surface_ID)
{
	(foam_surfaces[Surface_ID])->printSurface();
}

void SSFI::printESSINode(int Node_ID)
{
	(ESSI_nodes[Node_ID])->printNode();
}


void SSFI::printESSISurface(int Surface_ID)
{
	(ESSI_surfaces[Surface_ID])->printSurface();
}


std::map<int, int> SSFI::FoamInterfaceIDInfo() 
{
	string Upperdir=getUpperDirectory();

	string boundary_file_DIR=Upperdir+"/"+ModelName+"_fluid_simulation/constant/polyMesh/boundary";
	
	string_operator so;
	
	so.readfile2string(boundary_file_DIR);
	
	string opening_flag="{";
	
	string closing_flag="}";
	
	std::map<int, int> ret;

	for(std::vector<string>::iterator it=interface_name.begin(); it!=interface_name.end(); ++it)
	{
		string boundary_surface=(*it);

		string extracted_string=so.balanced_extractor(boundary_surface,opening_flag,closing_flag);  //First layer extraction: go into each boundary content
		
		string_operator so1=string_operator(extracted_string);
		// string regex_str="nFaces[\\s]*([0-9]+);[\n\\s]*startFace[\\s]*([0-9]+);";
		// startTime[\\s]*([0-9\\.]+);
		std::regex e("nFaces[\\s]*([0-9]+);[\n\\s]*startFace[\\s]*([0-9]+);");
		
		std::regex_iterator<std::string::iterator> it1=so1.search_reg(e);
		
		string nFaces=so1.match_reg(e,it1,1);
		
		string startFace=so1.match_reg(e,it1,2);
		
		ret[std::stoi(startFace)]=std::stoi(nFaces);
	}

	return ret;

}



std::vector<double> SSFI::readFoamSurfacePressure()  //From Openfoam output file to read current interface pressure in fluid domain.
{
	// auto time_str=std::to_string(time);   This can not change 0.005 to the exact same string "0.005". Instead it will get "0.005000".
	std::ostringstream strs;
	
	strs << current_time;
	
	std::string time_str = strs.str();

	string Upperdir=getUpperDirectory();

	string pressure_file_DIR=Upperdir+"/"+ModelName+"_fluid_simulation/"+time_str+"/p";

	string_operator so;

	so.readfile2string(pressure_file_DIR);

	string opening_flag="{";
	string closing_flag="}";

	string output_string="";

	string opening_flag_inside="(";
	string closing_flag_inside=")";

	string separator="\n";

	string extraction_tag="boundaryField";

	string extracted_string=so.balanced_extractor(extraction_tag,opening_flag,closing_flag);

	string_operator so1=string_operator(extracted_string);

	std::vector<double> ret;


	std::map<int, int> foam_interface_ID_info=FoamInterfaceIDInfo();
	
	int index=0; //using this index to assis to access ith element of the FoamInterfaceIDInfo map.

	for(std::vector<string>::iterator it=interface_name.begin(); it!=interface_name.end(); ++it)
	{
		string boundary_name=(*it);

		string extracted_boundary_pressure=so1.balanced_extractor(boundary_name,opening_flag,closing_flag);

		
		std::map<int,int>::iterator it1=foam_interface_ID_info.begin();

		std::advance(it1,index);

		int No_faces=it1->second;
		
		string No_boundary_faces=std::to_string(No_faces);

		string_operator so2=string_operator(extracted_boundary_pressure);
		
		string interface_pressures=so2.balanced_extractor(No_boundary_faces,opening_flag_inside,closing_flag_inside);

	//##########################This section needed to be tested carefully!!!######################################################

		string_operator so3=string_operator(interface_pressures);

		std::vector<string> Foam_surface_pressures=so3.string_separator(interface_pressures,separator);

		for (int i = 0; i < Foam_surface_pressures.size(); ++i)
		{
			ret.push_back(std::stod(Foam_surface_pressures[i]));

		}

	//###############################################################################################################################

		output_string=output_string+interface_pressures;

		index=index+1;

	}
//###############################################################################################################################################################################
//####################################### This is for debugging by Hexiang Wang, we do not want to write output pressure file every time #########################################
//################################################################################################################################################################################ 
	// string output_dir=getFilePath()+"/foam_pressure.fei";
	
	// std::ofstream out(output_dir);

	// out<<output_string;
	
	// out.close();
//##################################################################################################################################################################################
//##################################################################################################################################################################################
//#################################################################################################################################################################################

	return ret;
}



void SSFI::setFoamSurfacePressure()
{
	std::vector<double> FoamSurfacePressures=readFoamSurfacePressure();

	if(FoamSurfacePressures.size()!=foam_surfaces.size())
	{	
		cerr<<"SSFI::setFoamSurfacePressure()- The number of surface pressure values does not equal to the number of Foam surfaces"<<endl;
		return;
	}

	else
	{	
		int pressure_index=0;

		for (std::map<int, FoamSurface*>::iterator it=foam_surfaces.begin(); it!= foam_surfaces.end(); ++it)				// Attention!!! here we used the property that our foam_surfaces map is ordered by foam_surface_ID. (i.e. in ascending order from surface with small ID to surface with larger ID) 
		{
			(it->second)->setSurfacePressure(FoamSurfacePressures[pressure_index]);
			pressure_index=pressure_index+1;
		}
	}

	cout<<"SSFI::setFoamSurfacePressure()-Successfully set pressure for Foam surfaces"<<endl;

}


void SSFI::FoamNodeMapToFoamSurfaces()
{
	if (!Is_foam_surfaces_determined)
	{
		setFoamSurfaces();
	}

	Is_FoamNode_map_to_FoamSurfaces=false;

	FoamNodeToFoamSurfacesMapping.clear();

	for (std::map<int, FoamSurface*>::iterator it=foam_surfaces.begin(); it != foam_surfaces.end(); ++it)
	{
		int surface_ID=it->first;
		FoamSurface* surface=it->second;
		std::vector<int> surface_node_ID=surface->getSurfaceNodeId();

		for (int i = 0; i < surface_node_ID.size(); ++i)
		{
			(FoamNodeToFoamSurfacesMapping[surface_node_ID[i]]).push_back(surface_ID);
		}

	}

	Is_FoamNode_map_to_FoamSurfaces=true;
	cout<<"SSFI::FoamNodeMapToFoamSurfaces()- Successfully build the map from Foam Node to Foam Surfaces"<<endl;
}


void SSFI::setFoamNodePressure()
{
	if (!Is_foam_nodes_determined)
	{
		setFoamNodes();
	}


	if (!Is_FoamNode_map_to_FoamSurfaces)
	{
		FoamNodeMapToFoamSurfaces();
	}

	setFoamSurfacePressure();

	for (std::map<int, FoamNode*>::iterator it=foam_nodes.begin(); it!=foam_nodes.end(); ++it)
	{
		int Node_ID=it->first;
		FoamNode *node=it->second;
		double nodalpressure=0;

		std::vector<int> mapped_surfaces=FoamNodeToFoamSurfacesMapping[Node_ID];
		for (int i = 0; i < mapped_surfaces.size(); ++i)
		{
			nodalpressure=nodalpressure+(foam_surfaces[mapped_surfaces[i]])->getSurfacePressure();
		}
		node->setNodePressure(nodalpressure/(1.0*mapped_surfaces.size()));
	}

}



void SSFI::ESSINodeMapToFoamNodes()
{
	if(!Is_ESSI_nodes_determined)
	{
		setESSINodes();
	}	

	if(!Is_foam_nodes_determined)
	{
		setFoamNodes();
	}

	Is_ESSINode_map_to_FoamNodes=false;

	ESSINodeToFoamNodesMapping.clear();


	for (std::map<int, ESSINode*>::iterator it=ESSI_nodes.begin();  it!=ESSI_nodes.end(); ++it)
	{
		int Node_ID=it->first;
		
		ESSINode *node=it->second;
		
		std::vector<double> ESSI_node_coord=node->getNodeCoord();

		for (std::map<int, FoamNode*>::iterator it1=foam_nodes.begin(); it1!=foam_nodes.end(); ++it1)
		{
			std::vector<double> foam_node_coord=(it1->second)->getNodeCoord();
			if(pow((ESSI_node_coord[0]-foam_node_coord[0]),2)+pow((ESSI_node_coord[1]-foam_node_coord[1]),2)+pow((ESSI_node_coord[2]-foam_node_coord[2]),2)<=pow(tolerance,2))
			{
				int Foam_node_ID=it1->first;
				(ESSINodeToFoamNodesMapping[Node_ID]).push_back(Foam_node_ID);
			}
		}
	}

	Is_ESSINode_map_to_FoamNodes=true;
	cout<<"SSFI::ESSINodeMapToFoamNodes()-Successfully build the map from ESSI ndoe to Foam Nodes"<<endl;
}

void SSFI::setESSINodePressure()
{
	setFoamNodePressure();
	
	if (!Is_ESSINode_map_to_FoamNodes)
	{
		ESSINodeMapToFoamNodes();
	}

	for (std::map<int, std::vector<int>>::iterator it=ESSINodeToFoamNodesMapping.begin(); it!=ESSINodeToFoamNodesMapping.end(); ++it)
	{
		double nodalpressure=0;
		int ESSI_node_ID=it->first;
		std::vector<int> mapped_foam_nodes_ID=it->second;
		for (int i = 0; i < mapped_foam_nodes_ID.size(); ++i)
		{
			nodalpressure=nodalpressure+(foam_nodes[mapped_foam_nodes_ID[i]])->getNodePressure();
		}
		(ESSI_nodes[ESSI_node_ID])->setNodePressure(nodalpressure/(1.0*mapped_foam_nodes_ID.size()));
	}
	cout<<"SSFI::setESSINodePressure()-Successfully set pressure values for ESSI nodes"<<endl;

}

void SSFI::FoamSurfaceMapToESSINodes()
{
	if (!Is_foam_surfaces_determined)
	{
		setFoamSurfaces();
	}

	if(!Is_ESSI_surfaces_determnined)
	{
		setESSISurfaces();
	}

	Is_FoamSurface_map_to_ESSINodes=false;

	FoamSurfaceToESSINodesMapping.clear();

	for (std::map<int, FoamSurface*>::iterator it=foam_surfaces.begin(); it!=foam_surfaces.end(); ++it)
	{
		int surface_ID=it->first;
		FoamSurface *surface=it->second;
		std::vector<double> surface_center=surface->getSurfaceCenterCoord();
		
		bool tag=false;

		for (std::map<int, ESSISurface*>::iterator it1=ESSI_surfaces.begin(); it1 != ESSI_surfaces.end(); ++it1)
		{
			ESSISurface* essi_surface=it1->second;

			if(essi_surface->Is_foam_node_inside(surface_center))
			{
				std::vector<int> vertice_node_IDs=essi_surface->getSurfaceVerticeId();

				FoamSurfaceToESSINodesMapping[surface_ID]=vertice_node_IDs;
				
				tag=true;
				
				break;
			}
		}

		if(!tag)
		{
			cerr<<"SSFI::FoamSurfaceMapToESSINodes() - FoamSurface No "<<surface_ID<<" dose not find its counter-ESSINodes"<<endl;
			return;
		}
	}

	Is_FoamSurface_map_to_ESSINodes=true;
	cout<<"SSFI::FoamSurfaceMapToESSINodes() -Successfully build the map from Foam Surface to ESSI Nodes"<<endl;
} 


void SSFI::FoamToESSIUpdate(double t)
{
	setTime(t);

	setESSINodePressure();
}


std::map<int, std::vector<int>> SSFI::getFoamNodeToFoamSurfacesMapping()
{
	return this->FoamNodeToFoamSurfacesMapping;
}


std::map<int, std::vector<int>> SSFI::getESSINodeToFoamNodesMapping()
{
	return this->ESSINodeToFoamNodesMapping;
}

std::map<int, std::vector<int>> SSFI::getFoamSurfaceToESSINodesMapping()
{
	return this->FoamSurfaceToESSINodesMapping;
}


void SSFI::printFoamNodeToFoamSurfacesMapping()
{
	if (!Is_FoamNode_map_to_FoamSurfaces)
	{
		FoamNodeMapToFoamSurfaces();
	}
	for(std::map<int, std::vector<int>>::iterator it=FoamNodeToFoamSurfacesMapping.begin(); it!= FoamNodeToFoamSurfacesMapping.end(); ++it)
	{
		cout<<"SSFI::printFoamNodeToFoamSurfacesMapping()-FoamNode No "<<it->first<<" is mapping to FoamSurfaces ";
		vectorPrint(it->second);
		cout<<endl;
	}
}

void SSFI::printESSINodeToFoamNodesMapping()
{	
	if (!Is_ESSINode_map_to_FoamNodes)
	{
		ESSINodeMapToFoamNodes();
	}
	for(std::map<int, std::vector<int>>::iterator it=ESSINodeToFoamNodesMapping.begin(); it!= ESSINodeToFoamNodesMapping.end(); ++it)
	{
		cout<<"SSFI::printESSINodeToFoamNodesMapping()-ESSINode No "<<it->first<<" is mapping to FoamNodes ";
		vectorPrint(it->second);
		cout<<endl;
	}
}

void SSFI::printFoamSurfaceToESSINodesMapping()
{	
	if (!Is_FoamSurface_map_to_ESSINodes)
	{
		FoamSurfaceMapToESSINodes();
	}
	for(std::map<int, std::vector<int>>::iterator it=FoamSurfaceToESSINodesMapping.begin(); it!= FoamSurfaceToESSINodesMapping.end(); ++it)
	{
		cout<<"SSFI::printFoamSurfaceToESSINodesMapping()-FoamSurface No "<<it->first<<" is mapping to ESSINodes ";
		vectorPrint(it->second);
		cout<<endl;
	}
}

void SSFI::vectorPrint(std::vector<int> vec)
{
	cout<<"(";
	for (int i = 0; i < vec.size()-1; ++i)
	{
	cout<<vec[i]<<",";
	}
	cout<<vec[vec.size()-1]<<")";
}
