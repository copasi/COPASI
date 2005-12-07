/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CKinFunction.h,v $
   $Revision: 1.31 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/12/07 10:55:59 $
   End CVS Header */

/**
 * CKinFunction
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CKinFunction
#define COPASI_CKinFunction

#include <vector>

#include "CFunction.h"

#include "CNodeK.h"
#include "utilities/CReadConfig.h"

class CCopasiObject;

/** @dia:pos 61.7476,54.3157 */
/** @dia:route CFunction; v,58.2,35.55,51.6337,82.8684,54.3157 */
class CKinFunction : public CFunction
  {
    // Attributes
  private:
    /**
     *  The vector of nodes of the binary tree of the function
     *  @supplierCardinality 0..*
     *  @associates <{CNodeK}>
     */
    /** @dia:route 0,2; h,61.7476,54.3157,55.1707,42.4925,46.911 */
    std::vector< CNodeK * > mNodes;

    std::vector<CCopasiObject*> ObjList;
    /**
     *  Internal variable
     */
    unsigned C_INT32 mNidx;

    // Operations
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CKinFunction(const std::string & name = "NoName",
                 const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CFunction &" src
     * @param "CReadConfig *" configBuffer (Default = NULL)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CKinFunction(const CFunction & src,
                 CReadConfig * configBuffer = NULL,
                 const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CKinFunction &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CKinFunction(const CKinFunction & src,
                 const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor
     */
    ~CKinFunction();

    /**
     *  Cleanup
     */
    void cleanup();

    virtual void writeMathML(std::ostream & out) const;

    /**
     *  Retreives the nodes of the function
     */
    std::vector< CNodeK * > & getNodes();

  private:

    /**
        *  This function indentify the object from name
        */ 
    //bool createObjList();

    /**
        *  This  connects the nodes to build the binary function tree
        */ 
    //C_INT32 connectNodes();

    /**
     * This function is part of the algorithm that builds the binary tree.
     * The expression to the right of the current node (mNidx) is parsed until
     * an operand with a left priority <= the argument (right priority) 
     * is encounterd. The pointer to the top node of the parsed expression is
     * returned.
     * @param C_INT16 priority
     * @return CNodeK *
     */ 
    //CNodeK * parseExpression(C_INT16 priority);

    /**
     * This function is part of the algorithm that builds the binary tree.
     * It returns a pointer to next primary node. Here next is with repect 
     * to the internal counter mNidx. If the node is a dead end, i.e., any contant
     * a pointer the node is returned. If then node is '(' the expression between
     * the node and the matching ')' is parsed and a pointer to the resulting top
     * node is returned. If the node is a function or a unary minus the argument is
     * parsed and a pointer to the function node is returned. 
     * @return CNodeK *
     */ 
    //CNodeK * parsePrimary();

    /**
     *  This function creates the parameter description for older file versions
     */
    void createParameters();

    /**
     * Cleanup nodes
     */
    void cleanupNodes();
  };

#endif // COPASI_CKinFunction
