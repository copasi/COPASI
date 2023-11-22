// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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
#include "copasi/utilities/CBalanceTree.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeLogical::CEvaluationNodeLogical():
  CEvaluationNode(MainType::LOGICAL, SubType::INVALID, ""),
  mpLeftNode(NULL),
  mpRightNode(NULL),
  mpLeftValue(NULL),
  mpRightValue(NULL)
{
  mValueType = ValueType::Boolean;
}

CEvaluationNodeLogical::CEvaluationNodeLogical(const SubType & subType,
    const Data & data):
  CEvaluationNode(MainType::LOGICAL, subType, data),
  mpLeftNode(NULL),
  mpRightNode(NULL),
  mpLeftValue(NULL),
  mpRightValue(NULL)
{
  mValueType = ValueType::Boolean;

  switch (mSubType)
    {
      case SubType::OR:
        mPrecedence = PRECEDENCE_LOGIG_OR;
        break;

      case SubType::XOR:
        mPrecedence = PRECEDENCE_LOGIG_XOR;
        break;

      case SubType::AND:
        mPrecedence = PRECEDENCE_LOGIG_AND;
        break;

      case SubType::EQ:
        mPrecedence = PRECEDENCE_LOGIG_EQ;
        break;

      case SubType::NE:
        mPrecedence = PRECEDENCE_LOGIG_NE;
        break;

      case SubType::GT:
        mPrecedence = PRECEDENCE_LOGIG_GT;
        break;

      case SubType::GE:
        mPrecedence = PRECEDENCE_LOGIG_GE;
        break;

      case SubType::LT:
        mPrecedence = PRECEDENCE_LOGIG_LT;
        break;

      case SubType::LE:
        mPrecedence = PRECEDENCE_LOGIG_LE;
        break;
    }
}

CEvaluationNodeLogical::CEvaluationNodeLogical(const CEvaluationNodeLogical & src):
  CEvaluationNode(src),
  mpLeftNode(src.mpLeftNode),
  mpRightNode(src.mpRightNode),
  mpLeftValue(src.mpLeftValue),
  mpRightValue(src.mpRightValue)
{}

CEvaluationNodeLogical::~CEvaluationNodeLogical() {}

CIssue CEvaluationNodeLogical::compile()
{
  mpLeftNode = static_cast<CEvaluationNode *>(getChild());

  if (mpLeftNode == NULL) return CIssue(CIssue::eSeverity::Error, CIssue::eKind::VariableNotfound);

  mpLeftValue = mpLeftNode->getValuePointer();

  mpRightNode = static_cast<CEvaluationNode *>(mpLeftNode->getSibling());

  if (mpRightNode == NULL) return CIssue(CIssue::eSeverity::Error, CIssue::eKind::VariableNotfound);

  mpRightValue = mpRightNode->getValuePointer();

  CIssue Result;

  if (mpRightNode->getSibling() != NULL) // We must have exactly two children
    Result &= CIssue(CIssue::eSeverity::Error, CIssue::eKind::TooManyArguments);

  // The child nodes must have the same type
  switch (mSubType)
    {
      case SubType::OR:
      case SubType::XOR:
      case SubType::AND:
        Result &= mpLeftNode->setValueType(ValueType::Boolean);
        Result &= mpRightNode->setValueType(ValueType::Boolean);
        break;

      case SubType::EQ:
      case SubType::NE:

        if (mpLeftNode->getValueType() != ValueType::Unknown)
          Result &= mpRightNode->setValueType(mpLeftNode->getValueType());
        else if (mpRightNode->getValueType() != ValueType::Unknown)
          Result &= mpLeftNode->setValueType(mpRightNode->getValueType());

        break;

      case SubType::GT:
      case SubType::GE:
      case SubType::LT:
      case SubType::LE:
        Result &= mpLeftNode->setValueType(ValueType::Number);
        Result &= mpRightNode->setValueType(ValueType::Number);
        break;
    }

  return Result;
}

