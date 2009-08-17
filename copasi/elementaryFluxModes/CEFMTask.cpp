// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMTask.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/08/17 19:56:49 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CEFMTask class.
 *
 * This class implements a optimization task which is comprised of a
 * of a problem and a method.
 *
 */
#include "copasi.h"

#include "CEFMTask.h"
#include "CEFMMethod.h"
#include "CEFMProblem.h"

#ifdef COPASI_SSA
#include "CSSAMethod.h"
#endif

#include "model/CModel.h"
#include "model/CChemEqInterface.h"
#include "utilities/CCopasiProblem.h"

const unsigned C_INT32 CEFMTask::ValidMethods[] =
{
  CCopasiMethod::EFMAlgorithm,
#ifdef COPASI_SSA
  CCopasiMethod::stoichiometricStabilityAnalysis,
#endif
  0
};

CEFMTask::CEFMTask(const CCopasiContainer * pParent):
    CCopasiTask(CCopasiTask::fluxMode, pParent)
{
  mpProblem = new CEFMProblem(this);
  mpMethod = CEFMMethod::createMethod();

  this->add(mpMethod, true);
}

CEFMTask::CEFMTask(const CEFMTask & src,
                   const CCopasiContainer * pParent):
    CCopasiTask(src, pParent)
{
  mpProblem = new CCopasiProblem(*static_cast< CEFMProblem * >(src.mpProblem), this);
  mpMethod = CEFMMethod::createMethod(src.mpMethod->getSubType());

  this->add(mpMethod, true);
}

CEFMTask::~CEFMTask()
{}

bool CEFMTask::setCallBack(CProcessReport * pCallBack)
{
  bool success = CCopasiTask::setCallBack(pCallBack);

  if (!mpProblem->setCallBack(pCallBack)) success = false;

  if (!mpMethod->setCallBack(pCallBack)) success = false;

  return success;
}

bool CEFMTask::initialize(const OutputFlag & of,
                          COutputHandler * pOutputHandler,
                          std::ostream * pOstream)
{
  CEFMMethod * pMethod = dynamic_cast<CEFMMethod *>(mpMethod);

  if (pMethod == NULL) return false;

  return CCopasiTask::initialize(of, pOutputHandler, pOstream);
}

bool CEFMTask::process(const bool & /* useInitialValues */)
{
  return static_cast<CEFMMethod *>(mpMethod)->calculate();
}

bool CEFMTask::setMethodType(const int & type)
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  if (mpMethod->getSubType() == Type) return true;

  pdelete(mpMethod);

  mpMethod = CEFMMethod::createMethod(Type);
  this->add(mpMethod, true);

  return true;
}

bool CEFMTask::isFluxModeReversible(unsigned C_INT32 index) const
{return static_cast<CEFMMethod *>(mpMethod)->getFluxModes()[index].isReversible();}

//const CFluxMode & CElementaryFluxModes::getFluxMode(unsigned C_INT32 index) const
//  {return static_cast<CEFMMethod *>(mpMethod)->getFluxModes()[index];}

std::string
CEFMTask::getFluxModeDescription(unsigned C_INT32 index) const
{
  std::stringstream tmp;
  tmp.flags(std::ios::fixed);
  tmp.precision(0);

  const std::vector< CFluxMode > & FluxModes =
    static_cast<CEFMMethod *>(mpMethod)->getFluxModes();
  const CVector< const CReaction * > & ReorderedReactions =
    static_cast<CEFMMethod *>(mpMethod)->getReorderedReactions();

  unsigned C_INT32 j, jmax = FluxModes[index].size();

#ifdef COPASI_SSA

  if (mpMethod->getSubType() == CCopasiMethod::stoichiometricStabilityAnalysis)
    {
      CSSAMethod * method = dynamic_cast<CSSAMethod *>(mpMethod);

      for (j = 0; j < jmax; j++)
        {
          if (j) tmp << "\n";

          std::string addstrng = "";

          if (ReorderedReactions[FluxModes[index].getReactionIndex(j)]->isReversible())
            {
              addstrng = " (Forward)";

              if (method->isReactionReversed(FluxModes[index].getReactionIndex(j)))
                addstrng = " (Backward)";
            }

          tmp << FluxModes[index].getMultiplier(j) << " * "
          << ReorderedReactions[FluxModes[index].getReactionIndex(j)]->getObjectName()
          << addstrng;
        }
    }
  else
#endif
    for (j = 0; j < jmax; j++)
      {
        if (j) tmp << "\n";

        tmp << FluxModes[index].getMultiplier(j) << " * "
        << ReorderedReactions[FluxModes[index].getReactionIndex(j)]->getObjectName();
      }

  return tmp.str();
}

unsigned C_INT32 CEFMTask::getFluxModeSize() const
{return static_cast<CEFMMethod *>(mpMethod)->getFluxModes().size();}

unsigned C_INT32 CEFMTask::getFluxModeSize(unsigned C_INT32 index) const
{return static_cast<CEFMMethod *>(mpMethod)->getFluxModes()[index].size();}

std::string CEFMTask::getReactionEquation(unsigned C_INT32 index1, unsigned C_INT32 index2) const
{
  CEFMMethod * pMethod = static_cast<CEFMMethod *>(mpMethod);

  const CReaction * pReaction =
    pMethod->getReorderedReactions()[pMethod->getFluxModes()[index1].getReactionIndex(index2)];

#ifdef COPASI_SSA

  if (mpMethod->getSubType() == CCopasiMethod::stoichiometricStabilityAnalysis)
    {
      CSSAMethod * method = static_cast<CSSAMethod *>(mpMethod);

      std::string retstring = getReactionEquationForward(index1, index2);

      if (pReaction->isReversible())
        {
          if (method->isReactionReversed(pMethod->getFluxModes()[index1].getReactionIndex(index2)))
            retstring = getReactionEquationBackward(index1, index2);
        }

      return retstring;
    }
  else
#endif //COPASI_SSA
    return CChemEqInterface::getChemEqString(mpProblem->getModel(), *pReaction, false);
}

#ifdef COPASI_SSA
std::string CEFMTask::getReactionEquationForward(unsigned C_INT32 index1, unsigned C_INT32 index2) const
{
  const CReaction *pReaction =
    static_cast<CEFMMethod *>(mpMethod)->getReorderedReactions()[static_cast<CEFMMethod *>(mpMethod)->getFluxModes()[index1].getReactionIndex(index2)];

  std::string equation = CChemEqInterface::getChemEqString(mpProblem->getModel(),
                         *pReaction,
                         false);

  if (pReaction->isReversible())
    {
      int i = equation.find("=", 0);
      equation.replace(i, 1, "->");
    }

  return equation;
}

std::string CEFMTask::getReactionEquationBackward(unsigned C_INT32 index1, unsigned C_INT32 index2) const
{
  const CReaction *pReaction =
    static_cast<CEFMMethod *>(mpMethod)->getReorderedReactions()[static_cast<CEFMMethod *>(mpMethod)->getFluxModes()[index1].getReactionIndex(index2)];

  std::string equation = CChemEqInterface::getChemEqString(mpProblem->getModel(),
                         *pReaction,
                         false);

  if (pReaction->isReversible())
    {
      int i = equation.find("=", 0);
      std::string lhs = equation.substr(0, i - 1);
      std::string rhs = equation.substr(i + 2 , equation.size() - i - 1);
      equation = rhs + " -> " + lhs;
    }

  return equation;
}
#endif // COPASI_SSA
