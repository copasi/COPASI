// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/COptItem.i,v $ 
//   $Revision: 1.2.20.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/27 18:59:23 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "optimization/COptItem.h"

%}

%ignore operator<<(std::ostream&, const COptItem&);
%ignore COptItem::getObjectValue;
%ignore COptItem::getLowerBoundValue;
%ignore COptItem::getUpperBoundValue;

%include "optimization/COptItem.h"

// unignore getObjectValue
%rename(getObjectValue) COptItem::getObjectValue;
%rename(getLowerBoundValue) COptItem::getLowerBoundValue;
%rename(getUpperBoundValue) COptItem::getUpperBoundValue;

%extend COptItem
{
    double getObjectValue() const
    {
        double v=*($self->getObjectValue());
        return v;
    }

    double getLowerBoundValue() const
    {
        double v=*($self->getLowerBoundValue());
        return v;
    }

    double getUpperBoundValue() const
    {
        double v=*($self->getUpperBoundValue());
        return v;
    }
}


