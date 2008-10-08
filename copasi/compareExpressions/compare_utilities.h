// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/compare_utilities.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/10/08 15:50:43 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

CNormalFraction* create_simplified_normalform(const ASTNode* pSource);

CNormalFraction* create_normalform(const ASTNode* pSource);

bool are_equal(const CNormalFraction* pLHS, const CNormalFraction* pRHS);

void normalize_variable_names(CNormalBase* pBase, std::map<std::string, std::string>& variableMap);

ASTNode* replace_variable_names(const ASTNode* pNode, const std::map<std::string, const ASTNode*>& argumentMap);

ASTNode* expand_function_call(const ASTNode* pCall, const Model* pModel);

ASTNode* expand_function_calls(const ASTNode* pNode, const Model* pModel);

/**
 * This function replaces a call to SEC by 1/COS.
 */
ASTNode* replace_SEC(const ASTNode* pChild);

/**
 * This function replaces a call to CSC by 1/SIN.
 */
ASTNode* replace_CSC(const ASTNode* pChild);

/**
 * This function replaces a call to COT by COS/SIN.
 */
ASTNode* replace_COT(const ASTNode* pChild);

/**
 * This function replaces a call to SINH by (e^X-e^(-X))/2.
 */
ASTNode* replace_SINH(const ASTNode* pChild);

/**
 * This function replaces a call to COSH by (e^X+e^(-X))/2
 */
ASTNode* replace_COSH(const ASTNode* pChild);

/**
 * This function replaces a call to TANH by (e^X-e^(-X))/(e^X+e^(-X))
 */
ASTNode* replace_TANH(const ASTNode* pChild);

/**
 * This function replaces a call to SECH by 2/(e^X+e^(-X))
 */
ASTNode* replace_SECH(const ASTNode* pChild);

/**
 * This function replaces a call to CSCH by 2/(e^X-e^(-X))
 */
ASTNode* replace_CSCH(const ASTNode* pChild);

/**
 * This function replaces a call to COTH by (e^X+e^(-X))/(e^X-e^(-X))
 */
ASTNode* replace_COTH(const ASTNode* pChild);

/**
 * This function replaces a call to ARCSINH by log(X + sqrt(X^2 + 1))
 */
ASTNode* replace_ARCSINH(const ASTNode* pChild);

/**
 * This function replaces a call to ARCCOSH by log(X + sqrt(X-1) * sqrt(X+1))
 */
ASTNode* replace_ARCCOSH(const ASTNode* pChild);

/**
 * This function replaces a call to ARCTANH by 1/2 * (log(1+X) - log(1-X))
 */
ASTNode* replace_ARCTANH(const ASTNode* pChild);

/**
 * This function replaces a call to ARCSECH by log(sqrt((1/X)-1) * sqrt(1+(1/X)) + 1/X)
 */
ASTNode* replace_ARCSECH(const ASTNode* pChild);

/**
 * This function replaces a call to ARCCSCH by log(sqrt(1+ (1/ (X^2)))+(1/X))
 */
ASTNode* replace_ARCCSCH(const ASTNode* pChild);

#endif /* COMPARE_UTILITIES_H__ */
