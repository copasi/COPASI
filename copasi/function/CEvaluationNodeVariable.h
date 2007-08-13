// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeVariable.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/13 15:05:48 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEvaluationNodeVariable
#define COPASI_CEvaluationNodeVariable

class ASTNode;

/**
 * This is class for nodes presenting numbers used in an evaluation trees
 */
class CEvaluationNodeVariable : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
     * The typing of variables must be handled by the tree.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      ANY = 0x00000000
    };

    // Operations
  private:
    /**
     * Default constructor
     */
    CEvaluationNodeVariable();

  public:
    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeVariable(const SubType & subType,
                            const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeVariable & src
     */
    CEvaluationNodeVariable(const CEvaluationNodeVariable & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeVariable();

    /**
     * Compile a node;
     * @param const CEvaluationTree * pTree
     * @return bool success;
     */
    virtual bool compile(const CEvaluationTree * pTree);

    /**
     * Retrieve the value of the node
     * @return const C_FLOAT64 & value
     */
    virtual inline const C_FLOAT64 & value() const;

    /**
     * Converts this node to an AST Node of type AST_NAME
     * @return ASTNode* the resulting ASTNode.
     */
    virtual ASTNode* toAST() const;

    /**
     * generate display MathML recursively
     */
    virtual void writeMathML(std::ostream & out,
                             const std::vector<std::vector<std::string> > & env,
                             bool expand = true,
                             unsigned C_INT32 l = 0) const;

    /**
     * return the index of the variable in the function parameter list
     */
    unsigned C_INT32 getIndex() const;

    //Attributes
  private:
    /**
     * Pointer to the evaluation tree.
     */
    const CEvaluationTree * mpTree;

    /**
     * Index of the variable used to retrieve its value from the tree.
     */
    unsigned C_INT32 mIndex;
  };

#endif // COPASI_CEvaluationNodeVariable
