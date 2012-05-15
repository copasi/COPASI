// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeChoice.cpp,v $
//   $Revision: 1.23 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/05/15 18:32:57 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

#include "sbml/math/ASTNode.h"

CEvaluationNodeChoice::CEvaluationNodeChoice():
    CEvaluationNode(CEvaluationNode::INVALID, "")
{mPrecedence = PRECEDENCE_NUMBER;}

CEvaluationNodeChoice::CEvaluationNodeChoice(const SubType & subType,
    const Data & data):
    CEvaluationNode((Type)(CEvaluationNode::CHOICE | subType), data),
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

void CEvaluationNodeChoice::calculate()
{
  if (mpIf->getValue() > 0.5)
    {
      mValue = mpTrue->getValue();
    }
  else
    {
      mValue = mpFalse->getValue();
    }
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

// virtual
std::string CEvaluationNodeChoice::getInfix(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeChoice *>(this)->compile(NULL))
    return mData + "(" + children[0] + "," + children[1] + "," + children[2] + ")";
  else
    return "@";
}

// virtual
std::string CEvaluationNodeChoice::getDisplayString(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeChoice *>(this)->compile(NULL))
    return mData + "(" + children[0] + "," + children[1] + "," + children[2] + ")";
  else
    return "@";
}

// virtual
std::string CEvaluationNodeChoice::getCCodeString(const std::vector< std::string > & children) const
{
  if (const_cast<CEvaluationNodeChoice *>(this)->compile(NULL))
    return "(" + children[0] + " ? " + children[1] + " : " + children[2] + ")";
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

// static
CEvaluationNode * CEvaluationNodeChoice::fromAST(const ASTNode * pASTNode, const std::vector< CEvaluationNode * > & children)
{
  assert(pASTNode->getNumChildren() == children.size());

  size_t i = 0, iMax = children.size();

  // a piecewise function definition can have zero or more children.
  if (iMax == 0)
    {
      // create a NaN node
      return new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NAN");
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
        subType = IF;
        data = "if";
        break;

      default:
        subType = INVALID;
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
            pCurrent->addChild(new CEvaluationNodeConstant(CEvaluationNodeConstant::_NaN, "NAN"));
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

ASTNode* CEvaluationNodeChoice::toAST(const CCopasiDataModel* pDataModel) const
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

#include "utilities/copasimathml.h"

void CEvaluationNodeChoice::writeMathML(std::ostream & out,
                                        const std::vector<std::vector<std::string> > & env,
                                        bool expand,
                                        size_t l) const
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
