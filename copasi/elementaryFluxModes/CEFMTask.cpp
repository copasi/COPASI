// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CEFMTask class.
 *
 * This class implements a optimization task which is comprised of a
 * of a problem and a method.
 *
 */

#include <sstream>

#include "copasi/copasi.h"

#include "CEFMTask.h"
#include "CEFMMethod.h"
#include "CEFMProblem.h"
#include "CFluxMode.h"

#ifdef COPASI_SSA
#include "CSSAMethod.h"
#endif

#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CMetabNameInterface.h"
#include "copasi/model/CChemEqInterface.h"
#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/utilities/CMethodFactory.h"

CEFMTask::CEFMTask(const CDataContainer * pParent,
                   const CTaskEnum::Task & type):
  CCopasiTask(pParent, type)
{
  mpMethod = CMethodFactory::create(getType(), CTaskEnum::Method::EFMAlgorithm, this);
}

CEFMTask::CEFMTask(const CEFMTask & src,
                   const CDataContainer * pParent):
  CCopasiTask(src, pParent)
{}

CEFMTask::~CEFMTask()
{}

bool CEFMTask::setCallBack(CProcessReportLevel callBack)
{
  bool success = CCopasiTask::setCallBack(callBack);

  if (!mpProblem->setCallBack(mProcessReport)) success = false;

  if (!mpMethod->setCallBack(mProcessReport)) success = false;

  return success;
}

bool CEFMTask::initialize(const OutputFlag & of,
                          COutputHandler * pOutputHandler,
                          std::ostream * pOstream)
{
  CEFMMethod * pMethod = dynamic_cast<CEFMMethod *>(mpMethod);

  if (pMethod == NULL) return false;

  bool success = mpMethod->isValidProblem(mpProblem);
  success &= CCopasiTask::initialize(of, pOutputHandler, pOstream);

  return success;
}

bool CEFMTask::process(const bool & /* useInitialValues */)
{
  output(COutputInterface::BEFORE);

  bool success = static_cast<CEFMMethod *>(mpMethod)->calculate();

  output(COutputInterface::AFTER);

  return success;
}

// virtual
const CTaskEnum::Method * CEFMTask::getValidMethods() const
{
  static const CTaskEnum::Method ValidMethods[] =
  {
    CTaskEnum::Method::EFMAlgorithm,

#ifdef COPASI_DEBUG
    CTaskEnum::Method::EFMBitPatternTreeAlgorithm,
    CTaskEnum::Method::EFMBitPatternAlgorithm,
#endif // COPASI_DEBUG

#ifdef COPASI_SSA
    CTaskEnum::Method::stoichiometricStabilityAnalysis,
#endif // COPASI_SSA

    CTaskEnum::Method::UnsetMethod
  };

  return ValidMethods;
}

std::string CEFMTask::getFluxModeDescription(const CFluxMode & fluxMode) const
{
  std::stringstream tmp;
  tmp.flags(std::ios::fixed);
  tmp.precision(0);

  const std::vector< const CReaction * > & ReorderedReactions =
    static_cast<CEFMProblem *>(mpProblem)->getReorderedReactions();

  unsigned C_INT32 j;
  CFluxMode::const_iterator itMode = fluxMode.begin();
  CFluxMode::const_iterator endMode = fluxMode.end();

#ifdef COPASI_SSA

  if (mpMethod->getSubType() == CTaskEnum::Method::stoichiometricStabilityAnalysis)
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
    for (j = 0; itMode != endMode; ++itMode, j++)
      {
        if (j) tmp << "\n";

        tmp << itMode->second << " * "
            << ReorderedReactions[itMode->first]->getObjectName();
      }

  return tmp.str();
}

const std::vector< CFluxMode > & CEFMTask::getFluxModes() const
{
  return static_cast<const CEFMProblem *>(mpProblem)->getFluxModes();
}

std::string CEFMTask::getReactionEquation(const std::map< size_t, C_FLOAT64 >::const_iterator & itReaction) const
{
  CEFMProblem * pProblem = static_cast<CEFMProblem *>(mpProblem);

  const CReaction * pReaction =
    pProblem->getReorderedReactions()[itReaction->first];

#ifdef COPASI_SSA

  if (mpMethod->getSubType() == CTaskEnum::Method::stoichiometricStabilityAnalysis)
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
    return CChemEqInterface::getChemEqString(*pReaction, false);
}

