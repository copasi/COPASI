## COPASI: biochemical network simulator

COPASI is a software application for simulation and analysis of biochemical 
networks and their dynamics. COPASI is a stand-alone program that supports 
models in the [SBML standard](http://www.sbml.org/) and can simulate their 
behavior using ODEs or Gillespie's stochastic simulation algorithm; arbitrary 
discrete events can be included in such simulations.

COPASI carries out several analyses of the network and its dynamics and has 
extensive support for parameter estimation and optimization. COPASI provides 
means to visualize data in customizable plots, histograms and animations of 
network diagrams. 
([list of features](http://www.copasi.org/tiki-index.php?page=FeatureList)). 

Follow us on [Google+](https://plus.google.com/103737270060170895963) or 
[Twitter](https://twitter.com/COPASI_software). 

### Download COPASI
Precompiled versions of COPASI are available for all operating systems on the 
[COPASI Homepage](http://www.copasi.org/tiki-index.php?page=downloadnoncommercial).

### Building COPASI
COPASI's sources are available from our [github repository](https://github.com/copasi/COPASI). 
These sources are written in standard C++ and will compile on Linux, OS X and Windows. 

#### Dependencies
To start compiling COPASI we recommend to use the [copasi-dependencies](https://github.com/copasi/copasi-dependencies) package.The dependency package compiles all the dependencies 
necessary for COPASI, they include `clapack`, `cppunit`, `expat`, `raptor` 
`libSEDML`, `libsbml`, `SBW` as well as the Qt libraries `QWT`, `QWT3D` and 
the `Qt MML widget`. Instructions for building the dependencies are described 
here: 

* [General Instructions](https://github.com/copasi/copasi-dependencies/blob/master/readme.md)  
* [Linux build instructions](https://github.com/copasi/copasi-dependencies/blob/master/readme_linux.md)

#### Compiling COPASI
Once the dependencies have been built, COPASI is easily compiled using 
[CMake](http://www.cmake.org):

	git clone https://github.com/copasi/COPASI
	mkdir build_copasi
	cd build_copasi
	cmake -DBUILD_GUI=OFF -DCMAKE_INSTALL_PREFIX=~/copasi -DCOPASI_DEPENDENCY_DIR=../copasi-dependencies/bin ../COPASI
	make
	make install 

In the above `../copasi-dependencies` is the location of the compiled 
copasi-dependencies project. The option `BUILD_GUI=OFF` builds only the 
command line version of COPASI (aka `CopasiSE`). To build the graphical 
frontend (aka `CopasiUI`), and having Qt 4 installed, the option would 
need to be `BUILD_GUI=ON`. The option `CMAKE_INSTALL_PREFIX=~/copasi`
 specifies, that COPASI ought to be installed in the current users home 
directory in a subfolder `copasi`. 

There are many more compile options available, options for building the 
language bindings as well as options to enable some experimental features that
are not yet available in the stable builds that are [released publicly](http://www.copasi.org/tiki-index.php?page=downloadnoncommercial). To view the complete set of options, start the 
graphical cmake frontend in the continuing from the above command this would
be done with:

	cmake-gui ../COPASI


### Feedback
To submit feedback, or bug reports, please use the [COPASI Tracker](http://www.copasi.org/tracker/), 
or our [mailing list](https://groups.google.com/forum/#!forum/copasi-user-forum). 

### License
The packages available on this page are provided under the 
[Artistic License 2.0](http://www.copasi.org/tiki-index.php?page=ArtisticLicense), 
which is an [OSI](http://www.opensource.org/) approved license. This license 
allows non-commercial and commercial use free of charge.
