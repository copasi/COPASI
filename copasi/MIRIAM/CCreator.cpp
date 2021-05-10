// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"

#include "copasi/MIRIAM/CRDFGraph.h"
#include "copasi/MIRIAM/CCreator.h"
#include "copasi/MIRIAM/CRDFLiteral.h"
#include "copasi/MIRIAM/CModelMIRIAMInfo.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"

// static
CCreator * CCreator::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  CCreator * pCreator = NULL;
  CDataContainer * pObjectParent = dynamic_cast< CDataContainer * >(pParent);

  if (pObjectParent != NULL)
    {
      CMIRIAMInfo * pMiriamInfo = dynamic_cast< CMIRIAMInfo * >(pObjectParent->getObjectAncestor("CMIRIAMInfo"));

      if (pMiriamInfo != NULL)
        {
          pCreator = pMiriamInfo->createCreator(data.getProperty(CData::OBJECT_NAME).toString());
          pObjectParent->remove(pCreator);
        }
    }

  return pCreator;
}

// virtual
void CCreator::destruct()
{
  CMIRIAMInfo * pMiriamInfo = dynamic_cast< CMIRIAMInfo * >(getObjectAncestor("CMIRIAMInfo"));

  if (pMiriamInfo != NULL)
    {
      pMiriamInfo->removeCreator(this);
      pMiriamInfo->save();
    }

  CDataContainer::destruct();
}

// virtual
CData CCreator::toData() const
{
  CData Data = CDataContainer::toData();

  Data.addProperty(CData::GIVEN_NAME, getGivenName());
  Data.addProperty(CData::FAMILY_NAME, getFamilyName());
  Data.addProperty(CData::EMAIL, getEmail());
  Data.addProperty(CData::ORGANIZATION, getORG());

  Data.removeProperty(CData::OBJECT_INDEX);
  Data.addProperty(CData::OBJECT_HASH, Data.hash());

  return Data;
}

// virtual
bool CCreator::applyData(const CData & data, CUndoData::CChangeSet & changes)
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

  CMIRIAMInfo * pMiriamInfo = dynamic_cast< CMIRIAMInfo * >(getObjectAncestor("CMIRIAMInfo"));

  if (pMiriamInfo != NULL)
    {
      return pMiriamInfo->save();
    }

  return success;
}

// virtual
void CCreator::createUndoData(CUndoData & undoData,
                              const CUndoData::Type & type,
                              const CData & oldData,
                              const CCore::Framework & framework) const
{
  CDataContainer::createUndoData(undoData, type, oldData, framework);

  if (type != CUndoData::Type::CHANGE)
    {
      return;
    }

  undoData.addProperty(CData::GIVEN_NAME, oldData.getProperty(CData::GIVEN_NAME), getGivenName());
  undoData.addProperty(CData::FAMILY_NAME, oldData.getProperty(CData::FAMILY_NAME), getFamilyName());
  undoData.addProperty(CData::EMAIL, oldData.getProperty(CData::EMAIL), getEmail());
  undoData.addProperty(CData::ORGANIZATION, oldData.getProperty(CData::ORGANIZATION), getORG());
  undoData.removeProperty(CData::OBJECT_INDEX);

  if (!undoData.empty())
    {
      undoData.addProperty(CData::OBJECT_HASH, oldData.getProperty(CData::OBJECT_HASH), toData().getProperty(CData::OBJECT_HASH));
    }
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
