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
CModification * CModification::fromData(const CData & data)
{
  return new CModification(data.getProperty(CData::OBJECT_NAME).toString(),
                           NO_PARENT);
}

// virtual
CData CModification::toData() const
{
  CData Data = CDataContainer::toData();

  Data.addProperty(CData::DATE, getDate());

  return Data;
}

// virtual
bool CModification::applyData(const CData & data)
{
  bool success = CDataContainer::applyData(data);

  if (data.isSetProperty(CData::DATE))
    {
      setDate(data.getProperty(CData::DATE).toString());
    }

  return success;
}

CModification::CModification(const std::string & objectName,
                             const CDataContainer * pParent):
  CDataContainer(objectName, pParent, "Modification"),
  mTriplet(),
  mNodePath(),
  mKey(CRootContainer::getKeyFactory()->add("Modification", this))
{}

CModification::CModification(const CRDFTriplet & triplet,
                             const std::string & objectName,
                             const CDataContainer * pParent):
  CDataContainer(objectName, pParent, "Modification"),
  mTriplet(triplet),
  mNodePath(),
  mKey(CRootContainer::getKeyFactory()->add("Modification", this))
{
  if (!mTriplet)
    return;

  mNodePath = mTriplet.pObject->getPath();
}

CModification::CModification(const CModification & src,
                             const CDataContainer * pParent):
  CDataContainer(src, pParent),
  mTriplet(src.mTriplet),
  mNodePath(src.mNodePath),
  mKey(CRootContainer::getKeyFactory()->add("Modification", this))
{}

CModification::~CModification()
{
  CRootContainer::getKeyFactory()->remove(mKey);
}

const CRDFTriplet & CModification::getTriplet() const
{return mTriplet;}

const std::string & CModification::getKey() const
{return mKey;}

void CModification::setDate(const std::string & date)
{mTriplet.pObject->setFieldValue(date, CRDFPredicate::dcterms_W3CDTF, mNodePath);}

const std::string & CModification::getDate() const
{return mTriplet.pObject->getFieldValue(CRDFPredicate::dcterms_W3CDTF);}
