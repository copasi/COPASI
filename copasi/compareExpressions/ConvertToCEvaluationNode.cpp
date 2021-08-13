// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#ifdef WIN32
# pragma warning (disable: 4786)
# pragma warning (disable: 4243)
// warning C4355: 'this' : used in base member initializer list
# pragma warning (disable: 4355)
#endif  // WIN32

#include <assert.h>
#include <sstream>
#include <exception>
#include <vector>

#include "ConvertToCEvaluationNode.h"

#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeOperator.h"
#include "copasi/function/CEvaluationNodeConstant.h"
#include "copasi/function/CEvaluationNodeDelay.h"
#include "copasi/function/CEvaluationNodeFunction.h"
#include "copasi/function/CEvaluationNodeNumber.h"
#include "copasi/function/CEvaluationNodeObject.h"
#include "copasi/function/CEvaluationNodeVariable.h"
#include "copasi/function/CEvaluationNodeChoice.h"
#include "copasi/function/CEvaluationNodeLogical.h"

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
#include "CNormalCall.h"
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
      CEvaluationNodeOperator* pDivision = new CEvaluationNodeOperator(CEvaluationNode::SubType::DIVIDE, "/");
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
  CEvaluationNode::SubType type = CEvaluationNode::SubType::INVALID;

  switch (item.getType())
    {
      case CNormalItem::CONSTANT:

        // create a CEvaluationNodeNumber
        if (item.getName() == "pi" || item.getName() == "PI")
          {
            type = (CEvaluationNode::SubType::PI);
          }
        else if (item.getName() == "EXPONENTIALE" || item.getName() == "exponentiale")
          {
            type = (CEvaluationNode::SubType::EXPONENTIALE);
          }
        else if (item.getName() == "TRUE" || item.getName() == "true")
          {
            type = (CEvaluationNode::SubType::True);
          }
        else if (item.getName() == "FALSE" || item.getName() == "false")
          {
            type = (CEvaluationNode::SubType::False);
          }
        else if (item.getName() == "INFINITY" || item.getName() == "infinity")
          {
            type = (CEvaluationNode::SubType::Infinity);
          }
        else if (item.getName() == "NAN" || item.getName() == "nan" || item.getName() == "Nan")
          {
            type = (CEvaluationNode::SubType::NaN);
          }

        pNode = new CEvaluationNodeConstant(type, item.getName());
        break;

      case CNormalItem::VARIABLE:
        // create a CEvaluationNodeVariable
        pNode = new CEvaluationNodeVariable(CEvaluationNode::SubType::DEFAULT, item.getName());
        break;
    }

  // TODO what about object nodes ?????
  return pNode;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalItemPower& itemPower)
{
  CEvaluationNode* pResult = NULL;

  if (fabs(itemPower.getExp() - 1.0) < 1e-12)
    {
      pResult = convertToCEvaluationNode(itemPower.getItem());
    }
  else
    {
      std::ostringstream sstream;
      CEvaluationNodeOperator* pPowerNode = new CEvaluationNodeOperator(CEvaluationNode::SubType::POWER, "^");
      CEvaluationNode* pChild = convertToCEvaluationNode(itemPower.getItem());
      pPowerNode->addChild(pChild);
      sstream << itemPower.getExp();
      pPowerNode->addChild(new CEvaluationNodeNumber(CEvaluationNode::SubType::DOUBLE, sstream.str()));
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
  CEvaluationNodeOperator* pMult = new CEvaluationNodeOperator(CEvaluationNode::SubType::MULTIPLY, "*");
  pResult = pMult;
  CEvaluationNode* pChild = NULL;

  while (it != itEnd)
    {
      assert(pMult != NULL);
      pChild = new CEvaluationNodeOperator(CEvaluationNode::SubType::MULTIPLY, "*");
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
      pChild = new CEvaluationNodeOperator(CEvaluationNode::SubType::MULTIPLY, "*");
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
      sstream.precision(std::numeric_limits<double>::digits10 + 2);
      sstream << product.getFactor();
      pResult = new CEvaluationNodeNumber(CEvaluationNode::SubType::DOUBLE, sstream.str());
    }
  else
    {
      const std::set<CNormalItemPower*, compareItemPowers >& itemPowers = product.getItemPowers();
      std::set<CNormalItemPower*, compareItemPowers >::const_iterator it = itemPowers.begin();
      std::set<CNormalItemPower*, compareItemPowers >::const_iterator itEnd = itemPowers.end();
      CEvaluationNode* pChild = NULL;
      std::vector<CEvaluationNode*> products;

      while (it != itEnd)
        {
          pChild = convertToCEvaluationNode(**it);
          products.push_back(pChild);
          ++it;
        }

      if (fabs(product.getFactor() - 1.0) >= 1e-12)
        {
          sstream.precision(std::numeric_limits<double>::digits10 + 2);
          sstream << product.getFactor();
          products.push_back(new CEvaluationNodeNumber(CEvaluationNode::SubType::DOUBLE, sstream.str()));
        }

      pResult = CNormalTranslation::createChain(&CNormalTranslation::TIMES_NODE, &CNormalTranslation::ONE_NODE, products);
    }

  return pResult;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalSum& sum)
{
  const std::set<CNormalFraction*>& fractions = sum.getFractions();
  std::set<CNormalFraction*>::const_iterator it = fractions.begin();
  std::set<CNormalFraction*>::const_iterator itEnd = fractions.end();
  std::vector<const CEvaluationNode*> summands;
  CEvaluationNode* pChild = NULL;

  while (it != itEnd)
    {
      pChild = convertToCEvaluationNode(**it);
      summands.push_back(pChild);
      ++it;
    }

  const std::set<CNormalProduct*, compareProducts >& products = sum.getProducts();

  std::set<CNormalProduct*, compareProducts >::const_iterator it2 = products.begin();

  std::set<CNormalProduct*, compareProducts >::const_iterator itEnd2 = products.end();

  while (it2 != itEnd2)
    {
      pChild = convertToCEvaluationNode(**it2);
      summands.push_back(pChild);
      ++it2;
    }

  CEvaluationNode* pResult = NULL;

  if (!summands.empty())
    {
      pResult = CNormalTranslation::createChain(&CNormalTranslation::PLUS_NODE, &CNormalTranslation::ZERO_NODE, summands);
    }
  else
    {
      pResult = CNormalTranslation::ZERO_NODE.copyBranch();
    }

  std::vector<const CEvaluationNode*>::iterator vIt = summands.begin(), vEndit = summands.end();

  while (vIt != vEndit)
    {
      delete *vIt;
      ++vIt;
    }

  return pResult;
}

/**
 * Create a fraction from a node. node is necessarily a DIVIDE operator if not the root node of the tree.
 * @return CNormalFraction*, pointer to newly created fraction.
 */
CNormalFraction* createFraction(const CEvaluationNode* node)
{
  CNormalFraction* pFraction = new CNormalFraction();

  if (node->getData() == "/")
    {
      // always executed except on root node possibly not
      // find a product chain and create new temporary nodes for the
      // numerator and denominator which are then converted to sums
      std::vector<const CEvaluationNode*> multiplications, divisions;
      CNormalTranslation::splitProduct(node, multiplications, divisions, false);
      std::vector<CEvaluationNode*> tmp;
      std::vector<const CEvaluationNode*>::const_iterator it = multiplications.begin(), endit = multiplications.end();

      while (it != endit)
        {
          tmp.push_back((*it)->copyBranch());
          ++it;
        }

      CEvaluationNode* pTmpNode = CNormalTranslation::createChain(&CNormalTranslation::TIMES_NODE, &CNormalTranslation::ONE_NODE, tmp);
      assert(pTmpNode != NULL);
      CNormalSum* pNum = createSum(pTmpNode);
      assert(pNum != NULL);
      delete pTmpNode;
      tmp.clear();
      it = divisions.begin();
      endit = divisions.end();

      while (it != endit)
        {
          tmp.push_back((*it)->copyBranch());
          ++it;
        }

      pTmpNode = CNormalTranslation::createChain(&CNormalTranslation::TIMES_NODE, &CNormalTranslation::ONE_NODE, tmp);
      assert(pTmpNode != NULL);
      CNormalSum* pDenom = createSum(pTmpNode);
      assert(pDenom != NULL);
      delete pTmpNode;
      pFraction->setNumerator(*pNum);
      pFraction->setDenominator(*pDenom);
      //pFraction->cancel();
      delete pNum;
      delete pDenom;
    }
  else
    {
      // only possible for root node
      CNormalSum* pNum = createSum(node);
      CNormalSum* pDenom = new CNormalSum();
      CNormalProduct* pProduct = new CNormalProduct();
      pDenom->add(*pProduct);
      pFraction->setNumerator(*pNum);
      pFraction->setDenominator(*pDenom);
      pFraction->cancel();
      delete pProduct;
      delete pNum;
      delete pDenom;
    }

  return pFraction;
};

/**
 * Create an item from an evaluation node that need not be of specific type.
 * @return CNormalItem*, pointer to newly created item.
 */
CNormalItem* createItem(const CEvaluationNode* pNode)
{
  CNormalItem* pItem = NULL;

  switch (pNode->mainType())
    {
      case CEvaluationNode::MainType::VARIABLE:
        pItem = new CNormalItem(pNode->buildInfix(), CNormalItem::VARIABLE);
        break;

      case CEvaluationNode::MainType::CONSTANT:
        pItem = new CNormalItem(pNode->buildInfix(), CNormalItem::CONSTANT);
        break;

      /*
      case CEvaluationNode::T_OPERATOR:
      if ((pNode->subType())==CEvaluationNode::S_POWER
          || (pNode->subType())==CEvaluationNode::S_MODULUS)
      {
          // calling createItem will add the wrong pNode for the
          // string into the lookup table
          CNormalItem * child1 = createItem(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));
          CNormalItem * child2 = createItem(dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling()));

          std::stringstream tmp;
          if ((child1->getType() == CNormalItem::VARIABLE) || (child1->getType() == CNormalItem::CONSTANT))
              tmp << *child1;
          else
          {
              tmp << "(" << *child1 << ")";
          }
          tmp << pNode->getData();
          if ((child2->getType() == CNormalItem::VARIABLE) || (child2->getType() == CNormalItem::CONSTANT))
              tmp << *child2;
          else
          {
              tmp << "(" << *child2 << ")";
          }

          pItem = new CNormalItem(tmp.str(), CNormalItem::FUNCTION);
          std::string s=tmp.str();
          std::map<std::string,const CEvaluationNode*>::const_iterator pos=str2eval.find(tmp.str());
          if(pos==str2eval.end())
          {
              CEvaluationNode::SubType type=CEvaluationNode::S_POWER;
              std::string s("^");
              if(pNode->getData()=="%")
              {
                  type=CEvaluationNode::S_MODULUS;
                  s="%";
              }
              CEvaluationNodeOperator* pNode=new CEvaluationNodeOperator(type,s);
              // when the child pNode is converted, the wrongly added
              // pNode from above is returned

              pNode->addChild(convertToCEvaluationNode(*child1));
              pNode->addChild(convertToCEvaluationNode(*child2));
              //pNode->printRecursively(std::cerr);
              str2eval[tmp.str()]=pNode;
          }
          delete child1;
          delete child2;
      }
      else // can be called only by createItem('OPERATOR pNode')
      {
          CNormalFraction * normedNode = createFraction(pNode);
          normedNode->simplify();
          CEvaluationNode* pTmpNode=convertToCEvaluationNode(*normedNode);
          std::stringstream tmp;
          tmp << *normedNode;
          pItem = new CNormalItem(tmp.str(), CNormalItem::FUNCTION);
          std::map<std::string,const CEvaluationNode*>::const_iterator pos=str2eval.find(normedNode->toString());
          if(pos==str2eval.end())
          {
              str2eval[tmp.str()]=pTmpNode;
          }

          delete normedNode;
      }
      break;
      */
      default:   //cases CALL, CHOICE, LOGICAL, OBJECT, VECTOR.  NUMBER should not occur!
        throw std::exception();
        break;
    }

  return pItem;
}

/**
 * Create an item power from an evaluation node.
 * Depending on the given node, we have to create different items.
 * Either we have to create a CNormalItem, a
 * CNormalGeneralPower, a function or a choice.
 */
CNormalItemPower * createItemPower(const CEvaluationNode* node)
{
  // make sure we create the correct item for the given node
  CNormalItemPower * pItemPower = new CNormalItemPower();

  if (node->mainType() == CEvaluationNode::MainType::OPERATOR && node->subType() == CEvaluationNode::SubType::POWER)
    {
      // check if the second child is a number
      if (dynamic_cast<const CEvaluationNode*>(node->getChild()->getSibling())->mainType() == CEvaluationNode::MainType::NUMBER)
        {
          // we set the exponent to that number
          pItemPower->setExp((C_FLOAT64)*dynamic_cast<const CEvaluationNodeNumber *>(node->getChild()->getSibling())->getValuePointer());
          // check if we can create a CNormalItem object for the fist child, else we
          // create a general power with exponent 1
          CEvaluationNode::MainType type = dynamic_cast<const CEvaluationNode*>(node->getChild())->mainType();

          if (type == CEvaluationNode::MainType::CONSTANT || type == CEvaluationNode::MainType::OBJECT || type == CEvaluationNode::MainType::VARIABLE || type == CEvaluationNode::MainType::FUNCTION || type == CEvaluationNode::MainType::CHOICE || type == CEvaluationNode::MainType::CALL || type == CEvaluationNode::MainType::LOGICAL)
            {
              CNormalBase* pItem = createItemPowerItem(dynamic_cast<const CEvaluationNode*>(node->getChild()));
              assert(pItem != NULL);
              pItemPower->setItem(*pItem);
              delete pItem;
            }
          else
            {
              // create a general power for the child node
              CNormalGeneralPower* pGeneralPower = createGeneralPower(dynamic_cast<const CEvaluationNode*>(node->getChild()));
              assert(pGeneralPower != NULL);
              pItemPower->setItem(*pGeneralPower);
              delete pGeneralPower;
            }
        }
      else
        {
          // create a general power for the node
          CNormalGeneralPower* pGeneralPower = createGeneralPower(node);
          assert(pGeneralPower != NULL);
          pItemPower->setItem(*pGeneralPower);
          pItemPower->setExp(1.0);
          delete pGeneralPower;
        }
    }
  else if (node->mainType() == CEvaluationNode::MainType::FUNCTION)
    {
      if ((node->subType()) == CEvaluationNode::SubType::MINUS)
        {
          // multiply the second node by -1 and call createItempower with the
          // result
          CEvaluationNodeNumber* pNumberNode = new CEvaluationNodeNumber(CEvaluationNode::SubType::DOUBLE, "-1.0");
          CEvaluationNodeOperator* pOperatorNode = new CEvaluationNodeOperator(CEvaluationNode::SubType::MULTIPLY, "*");
          pOperatorNode->addChild(pNumberNode);
          pOperatorNode->addChild(dynamic_cast<const CEvaluationNode*>(node->getChild())->copyBranch());
          // delete the old item power object
          delete pItemPower;
          // create a new item power object by calling this method again with
          // the newly created multiplication node
          pItemPower = createItemPower(pOperatorNode);
          // delete the multiplication node
          delete pOperatorNode;
        }
      else
        {
          CNormalFunction* pFunction = createFunction(node);
          assert(pFunction != NULL);
          pItemPower->setItem(*pFunction);
          delete pFunction;
          pItemPower->setExp(1.0);
        }
    }
  else if (node->mainType() == CEvaluationNode::MainType::CALL || node->mainType() == CEvaluationNode::MainType::DELAY)
    {
      CNormalCall* pCall = createCall(node);
      assert(pCall != NULL);
      pItemPower->setItem(*pCall);
      delete pCall;
      pItemPower->setExp(1.0);
    }
  else if (node->mainType() == CEvaluationNode::MainType::CHOICE)
    {
      CNormalChoice* pChoice = createChoice(node);
      assert(pChoice != NULL);
      pItemPower->setItem(*pChoice);
      delete pChoice;
      pItemPower->setExp(1.0);
    }
  else if (node->mainType() == CEvaluationNode::MainType::CONSTANT || node->mainType() == CEvaluationNode::MainType::OBJECT || node->mainType() == CEvaluationNode::MainType::VARIABLE)
    {
      CNormalItem* pItem = createItem(node);
      assert(pItem != NULL);
      pItemPower->setItem(*pItem);
      delete pItem;
      pItemPower->setExp(1.0);
    }
  else if (node->mainType() == CEvaluationNode::MainType::LOGICAL)
    {
      CNormalBase* pItem = createItemPowerItem(node);
      assert(pItem != NULL);
      pItemPower->setItem(*pItem);
      delete pItem;
      pItemPower->setExp(1.0);
    }
  else
    {
      // create a general power for the node
      CNormalGeneralPower* pGeneralPower = createGeneralPower(node);
      assert(pGeneralPower != NULL);
      pItemPower->setItem(*pGeneralPower);
      pItemPower->setExp(1.0);
      delete pGeneralPower;
    }

  return pItemPower;
}

/*
 * Create a product from an evaluation node that is not necessarily a multiply operator.
 * @return CNormalProduct*, pointer to newly created product.
 */
CNormalProduct * createProduct(const CEvaluationNode* node)
{
  CNormalProduct * pProduct = new CNormalProduct();

  if (node->mainType() == CEvaluationNode::MainType::OPERATOR && node->subType() == CEvaluationNode::SubType::MULTIPLY)
    {
      // find the product chain, if there are divisions, we have to create a
      // general power, else we create a product with as many items as the
      // multiplication vector has entries
      std::vector<const CEvaluationNode*> multiplications, divisions;
      CNormalTranslation::splitProduct(node, multiplications, divisions, false);
      double factor = 1.0;

      if (divisions.empty())
        {
          std::vector<const CEvaluationNode*>::const_iterator it = multiplications.begin(), endit = multiplications.end();
          CNormalItemPower* pItemPower = NULL;

          while (it != endit)
            {
              // check if the node is a pure number
              // if so, use it to update the factor
              // instead of creating an item for it
              if ((*it)->mainType() == CEvaluationNode::MainType::NUMBER)
                {
                  factor *= *dynamic_cast<const CEvaluationNodeNumber *>(*it)->getValuePointer();
                }
              else
                {
                  pItemPower = createItemPower(*it);
                  assert(pItemPower != NULL);
                  pProduct->multiply(*pItemPower);
                  delete pItemPower;
                }

              ++it;
            }
        }
      else
        {
          CEvaluationNodeOperator* pTmpOperator = new CEvaluationNodeOperator(CEvaluationNode::SubType::DIVIDE, "/");
          std::vector<CEvaluationNode*> tmp;
          std::vector<const CEvaluationNode*>::const_iterator it = multiplications.begin(), endit = multiplications.end();
          // check if the multiplications and divisions contain only numbers
          // in that case, done create a general item
          bool empty = false;

          while (it != endit)
            {
              // check if the node is a pure number
              // if so, use it to update the factor
              // instead of adding it to the factor
              if ((*it)->mainType() == CEvaluationNode::MainType::NUMBER)
                {
                  factor *= *dynamic_cast<const CEvaluationNodeNumber *>(*it)->getValuePointer();
                }
              else
                {
                  tmp.push_back((*it)->copyBranch());
                }

              ++it;
            }

          empty = tmp.empty();
          CEvaluationNode* pTmpNode1 = NULL;

          // if we have non number nodes, we need to combine those again into a
          // multiplication chain
          // otherwise the numerator is 1
          if (!empty)
            {
              pTmpNode1 = CNormalTranslation::createChain(&CNormalTranslation::TIMES_NODE, &CNormalTranslation::ONE_NODE, tmp);
            }
          else
            {
              pTmpNode1 = CNormalTranslation::ONE_NODE.copyBranch();
            }

          pTmpOperator->addChild(pTmpNode1);
          tmp.clear();
          it = divisions.begin();
          endit = divisions.end();

          while (it != endit)
            {
              // check if the node is a pure number
              // if so, use it to update the factor
              // instead of adding it to the vector
              if ((*it)->mainType() == CEvaluationNode::MainType::NUMBER)
                {
                  factor /= *dynamic_cast<const CEvaluationNodeNumber *>(*it)->getValuePointer();
                }
              else
                {
                  tmp.push_back((*it)->copyBranch());
                }

              ++it;
            }

          // if tmp was empty both times, empty must be true
          empty = (empty & tmp.empty());

          if (!empty)
            {
              CNormalItemPower* pItemPower = NULL;

              if (!tmp.empty())
                {
                  pTmpNode1 = CNormalTranslation::createChain(&CNormalTranslation::TIMES_NODE, &CNormalTranslation::ONE_NODE, tmp);
                  pTmpOperator->addChild(pTmpNode1);
                  pItemPower = createItemPower(pTmpOperator);
                }
              else
                {
                  pItemPower = createItemPower(pTmpNode1);
                }

              assert(pItemPower != NULL);
              pProduct->multiply(*pItemPower);
              delete pItemPower;
            }

          delete pTmpOperator;
        }

      pProduct->setFactor(factor);
    }
  else if (node->mainType() == CEvaluationNode::MainType::NUMBER)
    {
      double factor = *dynamic_cast<const CEvaluationNodeNumber *>(node)->getValuePointer();
      // set the factor
      pProduct->setFactor(factor);
    }
  else
    {
      // we create the appropriate item
      CNormalItemPower* pItemPower = createItemPower(node);
      assert(pItemPower != NULL);
      pProduct->multiply(*pItemPower);
      delete pItemPower;
    }

  return pProduct;
}

/** THIS CODE should be obsolete, RG (06/04/6.2008)
 * Create a product from an evaluation node that is not necessarily a multiply operator.
 * @return CNormalProduct*, pointer to newly created product.
 */
//CNormalProduct * createProduct(const CEvaluationNode* node)
//{
//  CNormalProduct * product = new CNormalProduct();
//  CNormalChoice * pChoice = NULL;
//  switch (node->mainType())
//    {
//    case CEvaluationNode::T_OPERATOR: // PLUS(->createSum), MINUS(translated as +(-..)) and DIVIDE(->createFraction) do not occur.
//      if (node->getData() == "^")
//        {
//          if (CEvaluationNode::type(static_cast<const CEvaluationNode*>(node->getChild()->getSibling())->getType()) == CEvaluationNode::T_NUMBER &&
//              (node->getChild()->getChild() == NULL || CEvaluationNode::type(static_cast<const CEvaluationNode*>(node->getChild())->getType()) == CEvaluationNode::T_CHOICE || CEvaluationNode::type(static_cast<const CEvaluationNode*>(node->getChild())->getType()) == CEvaluationNode::T_FUNCTION))
//            {
//              CNormalItemPower* power = createItemPower(node);
//              product->multiply(*power);
//              delete power;
//}
//          else
//            {
//              CNormalGeneralPower* item = createGeneralPower(node);
//              product->multiply(*item);
//              delete item;
//}
//}
//      else if (node->getData() == "*")
//        {
//          CNormalProduct* product1 = createProduct(static_cast<const CEvaluationNode*>(node->getChild()));
//          if (product1 != NULL)
//            {
//              CNormalProduct* product2 = createProduct(static_cast<const CEvaluationNode*>(node->getChild()->getSibling()));
//              if (product2 != NULL)
//                {
//                  product->multiply(*product1);
//                  product->multiply(*product2);
//                  delete product2;
//}
//              else
//                {
//                  product = NULL;
//}
//              delete product1;
//}
//          else
//            {
//              product = NULL;
//}
//}
//      else if (node->getData() == "%")
//
//        {
//          CNormalGeneralPower* item = createGeneralPower(node);
//          product->multiply(*item);
//          delete item;
//}
//      else
//        {
//          delete product;
//          product = NULL;
//}
//      break;
//    case CEvaluationNode::T_NUMBER:
//      product->multiply(node->value());
//      break;
//    case CEvaluationNode::T_FUNCTION:
//      if ((node->subType()) == CEvaluationNode::S_MINUS)
//        {
//          product->multiply(-1.0);
//          CNormalProduct * product2 = createProduct(dynamic_cast<const CEvaluationNode*>(node->getChild()));
//          assert(product2 != NULL);
//          product->multiply(*product2);
//          delete product2;
//}
//      else if ((node->subType()) == CEvaluationNode::S_PLUS)
//        {
//          CNormalProduct * product2 = createProduct(dynamic_cast<const CEvaluationNode*>(node->getChild()));
//          assert(product2 != NULL);
//          product->multiply(*product2);
//          delete product2;
//}
//      else
//        {
//          CNormalFunction * item = createFunction(node);
//          product->multiply(*item);
//          delete item;
//}
//      break;
//    case CEvaluationNode::T_LOGICAL:
//      throw std::exception(/*"Error. Logical Nodes are not allowed here."*/);
//      break;
//    case CEvaluationNode::T_CHOICE:
//      pChoice = createChoice(dynamic_cast<const CEvaluationNode*>(node));
//      product->multiply(*pChoice);
//      delete pChoice;
//      break;
//    default:   //cases VARIABLE, CONSTANT, OBJECT, VECTOR
//      CNormalItem * item = createItem(node);
//      product->multiply(*item);
//      delete item;
//      break;
//}
//  return product;
//}

/**
 * Create a sum from an evaluation node -node does not need to be a PLUS operator!
 * @return CNormalSum*, pointer to newly created sum
 */
CNormalSum* createSum(const CEvaluationNode* node)
{
  CNormalSum* pSum = new CNormalSum();

  if (node->mainType() == CEvaluationNode::MainType::OPERATOR && (node->subType() == CEvaluationNode::SubType::MINUS || node->subType() == CEvaluationNode::SubType::PLUS))
    {
      // find a summation chain and create a product node for each addition and
      // subtraction node
      std::vector<const CEvaluationNode*> additions, subtractions;
      CNormalTranslation::splitSum(node, additions, subtractions, false);
      std::vector<const CEvaluationNode*>::iterator it = additions.begin(), endit = additions.end();
      CNormalProduct* pProduct = NULL;

      while (it != endit)
        {
          pProduct = createProduct(*it);
          assert(pProduct != NULL);
          pSum->add(*pProduct);
          delete pProduct;
          ++it;
        }

      it = subtractions.begin(), endit = subtractions.end();

      while (it != endit)
        {
          pProduct = createProduct(*it);
          assert(pProduct != NULL);
          // since these are subtractions, we need to set the factor the -1.0
          // times the old factor
          pProduct->setFactor(-1.0 * pProduct->getFactor());
          pSum->add(*pProduct);
          delete pProduct;
          ++it;
        }
    }
  else
    {
      // create a sum and add the product made from the given node
      CNormalProduct* pProduct = createProduct(node);
      assert(pProduct != NULL);
      pSum->add(*pProduct);
      delete pProduct;
      /* This code should be obsolete, RG (4.6.2008)
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
          if (product != NULL)
            {
              sum->add(*product);
              delete product;
            }
          else
            {
              CNormalFraction* pFraction = createFraction(node);
              sum->add(*pFraction);
              delete pFraction;
            }
          return sum;
        }
        */
    }

  return pSum;
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
  CEvaluationNode* pTmp2 = node->copyBranch();
  CEvaluationNode* pTmp = CNormalTranslation::expandProducts(pTmp2);

  if (pTmp != NULL)
    {
      delete pTmp2;
    }
  else
    {
      pTmp = pTmp2;
    }

  pTmp2 = CNormalTranslation::newEvaluateNumbers(pTmp);

  if (pTmp2 != NULL)
    {
      delete pTmp;
    }
  else
    {
      pTmp2 = pTmp;
    }

  CEvaluationNode::MainType type = pTmp2->mainType();

  switch (type)
    {
      case CEvaluationNode::MainType::NUMBER:
      case CEvaluationNode::MainType::OPERATOR:
      case CEvaluationNode::MainType::CONSTANT:
      case CEvaluationNode::MainType::VARIABLE:
      case CEvaluationNode::MainType::CHOICE:
      case CEvaluationNode::MainType::LOGICAL:
      case CEvaluationNode::MainType::FUNCTION:
      case CEvaluationNode::MainType::CALL:
      case CEvaluationNode::MainType::DELAY:
        pFrac = createFraction(pTmp2);
        break;

      default:
        assert(false);
        break;
    }

  if (pTmp2 != NULL)
    {
      delete pTmp2;
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
  else if (dynamic_cast<const CNormalCall*>(&base) != NULL)
    {
      pNode = convertToCEvaluationNode(dynamic_cast<const CNormalCall&>(base));
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
        pResult = new CEvaluationNodeOperator(CEvaluationNode::SubType::POWER, "^");
        break;

      case CNormalGeneralPower::MODULO:
        pResult = new CEvaluationNodeOperator(CEvaluationNode::SubType::MODULUS, "%");
        break;

      case CNormalGeneralPower::INVALID:
        break;
    }

  if (pResult != NULL)
    {
      if (pow.getRight().checkIsOne())
        {
          delete pResult;
          pResult = convertToCEvaluationNode(pow.getLeft());
        }
      else
        {
          CEvaluationNode* pChild = convertToCEvaluationNode(pow.getLeft());
          pResult->addChild(pChild);
          pChild = convertToCEvaluationNode(pow.getRight());
          pResult->addChild(pChild);
        }
    }

  return pResult;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalCall& call)
{
  CEvaluationNode* pCall = NULL;

  // check if the name contains any non-whitespace characters at all
  if (call.getName().find_first_not_of("\t\r\n ") != std::string::npos)
    {
      CEvaluationNode::SubType type = CEvaluationNode::SubType::INVALID;

      switch (call.getType())
        {
          case CNormalCall::EXPRESSION:
            type = CEvaluationNode::SubType::EXPRESSION;
            break;

          case CNormalCall::FUNCTION:
            type = CEvaluationNode::SubType::FUNCTION;
            break;

          case CNormalCall::DELAY:
            pCall = new CEvaluationNodeDelay(CEvaluationNode::SubType::DELAY, "delay");
            break;

          case CNormalCall::INVALID:
            break;
        }

      if (!pCall)
        {
          pCall = new CEvaluationNodeCall(type, call.getName());
        }

      const std::vector<CNormalFraction*>& children = call.getFractions();

      std::vector<CNormalFraction*>::const_iterator it = children.begin(), endit = children.end();

      while (it != endit)
        {
          CEvaluationNode* pChild = convertToCEvaluationNode(**it);
          assert(pChild != NULL);
          pCall->addChild(pChild);
          ++it;
        }
    }

  return pCall;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalFunction& fun)
{
  CEvaluationNode* pResult = NULL;
  std::string data;
  CEvaluationNode::SubType subType = CEvaluationNode::SubType::INVALID;

  switch (fun.getType())
    {
      case CNormalFunction::LOG:
        subType = CEvaluationNode::SubType::LOG;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::LOG10:
        subType = CEvaluationNode::SubType::LOG10;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::EXP:
        subType = CEvaluationNode::SubType::EXP;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::SIN:
        subType = CEvaluationNode::SubType::SIN;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction:: COS:
        subType = CEvaluationNode::SubType::COS;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::TAN:
        subType = CEvaluationNode::SubType::TAN;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::SEC:
        subType = CEvaluationNode::SubType::SEC;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::CSC:
        subType = CEvaluationNode::SubType::CSC;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::COT:
        subType = CEvaluationNode::SubType::COT;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::SINH:
        subType = CEvaluationNode::SubType::SINH;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::COSH:
        subType = CEvaluationNode::SubType::COSH;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::TANH:
        subType = CEvaluationNode::SubType::TANH;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::SECH:
        subType = CEvaluationNode::SubType::SECH;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::CSCH:
        subType = CEvaluationNode::SubType::CSCH;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::COTH:
        subType = CEvaluationNode::SubType::COTH;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::ARCSIN:
        subType = CEvaluationNode::SubType::ARCSIN;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::ARCCOS:
        subType = CEvaluationNode::SubType::ARCCOS;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::ARCTAN:
        subType = CEvaluationNode::SubType::ARCTAN;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::ARCSEC:
        subType = CEvaluationNode::SubType::ARCSEC;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::ARCCSC:
        subType = CEvaluationNode::SubType::ARCCSC;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::ARCCOT:
        subType = CEvaluationNode::SubType::ARCCOT;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::ARCSINH:
        subType = CEvaluationNode::SubType::ARCSINH;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::ARCCOSH:
        subType = CEvaluationNode::SubType::ARCCOSH;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::ARCTANH:
        subType = CEvaluationNode::SubType::ARCTANH;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::ARCSECH:
        subType = CEvaluationNode::SubType::ARCSECH;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::ARCCSCH:
        subType = CEvaluationNode::SubType::ARCCSCH;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::ARCCOTH:
        subType = CEvaluationNode::SubType::ARCCOTH;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::SQRT:
        subType = CEvaluationNode::SubType::SQRT;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::ABS:
        subType = CEvaluationNode::SubType::ABS;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::FLOOR:
        subType = CEvaluationNode::SubType::FLOOR;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::CEIL:
        subType = CEvaluationNode::SubType::CEIL;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::FACTORIAL:
        subType = CEvaluationNode::SubType::FACTORIAL;
        data = CNormalFunction::NAMES[fun.getType()];
        break;

      case CNormalFunction::INVALID:
        data = "@";
        break;
    }

  pResult = new CEvaluationNodeFunction(subType, data);

  if (subType != CEvaluationNode::SubType::INVALID)
    {
      CEvaluationNode* pChild = convertToCEvaluationNode(fun.getFraction());
      pResult->addChild(pChild);
    }

  return pResult;
}

/**
 * Create an general power from an evaluation node.
 * if it is a power node, create a for each child and set base and exponent,
 * else only create the base from the node and set the exponent to 1
 * @return CNormalItemPower*, pointer to newly created general power (or modulo).
 */
CNormalGeneralPower * createGeneralPower(const CEvaluationNode* node)
{
  CNormalGeneralPower* pPow = NULL;

  if (node != NULL)
    {
      if (node->mainType() == CEvaluationNode::MainType::OPERATOR)
        {
          if ((node->subType()) == CEvaluationNode::SubType::POWER)
            {
              pPow = new CNormalGeneralPower();
              pPow->setType(CNormalGeneralPower::POWER);
            }
          else if ((node->subType()) == CEvaluationNode::SubType::MODULUS)
            {
              pPow = new CNormalGeneralPower();
              pPow->setType(CNormalGeneralPower::MODULO);
            }

          if (pPow != NULL)
            {
              // add the left and the right side
              CNormalFraction* pBase = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(node->getChild()));
              CNormalFraction* pExponent = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(node->getChild()->getSibling()));
              assert(pBase != NULL);
              assert(pExponent != NULL);
              pPow->setLeft(*pBase);
              pPow->setRight(*pExponent);
              delete pBase;
              delete pExponent;
            }
          else
            {
              // create a fraction for the base and a unit fraction for the exponent
              pPow = new CNormalGeneralPower();
              pPow->setType(CNormalGeneralPower::POWER);
              CNormalFraction* pBase = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(node));
              CEvaluationNode* pTmpNode = new CEvaluationNodeNumber(CEvaluationNode::SubType::DOUBLE, "1.0");
              CNormalFraction* pExponent = createNormalRepresentation(pTmpNode);
              delete pTmpNode;
              assert(pBase != NULL);
              assert(pExponent != NULL);
              pPow->setLeft(*pBase);
              pPow->setRight(*pExponent);
              delete pBase;
              delete pExponent;
            }
        }
      else
        {
          // create a fraction for the base and a unit fraction for the exponent
          pPow = new CNormalGeneralPower();
          pPow->setType(CNormalGeneralPower::POWER);
          CNormalFraction* pBase = createNormalRepresentation(dynamic_cast<const CEvaluationNode*>(node));
          CEvaluationNode* pTmpNode = new CEvaluationNodeNumber(CEvaluationNode::SubType::DOUBLE, "1.0");
          CNormalFraction* pExponent = createNormalRepresentation(pTmpNode);
          delete pTmpNode;
          assert(pBase != NULL);
          assert(pExponent != NULL);
          pPow->setLeft(*pBase);
          pPow->setRight(*pExponent);
          delete pBase;
          delete pExponent;
        }
    }

  return pPow;
}

