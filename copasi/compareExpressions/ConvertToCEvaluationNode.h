// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/ConvertToCEvaluationNode.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/10/15 07:10:30 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef ConvertToCEvaluationNode_H__
#define ConvertToCEvaluationNode_H__

#include <string>
#include <map>

class CEvaluationNode;
class CNormalItem;
class CNormalItemPower;
class CNormalLcm;
class CNormalSum;
class CNormalProduct;
class CNormalBase;
class CNormalChoice;
class CNormalChoiceLogical;
class CNormalLogical;
class CNormalLogicalItem;
class CNormalGeneralPower;
class CNormalFunction;
class CNormalCall;

#include "copasi/compareExpressions/CNormalFraction.h"

extern std::map<std::string, const CEvaluationNode*> str2eval;

CEvaluationNode* convertToCEvaluationNode(const CNormalFraction& fraction);
CEvaluationNode* convertToCEvaluationNode(const CNormalItem& item);
CEvaluationNode* convertToCEvaluationNode(const CNormalItemPower& itemPower);
CEvaluationNode* convertToCEvaluationNode(const CNormalLcm& lcm);
CEvaluationNode* convertToCEvaluationNode(const CNormalProduct& product);
CEvaluationNode* convertToCEvaluationNode(const CNormalSum& sum);
CEvaluationNode* convertToCEvaluationNode(const CNormalChoice& choice);
CEvaluationNode* convertToCEvaluationNode(const CNormalChoiceLogical& choice);
CEvaluationNode* convertToCEvaluationNode(const CNormalLogicalItem& choice);
CEvaluationNode* convertToCEvaluationNode(const CNormalLogical& logical);
CEvaluationNode* convertToCEvaluationNode(const CNormalBase& base);
CEvaluationNode* convertToCEvaluationNode(const CNormalGeneralPower& pow);
CEvaluationNode* convertToCEvaluationNode(const CNormalFunction& fun);
CEvaluationNode* convertToCEvaluationNode(const CNormalCall& call);

/**
 * Create a fraction from a node. node is necessarily a DIVIDE operator if not the root node of the tree.
 * @return CNormalFraction*, pointer to newly created fraction.
 */
CNormalFraction* createFraction(const CEvaluationNode* node);

/**
 * Create an item from an evaluation node that need not be of specific type.
 * @return CNormalItem*, pointer to newly created item.
 */
CNormalItem* createItem(const CEvaluationNode* node);

/**
 * Create a product from an evaluation node that is not necessarily a multiply operator.
 * @return CNormalProduct*, pointer to newly created product.
 */
CNormalProduct * createProduct(const CEvaluationNode* node);

/**
 * Create a sum from an evaluation node -node does not need to be a PLUS operator!
 * @return CNormalSum*, pointer to newly created sum
 */
CNormalSum* createSum(const CEvaluationNode* node);

/**
 * Create an item power from an evaluation node.
 * Node MUST BE a POWER operator with second child (exponent) of type NUMBER !!
 * @return CNormalItemPower*, pointer to newly created item power.
 */
CNormalItemPower * createItemPower(const CEvaluationNode* node);

/**
 * Create an general power from an evaluation node.
 * Node MUST BE a POWER operator with second child (exponent) of type not NUMBER !!
 * @return CNormalItemPower*, pointer to newly created general power (or modulo).
 */
CNormalGeneralPower * createGeneralPower(const CEvaluationNode* node);

/**
 * Create an function call from an evaluation node.
 * @return CNormalCall*, pointer to newly created call
 */
CNormalCall * createCall(const CEvaluationNode* node);

/**
 * Create an function from an evaluation node.
 * @return CNormalFunction*, pointer to newly created function
 */
CNormalFunction * createFunction(const CEvaluationNode* node);

/**
 * Create an item power from an evaluation node.
 * Must be a CEvaluationNodeChoice.
 * @return CNormalChoice*, pointer to newly created choice node.
CNormalChoice * createChoice(const CEvaluationNode* node);
 */

/**
 * Create an item power from an evaluation node.
 * @return CNormalBase*, pointer to newly created normal base object power.
 */
CNormalFraction * createNormalRepresentation(const CEvaluationNode* node);

/**
 * Create an logical node from an evaluation node.
 * Must be a CEvaluationNodeLogical or the not function.
 * @return CNormalLogical*, pointer to newly created logical node.
CNormalLogical* createLogical(const CEvaluationNode* node);
 */

bool isLogical(const CEvaluationNode* pNode);

CNormalBase* createItemPowerItem(const CEvaluationNode* pNode);

CNormalChoice* createChoice(const CEvaluationNode* pNode);
CNormalChoiceLogical* createLogicalChoice(const CEvaluationNode* pNode);
CNormalLogical* createLogical(const CEvaluationNode* pNode);
CNormalLogicalItem* createLogicalItem(const CEvaluationNode* pNode);

#endif /* ConvertToCEvaluationNode_H__ */
