// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sbml/math/ASTNode.h>

#include "copasi.h"

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "math/CMathContainer.h"
#include "model/CModel.h"
#include "utilities/utility.h"
#include "utilities/CValidatedUnit.h"
#include "copasi/report/CCopasiRootContainer.h"

CEvaluationNodeDelay::CEvaluationNodeDelay():
  CEvaluationNode(T_DELAY, S_INVALID, ""),
  mpDelayValue(NULL),
  mpDelayLag(NULL)
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeDelay::CEvaluationNodeDelay(const SubType & subType,
    const Data & /* data */):
  CEvaluationNode(T_DELAY, subType, "delay"),
  mpDelayValue(NULL),
  mpDelayLag(NULL)
{
  switch (subType)
    {
      case S_DELAY:
        mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
        break;

      default:
        fatalError();
        break;
    }

  mPrecedence = PRECEDENCE_FUNCTION;
}

CEvaluationNodeDelay::CEvaluationNodeDelay(const CEvaluationNodeDelay & src):
  CEvaluationNode(src),
  mpDelayValue(NULL),
  mpDelayLag(NULL)
{}

CEvaluationNodeDelay::~CEvaluationNodeDelay() {}

bool CEvaluationNodeDelay::compile(const CEvaluationTree * /*pTree*/)
{
  bool success = true;

  switch (mSubType)
    {
      case S_DELAY:
        mpDelayValue = static_cast<CEvaluationNode *>(getChild());

        if (mpDelayValue == NULL) return false;

        mpDelayLag = static_cast<CEvaluationNode *>(mpDelayValue->getSibling());

        if (mpDelayLag == NULL) return false;

        return (mpDelayLag->getSibling() == NULL); // We must have exactly 2 children

        break;

      default:
        success = false;
        break;
    }

  return success;
}

// virtual
std::string CEvaluationNodeDelay::getInfix(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeDelay*>(this)->compile(NULL))
    {
      switch (mSubType)
        {
          case S_DELAY:
            return mData + "(" + children[0] + "," + children[1] + ")";
            break;

          default:
            break;
        }
    }

  return "@";
}

// virtual
std::string CEvaluationNodeDelay::getDisplayString(const std::vector< std::string > & children) const
{
  switch (mSubType)
    {
      case S_DELAY:
        return mData + "(" + children[0] + "," + children[1] + ")";
        break;

      default:
        break;
    }

  return "@";
}

// virtual
std::string CEvaluationNodeDelay::getCCodeString(const std::vector< std::string > & children) const
{
  switch (mSubType)
    {
      case S_DELAY:
        return mData + "(" + children[0] + "," + children[1] + ")";
        break;

      default:
        break;
    }

  return "@";
}

// virtual
std::string CEvaluationNodeDelay::getBerkeleyMadonnaString(const std::vector< std::string > & children) const
{
  switch (mSubType)
    {
      case S_DELAY:
        return mData + "(" + children[0] + "," + children[1] + ")";
        break;

      default:
        break;
    }

  return "@";
}

// virtual
std::string CEvaluationNodeDelay::getXPPString(const std::vector< std::string > & children) const
{
  switch (mSubType)
    {
      case S_DELAY:
        return mData + "(" + children[0] + "," + children[1] + ")";
        break;

      default:
        break;
    }

  return "@";
}

// virtual
CValidatedUnit CEvaluationNodeDelay::getUnit(const CMathContainer & container,
    const std::vector< CValidatedUnit > & units) const
{
  // The units of the delay functions are the units of the delay value which is the first child
  CValidatedUnit Delay = units[0];
  CValidatedUnit Lag = CValidatedUnit::merge(CValidatedUnit(container.getModel().getTimeUnit(), false), units[1]);

  Delay.setConflict(Delay.conflict() || Lag.conflict());

  return Delay;
}

// virtual
CValidatedUnit CEvaluationNodeDelay::setUnit(const CMathContainer & container,
    const std::map < CEvaluationNode * , CValidatedUnit > & currentUnits,
    std::map < CEvaluationNode * , CValidatedUnit > & targetUnits) const
{
  CValidatedUnit Delay = CValidatedUnit::merge(currentUnits.find(const_cast< CEvaluationNodeDelay * >(this))->second,
                         targetUnits[const_cast< CEvaluationNodeDelay * >(this)]);

  targetUnits[mpDelayValue] = Delay;
  targetUnits[mpDelayLag] = CValidatedUnit(container.getModel().getTimeUnit(), false);

  return Delay;
}

// static
CEvaluationNode * CEvaluationNodeDelay::fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children)
{
  assert(pASTNode->getNumChildren() == children.size());

  size_t i = 0, iMax = children.size();

  SubType subType = S_DELAY;
  std::string data = "delay";

  CEvaluationNode * pConvertedNode = new CEvaluationNodeDelay(subType, data);

  for (i = 0; i < iMax; ++i)
    {
      pConvertedNode->addChild(children[i]);
    }

  pConvertedNode->compile(NULL);
  return pConvertedNode;
}

ASTNode* CEvaluationNodeDelay::toAST(const CCopasiDataModel* pDataModel) const
{
  ASTNode* pNode = new ASTNode(AST_FUNCTION_DELAY);
  const CEvaluationNode* child = static_cast<const CEvaluationNode*>(this->getChild());

  while (child)
    {
      pNode->addChild(child->toAST(pDataModel));
      child = static_cast<const CEvaluationNode*>(child->getSibling());
    }

  return pNode;
}

#include "utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeDelay::getMMLString(const std::vector< std::string > & children,
    bool /* expand */,
    const std::vector< std::vector< std::string > > & /* variables */) const
{
  std::ostringstream out;

  switch (mSubType)
    {
      case S_DELAY:
        out << "<mrow>" << std::endl;

        out << "<mi>" << mData << "</mi>" << std::endl;
        out << "<mrow>" << std::endl;
        out << "<mo> (</mo>" << std::endl;
        out << "<mrow>" << std::endl;

        out << children[0];

        out << "<mo> , </mo>" << std::endl;

        out << children[1];

        out << "</mrow>" << std::endl;
        out << "<mo>) </mo>" << std::endl;

        out << "</mrow>" << std::endl;
        out << "</mrow>" << std::endl;
        break;

      default:
        break;
    }

  return out.str();
}
