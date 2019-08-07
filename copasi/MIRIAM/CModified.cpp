// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include "CRDFGraph.h"
#include "CCreator.h"
#include "CRDFLiteral.h"
#include "CModelMIRIAMInfo.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"

// static
CModification * CModification::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  CModification * pModification = NULL;
  CDataContainer * pObjectParent = dynamic_cast< CDataContainer * >(pParent);

  if (pObjectParent != NULL)
    {
      CMIRIAMInfo * pMiriamInfo = dynamic_cast< CMIRIAMInfo * >(pObjectParent->getObjectAncestor("CMIRIAMInfo"));

      if (pMiriamInfo != NULL)
        {
          pModification = pMiriamInfo->createModification(data.getProperty(CData::OBJECT_NAME).toString());
          pObjectParent->remove(pModification);
        }
    }

  return pModification;
}

// virtual
void CModification::destruct()
{
  CMIRIAMInfo * pMiriamInfo = dynamic_cast< CMIRIAMInfo * >(getObjectAncestor("CMIRIAMInfo"));

  if (pMiriamInfo != NULL)
    {
      pMiriamInfo->removeModification(this);
      pMiriamInfo->save();
    }

  CDataContainer::destruct();
}

// virtual
CData CModification::toData() const
{
  CData Data = CDataContainer::toData();

  Data.addProperty(CData::DATE, getDate());

  Data.removeProperty(CData::OBJECT_INDEX);
  Data.addProperty(CData::OBJECT_HASH, Data.hash());

  return Data;
}

// virtual
bool CModification::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CDataContainer::applyData(data, changes);

  if (data.isSetProperty(CData::DATE))
    {
      setDate(data.getProperty(CData::DATE).toString());
    }

  CMIRIAMInfo * pMiriamInfo = dynamic_cast< CMIRIAMInfo * >(getObjectAncestor("CMIRIAMInfo"));

  if (pMiriamInfo != NULL)
    {
      return pMiriamInfo->save();
    }

  return success;
}

// virtual
void CModification::createUndoData(CUndoData & undoData,
                                   const CUndoData::Type & type,
                                   const CData & oldData,
                                   const CCore::Framework & framework) const
{
  CDataContainer::createUndoData(undoData, type, oldData, framework);

  if (type != CUndoData::Type::CHANGE)
    {
      return;
    }

  undoData.addProperty(CData::DATE, oldData.getProperty(CData::DATE), getDate());
  undoData.removeProperty(CData::OBJECT_INDEX);

  if (!undoData.empty())
    {
      undoData.addProperty(CData::OBJECT_HASH, oldData.getProperty(CData::OBJECT_HASH), toData().getProperty(CData::OBJECT_HASH));
    }
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
