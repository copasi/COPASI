/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/CPlotSpecification.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/07/06 14:45:05 $
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
    "Enhanced Newton",
    "Deterministic (LSODA)",
    "Stochastic",
    "Hybrid",
    ""
  };

const char* CCopasiMethod::XMLSubType[] =
  {
    "NotSet",
    "RandomSearch",
    "RandomSearch(PVM)",
    "SimulatedAnnealing",
    "EnhancedNewton",
    "Deterministic(LSODA)",
    "Stochastic",
    "Hybrid",
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
    mSubType(unset)
{setName(SubTypeName[mType]);}

CCopasiMethod::CCopasiMethod(const CCopasiTask::Type & type,
                             const CCopasiMethod::SubType & subType,
                             const CCopasiContainer * pParent):
    CCopasiParameterGroup(TypeName[type], pParent, "Method"),
    mType(type),
    mSubType(subType)
{setName(SubTypeName[mSubType]);}

CCopasiMethod::CCopasiMethod(const CCopasiMethod & src,
                             const CCopasiContainer * pParent):
    CCopasiParameterGroup(src, pParent),
    mType(src.mType),
    mSubType(src.mSubType)
{}

CCopasiMethod::~CCopasiMethod() {}

const CCopasiTask::Type & CCopasiMethod::getType() const {return mType;}

// void CCopasiMethod::setType(const CCopasiTask::Type & type) {mType = type;}

const CCopasiMethod::SubType & CCopasiMethod::getSubType() const
  {return mSubType;}

// void CCopasiMethod::setSubType(const CCopasiMethod::SubType & subType)
// {mSubType = subType;}

void CCopasiMethod::load(CReadConfig & C_UNUSED(configBuffer),
                         CReadConfig::Mode C_UNUSED(mode))
{fatalError();}