// virtual
std::string CEvaluationNodeLogical::getInfix(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeLogical *>(this)->compile())
    {
      Data Infix;

      if (*mpLeftNode < * (CEvaluationNode *)this)
        Infix = "(" + children[0] + ")";
      else
        Infix = children[0];

      Infix += " " + mData + " ";

      if (!(*(CEvaluationNode *)this < *mpRightNode))
        Infix += "(" + children[1] + ")";
      else
        Infix += children[1];

      return Infix;
    }
  else
    return "@";
}

// virtual
std::string CEvaluationNodeLogical::getDisplayString(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeLogical *>(this)->compile())
    {
      Data DisplayString;

      if (*mpLeftNode < * (CEvaluationNode *)this)
        DisplayString = "(" + children[0] + ")";
      else
        DisplayString = children[0] + " ";

      DisplayString += mData;

      if (!(*(CEvaluationNode *)this < *mpRightNode))
        DisplayString += "(" + children[1] + ")";
      else
        DisplayString += " " + children[1];

      return DisplayString;
    }
  else
    return "@";
}

// virtual
std::string CEvaluationNodeLogical::getCCodeString(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeLogical *>(this)->compile())
    {
      Data DisplayString;
      Data data;
      bool isXor = false;

      switch ((SubType)this->subType())
        {
          case SubType::AND:
            data = "&&";
            break;

          case SubType::OR:
            data = "||";
            break;

          case SubType::EQ:
            data = "==";
            break;

          case SubType::GE:
            data = ">=";
            break;

          case SubType::GT:
            data = ">";
            break;

          case SubType::LE:
            data = "<=";
            break;

          case SubType::LT:
            data = "<";
            break;

          case SubType::NE:
            data = "!=";
            break;

          default:
            /*
             * case S_XOR:
             */
            data = "!=";
            isXor = true;
            break;
        }

      if (isXor)
        DisplayString = " !";
      else
        DisplayString = "";

      if (*mpLeftNode < * (CEvaluationNode *)this)
        DisplayString += "(" + children[0] + ")";
      else
        DisplayString += children[0] + " ";

      DisplayString += data;

      if (isXor)
        DisplayString += " !";

      if (!(*(CEvaluationNode *)this < *mpRightNode))
        DisplayString += "(" + children[1] + ")";
      else
        DisplayString += " " + children[1];

      return DisplayString;
    }
  else
    return "@";
}

// virtual
std::string CEvaluationNodeLogical::getBerkeleyMadonnaString(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeLogical *>(this)->compile())
    {
      Data DisplayString;
      Data data;

      switch ((SubType)this->subType())
        {
          case SubType::AND:
            data = "AND";
            break;

          case SubType::OR:
            data = "OR";
            break;

          /* case S_XOR:
             break; */
          case SubType::EQ:
            data = "=";
            break;

          case SubType::GE:
            data = ">=";
            break;

          case SubType::GT:
            data = ">";
            break;

          case SubType::LE:
            data = "<=";
            break;

          case SubType::LT:
            data = "<";
            break;

          case SubType::NE:
            data = "<>";
            break;

          default:
            data = "@";
            break;
        }

      if (*mpLeftNode < * (CEvaluationNode *)this)
        DisplayString = "(" + children[0] + ")";
      else
        DisplayString = children[0] + " ";

      DisplayString += data;

      if (!(*(CEvaluationNode *)this < *mpRightNode))
        DisplayString += "(" + children[1] + ")";
      else
        DisplayString += " " + children[1];

      return DisplayString;
    }
  else
    return "@";
}

// virtual
std::string CEvaluationNodeLogical::getXPPString(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeLogical *>(this)->compile())
    {
      Data DisplayString;
      Data data;

      switch ((SubType)this->subType())
        {
          case SubType::AND:
            data = "&";
            break;

          case SubType::OR:
            data = "|";
            break;

          case SubType::EQ:
            data = "==";
            break;

          case SubType::GE:
            data = ">=";
            break;

          case SubType::GT:
            data = ">";
            break;

          case SubType::LE:
            data = "<=";
            break;

          case SubType::LT:
            data = "<";
            break;

          case SubType::NE:
            data = "!=";
            break;

          default:
            /* case S_XOR: */
            CCopasiMessage(CCopasiMessage::WARNING, " TODO   ");
            data = "@"; //TODO
            break;
        }

      if (*mpLeftNode < * (CEvaluationNode *)this)
        DisplayString = "(" + children[0] + ")";
      else
        DisplayString = children[0] + " ";

      DisplayString += data;

      if (!(*(CEvaluationNode *)this < *mpRightNode))
        DisplayString += "(" + children[1] + ")";
      else
        DisplayString += " " + children[1];

      return DisplayString;
    }
  else
    return "@"; //TODO
}

