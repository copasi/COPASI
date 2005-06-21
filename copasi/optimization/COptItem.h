/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptItem.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/21 20:34:20 $
   End CVS Header */

#ifndef COPASI_COptItem
#define COPASI_COptItem

#include <vector>

#include "report/CCopasiObject.h"
#include "report/CCopasiContainer.h"

class CCopasiParameterGroup;
class CCopasiObjectName;
class COptProblem;

class COptItem
  {
    friend class COptProblem;

    //Operations
  private:
    /**
     * Specific Constructor
     */
    COptItem(CCopasiParameterGroup & group);

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
     * Copy Constructor
     * @param COptItem & src
     */
    COptItem(COptItem & src);

    /**
     * Destructor
     */
    ~COptItem();

    /**
     * Initialize the optimization item.
     * @param const CCopasiObjectName & objectCN
     * @return bool success
     */
    bool initialize(const CCopasiObjectName & objectCN);

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
     * Set the lower relationship.
     * @param const std::string & lowerRel (< or <=)
     * @return bool success
     */
    bool setLowerRelation(const std::string & lowerRel);

    /**
     * Retrieve the lower relationship.
     * @return const std::string lowerRel
     */
    const std::string getLowerRelation() const;

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
     * Set the upper relationship.
     * @param const std::string & upperRel (< or <=)
     * @return bool success
     */
    bool setUpperRelation(const std::string & upperRel);

    /**
     * Retrieve the upper relationship.
     * @return const std::string upperRel
     */
    const std::string getUpperRelation() const;

    /**
     * Retrieve the update method
     * @return UpdateMethod * pUpdateMethod
     */
    UpdateMethod * getUpdateMethod() const;

    /**
     * Check the validity of the optimization item.
     * @return bool isValid
     */
    bool isValid() const;

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
    bool compile(const std::vector< CCopasiContainer * > listOfContainer =
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
    const C_FLOAT64 * getObjectValue() const;

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

    //Attributes:
  private:
    /**
     * A pointer to the parameter group which stores the information.
     */
    CCopasiParameterGroup * mpGroup;

    /**
     * A pointer to the object value
     */
    UpdateMethod * mpMethod;

    /**
     * A pointer to the object value
     */
    const C_FLOAT64 * mpObjectValue;

    /**
     * A pointer to the lower bound value
     */
    const C_FLOAT64 * mpLowerBound;

    /**
     * The value of the lower bound (only if not on object) 
     */
    C_FLOAT64 mLowerBound;

    /**
     * A pointer to the function for checking the lower relationship
     * @param const C_FLOAT64 & val1
     * @param const C_FLOAT64 & val2
     * @return bool fulfills
     */
    bool (*mpLowerRel)(const C_FLOAT64 & val1, const C_FLOAT64 & val2);

    /**
     * A pointer to the upper bound value
     */
    const C_FLOAT64 * mpUpperBound;

    /**
     * The value of the upper bound (only if not on object) 
     */
    C_FLOAT64 mUpperBound;

    /**
     * A pointer to the function for checking the upper relationship
     * @param const C_FLOAT64 & val1
     * @param const C_FLOAT64 & val2
     * @return bool fulfills
     */
    bool (*mpUpperRel)(const C_FLOAT64 & val1, const C_FLOAT64 & val2);
  };

#endif // COPASI_COptItem
