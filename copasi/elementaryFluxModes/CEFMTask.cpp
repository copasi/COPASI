/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMTask.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/29 20:15:14 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
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

#include "model/CModel.h"
#include "model/CChemEqInterface.h"
#include "utilities/CCopasiProblem.h"

const unsigned C_INT32 CEFMTask::ValidMethods[] =
  {
    CCopasiMethod::EFMAlgorithm
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
                          std::ostream * pOstream)
{
  CEFMMethod * pMethod = dynamic_cast<CEFMMethod *>(mpMethod);
  if (pMethod == NULL) return false;

  return CCopasiTask::initialize(of, pOstream);
}

bool CEFMTask::process(const bool & /* useInitialValues */)
{
  return static_cast<CEFMMethod *>(mpMethod)->calculate();
}

bool CEFMTask::setMethodType(const int & type)
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  if (mpMethod->getSubType() == Type) return true;

  pdelete (mpMethod);

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
    const std::vector< CFluxMode > & FluxModes =
      static_cast<CEFMMethod *>(mpMethod)->getFluxModes();
    const CVector< unsigned C_INT32 > & Index =
      static_cast<CEFMMethod *>(mpMethod)->getIndex();

    unsigned C_INT32 j, jmax = FluxModes[index].size();
    const CCopasiVectorNS< CReaction > & Reactions = mpProblem->getModel()->getReactions();

    for (j = 0; j < jmax; j++)
      {
        if (j) tmp << "\n";
        tmp << FluxModes[index].getMultiplier(j) << " * "
        << Reactions[Index[FluxModes[index].getReactionIndex(j)]]->getObjectName();
      }

    return tmp.str();
  }

unsigned C_INT32 CEFMTask::getFluxModeSize() const
{return static_cast<CEFMMethod *>(mpMethod)->getFluxModes().size();}

unsigned C_INT32 CEFMTask::getFluxModeSize(unsigned C_INT32 index) const
  {return static_cast<CEFMMethod *>(mpMethod)->getFluxModes()[index].size();}

std::string CEFMTask::getReactionEquation(unsigned C_INT32 index1, unsigned C_INT32 index2) const
  {
    const CCopasiVectorNS < CReaction > & Reactions = mpProblem->getModel()->getReactions();

    return CChemEqInterface::getChemEqString(mpProblem->getModel(),
        *Reactions[static_cast<CEFMMethod *>(mpMethod)->getIndex()[static_cast<CEFMMethod *>(mpMethod)->getFluxModes()[index1].getReactionIndex(index2)]],
        false);
  }
