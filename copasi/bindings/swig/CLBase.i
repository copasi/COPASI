// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CLBase.i,v $ 
//   $Revision: 1.1.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/10 14:22:07 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

#include "layout/CLBase.h"

%}

%ignore CLPoint::getX() const;
%ignore CLPoint::getY() const;
%ignore CLDimensions::getHeight() const;
%ignore CLDimensions::getWidth() const;
%ignore CLBoundingBox::getPosition() const;
%ignore CLBoundingBox::getDimensions() const;
%ignore CLPoint::operator<(const CLPoint&) const;

%include "layout/CLBase.h"


