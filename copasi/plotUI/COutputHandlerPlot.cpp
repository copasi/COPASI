/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/COutputHandlerPlot.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/04 21:05:08 $
   End CVS Header */

#include "copasi.h"
#include "COutputHandlerPlot.h"
#include "plot/CPlotSpecVector.h"

//COutputHandlerPlot::COutputHandlerPlot():
//    mpPlotSpecVector(NULL)
//{};

bool COutputHandlerPlot::init()
{
  //std::cout << "OutputHandlerPlot: init" << std::endl;

  //if (!mpPlotSpecVector) return false;
  //datafile.open("datafile", std::ios::in);

  //mpPlotSpecVector->setNumColumns(3);
  //mpPlotSpecVector->setSourceStream(&datafile);
  if (!mpPlotSpecVector) return false;
  return mpPlotSpecVector->initPlottingFromObjects();
  //return true;
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
  /*datafile.open("datafile", std::ios::in);

  mpPlotSpecVector->setNumColumns(3);
  mpPlotSpecVector->setSourceStream(&datafile);
  mpPlotSpecVector->initPlottingFromStream();*/

  //mpPlotSpecVector->doPlotting();

  return mpPlotSpecVector->finishPlotting();

  //return true;
}

void COutputHandlerPlot::setPlotSpecVectorAddress(CPlotSpecVector* ppp)
{mpPlotSpecVector = ppp;}
