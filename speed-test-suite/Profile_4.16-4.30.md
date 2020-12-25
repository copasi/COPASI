# Evolution of COPASI speed in versions 4.16 through to 4.30
## Pedro Mendes
Center for Cell Analysis and Modeling, University of Connecticut School of Medicine

## Abstract
Recent changes to COPASI source code have resulted in a general performance increase. The 
aim of this work is to quantify the effective speed gains achieved in different simulation 
and analysis tasks. This is done by using specific models that challenge these tasks and are 
especially long to execute. This set of models and tasks will be useful for future 
comparisons to continue documenting the evolution of the software performance.

## Introduction

## Methods
Each test is contained in a single .cps file that contains a challenging model, the 
specific task marked as executable and a report file defined to capture the result (CPU time 
used, as measured internally by COPASI). The report is defined in append mode, which is 
convenient to run several tests with different versions and capture all in the same report 
file. Most COPASI versions will also output a line with their version number (except those 
prior to XXXX, which will simply output an empty line instead of the version number due to 
lack of that capability). Thus to run the test one needs only to issue the following 
command:
```bash
CopasiSE modelfile.cps
```
and this appends the results (CPU time in seconds) to the *modelfile.out* file. Note that 
*CopasiSE* should be the full path of CopasiSE of the appropriate version to test. An 
example would be *\usr\local\COPASI-4.29.227-Linux-64bit\bin\CopasiSE* to test Build 227.

A few tests target the time taken to load a file, and in that case the measurement of time spent 
has to be carried out externally with the GNU  *time* command. Since the BASH shell also 
contains a *time* command, but which is not as flexible, one needs to actually call the 
command with the full pathname (in most Linux systems this is */usr/bin/time*). In those 
cases the command used to test those files should be:
```bash
CopasiSE --version >> modelfile.out
/usr/bin/time -f "%e" -a -o modelfile.out CopasiSE modelfile.cps
```
as this will provide a similar output as with the previous tasks (one line with version 
numnber and another with time taken to process file in seconds).

## Models

## Results

## Conclusion

 
