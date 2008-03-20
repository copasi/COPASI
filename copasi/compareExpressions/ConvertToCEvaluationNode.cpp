// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/ConvertToCEvaluationNode.cpp,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/03/20 20:31:36 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#include <assert.h>
#include <sstream>
#include <exception>

#include "ConvertToCEvaluationNode.h"

#include "function/CEvaluationNode.h"
#include "function/CEvaluationNodeOperator.h"
#include "function/CEvaluationNodeConstant.h"
#include "function/CEvaluationNodeFunction.h"
#include "function/CEvaluationNodeNumber.h"
#include "function/CEvaluationNodeObject.h"
#include "function/CEvaluationNodeVariable.h"
#include "function/CEvaluationNodeChoice.h"
#include "function/CEvaluationNodeLogical.h"

#include "CNormalItem.h"
#include "CNormalItemPower.h"
#include "CNormalSum.h"
#include "CNormalProduct.h"
#include "CNormalLcm.h"
#include "CNormalFraction.h"
#include "CNormalBase.h"
#include "CNormalChoice.h"
#include "CNormalChoiceLogical.h"
#include "CNormalLogical.h"
#include "CNormalLogicalItem.h"
#include "CNormalFunction.h"
#include "CNormalGeneralPower.h"
#include "CNormalTranslation.h"

std::map<std::string, const CEvaluationNode*> str2eval;

CEvaluationNode* convertToCEvaluationNode(const CNormalFraction& fraction)
{
  CEvaluationNode* pResult = NULL;
  if (fraction.checkDenominatorOne())
    {
      pResult = convertToCEvaluationNode(fraction.getNumerator());
    }
  else
    {
      CEvaluationNodeOperator* pDivision = new CEvaluationNodeOperator(CEvaluationNodeOperator::DIVIDE, "/");
      CEvaluationNode* pChild = convertToCEvaluationNode(fraction.getNumerator());
      pDivision->addChild(pChild);
      pChild = convertToCEvaluationNode(fraction.getDenominator());
      pDivision->addChild(pChild);
      pResult = pDivision;
    }
  return pResult;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalItem& item)
{
  CEvaluationNode* pNode = NULL;
  CEvaluationNode::Type type = CEvaluationNode::INVALID;
  switch (item.getType())
    {
    case CNormalItem::CONSTANT:
      // create a CEvaluationNodeNumber
      if (item.getName() == "pi" || item.getName() == "PI")
        {
          type = (CEvaluationNode::Type)(CEvaluationNodeConstant::PI);
        }
      else if (item.getName() == "EXPONENTIALE" || item.getName() == "exponentiale")
        {
          type = (CEvaluationNode::Type)(CEvaluationNodeConstant::EXPONENTIALE);
        }
      else if (item.getName() == "TRUE" || item.getName() == "true")
        {
          type = (CEvaluationNode::Type)(CEvaluationNodeConstant::TRUE);
        }
      else if (item.getName() == "FALSE" || item.getName() == "false")
        {
          type = (CEvaluationNode::Type)(CEvaluationNodeConstant::FALSE);
        }
      else if (item.getName() == "INFINITY" || item.getName() == "infinity")
        {
          type = (CEvaluationNode::Type)(CEvaluationNodeConstant::_INFINITY);
        }
      else if (item.getName() == "NAN" || item.getName() == "nan")
        {
          type = (CEvaluationNode::Type)(CEvaluationNodeConstant::_NaN);
        }
      pNode = new CEvaluationNodeConstant((CEvaluationNodeConstant::SubType)type, item.getName());
      break;
    case CNormalItem::VARIABLE:
      // create a CEvaluationNodeVariable
      pNode = new CEvaluationNodeVariable(CEvaluationNodeVariable::ANY, item.getName());
      break;
    }
  return pNode;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalItemPower& itemPower)
{
  CEvaluationNode* pResult = NULL;
  if (itemPower.getExp() == 1.0)
    {
      pResult = convertToCEvaluationNode(itemPower.getItem());
    }
  else
    {
      std::ostringstream sstream;
      CEvaluationNodeOperator* pPowerNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "^");
      CEvaluationNode* pChild = convertToCEvaluationNode(itemPower.getItem());
      pPowerNode->addChild(pChild);
      sstream << itemPower.getExp();
      pPowerNode->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, sstream.str()));
      pResult = pPowerNode;
    }
  return pResult;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalLcm& lcm)
{
  CEvaluationNode* pResult = NULL;
  const std::set<CNormalItemPower*, compareItemPowers >& itemPowers = lcm.getItemPowers();
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator it = itemPowers.begin();
  std::set<CNormalItemPower*, compareItemPowers >::const_iterator itEnd = itemPowers.end();
  CEvaluationNodeOperator* pMult = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
  pResult = pMult;
  CEvaluationNode* pChild = NULL;
  while (it != itEnd)
    {
      assert(pMult != NULL);
      pChild = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
      pMult->addChild(pChild);
      pChild = convertToCEvaluationNode(**it);
      pMult->addChild(pChild);
      pMult = dynamic_cast<CEvaluationNodeOperator*>(pMult->getChild());
      ++it;
    }
  const std::vector<CNormalSum*>& sums = lcm.getSums();
  std::vector<CNormalSum*>::const_iterator it2 = sums.begin();
  std::vector<CNormalSum*>::const_iterator itEnd2 = sums.end();
  while (it2 != itEnd2)
    {
      assert(pMult != NULL);
      pChild = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
      pMult->addChild(pChild);
      pChild = convertToCEvaluationNode(**it);
      pMult->addChild(pChild);
      pMult = dynamic_cast<CEvaluationNodeOperator*>(pMult->getChild());
      ++it;
    }
  if (pMult->getParent() == pResult)
    {
      pResult->removeChild(pMult);
      delete pMult;
    }
  else
    {
      CEvaluationNode* pParent = dynamic_cast<CEvaluationNode*>(pMult->getParent());
      assert(pParent != NULL);
      pParent->removeChild(pMult);
      delete pMult;
      pMult = dynamic_cast<CEvaluationNodeOperator*>(pParent->getParent());
      assert(pMult != NULL);
      pMult->removeChild(pParent);
      pMult->addChild(dynamic_cast<CEvaluationNode*>(pParent->getChild())->copyBranch());
      delete pParent;
    }
  return pResult;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalProduct& product)
{
  CEvaluationNode* pResult = NULL;
  std::ostringstream sstream;
  if (product.getItemPowers().size() == 0)
    {
      sstream << product.getFactor();
      pResult = new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, sstream.str());
    }
  else
    {
      const std::set<CNormalItemPower*, compareItemPowers >& itemPowers = product.getItemPowers();
      std::set<CNormalItemPower*, compareItemPowers >::const_iterator it = itemPowers.begin();
      std::set<CNormalItemPower*, compareItemPowers >::const_iterator itEnd = itemPowers.end();
      CEvaluationNodeOperator* pMult = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
      pResult = pMult;
      CEvaluationNode* pChild = NULL;
      while (it != itEnd)
        {
          pChild = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
          pMult->addChild(pChild);
          pChild = convertToCEvaluationNode(**it);
          pMult->addChild(pChild);
          pMult = dynamic_cast<CEvaluationNodeOperator*>(pMult->getChild());
          ++it;
        }
      if (product.getFactor() != 1.0)
        {
          sstream << product.getFactor();
          pMult->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, sstream.str()));
          if (pMult == pResult)
            {
              // there were no item powers
              pResult = dynamic_cast<CEvaluationNode*>(pResult->getChild())->copyBranch();
              delete pMult;
            }
          else
            {
              CEvaluationNode* pParent = dynamic_cast<CEvaluationNode*>(pMult->getParent());
              assert(pParent != NULL);
              pParent->removeChild(pMult);
              pParent->addChild(dynamic_cast<CEvaluationNode*>(pMult->getChild())->copyBranch());
              delete pMult;
            }
        }
      else
        {
          if (pMult == pResult)
            {
              // there were no item powers
              delete pResult;
              pResult = dynamic_cast<CEvaluationNode*>(pResult->getChild())->copyBranch();
            }
          else
            {
              // replace the parent of pMult by the sibling of pMult and delete
              // the parent and pMult
              CEvaluationNode* pParent = dynamic_cast<CEvaluationNode*>(pMult->getParent());
              assert(pParent != NULL);
              if (pParent == pResult)
                {
                  pResult = dynamic_cast<CEvaluationNode*>(pMult->getSibling());
                  pParent->removeChild(pResult);
                  delete pParent;
                }
              else
                {
                  CEvaluationNode* pGrandParent = dynamic_cast<CEvaluationNode*>(pParent->getParent());
                  pGrandParent->removeChild(pParent);
                  pGrandParent->addChild(dynamic_cast<CEvaluationNode*>(pMult->getSibling())->copyBranch());
                  delete pParent;
                }
            }
        }
    }
  return pResult;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalSum& sum)
{
  //std::cout << "Converting Sum: " << sum << std::endl;
  const std::set<CNormalFraction*>& fractions = sum.getFractions();
  std::set<CNormalFraction*>::const_iterator it = fractions.begin();
  std::set<CNormalFraction*>::const_iterator itEnd = fractions.end();
  CEvaluationNode* pResult = new CEvaluationNodeOperator(CEvaluationNodeOperator::PLUS, "+");
  CEvaluationNode* pOperator = pResult;
  CEvaluationNode* pChild = NULL;
  while (it != itEnd)
    {
      pChild = convertToCEvaluationNode(**it);
      pOperator->addChild(pChild);
      pChild = new CEvaluationNodeOperator(CEvaluationNodeOperator::PLUS, "+");
      pOperator->addChild(pChild);
      pOperator = pChild;
      ++it;
    }
  const std::set<CNormalProduct*, compareProducts >& products = sum.getProducts();
  std::set<CNormalProduct*, compareProducts >::const_iterator it2 = products.begin();
  std::set<CNormalProduct*, compareProducts >::const_iterator itEnd2 = products.end();
  while (it2 != itEnd2)
    {
      pChild = convertToCEvaluationNode(**it2);
      pOperator->addChild(pChild);
      pChild = new CEvaluationNodeOperator(CEvaluationNodeOperator::PLUS, "+");
      pOperator->addChild(pChild);
      pOperator = pChild;
      ++it2;
    }
  // get the parent of the last operator and replace it by its first child.
  // but only if the last operator is not equal to pResult
  if (pOperator != pResult)
    {
      pOperator = dynamic_cast<CEvaluationNodeOperator*>(pOperator->getParent());
      assert(pOperator != NULL);
      CEvaluationNode* pParent = dynamic_cast<CEvaluationNode*>(pOperator->getParent());
      if (pParent == NULL)
        {
          pResult = dynamic_cast<CEvaluationNode*>(pOperator->getChild());
          pOperator->removeChild(pResult);
        }
      else
        {
          pParent->removeChild(pOperator);
          pParent->addChild(dynamic_cast<CEvaluationNode*>(pOperator->getChild())->copyBranch());
        }
      delete pOperator;
    }
  //std::cout << "Converted Sum: " << std::endl;
  //pResult->printRecursively(std::cout);
  //std::cout << "---- End Of Converted Sum ----" << std::endl;
  return pResult;
}

