/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiMethod.cpp,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/07/01 09:39:48 $
   End CVS Header */

/**
 *  CCopasiMethod class.
 *  This class is used to describe a task in COPASI. This class is 
 *  intended to be used as the parent class for all tasks whithin COPASI.
 *  
 *  Created for Copasi by Stefan Hoops 2003
 */

#include "copasi.h"

#include "CCopasiMethod.h"
#include "CCopasiMessage.h"

const std::string CCopasiMethod::SubTypeName[] =
  {
    "Not set",
    "Random Search",
    "Random Search (PVM)",
    "Simulated Annealing",
    "Genetic Algorithm",
    "Evolutionary Program",
    "Hybrid GA/SA",
    "Genetic Algorithm SR",
    "Enhanced Newton",
    "Deterministic (LSODA)",
    "Stochastic",
    "Hybrid",
    "tau-Leap",
    "MCA Method (Reder)",
    "Scan Framework",
    "Time scale separation Method",
    ""
  };

const char* CCopasiMethod::XMLSubType[] =
  {
    "NotSet",
    "RandomSearch",
    "RandomSearch(PVM)",
    "SimulatedAnnealing",
    "GeneticAlgorithm",
    "EvolutionaryProgram2",
    "HybridGASA",
    "GeneticAlgorithmSR",
    "EnhancedNewton",
    "Deterministic(LSODA)",
    "Stochastic",
    "Hybrid",
    "TauLeap",
    "MCAMethod(Reder)",
    "ScanFramework",
    "TimeScaleSeparationMethod",
    NULL
  };

//    std::string mType;

CCopasiMethod::SubType CCopasiMethod::TypeNameToEnum(const std::string & subTypeName)
{
  unsigned C_INT32 i = 0;
  while (SubTypeName[i] != subTypeName && SubTypeName[i] != "") i++;

  if (CCopasiMethod::SubTypeName[i] != "") return (CCopasiMethod::SubType) i;
  else return CCopasiMethod::unset;
}

CCopasiMethod::SubType CCopasiMethod::XMLNameToEnum(const char * xmlTypeName)
{
  unsigned C_INT32 i = 0;
  while (strcmp(xmlTypeName, XMLSubType[i]) && XMLSubType[i]) i++;

  if (XMLSubType[i]) return (CCopasiMethod::SubType) i;
  else return CCopasiMethod::unset;
}

CCopasiMethod::CCopasiMethod():
    CCopasiParameterGroup("NoName", NULL, "Method"),
    mType(CCopasiTask::unset),
    mSubType(unset),
    mpCallBack(NULL)
{setObjectName(SubTypeName[mType]);}

CCopasiMethod::CCopasiMethod(const CCopasiTask::Type & type,
                             const CCopasiMethod::SubType & subType,
                             const CCopasiContainer * pParent):
    CCopasiParameterGroup(TypeName[type], pParent, "Method"),
    mType(type),
    mSubType(subType),
    mpCallBack(NULL)
{setObjectName(SubTypeName[mSubType]);}

CCopasiMethod::CCopasiMethod(const CCopasiMethod & src,
                             const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mType(src.mType),
    mSubType(src.mSubType),
    mpCallBack(src.mpCallBack)
{}

CCopasiMethod::~CCopasiMethod() {}

bool CCopasiMethod::setCallBack(CProcessReport * pCallBack)
{
  mpCallBack = pCallBack;
  return true;
}

const CCopasiTask::Type & CCopasiMethod::getType() const {return mType;}

// void CCopasiMethod::setType(const CCopasiTask::Type & type) {mType = type;}

const CCopasiMethod::SubType & CCopasiMethod::getSubType() const
  {return mSubType;}

// void CCopasiMethod::setSubType(const CCopasiMethod::SubType & subType)
// {mSubType = subType;}

//virtual
bool CCopasiMethod::isValidProblem(const CCopasiProblem * C_UNUSED(pProblem))
{
  return false; //the abstract method is not really suitable for any problem
}

void CCopasiMethod::load(CReadConfig & C_UNUSED(configBuffer),
                         CReadConfig::Mode C_UNUSED(mode))
{fatalError();}
