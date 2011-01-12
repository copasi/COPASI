/* Begin CVS Header
 $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CReportDefinitionVector.cpp,v $
 $Revision: 1.21.4.1 $
 $Name:  $
 $Author: shoops $
 $Date: 2011/01/12 19:05:31 $
 End CVS Header */

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// ReportDefinitionVector.cpp: implementation of the CReportDefinitionVector class.
//
//////////////////////////////////////////////////////////////////////

#include "copasi.h"
#include "CReportDefinitionVector.h"
#include "CKeyFactory.h"
#include "copasi/report/CCopasiRootContainer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportDefinitionVector::CReportDefinitionVector(const std::string & name,
    const CCopasiContainer * pParent):
    CCopasiVectorN< CReportDefinition >(name, pParent),
    mKey(CCopasiRootContainer::getKeyFactory()->add("CReportDefinitionVector", this))
{}

CReportDefinitionVector::~CReportDefinitionVector()
{
  cleanup();
}

void CReportDefinitionVector::cleanup()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
}

const std::string& CReportDefinitionVector::getKey()
{
  return mKey;
}

CReportDefinition* CReportDefinitionVector::createReportDefinition(const std::string & name, const std::string & comment)
{
  size_t i;

  for (i = 0; i < size(); i++)
    if ((*this)[i]->getObjectName() == name)
      return NULL; // duplicate name

  CReportDefinition* pNewReportDef = new CReportDefinition(name, this);
  pNewReportDef->setComment(comment);
  pNewReportDef->setObjectName(name);

  add(pNewReportDef);
  return pNewReportDef;
}

bool CReportDefinitionVector::removeReportDefinition(const std::string & key)
{
  CReportDefinition* pRep =
    dynamic_cast<CReportDefinition *>(CCopasiRootContainer::getKeyFactory()->get(key));
  size_t index = this->CCopasiVector<CReportDefinition>::getIndex(pRep);

  if (index == C_INVALID_INDEX)
    return false;

  this->CCopasiVector<CReportDefinition>::remove(index);

  //pdelete(pRep);  //TODO: propably a memory leak, may be not

  return true;
}
