
# Default Makefile Variables 
NP=4 

all: 
	 essi -f /home/hexiang/git/SSFI/tutorial/test_case/box/box_ESSI_Simulation/box_analysis.fei

serial: 
	 essi -f /home/hexiang/git/SSFI/tutorial/test_case/box/box_ESSI_Simulation/box_analysis.fei

parallel: 
	 mpirun -np ${NP} pessi -f /home/hexiang/git/SSFI/tutorial/test_case/box/box_ESSI_Simulation/box_analysis.fei

clean: 
	 rm *.feioutput 

