/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/Attic/CUsageRange.cpp,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/11/24 14:51:29 $
   End CVS Header */

/**
 * CUsageRange
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CUsageRange.h"

CUsageRange::CUsageRange(const std::string & name,
                         const CCopasiContainer * pParent,
                         const std::string & type):
    CRange(name, pParent, type)
{CONSTRUCTOR_TRACE;}

CUsageRange::CUsageRange(const CUsageRange & src,
                         const CCopasiContainer * pParent):
    CRange(src, pParent)
{CONSTRUCTOR_TRACE;}

CUsageRange::~CUsageRange() {DESTRUCTOR_TRACE;}

/*void CUsageRange::load(CReadConfig & configBuffer,
                       CReadConfig::Mode mode)
{
  std::string tmp;
  configBuffer.getVariable("Usage", "string", &tmp, mode);
  setObjectName(tmp);
  CRange::load(configBuffer);
}*/

bool CUsageRange::setUsage(const std::string & usage)
{
  return setObjectName(usage);
}

const std::string & CUsageRange::getUsage() const
  {
    return getObjectName();
  }

/*const std::string & CUsageRange::getName() const
  {
    return getObjectName();
  }*/
