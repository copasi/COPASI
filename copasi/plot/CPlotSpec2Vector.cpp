/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CPlotSpec2Vector.cpp,v $
   $Revision: 1.20 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/05 16:03:51 $
   End CVS Header */

#include <limits>

#include "copasi.h"
#include "CPlotSpec2Vector.h"
#include "report/CKeyFactory.h"
#include "report/CCopasiObjectReference.h"
#include "report/CCopasiTimer.h"
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

CCopasiVectorN< CPlotSpecification> * CPlotSpec2Vector::getPlotDefinitionList()
{return mpPlotDefinitionList;}

void CPlotSpec2Vector::initPlotting()
{
  std::vector<PlotWindow*>::const_iterator it = mActivePlots.begin();
  std::vector<PlotWindow*>::const_iterator end = mActivePlots.end();

  for (; it != end; ++it)
    (*it)->initPlot();

  return;
}

void CPlotSpec2Vector::sendDataToAllPlots()
{
  std::vector<PlotWindow*>::const_iterator it = mActivePlots.begin();
  std::vector<PlotWindow*>::const_iterator end = mActivePlots.end();

  for (; it != end; ++it)
    (*it)->takeData();

  return;
}

void CPlotSpec2Vector::updateAllPlots()
{
  std::vector<PlotWindow*>::const_iterator it = mActivePlots.begin();
  std::vector<PlotWindow*>::const_iterator end = mActivePlots.end();

  for (; it != end; ++it)
    (*it)->updatePlot();

  return;
}

void CPlotSpec2Vector::finishAllPlots()
{
  std::vector<PlotWindow*>::const_iterator it = mActivePlots.begin();
  std::vector<PlotWindow*>::const_iterator end = mActivePlots.end();

  for (; it != end; ++it)
    (*it)->finishPlot();

  return;
}

bool CPlotSpec2Vector::initAllPlots()
{
  if (!mpPlotDefinitionList) return false;

  mActivePlots.clear();

  //step through the vector of specifications and create the plot windows
  std::string key;

  unsigned C_INT32 i, imax = mpPlotDefinitionList->size();

  for (i = 0; i < imax; i++)
    {
      if ((*mpPlotDefinitionList)[i]->isActive())
        {
          key = (*mpPlotDefinitionList)[i]->CCopasiParameter::getKey();
          //std::cout << key << std::endl;

          if (mPlotMap[key] == NULL)
            {
              mPlotMap[key] = new PlotWindow(this, (*mpPlotDefinitionList)[i]);
            }
          else
            {
              mPlotMap[key]->initFromSpec((*mpPlotDefinitionList)[i]);
            }
          mPlotMap[key]->show();

          mActivePlots.push_back(mPlotMap[key]);
        }
    }

  return true;
}

void CPlotSpec2Vector::doPlotting()
{
  sendDataToAllPlots();

  if (mTime + LLONG_CONST(200000) < CCopasiTimeVariable::getCurrentWallTime())
    {
      CCopasiTimeVariable oldTime = CCopasiTimeVariable::getCurrentWallTime();
      updateAllPlots();
      mTime = CCopasiTimeVariable::getCurrentWallTime();
      CCopasiTimeVariable timeDiff = mTime - oldTime;
      mTime = mTime + timeDiff + timeDiff + timeDiff;
    }

  return;
}

void CPlotSpec2Vector::doSeparator()
{
  std::vector<PlotWindow*>::const_iterator it = mActivePlots.begin();
  std::vector<PlotWindow*>::const_iterator end = mActivePlots.end();

  for (; it != end; ++it)
    (*it)->doSeparator();

  if (mTime + LLONG_CONST(200000) < CCopasiTimeVariable::getCurrentWallTime())
    {
      CCopasiTimeVariable oldTime = CCopasiTimeVariable::getCurrentWallTime();
      updateAllPlots();
      mTime = CCopasiTimeVariable::getCurrentWallTime();
      CCopasiTimeVariable timeDiff = mTime - oldTime;
      mTime = mTime + timeDiff + timeDiff + timeDiff;
    }

  return;
}

void CPlotSpec2Vector::finishPlotting()
{
  updateAllPlots();
  finishAllPlots();
}

#ifdef XXXX
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
#endif // XXXX

bool CPlotSpec2Vector::compile(std::vector< CCopasiContainer * > listOfContainer)
{
  // build the vector of active plots
  if (!initAllPlots()) return false;

  bool success = true;

  std::vector<PlotWindow *>::iterator it = mActivePlots.begin();
  std::vector<PlotWindow *>::iterator end = mActivePlots.end();
  for (; it != end; ++it)
    success &= (*it)->compile(listOfContainer);

  return success;
}
