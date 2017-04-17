//*******************************************************************************************************//
//File:              water_break.geo                                              
// Author:            hexiang                                     | Boris Jeremic,                       //
// Date:              2017-04-16 15:17:10                         | University of California, Davis,95616//
// Description:       #############                               | California                           //
// Rev:               Version 1                                   | jeremic@ucdavis.edu                  //
// Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     //
// * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  //
//                           Last Modified time: 2017-04-16 22:45:52                                     //            
//  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //        
// The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     //
// The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance//
// with the terms and conditions stipulated in the agreement/contract under which the program have been  //
// supplied.                                                                                             //
//*******************************************************************************************************//



//####################################### usr input variable ################################################
x_length=30;
x_mesh_layers=30;

y_thick=3;
y_thick_layer=6;

z_bed_height=3;
z_bed_layers=6;

z_break_water_height=4;
z_break_water_layers=4;

No_lateral_free_layers_left=12;  // How many layers have been contracted in x direction of left-side, from seabed to breakwater
No_lateral_free_layers_right=12;
x_breakwater_contraction_length=1;

water_height=7;
z_water_height_layers=7;


//###################################### Ending usr input #################################################


////################################ Build solid part#####################################
x_bed_mesh_size=1.0*x_length/x_mesh_layers ;

Point(1) = {0, 0, 0, 1.0};

Extrude {No_lateral_free_layers_left*x_bed_mesh_size, 0, 0} { Point{1}; Layers{No_lateral_free_layers_left}; }

No_middle_layers=x_mesh_layers-No_lateral_free_layers_left-No_lateral_free_layers_right;

Extrude {No_middle_layers*x_bed_mesh_size, 0, 0} {  Point{2}; Layers{No_middle_layers}; }

Extrude {No_lateral_free_layers_right*x_bed_mesh_size, 0, 0} {  Point{3}; Layers{No_lateral_free_layers_right}; }

seabed_surface[]=Extrude {0, 0, -z_bed_height} {Line{1, 2, 3}; Layers{z_bed_layers}; Recombine; };

Extrude {x_breakwater_contraction_length, 0, z_break_water_height} {  Point{2}; Layers{z_break_water_layers}; }

Extrude {-x_breakwater_contraction_length, 0, z_break_water_height} {  Point{3}; Layers{z_break_water_layers}; }

Line(18) = {12, 11};

Transfinite Line{18}=No_middle_layers+1;

Line Loop(1) = {2,17,18,-16};

Plane Surface(1)={1};

Transfinite Surface {1};
Recombine Surface {1};


break_water[]=Extrude {0, y_thick, 0} { Surface{1}; Layers{y_thick_layer}; Recombine;};

Physical Volume("breakwater",1)=break_water[1];
Physical Surface("breakwater_top_surface",13)={break_water[4]};
Physical Surface("breakwater_left_surface",14)={break_water[5]};
Physical Surface("breakwater_right_surface",15)={break_water[3]};


seabed[]=Extrude{0,y_thick,0} { Surface{seabed_surface[1], seabed_surface[5],seabed_surface[9]}; Layers{y_thick_layer}; Recombine; };

Physical Volume("seabed",2)={seabed[1], seabed[7], seabed[13]};

Physical Surface("seabed_topleft_surface",11)={ seabed[2] };

Physical Surface("seabed_topright_surface",12)={ seabed[14] };

Physical Surface("seabed_left_surface",16)={ seabed[5] };

Physical Surface("seabed_right_surface",17)={seabed[15]};

Physical Surface("seabed_front_surface",18)={seabed[0], seabed[6],seabed[12]};

Physical Surface("seabed_back_surface",19)={seabed_surface[1], seabed_surface[5],seabed_surface[9]};

Physical Surface("seabed_bottom_surface",20)={seabed[4],seabed[10],seabed[16]};

Physical Surface("fluid_interface_surface",21)={ seabed[2], seabed[14], break_water[4], break_water[5], break_water[3] };

Physical Surface("breakwater_front_surface",22)={break_water[0]};

Physical Surface("breakwater_back_surface",23)={1};

Physical Volume("solid",4)={seabed[1], seabed[7], seabed[13], break_water[1]};


//Printf("New surfaces %g %g %g %g  ", seabed[14],seabed[15],seabed[16],seabed[17]);

////################################ Ending build solid part#####################################

////################################ Build fluid part#####################################
temp[]=Extrude {0, 0, z_break_water_height} { Point{1}; Layers{z_break_water_layers}; };

l1=newl;

Line(l1) = {temp[0], 11};

Transfinite Line{l1}=No_lateral_free_layers_left+1;

s1=news;

Line Loop(2) ={temp[1], l1, -16, -1};

Plane Surface(s1)={2};

Transfinite Surface {s1};

Recombine Surface {s1};


temp_1[]=Extrude {0, 0, z_break_water_height} { Point{4}; Layers{z_break_water_layers}; };

l2=newl;

Line(l2) = {temp_1[0], 12};

Transfinite Line{l2}=No_lateral_free_layers_right+1;

s2=news;

Line Loop(3) ={temp_1[1], l2, -17, 3};

Plane Surface(s2)={3};

Transfinite Surface {s2};

Recombine Surface {s2};

water_upper_surface[]=Extrude {0, 0, water_height-z_break_water_height} { Line{108,18,111}; Layers{z_water_height_layers-z_break_water_layers}; Recombine; };

water_surface[]={s1,s2,water_upper_surface[1], water_upper_surface[5],water_upper_surface[9]};

Physical Surface("water_front_surface",24)={water_surface[]};

water[]=Extrude {0, y_thick, 0} { Surface{water_surface[]}; Layers{y_thick_layer}; Recombine;};

Physical Volume("water",3)={water[1],water[7],water[13],water[19],water[25]};

Physical Surface("water_back_surface",25)={water[0],water[6],water[12],water[18],water[24]};

Physical Surface("water_left_surface",26)={189,133};

Physical Surface("water_right_surface",27)={155,233};

Physical Surface("water_top_surface",28)={185,207,229};

