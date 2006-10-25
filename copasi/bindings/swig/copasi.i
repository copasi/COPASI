%module COPASI

%{

#define COPASI_MAIN
#include "copasi.h"
#undef COPASI_MAIN

%}

%include std_string.i
// %include std_vector.i

%include "CVersion.i"
%include "CCopasiDataModel.i"

%init %{

#include "report/CCopasiContainer.h"
// Taken from CopasiSE.cpp

// Create the root container
CCopasiContainer::init();

// Create the global data model
CCopasiDataModel::Global = new CCopasiDataModel;

%}

