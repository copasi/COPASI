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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/copasi.h"

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

#include "copasi/utilities/CValidatedUnit.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeChoice::CEvaluationNodeChoice():
  CEvaluationNode(MainType::CHOICE, SubType::INVALID, ""),
  mpIfNode(NULL),
  mpTrueNode(NULL),
  mpFalseNode(NULL),
  mpIfValue(NULL),
  mpTrueValue(NULL),
  mpFalseValue(NULL)
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeChoice::CEvaluationNodeChoice(const SubType & subType,
    const Data & data):
  CEvaluationNode(MainType::CHOICE, subType, data),
  mpIfNode(NULL),
  mpTrueNode(NULL),
  mpFalseNode(NULL),
  mpIfValue(NULL),
  mpTrueValue(NULL),
  mpFalseValue(NULL)
{
  switch (subType)
    {
      case SubType::IF:
        break;

      default:
        fatalError();
        break;
    }

  mPrecedence = PRECEDENCE_FUNCTION;
}

CEvaluationNodeChoice::CEvaluationNodeChoice(const CEvaluationNodeChoice & src):
  CEvaluationNode(src),
  mpIfNode(src.mpIfNode),
  mpTrueNode(src.mpTrueNode),
  mpFalseNode(src.mpFalseNode),
  mpIfValue(src.mpIfValue),
  mpTrueValue(src.mpTrueValue),
  mpFalseValue(src.mpFalseValue)
{}

CEvaluationNodeChoice::~CEvaluationNodeChoice() {}

void CEvaluationNodeChoice::calculate()
{
  mValue = (*mpIfValue > 0.5) ? *mpTrueValue : *mpFalseValue;
}

CIssue CEvaluationNodeChoice::compile()
{
  mpIfNode = static_cast<CEvaluationNode *>(getChild());

  if (mpIfNode == NULL) return CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid);

  mpIfValue = mpIfNode->getValuePointer();

  mpTrueNode = static_cast<CEvaluationNode *>(mpIfNode->getSibling());

  if (mpTrueNode == NULL) return CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid);

  mpTrueValue = mpTrueNode->getValuePointer();

  mpFalseNode = static_cast<CEvaluationNode *>(mpTrueNode->getSibling());

  if (mpFalseNode == NULL) return CIssue(CIssue::eSeverity::Error, CIssue::eKind::StructureInvalid);

  mpFalseValue = mpFalseNode->getValuePointer();

  if (mpFalseNode->getSibling() != NULL) // We must have exactly three children
    return CIssue(CIssue::eSeverity::Error, CIssue::eKind::TooManyArguments);

  // True and false node must have the same type if either is known
  if (mpTrueNode->getValueType() != ValueType::Unknown)
    return mpFalseNode->setValueType(mpTrueNode->getValueType());

  if (mpFalseNode->getValueType() != ValueType::Unknown)
    return mpTrueNode->setValueType(mpFalseNode->getValueType());

  return CIssue::Success;
}

// virtual
std::string CEvaluationNodeChoice::getInfix(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeChoice *>(this)->compile())
    return mData + "(" + children[0] + "," + children[1] + "," + children[2] + ")";
  else
    return "@";
}

// virtual
std::string CEvaluationNodeChoice::getDisplayString(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeChoice *>(this)->compile())
    return mData + "(" + children[0] + "," + children[1] + "," + children[2] + ")";
  else
    return "@";
}

// virtual
std::string CEvaluationNodeChoice::getCCodeString(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeChoice *>(this)->compile())
    return "(" + children[0] + " ? " + children[1] + " : " + children[2] + ")";
  else
    return "@";
}

// virtual
std::string CEvaluationNodeChoice::getBerkeleyMadonnaString(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeChoice *>(this)->compile())
    return "(if " + children[0] + " then " + children[1] + " else " + children[2] + ")";
  else
    return "@";
}

// virtual
std::string CEvaluationNodeChoice::getXPPString(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeChoice *>(this)->compile())
    return "if(" + children[0] + ")then(" + children[1] + ")else(" + children[2] + ")";
  else
    return "@"; //TODO
}

// virtual
CIssue CEvaluationNodeChoice::setValueType(const CEvaluationNode::ValueType & valueType)
{
  CIssue Result;

  if (mpTrueNode != NULL)
    {
      Result &= mpTrueNode->setValueType(valueType);
    }

  if (mpFalseNode != NULL)
    {
      Result &= mpFalseNode->setValueType(valueType);
    }

  return Result;
}

