/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CExpression.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/15 19:09:28 $
   End CVS Header */

#ifndef COPASI_CExpression
#define COPASI_CExpression

#include "CEvaluationTree.h"
#include "report/CCopasiContainer.h"

class CExpression:
      public CCopasiContainer,
      protected CEvaluationTree

  {
    // Operations
  private:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CExpression(const std::string & name = "NoName",
                const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CExpression &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CExpression(const CExpression & src,
                const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor
     */
    virtual ~CExpression();

    /**
     * Compile the function.
     * @param std::vector< CCopasiContainer * > listOfContainer (Default: CCopasiContainer::EmptyList)
     * @return bool success
     */
    virtual bool compile(std::vector< CCopasiContainer * > listOfContainer =
                           CCopasiContainer::EmptyList);

    /**
     * Calculates the value of the function
     * @return C_FLOAT64 result
     */
    virtual C_FLOAT64 calcValue();

    /**
     * Retrieve a pointer to the value of the object define dby CN.
     * @param const CCopasiObjectName & CN
     * @return C_FLOAT64 * value
     */
    virtual C_FLOAT64 * getObjectValue(const CCopasiObjectName & CN) const;

    // Attribute
  protected:
    /**
     * Pointer to the list of containers used for compilation.
     */
    std::vector< CCopasiContainer * > * mpListOfContainer;
  };

#endif // COPASI_CExpression
