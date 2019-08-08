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
#include "copasi/function/CExpression.h"
%}

%newobject CEvaluationTree::createInitialExpression;

%ignore CExpression::writeMathML;

%include "copasi/function/CExpression.h"

// unignore writeMathML
%rename(writeMathML) CExpression::writeMathML;

%extend CExpression
{
    std::string writeMathML(bool fullExpand, unsigned C_INT32 l) const
    {
        std::ostringstream os;
        $self->writeMathML(os,fullExpand,l);
        return os.str();
    }
}