/**
 * Create an function call from an evaluation node.
 * @return CNormalCall*, pointer to newly created call
 */
CNormalCall * createCall(const CEvaluationNode* node)
{
  CNormalCall* pCall = NULL;
  CEvaluationNode::MainType type = node->mainType();

  if (type == CEvaluationNode::MainType::CALL || type == CEvaluationNode::MainType::DELAY)
    {
      // create a call object and add all children
      pCall = new CNormalCall();
      // set the name
      pCall->setName(node->getData());
      const CEvaluationNode* pChild = dynamic_cast<const CEvaluationNode*>(node->getChild());

      while (pChild != NULL)
        {
          CNormalFraction* pFraction = createNormalRepresentation(pChild);
          assert(pFraction != NULL);
          pCall->add(*pFraction);
          delete pFraction;
          pChild = dynamic_cast<const CEvaluationNode*>(pChild->getSibling());
        }

      if (type == CEvaluationNode::MainType::DELAY)
        {
          pCall->setType(CNormalCall::DELAY);
        }
      else
        {
          CEvaluationNode::SubType subType = node->subType();

          switch (subType)
            {
              case CEvaluationNode::SubType::EXPRESSION:
                pCall->setType(CNormalCall::EXPRESSION);
                break;

              case CEvaluationNode::SubType::FUNCTION:
                pCall->setType(CNormalCall::FUNCTION);
                break;

              case CEvaluationNode::SubType::INVALID:
                pCall->setType(CNormalCall::INVALID);
                break;

              default:
                break;
            }
        }
    }

  return pCall;
}

