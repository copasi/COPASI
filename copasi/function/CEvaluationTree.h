/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationTree.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/31 17:48:57 $
   End CVS Header */

#ifndef COPASI_CEvaluationTree
#define COPASI_CEvaluationTree

#include "utilities/CCopasiTree.h"

class CEvaluationNode;
class CCopasiObjectName;

class CEvaluationTree : public CCopasiTree < CEvaluationNode >
  {
    // Operations
  public:
    /**
     * Default constructor
     */
    CEvaluationTree();

    /**
     * Destructor
     */
    virtual ~CEvaluationTree();

    /**
     * Retrieve a pointer to the value of the named variable.
     * @param const std::string & name
     * @return C_FLOAT64 * value
     */
    C_FLOAT64 * getVariableValue(const std::string & name) const;

    /**
     * Retrieve a pointer to the value of the object define dby CN.
     * @param const CCopasiObjectName & CN
     * @return C_FLOAT64 * value
     */
    C_FLOAT64 * getObjectValue(const CCopasiObjectName & CN) const;
  };

#endif // COPASI_CEvaluationTree
