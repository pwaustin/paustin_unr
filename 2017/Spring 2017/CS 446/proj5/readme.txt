Compile with the included makefile and run with the Sim05 executable and a .conf file, as per previous projects. 

The program assumes that config file will contain a Processor Quantum Number value and a CPU scheduling code (FIFO, PS, SJF are supported in this project, anything else will throw an error).

Scheduling is implemented by sorting the vector of event objects in the data class; see the new schedule function in the data class for implementation details.

FIFO: runs the simulation as per the previous project.
PS: runs all I and O processes first, in descending order of quantity of tasks, followed by all other tasks in their original order.
SJF: runs processes in ascending order of quantity of tasks.

NOTE: project tested on ECC ubuntu install, NOT the nomachine.
