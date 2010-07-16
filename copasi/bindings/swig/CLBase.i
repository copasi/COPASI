// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CLBase.i,v $ 
//   $Revision: 1.2 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:27 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

#include "layout/CLBase.h"

%}

%ignore CLBase::CLBase(const SBase&);

%ignore CLPoint::getX;
%ignore CLPoint::getY;
%ignore CLPoint::CLPoint(const Point&);
%ignore CLPoint::getSBMLPoint() const;
%ignore CLPoint::operator<(const CLPoint&) const;

%ignore CLDimensions::getHeight;
%ignore CLDimensions::getWidth;
%ignore CLDimensions::CLDimensions(const Dimensions&);
%ignore CLDimensions::getSBMLDimensions() const;

%ignore CLBoundingBox::getPosition() const;
%ignore CLBoundingBox::getDimensions() const;
%ignore CLBoundingBox::CLBoundingBox(const BoundingBox&);
%ignore CLBoundingBox::getSBMLBoundingBox() const;


%include "layout/CLBase.h"

// unignore getX and getY for CLPoint
%rename(getX) CLPoint::getX;
%rename(getY) CLPoint::getY;

// unignore getHeight and getWidth for CLDimensions
%rename(getHeight) CLDimensions::getHeight;
%rename(getWidth) CLDimensions::getWidth;

%extend CLPoint
{
    double getX() const
    {
        double v=$self->getX();
        return v;
    }

    double getY() const
    {
        double v=$self->getY();
        return v;
    }
}

%extend CLDimensions
{
    double getHeight() const
    {
        double v=$self->getHeight();
        return v;
    }

    double getWidth() const
    {
        double v=$self->getWidth();
        return v;
    }
}
