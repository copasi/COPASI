/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/COutputHandler.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/05 16:03:52 $
   End CVS Header */

#ifndef OUTPUT_HANDLER
#define OUTPUT_HANDLER

#include <vector>

class CCopasiContainer;

/**
 *  This is just a wrapper class that is used to call the plotting classes.
 *  We do not want to call gui stuff directly from the trajectory task. 
 */
class CCallbackHandler
  {
  public:

    virtual ~CCallbackHandler() {};

    /**
     * compile the object list from name vector
     * @param std::vector< CCopasiContainer * > listOfContainer
     * (default: CCopasiContainer::EmptyList)
     * @return bool success
     */
    virtual bool compile(std::vector< CCopasiContainer * > listOfContainer =
                           std::vector< CCopasiContainer * >());

    //for output handler
    virtual void init();
    virtual void doOutput();
    virtual void finish();

    virtual void doSeparator();
  };

#endif
