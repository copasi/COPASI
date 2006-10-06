/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/COutputHandlerPlot.cpp,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/10/06 16:03:52 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "COutputHandlerPlot.h"
#include "COutputDefinitionVector.h"
#include "plotwindow.h"

COutputHandlerPlot::COutputHandlerPlot():
    COutputHandler(),
    mpDefinitionVector(NULL)
{}

COutputHandlerPlot::COutputHandlerPlot(const COutputHandlerPlot & src):
    COutputHandler(src),
    mpDefinitionVector(src.mpDefinitionVector)
{}

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
          else if ("Copasi Plot: " + pSpecification->getTitle() !=
                   (const char *)mPlotMap[key]->caption().utf8())
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

void COutputHandlerPlot::removeInterface(COutputInterface * pInterface)
{
  std::map<std::string, PlotWindow*>::iterator it = mPlotMap.begin();
  std::map<std::string, PlotWindow*>::iterator end = mPlotMap.end();

  for (; it != end; ++it)
    if (it->second == pInterface)
      {
        mPlotMap.erase(it);
        return;
      }

  COutputHandler::removeInterface(pInterface);
  return;
}

void COutputHandlerPlot::setOutputDefinitionVector(COutputDefinitionVector * pDefinitionVector)
{mpDefinitionVector = pDefinitionVector;}
