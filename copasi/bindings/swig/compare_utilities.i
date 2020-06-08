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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "copasi/compareExpressions/compare_utilities.h"
#include "sbml/math/ASTNode.h"  
#include "sbml/Model.h"  
%}

// we ignore all functions that need objects from libsbml
%ignore create_expression(const ASTNode* , const Model* );
%ignore create_simplified_normalform(const ASTNode *);
%ignore create_normalform(const ASTNode* );
%ignore are_equal(const CNormalFraction* , const CNormalFraction* );
%ignore normalize_variable_names(CNormalBase*, std::map<std::string, std::string>&);
%ignore replace_variable_names;
%ignore expand_function_call;
%ignore expand_function_calls;
%ignore create_expression(const ASTNode* , const Model* );
%ignore replace_SEC(const ASTNode* );
%ignore replace_CSC(const ASTNode* );
%ignore replace_COT(const ASTNode* );
%ignore replace_SINH(const ASTNode* );
%ignore replace_COSH(const ASTNode* );
%ignore replace_TANH(const ASTNode* );
%ignore replace_SECH(const ASTNode* );
%ignore replace_CSCH(const ASTNode* );
%ignore replace_COTH(const ASTNode* );
%ignore replace_ARCSINH(const ASTNode* );
%ignore replace_ARCCOSH(const ASTNode* );
%ignore replace_ARCTANH(const ASTNode* );
%ignore replace_ARCSECH(const ASTNode* );
%ignore replace_ARCCSCH(const ASTNode* );

%include "copasi/compareExpressions/compare_utilities.h"



