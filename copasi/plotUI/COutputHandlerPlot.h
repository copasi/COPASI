/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/COutputHandlerPlot.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/05 16:03:51 $
   End CVS Header */

#ifndef OUTPUT_HANDLER_PLOT
#define OUTPUT_HANDLER_PLOT

#include <vector>

#include "utilities/COutputHandler.h"

class CPlotSpec2Vector;
class CCopasiContainer;

/**
 *  This is used to call the plotting routines from the tasks
 *  We do not want to call gui stuff directly from the trajectory task. 
 */
class COutputHandlerPlot : public CCallbackHandler
  {
  public:
    //   COutputHandlerPlot();
    virtual ~COutputHandlerPlot() {};

    /**
     * compile the object list from name vector
     * @param std::vector< CCopasiContainer * > listOfContainer
     * (default: CCopasiContainer::EmptyList)
     * @return bool success
     */
    virtual bool compile(std::vector< CCopasiContainer * > listOfContainer =
                           std::vector< CCopasiContainer * >());

    void takeData();
    virtual void init();
    virtual void doOutput();
    virtual void finish();

    virtual void doSeparator();

    void setPlotSpecVectorAddress(CPlotSpec2Vector* ppp);

  private:
    CPlotSpec2Vector * mpPlotSpecVector;

    //for testing only
    std::ifstream datafile;
  };

#endif
