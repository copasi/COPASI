/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMProblem.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2009/09/25 14:46:21 $
   End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CEFMProblem.h"
#include "CEFMTask.h"
#include "CFluxMode.h"

//  Default constructor
CEFMProblem::CEFMProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::optimization, pParent)
{
  initializeParameter();
  initObjects();
}

// copy constructor
CEFMProblem::CEFMProblem(const CEFMProblem& src,
                         const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent)
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

bool CEFMProblem::setCallBack(CProcessReport * pCallBack)
{
  CCopasiProblem::setCallBack(pCallBack);

  return true;
}

void CEFMProblem::initObjects()
{}

bool CEFMProblem::initialize()
{
  return CCopasiProblem::initialize();
}

void CEFMProblem::printResult(std::ostream * ostream) const
{
  CEFMTask * pTask = dynamic_cast< CEFMTask * >(getObjectParent());

  if (pTask)
    {
      const std::vector< CFluxMode > & FluxModes = pTask->getFluxModes();

      *ostream << "\tNumber of Modes:\t" << FluxModes.size() << std::endl;

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
    }
}