/**
 * Create a fraction from a node. node is necessarily a DIVIDE operator if not the root node of the tree.
 * @return CNormalFraction*, pointer to newly created fraction.
 */
CNormalFraction* createFraction(const CEvaluationNode* node)
{
  if (node->getData() == "/")
    {// always executed except on root node possibly not
      CNormalFraction* fraction = new CNormalFraction();
      CNormalSum* num = createSum(static_cast<const CEvaluationNode*>(node->getChild()));
      CNormalSum* denom = createSum(static_cast<const CEvaluationNode*>(node->getChild()->getSibling()));
      fraction->setNumerator(*num);
      fraction->setDenominator(*denom);
      fraction->cancel();
      delete num;
      delete denom;
      return fraction;
    }
  else
    {// only possible for root node
      CNormalFraction* fraction = new CNormalFraction();
      CNormalSum* num = createSum(node);
      CNormalSum* denom = new CNormalSum();
      CNormalProduct* product = new CNormalProduct();
      denom->add(*product);
      fraction->setNumerator(*num);
      fraction->setDenominator(*denom);
      fraction->cancel();
      delete product;
      delete num;
      delete denom;
      return fraction;
    }
};

/**
 * Create an item from an evaluation node that need not be of specific type.
 * @return CNormalItem*, pointer to newly created item.
 */
CNormalItem* createItem(const CEvaluationNode* node)
{
  CNormalItem* pItem = NULL;
  switch (CEvaluationNode::type(node->getType()))
    {
    case CEvaluationNode::VARIABLE:
      pItem = new CNormalItem(node->getInfix(), CNormalItem::VARIABLE);
      break;
    case CEvaluationNode::CONSTANT:
      pItem = new CNormalItem(node->getInfix(), CNormalItem::CONSTANT);
      break;
      /*
      case CEvaluationNode::OPERATOR:
      if (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(node->getType()))==CEvaluationNodeOperator::POWER
          || ((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(node->getType()))==CEvaluationNodeOperator::MODULUS)
      {
          // calling createItem will add the wrong node for the
          // string into the lookup table
          CNormalItem * child1 = createItem(dynamic_cast<const CEvaluationNode*>(node->getChild()));
          CNormalItem * child2 = createItem(dynamic_cast<const CEvaluationNode*>(node->getChild()->getSibling()));

          std::stringstream tmp;
          if ((child1->getType() == CNormalItem::VARIABLE) || (child1->getType() == CNormalItem::CONSTANT))
              tmp << *child1;
          else
          {
              tmp << "(" << *child1 << ")";
          }
          tmp << node->getData();
          if ((child2->getType() == CNormalItem::VARIABLE) || (child2->getType() == CNormalItem::CONSTANT))
              tmp << *child2;
          else
          {
              tmp << "(" << *child2 << ")";
          }
          //std::cout << "if: " << tmp.str() << std::endl;

          pItem = new CNormalItem(tmp.str(), CNormalItem::FUNCTION);
          std::string s=tmp.str();
          std::map<std::string,const CEvaluationNode*>::const_iterator pos=str2eval.find(tmp.str());
          if(pos==str2eval.end())
          {
              CEvaluationNodeOperator::SubType type=CEvaluationNodeOperator::POWER;
              std::string s("^");
              if(node->getData()=="%")
              {
                  type=CEvaluationNodeOperator::MODULUS;
                  s="%";
              }
              CEvaluationNodeOperator* pNode=new CEvaluationNodeOperator(type,s);
              // when the child node is converted, the wrongly added
              // node from above is returned

              pNode->addChild(convertToCEvaluationNode(*child1));
              pNode->addChild(convertToCEvaluationNode(*child2));
              //pNode->printRecursively(std::cerr);
              str2eval[tmp.str()]=pNode;
              //std::cout << "Adding node for " << tmp.str() << std::endl;
              //pNode->printRecursively(std::cout);
          }
          delete child1;
          delete child2;
      }
      else // can be called only by createItem('OPERATOR node')
      {
          CNormalFraction * normedNode = createFraction(node);
          normedNode->simplify();
          CEvaluationNode* pTmpNode=convertToCEvaluationNode(*normedNode);
          std::stringstream tmp;
          tmp << *normedNode;
          //std::cout << "else: " << tmp.str() << std::endl;
          pItem = new CNormalItem(tmp.str(), CNormalItem::FUNCTION);
          std::map<std::string,const CEvaluationNode*>::const_iterator pos=str2eval.find(normedNode->toString());
          if(pos==str2eval.end())
          {
              str2eval[tmp.str()]=pTmpNode;
              //std::cout << "Adding node for " << tmp.str() << std::endl;
              //pTmpNode->printRecursively(std::cout);
          }

          delete normedNode;
      }
      break;
      */
    default:  //cases CALL, CHOICE, LOGICAL, OBJECT, VECTOR.  NUMBER should not occur!
      throw std::exception();
      break;
    }
  return pItem;
}

/**
 * Create an item power from an evaluation node.
 * Node MUST BE a POWER operator with second child (exponent) of type NUMBER !!
 * @return CNormalItemPower*, pointer to newly created item power.
 */
