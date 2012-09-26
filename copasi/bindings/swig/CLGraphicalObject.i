// Begin git Header 
//   Commit: 28d5663ff3fc99993d3b249dec626841cb5247ab 
//   Author: Frank T. Bergmann fbergman@caltech.edu 
//   Date: 2012-08-29 10:43:00 +0200 
// End git Header 


// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

#include "layout/CLGraphicalObject.h"

%}

%ignore operator<<;
%ignore CLGraphicalObject::getBoundingBox() const;
%ignore CLGraphicalObject::operator= (const CLGraphicalObject&);
%ignore CLGraphicalObject::CLGraphicalObject(const GraphicalObject & , std::map<std::string, std::string> & , const CCopasiContainer * pParent = NULL);
%ignore CLGraphicalObject::exportToSBML;
%ignore CLGraphicalObject::print;

// suppress warnings on multiple inheritance
%warnfilter(813) CLGraphicalObject;

%include "layout/CLGraphicalObject.h"


