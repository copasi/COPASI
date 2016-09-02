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

#include "copasi.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"
#include "utilities/CValidatedUnit.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeLogical::CEvaluationNodeLogical():
  CEvaluationNode(T_LOGICAL, S_INVALID, ""),
  mpLeftNode(NULL),
  mpRightNode(NULL),
  mpLeftValue(NULL),
  mpRightValue(NULL)
{}

CEvaluationNodeLogical::CEvaluationNodeLogical(const SubType & subType,
    const Data & data):
  CEvaluationNode(T_LOGICAL, subType, data),
  mpLeftNode(NULL),
  mpRightNode(NULL),
  mpLeftValue(NULL),
  mpRightValue(NULL)
{
  switch (mSubType)
    {
      case S_OR:
        mPrecedence = PRECEDENCE_LOGIG_OR;
        break;

      case S_XOR:
        mPrecedence = PRECEDENCE_LOGIG_XOR;
        break;

      case S_AND:
        mPrecedence = PRECEDENCE_LOGIG_AND;
        break;

      case S_EQ:
        mPrecedence = PRECEDENCE_LOGIG_EQ;
        break;

      case S_NE:
        mPrecedence = PRECEDENCE_LOGIG_NE;
        break;

      case S_GT:
        mPrecedence = PRECEDENCE_LOGIG_GT;
        break;

      case S_GE:
        mPrecedence = PRECEDENCE_LOGIG_GE;
        break;

      case S_LT:
        mPrecedence = PRECEDENCE_LOGIG_LT;
        break;

      case S_LE:
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

bool CEvaluationNodeLogical::compile(const CEvaluationTree * /* pTree */)
{
  mpLeftNode = static_cast<CEvaluationNode *>(getChild());

  if (mpLeftNode == NULL) return false;

  mpLeftValue = mpLeftNode->getValuePointer();

  mpRightNode = static_cast<CEvaluationNode *>(mpLeftNode->getSibling());

  if (mpRightNode == NULL) return false;

  mpRightValue = mpRightNode->getValuePointer();

  return (mpRightNode->getSibling() == NULL); // We must have exactly two children
}

// virtual
std::string CEvaluationNodeLogical::getInfix(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeLogical *>(this)->compile(NULL))
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
  if (const_cast<CEvaluationNodeLogical *>(this)->compile(NULL))
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
  if (const_cast<CEvaluationNodeLogical *>(this)->compile(NULL))
    {
      Data DisplayString;
      Data data;
      bool isXor = false;

      switch ((SubType)this->subType())
        {
          case S_AND:
            data = "&&";
            break;

          case S_OR:
            data = "||";
            break;

          case S_EQ:
            data = "==";
            break;

          case S_GE:
            data = ">=";
            break;

          case S_GT:
            data = ">";
            break;

          case S_LE:
            data = "<=";
            break;

          case S_LT:
            data = "<";
            break;

          case S_NE:
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
  if (const_cast<CEvaluationNodeLogical *>(this)->compile(NULL))
    {
      Data DisplayString;
      Data data;

      switch ((SubType)this->subType())
        {
          case S_AND:
            data = "AND";
            break;

          case S_OR:
            data = "OR";
            break;

            /* case S_XOR:
               break; */
          case S_EQ:
            data = "=";
            break;

          case S_GE:
            data = ">=";
            break;

          case S_GT:
            data = ">";
            break;

          case S_LE:
            data = "<=";
            break;

          case S_LT:
            data = "<";
            break;

          case S_NE:
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
  if (const_cast<CEvaluationNodeLogical *>(this)->compile(NULL))
    {
      Data DisplayString;
      Data data;

      switch ((SubType)this->subType())
        {
          case S_AND:
            data = "&";
            break;

          case S_OR:
            data = "|";
            break;

          case S_EQ:
            data = "==";
            break;

          case S_GE:
            data = ">=";
            break;

          case S_GT:
            data = ">";
            break;

          case S_LE:
            data = "<=";
            break;

          case S_LT:
            data = "<";
            break;

          case S_NE:
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
      case S_OR:
      case S_XOR:
      case S_AND:
        if (!(units[0] == CBaseUnit::dimensionless) ||
            !(units[1] == CBaseUnit::dimensionless))
          {
            Unit.setConflict(true);
          }

        break;

      case S_EQ:
      case S_NE:
      case S_GT:
      case S_GE:
      case S_LT:
      case S_LE:
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
    const std::map < CEvaluationNode * , CValidatedUnit > & currentUnits,
    std::map < CEvaluationNode * , CValidatedUnit > & targetUnits) const
{
  CValidatedUnit Result = CValidatedUnit::merge(currentUnits.find(const_cast< CEvaluationNodeLogical * >(this))->second,
                          targetUnits[const_cast< CEvaluationNodeLogical * >(this)]);

  switch (mSubType)
    {
      case S_OR:
      case S_XOR:
      case S_AND:
        targetUnits[mpLeftNode] = CValidatedUnit(CBaseUnit::dimensionless, false);
        targetUnits[mpRightNode] = CValidatedUnit(CBaseUnit::dimensionless, false);
        break;

      case S_EQ:
      case S_NE:
      case S_GT:
      case S_GE:
      case S_LT:
      case S_LE:
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
        subType = S_AND;
        data = "and";
        break;

      case AST_LOGICAL_OR:
        subType = S_OR;
        data = "or";
        break;

      case AST_LOGICAL_XOR:
        subType = S_XOR;
        data = "xor";
        break;

      case AST_RELATIONAL_EQ:
        subType = S_EQ;
        data = "eq";
        break;

      case AST_RELATIONAL_GEQ:
        subType = S_GE;
        data = "ge";
        break;

      case AST_RELATIONAL_GT:
        subType = S_GT;
        data = "gt";
        break;

      case AST_RELATIONAL_LEQ:
        subType = S_LE;
        data = "le";
        break;

      case AST_RELATIONAL_LT:
        subType = S_LT;
        data = "lt";
        break;

      case AST_RELATIONAL_NEQ:
        subType = S_NE;
        data = "ne";
        break;

      default:
        subType = S_INVALID;
        break;
    }

  CEvaluationNode* pNode = NULL;
  // convert the two children

  switch (subType)
    {
      case S_AND:
      case S_OR:
      case S_XOR:

        // The number of chidren may vary
        switch (iMax)
          {
            case 0:

              if (subType == S_AND)
                pNode = new CEvaluationNodeConstant(S_TRUE, "TRUE");
              else
                pNode = new CEvaluationNodeConstant(S_FALSE, "FALSE");

              break;

            case 1:
              pNode = children[0];
              break;

            default:
            {
              pNode = new CEvaluationNodeLogical(subType, data);
              CEvaluationNode * pCurrent = pNode;

              // We have at least 2 children
              while (i < iMax - 1)
                {
                  // add the first value
                  pCurrent->addChild(children[i++]);

                  switch (iMax - i)
                    {
                      case 1:
                        // We have only 1 more child
                        pCurrent->addChild(children[i++]);
                        break;

                      default:
                        // We have at least 2 more children
                      {
                        // create a new node with the same operator
                        CEvaluationNode * pTmp = new CEvaluationNodeLogical(subType, data);
                        pCurrent->addChild(pTmp);
                        pCurrent = pTmp;
                      }
                      break;
                    }
                }
            }
            break;
          }

        break;

      case S_EQ:
      case S_NE:
      case S_GE:
      case S_GT:
      case S_LE:
      case S_LT:
        // all these are binary
        assert(iMax == 2);
        pNode = new CEvaluationNodeLogical(subType, data);
        pNode->addChild(children[0]);
        pNode->addChild(children[1]);
        break;

      case S_INVALID:
        // do nothing
        break;
    }

  return pNode;
}

// virtual
bool CEvaluationNodeLogical::isBoolean() const
{return true;}

ASTNode* CEvaluationNodeLogical::toAST(const CCopasiDataModel* pDataModel) const
{
  SubType subType = (SubType)this->subType();
  ASTNode* node = new ASTNode();

  switch (subType)
    {
      case S_AND:
        node->setType(AST_LOGICAL_AND);
        break;

      case S_OR:
        node->setType(AST_LOGICAL_OR);
        break;

      case S_XOR:
        node->setType(AST_LOGICAL_XOR);
        break;

      case S_EQ:
        node->setType(AST_RELATIONAL_EQ);
        break;

      case S_NE:
        node->setType(AST_RELATIONAL_NEQ);
        break;

      case S_GT:
        node->setType(AST_RELATIONAL_GT);
        break;

      case S_GE:
        node->setType(AST_RELATIONAL_GEQ);
        break;

      case S_LT:
        node->setType(AST_RELATIONAL_LT);
        break;

      case S_LE:
        node->setType(AST_RELATIONAL_LEQ);
        break;

      case S_INVALID:
        break;

      default:
        subType = S_INVALID;
        break;
    }

  if (subType != S_INVALID)
    {
      const CEvaluationNode* child1 = dynamic_cast<const CEvaluationNode*>(this->getChild());
      const CEvaluationNode* child2 = dynamic_cast<const CEvaluationNode*>(child1->getSibling());
      node->addChild(child1->toAST(pDataModel));
      node->addChild(child2->toAST(pDataModel));
    }

  return node;
}

#include "utilities/copasimathml.h"

// virtual
std::string CEvaluationNodeLogical::getMMLString(const std::vector< std::string > & children,
    bool /* expand */,
    const std::vector< std::vector< std::string > > & /* variables */) const
{
  std::ostringstream out;

  if (const_cast<CEvaluationNodeLogical *>(this)->compile(NULL))
    {
      std::string data = "";
      bool flag = false;

      switch ((SubType)this->subType())
        {
          case S_AND:
            data = " and ";
            break;

          case S_OR:
            data = " or ";
            break;

          case S_XOR:
            data = " xor ";
            break;

          case S_EQ:
            data = "=";
            break;

          case S_GE:
            data = "&gt;=";
            break;

          case S_GT:
            data = "&gt;";
            break;

          case S_LE:
            data = "&lt;=";
            break;

          case S_LT:
            data = "&lt;";
            break;

          case S_NE:
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
