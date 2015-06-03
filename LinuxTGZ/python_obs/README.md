## python obs
This directory contains the build scripts for the python-copasi Open Build Service project, that is currently kept here: 

<https://build.opensuse.org/package/show/home:fbergman:COPASI/python-copasi>

## Creating a package for python-copasi

### 32bit Linux
1. checkout and build the [copasi-dependencies](https://github.com/copasi/copasi-dependencies) project
2. create an archive of the bin directory called `dependencies-32.tar.gz` (the contents of the archive should be the `bin`, `lib`, `include` and `share` directories i.e. no additional subdirectories.)
3. build COPASI regularly, configured with python and using the [copasi-dependencies](https://github.com/copasi/copasi-dependencies) project. 
4. call `createSE.sh` with the build dir as argument, in order to create an archive `se-32.tar.gz`
5. copy those two archives onto some share, so that you can get onto those files later. Below this will be called the `dependency dir`. 

### 64bit Linux
1. checkout and build the [copasi-dependencies](https://github.com/copasi/copasi-dependencies) project
2. create an archive of the bin directory called `dependencies-64.tar.gz` (the contents of the archive should be the `bin`, `lib`, `include` and `share` directories i.e. no additional subdirectories.)
3. build COPASI regularly, configured with python and using the [copasi-dependencies](https://github.com/copasi/copasi-dependencies) project. 
4. call `createSE.sh` with the build dir as argument, in order to create an archive `se-64.tar.gz`
5. copy those two archives onto some share, so that you can get onto those files later. Below this will be called the `dependency dir`. 

### creating the source archive 

At this point you should be on either the 32 bit or 64 bit machine, with access to the `dependency dir` that contains the four files:

* `dependencies-32.tar.gz`
* `dependencies-64.tar.gz`
* `se-32.tar.gz`
* `se-64.tar.gz`

now you invoke `create-package.sh` with four arguments: 

1. the version to create (defaults to 4.14.92)
2. the source dir (defaults to `../COPASI`)
3. the binary dir (defaults to `../package`)
4. the `dependency dir` (defaults to `/mnt/hgfs/share`)

This will produce a file called `python-copasi-<VERSION>.tar.gz` that is ready to be uploaded to OBS. 

## Triggering an OBS build
To get the build updated, you now go ahead and log into OBS, at:

<https://build.opensuse.org/package/show/home:fbergman:COPASI/python-copasi>

and modify as follows: 

* upload the `python-copasi-<VERSION>.tar.gz` file
* edit the `debian.changelog` with the latest update
* edit the `python-copasi.changes` with the latest update
* edit the `python-copasi.dsc` updating the python-copasi-<VERSION>.tar.gz information as well as the `VERSION: ` field
* edit the `python-copasi.spec` updating only the `VERSION:`field

at this point obs should have triggered a full rebuild and the new file will be created. Any errors should be logged in the tracker. 