// virtual
CValidatedUnit CEvaluationNodeLogical::getUnit(const CMathContainer & /* container */,
    const std::vector< CValidatedUnit > & units) const
{
  CValidatedUnit Unit(CBaseUnit::dimensionless, false);

  switch (mSubType)
    {
      case SubType::OR:
      case SubType::XOR:
      case SubType::AND:
        if (!(units[0] == CBaseUnit::dimensionless) ||
            !(units[1] == CBaseUnit::dimensionless))
          {
            Unit.setConflict(true);
          }

        break;

      case SubType::EQ:
      case SubType::NE:
      case SubType::GT:
      case SubType::GE:
      case SubType::LT:
      case SubType::LE:
      {
        CValidatedUnit Arguments = CValidatedUnit::merge(units[0], units[1]);
        Unit.setConflict(Arguments.conflict());
      }
      break;
    }

  return Unit;
}

// virtual
CValidatedUnit CEvaluationNodeLogical::setUnit(const CMathContainer & container,
    const std::map < CEvaluationNode *, CValidatedUnit > & currentUnits,
    std::map < CEvaluationNode *, CValidatedUnit > & targetUnits) const
{
  CValidatedUnit Result(CEvaluationNode::setUnit(container, currentUnits, targetUnits));

  switch (mSubType)
    {
      case SubType::OR:
      case SubType::XOR:
      case SubType::AND:
        targetUnits[mpLeftNode] = CValidatedUnit(CBaseUnit::dimensionless, false);
        targetUnits[mpRightNode] = CValidatedUnit(CBaseUnit::dimensionless, false);
        break;

      case SubType::EQ:
      case SubType::NE:
      case SubType::GT:
      case SubType::GE:
      case SubType::LT:
      case SubType::LE:
      {

        CValidatedUnit Arguments = CValidatedUnit::merge(currentUnits.find(const_cast< CEvaluationNode * >(mpLeftNode))->second,
                                   currentUnits.find(const_cast< CEvaluationNode * >(mpRightNode))->second);

        targetUnits[mpLeftNode] = Arguments;
        targetUnits[mpRightNode] = Arguments;
      }
      break;
    }

  return Result;
}

// static
CEvaluationNode * CEvaluationNodeLogical::fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children)
{
  assert(pASTNode->getNumChildren() == children.size());

  size_t i = 0;
  size_t iMax = children.size();

  SubType subType;
  std::string data = "";

  switch (pASTNode->getType())
    {
      case AST_LOGICAL_AND:
        subType = SubType::AND;
        data = "and";
        break;

      case AST_LOGICAL_OR:
        subType = SubType::OR;
        data = "or";
        break;

      case AST_LOGICAL_XOR:
        subType = SubType::XOR;
        data = "xor";
        break;

      case AST_RELATIONAL_EQ:
        subType = SubType::EQ;
        data = "eq";
        break;

      case AST_RELATIONAL_GEQ:
        subType = SubType::GE;
        data = "ge";
        break;

      case AST_RELATIONAL_GT:
        subType = SubType::GT;
        data = "gt";
        break;

      case AST_RELATIONAL_LEQ:
        subType = SubType::LE;
        data = "le";
        break;

      case AST_RELATIONAL_LT:
        subType = SubType::LT;
        data = "lt";
        break;

      case AST_RELATIONAL_NEQ:
        subType = SubType::NE;
        data = "ne";
        break;

      default:
        subType = SubType::INVALID;
        break;
    }

  CEvaluationNode* pNode = NULL;
  // convert the two children

  switch (subType)
    {
      case SubType::AND:
      case SubType::OR:
      case SubType::XOR:

        // The number of children may vary
        switch (iMax)
          {
            case 0:
              if (subType == SubType::AND)
                pNode = new CEvaluationNodeConstant(SubType::True, "TRUE");
              else
                pNode = new CEvaluationNodeConstant(SubType::False, "FALSE");

              break;

            default:
            {
              pNode = BalanceTree< CEvaluationNode * >::create(children, [subType, data](CEvaluationNode * const & pFirst, CEvaluationNode * const & pSecond)
              {
                CEvaluationNode * pNew = new CEvaluationNodeLogical(subType, data);
                pNew->addChild(pFirst);
                pNew->addChild(pSecond);
                return pNew;
              });
            }
            break;
          }

        break;

      case SubType::EQ:
      case SubType::NE:
      case SubType::GE:
      case SubType::GT:
      case SubType::LE:
      case SubType::LT:
        // all these are binary
        assert(iMax == 2);
        pNode = new CEvaluationNodeLogical(subType, data);
        pNode->addChild(children[0]);
        pNode->addChild(children[1]);
        break;

      case SubType::INVALID:
        // do nothing
        break;
    }

  return pNode;
}

