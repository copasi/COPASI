// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef ConverterASTNode_HPP__
#define ConverterASTNode_HPP__

#include "copasi/copasi.h"

#include "sbml/math/ASTNode.h"

class ConverterASTNode : public ASTNode
{
public:
  /**
   * Standard constructor.
   */
  ConverterASTNode();

  /**
   * Sets the list of children to the one given as argument. The list is not
   * copied.
   */
  void setChildren(List* children);

  /**
   * Removes a child from the list of children.
   */
  ASTNode* removeChild(unsigned int index);

  /**
   * Constructor that makes a ConverterASTNode from an ASTNode.
   */
  ConverterASTNode(const ASTNode& templ);

  /**
   * This function returns true if the node represents a user defined function.
   */
  //bool isUserDefinedFunction();

  // make a shallow copy of an ASTNode
  static ASTNode* shallowCopy(const ASTNode* pOrig);

#ifdef COPASI_DEBUG
  /**
   * Function to print an ASTNode and its children as a simple tree.
   * The arguments are the node to be printed and the number of spaces that this
   * node will be indented.
   */
  static void printASTNode(const ASTNode* node, unsigned int indent = 0);
#endif // COPASI_DEBUG
};

#endif
