// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CRDFGraph.h"
#include "CCreator.h"
#include "CRDFLiteral.h"
#include "CModelMIRIAMInfo.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "copasi/report/CCopasiRootContainer.h"

// static
CCreator * CCreator::create(const CData & data)
{
  return new CCreator(data.getProperty(CData::OBJECT_NAME).toString(),
                      NO_PARENT);
}

CCreator::CCreator(const std::string & objectName,
                   const CCopasiContainer * pParent):
  CCopasiContainer(objectName, pParent, "Creator"),
  mTriplet(),
  mNodePath(),
  mKey(CCopasiRootContainer::getKeyFactory()->add("Creator", this))
{}

CCreator::CCreator(const CRDFTriplet & triplet,
                   const std::string & objectName,
                   const CCopasiContainer * pParent):
  CCopasiContainer(objectName, pParent, "Creator"),
  mTriplet(triplet),
  mNodePath(),
  mKey(CCopasiRootContainer::getKeyFactory()->add("Creator", this))
{
  if (!mTriplet)
    return;

  mNodePath = mTriplet.pObject->getPath();
}

CCreator::CCreator(const CCreator & src,
                   const CCopasiContainer * pParent):
  CCopasiContainer(src, pParent),
  mTriplet(src.mTriplet),
  mNodePath(src.mNodePath),
  mKey(CCopasiRootContainer::getKeyFactory()->add("Creator", this))
{}

CCreator::~CCreator()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
}

const CRDFTriplet & CCreator::getTriplet() const
{return mTriplet;}

const std::string & CCreator::getKey() const
{return mKey;}

const std::string & CCreator::getFamilyName() const
{return mTriplet.pObject->getFieldValue(CRDFPredicate::vcard_Family);}

const std::string & CCreator::getGivenName() const
{return mTriplet.pObject->getFieldValue(CRDFPredicate::vcard_Given);}

const std::string & CCreator::getEmail() const
{return mTriplet.pObject->getFieldValue(CRDFPredicate::vcard_EMAIL);}

const std::string & CCreator::getORG() const
{return mTriplet.pObject->getFieldValue(CRDFPredicate::vcard_Orgname);}

void CCreator::setFamilyName(const std::string & familyName)
{mTriplet.pObject->setFieldValue(familyName, CRDFPredicate::vcard_Family, mNodePath);}

void CCreator::setGivenName(const std::string & givenName)
{mTriplet.pObject->setFieldValue(givenName, CRDFPredicate::vcard_Given, mNodePath);}

void CCreator::setEmail(const std::string & Email)
{mTriplet.pObject->setFieldValue(Email, CRDFPredicate::vcard_EMAIL, mNodePath);}

void CCreator::setORG(const std::string & Orgname)
{mTriplet.pObject->setFieldValue(Orgname, CRDFPredicate::vcard_Orgname, mNodePath);}
