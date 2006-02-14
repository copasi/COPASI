/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitMethod.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/02/14 14:35:28 $
   End CVS Header */

#include "copasi.h"

#include "CFitTask.h"
 #include "CFitMethod.h"
 #include "CFitProblem.h"

#include "utilities/CCopasiMessage.h"

const std::string CFitMethod::TypeName[] =
  {
    ""
  };

COptMethod * CFitMethod::createMethod(CCopasiMethod::SubType subType)
{
  COptMethod * pMethod = NULL;

  switch (subType)
    {
      /*
          case GeneticAlgorithmSR:
            pMethod = new COptMethodGASR();
            break;
      */

    default:
      pMethod = COptMethod::createMethod(subType);
    }

  return pMethod;
}

// Default constructor
CFitMethod::CFitMethod():
    COptMethod(CCopasiTask::parameterFitting, CCopasiMethod::unset),
    mpFitProblem(NULL),
    mpFitTask(NULL)
{CONSTRUCTOR_TRACE;}

CFitMethod::CFitMethod(CCopasiMethod::SubType subType,
                       const CCopasiContainer * pParent):
    COptMethod(CCopasiTask::parameterFitting, subType, pParent),
    mpFitProblem(NULL),
    mpFitTask(NULL)
{CONSTRUCTOR_TRACE;}

CFitMethod::CFitMethod(const CFitMethod & src,
                       const CCopasiContainer * pParent):
    COptMethod(src, pParent),
    mpFitProblem(src.mpFitProblem),
    mpFitTask(src.mpFitTask)
{CONSTRUCTOR_TRACE;}

CFitMethod::~CFitMethod()
{}

bool CFitMethod::initialize()
{
  if (!COptMethod::initialize()) return false;

  mpFitTask = dynamic_cast<CFitTask *>(getObjectParent());
  if (!mpFitTask) return false;

  return true;
}

bool CFitMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!COptMethod::isValidProblem(pProblem)) return false;

  const CFitProblem * pTP = dynamic_cast<const CFitProblem *>(pProblem);
  if (!pTP)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Problem is not a parameter estimation problem.");
      return false;
    }

  return true;
}
