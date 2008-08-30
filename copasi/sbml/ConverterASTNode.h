/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/ConverterASTNode.h,v $
 $Revision: 1.8 $
 $Name:  $
 $Author: gauges $
 $Date: 2008/08/30 16:06:49 $
 End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef ConverterASTNode_HPP__
#define ConverterASTNode_HPP__

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
