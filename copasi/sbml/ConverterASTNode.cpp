/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/ConverterASTNode.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/06/15 16:35:26 $
   End CVS Header */

#include "ConverterASTNode.h"
#include <string.h>
#include <iostream>

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
  for (unsigned int counter = 0; counter < templ.getNumChildren(); counter++)
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

/**
 * Function to print an ASTNode and its children as a simple tree.
 * The arguments are the node to be printed and the number of spaces that this
 * node will be indented.
 */
void ConverterASTNode::printASTNode(const ASTNode* node, unsigned int indent)
{
  std::string spacer = "";
  for (unsigned int counter = 0; counter < indent; counter++)
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
  for (unsigned int counter = 0; counter < node->getNumChildren(); counter++)
    {
      ConverterASTNode::printASTNode(node->getChild(counter), indent + 2);
    }
};
