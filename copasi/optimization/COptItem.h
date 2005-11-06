/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptItem.h,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/06 22:15:30 $
   End CVS Header */

#ifndef COPASI_COptItem
#define COPASI_COptItem

#include <vector>

#include "report/CCopasiObject.h"
#include "report/CCopasiContainer.h"
#include "utilities/CCopasiParameterGroup.h"

class CCopasiObjectName;
class COptProblem;

class COptItem: public CCopasiParameterGroup
  {
    //Operations
  protected:
    /**
     * Checks whether val1 < val2
     * @param const C_FLOAT64 & val1
     * @param const C_FLOAT64 & val2
     * @return bool fulfills
     */
    static bool less(const C_FLOAT64 & val1, const C_FLOAT64 & val2);

    /**
     * Checks whether val1 <= val2
     * @param const C_FLOAT64 & val1
     * @param const C_FLOAT64 & val2
     * @return bool fulfills
     */
    static bool lessOrEqual(const C_FLOAT64 & val1, const C_FLOAT64 & val2);

  public:
    /**
     * Default constructor
     * @param const std::string & name (default: OptimizationItem)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptItem(const std::string & name = "OptimizationItem",
             const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const COptItem & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptItem(const COptItem & src,
             const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor used for reading copasi files
     * @param const CCopasiParameterGroup & group
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptItem(const CCopasiParameterGroup & group,
             const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COptItem();

    /**
     * Set the object of the optimization item.
     * @param const CCopasiObjectName & objectCN
     * @return bool success
     */
    bool setObjectCN(const CCopasiObjectName & objectCN);

    /**
     * Retrieve the object of the optimization item.
     * @return const CCopasiObjectName objectCN
     */
    const CCopasiObjectName getObjectCN() const;

    /**
     * Retrieve the display name of the optimization item.
     * @return std::string displayName
     */
    std::string getObjectDisplayName() const;

    /**
     * Set the lower bound.
     * @param const CCopasiObjectName & lowerBound
     * @return bool success
     */
    bool setLowerBound(const CCopasiObjectName & lowerBound);

    /**
     * Retrieve the lower bound.
     * @return const std::string lowerBound
     */
    const std::string getLowerBound() const;

    /**
     * Set the upper bound.
     * @param const CCopasiObjectName & upperBound
     * @return bool success
     */
    bool setUpperBound(const CCopasiObjectName & upperBound);

    /**
     * Retrieve the upper bound.
     * @return const std::string upperBound
     */
    const std::string getUpperBound() const;

    /**
     * Retrieve the update method
     * @return UpdateMethod * pUpdateMethod
     */
    virtual UpdateMethod * getUpdateMethod() const;

    /**
     * Check the validity of the optimization item.
     * @return bool isValid
     */
    virtual bool isValid() const;

    /**
     * Check whether the group describes a valid optimization item.
     * @param CCopasiParameterGroup & group
     * @return bool isValid
     */
    static bool isValid(CCopasiParameterGroup & group);

    /**
     * Compile the optimization item. This function must be called 
     * before any of the check functions are called.
     * @param const std::vector< CCopasiContainer * > listOfContainer
     * @return bool success
     */
    virtual bool compile(const std::vector< CCopasiContainer * > listOfContainer =
                           CCopasiContainer::EmptyList);

    /**
     * This functions check whether the current value is within the limits
     * of the optimization item.
     * @return C_INT32 result (-1: to small, 0: within boundaries, 1 to large)
     */
    C_INT32 checkConstraint() const;

    /**
     * This functions check whether the value is within the limits
     * of the optimization item.
     * @param const C_FLOAT64 & value
     * @return C_INT32 result (-1: to small, 0: within boundaries, 1 to large)
     */
    C_INT32 checkConstraint(const C_FLOAT64 & value) const;

    /**
     * Checks whether the value fulfills the lower bound constraint.
     * @param const C_FLOAT64 & value
     * @return bool fulfills
     */
    bool checkLowerBound(const C_FLOAT64 & value) const;

    /**
     * Checks whether the value fulfills the upper bound constraint.
     * @param const C_FLOAT64 & value
     * @return bool fulfills
     */
    bool checkUpperBound(const C_FLOAT64 & value) const;

    /**
     * Retrieve the value of the optimization object.
     * @return const C_FLOAT64 * objectValue
     */
    virtual const C_FLOAT64 * getObjectValue() const;

    /**
     * Retrieve the value of the lower bound.
     * @return const C_FLOAT64 * lowerBoundValue
     */
    inline const C_FLOAT64 * COptItem::getLowerBoundValue() const
      {return mpLowerBound;}

    /**
     * Retrieve the value of the upper bound.
     * @return const C_FLOAT64 * upperBoundValue
     */
    inline const C_FLOAT64 * COptItem::getUpperBoundValue() const
      {return mpUpperBound;}

    /**
     * Output stream operator
     * @param ostream & os
     * @param const COptItem & A
     * @return ostream & os
     */
    friend std::ostream &operator<<(std::ostream &os, const COptItem & o);

  private:
    /**
     * Allocates all group parameters and assures that they are 
     * properly initialized.
     */
    void initializeParameter();

    //Attributes:
  private:
    /**
     * A pointer to the value of the CCopasiParameter holding the ObjectCN
     */
    std::string * mpParmObjectCN;

    /**
     * A pointer to the value of the CCopasiParameter holding the LowerBound
     */
    std::string * mpParmLowerBound;

    /**
     * A pointer to the value of the CCopasiParameter holding the UpperBound
     */
    std::string * mpParmUpperBound;

    /**
     * A pointer to the object
     */
    const CCopasiObject * mpObject;

    /**
     * A pointer to the object update method
     */
    UpdateMethod * mpMethod;

    /**
     * A pointer to the object value
     */
    const C_FLOAT64 * mpObjectValue;

    /**
     * A pointer to the object for the lower bound
     */
    const CCopasiObject * mpLowerObject;

    /**
     * A pointer to the lower bound value
     */
    const C_FLOAT64 * mpLowerBound;

    /**
     * The value of the lower bound (only if not on object) 
     */
    C_FLOAT64 mLowerBound;

    /**
     * A pointer to the object for the upper bound
     */
    const CCopasiObject * mpUpperObject;

    /**
     * A pointer to the upper bound value
     */
    const C_FLOAT64 * mpUpperBound;

    /**
     * The value of the upper bound (only if not on object) 
     */
    C_FLOAT64 mUpperBound;
  };

#endif // COPASI_COptItem
