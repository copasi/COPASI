## Stochastic TestSuite
This folder contains the wrapper to run the stochastic test suite written by Darren Wilkinson [1]. To run this suite against the stochastic solvers in COPASI you have to: 

1. obtain the suite with sbml files
2. build the stochastic test suite wrapper 
3. run the test suite


### 1) Obtaining the Test Suite SBML files
They can be obtained by cloning the test suite repository <https://github.com/darrenjw/dsmts> and running `make sbml`. For this to work you will have to have the `csh` installed, as well as the `python-libsbml` package. So after: 

	sudo apt-get install csh
	pip install python-libsbml 

you should be fine to run: 

	git clone https://github.com/darrenjw/dsmts
	cd dsmts
	chmod +x build.csh
	make sbml

after this you should find the test-cases in the form of `dsmts-xxx-yy.xml` in the same folder.

*NOTE*: At this point remember the full path to the test suite directory, as it will be needed later.  


### 2) Build the stochastic test suite wrapper
The task of the test suite [wrapper file](copasi_wrapper.cpp) is to import the SBML file, convert it to COPASI file and generate the necessary output report. This wrapper is not built by default, so you will have to enable the cmake option `-DBUILD_STOCHASTIC_TESTSUITE=ON` when building COPASI. For more information on compiling COPASI see the readme file in the [root folder](../README.md).

After building the test suite wrapper, you should find the executable `stochastic-testsuite` in the build folder `stochastic-testsuite`. And you are ready to run the test suite.

*NOTE*: At this point remember the full path to the executable, as it will be needed in the next step.  

### 3) Running the test suite

To run the test suite change into the `stochastic-testsuite` source folder (i.e where this readme file is located). You will find a shell script `run.sh` as well as python scripts for comparing mean and variance. If you run the script it displays all the needed arguments to run it: 


	Usage: run.sh WRAPPER TESTSDIR [MODEL_LIST_FILE|MODEL] METHOD NUM_REPEATS

with the following arguments:
 
 * `WRAPPER`: this is the full path to the executable of the test suite wrapper generated in 2) above.
 * `TESTSDIR`: this is the full path to the DSMTS test suite directory from 1)
 * `MODEL_LIST_FILE|MODEL` either a file containing the names of the models to run like `copasi-model-list` or the `model-list` file in the test suite directory. Or it could be a specific test like `dsmts-001-02`. 
 * `METHOD`: this allows to select for the stochastic solver that you want to run the test suite for. This can be one out of: 
	 * `stochastic`:  an implementation using the direct method
	 * `directMethod`: an implementation of Gibson + Bruck
	 * `adaptiveSA`: an implementation of Adaptive SSA/τ-Leap
	 * `tauLeap`: τ-Leap implementation
	 * `LSODA`: a Hybrid LSODA implementation
	 * `HybridODE45`: a hybrid implementation ocmbining DSA and RK 45
 * `NUM_REPEATS`: is the number of repetitions that each test is supposed to be run for. For some tests `2000` might be good enough, for others hundreds of thousands might be needed. 

For example: 

	./run.sh ../../build_copasi/stochastic-testsuite/stochastic-testsuite ~/Development/dsmts dsmts-001-02 "stochastic" 2000

runs the: 

* wrapper from the specified build folder `../../build_copasi/stochastic-testsuite/stochastic-testsuite`
* uses the sbml test files from `~/Development/dsmts`
* runs test `dsmts-001-02` 
* using the direct method implemented in COPASI
* for `2000` runs

After the run in case of success, you will get a message like: 

	./run.sh ../../build_copasi/stochastic-testsuite/stochastic-testsuite ~/Development/dsmts dsmts-001-02 "stochastic" 2000
	../../build_copasi/stochastic-testsuite/stochastic-testsuite stochastic "/root/Development/dsmts/dsmts-001-02.xml" 50 50 2000 "/root/Development/dsmts/dsmts-001-02.RESULT" X
	time: 1.28 seconds
	dsmts-001-02 passed
	Time used for simulations: 1.28 seconds

or in case of a failure: 

	./run.sh ../../build_copasi/stochastic-testsuite/stochastic-testsuite ~/Development/dsmts dsmts-001-02 "directMethod" 2000
	../../build_copasi/stochastic-testsuite/stochastic-testsuite directMethod "/root/Development/dsmts/dsmts-001-02.xml" 50 50 2000 "/root/Development/dsmts/dsmts-001-02.RESULT" X
	time: 1.24 seconds
	ERROR at /root/Development/dsmts/dsmts-001-02-mean.RESULT (41, 1): Mean: 68.678339, RefMean: 67.032000, Tol: 1.445118.
	ERROR at /root/Development/dsmts/dsmts-001-02-mean.RESULT (42, 1): Mean: 68.077039, RefMean: 66.365030, Tol: 1.452383.
	ERROR at /root/Development/dsmts/dsmts-001-02-mean.RESULT (43, 1): Mean: 67.394697, RefMean: 65.704680, Tol: 1.459256.
	ERROR at /root/Development/dsmts/dsmts-001-02-mean.RESULT (44, 1): Mean: 66.688844, RefMean: 65.050910, Tol: 1.465752.
	dsmts-001-02 failed
	Time used for simulations: 1.24 seconds

in the case of a failure you would either re-run the test case (the occasional failure is expected after all) and/or increase the number of repeats. 

### References

[1] Thomas W. Evans, Colin S. Gillespie, Darren J. Wilkinson, The SBML discrete stochastic models test suite, Bioinformatics, Volume 24, Issue 2, 15 January 2008, Pages 285–286, <https://doi.org/10.1093/bioinformatics/btm566>
