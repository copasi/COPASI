## COPASI Python Bindings
This directory holds the COPASI bindings for python. They will be build automatically by the main CMake build, if the `ENABLE_PYTHON` option is enabled.

It is also possible to build the python bindings directly, using the supplied `setup.py` file from this directory. The step by step build instructions are as follows. 

* check out COPASI & COPASI-dependencies
* build COPASI dependencies and note the directory the files are placed in
* update the version information of COPASI by running `./gitTools/UpdateCopasiVersion`. 

For example: 

	git clone https://github.com/COPASI/copasi-dependencies
	git clone https://github.com/COPASI/COPASI
	cd COPASI
	./gitTools/UpdateCopasiVersion
	
Now run `setup.py` from the top level directory:

	python copasi/bindings/python/setup.py build

Several environment variables can be used to modify the build: 

* `COPASI_DEP_SRC`: the directory of the `copasi-dependencies` project, defaults to `../copasi-dependencies`
* `COPASI_DEP_DIR`: the build folder of `copasi-dependencies` in case you want to use a previously build set of dependencies defaults to `../copasi_dependencies`
* `COPASI_DEP_DIR_32`: windows binary dependencies directory containing 32bit binaries. defaults to `../win_copasi_dependencies_32/`
* `COPASI_DEP_DIR_64`: windows binary dependencies directory containing 64bit binaries. defaults to `../win_copasi_dependencies_64/`

To change what compiler / cmake generator is used, the following environment variables will be passed on: 

* `CMAKE_CXX_COMPILER`
* `CMAKE_C_COMPILER`
* `CMAKE_LINKER`
* `CMAKE_GENERATOR`
* `SWIG_DIR`
* `SWIG_EXECUTABLE`

