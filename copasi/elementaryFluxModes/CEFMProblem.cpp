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

#include "copasi/copasi.h"

#include "CEFMProblem.h"
#include "CEFMTask.h"
#include "CFluxMode.h"
#include "CEFMMethod.h"

#include "copasi/model/CReaction.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CMetabNameInterface.h"
#include "copasi/math/CMathContainer.h"

//  Default constructor
CEFMProblem::CEFMProblem(const CDataContainer * pParent):
  CCopasiProblem(CTaskEnum::Task::fluxMode, pParent),
  mFluxModes(),
  mReorderedReactions()
{
  initializeParameter();
  initObjects();
}

// copy constructor
CEFMProblem::CEFMProblem(const CEFMProblem& src,
                         const CDataContainer * pParent):
  CCopasiProblem(src, pParent),
  mFluxModes(src.mFluxModes),
  mReorderedReactions(src.mReorderedReactions)
{
  initializeParameter();
  initObjects();
}

// Destructor
CEFMProblem::~CEFMProblem()
{}

void CEFMProblem::initializeParameter()
{elevateChildren();}

bool CEFMProblem::elevateChildren()
{return true;}

bool CEFMProblem::setCallBack(CProcessReportLevel callBack)
{
  CCopasiProblem::setCallBack(callBack);

  return true;
}

void CEFMProblem::initObjects()
{}

bool CEFMProblem::initialize()
{
  return CCopasiProblem::initialize();
}

const std::vector< CFluxMode > & CEFMProblem::getFluxModes() const
{return mFluxModes;}

std::vector< CFluxMode > & CEFMProblem::getFluxModes()
{return mFluxModes;}

const std::vector< const CReaction * > & CEFMProblem::getReorderedReactions() const
{return mReorderedReactions;}

std::vector< const CReaction * > & CEFMProblem::getReorderedReactions()
{return mReorderedReactions;}

void CEFMProblem::printResult(std::ostream * ostream) const
{
  CEFMTask * pTask = dynamic_cast< CEFMTask * >(getObjectParent());

  if (pTask)
    {
      const std::vector< CFluxMode > & FluxModes = pTask->getFluxModes();

      // List
      *ostream << "\tNumber of Modes:\t" << FluxModes.size() << std::endl;

      // Column header
      *ostream << "#\t\tReactions\tEquations" << std::endl;

      std::vector< CFluxMode >::const_iterator itMode = FluxModes.begin();
      std::vector< CFluxMode >::const_iterator endMode = FluxModes.end();

      unsigned C_INT32 j;

      for (j = 0; itMode != endMode; ++itMode, j++)
        {
          *ostream << j + 1;

          if (itMode->isReversible() == true)
            *ostream << "\tReversible";
          else
            *ostream << "\tIrreversible";

          std::string Description = pTask->getFluxModeDescription(*itMode);
          CFluxMode::const_iterator itReaction = itMode->begin();
          CFluxMode::const_iterator endReaction = itMode->end();

          std::string::size_type start = 0;
          std::string::size_type end = 0;

          for (; itReaction != endReaction; ++itReaction)
            {
              if (itReaction != itMode->begin())
                *ostream << "\t";

              end = Description.find("\n", start);
              *ostream << "\t" << Description.substr(start, end - start);
              start = end + 1;
              *ostream << "\t" << pTask->getReactionEquation(itReaction) << std::endl;
            }
        }

      *ostream << std::endl;

      // Net Reactions
      // Column header
      *ostream << "#\tNet Reaction\tInternal Species" << std::endl;

      itMode = FluxModes.begin();

      for (j = 0; itMode != endMode; ++itMode, j++)
        {
          *ostream << j + 1;
          *ostream << "\t" << pTask->getNetReaction(*itMode);
          *ostream << "\t" << pTask->getInternalSpecies(*itMode) << std::endl;
        }

      *ostream << std::endl;

      // EFM vs Reaction
      std::vector< const CReaction * >::const_iterator itReaction = mReorderedReactions.begin();
      std::vector< const CReaction * >::const_iterator endReaction = mReorderedReactions.end();

      // Column header
      *ostream << "#";

      for (; itReaction != endReaction; ++itReaction)
        {
          *ostream << "\t" << (*itReaction)->getObjectName();
        }

      *ostream << std::endl;

      itMode = FluxModes.begin();
      size_t k;

      for (j = 0; itMode != endMode; ++itMode, j++)
        {
          itReaction = mReorderedReactions.begin();

          *ostream << j + 1;

          for (k = 0; itReaction != endReaction; ++itReaction, k++)
            {
              *ostream << "\t" << itMode->getMultiplier(k);
            }

          *ostream << std::endl;
        }

      *ostream << std::endl;

      const CModel & Model = mpContainer->getModel();

      // EFM vs Species
      std::vector< CMetab * >::const_iterator itSpecies = Model.getMetabolites().begin();
      std::vector< CMetab * >::const_iterator endSpecies = Model.getMetabolites().end();
      // Column header
      *ostream << "#";

      for (; itSpecies != endSpecies; ++itSpecies)
        {
          *ostream << "\t" << CMetabNameInterface::getDisplayName(&Model, **itSpecies, false);
        }

      *ostream << std::endl;

      itMode = FluxModes.begin();

      for (j = 0; itMode != endMode; ++itMode, j++)
        {
          itSpecies = Model.getMetabolites().begin();

          *ostream << j + 1;

          for (; itSpecies != endSpecies; ++itSpecies)
            {
              std::pair< C_FLOAT64, C_FLOAT64 > Changes =
                pTask->getSpeciesChanges(*itMode, **itSpecies);

              *ostream << "\t";

              if (Changes.first > 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon() ||
                  Changes.second > 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
                {
                  *ostream << "-" << Changes.first << " | +" << Changes.second;
                }
            }

          *ostream << std::endl;
        }

      *ostream << std::endl;
    }
}
