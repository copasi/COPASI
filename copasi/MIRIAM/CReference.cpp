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
#include "CModelMIRIAMInfo.h"
#include "CReference.h"

#include "copasi/report/CKeyFactory.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/model/CModel.h"
#include "copasi/core/CRootContainer.h"

// static
CReference * CReference::fromData(const CData & data, CUndoObjectInterface * pParent)
{
  CReference * pReference = NULL;
  CDataContainer * pObjectParent = dynamic_cast< CDataContainer * >(pParent);

  if (pObjectParent != NULL)
    {
      CMIRIAMInfo * pMiriamInfo = dynamic_cast< CMIRIAMInfo * >(pObjectParent->getObjectAncestor("CMIRIAMInfo"));

      if (pMiriamInfo != NULL)
        {
          pReference = pMiriamInfo->createReference(data.getProperty(CData::OBJECT_NAME).toString());
          pObjectParent->remove(pReference);
        }
    }

  return pReference;
}

// virtual
void CReference::destruct()
{
  CMIRIAMInfo * pMiriamInfo = dynamic_cast< CMIRIAMInfo * >(getObjectAncestor("CMIRIAMInfo"));

  if (pMiriamInfo != NULL)
    {
      pMiriamInfo->removeReference(this);
      pMiriamInfo->save();
    }

  CDataContainer::destruct();
}

// virtual
CData CReference::toData() const
{
  CData Data = CDataContainer::toData();

  Data.addProperty(CData::MIRIAM_RESOURCE, getResource());
  Data.addProperty(CData::MIRIAM_ID, getId());
  Data.addProperty(CData::MIRIAM_DESCRIPTION, getDescription());

  Data.removeProperty(CData::OBJECT_INDEX);
  Data.addProperty(CData::OBJECT_HASH, Data.hash());

  return Data;
}

// virtual
bool CReference::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CDataContainer::applyData(data, changes);

  if (data.isSetProperty(CData::MIRIAM_RESOURCE))
    {
      setResource(data.getProperty(CData::MIRIAM_RESOURCE).toString());
    }

  if (data.isSetProperty(CData::MIRIAM_ID))
    {
      setId(data.getProperty(CData::MIRIAM_ID).toString());
    }

  if (data.isSetProperty(CData::MIRIAM_DESCRIPTION))
    {
      setDescription(data.getProperty(CData::MIRIAM_DESCRIPTION).toString());
    }

  CMIRIAMInfo * pMiriamInfo = dynamic_cast< CMIRIAMInfo * >(getObjectAncestor("CMIRIAMInfo"));

  if (pMiriamInfo != NULL)
    {
      return pMiriamInfo->save();
    }

  return success;
}

// virtual
void CReference::createUndoData(CUndoData & undoData,
                                const CUndoData::Type & type,
                                const CData & oldData,
                                const CCore::Framework & framework) const
{
  CDataContainer::createUndoData(undoData, type, oldData, framework);

  if (type != CUndoData::Type::CHANGE)
    {
      return;
    }

  undoData.addProperty(CData::MIRIAM_RESOURCE, oldData.getProperty(CData::MIRIAM_RESOURCE), getResource());
  undoData.addProperty(CData::MIRIAM_ID, oldData.getProperty(CData::MIRIAM_ID), getId());
  undoData.addProperty(CData::MIRIAM_DESCRIPTION, oldData.getProperty(CData::MIRIAM_DESCRIPTION), getDescription());
  undoData.removeProperty(CData::OBJECT_INDEX);

  if (!undoData.empty())
    {
      undoData.addProperty(CData::OBJECT_HASH, oldData.getProperty(CData::OBJECT_HASH), toData().getProperty(CData::OBJECT_HASH));
    }
}

CReference::CReference(const std::string & objectName,
                       const CDataContainer * pParent):
  CDataContainer(objectName, pParent, "Reference"),
  mTriplet(),
  mNodePath(),
  mKey(CRootContainer::getKeyFactory()->add("Reference", this)),
  mIdTriplet(),
  mResource(NULL)
{}

