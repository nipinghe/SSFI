#! /usr/bin/env python
import scipy as sp
import sys
import os

# #####################usr input variables########################################################
CURRENT_DIR=os.getcwd()

fluid_surface_node_file=sys.argv[1]+"_fluid_surface_Nodes.txt"   # filename about ESSI nodes inforamtion

surface_load_file="surface_load.include"   #filename about ESSI surface load information

foam_nodes_file="foam_nodes"   #filename about Openfoam nodes information

foam_faces_file="foam_faces"   #filename about Openfoam faces information

foam_pressure_file="foam_pressure"  #filename about Openfoam pressure information

pressure_unit="kg/m/s^(2)"

# ##################### the beginning load ID of surface load ####################################
# beginning_load_id=int(sys.argv[2])
##############################################################################################

# ##################### end input ################################################################


fluid_surface_node_DIR=CURRENT_DIR+"/"+sys.argv[1]+"_ESSI_Simulation"+"/"+fluid_surface_node_file

surface_load_file_DIR=CURRENT_DIR+"/"+sys.argv[1]+"_ESSI_Simulation"+"/"+surface_load_file

foam_nodes_file_DIR=CURRENT_DIR+"/"+sys.argv[1]+"_ESSI_Simulation"+"/"+foam_nodes_file

foam_faces_file_DIR=CURRENT_DIR+"/"+sys.argv[1]+"_ESSI_Simulation"+"/"+foam_faces_file

foam_pressure_file_DIR=CURRENT_DIR+"/"+sys.argv[1]+"_ESSI_Simulation"+"/"+foam_pressure_file



surface_load=sp.loadtxt(surface_load_file_DIR)    ## surface_load has five columns: 1 surface load index; 1 element id ; 4 points id consisting of that surface         

surface_nodes=sp.loadtxt(fluid_surface_node_DIR)   ## surface_node has four columns: 1 node index. three node coordinates

foam_nodes=sp.loadtxt(foam_nodes_file_DIR)   ## by now, foam_nodes has three columns: 3 coordiantes; the index is from 0 to the end

foam_faces=sp.loadtxt(foam_faces_file_DIR)   ## by now, foam_faces has four columns: 4 nodes ID consisting the surface; the index is from 0 to the end

foam_pressure=sp.loadtxt(foam_pressure_file_DIR)   ## by now, foam pressure has one column: pressure value corresponding to the surface ID


# print "surface_load_size ", surface_load.shape

# print "surface_nodes_size", surface_nodes.shape

# print "foam_nodes_size", foam_nodes.shape

# print "foam_faces_size", foam_faces.shape

# print "foam_pressure_size", foam_pressure.shape


No_foam_nodes=foam_nodes.shape[0];
No_foam_faces=foam_faces.shape[0];
No_foam_pressure=foam_pressure.shape[0];

foam_nodes_ID=sp.linspace(0, No_foam_nodes-1, num=No_foam_nodes)   # In python, this will generate one column array
foam_nodes=sp.column_stack((foam_nodes_ID,foam_nodes))   ## Now, foam_nodes has four columns: one foam_nodes_ID; 3 coordiantes; 

foam_faces_ID=sp.linspace(0,No_foam_faces-1, num=No_foam_faces)
foam_faces=sp.column_stack((foam_faces_ID,foam_faces))  ## Now, foam_faces has five columns: one foam_faces_ID; 4 nodes ID consisting the surface; 

foam_pressure_ID=sp.linspace(0,No_foam_pressure-1, num=No_foam_pressure)
foam_pressure=sp.column_stack((foam_pressure_ID,foam_pressure))   ## Now, foam_pressure has two columns: one foam_faces_ID; one pressure value 


No_surface_nodes=surface_nodes.shape[0]
No_surface_load=surface_load.shape[0]

node_mapping={};  # node_mapping contains two columns: the first columns is surface_nodes_ID; the second column is foam_nodes_ID;

for x1 in xrange(0,No_surface_nodes):
	flag=0;     # A tag to represent whether the surface_node finds its counter-foam_node; 0 means no found yet; 1 means found
 	for x2 in xrange(0,No_foam_nodes):
 	 	if surface_nodes[x1,1]==foam_nodes[x2,1] and surface_nodes[x1,2]== foam_nodes[x2,2] and surface_nodes[x1,3]==foam_nodes[x2,3] :
 			node_mapping[surface_nodes[x1,0]]=foam_nodes[x2,0];
 			flag=1;
 	if flag==0:
 		print "Something is wrong in foam_nodes file, there is no matching node for ESSI node No ", surface_nodes[x1,0], "at [", surface_nodes[x1,1], " ", surface_nodes[x1,2], " ", surface_nodes[x1,3], "]";

# print node_mapping

def Is_same_surface(ESSI_surface_id,foam_surface_id):     ## this function return 0 means two faces are not the same faces and 1 means two faces are the same
	ESSI_surface_vertex=surface_load[ESSI_surface_id,2:6];  ## Note:: ESSI_interface_surface_ID is (ESSI_surface_load_ID-1) 
															## **********This generate a 1-D array, has only axis=0; shape=(4,); should be called using ESSI_surface_vertex[i]**************************
	foam_surface_vertex=foam_faces[foam_surface_id,1:5]    ## Here we know that by default all variable outside the function in python can be called inside the function, means outside variables are "global" to inside function
	
	ESSI_surface_vertex.sort(axis=0)
	foam_surface_vertex.sort(axis=0)

	if node_mapping[ESSI_surface_vertex[0]]==foam_surface_vertex[0] and node_mapping[ESSI_surface_vertex[1]]==foam_surface_vertex[1] and node_mapping[ESSI_surface_vertex[2]]==foam_surface_vertex[2] and node_mapping[ESSI_surface_vertex[3]]==foam_surface_vertex[3]:
		return 1
	else:
		return 0


surface_mapping={};   ## surface_mapping contains two columns: the first column is ESSI surface ID, actually the row number (beginning from 0) of surface_load; the second column is corresponding foam_faces_ID 

for x3 in xrange(0,No_surface_load):
	FLAG=0;
	for x4 in xrange(0,No_foam_faces):
		if Is_same_surface(x3,x4)==1:
			surface_mapping[x3]=x4;
			FLAG=1;
	if FLAG==0:
		print "Something is wrong in foam_faces file, there is no matching faces for ESSI surface load No ", (x3+1), ", surface consisting of ESSI nodes [", surface_load[x3,2], ",", surface_load[x3,3], ",", surface_load[x3,4], ",", surface_load[x3,5], "]";

# print surface_mapping;


surface_pressure=sp.zeros((No_surface_load,1));

for x5 in xrange(0,No_surface_load):
	surface_pressure[x5,0]=foam_pressure[surface_mapping[x5],1]
	# surface_load[x5,0]=surface_load[x5,0]+beginning_load_id;


surface_load=sp.column_stack((surface_load,surface_pressure))



##################### Generate input surface load file for real-ESSI #######################################
Input_surface_load_file="surface_load.fei"

Input_surface_load_DIR=CURRENT_DIR+"/"+sys.argv[1]+"_ESSI_Simulation"+"/"+Input_surface_load_file

f=open(Input_surface_load_DIR,"w+")

for x6 in xrange(0,No_surface_load):
	f.write("add load # %d to element # %d type surface at nodes (%d , %d, %d, %d) with magnitude %f*%s ;\n" %(surface_load[x6,0],surface_load[x6,1],surface_load[x6,2],surface_load[x6,3],surface_load[x6,4],surface_load[x6,5],surface_load[x6,6], pressure_unit))

f.close


# print surface_load
	






