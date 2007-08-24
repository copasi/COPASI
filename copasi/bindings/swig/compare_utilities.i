// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/compare_utilities.i,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2007/08/24 10:48:23 $ 
// End CVS Header 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "compareExpressions/compare_utilities.h"
#include "sbml/math/ASTNode.h"  
#include "sbml/Model.h"  
%}

%ignore normalize_variable_names(CNormalBase*, std::map<std::string, std::string>&);
%ignore replace_variable_names(ASTNode* , const std::map<std::string, ASTNode*>& );
%ignore expand_function_call(const ASTNode* , const Model* );
%ignore expand_function_calls(ASTNode* , const Model* );
%ignore create_expression(const ASTNode* , const Model* );
%ignore create_normalform(const ASTNode* );
%ignore are_equal(const CNormalFraction* , const CNormalFraction* );

%include "compareExpressions/compare_utilities.h"



