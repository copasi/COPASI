/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CPlotSpec2Vector.cpp,v $
   $Revision: 1.15 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/02 11:52:02 $
   End CVS Header */

#include <limits>

#include "copasi.h"
#include "CPlotSpec2Vector.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiObjectReference.h"
#include "utilities/CCopasiVector.h"
#include "model/CModel.h"
#include "plotwindow.h"

CPlotSpec2Vector::CPlotSpec2Vector(const std::string & name):
    CCopasiObject(name),
    //    CCopasiVectorN<CPlotSpecification>(name, pParent),
    //    mKey(GlobalKeys.add("CPlotSpecificationVector", this)),
    mpPlotDefinitionList(NULL),
    inputFlag(NO_INPUT)
{}

CPlotSpec2Vector::~CPlotSpec2Vector()
{
  cleanup();
}

void CPlotSpec2Vector::cleanup()
{/*GlobalKeys.remove(mKey);*/}

bool CPlotSpec2Vector::setPlotDefinitionList(COutputDefinitionVector * pPlotDefinitionList)
{
  mpPlotDefinitionList = pPlotDefinitionList;
  return true;
}

CCopasiVectorN< CPlotSpecification> * CPlotSpec2Vector::getPlotDefintionList()
{return mpPlotDefinitionList;}

bool CPlotSpec2Vector::initPlottingFromObjects()
{
  inputFlag = NO_INPUT;

  if (!mpPlotDefinitionList || mpPlotDefinitionList->size() == 0)
    {
      std::cout << "plot: not plots defined" << std::endl;
      return false;
    }

  mObjectNames.clear();

  if (!initAllPlots()) //create mObjectNames;
    {
      std::cout << "plot: problem while creating indices" << std::endl;
      return false;
    }

  if (mObjectNames.size() <= 0)
    {
      std::cout << "plot: number of objects <=0" << std::endl;
      return false;
    }
  data.resize(mObjectNames.size());

  inputFlag = FROM_OBJECTS;

  mTime = CCopasiTimeVariable::getCurrentWallTime();

  return compile(); //create mObjects
}

bool CPlotSpec2Vector::sendDataToAllPlots()
{
  std::vector<PlotWindow*>::const_iterator it;
  for (it = windows.begin(); it != windows.end(); ++it)
    {
      (*it)->takeData(data);
    }

  return true;
}

bool CPlotSpec2Vector::updateAllPlots()
{
  std::vector<PlotWindow*>::const_iterator it;
  for (it = windows.begin(); it != windows.end(); ++it)
    {
      (*it)->updatePlot();
    }

  return true;
}

bool CPlotSpec2Vector::initAllPlots()
{
  if (!mpPlotDefinitionList) return false;

  windows.clear();

  //step through the vector of specifications and create the plot windows
  std::string key;

  unsigned C_INT32 i, imax = mpPlotDefinitionList->size();

  for (i = 0; i < imax; i++)
    {
      if ((*mpPlotDefinitionList)[i]->isActive())
        {
          key = (*mpPlotDefinitionList)[i]->CCopasiParameter::getKey();
          std::cout << key << std::endl;

          if (windowMap[key] == NULL)
            {
              windowMap[key] = new PlotWindow(this, (*mpPlotDefinitionList)[i]);
            }
          else
            {
              windowMap[key]->initFromSpec(this, (*mpPlotDefinitionList)[i]);
            }
          windowMap[key]->show();

          windows.push_back(windowMap[key]);
        }
    }
  return true;
}

bool CPlotSpec2Vector::doPlotting()
{
  bool success = true;

  if (inputFlag == FROM_OBJECTS)
    {
      unsigned C_INT32 i = 0;
      std::vector<CCopasiObject*>::const_iterator it = mObjects.begin();
      for (; it != mObjects.end(); ++it, ++i)
        {
          if (*it)
            data[i] = *(C_FLOAT64*)(((CCopasiObjectReference<C_FLOAT64>*)(*it))->getReference());
          else
            data[i] = 0;
          //std::cout << "debug1: " <<  *(C_FLOAT64*)(((CCopasiObjectReference<C_FLOAT64>*)(*it))->getReference())<< std::endl;
          //std::cout << "debug2: " <<   data[i] << std::endl;
          //(*it)->print(&std::cout);
        }
      sendDataToAllPlots();
    }
  else
    {
      //std::cout << "doPlotting: no input method" << std::endl;
      return false;
    }

  /*  if (mTime + LLONG_CONST(200000) < CCopasiTimeVariable::getCurrentWallTime())
      {
        updateAllPlots();
        mTime = CCopasiTimeVariable::getCurrentWallTime();
      }*/
  if (mTime + LLONG_CONST(200000) < CCopasiTimeVariable::getCurrentWallTime())
    {
      CCopasiTimeVariable oldTime = CCopasiTimeVariable::getCurrentWallTime();
      updateAllPlots();
      mTime = CCopasiTimeVariable::getCurrentWallTime();
      CCopasiTimeVariable timeDiff = mTime - oldTime;
      //std::cout << timeDiff.getMicroSeconds() << std::endl;
      mTime = mTime + timeDiff + timeDiff + timeDiff;
    }

  return success;
}

bool CPlotSpec2Vector::doPlottingSeparator()
{
  unsigned C_INT32 i = 0;
  std::vector<CCopasiObject*>::const_iterator it = mObjects.begin();
  for (; it != mObjects.end(); ++it, ++i)
    {
      data[i] = std::numeric_limits<C_FLOAT64>::quiet_NaN(); //0/0;
    }
  sendDataToAllPlots();
  return true;
}

bool CPlotSpec2Vector::finishPlotting()
{
  return updateAllPlots();
}

C_INT32 CPlotSpec2Vector::getIndexFromCN(const CCopasiObjectName & name)
{
  //first look up the name in the vector
  std::vector<CCopasiObjectName>::const_iterator it;
  for (it = mObjectNames.begin(); it != mObjectNames.end(); ++it)
    if (*it == name) break;

  if (it != mObjectNames.end())
    {
      //std::cout << "CPlotSpec2Vector::getIndexFromCN; existing object: " << name << std::endl;
      return (it - mObjectNames.begin());
    }

  //the name is not yet in the list
  mObjectNames.push_back(name);
  //std::cout << "CPlotSpec2Vector::getIndexFromCN; new object: " << name << std::endl;
  return mObjectNames.size() - 1;
}

bool CPlotSpec2Vector::compile()
{
  mObjects.clear();

  CCopasiObject* pSelected;

  std::vector<CCopasiObjectName>::const_iterator it;
  for (it = mObjectNames.begin(); it != mObjectNames.end(); ++it)
    {
      //std::cout << "CPlotSpecVector::compile  " << *it << std::endl;
      pSelected = CCopasiContainer::ObjectFromName(*it);
      if (!pSelected)
        {
          std::cout << "Object not found!" << std::endl;
          mObjects.push_back(NULL);
          //return false;
        }
      else
        {
          //TODO check hasValue()
          //std::cout << "    compile: " << pSelected->getObjectName() << std::endl;
          mObjects.push_back(pSelected);
        }
    }
  return true; //success;
}
