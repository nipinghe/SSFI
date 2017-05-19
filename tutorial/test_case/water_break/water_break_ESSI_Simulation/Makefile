
# Default Makefile Variables 
NP=4 

all: 
	 essi -f /home/hexiang/git/SSFI/water_break/water_break_ESSI_Simulation/water_break_analysis.fei

serial: 
	 essi -f /home/hexiang/git/SSFI/water_break/water_break_ESSI_Simulation/water_break_analysis.fei

parallel: 
	 mpirun -np ${NP} pessi -f /home/hexiang/git/SSFI/water_break/water_break_ESSI_Simulation/water_break_analysis.fei

clean: 
	 rm *.feioutput 

