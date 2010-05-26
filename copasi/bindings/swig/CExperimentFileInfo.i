// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CExperimentFileInfo.i,v $ 
//   $Revision: 1.2.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/26 16:15:01 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

%{

#include "parameterFitting/CExperimentFileInfo.h"

%}

%ignore CExperimentFileInfo::getFirstUnusedSection;
%ignore CExperimentFileInfo::getNextUnusedSection;
%ignore CExperimentFileInfo::adjustForEmptyLines;

%include "parameterFitting/CExperimentFileInfo.h"


