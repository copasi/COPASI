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
    CRange(name, pParent, type),
    mUsage(mObjectName)
{CONSTRUCTOR_TRACE;}

CUsageRange::CUsageRange(const CUsageRange & src,
                         const CCopasiContainer * pParent):
    CRange(src, pParent),
    mUsage(mObjectName)
{CONSTRUCTOR_TRACE;}

CUsageRange::~CUsageRange() {DESTRUCTOR_TRACE;}

void CUsageRange::cleanup() {}

void CUsageRange::load(CReadConfig & configBuffer,
                       CReadConfig::Mode mode)
{
  configBuffer.getVariable("Usage", "string", &mUsage, mode);
  CRange::load(configBuffer);
}

void CUsageRange::save(CWriteConfig & configBuffer)
{
  configBuffer.setVariable("Usage", "string", &mUsage);
  CRange::save(configBuffer);
}

void CUsageRange::setUsage(const std::string & usage)
{
  mUsage = usage;
}

const std::string & CUsageRange::getUsage() const
  {
    return mUsage;
  }

const std::string & CUsageRange::getName() const
  {
    return mUsage;
  }
