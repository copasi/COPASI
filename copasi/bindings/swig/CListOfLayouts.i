// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CListOfLayouts.i,v $ 
//   $Revision: 1.1.2.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/10 15:33:43 $ 
// End CVS Header 


// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%template(LayoutVector) CCopasiVector<CLayout>;
typedef CCopasiVector<CLayout> LayoutVector;

%{

#include "layout/CListOfLayouts.h"

%}

%ignore CListOfLayouts::exportToSBML;

%include "layout/CListOfLayouts.h"


