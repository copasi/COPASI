// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string>
#include <iostream>
#include "sbml/util/List.h"
#include "sbml/common/libsbml-config-common.h"

#include "ConverterASTNode.h"

#ifndef LIBSBML_USE_LEGACY_MATH

/**
 * Standard constructor
 */
ConverterASTNode::ConverterASTNode(): ASTNode()
{};

/**
 * Extension of the ASTNode class from libsbml. This class extends the original
 * ASTNode by some functions to manipulate the children of a node.
 */

/**
 * Sets the list of children to the one given as argument. The list is not
 * copied.
 */
void ConverterASTNode::setChildren(List* children)
{
  if (mNumber != NULL)
    {
      return; // cannot add children to a number type astnode
    }
  else if (mFunction != NULL)
    {
      unsigned int size = mFunction->getNumChildren();

      for (unsigned int i = mFunction->getNumChildren(); i > 0; i--)
        {
          mFunction->removeChild(i - 1);
        }

      for (unsigned int i = 0; i < children->getSize(); i++)
        {
          mFunction->addChild(static_cast<ASTNode*>(children->get(i)));
        }
    }
};

/**
 * Constructor that makes a ConverterASTNode from an ASTNode.
 */
ConverterASTNode::ConverterASTNode(const ASTNode &templ): ASTNode(templ.getType())
{
  if (this->getType() == AST_RATIONAL)
    {
      setValue(templ.getNumerator(), templ.getDenominator());
    }
  else if (this->getType() == AST_REAL)
    {
      setValue(templ.getReal());
    }
  else if (this->getType() == AST_REAL_E)
    {
      setValue(templ.getMantissa(), templ.getExponent());
    }

  if (this->getType() == AST_PLUS ||
      this->getType() == AST_MINUS ||
      this->getType() == AST_TIMES ||
      this->getType() == AST_DIVIDE ||
      this->getType() == AST_POWER)
    {
      this->mChar = templ.getCharacter();
    }
  else if (this->getType() == AST_INTEGER)
    {
      setValue(templ.getInteger());
    }

  if ((!this->isOperator()) && (!this->isNumber()) && !isConstant())
    {
      this->setName(templ.getName());
    }

  unsigned int counter;

  for (counter = 0; counter < templ.getNumChildren(); counter++)
    {
      this->addChild(new ConverterASTNode(*templ.getChild(counter)));
    }
};

/**
 * This function returns true if the node represents a user defined function.
 */
/*
bool ConverterASTNode::isUserDefinedFunction(){
    return (this->getType()==AST_FUNCTION);
};
 */

#ifdef COPASI_DEBUG
/**
 * Function to print an ASTNode and its children as a simple tree.
 * The arguments are the node to be printed and the number of spaces that this
 * node will be indented.
 */
void ConverterASTNode::printASTNode(const ASTNode* node, unsigned int indent)
{
  std::string spacer = "";
  unsigned int counter;

  for (counter = 0; counter < indent; counter++)
    {
      spacer += " ";
    }

  std::cout << spacer;

  if (node->isFunction() || node->isName())
    {
      if (node->getName() == NULL)
        std::cout << "emptyName";
      else
        std::cout << node->getName();
    }
  else if (node->isOperator())
    {
      std::cout << node->getCharacter();
    }
  else if (node->isInteger())
    {
      std::cout << node->getInteger();
    }
  else if (node->isReal())
    {
      std::cout << node->getReal();
    }
  else
    {
      std::cout << "[" << node->getType() << "]";
    }

  std::cout << std::endl;

  for (counter = 0; counter < node->getNumChildren(); counter++)
    {
      ConverterASTNode::printASTNode(node->getChild(counter), indent + 2);
    }
};
#endif // COPASI_DEBUG

ASTNode* ConverterASTNode::removeChild(unsigned int index)
{
  ASTNode * removedChild = getChild(index);

  this->ASTNode::removeChild(index);

  return removedChild;
};

/**
 * Constructor that makes a ConverterASTNode from an ASTNode.
 */
ASTNode* ConverterASTNode::shallowCopy(const ASTNode* pOrig)
{
  ConverterASTNode* pTmp = new ConverterASTNode(*pOrig);

  while (pTmp->getNumChildren() > 0)
    {
      delete pTmp->removeChild(0);
    }

  ASTNode* pCopy = pTmp->deepCopy();
  delete pTmp;
  return pCopy;
};

#else

/**
 * Standard constructor
 */
ConverterASTNode::ConverterASTNode(): ASTNode()
{};

/**
 * Extension of the ASTNode class from libsbml. This class extends the original
 * ASTNode by some functions to manipulate the children of a node.
 */

/**
 * Sets the list of children to the one given as argument. The list is not
 * copied.
 */
