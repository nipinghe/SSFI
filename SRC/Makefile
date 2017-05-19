#*******************************************************************************************************#
# File:              Makefile                                              
# Author:            hexiang6666                                 | Boris Jeremic,                       #
# Date:              2017-02-27 20:45:30                         | University of California, Davis,95616#
# Description:       #############                               | California                           #
# Rev:               Version 1                                   | jeremic@ucdavis.edu                  #
# Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     #
# * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  # 
#                           Last Modified time: 2017-05-18 00:01:15                                     #              
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

all: test

string_operator: string_operator.cpp
				$(TOO) string_operator.cpp
				$(TOSO) libstring_operator.so string_operator.o
				@cd .. ; mkdir build 
				@mv ./string_operator.o $(BUILD_DIR)
				@mv ./libstring_operator.so $(BUILD_DIR)

ESSINode: ESSINode.cpp
		$(TOO) ESSINode.cpp
		$(TOSO) libESSINode.so ESSINode.o
		@mv ./ESSINode.o $(BUILD_DIR)
		@mv ./libESSINode.so $(BUILD_DIR)

ESSISurface: ESSISurface.cpp
	$(TOO) ESSISurface.cpp
	$(TOSO) libESSISurface.so ESSISurface.o
	@mv ./ESSISurface.o $(BUILD_DIR)
	@mv ./libESSISurface.so $(BUILD_DIR)

FoamNode: FoamNode.cpp
	$(TOO) FoamNode.cpp
	$(TOSO) libFoamNode.so FoamNode.o
	@mv ./FoamNode.o $(BUILD_DIR)
	@mv ./libFoamNode.so $(BUILD_DIR)

FoamSurface: FoamSurface.cpp
	$(TOO) FoamSurface.cpp
	$(TOSO) libFoamSurface.so FoamSurface.o
	@mv ./FoamSurface.o $(BUILD_DIR)
	@mv ./libFoamSurface.so $(BUILD_DIR)


SSFI: SSFI.cpp
	$(TOO) SSFI.cpp
	$(TOSO) libSSFI.so SSFI.o
	@mv ./SSFI.o $(BUILD_DIR)
	@mv ./libSSFI.so $(BUILD_DIR)

test: string_operator ESSINode ESSISurface FoamNode FoamSurface SSFI
	$(TOOUT) test.cpp -o test -L$(BUILD_DIR) -lSSFI -lFoamSurface -lFoamNode -lESSISurface -lESSINode -lstring_operator -Wl,-rpath=$(BUILD_DIR)
	@mv ./test $(BUILD_DIR)



# SSFI: string_operator ESSINode ESSISurface FoamNode FoamSurface
# 	$(TOOUT) SSFI.cpp -o SSFI -L$(BUILD_DIR)  -lFoamSurface -lFoamNode -lESSISurface -lESSINode -lstring_operator -Wl,-rpath=$(BUILD_DIR)
# 	@mv ./SSFI $(BUILD_DIR)
# 	@ln -sf $(BUILD_DIR)/SSFI /usr/local/bin

clean: 
	@cd $(BUILD_DIR); rm -r $(BUILD_DIR)

rebuild: clean test



