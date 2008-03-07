// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeChoice.cpp,v $
//   $Revision: 1.15.6.3 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/03/07 11:07:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "mathematics.h"
#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeChoice::CEvaluationNodeChoice():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeChoice::CEvaluationNodeChoice(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type) (CEvaluationNode::CHOICE | subType), data),
    mpIf(NULL),
    mpTrue(NULL),
    mpFalse(NULL)
{
  switch (subType)
    {
    case IF:
      break;

    default:
      fatalError();
      break;
    }

  mPrecedence = PRECEDENCE_FUNCTION;
}

CEvaluationNodeChoice::CEvaluationNodeChoice(const CEvaluationNodeChoice & src):
    CEvaluationNode(src),
    mpIf(src.mpIf),
    mpTrue(src.mpTrue),
    mpFalse(src.mpFalse)
{}

CEvaluationNodeChoice::~CEvaluationNodeChoice() {}

const C_FLOAT64 & CEvaluationNodeChoice::value() const
  {
    C_FLOAT64 &Value = *const_cast<C_FLOAT64 *>(&mValue);
    if (mpIf->value() != 0.0) return Value = mpTrue->value();
    else return Value = mpFalse->value();
  }

bool CEvaluationNodeChoice::compile(const CEvaluationTree * /* pTree */)
{
  mpIf = static_cast<CEvaluationNode *>(getChild());
  if (mpIf == NULL) return false;

  mpTrue = static_cast<CEvaluationNode *>(mpIf->getSibling());
  if (mpTrue == NULL) return false;

  mpFalse = static_cast<CEvaluationNode *>(mpTrue->getSibling());
  if (mpFalse == NULL) return false;

  return (mpFalse->getSibling() == NULL); // We must have exactly three children
}

std::string CEvaluationNodeChoice::getInfix() const
  {
    if (const_cast<CEvaluationNodeChoice *>(this)->compile(NULL))
      return mData + "(" + mpIf->getInfix() + "," + mpTrue->getInfix() + "," + mpFalse->getInfix() + ")";
    else
      return "@";
  }

std::string CEvaluationNodeChoice::getDisplayString(const CEvaluationTree * pTree) const
  {
    if (const_cast<CEvaluationNodeChoice *>(this)->compile(NULL))
      return mData + "(" + mpIf->getDisplayString(pTree) + "," + mpTrue->getDisplayString(pTree) + "," + mpFalse->getDisplayString(pTree) + ")";
    else
      return "@";
  }

std::string CEvaluationNodeChoice::getDisplay_C_String(const CEvaluationTree * pTree) const
  {
    if (const_cast<CEvaluationNodeChoice *>(this)->compile(NULL))
      return "(" + mpIf->getDisplay_C_String(pTree) + " ? " + mpTrue->getDisplay_C_String(pTree) + " : " + mpFalse->getDisplay_C_String(pTree) + ")";
    else
      return "@";
  }

std::string CEvaluationNodeChoice::getDisplay_MMD_String(const CEvaluationTree * pTree) const
  {
    if (const_cast<CEvaluationNodeChoice *>(this)->compile(NULL))
      return "(if " + mpIf->getDisplay_MMD_String(pTree) + " then " + mpTrue->getDisplay_MMD_String(pTree) + " else " + mpFalse->getDisplay_MMD_String(pTree) + ")";
    else
      return "@";
  }

std::string CEvaluationNodeChoice::getDisplay_XPP_String(const CEvaluationTree * pTree) const
  {
    if (const_cast<CEvaluationNodeChoice *>(this)->compile(NULL))
      return "if(" + mpIf->getDisplay_XPP_String(pTree) + ")then(" + mpTrue->getDisplay_XPP_String(pTree) + ")else(" + mpFalse->getDisplay_XPP_String(pTree) + ")";
    else
      return "@"; //TODO
  }