ASTNode* CEvaluationNodeLogical::toAST(const CDataModel* pDataModel) const
{
  SubType subType = (SubType)this->subType();
  ASTNode* node = new ASTNode();

  switch (subType)
    {
      case SubType::AND:
        node->setType(AST_LOGICAL_AND);
        break;

      case SubType::OR:
        node->setType(AST_LOGICAL_OR);
        break;

      case SubType::XOR:
        node->setType(AST_LOGICAL_XOR);
        break;

      case SubType::EQ:
        node->setType(AST_RELATIONAL_EQ);
        break;

      case SubType::NE:
        node->setType(AST_RELATIONAL_NEQ);
        break;

      case SubType::GT:
        node->setType(AST_RELATIONAL_GT);
        break;

      case SubType::GE:
        node->setType(AST_RELATIONAL_GEQ);
        break;

      case SubType::LT:
        node->setType(AST_RELATIONAL_LT);
        break;

      case SubType::LE:
        node->setType(AST_RELATIONAL_LEQ);
        break;

      case SubType::INVALID:
        break;

      default:
        subType = SubType::INVALID;
        break;
    }

  if (subType != SubType::INVALID)
    {
      const CEvaluationNode* child1 = dynamic_cast<const CEvaluationNode*>(this->getChild());
      const CEvaluationNode* child2 = dynamic_cast<const CEvaluationNode*>(child1->getSibling());
      node->addChild(child1->toAST(pDataModel));
      node->addChild(child2->toAST(pDataModel));
    }

  return node;
}

#include "copasi/utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeLogical::getMMLString(const std::vector< std::string > & children,
    bool /* expand */,
    const std::vector< std::vector< std::string > > & /* variables */) const
{
  std::ostringstream out;

  if (const_cast<CEvaluationNodeLogical *>(this)->compile())
    {
      std::string data = "";
      bool flag = false;

      switch ((SubType)this->subType())
        {
          case SubType::AND:
            data = " and ";
            break;

          case SubType::OR:
            data = " or ";
            break;

          case SubType::XOR:
            data = " xor ";
            break;

          case SubType::EQ:
            data = "=";
            break;

          case SubType::GE:
            data = "&gt;=";
            break;

          case SubType::GT:
            data = "&gt;";
            break;

          case SubType::LE:
            data = "&lt;=";
            break;

          case SubType::LT:
            data = "&lt;";
            break;

          case SubType::NE:
            data = "&NotEqual;";
            break;

          default:
            /*
             *
             */
            data = "@";
            break;
        }

      out << "<mrow>" << std::endl;

      flag = ((*mpLeftNode < * (CEvaluationNode *)this));

      if (flag) out << "<mfenced>" << std::endl;

      out << children[0];

      if (flag) out << "</mfenced>" << std::endl;

      out << "<mo>" << data << "</mo>" << std::endl;

      flag = ((*(CEvaluationNode *)this < *mpRightNode));

      if (!flag) out << "<mfenced>" << std::endl;

      out << children[1];

      if (!flag) out << "</mfenced>" << std::endl;

      out << "</mrow>" << std::endl;
    }

  return out.str();
}