CNormalItemPower * createItemPower(const CEvaluationNode* node)
{
  CNormalItemPower * itemPower = new CNormalItemPower();
  CNormalBase* item = createItemPowerItem(static_cast<const CEvaluationNode*>(node->getChild()));
  itemPower->setItem(*item);
  itemPower->setExp(static_cast<const CEvaluationNode*>(node->getChild()->getSibling())->value());
  delete item;
  return itemPower;
}

/**
 * Create a product from an evaluation node that is not necessarily a multiply operator.
 * @return CNormalProduct*, pointer to newly created product.
 */
CNormalProduct * createProduct(const CEvaluationNode* node)
{
  CNormalProduct * product = new CNormalProduct();
  CNormalChoice * pChoice = NULL;
  switch (CEvaluationNode::type(node->getType()))
    {
    case CEvaluationNode::OPERATOR:  // PLUS(->createSum), MINUS(translated as +(-..)) and DIVIDE(->createFraction) do not occur.
      if (node->getData() == "^")
        {
          if (CEvaluationNode::type(static_cast<const CEvaluationNode*>(node->getChild()->getSibling())->getType()) == CEvaluationNode::NUMBER && node->getChild()->getChild() == NULL)
            {
              CNormalItemPower* power = createItemPower(node);
              product->multiply(*power);
              delete power;
            }
          else
            {
              CNormalGeneralPower* item = createGeneralPower(node);
              product->multiply(*item);
              delete item;
            }
        }
      else if (node->getData() == "*")
        {
          CNormalProduct* product1 = createProduct(static_cast<const CEvaluationNode*>(node->getChild()));
          CNormalProduct* product2 = createProduct(static_cast<const CEvaluationNode*>(node->getChild()->getSibling()));
          std::string s1 = product1->toString();
          std::string s2 = product2->toString();
          product->multiply(*product1);
          product->multiply(*product2);
          delete product1;
          delete product2;
        }
      else
        {
          //default (case MODULUS):
          CNormalGeneralPower* item = createGeneralPower(node);
          product->multiply(*item);
          delete item;
        }
      break;
    case CEvaluationNode::NUMBER:
      product->multiply(node->value());
      break;
    case CEvaluationNode::FUNCTION:
      if (((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(node->getType())) == CEvaluationNodeFunction::MINUS)
        {
          product->multiply(-1.0);
          CNormalProduct * product2 = createProduct(dynamic_cast<const CEvaluationNode*>(node->getChild()));
          product->multiply(*product2);
          delete product2;
        }
      else if (((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(node->getType())) == CEvaluationNodeFunction::PLUS)
        {
          CNormalProduct * product2 = createProduct(dynamic_cast<const CEvaluationNode*>(node->getChild()));
          product->multiply(*product2);
          delete product2;
        }
      else
        {
          CNormalFunction * item = createFunction(node);
          product->multiply(*item);
          delete item;
        }
      break;
    case CEvaluationNode::LOGICAL:
      throw std::exception(/*"Error. Logical Nodes are not allowed here."*/);
      break;
    case CEvaluationNode::CHOICE:
      pChoice = createChoice(dynamic_cast<const CEvaluationNode*>(node));
      product->multiply(*pChoice);
      delete pChoice;
      break;
    default:   //cases VARIABLE, CONSTANT, OBJECT, VECTOR
      CNormalItem * item = createItem(node);
      product->multiply(*item);
      delete item;
      break;
    }
  return product;
}

/**
 * Create a sum from an evaluation node -node does not need to be a PLUS operator!
 * @return CNormalSum*, pointer to newly created sum
 */
CNormalSum* createSum(const CEvaluationNode* node)
{
  CNormalSum* sum = new CNormalSum();
  if (node->getData() == "+")
    {
      CNormalSum* sum1 = createSum(static_cast<const CEvaluationNode*>(node->getChild()));
      CNormalSum* sum2 = createSum(static_cast<const CEvaluationNode*>(node->getChild()->getSibling()));
      sum->add(*sum1);
      sum->add(*sum2);
      delete sum1;
      delete sum2;
      return sum;
    }
  else if (node->getData() == "-")
    {
      CNormalSum* sum1 = createSum(static_cast<const CEvaluationNode*>(node->getChild()));
      CEvaluationNodeOperator* pOperatorNode = new CEvaluationNodeOperator(CEvaluationNodeOperator::MULTIPLY, "*");
      pOperatorNode->addChild(new CEvaluationNodeNumber(CEvaluationNodeNumber::DOUBLE, "-1.0"));
      pOperatorNode->addChild(static_cast<const CEvaluationNode*>(node->getChild()->getSibling())->copyBranch());
      CNormalSum* sum2 = createSum(pOperatorNode);
      delete pOperatorNode;
      sum->add(*sum1);
      sum->add(*sum2);
      delete sum1;
      delete sum2;
      return sum;
    }
  else
    {
      if (node->getData() == "/")
        {
          CNormalFraction* fraction = createFraction(node);
          sum->add(*fraction);
          delete fraction;
          return sum;
        }
      else
        {
          CNormalProduct* product = createProduct(node);
          sum->add(*product);
          delete product;
          return sum;
        }
    }
}

/**
 * Create an item power from an evaluation node.
 * Must be a CEvaluationNodeChoice.
 * @return CNormalChoice*, pointer to newly created choice node.
CNormalChoice * createChoice(const CEvaluationNode* node)
{
    // there are two kinds of choice nodes, one where mpTrue and mpFalse are
    // fractions and one where they are choice or logical
    // if the child node directly is a logical or a comparison, we create the
    // Logical, otherwise we create the fraction.
    CNormalChoice* pChoice=NULL;
    const CEvaluationNodeChoice* pChoiceNode=dynamic_cast<const CEvaluationNodeChoice*>(node);
    if(pChoiceNode!=NULL)
    {
        pChoice=new CNormalChoice();
        const CEvaluationNode* pTmpNode=dynamic_cast<const CEvaluationNode*>(pChoiceNode->getChild());
        if(pTmpNode!=NULL)
        {
            // check if this subtree is a logical expression
            CNormalLogical* pLogic=createLogical(pTmpNode);
            if(pLogicc)
            {
                pChoice->setCondition(*pLogic);
                delete pLogic;
                pTmpNode=dynamic_cast<const CEvaluationNode*>(pTmpNode->getSibling());
                if(pTmpNode!=NULL)
                {
                    if(isLogical(pTmpNode))
                    {
                        pLogic=createLogical(pTmpNode);
                        if(pLogic!=NULL)
                        {
                          pChoice->setTrueExpression(pLogic);
                          delete pLogic;
                          pTmpNode=dynamic_cast<const CEvaluationNode*>(pTmpNode->getSibling());
                          if(pTmpNode!=NULL && isLogical(pTmpNode))
                          {
                            pLogical=createLogical(pTmpNode);
                            if(pLogical!=NULL)
                            {
                                pChoice->setFalseExpression(*pLogic);
                                delete pLogic;
                            }
                            else
                            {
                                delete pChoice;
                                pChoice=NULL;
                            }
                          }
                          else
                          {
                            delete pChoice;
                            pChoice=NULL;
                          }
                        }
                        else
                        {
                            delete pChoice;
                            pChoice=NULL;
                            delete pLogic;
                        }
                    }
                    else
                    {
                        CNormalFraction* pFrac=createNormalRepresentation(pTmpNode);
                        if(pFrac)
                        {
                            pChoice->setTrueExpression(*pFrac);
                            delete pFrac;
                            pTmpNode=dynamic_cast<const CEvaluationNode*>(pTmpNode->getSibling());
                            if(pTmpNode!=NULL)
                            {
                                CNormalFraction* pFrac=createNormalRepresentation(pTmpNode);
                                if(pFrac)
                                {
                                    pChoice->setFalseExpression(*pFrac);
                                    delete pFrac;
                                }
                                else
                                {
                                    delete pChoice;
                                    pChoice=NULL;
                                }
                            }
                            else
                            {
                                delete pChoice;
                                pChoice=NULL;
                            }
                        }
                        else
                        {
                            delete pChoice;
                            pChoice=NULL;
                        }
                    }
                }
                else
                {
                    delete pChoice;
                    pChoice=NULL;
                }
            }
            else
            {
                delete pChoice;
                pChoice=NULL;
            }
        }
        else
        {
            delete pChoice;
            pChoice=NULL;
        }
    }
    return pChoice;
}
 */

/**
 * Create an item power from an evaluation node.
 * @return CNormalBase*, pointer to newly created normal base object power.
 */
CNormalFraction * createNormalRepresentation(const CEvaluationNode* node)
{
  CNormalFraction* pFrac = NULL;
  switch (CEvaluationNode::type(node->getType()))
    {
    case CEvaluationNode::NUMBER:
    case CEvaluationNode::OPERATOR:
    case CEvaluationNode::CONSTANT:
    case CEvaluationNode::VARIABLE:
    case CEvaluationNode::CHOICE:
    case CEvaluationNode::LOGICAL:
    case CEvaluationNode::FUNCTION:
      pFrac = createFraction(node);
      break;
    default:
      break;
    }
  return pFrac;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalBase& base)
{
  CEvaluationNode* pNode = NULL;
  if (dynamic_cast<const CNormalItem*>(&base) != NULL)
    {
      pNode = convertToCEvaluationNode(dynamic_cast<const CNormalItem&>(base));
    }
  else if (dynamic_cast<const CNormalItemPower*>(&base) != NULL)
    {
      pNode = convertToCEvaluationNode(dynamic_cast<const CNormalItemPower&>(base));
    }
  else if (dynamic_cast<const CNormalGeneralPower*>(&base) != NULL)
    {
      pNode = convertToCEvaluationNode(dynamic_cast<const CNormalGeneralPower&>(base));
    }
  else if (dynamic_cast<const CNormalFunction*>(&base) != NULL)
    {
      pNode = convertToCEvaluationNode(dynamic_cast<const CNormalFunction&>(base));
    }
  else if (dynamic_cast<const CNormalFraction*>(&base) != NULL)
    {
      pNode = convertToCEvaluationNode(dynamic_cast<const CNormalFraction&>(base));
    }
  else if (dynamic_cast<const CNormalProduct*>(&base) != NULL)
    {
      pNode = convertToCEvaluationNode(dynamic_cast<const CNormalProduct&>(base));
    }
  else if (dynamic_cast<const CNormalSum*>(&base) != NULL)
    {
      pNode = convertToCEvaluationNode(dynamic_cast<const CNormalSum&>(base));
    }
  else if (dynamic_cast<const CNormalLogical*>(&base) != NULL)
    {
      pNode = convertToCEvaluationNode(dynamic_cast<const CNormalLogical&>(base));
    }
  else if (dynamic_cast<const CNormalChoice*>(&base) != NULL)
    {
      pNode = convertToCEvaluationNode(dynamic_cast<const CNormalChoice&>(base));
    }
  return pNode;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalGeneralPower& pow)
{
  CEvaluationNode* pResult = NULL;
  switch (pow.getType())
    {
    case CNormalGeneralPower::POWER:
      pResult = new CEvaluationNodeOperator(CEvaluationNodeOperator::POWER, "^");
      break;
    case CNormalGeneralPower::MODULO:
      pResult = new CEvaluationNodeOperator(CEvaluationNodeOperator::MODULUS, "%");
      break;
    case CNormalGeneralPower::INVALID:
      break;
    }
  if (pResult != NULL)
    {
      CEvaluationNode* pChild = convertToCEvaluationNode(pow.getLeft());
      pResult->addChild(pChild);
      pChild = convertToCEvaluationNode(pow.getRight());
      pResult->addChild(pChild);
    }
  return pResult;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalFunction& fun)
{
  CEvaluationNode* pResult = NULL;
  std::string data;
  CEvaluationNodeFunction::SubType subType = CEvaluationNodeFunction::INVALID;
  switch (fun.getType())
    {
    case CNormalFunction::LOG:
      subType = CEvaluationNodeFunction::LOG;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::LOG10:
      subType = CEvaluationNodeFunction::LOG10;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::EXP:
      subType = CEvaluationNodeFunction::EXP;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::SIN:
      subType = CEvaluationNodeFunction::SIN;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction:: COS:
      subType = CEvaluationNodeFunction::COS;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::TAN:
      subType = CEvaluationNodeFunction::TAN;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::SEC:
      subType = CEvaluationNodeFunction::SEC;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::CSC:
      subType = CEvaluationNodeFunction::CSC;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::COT:
      subType = CEvaluationNodeFunction::COT;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::SINH:
      subType = CEvaluationNodeFunction::SINH;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::COSH:
      subType = CEvaluationNodeFunction::COSH;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::TANH:
      subType = CEvaluationNodeFunction::TANH;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::SECH:
      subType = CEvaluationNodeFunction::SECH;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::CSCH:
      subType = CEvaluationNodeFunction::CSCH;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::COTH:
      subType = CEvaluationNodeFunction::COTH;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::ARCSIN:
      subType = CEvaluationNodeFunction::ARCSIN;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::ARCCOS:
      subType = CEvaluationNodeFunction::ARCCOS;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::ARCTAN:
      subType = CEvaluationNodeFunction::ARCTAN;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::ARCSEC:
      subType = CEvaluationNodeFunction::ARCSEC;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::ARCCSC:
      subType = CEvaluationNodeFunction::ARCCSC;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::ARCCOT:
      subType = CEvaluationNodeFunction::ARCCOT;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::ARCSINH:
      subType = CEvaluationNodeFunction::ARCSINH;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::ARCCOSH:
      subType = CEvaluationNodeFunction::ARCCOSH;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::ARCTANH:
      subType = CEvaluationNodeFunction::ARCTANH;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::ARCSECH:
      subType = CEvaluationNodeFunction::ARCSECH;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::ARCCSCH:
      subType = CEvaluationNodeFunction::ARCCSCH;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::ARCCOTH:
      subType = CEvaluationNodeFunction::ARCCOTH;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::SQRT:
      subType = CEvaluationNodeFunction::SQRT;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::ABS:
      subType = CEvaluationNodeFunction::ABS;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::FLOOR:
      subType = CEvaluationNodeFunction::FLOOR;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::CEIL:
      subType = CEvaluationNodeFunction::CEIL;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::FACTORIAL:
      subType = CEvaluationNodeFunction::FACTORIAL;
      data = CNormalFunction::NAMES[fun.getType()];
      break;
    case CNormalFunction::INVALID:
      data = "@";
      break;
    }
  pResult = new CEvaluationNodeFunction(subType, data);
  if (subType != CEvaluationNodeFunction::INVALID)
    {
      CEvaluationNode* pChild = convertToCEvaluationNode(fun.getFraction());
      pResult->addChild(pChild);
    }
  return pResult;
}

/**
 * Create an general power from an evaluation node.
 * Node MUST BE a POWER operator with second child (exponent) of type not NUMBER !!
 * @return CNormalItemPower*, pointer to newly created general power (or modulo).
 */
CNormalGeneralPower * createGeneralPower(const CEvaluationNode* node)
{
  CNormalGeneralPower* pPow = NULL;
  if (CEvaluationNode::type(node->getType()) == CEvaluationNode::OPERATOR)
    {
      if (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(node->getType())) == CEvaluationNodeOperator::POWER)
        {
          pPow = new CNormalGeneralPower();
          pPow->setType(CNormalGeneralPower::POWER);
        }
      else if (((CEvaluationNodeOperator::SubType)CEvaluationNode::subType(node->getType())) == CEvaluationNodeOperator::MODULUS)
        {
          pPow = new CNormalGeneralPower();
          pPow->setType(CNormalGeneralPower::MODULO);
        }
      if (pPow != NULL)
        {
          // add the left and the right side
          CNormalFraction* pChild1 = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(node->getChild()));
          CNormalFraction* pChild2 = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(node->getChild()->getSibling()));
          if (pChild1 != NULL && pChild2 != NULL)
            {
              pPow->setLeft(*pChild1);
              pPow->setRight(*pChild2);
            }
          if (pChild1 != NULL) delete pChild1;
          if (pChild2 != NULL) delete pChild2;
        }
    }
  return pPow;
}

