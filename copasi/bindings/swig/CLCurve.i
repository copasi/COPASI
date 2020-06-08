// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 


%{

#include "copasi/layout/CLCurve.h"

%}

%ignore CLLineSegment::operator<(const CLLineSegment&) const; 
%ignore CLLineSegment::CLLineSegment(const LineSegment&);
%ignore CLLineSegment::exportToSBMLBezier;
%ignore CLLineSegment::exportToSBMLLineSegment;
%ignore CLLineSegment::getStart() const;
%ignore CLLineSegment::getEnd() const;
%ignore CLLineSegment::getBase1() const;
%ignore CLLineSegment::getBase2() const;

%ignore CLCurve::getSegmentAt(size_t) const;
%ignore CLCurve::addCurveSegment(CLLineSegment const *);
%ignore CLCurve::CLCurve(const Curve&);
%ignore CLCurve::exportToSBML;

%include "copasi/layout/CLCurve.h"


