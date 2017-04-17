Point(1) = {-1, -1, 0, 1.0};

Extrude {1, 0, 0} {
  Point{1};  Layers{1};
}

Extrude {1, 0, 0} {
  Point{2}; Layers{1};
}
Extrude {0, 1, 0} {
  Line{1, 2}; Layers{1}; Recombine;
}
Extrude {0, 1, 0} {qqqqq
  Line{3, 7}; Layers{1};  Recombine;
}



layer_thickness[]={1,1,1,1};  //outside layer thickness in x & y direction; x direction thickness equals to y direction thickness assumed

Z_layer_thickness[]={1,1,1,1}; // outside layer thickness in z direction  

surface_index=0;  //index of surface id array
volume_index=0;  // index of volume id array
start_line_id=1;  //start_line_id: the begining line(direction from neg_x to pos_x) of the neg_y side

neg_z_length[]={1,1}; //neg_z_length per part
neg_z_layer[]={1,1};      //neg_z_layer per part

neg_y_length[]={1,1};        //neg_y_length per part
pos_y_length[]={1,1};        //pos_y_length per part
neg_x_length[]={1,1};        //neg_X_length per part
pos_x_length[]={1,1};        //pos_x_length per part

neg_y_layer[]={1,1};            //neg_y_layer per part
neg_x_layer[]={1,1};            //neg_x_layer per part
pos_y_layer[]={1,1};            //pos_y_layer per part
pos_x_layer[]={1,1};            //pos_x_layer per part



volume_index=0;




inner_part[]={6,10,14,18};
//Physical Surface("inner surface",#layer_thickness[]+10) =inner_part[];

