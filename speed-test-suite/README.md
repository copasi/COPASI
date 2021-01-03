# COPASI speed tests

## Aim
This folder contains a series of COPASI files that are useful to test the speed of the 
software objectively. Each file is directed at testing a specific task.

## Usage
Each file encodes an appropriate model and a specific task is marked as executable. Each one 
appends a simple numerical result to a report file: CPU time used. It adds a line with the 
version number for easy referencing (note that in versions prior to 4.24 this will be a blank line). 

To simplify the procedure of running all the tests, and to enhance reproducibility, the BASH 
script *copasispeedtests* can be executed to run all the tests serially. This script needs to 
be adapted to each local system by setting the appropriate paths for the different version 
COPASI executables used. This script takes a considerable time to run --- you've been warned. 
To be sure other processes are not interfering with the measures, you can run these tests in 
mode 1 (as root do *telinit 1*, which switches off networking, then run the script).

To run each test on its own, run them from the command line with the simple 
command:
```bash
/path/CopasiSE modelfile.cps
```
where "/path/" is the path where the COPASI executable to test is located. This will append 
the result to a file named *modelfile.out* (and will create it if needed). Of course, the files 
can also be used to test the speed of CopasiUI (the GUI front-end used by most users).

Some of these tests simply measure how fast files are loaded (or imported), and in those 
cases they need to be profiled using the Linux */usr/bin/time* command in this way:
```bash
CopasiSE | head -n 1 >> modelfile.out
/usr/bin/time -f "%e" -a -o modelfile.out CopasiSE --nologo modelfile.cps
```
This will provide the results in file modelfile.out, preceded by the version number. Note 
that this requires using the *head* command (available in Linux) and the GNU version of 
*time* which needs to be invoked with the full pathname (as opposed to simply *time*, which 
runs a BASH function).

Hopefuly a similar usage can be carried out on the console of OS X, and on modern Windows 
this should probably be run on the Windows Subsystem for Linux (WSL).

## Contributing new tests
If you have some COPASI file that tests a function that is not included here 
and you would like to contribute it, please make sure that the file has:
* metadata identifying you and a brief description in the model comments
* mark the task required as "executable" by setting the appropriate flag in the task page
* use a report template similar to the ones used here (check to see the report definition of one of these files)
* name the file *name_task.cps*, where "task" is the name of the task being probed
* make sure that the report output is directed to *file_task.out*

## Tests