CEvaluationNode* CEvaluationNodeChoice::createNodeFromASTTree(const ASTNode& node)
{
  SubType subType;
  std::string data = "";
  switch (node.getType())
    {
    case AST_FUNCTION_PIECEWISE:
      subType = IF;
      data = "if";
      break;
    default:
      subType = INVALID;
      break;
    }

  CEvaluationNode* convertedNode = new CEvaluationNodeChoice(subType, data);
  /*
  // convert the three children
  assert(node.getNumChildren()==3);
  */
  // a piecewise function definition can have zero or more children.
  if (node.getNumChildren() == 0)
    {
      // create a NaN node
      delete convertedNode;
      convertedNode = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NaN");
    }
  else if (node.getNumChildren() == 1)
    {
      // this must be the otherwise
      // It is not clearly specified what happens if there are no pieces, but
      // an otherwise. I would assume that in this case, the otherwise always
      // takes effect
      convertedNode = CEvaluationTree::convertASTNode(*node.getChild(0));
    }
  else
    {
      unsigned int i, iMax = node.getNumChildren();
      // the first iMax-(iMax%2) children must be piece elements
      CEvaluationNode* pPiecewise = convertedNode;
      for (i = 0;i < iMax / 2;++i)
        {
          ASTNode* pChild1 = node.getChild(i * 2); // the value, child 1 if the piecewise
          ASTNode* pChild2 = node.getChild(i * 2 + 1); // the condition, child 0 of the piecewise
          pPiecewise->addChild(CEvaluationTree::convertASTNode(*pChild2)); // add the condition
          pPiecewise->addChild(CEvaluationTree::convertASTNode(*pChild1));
          if (i != (iMax / 2) - 1)
            {
              // create a new piecewise as the else element
              CEvaluationNode* pTmp = new CEvaluationNodeChoice(CEvaluationNodeChoice::IF, "if");
              pPiecewise->addChild(pTmp);
              pPiecewise = pTmp;
            }
        }
      // if iMax%2 == 1, we have an otherwise element
      CEvaluationNode* pOtherwise = NULL;
      if ((iMax % 2) == 1)
        {
          pOtherwise = CEvaluationTree::convertASTNode(*node.getChild(iMax - 1));
        }
      else
        {
          pOtherwise = new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NaN");
        }
      // add the otherwise to the deepest piecewise node
      pPiecewise->addChild(pOtherwise);
    }
  /*
  if (subType != INVALID)
    {
      convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getChild(1)));
      convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getChild(0)));
      convertedNode->addChild(CEvaluationTree::convertASTNode(*node.getChild(2)));
    }
  */
  return convertedNode;
}

ASTNode* CEvaluationNodeChoice::toAST() const
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
    node->addChild(child2->toAST());
    node->addChild(child1->toAST());
    node->addChild(child3->toAST());
    return node;
  }

#include "utilities/copasimathml.h"

void CEvaluationNodeChoice::writeMathML(std::ostream & out,
                                        const std::vector<std::vector<std::string> > & env,
                                        bool expand,
                                        unsigned C_INT32 l) const
  {
    if (const_cast<CEvaluationNodeChoice *>(this)->compile(NULL))
      {
        out << SPC(l) << "<mrow>" << std::endl;
        out << SPC(l + 1) << "<mo> {</mo>" << std::endl;
        out << SPC(l + 1) << "<mtable>" << std::endl;

        out << SPC(l + 2) << "<mtr>" << std::endl;

        out << SPC(l + 3) << "<mtd>" << std::endl;
        mpTrue->writeMathML(out, env, expand, l + 3);
        out << SPC(l + 3) << "<mo> , </mo>" << std::endl;
        out << SPC(l + 3) << "</mtd>" << std::endl;

        out << SPC(l + 3) << "<mtd>" << std::endl;
        mpIf->writeMathML(out, env, expand, l + 3);

        out << SPC(l + 3) << "</mtd>" << std::endl;

        out << SPC(l + 2) << "</mtr>" << std::endl;

        out << SPC(l + 2) << "<mtr>" << std::endl;

        out << SPC(l + 3) << "<mtd>" << std::endl;
        mpFalse->writeMathML(out, env, expand, l + 3);
        out << SPC(l + 3) << "<mo> , </mo>" << std::endl;

        out << SPC(l + 3) << "</mtd>" << std::endl;
        out << SPC(l + 3) << "<mtd>" << std::endl;
        out << SPC(l + 3) << "<mo> else </mo>" << std::endl;
        out << SPC(l + 3) << "</mtd>" << std::endl;

        out << SPC(l + 2) << "</mtr>" << std::endl;

        out << SPC(l + 1) << "</mtable>" << std::endl;
        out << SPC(l) << "</mrow>" << std::endl;
      }
  }
