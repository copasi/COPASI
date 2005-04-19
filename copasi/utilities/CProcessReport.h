/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CProcessReport.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/19 11:43:41 $
   End CVS Header */

#ifndef COPASI_CProcessReport
#define COPASI_CProcessReport

#include <string>
#include <map>

#include "CCopasiParameter.h"

template < typename CType > class CVector;

class CProcessReportItem: public CCopasiParameter
  {
    // Operations
  private:
    CProcessReportItem();

  public:
    /**
     * Specific constructor
     * @param const string & name
     * @param const CCopasiParameter::Type & type
     * @param const void * pValue
     * @param const void * pEndValue (default: NULL)
     */
    CProcessReportItem(const std::string & name,
                       const Type & type,
                       const void * pValue,
                       const void * pEndValue = NULL);

    /**
     * Copy Constructor
     * @param const CProcessReportItem & src
     */
    CProcessReportItem(const CProcessReportItem & src);

    /**
     * Destructor
     */
    ~CProcessReportItem();

    /**
     * Retrieve the private end value of the parameter.
     * @return const void * pEndValue
     */
    const void * getEndValue() const;

    /**
     * Retrieve the private end value of the parameter.
     * @return void * pEndValue
     */
    void * getEndValue();

    // Attributes
  private:
    /**
     *  A pointer to the value of the parameter.
     */
    void * mpEndValue;
  };

class CProcessReport
  {
    // Operations
  public:
    /**
     * Default Constructor
     */
    CProcessReport();

    /**
     * Destructor
     */
    virtual ~CProcessReport();

    /**
     * Add a process report item to to the list of reporting items. 
     * The return value is the handle of the item and can be used to 
     * indicate process, finsh, or reset the item. If the method fails
     * C_INVALID_INDEX is returned.
     * @param const std::string & name
     * @param const CCopasiParameter::Type & type
     * @param const void * pValue
     * @param const void * pEndValue = NULL
     * @return unsigned C_INT32 handle
     */
    virtual unsigned C_INT32 addItem(const std::string & name,
                                     const CCopasiParameter::Type & type,
                                     const void * pValue,
                                     const void * pEndValue = NULL);
    /**
     * Report process on item handle. If no handle is given all items will
     * be treated as having changed. If the return value is false the calling 
     * process must halt execution and return.
     * @param const unsigned C_INT32 & handle = C_INVALID_INDEX
     * @param bool continue
     */
    virtual bool progress(const unsigned C_INT32 & handle = C_INVALID_INDEX);

    /**
     * Reset item handle. This means that the value of the item has changed
     * but not as part of a continous process. If you run multiple precesses
     * call reset beween them. If no handle is given all items will
     * be reset. If the return value is false the calling 
     * process must halt execution and return.
     * @param const unsigned C_INT32 & handle = C_INVALID_INDEX
     * @param bool continue
     */
    virtual bool reset(const unsigned C_INT32 & handle = C_INVALID_INDEX);

    /**
     * Indicate that item handle is finished reporting. If no handle is given 
     * all items will be treated as having finshed. The handle of that item is no longer
     * valid after the call. If the return value is false the calling 
     * process must halt execution and return.
     * @param const unsigned C_INT32 & handle = C_INVALID_INDEX
     * @param bool continue
     */
    virtual bool finish(const unsigned C_INT32 & handle = C_INVALID_INDEX);

    /**
     * Check whether the handle is valid, i.e., usable in progress, reset and finish.
     */
    bool isValidHandle(const unsigned C_INT32 handle) const;

    // Attributes
  protected:
    CVector< CProcessReportItem * > mProcessReportItemList;
  };

#endif // COPASI_CProcessReport
