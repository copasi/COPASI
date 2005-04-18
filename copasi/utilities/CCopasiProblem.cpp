/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiProblem.cpp,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/04/18 09:01:16 $
   End CVS Header */

/**
 *  CCopasiProblem class.
 *  This class is used to describe a task in COPASI. This class is 
 *  intended to be used as the parent class for all tasks whithin COPASI.
 *  
 *  Created for Copasi by Stefan Hoops 2003
 */

#include "copasi.h"

#include "CCopasiProblem.h"

CCopasiProblem::CCopasiProblem():
    CCopasiParameterGroup("NoName", NULL, "Problem"),
    mType(CCopasiTask::unset),
    mpModel(NULL),
    mpCallBack(NULL)
{}

CCopasiProblem::CCopasiProblem(const CCopasiTask::Type & type,
                               const CCopasiContainer * pParent):
    CCopasiParameterGroup(CCopasiTask::TypeName[type], pParent, "Problem"),
    mType(type),
    mpModel(NULL),
    mpCallBack(NULL)
{}

CCopasiProblem::CCopasiProblem(const CCopasiProblem & src,
                               const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mType(src.mType),
    mpModel(src.mpModel),
    mpCallBack(src.mpCallBack)
{}

CCopasiProblem::~CCopasiProblem() {}

const CCopasiTask::Type & CCopasiProblem::getType() const {return mType;}

bool CCopasiProblem::setModel(CModel * pModel)
{
  mpModel = pModel;
  return true;
}

CModel * CCopasiProblem::getModel() const {return mpModel;}

bool CCopasiProblem::setCallBack(CCopasiCallBack * pCallBack)
{
  mpCallBack = pCallBack;
  return true;
}

//virtual
std::vector<CDefaultPlotDescription> CCopasiProblem::getListOfDefaultPlotDescriptions() const
  {
    std::vector<CDefaultPlotDescription> ret;
    return ret;
  }

//virtual
bool CCopasiProblem::createDefaultPlot(C_INT32 C_UNUSED(id)) const
  {
    return false;
  }

//void CCopasiProblem::setInitialState(const CState & initialState) {}

// propably for optimization only

bool CCopasiProblem::initialize() {return true;}

bool CCopasiProblem::calculate() {return true;}

bool CCopasiProblem::checkParametricConstraints() {return true;}

bool CCopasiProblem::checkFunctionalConstraints() {return true;}
