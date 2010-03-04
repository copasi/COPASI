// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMTask.cpp,v $
//   $Revision: 1.14.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/03/04 18:11:45 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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
#include "CFluxMode.h"

#ifdef COPASI_SSA
#include "CSSAMethod.h"
#endif

#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CMetabNameInterface.h"
#include "model/CChemEqInterface.h"
#include "utilities/CCopasiProblem.h"

const unsigned C_INT32 CEFMTask::ValidMethods[] =
{
  CCopasiMethod::EFMAlgorithm,
#ifdef COPASI_DEBUG
  CCopasiMethod::EFMBitPatternTreeAlgorithm,
#endif // COPASI_DEBUG
#ifdef COPASI_SSA
  CCopasiMethod::stoichiometricStabilityAnalysis,
#endif // COPASI_SSA
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

  if (!mpMethod->isValidProblem(mpProblem))
    {
      return false;
    }

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

      CCopasiVector < CChemEqElement >::const_iterator it = pReaction->getChemEq().getSubstrates().begin();
      CCopasiVector < CChemEqElement >::const_iterator end = pReaction->getChemEq().getSubstrates().end();

      for (; it != end; ++it)
        {
          if ((*it)->getMetaboliteKey() == Key)
            {
              *pIn += fabs(itReaction->second) * (*it)->getMultiplicity();
              break;
            }
        }

      it = pReaction->getChemEq().getProducts().begin();
      end = pReaction->getChemEq().getProducts().end();

      for (; it != end; ++it)
        {
          if ((*it)->getMetaboliteKey() == Key)
            {
              *pOut += fabs(itReaction->second) * (*it)->getMultiplicity();
              break;
            }
        }
    }

  return std::make_pair(In, Out);
}

std::string CEFMTask::getNetReaction(const CFluxMode & fluxMode) const
{
  const CModel* pModel = getProblem()->getModel();

  if (pModel == NULL)
    return "";

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

          Products << CMetabNameInterface::getDisplayName(pModel, *it->first);
          ProductsSeparator = " + ";
        }
      else if (it->second < -100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
        {
          Substrates << SubstratesSeparator;

          if (it->second < -1.0 - 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
            {
              Substrates << -it->second << " * ";
            }

          Substrates << CMetabNameInterface::getDisplayName(pModel, *it->first);
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
  const CModel* pModel = getProblem()->getModel();

  if (pModel == NULL)
    return "";

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
          Modifiers << CMetabNameInterface::getDisplayName(pModel, *it->first);
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

      CCopasiVector < CChemEqElement >::const_iterator it = pReaction->getChemEq().getSubstrates().begin();
      CCopasiVector < CChemEqElement >::const_iterator end = pReaction->getChemEq().getSubstrates().end();

      for (; it != end; ++it)
        {
          pSpecies = (*it)->getMetabolite();

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
          pSpecies = (*it)->getMetabolite();

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
      std::string rhs = equation.substr(i + 2 , equation.size() - i - 1);
      equation = rhs + " -> " + lhs;
    }

  return equation;
}
#endif // COPASI_SSA