/**
 * Create an function from an evaluation node.
 * @return CNormalFunction*, pointer to newly created function
 */
CNormalFunction * createFunction(const CEvaluationNode* node)
{
  CNormalFunction* pFun = NULL;
  CEvaluationNode::MainType type = node->mainType();

  if (type == CEvaluationNode::MainType::FUNCTION)
    {
      CNormalFunction::Type type = CNormalFunction::INVALID;

      switch (node->subType())
        {
          case CEvaluationNode::SubType::LOG:
            type = CNormalFunction::LOG;
            break;

          case CEvaluationNode::SubType::LOG10:
            type = CNormalFunction::LOG10;
            break;

          case CEvaluationNode::SubType::EXP:
            type = CNormalFunction::EXP;
            break;

          case CEvaluationNode::SubType::SIN:
            type = CNormalFunction::SIN;
            break;

          case CEvaluationNode::SubType::COS:
            type = CNormalFunction::COS;
            break;

          case CEvaluationNode::SubType::TAN:
            type = CNormalFunction::TAN;
            break;

          case CEvaluationNode::SubType::SEC:
            type = CNormalFunction::SEC;
            break;

          case CEvaluationNode::SubType::CSC:
            type = CNormalFunction::CSC;
            break;

          case CEvaluationNode::SubType::COT:
            type = CNormalFunction::COT;
            break;

          case CEvaluationNode::SubType::SINH:
            type = CNormalFunction::SINH;
            break;

          case CEvaluationNode::SubType::COSH:
            type = CNormalFunction::COSH;
            break;

          case CEvaluationNode::SubType::TANH:
            type = CNormalFunction::TANH;
            break;

          case CEvaluationNode::SubType::SECH:
            type = CNormalFunction::SECH;
            break;

          case CEvaluationNode::SubType::CSCH:
            type = CNormalFunction::CSCH;
            break;

          case CEvaluationNode::SubType::COTH:
            type = CNormalFunction::COTH;
            break;

          case CEvaluationNode::SubType::ARCSIN:
            type = CNormalFunction::ARCSIN;
            break;

          case CEvaluationNode::SubType::ARCCOS:
            type = CNormalFunction::ARCCOS;
            break;

          case CEvaluationNode::SubType::ARCTAN:
            type = CNormalFunction::ARCTAN;
            break;

          case CEvaluationNode::SubType::ARCSEC:
            type = CNormalFunction::ARCSEC;
            break;

          case CEvaluationNode::SubType::ARCCSC:
            type = CNormalFunction::ARCCSC;
            break;

          case CEvaluationNode::SubType::ARCCOT:
            type = CNormalFunction::ARCCOT;
            break;

          case CEvaluationNode::SubType::ARCSINH:
            type = CNormalFunction::ARCSINH;
            break;

          case CEvaluationNode::SubType::ARCCOSH:
            type = CNormalFunction::ARCCOSH;
            break;

          case CEvaluationNode::SubType::ARCTANH:
            type = CNormalFunction::ARCTANH;
            break;

          case CEvaluationNode::SubType::ARCSECH:
            type = CNormalFunction::ARCSECH;
            break;

          case CEvaluationNode::SubType::ARCCSCH:
            type = CNormalFunction::ARCCSCH;
            break;

          case CEvaluationNode::SubType::ARCCOTH:
            type = CNormalFunction::ARCCOTH;
            break;

          case CEvaluationNode::SubType::SQRT:
            type = CNormalFunction::SQRT;
            break;

          case CEvaluationNode::SubType::ABS:
            type = CNormalFunction::ABS;
            break;

          case CEvaluationNode::SubType::FLOOR:
            type = CNormalFunction::FLOOR;
            break;

          case CEvaluationNode::SubType::CEIL:
            type = CNormalFunction::CEIL;
            break;

          case CEvaluationNode::SubType::FACTORIAL:
            type = CNormalFunction::FACTORIAL;
            break;

          case CEvaluationNode::SubType::INVALID:
          default:
            assert(false);
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
  // CEvaluationNodeLogical, CEvaluationNode::S_NOT or
  // CEvaluationNode::S_(TRUE|FALSE)
  if ((pNode->mainType() == CEvaluationNode::MainType::LOGICAL) ||
      ((pNode->mainType() == CEvaluationNode::MainType::FUNCTION && (pNode->subType()) == CEvaluationNode::SubType::NOT)) ||
      (pNode->mainType() == CEvaluationNode::MainType::CONSTANT && (((pNode->subType()) == CEvaluationNode::SubType::True) || ((pNode->subType()) == CEvaluationNode::SubType::False)))
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
  CEvaluationNode::MainType type = pNode->mainType();
  CEvaluationNode::SubType subType;

  switch (type)
    {
      case CEvaluationNode::MainType::OPERATOR:
        subType = pNode->subType();

        if (subType == CEvaluationNode::SubType::POWER)
          {
            if (dynamic_cast<const CEvaluationNode*>(pNode->getChild()->getSibling())->mainType() == CEvaluationNode::MainType::NUMBER)
              {
                pResult = createItemPower(pNode);
              }
            else
              {
                pResult = createGeneralPower(pNode);
              }
          }
        else if (subType == CEvaluationNode::SubType::MODULUS)
          {
            pResult = createGeneralPower(pNode);
          }
        else
          {
            pResult = createFraction(pNode);
          }

        break;

      case CEvaluationNode::MainType::NUMBER:
        pResult = createItem(pNode);
        break;

      case CEvaluationNode::MainType::FUNCTION:
        pResult = createFunction(pNode);
        break;

      case CEvaluationNode::MainType::CALL:
        pResult = createCall(pNode);
        break;

      case CEvaluationNode::MainType::CHOICE:
        pResult = createChoice(pNode);
        break;

      case CEvaluationNode::MainType::LOGICAL:
        pResult = createLogical(pNode);
        break;

      case CEvaluationNode::MainType::VARIABLE:
        pResult = createItem(pNode);
        break;

      case CEvaluationNode::MainType::CONSTANT:
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
              pChoiceNode = new CEvaluationNodeChoice(CEvaluationNode::SubType::IF, "IF");
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
              pChoiceNode = new CEvaluationNodeChoice(CEvaluationNode::SubType::IF, "IF");
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
        pLogicalNode = new CEvaluationNodeConstant(CEvaluationNode::SubType::True, "TRUE");
        pLogicalNode->compile();
        break;

      case CNormalLogicalItem::FALSE:
        pLogicalNode = new CEvaluationNodeConstant(CEvaluationNode::SubType::False, "FALSE");
        pLogicalNode->compile();
        break;

      case CNormalLogicalItem::EQ:
        pLogicalNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::EQ, "==");
        break;

      case CNormalLogicalItem::NE:
        pLogicalNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::NE, "!=");
        break;

      case CNormalLogicalItem::LT:
        pLogicalNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::LT, "<");
        break;

      case CNormalLogicalItem::GT:
        pLogicalNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::GT, ">");
        break;

      case CNormalLogicalItem::GE:
        pLogicalNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::GE, ">=");
        break;

      case CNormalLogicalItem::LE:
        pLogicalNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::LE, "<=");
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
              pLogicalNode->compile();
            }
        }
    }

  return pLogicalNode;
}

