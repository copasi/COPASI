/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/COutputHandler.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/04/06 15:01:18 $
   End CVS Header */

#if !defined OUTPUT_HANDLER
#define OUTPUT_HANDLER

/**
 *  This is just a wrapper class that is used to call the plotting classes.
 *  We do not want to call gui stuff directly from the trajectory task. 
 */
class COutputHandler
  {
  public:
    virtual bool init();
    virtual bool doOutput();
    virtual bool finish();
  };

#endif
