/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CProgressBar.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:46 $
   End CVS Header */

#if !defined HANDLER_PROGRESS_BAR
#define HANDLER_PROGRESS_BAR

#include "utilities/COutputHandler.h"
class QProgressDialog;
class DataModelGUI;

/**
 *  This is used to call the progress bar code
 *  We do not want to call gui stuff directly from the CModel. 
 */
class CProgressBar : public CCallbackHandler
  {
  public:
    CProgressBar(DataModelGUI* dm);
    virtual ~CProgressBar() {};

    virtual bool init(C_INT32 maxSteps, const std::string & text, bool cancelButton = false);
    virtual bool reInit(C_INT32 maxSteps, const std::string & text);
    virtual bool progress(C_INT32 steps);
    virtual bool finish();

  private:
    QProgressDialog * mpWidget;
    C_INT32 mProgress;
    DataModelGUI* mDataModel;
  };

#endif
