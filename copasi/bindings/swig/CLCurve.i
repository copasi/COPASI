// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
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
%ignore CLLineSegment::getStart() const;
%ignore CLLineSegment::getEnd() const;
%ignore CLLineSegment::getBase1() const;
%ignore CLLineSegment::getBase2() const;

%ignore CLCurve::getSegmentAt(size_t) const;
%ignore CLCurve::addCurveSegment(CLLineSegment const *);
%ignore CLCurve::CLCurve(const Curve&);
%ignore CLCurve::exportToSBML;

%include "layout/CLCurve.h"


