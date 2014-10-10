// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QtCore/QThread>

#include "UI/copasiui3window.h"

#include "copasi.h"

#include "COutputHandlerPlot.h"
#include "plot/COutputDefinitionVector.h"
#include "plotwindow.h"
#include "copasi/UI/qtUtilities.h"
#include "copasi/report/CCopasiRootContainer.h"

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

bool COutputHandlerPlot::compile(CObjectInterface::ContainerList listOfContainer)
{
  if (!mpDefinitionVector) return false;

  // This must only be executed in the main thread.
  if (CopasiUI3Window::isMainThread())
    {
      mInterfaces.clear();

      //step through the vector of specifications and create the plot windows
      std::string key;

      size_t i, imax = mpDefinitionVector->size();

      for (i = 0; i < imax; i++)
        {
          CPlotSpecification * pSpecification = (*mpDefinitionVector)[i];

          if (pSpecification->isActive())
            {
              key = pSpecification->CCopasiParameter::getKey();

              if (!mPlotMap.count(key))
                mPlotMap[key] = new PlotWindow(this, pSpecification, CopasiUI3Window::getMainWindow());
              else if ("COPASI Plot: " + pSpecification->getTitle() !=
                       TO_UTF8(mPlotMap[key]->windowTitle()))
                mPlotMap[key] = new PlotWindow(this, pSpecification, CopasiUI3Window::getMainWindow());
              else
                mPlotMap[key]->initFromSpec(pSpecification);

              mPlotMap[key]->show();

              mInterfaces.insert(mPlotMap[key]);
            }
        }
    }

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  return COutputHandler::compile(listOfContainer);
}

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