/**
 * Create an function from an evaluation node.
 * @return CNormalFunction*, pointer to newly created function
 */
CNormalFunction * createFunction(const CEvaluationNode* node)
{
  CNormalFunction* pFun = NULL;
  CEvaluationNode::Type type = CEvaluationNode::type(node->getType());
  if (type == CEvaluationNode::FUNCTION)
    {
      CNormalFunction::Type type = CNormalFunction::INVALID;
      switch ((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(node->getType()))
        {
        case CEvaluationNodeFunction::LOG:
          type = CNormalFunction::LOG;
          break;
        case CEvaluationNodeFunction::LOG10:
          type = CNormalFunction::LOG10;
          break;
        case CEvaluationNodeFunction::EXP:
          type = CNormalFunction::EXP;
          break;
        case CEvaluationNodeFunction::SIN:
          type = CNormalFunction::SIN;
          break;
        case CEvaluationNodeFunction:: COS:
          type = CNormalFunction::COS;
          break;
        case CEvaluationNodeFunction::TAN:
          type = CNormalFunction::TAN;
          break;
        case CEvaluationNodeFunction::SEC:
          type = CNormalFunction::SEC;
          break;
        case CEvaluationNodeFunction::CSC:
          type = CNormalFunction::CSC;
          break;
        case CEvaluationNodeFunction::COT:
          type = CNormalFunction::COT;
          break;
        case CEvaluationNodeFunction::SINH:
          type = CNormalFunction::SINH;
          break;
        case CEvaluationNodeFunction::COSH:
          type = CNormalFunction::COSH;
          break;
        case CEvaluationNodeFunction::TANH:
          type = CNormalFunction::TANH;
          break;
        case CEvaluationNodeFunction::SECH:
          type = CNormalFunction::SECH;
          break;
        case CEvaluationNodeFunction::CSCH:
          type = CNormalFunction::CSCH;
          break;
        case CEvaluationNodeFunction::COTH:
          type = CNormalFunction::COTH;
          break;
        case CEvaluationNodeFunction::ARCSIN:
          type = CNormalFunction::ARCSIN;
          break;
        case CEvaluationNodeFunction::ARCCOS:
          type = CNormalFunction::ARCCOS;
          break;
        case CEvaluationNodeFunction::ARCTAN:
          type = CNormalFunction::ARCTAN;
          break;
        case CEvaluationNodeFunction::ARCSEC:
          type = CNormalFunction::ARCSEC;
          break;
        case CEvaluationNodeFunction::ARCCSC:
          type = CNormalFunction::ARCCSC;
          break;
        case CEvaluationNodeFunction::ARCCOT:
          type = CNormalFunction::ARCCOT;
          break;
        case CEvaluationNodeFunction::ARCSINH:
          type = CNormalFunction::ARCSINH;
          break;
        case CEvaluationNodeFunction::ARCCOSH:
          type = CNormalFunction::ARCCOSH;
          break;
        case CEvaluationNodeFunction::ARCTANH:
          type = CNormalFunction::ARCTANH;
          break;
        case CEvaluationNodeFunction::ARCSECH:
          type = CNormalFunction::ARCSECH;
          break;
        case CEvaluationNodeFunction::ARCCSCH:
          type = CNormalFunction::ARCCSCH;
          break;
        case CEvaluationNodeFunction::ARCCOTH:
          type = CNormalFunction::ARCCOTH;
          break;
        case CEvaluationNodeFunction::SQRT:
          type = CNormalFunction::SQRT;
          break;
        case CEvaluationNodeFunction::ABS:
          type = CNormalFunction::ABS;
          break;
        case CEvaluationNodeFunction::FLOOR:
          type = CNormalFunction::FLOOR;
          break;
        case CEvaluationNodeFunction::CEIL:
          type = CNormalFunction::CEIL;
          break;
        case CEvaluationNodeFunction::FACTORIAL:
          type = CNormalFunction::FACTORIAL;
          break;
        case CEvaluationNodeFunction::INVALID:
        default:
          break;
        }
      if (type != CNormalFunction::INVALID)
        {
          CNormalFraction* pFrac = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(node->getChild()));
          if (pFrac != NULL)
            {
              pFun = new CNormalFunction();
              pFun->setType(type);
              pFun->setFraction(*pFrac);
              delete pFrac;
            }
        }
    }
  return pFun;
}