CEvaluationNode* convertToCEvaluationNode(const CNormalLogical& logical)
{
  CEvaluationNode* pResult = NULL;
  // go through all mAndSets and create AND combined chains which are then
  // combined with OR
  // do the same with all choice sets
  // combine the two results with OR
  CEvaluationNode* pNotNode = NULL;
  CEvaluationNode* pNode = NULL;
  CEvaluationNode* pOrNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::OR, "OR");
  CEvaluationNode* pAndNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::AND, "AND");
  std::vector<CEvaluationNode*> andElements;
  std::vector<CEvaluationNode*> orElements;
  CNormalLogical::ChoiceSetOfSets::const_iterator cIt = logical.getChoices().begin(), cEndit = logical.getChoices().end();

  while (cIt != cEndit)
    {
      CNormalLogical::ChoiceSet::const_iterator cInnerIt = (*cIt).first.begin(), cInnerEndit = (*cIt).first.end();

      while (cInnerIt != cInnerEndit)
        {
          pNode = convertToCEvaluationNode(*(*cInnerIt).first);
          assert(pNode != NULL);

          if ((*cInnerIt).second == true)
            {
              // only create the not node if it wouldn't result in the neutral
              // element
              if (*pNode != CNormalTranslation::NEUTRAL_ELEMENT_OR)
                {
                  pNotNode = new CEvaluationNodeFunction(CEvaluationNode::SubType::NOT, "NOT");
                  pNotNode->addChild(pNode);
                  pNode = pNotNode;
                }
              else
                {
                  pNode = NULL;
                }
            }

          ++cInnerIt;

          // if it is not the neutral element or it is the last element to be
          // inserted into an otherwise empty vector, insert the element
          if (((pNode != NULL) && ((*pNode) != CNormalTranslation::NEUTRAL_ELEMENT_AND)) || (andElements.empty() && cInnerIt == cInnerEndit))
            {
              andElements.push_back(pNode);
            }
        }

      // create the and chain
      pNode = CNormalTranslation::createChain(pAndNode, &CNormalTranslation::NEUTRAL_ELEMENT_AND, andElements);
      assert(pNode != NULL);
      andElements.clear();

      // check *cIt.second if it is true
      if ((*cIt).second == true)
        {
          // create a not node if it would not result in the creation of the
          // neutral element
          if (*pNode != CNormalTranslation::NEUTRAL_ELEMENT_AND)
            {
              pNotNode = new CEvaluationNodeFunction(CEvaluationNode::SubType::NOT, "NOT");
              pNode->addChild(pNode);
              pNode = pNotNode;
            }
          else
            {
              pNode = NULL;
            }
        }

      ++cIt;

      // if it is not the neutral element or it is the last element to be
      // inserted into an otherwise empty vector, insert the element
      if (((pNode != NULL) && ((*pNode) != CNormalTranslation::NEUTRAL_ELEMENT_OR)) || (orElements.empty() && cIt == cEndit))
        {
          orElements.push_back(pNode);
        }
    }

  // create the OR chain
  if (!orElements.empty())
    {
      pNode = CNormalTranslation::createChain(pOrNode, &CNormalTranslation::NEUTRAL_ELEMENT_OR, orElements);
      assert(pNode != NULL);
      orElements.clear();
    }

  pResult = pNode;
  pNode = NULL;

  CNormalLogical::ItemSetOfSets::const_iterator iIt = logical.getAndSets().begin(), iEndit = logical.getAndSets().end();

  while (iIt != iEndit)
    {
      CNormalLogical::ItemSet::const_iterator iInnerIt = (*iIt).first.begin(), iInnerEndit = (*iIt).first.end();

      while (iInnerIt != iInnerEndit)
        {
          pNode = convertToCEvaluationNode(*(*iInnerIt).first);
          assert(pNode != NULL);

          if ((*iInnerIt).second == true)
            {
              // only create the not node if it wouldn't result in the neutral
              // element
              if (*pNode != CNormalTranslation::NEUTRAL_ELEMENT_OR)
                {
                  pNotNode = new CEvaluationNodeFunction(CEvaluationNode::SubType::NOT, "NOT");
                  pNotNode->addChild(pNode);
                  pNode = pNotNode;
                }
              else
                {
                  delete pNode;
                  pNode = NULL;
                }
            }

          ++iInnerIt;

          // if it is not the neutral element or it is the last element to be
          // inserted into an otherwise empty vector, insert the element
          if (((pNode != NULL) && ((*pNode) != CNormalTranslation::NEUTRAL_ELEMENT_AND)) || (andElements.empty() && iInnerIt == iInnerEndit))
            {
              andElements.push_back(pNode);
            }
        }

      // create the and chain
      pNode = CNormalTranslation::createChain(pAndNode, &CNormalTranslation::NEUTRAL_ELEMENT_AND, andElements);
      assert(pNode != NULL);
      andElements.clear();

      // check *iIt.second if it is true
      if ((*iIt).second == true)
        {

          // create a not node if it does not result in the neutral node
          if (*pNode != CNormalTranslation::NEUTRAL_ELEMENT_AND)
            {
              pNotNode = new CEvaluationNodeFunction(CEvaluationNode::SubType::NOT, "NOT");
              pNotNode->addChild(pNode);
              pNode = pNotNode;
            }
          else
            {
              delete pNode;
              pNode = NULL;
            }
        }

      ++iIt;

      // if it is not the neutral element or it is the last element to be
      // inserted into an otherwise empty vector, insert the element
      if (((pNode != NULL) && ((*pNode) != CNormalTranslation::NEUTRAL_ELEMENT_OR)) || (orElements.empty() && iIt == iEndit))
        {
          orElements.push_back(pNode);
        }
    }

  // create the OR chain
  if (!orElements.empty())
    {
      pNode = CNormalTranslation::createChain(pOrNode, &CNormalTranslation::NEUTRAL_ELEMENT_OR, orElements);
      assert(pNode != NULL);
      orElements.clear();
    }

  if (pResult == NULL)
    {
      pResult = pNode;
      assert(pResult != NULL);
    }
  else
    {
      if (*pResult == CNormalTranslation::NEUTRAL_ELEMENT_OR)
        {
          pResult = pNode;
        }
      else if (*pNode == CNormalTranslation::NEUTRAL_ELEMENT_OR)
        {
          CEvaluationNode* pTmpNode = pOrNode->copyBranch();
          pTmpNode->addChild(pResult);
          pTmpNode->addChild(pNode);
          pResult = pTmpNode;
        }
    }

  // check if mNot is set
  if (logical.isNegated() == true)
    {
      pNotNode = new CEvaluationNodeFunction(CEvaluationNode::SubType::NOT, "NOT");
      pNode->addChild(pResult);
      pResult = pNotNode;
    }

  // clean up
  delete pOrNode;
  delete pAndNode;
  assert(pResult != NULL);
  return pResult;
}

