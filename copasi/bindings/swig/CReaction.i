// Begin CVS Header 
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CReaction.i,v $ 
//   $Revision: 1.15 $ 
//   $Name:  $ 
//   $Author: bergmann $ 
//   $Date: 2012/04/11 15:40:26 $ 
// End CVS Header 

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "model/CReaction.h"

%}
    
%ignore CReaction::load;
%ignore CReaction::getSmallestCompartment() const; // not implemented
%ignore CReaction::getParameterMappings() const; 
%ignore CReaction::setFunctionFromExpressionTree(CEvaluationTree* , std::map<CCopasiObject*, SBase*> & , CFunctionDB* );
%ignore CReaction::calculatePartialDerivative;
%ignore CReaction::getExpressionTree;
%ignore CReaction::getDeletedObjects;

#if (defined SWIGJAVA || defined SWIGCSHARP)
// remove some const methods to get rid of warnings
%ignore CReaction::getChemEq() const;
%ignore CReaction::getParameters() const;

#endif // SWIGJAVA || CSHARP

%catches(CCopasiException) CReaction::getLargestCompartment() const;

%include "model/CReaction.h"