std::pair< C_FLOAT64, C_FLOAT64 > CEFMTask::getSpeciesChanges(const CFluxMode & fluxMode,
    const CMetab & metab) const
{
  C_FLOAT64 In = 0.0;
  C_FLOAT64 Out = 0.0;
  C_FLOAT64 *pIn, *pOut;

  CFluxMode::const_iterator itReaction = fluxMode.begin();
  CFluxMode::const_iterator endReaction = fluxMode.end();

  std::string Key = metab.getKey();

  const std::vector< const CReaction * > & ReorderedReactions =
    static_cast<CEFMProblem *>(mpProblem)->getReorderedReactions();

  for (; itReaction != endReaction; ++itReaction)
    {
      const CReaction * pReaction = ReorderedReactions[itReaction->first];

      if (itReaction->second < 0.0)
        {
          pIn = &Out;
          pOut = &In;
        }
      else
        {
          pIn = &In;
          pOut = &Out;
        }

      CDataVector < CChemEqElement >::const_iterator it = pReaction->getChemEq().getSubstrates().begin();
      CDataVector < CChemEqElement >::const_iterator end = pReaction->getChemEq().getSubstrates().end();

      for (; it != end; ++it)
        {
          if (it->getMetaboliteKey() == Key)
            {
              *pIn += fabs(itReaction->second) * it->getMultiplicity();
              break;
            }
        }

      it = pReaction->getChemEq().getProducts().begin();
      end = pReaction->getChemEq().getProducts().end();

      for (; it != end; ++it)
        {
          if (it->getMetaboliteKey() == Key)
            {
              *pOut += fabs(itReaction->second) * it->getMultiplicity();
              break;
            }
        }
    }

  return std::make_pair(In, Out);
}

std::string CEFMTask::getNetReaction(const CFluxMode & fluxMode) const
{
  const CModel & Model = mpContainer->getModel();

  std::map< const CMetab *, C_FLOAT64 > Data = getNetReactionData(fluxMode);

  std::stringstream Substrates;
  Substrates.flags(std::ios::fixed);
  Substrates.precision(0);
  std::string SubstratesSeparator = "";

  std::stringstream Products;
  Products.flags(std::ios::fixed);
  Products.precision(0);
  std::string ProductsSeparator = "";

  std::map< const CMetab *, C_FLOAT64 >::const_iterator it = Data.begin();
  std::map< const CMetab *, C_FLOAT64 >::const_iterator end = Data.end();

  for (; it != end; ++it)
    {
      if (it->second > 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
        {
          Products << ProductsSeparator;

          if (it->second > 1.0 + 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              Products << it->second << " * ";
            }

          Products << CMetabNameInterface::getDisplayName(&Model, *it->first, true);
          ProductsSeparator = " + ";
        }
      else if (it->second < -100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
        {
          Substrates << SubstratesSeparator;

          if (it->second < -1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              Substrates << -it->second << " * ";
            }

          Substrates << CMetabNameInterface::getDisplayName(&Model, *it->first, true);
          SubstratesSeparator = " + ";
        }
    }

  if (fluxMode.isReversible())
    {
      return Substrates.str() + " = " + Products.str();
    }
  else
    {
      return Substrates.str() + " -> " + Products.str();
    }
}

std::string CEFMTask::getInternalSpecies(const CFluxMode & fluxMode) const
{
  const CModel & Model = mpContainer->getModel();

  std::map< const CMetab *, C_FLOAT64 > Data = getNetReactionData(fluxMode);

  std::stringstream Modifiers;
  Modifiers.flags(std::ios::fixed);
  Modifiers.precision(0);
  std::string ModifiersSeparator = "";

  std::map< const CMetab *, C_FLOAT64 >::const_iterator it = Data.begin();
  std::map< const CMetab *, C_FLOAT64 >::const_iterator end = Data.end();

  for (; it != end; ++it)
    {
      if (fabs(it->second) < 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
        {
          Modifiers << ModifiersSeparator;
          Modifiers << CMetabNameInterface::getDisplayName(&Model, *it->first, true);
          ModifiersSeparator = ", ";
        }
    }

  return Modifiers.str();
}

std::map< const CMetab *, C_FLOAT64 > CEFMTask::getNetReactionData(const CFluxMode & fluxMode) const
{
  std::map< const CMetab *, C_FLOAT64 > NetReaction;
  std::pair< C_FLOAT64, C_FLOAT64 > Changes;

  CFluxMode::const_iterator itReaction = fluxMode.begin();
  CFluxMode::const_iterator endReaction = fluxMode.end();

  const std::vector< const CReaction * > & ReorderedReactions =
    static_cast<CEFMProblem *>(mpProblem)->getReorderedReactions();

  const CMetab * pSpecies;

  for (; itReaction != endReaction; ++itReaction)
    {
      const CReaction * pReaction = ReorderedReactions[itReaction->first];

      CDataVector < CChemEqElement >::const_iterator it = pReaction->getChemEq().getSubstrates().begin();
      CDataVector < CChemEqElement >::const_iterator end = pReaction->getChemEq().getSubstrates().end();

      for (; it != end; ++it)
        {
          pSpecies = it->getMetabolite();

          if (NetReaction.count(pSpecies) == 0)
            {
              Changes = getSpeciesChanges(fluxMode, *pSpecies);
              NetReaction[pSpecies] = Changes.second - Changes.first;
            }
        }

      it = pReaction->getChemEq().getProducts().begin();
      end = pReaction->getChemEq().getProducts().end();

      for (; it != end; ++it)
        {
          pSpecies = it->getMetabolite();

          if (NetReaction.count(pSpecies) == 0)
            {
              Changes = getSpeciesChanges(fluxMode, *pSpecies);
              NetReaction[pSpecies] = Changes.second - Changes.first;
            }
        }
    }

  return NetReaction;
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
      std::string rhs = equation.substr(i + 2, equation.size() - i - 1);
      equation = rhs + " -> " + lhs;
    }

  return equation;
}
#endif // COPASI_SSA
