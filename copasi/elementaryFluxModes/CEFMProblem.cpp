/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMProblem.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/30 17:12:41 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CEFMProblem.h"
#include "CEFMTask.h"

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
        unsigned C_INT32 const noOfModesRows = pTask->getFluxModeSize();
        *ostream << "\tNumber of Modes:\t" << noOfModesRows << std::endl;

        unsigned C_INT32 j;
        for (j = 0; j < noOfModesRows; j++)
          {
            *ostream << j + 1;
            if (pTask->isFluxModeReversible(j) == true)
              *ostream << "\tReversible";
            else
              *ostream << "\tIrreversible";

            std::string Description = pTask->getFluxModeDescription(j);
            unsigned int x, xmax = pTask->getFluxModeSize(j);
            std::string::size_type start = 0;
            std::string::size_type end = 0;

            //const CFluxMode & mode = pTask->getFluxMode(j);
            for (x = 0; x < xmax; x++)
              {
                if (x)
                  *ostream << "\t";

                end = Description.find("\n", start);
                *ostream << "\t" << Description.substr(start, end - start);
                start = end + 1;
                *ostream << "\t" << pTask->getReactionEquation(j, x) << std::endl;
              }
          }
      }
  }
