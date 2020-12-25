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
front-end used by most users), whcih should not have much difference from the command line 
version.

If you want to be accurate, you should run these tests one at a time and not have any other 
application running that uses considerable CPU time (*i.e.* close your browser, IM 
application, etc.). If you want to be very accurate, on Linux you could do this in mode 1 
(as root do *telinit 1* which switches off networking)

## Tests
