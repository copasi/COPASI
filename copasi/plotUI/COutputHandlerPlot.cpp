/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/COutputHandlerPlot.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:59 $
   End CVS Header */

#include "copasi.h"
#include "COutputHandlerPlot.h"
#include "plot/CPlotSpec2Vector.h"

//COutputHandlerPlot::COutputHandlerPlot():
//    mpPlotSpecVector(NULL)
//{};

bool COutputHandlerPlot::init()
{
  if (!mpPlotSpecVector) return false;
  return mpPlotSpecVector->initPlottingFromObjects();
}

bool COutputHandlerPlot::doOutput()
{
  //std::cout << "OutputHandlerPlot: do" << std::endl;
  if (!mpPlotSpecVector) return false;
  return mpPlotSpecVector->doPlotting();
  //return true;
}

bool COutputHandlerPlot::finish()
{
  //std::cout << "OutputHandlerPlot: finish" << std::endl;
  if (!mpPlotSpecVector) return false;

  return mpPlotSpecVector->finishPlotting();
}

void COutputHandlerPlot::setPlotSpecVectorAddress(CPlotSpec2Vector* ppp)
{mpPlotSpecVector = ppp;}
