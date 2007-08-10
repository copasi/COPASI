// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/compare_utilities.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2007/08/10 13:42:20 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COMPARE_UTILITIES_H__
#define COMPARE_UTILITIES_H__

#include <string>
#include <map>

class ASTNode;
class CNormalFraction;
class Model;
class CNormalBase;
class ConverterASTNode;

ASTNode* create_expression(const ASTNode* pSource, const Model* pModel);

CNormalFraction* create_normalform(const ASTNode* pSource);

bool are_equal(const CNormalFraction* pLHS, const CNormalFraction* pRHS);

void normalize_variable_names(CNormalBase* pBase, std::map<std::string, std::string>& variableMap);

bool replace_variable_names(ASTNode* pNode, const std::map<std::string, ASTNode*>& argumentMap);

ASTNode* expand_function_call(const ASTNode* pCall, const Model* pModel);

bool expand_function_calls(ASTNode* pNode, const Model* pModel);

#endif /* COMPARE_UTILITIES_H__ */