void ConverterASTNode::setChildren(List* children)
{
  this->mChildren = children;
};

void fixNaryRelational(ASTNode& node)
{
  if (!node.isRelational()) return;

  if (node.getNumChildren() == 2) return;

  ASTNodeType_t type = node.getType();
  std::vector<ASTNode*> nodes;
  node.setType(AST_LOGICAL_AND);

  for (int i = 1; i < (int)node.getNumChildren(); ++i)
    {
      ASTNode *current = new ASTNode(type);
      current->addChild(node.getChild(i - 1)->deepCopy());
      current->addChild(node.getChild(i)->deepCopy());
      nodes.push_back(current);
    }

  while (node.getNumChildren() > 0)
    {
      delete node.getChild(0);
      node.removeChild(0);
    }

  std::vector<ASTNode*>::iterator it = nodes.begin();

  while (it != nodes.end())
    {
      node.addChild(*it);
      ++it;
    }
}

/**
 * Constructor that makes a ConverterASTNode from an ASTNode.
 */
ConverterASTNode::ConverterASTNode(const ASTNode &templ): ASTNode(templ.getType())
{
  if (this->getType() == AST_RATIONAL)
    {
      this->mDenominator = templ.getDenominator();
      this->mInteger = templ.getNumerator();
    }
  else if (this->getType() == AST_REAL || this->getType() == AST_REAL_E)
    {
      this->mExponent = templ.getExponent();
      this->mReal = templ.getMantissa();
    }

  if (templ.getNumChildren() > 2 && (
        this->getType() == AST_RELATIONAL_EQ ||
        this->getType() == AST_RELATIONAL_NEQ ||
        this->getType() == AST_RELATIONAL_GEQ ||
        this->getType() == AST_RELATIONAL_GT ||
        this->getType() == AST_RELATIONAL_LEQ ||
        this->getType() == AST_RELATIONAL_LT))
    {
      // reduce to binary
      //const_cast<ASTNode&>(templ).reduceToBinary();
      fixNaryRelational(const_cast<ASTNode&>(templ));
      ASTNode::setType(AST_LOGICAL_AND);
    }

  if (this->getType() == AST_PLUS || this->getType() == AST_MINUS || this->getType() == AST_TIMES || this->getType() == AST_DIVIDE || this->getType() == AST_POWER)
    {
      this->mChar = templ.getCharacter();
    }
  else if (this->getType() == AST_INTEGER)
    {
      this->mInteger = templ.getInteger();
    }

  if ((!this->isOperator()) && (!this->isNumber()))
    {
      this->setName(templ.getName());
    }

  unsigned int counter;

  for (counter = 0; counter < templ.getNumChildren(); counter++)
    {
      this->addChild(new ConverterASTNode(*templ.getChild(counter)));
    }
};

/**
 * This function returns true if the node represents a user defined function.
 */
/*
bool ConverterASTNode::isUserDefinedFunction(){
    return (this->getType()==AST_FUNCTION);
};
 */

#ifdef COPASI_DEBUG
/**
 * Function to print an ASTNode and its children as a simple tree.
 * The arguments are the node to be printed and the number of spaces that this
 * node will be indented.
 */
void ConverterASTNode::printASTNode(const ASTNode* node, unsigned int indent)
{
  std::string spacer = "";
  unsigned int counter;

  for (counter = 0; counter < indent; counter++)
    {
      spacer += " ";
    }

  std::cout << spacer;

  if (node->isFunction() || node->isName())
    {
      std::cout << node->getName();
    }
  else if (node->isOperator())
    {
      std::cout << node->getCharacter();
    }
  else if (node->isInteger())
    {
      std::cout << node->getInteger();
    }
  else if (node->isReal())
    {
      std::cout << node->getReal();
    }
  else
    {
      std::cout << "[" << node->getType() << "]";
    }

  std::cout << std::endl;

  for (counter = 0; counter < node->getNumChildren(); counter++)
    {
      ConverterASTNode::printASTNode(node->getChild(counter), indent + 2);
    }
};
#endif // COPASI_DEBUG

ASTNode* ConverterASTNode::removeChild(unsigned int index)
{
  return static_cast<ASTNode*>(this->mChildren->remove(index));
};

/**
 * Constructor that makes a ConverterASTNode from an ASTNode.
 */
ASTNode* ConverterASTNode::shallowCopy(const ASTNode* pOrig)
{
  ConverterASTNode* pTmp = new ConverterASTNode(*pOrig);

  while (pTmp->getNumChildren() > 0)
    {
      delete pTmp->removeChild(0);
    }

  ASTNode* pCopy = pTmp->deepCopy();
  delete pTmp;
  return pCopy;
};

#endif // LIBSBML_USE_LEGACY_MATH
