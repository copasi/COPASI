#!/bin/bash
# Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 


set -e
set -x

if [[ "$(uname -s)" == 'Darwin' ]]; then
    if which pyenv > /dev/null; then
        eval "$(pyenv init -)"
    fi
    pyenv activate conan
fi

git fetch --unshallow
mkdir build
cd build
conan install .. --build=missing
cmake -DBUILD_GUI=OFF -DCMAKE_CXX_FLAGS=-D_GLIBCXX_USE_CXX11_ABI=0 ../

if [[ "$OSTYPE" == "linux-gnu" ]]; then
    build-wrapper-linux-x86-64 --out-dir ../bw-output make CopasiSE
    #ctest
    cd ..
    sonar-scanner -Dproject.settings=./.sonarcloud.properties
else 
    cmake --build . --config Release --target CopasiSE
    #ctest
fi

