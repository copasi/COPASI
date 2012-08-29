// Begin CVS Header 
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/COptItem.i,v $ 
//   $Revision: 1.3 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:28 $ 
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
%ignore COptItem::getUpdateMethod;

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


