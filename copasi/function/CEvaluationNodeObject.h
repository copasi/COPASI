/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeObject.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/15 18:10:51 $
   End CVS Header */

#ifndef COPASI_CEvaluationNodeObject
#define COPASI_CEvaluationNodeObject

#include "report/CCopasiObjectName.h"

class CRegisteredObjectName;

/**
 * This is class for nodes presenting numbers used in an evaluation trees
 */
class CEvaluationNodeObject : public CEvaluationNode
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
    CEvaluationNodeObject();

  public:
    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeObject(const SubType & subType,
                          const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeObject & src
     */
    CEvaluationNodeObject(const CEvaluationNodeObject & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeObject();

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
    virtual inline const C_FLOAT64 & value() const {return *mpValue;}

    /**
     * Retrieve the value of the node. This method is superceded
     * value() which will perform faster.
     * @return const Data & value
     */
    virtual Data getData() const;

    /**
     * Set the data of the Node.
     * @param const Data & data
     * @return bool success
     */
    virtual bool setData(const Data & data);

    /**
     * Create a new operator node from an ASTNode tree.
     * @param const ASTNode* node
     * @return CEvaluationNode* return a pointer to the newly created node;
     */
    static CEvaluationNode* createNodeFromASTTree(const ASTNode& node);

    //Attributes
  private:
    /**
     * Pointer to the value of the variable.
     */
    C_FLOAT64 * mpValue;

    /**
     * The registered object name to track eventual renaming.
     */
    CRegisteredObjectName mRegisteredObjectCN;
  };

#endif // COPASI_CEvaluationNodeObject
