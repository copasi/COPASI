/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/Attic/CUsageRange.cpp,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:28:27 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CUsageRange
 *
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

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
