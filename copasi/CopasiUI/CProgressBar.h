/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CProgressBar.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/25 18:13:22 $
   End CVS Header */

#if !defined HANDLER_PROGRESS_BAR
#define HANDLER_PROGRESS_BAR

#include "utilities/CProcessReport.h"
#include "CQProgressDialog.h"

template < typename > class CVector;
class CQProgressItem;

/**
 *  This is used to call the progress bar code
 *  We do not want to call gui stuff directly from the CModel. 
 */
class CProgressBar : public CProcessReport, public CQProgressDialog
  {
  public:
    CProgressBar(QWidget* parent = 0,
                 const char* name = 0,
                 bool modal = FALSE,
                 WFlags fl = 0);

    virtual ~CProgressBar();

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
     * Report process on item handle. If the return value is false the calling 
     * process must halt execution and return.
     * @param const unsigned C_INT32 & handle
     * @param bool continue
     */
    virtual bool progress(const unsigned C_INT32 & handle);

    /**
     * Check whether processing shall proceed. If the return value is false 
     * the calling process must halt execution and return. This method is 
     * provided so that lenghty processing without advances in any of the 
     * reporting items can check whether continuation is requested.
     * @param bool continue
     */
    virtual bool proceed();

    /**
     * Reset item handle. This means that the value of the item has changed
     * but not as part of a continous process. If you run multiple processes
     * call reset beween them. If the return value is false the calling 
     * process must halt execution and return.
     * @param const unsigned C_INT32 & handle
     * @param bool continue
     */
    virtual bool reset(const unsigned C_INT32 & handle);

    /**
     * Indicate that all items are finished reporting. All item handles loose
     * their validity. If the return value is false the calling 
     * process must halt execution and return.
     * @param bool continue
     */
    virtual bool finish();

    /**
     * Indicate that item handle is finished reporting. The handle of that 
     * item is no longer valid after the call. If the return value is false 
     * the calling process must halt execution and return.
     * @param const unsigned C_INT32 & handle
     * @param bool continue
     */
    virtual bool finish(const unsigned C_INT32 & handle);

    /**
     * Set the name of the process.
     * @param const std::string & name
     * @return sucess
     */
    virtual bool setName(const std::string & name);

  private:
    CVector< CQProgressItem * > mProgressItemList;
  };

#endif
