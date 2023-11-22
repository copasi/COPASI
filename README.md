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
([list of features](http://copasi.org/Support/Features/)). 

Follow us on [Mastodon](https://fosstodon.org/@copasi). 

### Download COPASI
Precompiled versions of COPASI are available for all operating systems on the 
[COPASI Homepage](http://copasi.org/Download/).

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

#### Compiling COPASI
Once the dependencies have been built, COPASI is easily compiled using 
[CMake](http://www.cmake.org):

	git clone https://github.com/copasi/COPASI
	mkdir build_copasi
	cd build_copasi
	cmake -DBUILD_GUI=OFF -DCMAKE_INSTALL_PREFIX=~/copasi -DCOPASI_DEPENDENCY_DIR=../copasi-dependencies/bin ../COPASI
	make
	make install 

In the above `../copasi-dependencies/bin` is the location of the build folder of the compiled 
copasi-dependencies. The option `BUILD_GUI=OFF` builds only the 
command line version of COPASI (aka `CopasiSE`). To build the graphical 
frontend (aka `CopasiUI`), and having Qt 4 or 5 installed, the option would 
need to be `BUILD_GUI=ON`. In that case you'd additionally provide an option `SELECT_QT=Qt5` (or `SELECT_QT=Qt4`) for COPASI to look for the Qt libraries. (To help finding the Qt version you selected, you should specify the `Qt5_DIR=<dir>` variable to point to the `lib/cmake/Qt5` directory of the Qt5 installation. Alternatively for Qt4 you can set the `QT_DIR=<dir>` variable to point to your Qt4 installation.) 

The option `CMAKE_INSTALL_PREFIX=~/copasi` specifies, that COPASI ought to be installed in the current users home directory in a subfolder `copasi`. The path `../COPASI` is the source directory of COPASI that has been created by the git clone command in the first statement.  

There are many more compile options available, options for building the 
language bindings as well as options to enable some experimental features that
are not yet available in the stable builds that are [released publicly](http://copasi.org/Download/). To view the complete set of options, start the 
graphical cmake frontend in the continuing from the above command this would
be done with:

	cmake-gui ../COPASI

### The correct version number
The COPASI version number you will see in your application is generated during the build process. For this to work we install git hooks, so it gets updated automatically, by running: 

	./gitTools/initTools

once from the COPASI source dir (which will set up the paths to astyle, gawk, dos2unix and wget). This helps us keep commits formatted correctly from different operating systems. Once that is set up, a call to: 

	 ./gitTools/UpdateCopasiVersion

will update the `<copasi/CopasiVersion.h>` to match that of the selected branch. That   

### Linking a C++ program against the COPASI API
To link your own program against the COPASI C++ API you would first build COPASI as described above however, with an additional CMake option `-DCOPASI_INSTALL_C_API=ON`. Thus the full configure / make / install commands from above would be: 


	git clone https://github.com/copasi/COPASI
	mkdir build_copasi
	cd build_copasi
	cmake -DCOPASI_INSTALL_C_API=ON -DBUILD_GUI=OFF -DCMAKE_INSTALL_PREFIX=~/copasi -DCOPASI_DEPENDENCY_DIR=../copasi-dependencies/bin ../COPASI
	make
	make install 

Now additionally to the COPASI SE executable being built, also all COPASI header files and the COPASI (static) library will be installed into the `CMAKE_INSTALL_PREFIX` (thus in the example above header files will end up in `~/copasi/include` and libraries in `~/copasi/lib`). We also export a CMAKE configuration that you can import for your own CMAKE projects. That way you only need to add a line like: 

	find_package(libCOPASISE-static CONFIG REQUIRED)

to the `CMakeLists.txt` file of your project. And later link your project against `libCOPASISE-static`. This will then automatically link against all the libraries that the COPASISE library was linked against. In order for CMake to find the configuration you would either have to include the `lib/cmake` folder of your install prefix into your projects `CMAKE_PREFIX_PATH` variable or specify an option `libCOPASISE-static_DIR` with the folder of the config file when configuring your project. For the prefix specified above this would be: 

	-DlibCOPASISE-static_DIR=~/copasi/lib/cmake

The gist of a complete example [CMakeList.txt](https://gist.github.com/fbergmann/5eb625a23cb17eb8463b8a6365885fd1) is also available.   

### Feedback
To submit feedback, or bug reports, please use the [COPASI Tracker](http://tracker.copasi.org), 
or our [mailing list](https://groups.google.com/forum/#!forum/copasi-user-forum). 

### License
The packages available on this page are provided under the 
[Artistic License 2.0](http://copasi.org/Download/License/), 
which is an [OSI](http://www.opensource.org/) approved license. This license 
allows non-commercial and commercial use free of charge.

## Git maintenance

### Release branches:
 - Naming: `Version-$major.$minor`

#### Start release branch 
To create a new release branch check out the starting branch which is normally develop:
```
git checkout develop
git flow release start <name>
git push origin
```

#### Finish release branch 
To finish a release:
```
git checkout release/<name>
git flow release finish <name>
git push
```

#### Tagging snapshots
In order to tag the latest commit in the current branch as a snapshot execute:
```
gitTools/UpdateCopasiVersion --registerBuild
```
The above command will automatically select the next tag of the format: `Build-N` and push the tag to the upstream repository.

### Building API documentation
To build the API documentation doxygen can be used. here the command line for generating the documentation after a git 
checkout: 

```bash
PROJECT_NUMBER=4.40.278 doxygen -x COPASI.doxyfile > Doxyfile && doxygen
```

This will fix the version number of the generated files to the one specified in the environment variable and 
generate a local `Doxygen` file with which it runs doxygen.  The resulting documentation is placed in `./doc/html`.

To update it on the copasi.github.io project you'd run from the `copasi.github.io` folder: 

```bash
pushd ./static/API_Documentation/
rm -rf ./*
git commit -a -m " - removed old documentation"
cp -R ../../../COPASI/doc/html/* .
git add . 
git commit -a -m " - add documentation for COPASI 4.40.278"
git push
```