/**
 * This version of the method is wrong.
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
              pNot = new CEvaluationNodeFunction(CEvaluationNode::S_NOT, "NOT");
              pNot->addChild(pTmpResult);
              pTmpResult = pNot;
            }
        }
      else if ((*it).first.size() > 1)
        {
          CNormalLogical::ItemSet::const_iterator innerit = (*it).first.begin(), innerendit = (*it).first.end();
          // create the not
          CEvaluationNode* pOrNode = new CEvaluationNodeLogical(CEvaluationNode::S_OR, "OR");
          pTmpResult = pOrNode;
          while (innerit != innerendit && error == false)
            {
              CEvaluationNode* pItem = convertToCEvaluationNode(*(*innerit).first);
              if (pItem != NULL)
                {
                  if ((*innerit).second == true)
                    {
                      pNot = new CEvaluationNodeFunction(CEvaluationNode::S_NOT, "NOT");
                      pNot->addChild(pItem);
                      pItem = pNot;
                    }
                  pOrNode->addChild(pItem);
                  pOrNode->addChild(new CEvaluationNodeLogical(CEvaluationNode::S_OR, "OR"));
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
              pNot = new CEvaluationNodeFunction(CEvaluationNode::S_NOT, "NOT");
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
              pNot = new CEvaluationNodeFunction(CEvaluationNode::S_NOT, "NOT");
              pNot->addChild(pTmpResult);
              pTmpResult = pNot;
            }
        }
      else if ((*it2).first.size() > 1)
        {
          CNormalLogical::ChoiceSet::const_iterator innerit = (*it2).first.begin(), innerendit = (*it2).first.end();
          // create the not
          CEvaluationNode* pOrNode = new CEvaluationNodeLogical(CEvaluationNode::S_OR, "OR");
          pTmpResult = pOrNode;
          while (innerit != innerendit && error != true)
            {
              CEvaluationNode* pItem = convertToCEvaluationNode(*(*innerit).first);
              if (pItem != NULL)
                {
                  if ((*innerit).second == true)
                    {
                      pNot = new CEvaluationNodeFunction(CEvaluationNode::S_NOT, "NOT");
                      pNot->addChild(pItem);
                      pItem = pNot;
                    }
                  pOrNode->addChild(pItem);
                  pOrNode->addChild(new CEvaluationNodeLogical(CEvaluationNode::S_OR, "OR"));
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
              pNot = new CEvaluationNodeFunction(CEvaluationNode::S_NOT, "NOT");
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
              CEvaluationNode* pAndNode = new CEvaluationNodeLogical(CEvaluationNode::S_AND, "AND");
              pResult = pAndNode;
              while (andit != andendit)
                {
                  pAndNode->addChild(*andit);
                  pAndNode->addChild(new CEvaluationNodeLogical(CEvaluationNode::S_AND, "AND"));
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
          pNot = new CEvaluationNodeFunction(CEvaluationNode::S_NOT, "NOT");
          pNot->addChild(pResult);
          pResult = pNot;
        }
      pResult->compile(NULL);
    }
  return pResult;
}
 */

