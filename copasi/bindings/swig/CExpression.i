// Begin CVS Header 
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CExpression.i,v $ 
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
#include "function/CExpression.h"
%}

%newobject CEvaluationTree::createInitialExpression;

%ignore CExpression::writeMathML;

%include "function/CExpression.h"

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
