/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/COutputHandlerPlot.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/04/06 14:56:46 $
   End CVS Header */

#if !defined OUTPUT_HANDLER_PLOT
#define OUTPUT_HANDLER_PLOT

#include "utilities/COutputHandler.h"

class CPlotSpecVector;

/**
 *  This is used to call the plotting routines from the tasks
 *  We do not want to call gui stuff directly from the trajectory task. 
 */
class COutputHandlerPlot : public COutputHandler
  {
  public:
    //   COutputHandlerPlot();

    virtual bool init();
    virtual bool doOutput();
    virtual bool finish();

    void setPlotSpecVectorAddress(CPlotSpecVector* ppp);

  private:
    CPlotSpecVector * mpPlotSpecVector;

    //for testing only
    std::ifstream datafile;
  };

#endif
