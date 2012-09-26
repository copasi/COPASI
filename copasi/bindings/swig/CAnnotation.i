// Begin git Header 
//   Commit: 28d5663ff3fc99993d3b249dec626841cb5247ab 
//   Author: Frank T. Bergmann fbergman@caltech.edu 
//   Date: 2012-08-29 10:43:00 +0200 
// End git Header 


// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%ignore CAnnotation::operator==;
%ignore CAnnotation::getUnsupportedAnnotations() const;

%{

#include "model/CAnnotation.h"  
  
%}


%include "model/CAnnotation.h"