bool isLogical(const CEvaluationNode* pNode)
{
  bool result = false;
  // go through the tree until one of the following is encountered:
  // CEvaluationNodeLogical, CEvaluationNodeFunction::NOT or
  // CEvaluationNodeConstant::(TRUE|FALSE)
  if ((CEvaluationNode::type(pNode->getType()) == CEvaluationNode::LOGICAL) ||
      ((CEvaluationNode::type(pNode->getType()) == CEvaluationNode::FUNCTION && ((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(pNode->getType())) == CEvaluationNodeFunction::NOT)) ||
      (CEvaluationNode::type(pNode->getType()) == CEvaluationNode::CONSTANT && ((((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(pNode->getType())) == CEvaluationNodeConstant::TRUE) || (((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(pNode->getType())) == CEvaluationNodeConstant::FALSE)))
)

    {
      result = true;
    }
  const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
  while (result == false && pChild != NULL)
    {
      result = isLogical(pChild);
      pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
    }
  return result;
}

CNormalBase* createItemPowerItem(const CEvaluationNode* pNode)
{
  CNormalBase* pResult = NULL;
  CEvaluationNode::Type type = CEvaluationNode::type(pNode->getType());
  CEvaluationNodeOperator::SubType subType;
  switch (type)
    {
    case CEvaluationNode::OPERATOR:
      subType = (CEvaluationNodeOperator::SubType)CEvaluationNode::subType(pNode->getType());
      if (subType == CEvaluationNodeOperator::POWER)
        {
          if ((CEvaluationNode::type(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling())->getType())) == CEvaluationNode::NUMBER)
            {
              pResult = createItemPower(pNode);
            }
          else
            {
              pResult = createGeneralPower(pNode);
            }
        }
      else if (CEvaluationNodeOperator::MODULUS)
        {
          pResult = createGeneralPower(pNode);
        }
      else
        {
          pResult = createFraction(pNode);
        }
      break;
    case CEvaluationNode::NUMBER:
      pResult = createItem(pNode);
      break;
    case CEvaluationNode::FUNCTION:
      pResult = createFunction(pNode);
      break;
      /*
      case CEvaluationNode::CHOICE:
      break;
      */
    case CEvaluationNode::LOGICAL:
      throw std::exception();
      break;
    case CEvaluationNode::VARIABLE:
      pResult = createItem(pNode);
      break;
    case CEvaluationNode::CONSTANT:
      pResult = createItem(pNode);
      break;
    default:
      break;
    }
  return pResult;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalChoice& choice)
{
  // this will become a CEvaluationNodeChoice with an mpIf, an mpTrue and and
  // mpFalse
  CEvaluationNodeChoice* pChoiceNode = NULL;
  CEvaluationNode* pChild1 = convertToCEvaluationNode(choice.getCondition());
  if (pChild1 != NULL)
    {
      CEvaluationNode* pChild2 = convertToCEvaluationNode(choice.getTrueExpression());
      if (pChild2 != NULL)
        {
          CEvaluationNode* pChild3 = convertToCEvaluationNode(choice.getFalseExpression());
          if (pChild3 != NULL)
            {
              pChoiceNode = new CEvaluationNodeChoice(CEvaluationNodeChoice::IF, "IF");
              pChoiceNode->addChild(pChild1);
              pChoiceNode->addChild(pChild2);
              pChoiceNode->addChild(pChild3);
            }
        }
    }
  return pChoiceNode;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalChoiceLogical& choice)
{
  // this will become a CEvaluationNodeChoice with an mpIf, an mpTrue and and
  // mpFalse
  CEvaluationNodeChoice* pChoiceNode = NULL;
  CEvaluationNode* pChild1 = convertToCEvaluationNode(choice.getCondition());
  if (pChild1 != NULL)
    {
      CEvaluationNode* pChild2 = convertToCEvaluationNode(choice.getTrueExpression());
      if (pChild2 != NULL)
        {
          CEvaluationNode* pChild3 = convertToCEvaluationNode(choice.getFalseExpression());
          if (pChild3 != NULL)
            {
              pChoiceNode = new CEvaluationNodeChoice(CEvaluationNodeChoice::IF, "IF");
              pChoiceNode->addChild(pChild1);
              pChoiceNode->addChild(pChild2);
              pChoiceNode->addChild(pChild3);
            }
        }
    }
  return pChoiceNode;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalLogicalItem& item)
{
  CEvaluationNode* pLogicalNode = NULL;
  switch (item.getType())
    {
    case CNormalLogicalItem::TRUE:
      pLogicalNode = new CEvaluationNodeConstant(CEvaluationNodeConstant::TRUE, "TRUE");
      pLogicalNode->compile(NULL);
      break;
    case CNormalLogicalItem::FALSE:
      pLogicalNode = new CEvaluationNodeConstant(CEvaluationNodeConstant::TRUE, "FALSE");
      pLogicalNode->compile(NULL);
      break;
    case CNormalLogicalItem::EQ:
      pLogicalNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::EQ, "==");
      break;
    case CNormalLogicalItem::NE:
      pLogicalNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::NE, "!=");
      break;
    case CNormalLogicalItem::LT:
      pLogicalNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::LT, "<");
      break;
    case CNormalLogicalItem::GT:
      pLogicalNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::GT, ">");
      break;
    case CNormalLogicalItem::GE:
      pLogicalNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::GE, ">=");
      break;
    case CNormalLogicalItem::LE:
      pLogicalNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::LE, "<=");
      break;
    case CNormalLogicalItem::INVALID:
      break;
    }
  if (item.getType() != CNormalLogicalItem::TRUE && item.getType() != CNormalLogicalItem::FALSE)
    {
      CEvaluationNode* pChild1 = convertToCEvaluationNode(item.getLeft());
      if (pChild1 == NULL)
        {
          delete pLogicalNode;
          pLogicalNode = NULL;
        }
      else
        {
          CEvaluationNode* pChild2 = convertToCEvaluationNode(item.getRight());
          if (pChild2 == NULL)
            {
              delete pLogicalNode;
              pLogicalNode = NULL;
            }
          else
            {
              pLogicalNode->addChild(pChild1);
              pLogicalNode->addChild(pChild2);
              pLogicalNode->compile(NULL);
            }
        }
    }
  return pLogicalNode;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalLogical& logical)
{
  CEvaluationNode* pResult = NULL;
  bool error = false;
  CEvaluationNodeFunction* pNot = NULL;
  CNormalLogical::ItemSetOfSets::const_iterator it = logical.getAndSets().begin(), endit = logical.getAndSets().end();
  std::vector<CEvaluationNode*> andItems;
  while (it != endit && error == false)
    {
      CEvaluationNode* pTmpResult = NULL;
      if ((*it).first.size() == 1)
        {
          pTmpResult = convertToCEvaluationNode(*(*(*it).first.begin()).first);
          if ((*(*it).first.begin()).second == true)
            {
              pNot = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
              pNot->addChild(pTmpResult);
              pTmpResult = pNot;
            }
        }
      else if ((*it).first.size() > 1)
        {
          CNormalLogical::ItemSet::const_iterator innerit = (*it).first.begin(), innerendit = (*it).first.end();
          // create the not
          CEvaluationNode* pOrNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::OR, "OR");
          pTmpResult = pOrNode;
          while (innerit != innerendit && error == false)
            {
              CEvaluationNode* pItem = convertToCEvaluationNode(*(*innerit).first);
              if (pItem != NULL)
                {
                  if ((*innerit).second == true)
                    {
                      pNot = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
                      pNot->addChild(pItem);
                      pItem = pNot;
                    }
                  pOrNode->addChild(pItem);
                  pOrNode->addChild(new CEvaluationNodeLogical(CEvaluationNodeLogical::OR, "OR"));
                  pOrNode = dynamic_cast<CEvaluationNodeLogical*>(pOrNode->getChild()->getSibling());
                }
              else
                {
                  error = true;
                  delete pTmpResult;
                  pTmpResult = NULL;
                }
              ++innerit;
            }
          if (error == false)
            {
              // replace the parent of the current pOrNode with its first child;
              CEvaluationNode * pGrandParent = dynamic_cast<CEvaluationNode*>(pOrNode->getParent());
              pGrandParent->removeChild(pOrNode->getParent());
              pOrNode = dynamic_cast<CEvaluationNode*>(pOrNode->getParent());
              CEvaluationNode* pChild = dynamic_cast<CEvaluationNode*>(pOrNode->getChild());
              pOrNode->removeChild(pChild);
              pGrandParent->addChild(pChild);
              delete pOrNode;
            }
        }
      if (pTmpResult != NULL)
        {
          if ((*it).second == true)
            {
              pNot = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
              pNot->addChild(pTmpResult);
            }
          andItems.push_back(pTmpResult);
        }
      ++it;
    }
  CNormalLogical::ChoiceSetOfSets::const_iterator it2 = logical.getChoices().begin(), endit2 = logical.getChoices().end();
  while (it2 != endit2 && error == false)
    {
      CEvaluationNode* pTmpResult = NULL;
      if ((*it2).first.size() == 1)
        {
          pTmpResult = convertToCEvaluationNode(*(*(*it2).first.begin()).first);
          if ((*(*it2).first.begin()).second == true)
            {
              pNot = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
              pNot->addChild(pTmpResult);
              pTmpResult = pNot;
            }
        }
      else if ((*it2).first.size() > 1)
        {
          CNormalLogical::ChoiceSet::const_iterator innerit = (*it2).first.begin(), innerendit = (*it2).first.end();
          // create the not
          CEvaluationNode* pOrNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::OR, "OR");
          pTmpResult = pOrNode;
          while (innerit != innerendit && error != true)
            {
              CEvaluationNode* pItem = convertToCEvaluationNode(*(*innerit).first);
              if (pItem != NULL)
                {
                  if ((*innerit).second == true)
                    {
                      pNot = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
                      pNot->addChild(pItem);
                      pItem = pNot;
                    }
                  pOrNode->addChild(pItem);
                  pOrNode->addChild(new CEvaluationNodeLogical(CEvaluationNodeLogical::OR, "OR"));
                  pOrNode = dynamic_cast<CEvaluationNodeLogical*>(pOrNode->getChild()->getSibling());
                }
              else
                {
                  delete pTmpResult;
                  pTmpResult = NULL;
                  error = true;
                }
              ++innerit;
            }
          // replace the parent of the current pOrNode with its first child;
          if (error == false)
            {
              CEvaluationNode * pGrandParent = dynamic_cast<CEvaluationNode*>(pOrNode->getParent());
              pGrandParent->removeChild(pOrNode->getParent());
              pOrNode = dynamic_cast<CEvaluationNode*>(pOrNode->getParent());
              CEvaluationNode* pChild = dynamic_cast<CEvaluationNode*>(pOrNode->getChild());
              pOrNode->removeChild(pChild);
              pGrandParent->addChild(pChild);
              delete pOrNode;
            }
        }
      if (pTmpResult != NULL)
        {
          if ((*it2).second == true)
            {
              pNot = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
              pNot->addChild(pTmpResult);
            }
          andItems.push_back(pTmpResult);
        }
      ++it2;
    }
  if (!andItems.empty())
    {
      if (error == false)
        {
          if (andItems.size() == 1)
            {
              pResult = *andItems.begin();
            }
          else
            {
              std::vector<CEvaluationNode*>::iterator andit = andItems.begin(), andendit = andItems.end();
              CEvaluationNode* pAndNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
              pResult = pAndNode;
              while (andit != andendit)
                {
                  pAndNode->addChild(*andit);
                  pAndNode->addChild(new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND"));
                  pAndNode = dynamic_cast<CEvaluationNodeLogical*>(pAndNode->getChild()->getSibling());
                  ++andit;
                }
              // replace the parent of the current pAndNode with its first child;
              CEvaluationNode* pGrandParent = dynamic_cast<CEvaluationNode*>(pAndNode->getParent());
              pGrandParent->removeChild(pAndNode->getParent());
              pAndNode = dynamic_cast<CEvaluationNode*>(pAndNode->getParent());
              CEvaluationNode* pChild = dynamic_cast<CEvaluationNode*>(pAndNode->getChild());
              pAndNode->removeChild(pChild);
              pGrandParent->addChild(pChild);
              delete pAndNode;
            }
        }
      else
        {
          // an error has occured, we need to free the memory taken by all
          // andItems
          std::vector<CEvaluationNode*>::iterator andit = andItems.begin(), andendit = andItems.end();
          while (andit != andendit)
            {
              delete (*andit);
              ++andit;
            }
        }
    }
  if (pResult != NULL)
    {
      if (logical.isNegated() == true)
        {
          pNot = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
          pNot->addChild(pResult);
          pResult = pNot;
        }
      pResult->compile(NULL);
    }
  return pResult;
}

