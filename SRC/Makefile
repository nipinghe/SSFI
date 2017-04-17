#*******************************************************************************************************#
# File:              Makefile                                              
# Author:            hexiang6666                                 | Boris Jeremic,                       #
# Date:              2017-02-27 20:45:30                         | University of California, Davis,95616#
# Description:       #############                               | California                           #
# Rev:               Version 1                                   | jeremic@ucdavis.edu                  #
# Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     #
# * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  # 
#                           Last Modified time: 2017-03-27 15:56:36                                     #              
#  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * #         
# The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     #
# The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance# 
# with the terms and conditions stipulated in the agreement/contract under which the program have been  #
# supplied.                                                                                             #
#*******************************************************************************************************#
TOO=g++ -std=gnu++11 -fpic -c
TOSO=g++ -shared -o 
TOOUT=g++ -std=gnu++11
BUILD_DIR = $(realpath $(CURDIR))/../build
SOURCE_DIR= $(realpath $(CURDIR))

all: SSFI

string_operator: string_operator.cpp
				$(TOO) string_operator.cpp
				$(TOSO) libstring_operator.so string_operator.o
				@cd .. ; mkdir build 
				@mv ./string_operator.o $(BUILD_DIR)
				@mv ./libstring_operator.so $(BUILD_DIR)

postFoam: postFoam.cpp
		$(TOO) postFoam.cpp
		$(TOSO) libpostFoam.so postFoam.o
		@mv ./postFoam.o $(BUILD_DIR)
		@mv ./libpostFoam.so $(BUILD_DIR)

SSFI: string_operator sl_preprocess postFoam
	$(TOOUT) SSFI.cpp -o SSFI -L$(BUILD_DIR)  -lpostFoam -lstring_operator -Wl,-rpath=$(BUILD_DIR)
	@mv ./SSFI $(BUILD_DIR)
	@sudo ln -sf $(BUILD_DIR)/SSFI /usr/local/bin

sl_preprocess:
	@sudo ln -sf /home/hexiang/git/SSFI/SRC/surface_load_preprocess /usr/local/bin
	@cd /usr/local/bin ; sudo chmod +x surface_load_preprocess


clean: 
	@cd $(BUILD_DIR); rm -r $(BUILD_DIR)

rebuild: clean SSFI






# gmFoamTranslator: gmFoamTranslator.cpp
# 				$(TOO) gmFoamTranslator.cpp
# 				$(TOSO) libgmFoamTranslator.so gmFoamTranslator.o
# 				@mv ./gmFoamTranslator.o $(BUILD_DIR)
# 				@mv ./libgmFoamTranslator.so $(BUILD_DIR)
# boundary_type: boundary_type.cpp
# 				$(TOO) boundary_type.cpp
# 				$(TOSO) libboundary_type.so boundary_type.o
# 				@mv ./boundary_type.o $(BUILD_DIR)
# 				@mv ./libboundary_type.so $(BUILD_DIR)

# # try: string_operator boundary_type gmFoamTranslator mesh_conversion
# # 	$(TOOUT) try.cpp -o try -L$(BUILD_DIR)  -lgmFoamTranslator -lboundary_type -lstring_operator -Wl,-rpath=$(BUILD_DIR)
# # 	@mv ./try $(BUILD_DIR)
# # 	@sudo ln -sf $(BUILD_DIR)/try /usr/local/bin 

# gmFoam: string_operator boundary_type gmFoamTranslator mesh_conversion
# 		$(TOOUT) gmFoam.cpp -o gmFoam -L$(BUILD_DIR)  -lgmFoamTranslator -lboundary_type -lstring_operator -Wl,-rpath=$(BUILD_DIR)
# 		@mv ./gmFoam $(BUILD_DIR)
# 		@sudo ln -sf $(BUILD_DIR)/gmFoam /usr/local/bin 

# clean: 
# 	@cd $(BUILD_DIR); rm -r $(BUILD_DIR)

# rebuild: clean gmFoam

# mesh_conversion: $(SOURCE_DIR)/gmsh_conversion_reserved
# 	@if [ -f "./gmsh_conversion" ]; then rm ./gmsh_conversion; fi
# 	@cp ./gmsh_conversion_reserved ./gmsh_conversion
# 	@echo export SOURCE_DcleaIR=$(PWD)| cat - gmsh_conversion > temp && mv temp gmsh_conversion
# 	@echo '#!/bin/bash' | cat - gmsh_conversion > temp && mv temp gmsh_conversion
# 	@sudo ln -sf $(SOURCE_DIR)/gmsh_conversion /usr/local/bin
# 	@cd /usr/local/bin ; sudo chmod +x gmsh_conversion

# demo: clean string_operator
# 	$(TOOUT) demo.cpp -o demo -L$(BUILD_DIR) -lstring_operator -Wl,-rpath=$(BUILD_DIR)