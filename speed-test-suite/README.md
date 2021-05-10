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
COPASI executables used. This script takes a considerable time to run (you've been warned!). 
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
/path/CopasiSE | head -n 1 >> modelfile.out
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

## Results
Articles describing the results of profiling different COPASI versions will be included here. 
Currently the file *Profile_4.16-4.30.md* contains the results of profiling versions 4.16 to 4.30.

The results of the tests are all written out to files with extension *.out*. To facilitate 
summarizing the results a PERL script is provided; *results2tsv.pl* reads all *.out* files and writes 
them to a tab-separated file, with one test per line, with each numeric result in a new column. 
Note that while this script accounts for missing data it does not identify the special cases where
some older versions are not run (e.g. with tests for SDE and RADAU5 algorithms). In those 
cases the user will have to manually shift the columns appropriately.


## List of tests
File | Function tested | Observations
-----|-----------------|--------
Pollution_lsoda.cps | LSODA time course | stiff model
BCR_load.cps | native file loading | very large file (49 Mb) with 1122 species and 24388 reactions 
EGFR_sbml.xml | SBML import | large model (2.8Mb) with 356 species and 3749 reactions 
IP3CaTissue_gepasi.gps | Gepasi loading | Gepasi file with 192 species and 496 reactions
EGFR_gillespie.cps | Gillespie direct method time course | 
multistate_gillespie.cps | Gillespie direct method  time course| 
multistate_gb.cps | Gibson-Bruck time course | 
Vilar2002_tauleap.cps | tau-leap time course | noise-driven model, long time course
Vilar2002_adaptivetauleap.cps | adaptive tau-leap time course | noise-driven model, long time course
HuangFerrel_hydrib-rk.cps | hybrid (Runge-Kutta) time course | 
HuangFerrel_hydrib-lsoda.cps | hybrid (LSODA) time course | 
Dacheaux2017_hybrid-rk45.cps | hybrid (RK45) time course | two reactions deterministic
ERBB-RAS-AKT_ss.cps | steady state | ss criterion selected: "distance and rate" 1392 species 2686 reactions
Schoeberl_ss.cps | steady state | ss criterion selected: "distance"
Translation_ss.cps | steady state | ss criterion selected: "distance and rate"
BIOMOD70_efm.cps | elementary flux modes | model with 105 EFMs
Ecoli_efm.cps | elementary flux modes | model with 15090 EFMs
Ecoli_mca.cps | metabolic control analysis | model with 77 species and 68 reactions
Decroly_lyap.cps | Lyapunov exponents | chaotic model
CoopSF4_001_tssa-ildm.cps | time scale separation analysis ILDM | model with 100 species and 200 reactions
CoopSF4_001_tssa-csp.cps | time scale separation analysis CSP | model with 100 species and 200 reactions
3enzyme_lna.cps | linear noise approximation | 
HuangFerrel_lna.cps | linear noise approximation | 
JumboSF001_lna.cps | linear noise approximation | model with 1000 species and 2000 reactions
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
Colville_opt-tn.cps | optimization truncated Newton | Long, narrow ridge function, runs 100 times
Colville_opt-sd.cps | optimization steepest descent | Long, narrow ridge function, runs 100 times
Colville_opt-sd.cps | optimization praxis | Long, narrow ridge function, runs 100 times
Colville_opt-gasr.cps | optimization genetic algorithm SR | Long, narrow ridge function, runs 100 times
Rosenbrock10_opt-lm.cps | optimization Levenberg-Marquardt | 10D function with narrow ridge, runs 100 times
Rosenbrock10_opt-nm.cps | optimization Nelder-Mead | 10D function with narrow ridge, runs 100 times
Rosenbrock10_opt-hj.cps | optimization Hooke-Jeeves | 10D function with narrow ridge, runs 100 times
Rosenbrock10_opt-ss.cps | optimization scatter search | 10D function with narrow ridge, runs 100 times
Weierstrass_opt-de.cps | optimization differential evolution | near-fractal continuous non-differentiable function, runs 100 times
Weierstrass_opt-ep.cps | optimization evolutionionary programming | near-fractal continuous non-differentiable function, runs 100 times
Weierstrass_opt-sres.cps | optimization SRES | near-fractal continuous non-differentiable function, runs 100 times
Weierstrass_opt-sa.cps | optimization simulated annealing | near-fractal continuous non-differentiable function, runs 100 times
SchafferF7-10_opt-rs.cps | optimization random search | 10D function with concentric local minima, runs 100 times
SchafferF7-10_opt-ga.cps | optimization genetic algorithm | 10D function with concentric local minima, runs 100 times
SchafferF7-10_opt-ps.cps | optimization particle swarm | 10D function with concentric local minima, runs 100 times
Pollution_radau5.cps | RADAU5 time course | stiff model (Build 213 onwards)
HuangFerrel_sde.cps | RI5 time course (SDE) | (Build 226 onwards)
