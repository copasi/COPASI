// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "copasi/optimization/COptItem.h"
#include "copasi/parameterFitting/CFitItem.h"

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
        if (!$self->getObjectValue())
          return std::numeric_limits<double>::quiet_NaN();

        double v=*($self->getObjectValue());
        return v;
    }

    double getLowerBoundValue() const
    {
        if (!$self->getLowerBoundValue())
          return std::numeric_limits<double>::quiet_NaN();

        double v=*($self->getLowerBoundValue());
        return v;
    }

    double getUpperBoundValue() const
    {
        if (!$self->getUpperBoundValue())
          return std::numeric_limits<double>::quiet_NaN();

        double v=*($self->getUpperBoundValue());
        return v;
    }
    
    CFitItem* asFitItem()
    {
      return dynamic_cast<CFitItem*>($self);
    }

    CFitConstraint* asFitConstraint()
    {
      return dynamic_cast<CFitConstraint*>($self);
    }
}


