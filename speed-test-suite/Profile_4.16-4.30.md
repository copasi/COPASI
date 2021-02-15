# Evolution of COPASI speed in versions 4.16 through to 4.30
## Pedro Mendes
Center for Cell Analysis and Modeling, University of Connecticut School of 
Medicine, February 2021

## Abstract
Recent changes to COPASI source code have resulted in a general performance 
increase. The aim of this work is to quantify the effective speed gains 
achieved in different simulation and analysis tasks. This is done by using 
specific models that challenge these tasks and are especially long to execute. 
This set of models and tasks will be useful for future comparisons to continue 
documenting the evolution of the software performance. COPASI version 4.30 is 
significantly faster than the previous release, 4.28, particularly in the most 
often used tasks: time course integration and steady state solution. It was
also found that relative to version 4.16 (from August 2015) it can be several
fold faster, thus users are urged to update to version 4.30.

## Introduction

## Methods
Each test is contained in a single .cps file that contains a challenging model, 
the specific task marked as executable and a report file defined to capture the 
result (CPU time used, as measured internally by COPASI). The report is defined 
in append mode, which is convenient to run several tests with different versions 
and capture all in the same report file. Most COPASI versions will also output a 
line with their version number (except those prior to 4.24, which lack that 
capability and will simply output an empty line instead). Thus to run the test 
one needs only to issue the following command:
```bash
CopasiSE modelfile.cps
```
This runs the benchmark and appends the results (CPU time in seconds) to the 
*modelfile.out* file.  Note that *CopasiSE* should be the full path of CopasiSE 
of the appropriate  version to test. An example would be 
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
This will provide a similar output as with the previous tasks, namely a first 
line with version number and another line with the time (in seconds) taken to 
process the file.

In order to enhance reproducibility the entire test suite was ran using a single
single BASH script *copasispeedtests* that ran all the benchmarks in sequence. 
This  script has a number of local system dependencies encoded in environment 
variables at the top, which need to be appropriately configured to match the 
local requirements (file paths, etc.). 

## Tests

Each benchmark file is designed to test a single COPASI function, such as 
simulation or analysis task, as well as model loading and parsing SBML. Table 1
lists all the benchmarks and their characteristics.

Table 1. List of tests and their details
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

## Results
This benchmark suite was used to profile the latest COPASI version (4.30) against
a number of recent ones, listed in Table 2. All of the tests were run on a computer 
with a Intel(R) Core(TM) i7-9700 CPU at 3.00 GHz running Slackware64 
Linux and the Linux 64 bit binaries distributed by the COPASI 
project. The full set of results is available in the supplementary file  
[Profile_4.16-4.30.tsv](Profile_4.16-4.30.tsv), below is a summary of the 
important results.

Table 2. List of COPASI versions profiled 
Version | Build | Release date | Observations
-----|-----|----------|--------
4.16 | 104 | Aug 2015 | computations carried out from biochemical model class
4.17 | 135 | Nov 2016 | computations carried out in separate math model class
4.19 | 140 | Jan 2017 | improved performance
4.21 | 166 | Oct 2017 | improved performance of calculations
4.24 | 197 | Jul 2018 | SDE solver (RI5) introduced 
4.25 | 207 | Mar 2019 | improved SDE (RI5) solver, improved RK45 hybrid solver
4.26 | 213 | Jul 2019 | updated convergence criterion to steady state
4.27 | 217 | Sep 2019 |
4.28 | 226 | Jun 2020 | updated steady state convergence criterion
4.29 | 228 | Aug 2020 |
4.30 | 237 | Feb 2021 | just-in-time compiler for mathematical expressions

The most recent version (4.30) proved to be generally faster than all the 
previous ones. A few tasks suffered only small changes in speed since the 
last version (4.29): file loading, time course with SDE integrator, and
time scale separation analysis. Time course integrations with the 
Gillespie algorithm (direct method) and its derivatives (Gibson-Bruck, 
tau-leap, adaptive tau-leap and hybrid methods) increased in speed by a modest 
10-20%. But a number of other tasks have gained considerable speedups:
time course with LSODA (50%), time  course with RADAU5 (30%), steady state 
solution (45-72%), and Lyapunov exponents (88%). Most optimization algorithms 
are also faster, though this seems to be problem-dependent. Those 
with largest improvement were Praxis (48-68%), NL2SOL (44%), truncated Newtwon 
(33-58%), Hooke-Jeeves (30-50%), Nelder-Mead (22-53%), and Levenberg-Marquardt 
(21-47%).

Relative to version 4.16, the last version where the calculations were 
carried out from inside the model class, the speedup is often very large. 
Time course integration with LSODA being 3-fold faster, steady state 
calculations were 3 to 19-fold faster, Hooke-Jeeves optimization was 
5-fold faster, and Levenberg-Marquardt optimization was an impressive
668-fold faster. 
  
## Conclusion

The most recent version of COPASI, 4.30, is significantly faster than the 
previous release, 4.28, particularly in the most often used tasks: time
course integration and steady state solution. Compared with older versions,
which unfortunately are still cited in recent publications, version 4.30 can
be orders of magnitude faster.
 
