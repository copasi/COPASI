/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/COutputHandlerPlot.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/27 20:09:01 $
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

bool COutputHandlerPlot::doSeparator()
{
  if (!mpPlotSpecVector) return false;
  return mpPlotSpecVector->doPlottingSeparator();
}

void COutputHandlerPlot::setPlotSpecVectorAddress(CPlotSpec2Vector* ppp)
{mpPlotSpecVector = ppp;}
