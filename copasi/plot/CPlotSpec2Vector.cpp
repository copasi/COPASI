/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CPlotSpec2Vector.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/10/09 14:42:38 $
   End CVS Header */

#include "copasi.h"
#include "CPlotSpec2Vector.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiObjectReference.h"
#include "model/CModel.h"
#include "plotwindow.h"
#include "utilities/CGlobals.h"

CPlotSpec2Vector::CPlotSpec2Vector(const std::string & name,
                                   const CCopasiContainer * pParent):
    CCopasiVectorN<CPlotSpecification>(name, pParent),
    mKey(GlobalKeys.add("CPlotSpecificationVector", this)),
    inputFlag(NO_INPUT)
{}

CPlotSpec2Vector::~CPlotSpec2Vector()
{
  cleanup();
}

void CPlotSpec2Vector::cleanup()
{
  GlobalKeys.remove(mKey);
}

const std::string& CPlotSpec2Vector::getKey()
{
  return mKey;
}

CPlotSpecification* CPlotSpec2Vector::createPlotSpec(const std::string & name,
    CPlotItem::Type type)
{
  unsigned C_INT32 i;
  for (i = 0; i < size(); i++)
    if ((*this)[i]->getObjectName() == name)
      return NULL; // duplicate name

  CPlotSpecification* pNewPlotSpec = new CPlotSpecification(name, this, type);
  pNewPlotSpec->setObjectName(name);

  add(pNewPlotSpec);
  return pNewPlotSpec;
}

bool CPlotSpec2Vector::removePlotSpec(const std::string & key)
{
  CPlotSpecification* pPl =
    dynamic_cast<CPlotSpecification*>(GlobalKeys.get(key));
  unsigned C_INT32 index = this->CCopasiVector<CPlotSpecification>::getIndex(pPl);
  if (index == C_INVALID_INDEX)
    return false;

  this->CCopasiVector<CPlotSpecification>::remove(index);

  return true;
}

bool CPlotSpec2Vector::initPlottingFromObjects()
{
  inputFlag = NO_INPUT;

  if (size() == 0)
    {
      std::cout << "plot: not plots defined" << std::endl;
      return false;
    }

  mObjectNames.resize(0);

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

  mTime.init();

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
  windows.resize(0);

  //step through the vector of specifications and create the plot windows
  std::string key;
  const_iterator it;
  for (it = begin(); it != end(); ++it)
    {
      if ((*it)->isActive())
        {
          key = (*it)->CCopasiParameter::getKey();
          std::cout << key << std::endl;

          if (windowMap[key] == NULL)
            {
              windowMap[key] = new PlotWindow(this, *it);
            }
          else
            {
              windowMap[key]->initFromSpec(this, *it);
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

  if (mTime.getTimeDiff() > 200)
    {
      updateAllPlots();
      mTime.init();
    }

  return success;
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

  if (it != mObjectNames.end()) return (it - mObjectNames.begin());

  //the name is not yet in the list
  mObjectNames.push_back(name);
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
          //std::cout << "Object not found!" << std::endl;
          mObjects.push_back(NULL);
          //return false;
        }
      //TODO check hasValue()
      //std::cout << "    compile: " << pSelected->getObjectName() << std::endl;
      mObjects.push_back(pSelected);
    }
  return true; //success;
}
