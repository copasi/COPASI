/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeChoice.h,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: nsimus $
   $Date: 2006/05/02 13:05:50 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEvaluationNodeChoice
#define COPASI_CEvaluationNodeChoice

#include <limits>

#include "mathematics.h"
#include "utilities/CCopasiMessage.h"

/**
 * This is the class for nodes presenting opertors used in an evaluation trees.
 */
class CEvaluationNodeChoice : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      IF = 0x00000000
    };

    // Operations
  private:
    /**
     * Default constructor
     */
    CEvaluationNodeChoice();

  public:
    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeChoice(const SubType & subType,
                          const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeChoice & src
     */
    CEvaluationNodeChoice(const CEvaluationNodeChoice & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeChoice();

    /**
     * Retrieve the value of the node
     * @return const C_FLOAT64 & value
     */
    virtual const C_FLOAT64 & value() const;

    /**
     * Compile a node;
     * @param const CEvaluationTree * pTree
     * @return bool success;
     */
    virtual bool compile(const CEvaluationTree * pTree);

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
     * Retrieve the display string of the node and its eventual child nodes in C .
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
     * Creates a new CEvaluationNodeChoice from an ASTNode.
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
     *  generate display MathML recursively
     **/
    virtual void writeMathML(std::ostream & out, const std::vector<std::vector<std::string> > & env, bool expand = true, unsigned C_INT32 l = 0) const;

  private:

    // Attributes
  private:
    CEvaluationNode * mpIf;
    CEvaluationNode * mpTrue;
    CEvaluationNode * mpFalse;
  };

#endif // COPASI_CEvaluationNodeChoice
