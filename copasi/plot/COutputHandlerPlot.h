/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/COutputHandlerPlot.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/27 20:09:01 $
   End CVS Header */

#if !defined OUTPUT_HANDLER_PLOT
#define OUTPUT_HANDLER_PLOT

#include "utilities/COutputHandler.h"

class CPlotSpec2Vector;

/**
 *  This is used to call the plotting routines from the tasks
 *  We do not want to call gui stuff directly from the trajectory task. 
 */
class COutputHandlerPlot : public CCallbackHandler
  {
  public:
    //   COutputHandlerPlot();
    virtual ~COutputHandlerPlot() {};

    virtual bool init();
    virtual bool doOutput();
    virtual bool finish();

    virtual bool doSeparator();

    void setPlotSpecVectorAddress(CPlotSpec2Vector* ppp);

  private:
    CPlotSpec2Vector * mpPlotSpecVector;

    //for testing only
    std::ifstream datafile;
  };

#endif