CNormalChoice* createChoice(const CEvaluationNode* pNode)
{
  CNormalChoice* pResult = NULL;
  if (pNode != NULL && CEvaluationNode::type(pNode->getType()) == CEvaluationNode::CHOICE)
    {
      CNormalLogical* pLogical = createLogical(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
      if (pLogical != NULL)
        {
          CNormalFraction* pTrueFraction = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));
          if (pTrueFraction != NULL)
            {
              // the false branch is optional
              const CEvaluationNode* pFalseBranch = dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()->getSibling());
              if (pFalseBranch != NULL)
                {
                  CNormalFraction* pFalseFraction = createNormalRepresentation(pFalseBranch);
                  if (pFalseFraction != NULL)
                    {
                      pResult = new CNormalChoice();
                      pResult->setCondition(*pLogical);
                      pResult->setTrueExpression(*pTrueFraction);
                      pResult->setFalseExpression(*pFalseFraction);
                      delete pFalseFraction;
                    }
                }
              else
                {
                  CNormalFraction* pFalseFraction = new CNormalFraction();
                  pResult = new CNormalChoice();
                  pResult->setCondition(*pLogical);
                  pResult->setTrueExpression(*pTrueFraction);
                  pResult->setFalseExpression(*pFalseFraction);
                  delete pFalseFraction;
                }
              delete pTrueFraction;
            }
          delete pLogical;
        }
    }
  return pResult;
}

