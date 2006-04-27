/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeWhiteSpace.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:28:26 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEvaluationNodeWhiteSpace
#define COPASI_CEvaluationNodeWhiteSpace

class ASTNode;

/**
 * This is class for nodes presenting numbers used in an evaluation trees
 */
class CEvaluationNodeWhiteSpace : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
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
    CEvaluationNodeWhiteSpace();

  public:
    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeWhiteSpace(const SubType & subType,
                              const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeWhiteSpace & src
     */
    CEvaluationNodeWhiteSpace(const CEvaluationNodeWhiteSpace & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeWhiteSpace();

    /**
     * Create a new ASTNode corresponding to this OperatorNode.
     * @return ASTNode* return a pointer to the newly created node;
     */
    virtual ASTNode* toAST() const;
  };

#endif // COPASI_CEvaluationNodeWhiteSpace
