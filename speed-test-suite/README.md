# COPASI speed tests

## Aim
This folder contains a series of COPASI files that are useful to test the speed of the 
software objectively. Each file is directed at testing a specific task.

## Usage
Each file encodes an appropriate model and a specific task is marked as executable. Each one 
appends a simple numerical result to a report file: CPU time used. It adds a line with the 
version number for easy referencing (note that this will be a blank line in versions prior 
to XXXX, you may have to edit the report file to identify them properly). 

The typical way to use these files is to run them from the command line with the simple 
command:
```bash
CopasiSE modelfile.cps
```
This will append the result to a file named *modelfile.out* (it will create it if not 
existant yet). To use different versions, you would call this with different CopasiSE 
versions. Of course, the files can also be used to test the speed of CopasiUI (the GUI 
front-end used by most users), which should not have much difference from the command line 
version.

If you want to be accurate, you should run these tests one at a time and not have any other 
application running that uses considerable CPU time (*i.e.* close your browser, IM 
application, etc.). If you want to be very accurate, on Linux you could do this in mode 1 
(as root do *telinit 1* which switches off networking)

Some tests are directed simply at how fast the files are loaded (or imported), and in this 
case they need to be profiled using the Linux */usr/bin/time* command in this way:
```bash
CopasiSE | head -n 1 >> modelfile.out
/usr/bin/time -f "%e" -a -o modelfile.out CopasiSE --nologo modelfile.cps
```
This will provide the results in file modelfile.out, preceded by the version number. Note 
that this requires using the *head* command (available in Linux) and the GNU version of 
*time* which needs to be invoked with the full pathname (as opposed to simply *time* which 
runs a BASH function).

Hopefuly a similar usage can be carried out on the console of OS X, and on modern Windows 
this should probably be run on the Windows Subsystem for Linux (WSL).

To simplify the procedure of running all the tests, and to enhance reproducibility, the BASH 
script *copasispeedtests* encodes running all the tests. This will need to be adapted to 
each local system (*e.g.* the locations of where the different version COPASI executables 
reside).

## Tests
