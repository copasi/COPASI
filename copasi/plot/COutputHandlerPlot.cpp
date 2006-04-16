/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/COutputHandlerPlot.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/16 17:43:46 $
   End CVS Header */

#include "copasi.h"

#include "COutputHandlerPlot.h"
#include "COutputDefinitionVector.h"
#include "PlotWindow.h"

//COutputHandlerPlot::COutputHandlerPlot():
//    mpPlotSpecVector(NULL)
//{};

COutputHandlerPlot::~COutputHandlerPlot()
{}

bool COutputHandlerPlot::compile(std::vector< CCopasiContainer * > listOfContainer)
{
  if (!mpDefinitionVector) return false;

  mInterfaces.clear();

  //step through the vector of specifications and create the plot windows
  std::string key;

  unsigned C_INT32 i, imax = mpDefinitionVector->size();

  for (i = 0; i < imax; i++)
    {
      CPlotSpecification * pSpecification = (*mpDefinitionVector)[i];

      if (pSpecification->isActive())
        {
          key = pSpecification->CCopasiParameter::getKey();
          //std::cout << key << std::endl;

          if (!mPlotMap.count(key))
            mPlotMap[key] = new PlotWindow(this, pSpecification);
          else
            mPlotMap[key]->initFromSpec(pSpecification);

          mPlotMap[key]->show();

          mInterfaces.insert(mPlotMap[key]);
        }
    }

  return COutputHandler::compile(listOfContainer);
}

#ifdef XXXX
void COutputHandlerPlot::init()
{if (mpPlotSpecVector) mpPlotSpecVector->initPlotting();}

void COutputHandlerPlot::doOutput()
{if (mpPlotSpecVector) mpPlotSpecVector->doPlotting();}

void COutputHandlerPlot::finish()
{if (mpPlotSpecVector) mpPlotSpecVector->finishPlotting();}

void COutputHandlerPlot::doSeparator()
{if (mpPlotSpecVector) mpPlotSpecVector->doSeparator();}
#endif // XXXX

void COutputHandlerPlot::setOutputDefinitionVector(COutputDefinitionVector * pDefinitionVector)
{mpDefinitionVector = pDefinitionVector;}
