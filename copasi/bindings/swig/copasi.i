%module COPASI

%{

#define COPASI_MAIN
#include "copasi.h"
#undef COPASI_MAIN

%}

%import "copasi.h"

%include std_string.i
%include std_vector.i

%include "CCopasiObjectName.i"
%include "CCopasiObject.i"
%include "CCopasiContainer.i"
%include "CCopasiVector.i"
%include "CVersion.i"
%include "CCopasiTask.i"
%include "CCopasiDataModel.i"

%init %{

#include "report/CCopasiContainer.h"
// Taken from CopasiSE.cpp

// Create the root container
CCopasiContainer::init();

// Create the global data model
CCopasiDataModel::Global = new CCopasiDataModel;

%}

