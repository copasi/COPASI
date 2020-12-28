# Evolution of COPASI speed in versions 4.16 through to 4.30
## Pedro Mendes
Center for Cell Analysis and Modeling, University of Connecticut School of 
Medicine

## Abstract
Recent changes to COPASI source code have resulted in a general performance 
increase. The aim of this work is to quantify the effective speed gains 
achieved in different simulation and analysis tasks. This is done by using 
specific models that challenge these tasks and are especially long to execute. 
This set of models and tasks will be useful for future comparisons to continue 
documenting the evolution of the software performance.

## Introduction

## Methods
Each test is contained in a single .cps file that contains a challenging model, 
the specific task marked as executable and a report file defined to capture the 
result (CPU time used, as measured internally by COPASI). The report is defined 
in append mode, which is convenient to run several tests with different versions 
and capture all in the same report file. Most COPASI versions will also output a 
line with their version number (except those prior to XXXX, which will simply 
output an empty line instead of the version number due to lack of that 
capability). Thus to run the test one needs only to issue the following command:
```bash
CopasiSE modelfile.cps
```
and this appends the results (CPU time in seconds) to the *modelfile.out* file. 
Note that *CopasiSE* should be the full path of CopasiSE of the appropriate 
version to test. An example would be 
*\usr\local\COPASI-4.29.227-Linux-64bit\bin\CopasiSE* to test Build 227.

A few tests target the time taken to load a file, and in that case the 
measurement of time spent has to be carried out externally with the GNU  *time* 
command. Since the BASH shell also contains a *time* command, but which is not 
as flexible, one needs to actually call the command with the full pathname (in 
most Linux systems this is */usr/bin/time*). In those cases the command used to 
test those files should be:
```bash
CopasiSE | head -n 1 >> modelfile.out
/usr/bin/time -f "%e" -a -o modelfile.out CopasiSE --nologo modelfile.cps
```
as this will provide a similar output as with the previous tasks (one line with 
version numnber and another with time taken to process file in seconds).

In order to enhance reproducibility the entire test suite ran for the results 
provided here is encoded in a single BASH script *copasispeedtests*. This 
script has a number of local system dependencies encoded in environment 
variables at the top, which need to be configured for other systems. It includes 
basic instructions in comments.

## Tests

Each file is designed to test a single function, such as simulation or analysis 
task, as well as model loading and parsing SBML. A full list of tests used 
and details of each one are included in Table 1.

Table 1. List of tests and their details
File | Function tested | Observations
-----|-----------------|--------
BCR_load.cps | native file loading | very large file (49 Mb) with 1122 species and 24388 reactions 
EGFR_sbml.xml | SBML import | large model (2.8Mb) with 356 species and 3749 reactions 
IP3CaTissue_gepasi.gps | Gepasi loading | Gepasi file with 192 species and 496 reactions
EGFR_gillespie.cps | Gillespie direct method | 
Pollution_lsoda.cps | LSODA time course | stiff model
Pollution_radau5.cps | RADAU5 time course | stiff model; not all versions have RADAU5 method
Schoeberl_ss.cps | Steady state | ss criterion selected: "distance"
Translation_ss.cps | Steady state | ss criterion selected: "distance and rate"
3enzyme_nl2sol.cps | parameter estimation NL2SOL | task is run 100 times
3enzyme_steepest.cps | parameter estimation steepest descent | task is run 100 times
3enzyme_lm.cps | parameter estimation Levenberg-Marquardt | task is run 100 times
3enzyme_tn.cps | parameter estimation truncated Newton | task is run 100 times
3enzyme_nm.cps | parameter estimation Nelder-Mead | task is run 100 times
3enzyme_praxis.cps | parameter estimation praxis | task is run 100 times
3enzyme_ga.cps | parameter estimation genetic algorithm | task is run 10 times
3enzyme_gasr.cps | parameter estimation genetic algorithm SR | task is run 10 times
3enzyme_ps.cps | parameter estimation particle swarm | task is run 10 times
3enzyme_sres.cps | parameter estimation SRES | task is run 10 times
3enzyme_hj.cps | parameter estimation Hooke-Jeeves | task is run 10 times
3enzyme_ss.cps | parameter estimation scatter search | task is run 10 times
3enzyme_ep.cps | parameter estimation evolutionary programming | task is run 10 times
3enzyme_da.cps | parameter estimation genetic algorithm | task is run 10 times
3enzyme_rs.cps | parameter estimation random search | task is run 10 times
KinMMFit_sa.cps | parameter estimation simulated annealing | task is run 10 times

## Results

## Conclusion

 
