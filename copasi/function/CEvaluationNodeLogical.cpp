// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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

#include "sbml/math/ASTNode.h"

CEvaluationNodeLogical::CEvaluationNodeLogical():
  CEvaluationNode(CEvaluationNode::INVALID, ""),
  mpLeft(NULL),
  mpRight(NULL)
{}

CEvaluationNodeLogical::CEvaluationNodeLogical(const SubType & subType,
    const Data & data):
  CEvaluationNode((Type)(CEvaluationNode::LOGICAL | subType), data),
  mpLeft(NULL),
  mpRight(NULL)
{
  switch (mType & 0x00FFFFFF)
    {
      case OR:
        mPrecedence = PRECEDENCE_LOGIG_OR;
        break;

      case XOR:
        mPrecedence = PRECEDENCE_LOGIG_XOR;
        break;

      case AND:
        mPrecedence = PRECEDENCE_LOGIG_AND;
        break;

      case EQ:
        mPrecedence = PRECEDENCE_LOGIG_EQ;
        break;

      case NE:
        mPrecedence = PRECEDENCE_LOGIG_NE;
        break;

      case GT:
        mPrecedence = PRECEDENCE_LOGIG_GT;
        break;

      case GE:
        mPrecedence = PRECEDENCE_LOGIG_GE;
        break;

      case LT:
        mPrecedence = PRECEDENCE_LOGIG_LT;
        break;

      case LE:
        mPrecedence = PRECEDENCE_LOGIG_LE;
        break;
    }
}

CEvaluationNodeLogical::CEvaluationNodeLogical(const CEvaluationNodeLogical & src):
  CEvaluationNode(src),
  mpLeft(NULL),
  mpRight(NULL)
{}

CEvaluationNodeLogical::~CEvaluationNodeLogical() {}

bool CEvaluationNodeLogical::compile(const CEvaluationTree * /* pTree */)
{
  mpLeft = static_cast<CEvaluationNode *>(getChild());

  if (mpLeft == NULL) return false;

  mpRight = static_cast<CEvaluationNode *>(mpLeft->getSibling());

  if (mpRight == NULL) return false;

  return (mpRight->getSibling() == NULL); // We must have exactly two children
}

