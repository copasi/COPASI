// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CLCurve.i,v $ 
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

#include "layout/CLCurve.h"

%}

%ignore CLLineSegment::operator<(const CLLineSegment&) const; 
%ignore CLLineSegment::CLLineSegment(const LineSegment&);
%ignore CLLineSegment::exportToSBMLBezier;
%ignore CLLineSegment::exportToSBMLLineSegment;

%ignore CLCurve::CLCurve(const Curve&);
%ignore CLCurve::exportToSBML;

%include "layout/CLCurve.h"


