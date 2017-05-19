/********************************************************************************************************
* File:              postFoam.h                                              
* Author:            hexiang6666                                 | Boris Jeremic,                       *
* Date:              2017-03-14 16:48:14                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-05-10 16:23:34                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#ifndef POSTFOAM_H
#define POSTFOAM_H
#include <iostream>
#include "string_operator.h"

#ifdef _WIN32 
    #include <direct.h>
    #define GetCurrentDir _getcwd
    #define slash "\\"
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
	#define slash "/"
#endif

using namespace std;

class postFoam
{
	public:
		postFoam();
		~postFoam();
		postFoam(const string& str);
		// std::map<string, std::vector<string>> getboundaryInfo();
		void set_transfer_boundary(std::vector<string> boundary_name);
		void get_project_name();
		void get_transfer_boundary_name();
		string fluid_folder_DIR();
		string getFilePath();
		void surface_load_preprocess();
		std::map<int, int> surface_id_information();
		string No_points();
		string No_faces();
		string No_internalfaces();
		void fluid_nodes(); //write fluid nodes information to ESSI simulation folder
		void fluid_surfaces(); //write fluid surfaces information to ESSI simulation folder
		void boundary_pressure(double time); // write boundary pressure information to ESSI simulation folder
		void ESSI_input_pressure_load(); //build the geometry mapping realtionship and write ESSI input_pressure_load fei file

	private:
		string project_name; 
		std::vector<string> transfer_boundary_name;



};
#endif