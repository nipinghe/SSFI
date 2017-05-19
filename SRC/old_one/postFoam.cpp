/********************************************************************************************************
* File:              postFoam.cpp                                              
* Author:            hexiang6666                                 | Boris Jeremic,                       *
* Date:              2017-03-14 16:48:30                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-05-10 22:51:36                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#include <iostream>
#include "string_operator.h"
#include "postFoam.h"
#include <string>
#include <sstream>

using namespace std;

postFoam::postFoam(){};
postFoam::~postFoam(){};
postFoam::postFoam(const string& str):project_name{str}{};


//########### This function is to set solid-fluid interaction boundary surface######################
//###################### ATTENTION: the input boundary name must follow ############################
//###################the order that the ID of boundary surface(corresponding #####################
//############### to boundary name) is increasing, otherwise we need ##############################
//########write a mapping function to build the mapping relationship ##############################
//############between boundary surface name and  surface_id_information #########################
void postFoam::set_transfer_boundary(std::vector<string> boundary_name)                   
{
	for(std::vector<string>::iterator it=boundary_name.begin(); it!=boundary_name.end(); ++it)
	{
		transfer_boundary_name.push_back(*it);
	}

}
//###################################################################################################
//###################################################################################################

void postFoam::get_project_name()
{
	cout<<(*this).project_name<<endl;
}

void postFoam::get_transfer_boundary_name()
{
	for(std::vector<string>::iterator it=(*this).transfer_boundary_name.begin(); it!=(*this).transfer_boundary_name.end(); ++it)
	{
		cout<<(*it)<<endl;
	}
}

string postFoam::fluid_folder_DIR()
{
	string current_DIR=getFilePath();
	string ret=current_DIR+"/"+project_name+"_fluid_simulation";
	cout<<ret<<endl;
	return ret;
}


// ##############this function is written to get current path directory########################
string postFoam::getFilePath()
{

	char filePath[256];	
	if(!GetCurrentDir(filePath, sizeof(filePath)))
	{

		cout<<"** ERROR - Something went wrong, exiting...\n";
		return " ";
	}
	
	string FilePath(filePath);
	return FilePath;

}

//###############################################################################################
void postFoam::surface_load_preprocess()
{
	string bash_call_string="surface_load_preprocess  "+project_name+"_ESSI_Simulation";
	system(bash_call_string.c_str());
}


std::map<int, int> postFoam::surface_id_information()   //generate transfer boundary face information map: first element of the map is startFace-ID; second element of the map is nFaces
{
	string boundary_file_DIR=getFilePath()+"/"+project_name+"_fluid_simulation/constant/polyMesh/boundary";
	string_operator so;
	so.readfile2string(boundary_file_DIR);
	string opening_flag="{";
	string closing_flag="}";
	std::map<int, int> ret;
	
	for(std::vector<string>::iterator it=transfer_boundary_name.begin(); it!=transfer_boundary_name.end(); ++it)
	{
		string boundary_surface=(*it);
		string extracted_string=so.balanced_extractor(boundary_surface,opening_flag,closing_flag);  //First extraction: go into each boundary content
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

string postFoam::No_points()
{
	string ret;
	string information_file_DIR=getFilePath()+"/"+project_name+"_fluid_simulation/constant/polyMesh/neighbour";
	string_operator so;
	so.readfile2string(information_file_DIR);
	std::regex e("nPoints:[\\s]*([0-9]+)");
	std::regex_iterator<std::string::iterator> it=so.search_reg(e);
	ret=so.match_reg(e,it,1);
	return ret;
}

string postFoam::No_faces()
{
	string ret;
	string information_file_DIR=getFilePath()+"/"+project_name+"_fluid_simulation/constant/polyMesh/neighbour";
	string_operator so;
	so.readfile2string(information_file_DIR);
	std::regex e("nFaces:[\\s]*([0-9]+)");
	std::regex_iterator<std::string::iterator> it=so.search_reg(e);
	ret=so.match_reg(e,it,1);
	return ret;
}

string postFoam::No_internalfaces()
{
	string ret;
	string information_file_DIR=getFilePath()+"/"+project_name+"_fluid_simulation/constant/polyMesh/neighbour";
	string_operator so;
	so.readfile2string(information_file_DIR);
	std::regex e("nInternalFaces:[\\s]*([0-9]+)");
	std::regex_iterator<std::string::iterator> it=so.search_reg(e);
	ret=so.match_reg(e,it,1);
	return ret;
}

void postFoam::fluid_nodes()     //Note: these nodes contain all nodes include both inside and boundary nodes
{
	string No_points=(this->No_points());
	string points_file_DIR=getFilePath()+"/"+project_name+"_fluid_simulation/constant/polyMesh/points";
	string_operator so;
	so.readfile2string(points_file_DIR);
	string opening_flag="(";
	string closing_flag=")";
	string extracted_string=so.balanced_extractor(No_points,opening_flag,closing_flag); 

	// cout<<extracted_string<<endl;
	string output_string="";


	string_operator so1=string_operator(extracted_string);

	std::regex e("\\([-0-9\\s]+\\)");
	std::regex_iterator<std::string::iterator> it1=so1.search_reg(e);
	std::regex_iterator<std::string::iterator> rend;
	while (it1 != rend)
    {
    	string output_string_component= it1->str();
 		vector<string> temp=so1.string_extractor_with_spaces(output_string_component,opening_flag,closing_flag);
 		output_string=output_string+temp[0]+"\n";
    	++it1;
   	}
   	string output_dir=getFilePath()+"/"+project_name+"_ESSI_Simulation/foam_nodes";
	std::ofstream out(output_dir);
	out<<output_string;
	out.close();
	// cout<<output_string<<endl;
}

void postFoam::fluid_surfaces()   //Note: these surface are only boundary surfaces
{
	string No_faces=(this->No_faces());
	// int No_total_faces=std::stoi(No_faces);
	string faces_file_DIR=getFilePath()+"/"+project_name+"_fluid_simulation/constant/polyMesh/faces";
	string_operator so;
	so.readfile2string(faces_file_DIR);
	string opening_flag="(";
	string closing_flag=")";
	string extracted_string=so.balanced_extractor(No_faces,opening_flag,closing_flag);

	string output_string="";

	string_operator so1=string_operator(extracted_string);

	std::regex e("\\([-0-9\\s]+\\)");

	std::map<int, int> boundary_surface_id_information=surface_id_information();

	for(std::map<int,int>::iterator it2=boundary_surface_id_information.begin(); it2!=boundary_surface_id_information.end(); ++it2)
	{
		int startFace=(it2->first);
		int No_boundary_faces=(it2->second);

		for(int i=0; i<No_boundary_faces; ++i)
		{
			std::regex_iterator<std::string::iterator> it1=so1.search_reg(e);
			std::advance(it1,startFace);
			std::advance(it1,i);
			string output_string_component=it1->str();
			vector<string> temp=so1.string_extractor_with_spaces(output_string_component,opening_flag,closing_flag);
 			output_string=output_string+temp[0]+"\n";
		}
	 }

   	string output_dir=getFilePath()+"/"+project_name+"_ESSI_Simulation/foam_faces";
	std::ofstream out(output_dir);
	out<<output_string;
	out.close();
	// cout<<"final string"<<output_string<<endl;
}


void postFoam::boundary_pressure(double time)
{
	// auto time_str=std::to_string(time);   This can not change 0.005 to the exact same string "0.005". Instead it will get "0.005000".
	std::ostringstream strs;
	strs << time;
	std::string time_str = strs.str();

	string pressure_file_DIR=getFilePath()+"/"+project_name+"_fluid_simulation/"+time_str+"/p";

	// cout<<"pressure_file_DIR"<<pressure_file_DIR<<endl;

	string_operator so;
	so.readfile2string(pressure_file_DIR);

	// cout<<"total_string"<<so.get_string()<<endl;

	string opening_flag="{";
	string closing_flag="}";

	string output_string="";

	string opening_flag_inside="(";
	string closing_flag_inside=")";

	string extraction_tag="boundaryField";

	string extracted_string=so.balanced_extractor(extraction_tag,opening_flag,closing_flag);

	

	string_operator so1=string_operator(extracted_string);

	int index=0; //using this index to assis to access ith element of the surface_id_information map.

	for(std::vector<string>::iterator it=transfer_boundary_name.begin(); it!=transfer_boundary_name.end(); ++it)
	{
		string boundary_name=(*it);
		string extracted_boundary_pressure=so1.balanced_extractor(boundary_name,opening_flag,closing_flag);

		std::map<int, int> boundary_surface_id_information=surface_id_information();
		std::map<int,int>::iterator it1=boundary_surface_id_information.begin();
		std::advance(it1,index);
		int No_faces=it1->second;
		string No_boundary_faces=std::to_string(No_faces);

		string_operator so2=string_operator(extracted_boundary_pressure);
		string individual_boundary_pressure=so2.balanced_extractor(No_boundary_faces,opening_flag_inside,closing_flag_inside);

		output_string=output_string+individual_boundary_pressure;
		index=index+1;
	}
	string output_dir=getFilePath()+"/"+project_name+"_ESSI_Simulation/foam_pressure";
	std::ofstream out(output_dir);
	out<<output_string;
	out.close();

}


void postFoam::ESSI_input_pressure_load(int surface_load_beginning_ID)
void postFoam::ESSI_input_pressure_load()
{
	// string surface_load_id=std::to_string(surface_load_beginning_ID);
	// string bash_call_string="sl_mapping.py "+project_name+" "+surface_load_id;
	string bash_call_string="sl_mapping.py "+project_name;
	system(bash_call_string.c_str());		
}

