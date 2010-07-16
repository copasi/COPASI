// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CLGraphicalObject.i,v $ 
//   $Revision: 1.2 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:26 $ 
// End CVS Header 

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

%include "layout/CLGraphicalObject.h"


