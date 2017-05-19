/********************************************************************************************************
* File:              SSFI.cpp                                              
* Author:            hexiang                                     | Boris Jeremic,                       *
* Date:              2017-03-14 18:19:09                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-05-10 23:33:29                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#include <iostream>
#include "postFoam.h"

using namespace std;

int main(){

	// postFoam pf=postFoam("box");
	// std::vector<string> boundary_name={"bottom_fluid_surface","lateral_surface_1","lateral_surface_2","lateral_surface_3","lateral_surface_4"};
	pf.set_transfer_boundary(boundary_name);
	// pf.get_transfer_boundary_name();
	// pf.get_project_name();
	// pf.fluid_folder_DIR();
	pf.surface_load_preprocess();
	// std::map<int,int> temp=pf.surface_id_information();

	// for(std::map<int,int>::iterator it=temp.begin(); it!=temp.end(); ++it)
	// {
	// 	cout<<(it->first)<<endl<<(it->second)<<endl;
	// 	cout<<endl;
	// }
	// string No_points=pf.No_points();

	// pf.fluid_nodes();
	
	// pf.fluid_surfaces();

	pf.boundary_pressure(0.05);

	pf.ESSI_input_pressure_load();    // 122 is the allowable surface load beginning ID in RealESSI input for this case, because imposed motion take up some load ID. 

    return 0;
}