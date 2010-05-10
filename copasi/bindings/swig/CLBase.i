// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CLBase.i,v $ 
//   $Revision: 1.1.2.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/10 15:33:43 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

#include "layout/CLBase.h"

%}

%ignore CLBase::CLBase(const SBase&);

%ignore CLPoint::getX() const;
%ignore CLPoint::getY() const;
%ignore CLPoint::CLPoint(const Point&);
%ignore CLPoint::getSBMLPoint() const;
%ignore CLPoint::operator<(const CLPoint&) const;

%ignore CLDimensions::getHeight() const;
%ignore CLDimensions::getWidth() const;
%ignore CLDimensions::CLDimensions(const Dimensions&);
%ignore CLDimensions::getSBMLDimensions() const;

%ignore CLBoundingBox::getPosition() const;
%ignore CLBoundingBox::getDimensions() const;
%ignore CLBoundingBox::CLBoundingBox(const BoundingBox&);
%ignore CLBoundingBox::getSBMLBoundingBox() const;


%include "layout/CLBase.h"


