/********************************************************************************************************
* File:              test.cpp                                              
* Author:            hexiang6666                                     | Boris Jeremic,                       *
* Date:              2017-05-17 20:32:16                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-05-18 21:32:20                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#include <iostream>
#include "SSFI.h"


int main()
{
	double t=0.005;
	
	SSFI *ssfi=new SSFI(t);

	ssfi->FoamToESSIUpdate(t);

	// ssfi->printFoamNodeToFoamSurfacesMapping();
	// ssfi->printESSINodeToFoamNodesMapping();
	// ssfi->printFoamSurfaceToESSINodesMapping();

	ssfi->printFoamSurfaces();
	ssfi->printFoamNodes();
	ssfi->printESSINodes();

    return 0;
}