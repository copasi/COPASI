/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/COutputHandlerPlot.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/05 16:03:51 $
   End CVS Header */

#include "copasi.h"
#include "COutputHandlerPlot.h"
#include "plot/CPlotSpec2Vector.h"

//COutputHandlerPlot::COutputHandlerPlot():
//    mpPlotSpecVector(NULL)
//{};

bool COutputHandlerPlot::compile(std::vector< CCopasiContainer * > listOfContainer)
{
  if (!mpPlotSpecVector) return false;
  return mpPlotSpecVector->compile(listOfContainer);
}

void COutputHandlerPlot::init()
{if (mpPlotSpecVector) mpPlotSpecVector->initPlotting();}

void COutputHandlerPlot::doOutput()
{if (mpPlotSpecVector) mpPlotSpecVector->doPlotting();}

void COutputHandlerPlot::finish()
{if (mpPlotSpecVector) mpPlotSpecVector->finishPlotting();}

void COutputHandlerPlot::doSeparator()
{if (mpPlotSpecVector) mpPlotSpecVector->doSeparator();}

void COutputHandlerPlot::setPlotSpecVectorAddress(CPlotSpec2Vector* ppp)
{mpPlotSpecVector = ppp;}