// virtual
std::string CEvaluationNodeLogical::getInfix(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeLogical *>(this)->compile(NULL))
    {
      Data Infix;

      if (*mpLeft < * (CEvaluationNode *)this)
        Infix = "(" + children[0] + ")";
      else
        Infix = children[0];

      Infix += " " + mData + " ";

      if (!(*(CEvaluationNode *)this < *mpRight))
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

      if (*mpLeft < * (CEvaluationNode *)this)
        DisplayString = "(" + children[0] + ")";
      else
        DisplayString = children[0] + " ";

      DisplayString += mData;

      if (!(*(CEvaluationNode *)this < *mpRight))
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

      switch ((SubType)CEvaluationNode::subType(this->getType()))
        {
          case AND:
            data = "&&";
            break;

          case OR:
            data = "||";
            break;

          case EQ:
            data = "==";
            break;

          case GE:
            data = ">=";
            break;

          case GT:
            data = ">";
            break;

          case LE:
            data = "<=";
            break;

          case LT:
            data = "<";
            break;

          case NE:
            data = "!=";
            break;

          default:
            /*
             * case XOR:
             */
            data = "!=";
            isXor = true;
            break;
        }

      if (isXor)
        DisplayString = " !";
      else
        DisplayString = "";

      if (*mpLeft < * (CEvaluationNode *)this)
        DisplayString += "(" + children[0] + ")";
      else
        DisplayString += children[0] + " ";

      DisplayString += data;

      if (isXor)
        DisplayString += " !";

      if (!(*(CEvaluationNode *)this < *mpRight))
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

      switch ((SubType)CEvaluationNode::subType(this->getType()))
        {
          case AND:
            data = "AND";
            break;

          case OR:
            data = "OR";
            break;

            /* case XOR:
               break; */
          case EQ:
            data = "=";
            break;

          case GE:
            data = ">=";
            break;

          case GT:
            data = ">";
            break;

          case LE:
            data = "<=";
            break;

          case LT:
            data = "<";
            break;

          case NE:
            data = "<>";
            break;

          default:
            data = "@";
            break;
        }

      if (*mpLeft < * (CEvaluationNode *)this)
        DisplayString = "(" + children[0] + ")";
      else
        DisplayString = children[0] + " ";

      DisplayString += data;

      if (!(*(CEvaluationNode *)this < *mpRight))
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

      switch ((SubType)CEvaluationNode::subType(this->getType()))
        {
          case AND:
            data = "&";
            break;

          case OR:
            data = "|";
            break;

          case EQ:
            data = "==";
            break;

          case GE:
            data = ">=";
            break;

          case GT:
            data = ">";
            break;

          case LE:
            data = "<=";
            break;

          case LT:
            data = "<";
            break;

          case NE:
            data = "!=";
            break;

          default:
            /* case XOR: */
            CCopasiMessage(CCopasiMessage::WARNING, " TODO   ");
            data = "@"; //TODO
            break;
        }

      if (*mpLeft < * (CEvaluationNode *)this)
        DisplayString = "(" + children[0] + ")";
      else
        DisplayString = children[0] + " ";

      DisplayString += data;

      if (!(*(CEvaluationNode *)this < *mpRight))
        DisplayString += "(" + children[1] + ")";
      else
        DisplayString += " " + children[1];

      return DisplayString;
    }
  else
    return "@"; //TODO
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
        subType = AND;
        data = "and";
        break;

      case AST_LOGICAL_OR:
        subType = OR;
        data = "or";
        break;

      case AST_LOGICAL_XOR:
        subType = XOR;
        data = "xor";
        break;

      case AST_RELATIONAL_EQ:
        subType = EQ;
        data = "eq";
        break;

      case AST_RELATIONAL_GEQ:
        subType = GE;
        data = "ge";
        break;

      case AST_RELATIONAL_GT:
        subType = GT;
        data = "gt";
        break;

      case AST_RELATIONAL_LEQ:
        subType = LE;
        data = "le";
        break;

      case AST_RELATIONAL_LT:
        subType = LT;
        data = "lt";
        break;

      case AST_RELATIONAL_NEQ:
        subType = NE;
        data = "ne";
        break;

      default:
        subType = INVALID;
        break;
    }

  CEvaluationNode* pNode = NULL;
  // convert the two children

  switch (subType)
    {
      case AND:
      case OR:
      case XOR:

        // The number of chidren may vary
        switch (iMax)
          {
            case 0:

              if (subType == AND)
                pNode = new CEvaluationNodeConstant(CEvaluationNodeConstant::TRUE, "TRUE");
              else
                pNode = new CEvaluationNodeConstant(CEvaluationNodeConstant::FALSE, "FALSE");

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

      case EQ:
      case NE:
      case GE:
      case GT:
      case LE:
      case LT:
        // all these are binary
        assert(iMax == 2);
        pNode = new CEvaluationNodeLogical(subType, data);
        pNode->addChild(children[0]);
        pNode->addChild(children[1]);
        break;

      case INVALID:
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
  SubType subType = (SubType)CEvaluationNode::subType(this->getType());
  ASTNode* node = new ASTNode();

  switch (subType)
    {
      case AND:
        node->setType(AST_LOGICAL_AND);
        break;

      case OR:
        node->setType(AST_LOGICAL_OR);
        break;

      case XOR:
        node->setType(AST_LOGICAL_XOR);
        break;

      case EQ:
        node->setType(AST_RELATIONAL_EQ);
        break;

      case NE:
        node->setType(AST_RELATIONAL_NEQ);
        break;

      case GT:
        node->setType(AST_RELATIONAL_GT);
        break;

      case GE:
        node->setType(AST_RELATIONAL_GEQ);
        break;

      case LT:
        node->setType(AST_RELATIONAL_LT);
        break;

      case LE:
        node->setType(AST_RELATIONAL_LEQ);
        break;

      case INVALID:
        break;

      default:
        subType = INVALID;
        break;
    }

  if (subType != INVALID)
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

      switch ((SubType)CEvaluationNode::subType(this->getType()))
        {
          case AND:
            data = " and ";
            break;

          case OR:
            data = " or ";
            break;

          case XOR:
            data = " xor ";
            break;

          case EQ:
            data = "=";
            break;

          case GE:
            data = "&gt;=";
            break;

          case GT:
            data = "&gt;";
            break;

          case LE:
            data = "&lt;=";
            break;

          case LT:
            data = "&lt;";
            break;

          case NE:
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

      flag = ((*mpLeft < * (CEvaluationNode *)this));

      if (flag) out << "<mfenced>" << std::endl;

      out << children[0];

      if (flag) out << "</mfenced>" << std::endl;

      out << "<mo>" << data << "</mo>" << std::endl;

      flag = ((*(CEvaluationNode *)this < *mpRight));

      if (!flag) out << "<mfenced>" << std::endl;

      out << children[1];

      if (!flag) out << "</mfenced>" << std::endl;

      out << "</mrow>" << std::endl;
    }

  return out.str();
}
