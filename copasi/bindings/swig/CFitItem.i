// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CFitItem.i,v $ 
//   $Revision: 1.3 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:27 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

%{

#include "parameterFitting/CFitItem.h"

%}

%ignore CFitItem::updateBounds;
%ignore CFitItem::getObjectValue;
%ignore CFitItem::getUpdateMethod;

%include "parameterFitting/CFitItem.h"

// unignore getObjectValue
%rename(getObjectValue) CFitItem::getObjectValue;

%extend CFitItem
{
    double getObjectValue() const
    {
        double v=*($self->getObjectValue());
        return v;
    }
}
