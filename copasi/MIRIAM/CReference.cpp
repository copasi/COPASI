// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CReference.cpp,v $
//   $Revision: 1.9.6.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/10/27 13:55:41 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CRDFGraph.h"
#include "CModelMIRIAMInfo.h"
#include "CReference.h"

#include "report/CKeyFactory.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"

CReference::CReference(const std::string & objectName,
                       const CCopasiContainer * pParent):
    CCopasiContainer(objectName, pParent, "Reference"),
    mTriplet(),
    mNodePath(),
    mKey(GlobalKeys.add("Reference", this)),
    mIdTriplet(),
    mResource(NULL)
{}

CReference::CReference(const CRDFTriplet & triplet,
                       const std::string & objectName,
                       const CCopasiContainer * pParent):
    CCopasiContainer(objectName, pParent, "Reference"),
    mTriplet(triplet),
    mNodePath(),
    mKey(GlobalKeys.add("Creator", this)),
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
                       const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mTriplet(src.mTriplet),
    mNodePath(src.mNodePath),
    mKey(GlobalKeys.add("Creator", this)),
    mIdTriplet(src.mIdTriplet),
    mResource(src.mResource)
{}

CReference::~CReference()
{
  GlobalKeys.remove(mKey);
}

const CRDFTriplet & CReference::getTriplet() const
  {return mTriplet;}

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

  if (mIdTriplet && mResource.setDisplayName(resource))
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

  if (mIdTriplet && mResource.setId(id))
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
