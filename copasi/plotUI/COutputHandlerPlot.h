/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/COutputHandlerPlot.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:59 $
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

    void setPlotSpecVectorAddress(CPlotSpec2Vector* ppp);

  private:
    CPlotSpec2Vector * mpPlotSpecVector;

    //for testing only
    std::ifstream datafile;
  };

#endif
