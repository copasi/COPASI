/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/COutputHandlerPlot.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/04/26 15:26:03 $
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

  if (!mpPlotSpecVector) return false;
  datafile.open("datafile", std::ios::in);

  mpPlotSpecVector->setNumColumns(3);
  mpPlotSpecVector->setSourceStream(&datafile);
  mpPlotSpecVector->initPlottingFromStream();

  return true;
}

bool COutputHandlerPlot::doOutput()
{
  //std::cout << "OutputHandlerPlot: do" << std::endl;
  return true;
}

bool COutputHandlerPlot::finish()
{
  //std::cout << "OutputHandlerPlot: finish" << std::endl;
  if (!mpPlotSpecVector) return false;
  /*datafile.open("datafile", std::ios::in);
      
  mpPlotSpecVector->setNumColumns(3);
  mpPlotSpecVector->setSourceStream(&datafile);*/ 
  //mpPlotSpecVector->initPlottingFromStream();

  mpPlotSpecVector->doPlotting();

  return true;
}

void COutputHandlerPlot::setPlotSpecVectorAddress(CPlotSpecVector* ppp)
{mpPlotSpecVector = ppp;}