CNormalChoice* createChoice(const CEvaluationNode* pNode)
{
  CNormalChoice* pResult = NULL;

  if (pNode != NULL && pNode->mainType() == CEvaluationNode::MainType::CHOICE)
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

  if (pNode != NULL && pNode->mainType() == CEvaluationNode::MainType::CHOICE)
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
      CEvaluationNode::MainType mainType = pNode->mainType();
      CEvaluationNode::SubType subType = pNode->subType();

      if (mainType == CEvaluationNode::MainType::CONSTANT)
        {
          if (subType == CEvaluationNode::SubType::True || subType == CEvaluationNode::SubType::False)
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
      else if (mainType == CEvaluationNode::MainType::LOGICAL)
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

          switch (subType)
            {
              case CEvaluationNode::SubType::EQ:
              case CEvaluationNode::SubType::NE:
              case CEvaluationNode::SubType::GT:
              case CEvaluationNode::SubType::LT:
              case CEvaluationNode::SubType::GE:
              case CEvaluationNode::SubType::LE:
                pLogicalItem = createLogicalItem(pNode);

                if (pLogicalItem != NULL)
                  {
                    pResult = new CNormalLogical();
                    CNormalLogical::ItemSet tmp;
                    tmp.insert(std::make_pair(pLogicalItem, false));
                    pResult->getAndSets().insert(std::make_pair(tmp, false));
                  }

                break;

              case CEvaluationNode::SubType::XOR:
                // replace A xor B by A OR B AND NOT(A AND B)
                pA = dynamic_cast<const CEvaluationNode*>(pNode->getChild());
                pB = dynamic_cast<const CEvaluationNode*>(pA->getSibling());
                pAndNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::AND, "AND");
                pAndNode->addChild(pA->copyBranch());
                pAndNode->addChild(pB->copyBranch());
                pNotNode = new CEvaluationNodeFunction(CEvaluationNode::SubType::NOT, "NOT");
                pNotNode->addChild(pAndNode);
                pOrNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::OR, "OR");
                pOrNode->addChild(pA->copyBranch());
                pOrNode->addChild(pB->copyBranch());
                pAndNode = new CEvaluationNodeLogical(CEvaluationNode::SubType::AND, "AND");
                pAndNode->addChild(pOrNode);
                pAndNode->addChild(pNotNode);
                pResult = createLogical(pAndNode);
                delete pAndNode;
                break;

              case CEvaluationNode::SubType::AND:
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

                        delete pLeftLogical;
                        delete pRightLogical;
                      }
                    else
                      {
                        delete pLeftLogical;
                      }
                  }

                break;

              case CEvaluationNode::SubType::OR:
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
      else if (mainType == CEvaluationNode::MainType::FUNCTION &&  subType == CEvaluationNode::SubType::NOT)
        {
          pResult = createLogical(dynamic_cast<const CEvaluationNode*>(pNode->getChild()));

          if (pResult != NULL)
            {
              pResult->negate();
            }
        }
      else if (mainType == CEvaluationNode::MainType::CHOICE)
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

  return pResult;
}

