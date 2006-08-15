/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeVector.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: nsimus $
   $Date: 2006/08/15 11:46:10 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEvaluationNodeVector
#define COPASI_CEvaluationNodeVector

#include <limits>

#include "mathematics.h"
#include "utilities/CCopasiMessage.h"

/**
 * This is the class for nodes presenting opertors used in an evaluation trees.
 */
class CEvaluationNodeVector : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      VECTOR = 0x00000000
    };

    // Operations
  public:
    /**
     * Default constructor
     */
    CEvaluationNodeVector();

    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeVector(const SubType & subType,
                          const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeVector & src
     */
    CEvaluationNodeVector(const CEvaluationNodeVector & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeVector();

    /**
     * Retrieve the value of the node
     * @return const C_FLOAT64 & value
     */
    virtual const C_FLOAT64 & value() const;

    /**
     * Retrieve the infix value of the node and its eventual child nodes.
     * @return const Data & value
     */
    virtual std::string getInfix() const;

    /**
     * Retrieve the display string of the node and its eventual child nodes.
     * @return const Data & value
     */
    virtual std::string getDisplayString(const CEvaluationTree * pTree) const;

    /**
     * Retrieve the display string of the node and its eventual child nodes in C.
     * @return const Data & value
     */
    virtual std::string getDisplay_C_String(const CEvaluationTree * pTree) const;

    /**
     * Retrieve the display string of the node and its eventual child nodes
     * in Berkeley Madonna format.
     * @return const Data & value
     */
    virtual std::string getDisplay_MMD_String(const CEvaluationTree * pTree) const;

    /**
     * Retrieve the display string of the node and its eventual child nodes
     * in XPPAUT format.
     * @return const Data & value
     */
    virtual std::string getDisplay_XPP_String(const CEvaluationTree * pTree) const;

    /**
     * Creates a new CEvaluationNodeVector from an ASTNode.
     * @param const ASTNode* node
     * @return CEvaluationNode* return a pointer to the newly created node;
     */
    static CEvaluationNode* createNodeFromASTTree(const ASTNode& node);

    /**
     * Create a new ASTNode corresponding to this choice node.
     * @return ASTNode* return a pointer to the newly created node;
     */
    virtual ASTNode* toAST() const;

    /**
     * Add a child to a node.
     * If pAfter == this the child will be inserted at the fornt of the list
     * of children.
     * @param CCopasiNode< Data > * pChild
     * @param CCopasiNode< Data > * pAfter
     *        (default: NULL appended to the list of children)
     * @return bool Success
     */
    bool addChild(CCopasiNode< Data > * pChild,
                  CCopasiNode< Data > * pAfter = NULL);

    /**
     * Retrieve the vector of evaluation nodes
     * @return const std::vector< CEvaluationNode * > & vector
     */
    const std::vector< CEvaluationNode * > & getVector() const;

  private:

    // Attributes
  private:
    std::vector< CEvaluationNode * > mVector;
  };

#endif // COPASI_CEvaluationNodeVector
