/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/ConverterASTNode.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/06/16 13:29:59 $
   End CVS Header */

#ifndef ConverterASTNode_HPP__
#define ConverterASTNode_HPP__

#include "sbml/ASTNode.hpp"

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
     * Constructor that makes a ConverterASTNode from an ASTNode.
     */
    ConverterASTNode(const ASTNode& templ);

    /**
     * This function returns true if the node represents a user defined function.
     */ 
    //bool isUserDefinedFunction();

    /**
     * Function to print an ASTNode and its children as a simple tree.
     * The arguments are the node to be printed and the number of spaces that this
     * node will be indented.
     */
    static void printASTNode(const ASTNode* node, unsigned int indent = 0);
  };

#endif
