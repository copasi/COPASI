/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/COutputHandlerPlot.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/08/05 12:54:10 $
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
