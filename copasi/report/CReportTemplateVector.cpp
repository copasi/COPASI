// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// ReportTemplateVector.cpp: implementation of the CReportTemplateVector class.
//
//////////////////////////////////////////////////////////////////////

#include "copasi.h"
#include "CReportTemplateVector.h"
#include "CKeyFactory.h"
#include "copasi/report/CCopasiRootContainer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportTemplateVector::CReportTemplateVector(const std::string & name,
    const CCopasiContainer * pParent):
    CCopasiVectorN< CReportTemplate >(name, pParent),
    mKey(CCopasiRootContainer::getKeyFactory()->add("CReportTemplateVector", this))
{}

CReportTemplateVector::~CReportTemplateVector()
{
  cleanup();
}

void CReportTemplateVector::cleanup()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
}

const std::string & CReportTemplateVector::getKey() const
{
  return mKey;
}

CReportTemplate* CReportTemplateVector::createReportTemplate(const std::string & name, const std::string & comment)
{
  size_t i;

  for (i = 0; i < size(); i++)
    if ((*this)[i]->getObjectName() == name)
      return NULL; // duplicate name

  CReportTemplate* pNewReportDef = new CReportTemplate(name, this);
  pNewReportDef->setComment(comment);
  pNewReportDef->setObjectName(name);

  add(pNewReportDef);
  return pNewReportDef;
}

bool CReportTemplateVector::removeReportTemplate(const std::string & key)
{
  CReportTemplate* pRep =
    dynamic_cast<CReportTemplate *>(CCopasiRootContainer::getKeyFactory()->get(key));
  size_t index = this->CCopasiVector<CReportTemplate>::getIndex(pRep);

  if (index == C_INVALID_INDEX)
    return false;

  this->CCopasiVector<CReportTemplate>::remove(index);

  //pdelete(pRep);  //TODO: propably a memory leak, may be not

  return true;
}
