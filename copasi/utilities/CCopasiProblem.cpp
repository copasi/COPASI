/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiProblem.cpp,v $
   $Revision: 1.18 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/02/14 14:35:33 $
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
#include "model/CMetab.h"
#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "CCopasiVector.h"

CCopasiProblem::CCopasiProblem():
    CCopasiParameterGroup("NoName", NULL, "Problem"),
    mType(CCopasiTask::unset),
    mpModel(NULL),
    mpCallBack(NULL),
    mpReport(NULL)
{}

CCopasiProblem::CCopasiProblem(const CCopasiTask::Type & type,
                               const CCopasiContainer * pParent):
    CCopasiParameterGroup(CCopasiTask::TypeName[type], pParent, "Problem"),
    mType(type),
    mpModel(NULL),
    mpCallBack(NULL),
    mpReport(NULL)
{}

CCopasiProblem::CCopasiProblem(const CCopasiProblem & src,
                               const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mType(src.mType),
    mpModel(src.mpModel),
    mpCallBack(src.mpCallBack),
    mpReport(src.mpReport)
{}

CCopasiProblem::~CCopasiProblem() {}

const CCopasiTask::Type & CCopasiProblem::getType() const {return mType;}

bool CCopasiProblem::setModel(CModel * pModel)
{
  mpModel = pModel;
  return true;
}

CModel * CCopasiProblem::getModel() const {return mpModel;}

bool CCopasiProblem::setCallBack(CProcessReport * pCallBack)
{
  mpCallBack = pCallBack;
  return true;
}

// propably for optimization only

bool CCopasiProblem::initialize() {return true;}

bool CCopasiProblem::calculate() {return true;}

bool CCopasiProblem::restore(const bool & updateModel) {return true;}

bool CCopasiProblem::checkParametricConstraints() {return true;}

bool CCopasiProblem::checkFunctionalConstraints() {return true;}

void CCopasiProblem::print(std::ostream * ostream) const
  {*ostream << *this;}

void CCopasiProblem::printResult(std::ostream * ostream) const
  {*ostream << "Not implemented.";}

std::ostream &operator<<(std::ostream &os, const CCopasiProblem & o)
{
  os << "Problem Description:" << std::endl;

  CCopasiParameterGroup::parameterGroup::const_iterator it =
    o.CCopasiParameter::getValue().pGROUP->begin();
  CCopasiParameterGroup::parameterGroup::const_iterator end =
    o.CCopasiParameter::getValue().pGROUP->end();

  for (; it != end; ++it)
    {
      (*it)->print(&os);
      os << std::endl;
    }

  return os;
}
