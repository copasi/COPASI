/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CPlotSpecVector.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/13 13:28:18 $
   End CVS Header */

#include "copasi.h"
#include "CPlotSpecVector.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiObjectReference.h"
#include "model/CModel.h" 
//#include "CPlotSpec.h"
#include "plotwindow.h"
#include "utilities/CGlobals.h"

CPlotSpecVector::CPlotSpecVector(const std::string & name,
                                 const CCopasiContainer * pParent):
    CCopasiVectorN< CPlotSpec >(name, pParent),
    mKey(GlobalKeys.add("CPlotSpecVector", this)),
    pSource(NULL),
    //ncols(0),
    mReport(),
    mRepDef(),
    inputFlag(NO_INPUT)
{
  mReport.setReportDefinition(&mRepDef);
  //createDebugReport(); //for debugging only
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
    if ((*this)[i]->getObjectName() == name)
      return false; // duplicate name

  CPlotSpec* pNewPlotSpec = new CPlotSpec(name, this);
  //pNewPlotSpec->setComment(comment);
  pNewPlotSpec->setObjectName(name);

  add(pNewPlotSpec);
  return true;
}

bool CPlotSpecVector::initPlottingFromObjects()
{
  //  createDebugReport(); //for debugging only
  inputFlag = NO_INPUT;

  if (size() == 0)
    {
      std::cout << "plot: not plots defined" << std::endl;
      return false;
    }

  if (!compile()) //create mObjects;
    {
      std::cout << "plot: compile not successful" << std::endl;
      return false;
    }

  //ncols = mObjectNames.size();
  if (mObjectNames.size() <= 0)
    {
      std::cout << "plot: number of objects <=0" << std::endl;
      return false;
    }
  data.resize(mObjectNames.size());

  inputFlag = FROM_OBJECTS;

  return initAllPlots();

  //return success;
}

bool CPlotSpecVector::sendDataToAllPlots()
{
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
  std::vector<PlotWindow*>::iterator winit;
  windows.resize(size());
  for (it = begin(), winit = windows.begin(); it != end(); ++it, ++winit)
    {
      if (*winit)
      {(*winit)->initFromSpec(*it);}
      else
        {
          pTemp = new PlotWindow(*it);
          *winit = pTemp;
          //pTemp->resize(600, 360);
        }
      (*winit)->show();
    }
  return true;
}

bool CPlotSpecVector::doPlotting()
{
  bool success = true;

  if (inputFlag == FROM_OBJECTS)
    {
      unsigned C_INT32 i = 0;
      std::vector<CCopasiObject*>::const_iterator it = mObjects.begin();
      for (; it != mObjects.end(); ++it, ++i)
        {
          data[i] = *(C_FLOAT64*)(((CCopasiObjectReference<C_FLOAT64>*)(*it))->getReference());
          //std::cout << "debug1: " <<  *(C_FLOAT64*)(((CCopasiObjectReference<C_FLOAT64>*)(*it))->getReference())<< std::endl;
          //std::cout << "debug2: " <<   data[i] << std::endl;
          //(*it)->print(&std::cout);
        }
      sendDataToAllPlots();
    }
  else if (inputFlag == FROM_STREAM)
    {
      /*pSource->seekg(position);

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

      position = pSource->tellg();*/
    }
  else
    {
      std::cout << "doPlotting: no input method" << std::endl;
      return false;
    }

  //updateAllPlots();

  return success;
}

bool CPlotSpecVector::finishPlotting()
{
  return updateAllPlots();
}

C_INT32 CPlotSpecVector::getIndexFromCN(const CCopasiObjectName & name)
{
  //first look up the name in the vector
  std::vector<CCopasiObjectName>::const_iterator it;
  for (it = mObjectNames.begin(); it != mObjectNames.end(); ++it)
    if (*it == name) break;

  if (it != mObjectNames.end()) return (it - mObjectNames.begin());

  //the name is not yet in the list
  mObjectNames.push_back(name);
  return mObjectNames.size() - 1;
}

bool CPlotSpecVector::compile()
{
  //construct the mObjectNames and the indices
  CCopasiVectorN<CPlotSpec>::iterator psit;
  for (psit = begin(); psit != end(); ++psit)
    (*psit)->compile(this);

  bool success = true;

  mObjects.clear();

  std::vector< CCopasiContainer * > ListOfContainer;
  CCopasiObject* pSelected;

  std::vector<CCopasiObjectName>::const_iterator it = mObjectNames.begin();
  for (; it != mObjectNames.end(); ++it)
    {
      std::cout << "CPlotSpecVector::compile  " << *it << std::endl;

      pSelected = CCopasiContainer::ObjectFromName(ListOfContainer, *it);
      if (!pSelected)
        {
          std::cout << "Object not found!" << std::endl;
          return false;
        }

      //add(pSelected); //what's this?

      //TODO check hasValue()

      std::cout << "    compile: " << pSelected->getObjectName() << std::endl;

      mObjects.push_back(pSelected);
    }

  return success;
}

/*void CPlotSpecVector::createDebugReport()
{
  std::cout << "Create Debug Report for Plot" << std::endl;
 
  mObjectNames.clear();
 
  //std::cout << Copasi->pModel->getObject(CCopasiObjectName("Reference=Time"))->getCN() << std::endl;
  CCopasiObjectName name = Copasi->pModel->getObject(CCopasiObjectName("Reference=Time"))->getCN();
  std::cout << name << std::endl;
  mObjectNames.push_back(name);
 
  name = Copasi->pModel->getMetabolites()[0]->getObject(CCopasiObjectName("Reference=Concentration"))->getCN();
  std::cout << name << std::endl;
  mObjectNames.push_back(name);
 
  //mRepDef.getBodyAddr()->clear();
  //mRepDef.getBodyAddr()->push_bMck(name);
  //mReport.compile();
}*/
