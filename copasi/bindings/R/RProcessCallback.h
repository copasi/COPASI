#ifndef RProcessCallback_H
#define RProcessCallback_H

#include <copasi/utilities/CProcessReport.h>

/**
 * Utility class that calls back to the R API 
 * to figure out whether the current operation 
 * needs to be canceled
 */
class RProcessCallback : public CProcessReport
{
  public: 
    /** 
     * constructor with optional maximum runtime
     * 
     * @param maxTime maximum time after which the task
     *        will be stopped (0 = disabled)
     */
    RProcessCallback(const unsigned int & maxTime = 0);
    
    /** 
     * destructor
     */
    virtual ~RProcessCallback();
    
    /**
     * Report process on all items. If the return value is false the calling
     * process must halt execution and return.
     * @return boolean indicating whether the task should continue or not
     */
    virtual bool progress();
    
    /**
     * Report process on item handle. If the return value is false the calling
     * process must halt execution and return.
     * @param const size_t & handle
     * @return boolean indicating whether the task should continue or not
     */
    virtual bool progressItem(const size_t & handle);
    
    /**
     * Check whether processing shall proceed. If the return value is false
     * the calling process must halt execution and return. This method is
     * provided so that lengthy processing without advances in any of the
     * reporting items can check whether continuation is requested.
     *
     * @return boolean indicating whether the task should continue or not
     */
    virtual bool proceed();
    
    /**
     * Reset all item handle. This means that the values of the items have changed
     * but not as part of a continuous process. If you run multiple processes
     * call reset between them. If the return value is false the calling
     * process must halt execution and return.
     * 
     * @return boolean indicating whether the task should continue or not
     */
    virtual bool reset();
    
    /**
     * Indicate that all items are finished reporting. All item handles loose
     * their validity. If the return value is false the calling
     * process must halt execution and return.
     *
     * @return boolean indicating whether the task should continue or not
     */
    virtual bool finish();
  
};

#endif // RProcessCallback_H
