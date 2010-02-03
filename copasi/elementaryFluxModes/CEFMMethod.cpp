/* Begin CVS Header
  $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMMethod.cpp,v $
  $Revision: 1.11 $
  $Name:  $
  $Author: shoops $
  $Date: 2010/02/03 19:34:09 $
  End CVS Header */

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001-2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CEFMMethod class
 *  This class describes the interface to all optimization methods.
 *  The various method like RandomSearch or GA have to be derived from
 *  this class.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#include "copasi.h"

#include "CEFMTask.h"
#include "CEFMMethod.h"
#include "CEFMProblem.h"

#include "CEFMAlgorithm.h"
#include "CBitPatternTreeMethod.h"
#ifdef COPASI_SSA
# include "CSSAMethod.h"
#endif

#include "model/CModel.h"

CEFMMethod * CEFMMethod::createMethod(CCopasiMethod::SubType subType)
{
  CEFMMethod * pMethod = NULL;

  switch (subType)
    {
      case EFMAlgorithm:
        pMethod = new CEFMAlgorithm();
        break;

      case EFMBitPatternTreeAlgorithm:
        pMethod = new CBitPatternTreeMethod();
        break;

#ifdef COPASI_SSA
      case stoichiometricStabilityAnalysis:
        pMethod = new CSSAMethod();
        break;
#endif

      default:
        pMethod = new CBitPatternTreeMethod();
        break;
    }

  return pMethod;
}

// Default constructor
CEFMMethod::CEFMMethod():
    CCopasiMethod(CCopasiTask::fluxMode, CCopasiMethod::unset),
    mpFluxModes(NULL),
    mpReorderedReactions(NULL)
{CONSTRUCTOR_TRACE;}

CEFMMethod::CEFMMethod(const CCopasiTask::Type & taskType,
                       const CEFMMethod::SubType & subType,
                       const CCopasiContainer * pParent):
    CCopasiMethod(taskType, subType, pParent),
    mpFluxModes(NULL),
    mpReorderedReactions(NULL)
{CONSTRUCTOR_TRACE;}

CEFMMethod::CEFMMethod(const CEFMMethod & src,
                       const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    mpFluxModes(src.mpFluxModes),
    mpReorderedReactions(src.mpReorderedReactions)
{CONSTRUCTOR_TRACE;}

CEFMMethod::~CEFMMethod()
{}

bool CEFMMethod::calculate(void)
{
  return false;
}

bool CEFMMethod::initialize()
{
  CEFMTask * pTask = dynamic_cast< CEFMTask * >(getObjectParent());

  if (pTask == NULL)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCEFMAnalysis + 1);
      return false;
    }

  CEFMProblem * pProblem = dynamic_cast< CEFMProblem *>(pTask->getProblem());

  if (pProblem == NULL)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCEFMAnalysis + 2);
      return false;
    }

  mpFluxModes = & pProblem->getFluxModes();
  mpReorderedReactions = & pProblem->getReorderedReactions();

  mpReorderedReactions->clear();
  mpFluxModes->clear();

  return true;
}

bool CEFMMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  if (pProblem == NULL)
    {
      return false;
    }

  const CModel * pModel = pProblem ->getModel();

  if (pModel == NULL)
    {
      return false;
    }

  // Check that the stoichiometry matrix contains only integers.

  const CMatrix< C_FLOAT64 > & RedStoi = pModel->getRedStoi();
  const C_FLOAT64 * pValue = RedStoi.array();
  const C_FLOAT64 * pValueEnd = pValue + RedStoi.size();

  std::cout << 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() << std::endl;

  for (; pValue != pValueEnd; ++pValue)
    {
      if (fabs(*pValue - floor(*pValue + 0.5)) > 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
        {
          break;
        }
    }

  if (pValue != pValueEnd)
    {
      const CReaction * pReaction = pModel->getReactions()[(pValue - RedStoi.array()) % RedStoi.numCols()];

      CCopasiMessage(CCopasiMessage::ERROR, MCEFMAnalysis + 3, pReaction->getObjectName().c_str());

      return false;
    }

  return true;
}
