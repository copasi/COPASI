/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CPlotSpecVector.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/04/26 15:26:04 $
   End CVS Header */

#include "copasi.h"
#include "CPlotSpecVector.h"
#include "report/CKeyFactory.h"
#include "model/CModel.h"
#include "CPlotSpec.h"
#include "plotwindow.h"
#include "utilities/CGlobals.h"

CPlotSpecVector::CPlotSpecVector(const std::string & name,
                                 const CCopasiContainer * pParent):
    CCopasiVectorN< CPlotSpec >(name, pParent),
    mKey(GlobalKeys.add("CPlotSpecVector", this)),
    pSource(NULL),
    ncols(0),
    mReport(),
    mRepDef(),
    inputFlag(NO_INPUT)
{
  mReport.setReportDefinition(&mRepDef);
  createDebugReport(); //for debugging only
}

CPlotSpecVector::~CPlotSpecVector()
{
  cleanup();
}

void CPlotSpecVector::cleanup()
{
  GlobalKeys.remove(mKey);
}

const std::string& CPlotSpecVector::getKey()
{
  return mKey;
}

bool CPlotSpecVector::addNewPlotSpec(const std::string name /*, const std::string comment*/)
{
  unsigned C_INT32 i;
  for (i = 0; i < size(); i++)
    if ((*this)[i]->getName() == name)
      return false; // duplicate name

  CPlotSpec* pNewPlotSpec = new CPlotSpec(name, this);
  //pNewPlotSpec->setComment(comment);
  pNewPlotSpec->setObjectName(name);

  add(pNewPlotSpec);
  return true;
}

bool CPlotSpecVector::initPlottingFromStream()
{
  bool success = true;
  inputFlag = NO_INPUT;

  if (size() == 0)
    {
      std::cout << "plot: not plots defined" << std::endl;
      return false;
    }

  if (ncols <= 0)
    {
      std::cout << "plot: ncols <=0" << std::endl;
      return false;
    }
  data.resize(ncols);

  if (!pSource)
    {
      std::cout << "plot: no input stream" << std::endl;
      return false;
    }
  if (!(*pSource))
    {
      std::cout << "plot: input stream not open" << std::endl;
      return false;
    }
  pSource->seekg(0, std::ios::beg);
  position = pSource->tellg();
  inputFlag = FROM_STREAM;

  initAllPlots();

  return success;
}

bool CPlotSpecVector::sendDataToAllPlots()
{
  //C_INT32 i;
  //std::cout << "debug: ";
  //for (i=0; i<ncols; ++i)
  //  {
  //    std::cout << data[i] << "  ";
  //}
  //std::cout << std::endl;

  std::vector<PlotWindow*>::const_iterator it;
  for (it = windows.begin(); it != windows.end(); ++it)
    {
      (*it)->takeData(data);
    }

  return true;
}
bool CPlotSpecVector::updateAllPlots()
{
  std::vector<PlotWindow*>::const_iterator it;
  for (it = windows.begin(); it != windows.end(); ++it)
    {
      (*it)->updatePlot();
    }

  return true;
}

bool CPlotSpecVector::initAllPlots()
{
  //step through the vector of specifications and create the plot windows
  PlotWindow* pTemp;
  const_iterator it;
  for (it = begin(); it != end(); ++it)
    {
      pTemp = new PlotWindow(*it);
      windows.push_back(pTemp);
      //pTemp->resize(600, 360);
      pTemp->show();
    }
  return true;
}

bool CPlotSpecVector::doPlotting()
{
  bool success = true;
  if (!inputFlag == FROM_STREAM)
    {
      std::cout << "doPlotting: no input stream" << std::endl;
      return false;
    }

  pSource->seekg(position);

  C_INT32 i;

  while (!(pSource->eof()))
    {
      for (i = 0; i < ncols; ++i)
        {
          if (!(*pSource >> data[i])) break;
        }
      if (i == ncols) //line was read completely
        sendDataToAllPlots();
    };

  position = pSource->tellg();

  updateAllPlots();

  return success;
}

void CPlotSpecVector::createDebugReport()
{
  std::cout << "Create Debug Report for Plot" << std::endl;

  mRepDef.getBodyAddr()->clear();

  //std::cout << Copasi->pModel->getObject(CCopasiObjectName("Reference=Time"))->getCN() << std::endl;
  CCopasiObjectName name = Copasi->pModel->getObject(CCopasiObjectName("Reference=Time"))->getCN();
  std::cout << name << std::endl;

  mRepDef.getBodyAddr()->push_back(name);

  mReport.compile();
}