CNormalChoiceLogical* createLogicalChoice(const CEvaluationNode* pNode)
{
  CNormalChoiceLogical* pResult = NULL;
  if (pNode != NULL && CEvaluationNode::type(pNode->getType()) == CEvaluationNode::CHOICE)
    {
      CNormalLogical* pLogical = createLogical(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
      if (pLogical != NULL)
        {
          CNormalLogical* pTrueLogical = createLogical(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));
          if (pTrueLogical != NULL)
            {
              // the false branch is optional
              const CEvaluationNode* pFalseBranch = dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()->getSibling());
              if (pFalseBranch != NULL)
                {
                  CNormalLogical* pFalseLogical = createLogical(pFalseBranch);
                  if (pFalseLogical != NULL)
                    {
                      pResult = new CNormalChoiceLogical();
                      pResult->setCondition(*pLogical);
                      pResult->setTrueExpression(*pTrueLogical);
                      pResult->setFalseExpression(*pFalseLogical);
                      delete pFalseLogical;
                    }
                }
              else
                {
                  pResult = new CNormalChoiceLogical();
                  pResult->setCondition(*pLogical);
                  pResult->setTrueExpression(*pTrueLogical);
                  CNormalLogical* pFalseLogical = new CNormalLogical();
                  pResult->setFalseExpression(*pFalseLogical);
                  delete pFalseLogical;
                }
              delete pTrueLogical;
            }
          delete pLogical;
        }
    }
  return pResult;
}