// static
CEvaluationNode * CEvaluationNodeChoice::fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children)
{
  assert(pASTNode->getNumChildren() == children.size());

  size_t i = 0, iMax = children.size();

  // a piecewise function definition can have zero or more children.
  if (iMax == 0)
    {
      // create a NaN node
      return new CEvaluationNodeConstant(SubType::NaN, "NAN");
    }

  if (iMax == 1)
    {
      // this must be the otherwise
      // It is not clearly specified what happens if there are no pieces, but
      // an otherwise. I would assume that in this case, the otherwise always
      // takes effect

      return children[0];
    }

  SubType subType;
  std::string data = "";

  switch (pASTNode->getType())
    {
      case AST_FUNCTION_PIECEWISE:
        subType = SubType::IF;
        data = "if";
        break;

      default:
        subType = SubType::INVALID;
        break;
    }

  CEvaluationNodeChoice * pNode = new CEvaluationNodeChoice(subType, data);
  CEvaluationNode * pCurrent = pNode;

  // We have at least 2 children
  while (i < iMax - 1)
    {
      // add the condition
      pCurrent->addChild(children[i + 1]);
      // the true value
      pCurrent->addChild(children[i]);

      i += 2;

      switch (iMax - i)
        {
          case 0:
            // We are missing the false value
            pCurrent->addChild(new CEvaluationNodeConstant(SubType::NaN, "NAN"));
            break;

          case 1:
            // the false value
            pCurrent->addChild(children[i++]);
            break;

          default:
            // We have at least 2 more children
          {
            // create a new piecewise as the false value
            CEvaluationNode * pTmp = new CEvaluationNodeChoice(subType, data);
            pCurrent->addChild(pTmp);
            pCurrent = pTmp;
          }
          break;
        }
    }

  return pNode;
}

ASTNode* CEvaluationNodeChoice::toAST(const CDataModel* pDataModel) const
{
  ASTNode* node = new ASTNode(AST_FUNCTION_PIECEWISE);
  const CEvaluationNode* child1 = dynamic_cast<const CEvaluationNode*>(this->getChild());
  assert(child1 != NULL);
  const CEvaluationNode* child2 = dynamic_cast<const CEvaluationNode*>(child1->getSibling());
  assert(child2 != NULL);
  const CEvaluationNode* child3 = dynamic_cast<const CEvaluationNode*>(child2->getSibling());
  assert(child3 != NULL);
  // the condition is the second child to the AST node but the first child in
  // the CEvaluationNode
  node->addChild(child2->toAST(pDataModel));
  node->addChild(child1->toAST(pDataModel));
  node->addChild(child3->toAST(pDataModel));
  return node;
}

#include "copasi/utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeChoice::getMMLString(const std::vector< std::string > & children,
    bool /* expand */,
    const std::vector< std::vector< std::string > > & /* variables */) const
{
  std::ostringstream out;

  if (const_cast<CEvaluationNodeChoice *>(this)->compile())
    {
      out << "<mrow>" << std::endl;
      out << "<mo> {</mo>" << std::endl;
      out << "<mtable>" << std::endl;

      out << "<mtr>" << std::endl;

      out << "<mtd>" << std::endl;
      out << children[0];
      out << "<mo> , </mo>" << std::endl;
      out << "</mtd>" << std::endl;

      out << "<mtd>" << std::endl;
      out << children[1];

      out << "</mtd>" << std::endl;

      out << "</mtr>" << std::endl;

      out << "<mtr>" << std::endl;

      out << "<mtd>" << std::endl;
      out << "<mo> else, </mo>" << std::endl;

      out << "</mtd>" << std::endl;
      out << "<mtd>" << std::endl;
      out << children[2];
      out << "</mtd>" << std::endl;

      out << "</mtr>" << std::endl;

      out << "</mtable>" << std::endl;
      out << "</mrow>" << std::endl;
    }

  return out.str();
}

// virtual
CValidatedUnit CEvaluationNodeChoice::getUnit(const CMathContainer & /* container */,
    const std::vector< CValidatedUnit > & units) const
{
  return CValidatedUnit::merge(units[1], units[2]);
}

// virtual
CValidatedUnit CEvaluationNodeChoice::setUnit(const CMathContainer & container,
    const std::map < CEvaluationNode *, CValidatedUnit > & currentUnits,
    std::map < CEvaluationNode *, CValidatedUnit > & targetUnits) const
{
  CValidatedUnit Result(CEvaluationNode::setUnit(container, currentUnits, targetUnits));

  targetUnits[mpIfNode] = CValidatedUnit(CUnit("1"), false);
  targetUnits[mpTrueNode] = Result;
  targetUnits[mpFalseNode] = Result;

  return Result;
}
