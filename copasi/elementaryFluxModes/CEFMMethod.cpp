/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMMethod.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/12/13 18:20:09 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CEFMMethod class
 *  This class describes the interface to all optimization methods.
 *  The various method like RandomSearch or GA have to be derived from
 *  this class.
 *
 *  Created for Copasi by Stefan Hoops 2002
 */

#include "copasi.h"

#include "CEFMTask.h"
#include "CEFMMethod.h"

#include "CEFMAlgorithm.h"

#ifdef COPASI_EXTREMECURRENTS
# include "CExtremeCurrentCalculator.h"
#endif

CEFMMethod * CEFMMethod::createMethod(CCopasiMethod::SubType subType)
{
  CEFMMethod * pMethod = NULL;

  switch (subType)
    {
    case EFMAlgorithm:
      pMethod = new CEFMAlgorithm();
      break;
#ifdef COPASI_EXTREMECURRENTS
    case extremeCurrents:
      pMethod = new CExtremeCurrentCalculator();
      break;
#endif
    default:
      pMethod = new CEFMAlgorithm();
      break;
    }

  return pMethod;
}

// Default constructor
CEFMMethod::CEFMMethod():
    CCopasiMethod(CCopasiTask::fluxMode, CCopasiMethod::unset)
{CONSTRUCTOR_TRACE;}

CEFMMethod::CEFMMethod(const CCopasiTask::Type & taskType,
                       const CEFMMethod::SubType & subType,
                       const CCopasiContainer * pParent):
    CCopasiMethod(taskType, subType, pParent)
{CONSTRUCTOR_TRACE;}

CEFMMethod::CEFMMethod(const CEFMMethod & src,
                       const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent)
{CONSTRUCTOR_TRACE;}

CEFMMethod::~CEFMMethod()
{}

bool CEFMMethod::calculate(void)
{
  return false;
}

bool CEFMMethod::initialize()
{
  return true;
}

bool CEFMMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  return true;
}

const std::vector< CFluxMode > & CEFMMethod::getFluxModes() const
{return mFluxModes;}

const CVector< unsigned C_INT32 > & CEFMMethod::getIndex() const
  {return mIndex;}