CReference::CReference(const CRDFTriplet & triplet,
                       const std::string & objectName,
                       const CDataContainer * pParent):
  CDataContainer(objectName, pParent, "Reference"),
  mTriplet(triplet),
  mNodePath(),
  mKey(CRootContainer::getKeyFactory()->add("Creator", this)),
  mIdTriplet(),
  mResource(NULL)
{
  if (!mTriplet)
    return;

  mNodePath = mTriplet.pObject->getPath();

  CRDFPredicate::ePredicateType Predicates[] =
  {
    CRDFPredicate::copasi_isDescribedBy,
    CRDFPredicate::bqbiol_isDescribedBy,
    CRDFPredicate::bqmodel_isDescribedBy,
    CRDFPredicate::end
  };

  std::set< CRDFTriplet > Triples;

  CRDFPredicate::ePredicateType * pPredicate = Predicates;
  std::set< CRDFTriplet >::iterator it;

  for (; *pPredicate != CRDFPredicate::end; ++pPredicate)
    {
      Triples = mTriplet.pObject->getDescendantsWithPredicate(*pPredicate);
      it = Triples.begin();

      if (it != Triples.end())
        {
          mIdTriplet = *it;
          mResource.setNode(mIdTriplet.pObject);
        }
    }
}

CReference::CReference(const CReference & src,
                       const CDataContainer * pParent):
  CDataContainer(src, pParent),
  mTriplet(src.mTriplet),
  mNodePath(src.mNodePath),
  mKey(CRootContainer::getKeyFactory()->add("Creator", this)),
  mIdTriplet(src.mIdTriplet),
  mResource(src.mResource)
{}

CReference::~CReference()
{
  CRootContainer::getKeyFactory()->remove(mKey);
}

const CRDFTriplet & CReference::getTriplet() const
{return mTriplet;}
const CMIRIAMResourceObject & CReference::getMIRIAMResourceObject() const
{
  return mResource;
}

const std::string & CReference::getKey() const
{return mKey;}

std::string CReference::getResource() const
{return mResource.getDisplayName();}

void CReference::setResource(const std::string & resource)
{
  if (!mIdTriplet)
    {
      // We create an Id triplet
      // This only adds the triplet if the resource is valid, i.e., it does not work;

      mTriplet.pObject->setFieldValue("---", CRDFPredicate::copasi_isDescribedBy, mNodePath);

      std::set< CRDFTriplet > Triples;
      std::set< CRDFTriplet >::iterator it;

      Triples = mTriplet.pObject->getDescendantsWithPredicate(CRDFPredicate::copasi_isDescribedBy);
      it = Triples.begin();

      if (it != Triples.end())
        {
          mIdTriplet = *it;
          mResource.setNode(mIdTriplet.pObject);
        }
    }

  if (mResource.setDisplayName(resource))
    mIdTriplet.pObject->getObject().setResource(mResource.getURI(), false);
}

const std::string & CReference::getId() const
{return mResource.getId();}

void CReference::setId(const std::string & id)
{
  if (!mIdTriplet)
    {
      // We create an Id triplet
      mTriplet.pObject->setFieldValue("---", CRDFPredicate::copasi_isDescribedBy, mNodePath);

      std::set< CRDFTriplet > Triples;
      std::set< CRDFTriplet >::iterator it;

      Triples = mTriplet.pObject->getDescendantsWithPredicate(CRDFPredicate::copasi_isDescribedBy);
      it = Triples.begin();

      if (it != Triples.end())
        {
          mIdTriplet = *it;
          mResource.setNode(mIdTriplet.pObject);
        }
    }

  if (mResource.setId(id))
    mIdTriplet.pObject->getObject().setResource(mResource.getURI(), false);
}

std::string CReference::getURI() const
{return mResource.getURI();}

const std::string & CReference::getDescription() const
{return mTriplet.pObject->getFieldValue(CRDFPredicate::dcterms_description);}

void CReference::setDescription(const std::string & description)
{
  mTriplet.pObject->setFieldValue(description, CRDFPredicate::dcterms_description, mNodePath);
}

void CReference::clearInvalidEntries()
{
  // Empty descriptions are handled automatically since setFieldValue removes
  // a triplet if the value is an empty string.

  // Handle invalid resource
  if (!mResource.isValid() && mIdTriplet)
    {
      // We remove the Id triplet
      mTriplet.pObject->setFieldValue("", CRDFPredicate::copasi_isDescribedBy, mNodePath);
      mIdTriplet = CRDFTriplet(); // This makes it invalid.

      mResource.setURI("---");
    }
}
