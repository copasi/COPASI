/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiProblem.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/10/04 13:39:34 $
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
    mCalculateVariables(),
    mCalculateResults(),
    mSolutionVariables(),
    mSolutionResults()
{}

CCopasiProblem::CCopasiProblem(const CCopasiTask::Type & type,
                               const CCopasiContainer * pParent):
    CCopasiParameterGroup(CCopasiTask::TypeName[type], pParent, "Problem"),
    mType(type),
    mpModel(NULL),
    mCalculateVariables(),
    mCalculateResults(),
    mSolutionVariables(),
    mSolutionResults()
{}

CCopasiProblem::CCopasiProblem(const CCopasiProblem & src,
                               const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mType(src.mType),
    mpModel(src.mpModel),
    mCalculateVariables(src.mCalculateVariables),
    mCalculateResults(src.mCalculateResults),
    mSolutionVariables(src.mSolutionVariables),
    mSolutionResults(src.mSolutionResults)
{}

CCopasiProblem::~CCopasiProblem() {}

const CCopasiTask::Type & CCopasiProblem::getType() const {return mType;}

bool CCopasiProblem::setModel(CModel * pModel)
{
  mpModel = pModel;
  return true;
}

CModel * CCopasiProblem::getModel() const {return mpModel;}

unsigned C_INT32 CCopasiProblem::getVariableSize() const
  {return mCalculateVariables.size();}

unsigned C_INT32 CCopasiProblem::getResultSize() const
  {return mCalculateResults.size();}

C_FLOAT64 * CCopasiProblem::getCalculateVariables()
{return mCalculateVariables.array();}

C_FLOAT64 * CCopasiProblem::getCalculateResults()
{return mCalculateResults.array();}

C_FLOAT64 * CCopasiProblem::getSolutionVariables()
{return mSolutionVariables.array();}

C_FLOAT64 * CCopasiProblem::getSolutionResults()
{return mSolutionResults.array();}

bool CCopasiProblem::initialize() {return true;}

bool CCopasiProblem::calculate() {return true;}

bool CCopasiProblem::checkParametricConstraints() {return true;}

bool CCopasiProblem::checkFunctionalConstraints() {return true;}

void CCopasiProblem::setInitialState(const CState & initialState) {}