CNormalLogicalItem* createLogicalItem(const CEvaluationNode* pNode)
{
  CNormalLogicalItem* pResult = NULL;

  if (pNode != NULL)
    {
      CEvaluationNode::MainType mainType = pNode->mainType();
      CEvaluationNode::SubType subType = pNode->subType();

      if (mainType == CEvaluationNode::MainType::CONSTANT)
        {
          if (subType == CEvaluationNode::SubType::False)
            {
              pResult = new CNormalLogicalItem();
              pResult->setType(CNormalLogicalItem::FALSE);
            }
          else if (subType == CEvaluationNode::SubType::True)
            {
              pResult = new CNormalLogicalItem();
              pResult->setType(CNormalLogicalItem::TRUE);
            }
        }

      if (mainType == CEvaluationNode::MainType::LOGICAL)
        {
          CNormalFraction* pFrac1 = NULL;
          CNormalFraction* pFrac2 = NULL;

          switch (subType)
            {
              case CEvaluationNode::SubType::EQ:
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

              case CEvaluationNode::SubType::NE:
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

              case CEvaluationNode::SubType::GT:
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

              case CEvaluationNode::SubType::LT:
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

              case CEvaluationNode::SubType::GE:
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

              case CEvaluationNode::SubType::LE:
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

  return pResult;
}