ini_surface_inner[]=inner_part[];
For i11 In {0:#neg_z_length[]-1}
  temp_volume[]=Extrude {0, 0, -neg_z_length[i11]} { Surface{ini_surface_inner[]}; Layers{neg_z_layer[i11]}; Recombine; };
  For i12 In {0:#ini_surface_inner[]-1}
  ini_surface_inner[i12]=temp_volume[0+i12*6];
  volume_id[volume_index]=temp_volume[1+i12*6];
  volume_index=volume_index+1;
  EndFor
EndFor

Physical Volume("inner part",#layer_thickness[]+1)=volume_id[];
volume_index=0;




For i In {0:#layer_thickness[]-1}    
//#layer_thickness[]-1
  temp_volume[]=Extrude {0, 0, -Z_layer_thickness[i]} { Surface{ini_surface_inner[]}; Layers{1}; Recombine; };
  For i16 In {0:#ini_surface_inner[]-1}
  ini_surface_inner[i16]=temp_volume[0+i16*6];
  volume_id[volume_index]=temp_volume[1+i16*6];
  volume_index=volume_index+1;
  EndFor

//#layer_thickness[]-1

temp1[]=Extrude {0, -layer_thickness[i], 0} { Line{start_line_id}; Layers{1}; Recombine;};
surface_id[surface_index]=temp1[1];
surface_index=surface_index+1;


ini_line_id=temp1[2];
For i1 In {0:#neg_y_length[]-2}
    temp2[]=Extrude {neg_y_length[i1+1],0,0} {  Line{ini_line_id}; Layers{ neg_y_layer[i1+1]}; Recombine;};
    surface_id[surface_index]=temp2[1];
    surface_index=surface_index+1;
    ini_line_id=temp2[0];
EndFor

temp3[]=Extrude {layer_thickness[i], 0, 0} { Line{temp2[0]}; Layers{1}; Recombine;};
surface_id[surface_index]=temp3[1];
surface_index=surface_index+1;
ini_line_id=temp3[3];


For i2 In {0:#pos_x_length[]-1}
  temp4[]=Extrude {0,pos_x_length[i2],0} {  Line{ini_line_id}; Layers{ pos_x_layer[i2]}; Recombine;};
  surface_id[surface_index]=temp4[1];
  surface_index=surface_index+1;
  ini_line_id=temp4[0];
EndFor

temp5[]=Extrude {0, layer_thickness[i], 0} { Line{temp4[0]}; Layers{1}; Recombine;};
surface_id[surface_index]=temp5[1];
surface_index=surface_index+1;
ini_line_id=temp5[2];

For i3 In {0:#pos_y_length[]-1}
  temp6[]=Extrude {-pos_y_length[i3], 0, 0} {  Line{ini_line_id}; Layers{ pos_y_layer[i3]}; Recombine;};
  surface_id[surface_index]=temp6[1];
  surface_index=surface_index+1;
  ini_line_id=temp6[0];
EndFor

temp7[]=Extrude {-layer_thickness[i], 0, 0} { Line{temp6[0]}; Layers{1}; Recombine;};
surface_id[surface_index]=temp7[1];
surface_index=surface_index+1;
ini_line_id=temp7[3];

//Printf("New surfaces %g and %g", ini_line_id, temp7[3]);

For i4 In {0:#neg_x_length[]-1}
  temp8[]=Extrude {0, -neg_x_length[i4], 0} {  Line{ini_line_id}; Layers{ neg_x_layer[i4]}; Recombine;};
  surface_id[surface_index]=temp8[1];
  surface_index=surface_index+1;
  ini_line_id=temp8[0];
EndFor

temp9[]=Extrude {0,-layer_thickness[i], 0} { Line{temp8[0]}; Layers{1}; Recombine;};
surface_id[surface_index]=temp9[1];
surface_index=surface_index+1;

start_line_id=temp9[0];
//Printf("New surfaces %g and %g", start_line_id, temp9[0]);
If (i==0)
	//Physical Surface("surface of DMR layer",i+10) = surface_id[];
EndIf
If (i==1 )
	//Physical Surface("surface of outside layer_1",i+10) = surface_id[];
EndIf
If (i==2 )
	//Physical Surface("surface of outside layer_2",i+10) = surface_id[];
EndIf
If (i==3 )
	//Physical Surface("surface of outside layer_3",i+10) = surface_id[];
EndIf


surface_index=0;

ini_surface[]=surface_id[];
For i10 In {0:#neg_z_length[]-1}
  temp_volume[]=Extrude {0, 0, -neg_z_length[i10]} { Surface{ini_surface[]}; Layers{neg_z_layer[i10]}; Recombine; };
  For i9 In {0:#ini_surface[]-1}
  ini_surface[i9]=temp_volume[0+i9*6];
  volume_id[volume_index]=temp_volume[1+i9*6];
  volume_index=volume_index+1;
  EndFor
EndFor

For i13 In {0:i}
  temp_volume[]=Extrude {0, 0, -Z_layer_thickness[i13]} { Surface{ini_surface[]}; Layers{1}; Recombine; };
  For i14 In {0:#ini_surface[]-1}
  ini_surface[i14]=temp_volume[0+i14*6];
  volume_id[volume_index]=temp_volume[1+i14*6];
  volume_index=volume_index+1;
  EndFor
EndFor

If (i==0)
	Physical Volume("DRM layer",i+1)=volume_id[];
EndIf
If (i==1 )
	Physical Volume("outside layer_1",i+1)=volume_id[];
EndIf
If (i==2 )
	Physical Volume("outside layer_2",i+1)=volume_id[];
EndIf
If (i==3 )
	Physical Volume("outside layer_3",i+1)=volume_id[];
EndIf


volume_index=0;


  temp_size=#ini_surface_inner[];
  For i17 In {0:#ini_surface[]-1}
  ini_surface_inner[i17+temp_size]=ini_surface[i17];
  EndFor


//Printf("New surfaces %g %g %g %g %g %g %g %g %g %g %g", temp_volume[0], temp_volume[1],  temp_volume[2], temp_volume[3], temp_volume[4], temp_volume[5],temp_volume[6],temp_volume[7],temp_volume[8], temp_volume[9], temp_volume[10]);

temp_neg_y_length[0]=layer_thickness[i];
temp_pos_y_length[0]=layer_thickness[i];
temp_neg_x_length[0]=layer_thickness[i];
temp_pos_x_length[0]=layer_thickness[i];

temp_neg_y_layer[0]=1;
temp_pos_y_layer[0]=1;
temp_neg_x_layer[0]=1;
temp_pos_x_layer[0]=1;

For i5 In {0:#neg_y_length[]-1}
temp_neg_y_length[i5+1]=neg_y_length[i5];
temp_neg_y_layer[i5+1]=neg_y_layer[i5];
EndFor

For i6 In {0:#pos_y_length[]-1}
temp_pos_y_length[i6+1]=pos_y_length[i6];
temp_pos_y_layer[i6+1]=pos_y_layer[i6];
EndFor

For i7 In {0:#neg_x_length[]-1}
temp_neg_x_length[i7+1]=neg_x_length[i7];
temp_neg_x_layer[i7+1]=neg_x_layer[i7];
EndFor

For i8 In {0:#pos_x_length[]-1}
temp_pos_x_length[i8+1]=pos_x_length[i8];
temp_pos_x_layer[i8+1]=pos_x_layer[i8];
EndFor

temp_neg_y_length[#neg_y_length[]+1]=layer_thickness[i];
temp_pos_y_length[#neg_y_length[]+1]=layer_thickness[i];
temp_neg_x_length[#neg_y_length[]+1]=layer_thickness[i];
temp_pos_x_length[#neg_y_length[]+1]=layer_thickness[i];

temp_neg_y_layer[#neg_y_length[]+1]=1;
temp_pos_y_layer[#neg_y_length[]+1]=1;
temp_neg_x_layer[#neg_y_length[]+1]=1;
temp_pos_x_layer[#neg_y_length[]+1]=1;


neg_y_length[]=temp_neg_y_length[];
neg_x_length[]=temp_neg_x_length[];
pos_y_length[]=temp_pos_y_length[];
pos_x_length[]=temp_pos_x_length[];

neg_y_layer[]=temp_neg_y_layer[];
pos_y_layer[]=temp_pos_y_layer[];
neg_x_layer[]=temp_neg_x_layer[];
pos_x_layer[]=temp_pos_x_layer[];


EndFor

//Printf("New surfaces %g and %g", layer_thickness[0], layer_thickness[1]);

//volume_index=0;

//inner_part[]={89, 93, 97, 101, 105, 85, 81, 77, 69, 49, 53, 73, 57, 61, 65, 45, 41, 37, 29, 33, 13, 9, 17, 25, 21};
//Physical Surface(#layer_thickness[]) =inner_part[] ;

//ini_surface[]=inner_part[];
//For i11 In {0:#neg_z_length[]-1}
//  temp_volume[]=Extrude {0, 0, -neg_z_length[i11]} { Surface{ini_surface[]}; Layers{neg_z_layer[i11]}; Recombine; };
//  For i12 In {0:#ini_surface[]-1}
//  ini_surface[i12]=temp_volume[0+i12*6];
//  volume_id[volume_index]=temp_volume[1+i12*6];
//  volume_index=volume_index+1;
//  EndFor
//EndFor

//Physical Volume(#layer_thickness[])=volume_id[];
//volume_index=0;

//For i15 In {0:#layer_thickness[]-1}
//  temp_volume[]=Extrude {0, 0, -Z_layer_thickness[i15]} { Surface{ini_surface[]}; Layers{1}; Recombine; };
//  For i16 In {0:#ini_surface[]-1}
//  ini_surface[i16]=temp_volume[0+i16*6];
//  volume_id[volume_index]=temp_volume[1+i16*6];
//  volume_index=volume_index+1;
//  EndFor
// Physical Volume(#layer_thickness[]+i15+1)=volume_id[];
// volume_index=0;
//EndFor


//Physical Surface("bottom surface",15) = {40875, 40941, 40897, 40853, 40831, 40809, 40787, 41029, 41051, 41007, 40985, 40963, 40919, 29265, 41073, 29177, 29199, 29221, 29243, 29111, 29287, 29309, 29133, 29331, 40765, 29155, 41095, 40743, 28385, 29089, 28539, 28517, 28495, 28473, 28451, 28429, 28407, 28363, 29353, 28341, 27857, 27835, 29375, 27813, 27791, 28561, 27901, 29067, 27879, 40721, 41117, 27923, 29045, 27219, 27241, 40699, 27439, 27461, 27659, 27769, 27945, 28319, 28583, 41139, 29397, 40677, 27483, 27417, 27637, 27747, 27967, 27263, 28297, 28605, 41161, 27197, 29419, 29023, 40655, 27395, 27175, 27285, 27505, 27615, 27725, 27989, 28275, 28627, 41183, 29001, 29441, 28649, 27153, 27351, 27373, 27549, 27571, 27703, 28011, 28253, 28979, 29463, 40633, 41205, 40611, 29485, 41227, 28957, 28671, 28231, 27131, 28033, 27681, 27593, 27527, 27329, 27307, 28099, 40589, 41249, 28055, 28077, 28121, 28143, 28165, 28187, 28209, 28693, 29507, 28935, 28913, 28891, 28869, 28847, 28825, 41271, 28803, 28781, 28759, 28737, 29529, 28715, 40567, 40545, 41293, 29705, 29771, 29749, 29727, 29683, 29661, 29639, 29617, 29573, 29595, 29551, 41359, 41403, 41337, 41315, 41513, 41425, 41447, 41535, 41491, 41469, 41381, 41557, 41579};

//
//Physical Surface("bottom surface",15) = {13206, 13228, 13250, 13272, 13294, 13316, 13338, 13360, 13382, 13404, 8486, 13184, 8552, 8530, 8508, 13426, 8398, 8420, 8442, 8464, 13162, 8574, 8376, 7914, 7980, 7958, 7936, 7892, 7870, 13448, 7518, 7540, 7562, 8596, 8354, 13470, 13140, 7584, 8002, 7848, 13492, 7386, 8332, 7364, 8618, 7496, 13118, 7606, 7826, 8024, 7342, 8640, 13096, 13514, 8046, 7804, 8310, 7320, 7628, 7474, 7650, 8068, 7782, 13074, 7452, 7408, 8288, 13536, 8662, 7430, 7672, 7694, 7716, 7738, 7760, 13052, 8684, 13558, 8090, 8266, 8134, 13580, 8156, 13030, 8112, 8244, 8222, 8200, 8178, 8706, 13602, 12832, 12854, 12876, 12898, 12920, 12942, 12964, 12986, 13008};

top_fluid_surface[] = {4162, 4166, 4170, 4190, 4174, 4178, 4182, 4186, 1522, 1514, 1518, 4158, 1526, 4194, 1530, 1534, 318, 314, 310, 306, 4198, 4154, 1538, 1510, 4150, 1542, 1506, 322, 302, 4202, 18, 14, 10, 4146, 4206, 1546, 298, 326, 1502, 6, 286, 330, 1498, 4210, 1550, 4142, 294, 290, 4138, 1494, 1490, 1486, 1482, 1478, 4214, 1554, 4218, 4134, 4130, 4126, 4122, 4118, 4114, 4110};
Physical Surface("top_fluid_surface",10) = {top_fluid_surface[]};

bottom_fluid_surface[]= {6990, 7012, 7034, 7056, 7078, 7100, 7122, 7144, 6968, 3886, 3908, 3930, 3952, 3974, 3996, 7166, 6946, 3864, 3534, 3556, 3578, 3600, 4018, 7188, 6924, 3842, 3512, 3402, 3380, 3622, 4040, 7210, 6902, 3820, 3490, 3358, 3336, 3644, 4062, 7232, 6880, 3798, 3468, 3446, 3424, 3666, 4084, 7254, 6858, 3776, 3754, 3732, 3710, 3688, 4106, 7276, 6836, 6814, 6792, 6770, 6748, 6726, 6704, 7298};
Physical Surface("bottom_fluid_surface",11)={bottom_fluid_surface[]};

lateral_surface_1[]={4363, 4979, 5595, 6211, 6827, 4341, 4957, 5573, 6189, 6805, 4319, 4935, 5551, 6167, 6783, 4297, 4913, 5529, 6145, 6761, 4275, 4891, 5507, 6123, 6739, 4253, 4869, 5485, 6101, 6717, 4235, 4851, 5467, 6083, 6699, 4829, 5445, 6061, 6677, 7293};

Physical Surface("lateral_surface_1",12) = {lateral_surface_1[]};

lateral_surface_2[]= {4521, 5137, 5753, 4539, 5155, 5771, 6387, 4561, 5177, 5793, 6409, 7025, 4583, 5199, 5815, 6431, 7047, 4605, 5221, 5837, 6453, 7069, 4627, 5243, 5859, 6475, 7091, 4649, 5265, 5881, 6497, 7113, 4671, 5287, 5903, 6519, 7135, 6369, 6985, 7003};
Physical Surface("lateral_surface_2",13) ={lateral_surface_2[]} ;


lateral_surface_3[]= {6989, 6373, 5757, 5141, 4525, 6967, 6351, 5735, 5119, 4503, 6945, 6329, 5713, 5097, 4481, 6923, 6307, 5691, 5075, 4459, 6901, 6285, 5669, 5053, 4437, 6879, 6263, 5647, 5031, 4415, 6857, 6241, 5625, 5009, 4393, 6831, 6215, 5599, 4983, 4367};
Physical Surface("lateral_surface_3",14)={lateral_surface_3[]};

lateral_surface_4[]= {4675, 5291, 5907, 6523, 7139, 4701, 5317, 5933, 6549, 7165, 4723, 5339, 5955, 6571, 7187, 4745, 5361, 5977, 6593, 7209, 4767, 5383, 5999, 6615, 7231, 4789, 5405, 6021, 6637, 7253, 4811, 5427, 6043, 6659, 7275, 4833, 5449, 6065, 6681, 7297};
Physical Surface("lateral_surface_4",15) = {lateral_surface_4[]};

Physical Surface("fluid_surface",17) = {bottom_fluid_surface[],lateral_surface_1[],lateral_surface_2[],lateral_surface_3[],lateral_surface_4[]};

//Physical Surface("bottom_fluid_surface",11) = {6990, 7012, 7034, 7056, 7078, 7100, 7122, 7144, 6968, 3886, 3908, 3930, 3952, 3974, 3996, 7166, 6946, 3864, 3534, 3556, 3578, 3600, 4018, 7188, 6924, 3842, 3512, 3402, 3380, 3622, 4040, 7210, 6902, 3820, 3490, 3358, 3336, 3644, 4062, 7232, 6880, 3798, 3468, 3446, 3424, 3666, 4084, 7254, 6858, 3776, 3754, 3732, 3710, 3688, 4106, 7276, 6836, 6814, 6792, 6770, 6748, 6726, 6704, 7298};
//Physical Surface("lateral_surface_1",12) = {4363, 4979, 5595, 6211, 6827, 4341, 4957, 5573, 6189, 6805, 4319, 4935, 5551, 6167, 6783, 4297, 4913, 5529, 6145, 6761, 4275, 4891, 5507, 6123, 6739, 4253, 4869, 5485, 6101, 6717, 4235, 4851, 5467, 6083, 6699, 4829, 5445, 6061, 6677, 7293};
//Physical Surface("lateral_surface_2",13) = {4521, 5137, 5753, 4539, 5155, 5771, 6387, 4561, 5177, 5793, 6409, 7025, 4583, 5199, 5815, 6431, 7047, 4605, 5221, 5837, 6453, 7069, 4627, 5243, 5859, 6475, 7091, 4649, 5265, 5881, 6497, 7113, 4671, 5287, 5903, 6519, 7135, 6369, 6985, 7003};
//Physical Surface("lateral_surface_3",14) = {6989, 6373, 5757, 5141, 4525, 6967, 6351, 5735, 5119, 4503, 6945, 6329, 5713, 5097, 4481, 6923, 6307, 5691, 5075, 4459, 6901, 6285, 5669, 5053, 4437, 6879, 6263, 5647, 5031, 4415, 6857, 6241, 5625, 5009, 4393, 6831, 6215, 5599, 4983, 4367};
//Physical Surface("lateral_surface_4",15) = {4675, 5291, 5907, 6523, 7139, 4701, 5317, 5933, 6549, 7165, 4723, 5339, 5955, 6571, 7187, 4745, 5361, 5977, 6593, 7209, 4767, 5383, 5999, 6615, 7231, 4789, 5405, 6021, 6637, 7253, 4811, 5427, 6043, 6659, 7275, 4833, 5449, 6065, 6681, 7297};
Physical Surface("bottom_surface",16) = {13404, 13382, 13360, 13338, 13316, 13294, 13272, 13250, 13228, 13206, 13426, 8552, 8530, 8508, 8486, 8464, 8442, 8420, 8398, 13184, 13448, 8574, 7980, 7958, 7936, 7914, 7892, 7870, 8376, 13162, 13470, 8596, 8002, 7584, 7562, 7540, 7518, 7848, 8354, 13140, 13492, 8618, 8024, 7606, 7364, 7386, 7496, 7826, 8332, 13118, 13514, 8640, 8046, 7628, 7320, 7342, 7474, 7804, 8310, 13096, 13536, 8662, 8068, 7650, 7408, 7430, 7452, 7782, 8288, 13074, 13558, 8684, 8090, 7672, 7694, 7716, 7738, 7760, 8266, 13052, 13580, 8706, 8112, 8134, 8156, 8178, 8200, 8222, 8244, 13030, 13602, 12832, 12854, 12876, 12898, 12920, 12942, 12964, 12986, 13008};
