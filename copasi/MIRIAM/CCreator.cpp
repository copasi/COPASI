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

#include "CopasiDataModel/CDataModel.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"

// static
CCreator * CCreator::fromData(const CData & data)
{
  return new CCreator(data.getProperty(CData::OBJECT_NAME).toString(),
                      NO_PARENT);
}

// virtual
CData CCreator::toData() const
{
  CData Data = CDataContainer::toData();

  Data.addProperty(CData::GIVEN_NAME, getGivenName());
  Data.addProperty(CData::FAMILY_NAME, getFamilyName());
  Data.addProperty(CData::EMAIL, getEmail());
  Data.addProperty(CData::ORGANIZATION, getORG());

  return Data;
}

// virtual
bool CCreator::applyData(const CData & data, CUndoData::ChangeSet & changes)
{
  bool success = CDataContainer::applyData(data, changes);

  if (data.isSetProperty(CData::GIVEN_NAME))
    {
      setGivenName(data.getProperty(CData::GIVEN_NAME).toString());
    }

  if (data.isSetProperty(CData::FAMILY_NAME))
    {
      setFamilyName(data.getProperty(CData::FAMILY_NAME).toString());
    }

  if (data.isSetProperty(CData::EMAIL))
    {
      setEmail(data.getProperty(CData::EMAIL).toString());
    }

  if (data.isSetProperty(CData::ORGANIZATION))
    {
      setORG(data.getProperty(CData::ORGANIZATION).toString());
    }

  return success;
}

CCreator::CCreator(const std::string & objectName,
                   const CDataContainer * pParent):
  CDataContainer(objectName, pParent, "Creator"),
  mTriplet(),
  mNodePath(),
  mKey(CRootContainer::getKeyFactory()->add("Creator", this))
{}

CCreator::CCreator(const CRDFTriplet & triplet,
                   const std::string & objectName,
                   const CDataContainer * pParent):
  CDataContainer(objectName, pParent, "Creator"),
  mTriplet(triplet),
  mNodePath(),
  mKey(CRootContainer::getKeyFactory()->add("Creator", this))
{
  if (!mTriplet)
    return;

  mNodePath = mTriplet.pObject->getPath();
}

CCreator::CCreator(const CCreator & src,
                   const CDataContainer * pParent):
  CDataContainer(src, pParent),
  mTriplet(src.mTriplet),
  mNodePath(src.mNodePath),
  mKey(CRootContainer::getKeyFactory()->add("Creator", this))
{}

CCreator::~CCreator()
{
  CRootContainer::getKeyFactory()->remove(mKey);
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