CNormalLogical* createLogical(const CEvaluationNode* pNode)
{
  CNormalLogical* pResult = NULL;
  if (pNode != NULL)
    {
      CEvaluationNode::Type type = pNode->getType();
      if (CEvaluationNode::type(type) == CEvaluationNode::CONSTANT)
        {
          if (((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(type)) == CEvaluationNodeConstant::TRUE || ((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(type)) == CEvaluationNodeConstant::FALSE)
            {
              CNormalLogicalItem* pLogicalItem = createLogicalItem(pNode);
              if (pLogicalItem != NULL)
                {
                  pResult = new CNormalLogical();
                  CNormalLogical::ItemSet tmp;
                  tmp.insert(std::make_pair(pLogicalItem, false));
                  pResult->getAndSets().insert(std::make_pair(tmp, false));
                }
            }
        }
      else if (CEvaluationNode::type(type) == CEvaluationNode::LOGICAL)
        {
          CNormalLogicalItem* pLogicalItem = NULL;
          CEvaluationNode* pOrNode = NULL;
          CEvaluationNode* pAndNode = NULL;
          const CEvaluationNode* pA = NULL;
          const CEvaluationNode* pB = NULL;
          CEvaluationNode* pNotNode = NULL;
          CNormalLogical* pLeftLogical = NULL;
          CNormalLogical::ChoiceSetOfSets::const_iterator it, endit;
          CNormalLogical::ItemSetOfSets::const_iterator it2, endit2;
          switch ((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(type))
            {
            case CEvaluationNodeLogical::EQ:
            case CEvaluationNodeLogical::NE:
            case CEvaluationNodeLogical::GT:
            case CEvaluationNodeLogical::LT:
            case CEvaluationNodeLogical::GE:
            case CEvaluationNodeLogical::LE:
              pLogicalItem = createLogicalItem(pNode);
              if (pLogicalItem != NULL)
                {
                  pResult = new CNormalLogical();
                  CNormalLogical::ItemSet tmp;
                  tmp.insert(std::make_pair(pLogicalItem, false));
                  pResult->getAndSets().insert(std::make_pair(tmp, false));
                }
              break;
            case CEvaluationNodeLogical::XOR:
              // replace A xor B by A OR B AND NOT(A AND B)
              pA = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
              pB = dynamic_cast<const CEvaluationNode*>(pA->getSibling());
              pAndNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
              pAndNode->addChild(pA->copyBranch());
              pAndNode->addChild(pB->copyBranch());
              pNotNode = new CEvaluationNodeFunction(CEvaluationNodeFunction::NOT, "NOT");
              pNotNode->addChild(pAndNode);
              pOrNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::OR, "OR");
              pOrNode->addChild(pA->copyBranch());
              pOrNode->addChild(pB->copyBranch());
              pAndNode = new CEvaluationNodeLogical(CEvaluationNodeLogical::AND, "AND");
              pAndNode->addChild(pOrNode);
              pAndNode->addChild(pNotNode);
              pResult = createLogical(pAndNode);
              delete pAndNode;
              break;
            case CEvaluationNodeLogical::AND:
              pLeftLogical = createLogical(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
              if (pLeftLogical != NULL)
                {
                  pLeftLogical->simplify();
                  CNormalLogical* pRightLogical = createLogical(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));
                  if (pRightLogical != NULL)
                    {
                      pRightLogical->simplify();
                      // integrate the items into a new logical item
                      // we have to create an AND set for every
                      // combination between two AND Sets from the
                      // two logicals
                      pResult = new CNormalLogical();
                      CNormalLogical::ChoiceSetOfSets::const_iterator it = pLeftLogical->getChoices().begin(), endit = pLeftLogical->getChoices().end();
                      while (it != endit)
                        {
                          CNormalLogical::ChoiceSetOfSets::const_iterator it2 = pRightLogical->getChoices().begin(), endit2 = pRightLogical->getChoices().end();
                          if ((*it).second == true) throw std::exception();
                          while (it2 != endit2)
                            {
                              // create an AND set from the two, but only
                              // if both don't have the NOT flag set
                              // which should always be the case since we
                              // called simplify on the items.
                              if ((*it2).second == true) throw std::exception();
                              CNormalLogical::ChoiceSet tmp;
                              CNormalLogical::ChoiceSet::const_iterator innerit = (*it).first.begin(), innerendit = (*it).first.end();
                              while (innerit != innerendit)
                                {
                                  tmp.insert(std::make_pair(new CNormalChoiceLogical(*(*innerit).first), (*innerit).second));
                                  ++innerit;
                                }
                              innerit = (*it2).first.begin(), innerendit = (*it2).first.end();
                              while (innerit != innerendit)
                                {
                                  tmp.insert(std::make_pair(new CNormalChoiceLogical(*(*innerit).first), (*innerit).second));
                                  ++innerit;
                                }
                              pResult->getChoices().insert(std::make_pair(tmp, false));
                              ++it2;
                            }
                          ++it;
                        }
                      CNormalLogical::ItemSetOfSets::const_iterator it2 = pLeftLogical->getAndSets().begin(), endit2 = pLeftLogical->getAndSets().end();
                      while (it2 != endit2)
                        {
                          CNormalLogical::ItemSetOfSets::const_iterator it3 = pRightLogical->getAndSets().begin(), endit3 = pRightLogical->getAndSets().end();
                          if ((*it2).second == true) throw std::exception();
                          while (it3 != endit3)
                            {
                              // create an AND set from the two, but only
                              // if both don't have the NOT flag set
                              // which should always be the case since we
                              // called simplify on the items.
                              if ((*it3).second == true) throw std::exception();
                              CNormalLogical::ItemSet tmp;
                              CNormalLogical::ItemSet::const_iterator innerit = (*it2).first.begin(), innerendit = (*it2).first.end();
                              while (innerit != innerendit)
                                {
                                  tmp.insert(std::make_pair(new CNormalLogicalItem(*(*innerit).first), (*innerit).second));
                                  ++innerit;
                                }
                              innerit = (*it3).first.begin(), innerendit = (*it3).first.end();
                              while (innerit != innerendit)
                                {
                                  tmp.insert(std::make_pair(new CNormalLogicalItem(*(*innerit).first), (*innerit).second));
                                  ++innerit;
                                }
                              pResult->getAndSets().insert(std::make_pair(tmp, false));
                              ++it3;
                            }
                          ++it2;
                        }
                    }
                }
              break;
            case CEvaluationNodeLogical::OR:
              // 1. create two logicals, one for the left side and one for the
              //    right side
              pResult = createLogical(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
              pLeftLogical = createLogical(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));
              // 2. add all or items from the second logical to the first and
              //    delete the second
              it = pLeftLogical->getChoices().begin(), endit = pLeftLogical->getChoices().end();
              while (it != endit)
                {
                  CNormalLogical::ChoiceSet tmpSet;
                  CNormalLogical::copySet((*it).first, tmpSet);
                  pResult->getChoices().insert(std::make_pair(tmpSet, (*it).second));
                  ++it;
                }
              it2 = pLeftLogical->getAndSets().begin(), endit2 = pLeftLogical->getAndSets().end();
              while (it2 != endit2)
                {
                  CNormalLogical::ItemSet tmpSet;
                  CNormalLogical::copySet((*it2).first, tmpSet);
                  pResult->getAndSets().insert(std::make_pair(tmpSet, (*it2).second));
                  ++it2;
                }
              delete pLeftLogical;
              break;
            default:
              break;
            }
        }
      else if (CEvaluationNode::type(type) == CEvaluationNode::FUNCTION && ((CEvaluationNodeFunction::SubType)CEvaluationNode::subType(type)) == CEvaluationNodeFunction::NOT)
        {
          pResult = createLogical(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
          if (pResult != NULL)
            {
              pResult->negate();
            }
        }
      else if (CEvaluationNode::type(type) == CEvaluationNode::CHOICE)
        {
          CNormalChoiceLogical* pLogicalChoice = createLogicalChoice(pNode);
          if (pLogicalChoice != NULL)
            {
              CNormalLogical::ChoiceSet tmp;
              tmp.insert(std::make_pair(pLogicalChoice, false));
              pResult = new CNormalLogical();
              pResult->getChoices().insert(std::make_pair(tmp, false));
            }
        }
    }
  //std::cout << pResult->debug();
  return pResult;
}

CNormalLogicalItem* createLogicalItem(const CEvaluationNode* pNode)
{
  CNormalLogicalItem* pResult = NULL;
  if (pNode != NULL)
    {
      CEvaluationNode::Type type = pNode->getType();
      if (CEvaluationNode::type(type) == CEvaluationNode::CONSTANT)
        {
          if (((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(type)) == CEvaluationNodeConstant::FALSE)
            {
              pResult = new CNormalLogicalItem();
              pResult->setType(CNormalLogicalItem::FALSE);
            }
          else if (((CEvaluationNodeConstant::SubType)CEvaluationNode::subType(type)) == CEvaluationNodeConstant::TRUE)
            {
              pResult = new CNormalLogicalItem();
              pResult->setType(CNormalLogicalItem::TRUE);
            }
        }
      if (CEvaluationNode::type(type) == CEvaluationNode::LOGICAL)
        {
          CNormalFraction* pFrac1 = NULL;
          CNormalFraction* pFrac2 = NULL;
          switch ((CEvaluationNodeLogical::SubType)CEvaluationNode::subType(type))
            {
            case CEvaluationNodeLogical::EQ:
              pResult = new CNormalLogicalItem();
              pResult->setType(CNormalLogicalItem::EQ);
              pFrac1 = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
              if (pFrac1 != NULL)
                {
                  pFrac2 = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));
                  if (pFrac2 != NULL)
                    {
                      pResult->setLeft(*pFrac1);
                      pResult->setRight(*pFrac2);
                      delete pFrac1;
                      delete pFrac2;
                    }
                  else
                    {
                      delete pFrac1;
                      pFrac1 = NULL;
                    }
                }
              break;
            case CEvaluationNodeLogical::NE:
              pResult = new CNormalLogicalItem();
              pResult->setType(CNormalLogicalItem::NE);
              pFrac1 = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
              if (pFrac1 != NULL)
                {
                  pFrac2 = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));
                  if (pFrac2 != NULL)
                    {
                      pResult->setLeft(*pFrac1);
                      pResult->setRight(*pFrac2);
                      delete pFrac1;
                      delete pFrac2;
                    }
                  else
                    {
                      delete pFrac1;
                      pFrac1 = NULL;
                    }
                }
              break;
            case CEvaluationNodeLogical::GT:
              pResult = new CNormalLogicalItem();
              pResult->setType(CNormalLogicalItem::GT);
              pFrac1 = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
              if (pFrac1 != NULL)
                {
                  pFrac2 = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));
                  if (pFrac2 != NULL)
                    {
                      pResult->setLeft(*pFrac1);
                      pResult->setRight(*pFrac2);
                      delete pFrac1;
                      delete pFrac2;
                    }
                  else
                    {
                      delete pFrac1;
                      pFrac1 = NULL;
                    }
                }
              break;
            case CEvaluationNodeLogical::LT:
              pResult = new CNormalLogicalItem();
              pResult->setType(CNormalLogicalItem::LT);
              pFrac1 = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
              if (pFrac1 != NULL)
                {
                  pFrac2 = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));
                  if (pFrac2 != NULL)
                    {
                      pResult->setLeft(*pFrac1);
                      pResult->setRight(*pFrac2);
                      delete pFrac1;
                      delete pFrac2;
                    }
                  else
                    {
                      delete pFrac1;
                      pFrac1 = NULL;
                    }
                }
              break;
            case CEvaluationNodeLogical::GE:
              pResult = new CNormalLogicalItem();
              pResult->setType(CNormalLogicalItem::GE);
              pFrac1 = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
              if (pFrac1 != NULL)
                {
                  pFrac2 = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));
                  if (pFrac2 != NULL)
                    {
                      pResult->setLeft(*pFrac1);
                      pResult->setRight(*pFrac2);
                      delete pFrac1;
                      delete pFrac2;
                    }
                  else
                    {
                      delete pFrac1;
                      pFrac1 = NULL;
                    }
                }
              break;
            case CEvaluationNodeLogical::LE:
              pResult = new CNormalLogicalItem();
              pResult->setType(CNormalLogicalItem::LE);
              pFrac1 = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
              if (pFrac1 != NULL)
                {
                  pFrac2 = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));
                  if (pFrac2 != NULL)
                    {
                      pResult->setLeft(*pFrac1);
                      pResult->setRight(*pFrac2);
                      delete pFrac1;
                      delete pFrac2;
                    }
                  else
                    {
                      delete pFrac1;
                      pFrac1 = NULL;
                    }
                }
              break;
            default:
              break;
            }
        }
    }
  /*
  std::cout << "Created a logical item: " << *pResult << std::endl;
  std::cout << "item left: " << pResult->getLeft() << std::endl;
  std::cout << "item right: " << pResult->getRight() << std::endl;
  */
  return pResult;
}
