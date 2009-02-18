// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CBiologicalDescription.cpp,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2009/02/18 20:53:03 $
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
#include "copasi/report/CCopasiRootContainer.h"

CBiologicalDescription::CBiologicalDescription(const std::string & objectName,
    const CCopasiContainer * pParent):
    CCopasiContainer(objectName, pParent, "BiologicalDescription"),
    mTriplet(),
    mKey(CCopasiRootContainer::Root->getKeyFactory()->add("BiologicalDescription", this)),
    mResource(NULL)
{}

CBiologicalDescription::CBiologicalDescription(const CRDFTriplet & triplet,
    const std::string & objectName,
    const CCopasiContainer * pParent):
    CCopasiContainer(objectName, pParent, "BiologicalDescription"),
    mTriplet(triplet),
    mKey(CCopasiRootContainer::Root->getKeyFactory()->add("BiologicalDescription", this)),
    mResource(mTriplet.pObject)
{}

CBiologicalDescription::CBiologicalDescription(const CBiologicalDescription & src,
    const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mTriplet(src.mTriplet),
    mKey(CCopasiRootContainer::Root->getKeyFactory()->add("Creator", this)),
    mResource(src.mResource)
{}

CBiologicalDescription::~CBiologicalDescription()
{
  CCopasiRootContainer::Root->getKeyFactory()->remove(mKey);
}

const CRDFTriplet & CBiologicalDescription::getTriplet() const
  {return mTriplet;}

const std::string & CBiologicalDescription::getKey() const
  {return mKey;}

std::string CBiologicalDescription::getPredicate() const
  {return CRDFPredicate::getDisplayName(mTriplet.Predicate);}

std::string CBiologicalDescription::getResource() const
  {return mResource.getDisplayName();}

const std::string & CBiologicalDescription::getId() const
  {return mResource.getId();}

void CBiologicalDescription::setPredicate(const std::string & predicate)
{
  CRDFPredicate Predicate(CRDFPredicate::getPredicateFromDisplayName(predicate));

  if (Predicate == mTriplet.Predicate)
    return;

  // Add the edge with the new predicate without any object creation.
  mTriplet.pSubject->addEdge(Predicate, mTriplet.pObject);

  // Remove the edge with the predicate without destroying any objects.
  mTriplet.pSubject->removeEdge(mTriplet.Predicate, mTriplet.pObject);

  // Set the new predicate
  mTriplet.Predicate = Predicate;
}

void CBiologicalDescription::setResource(const std::string & resource)
{
  mResource.setDisplayName(resource);
  mTriplet.pObject->getObject().setResource(mResource.getURI(), false);
}

void CBiologicalDescription::setId(const std::string & id)
{
  mResource.setId(id);
  mTriplet.pObject->getObject().setResource(mResource.getURI(), false);
}

std::string CBiologicalDescription::getURI() const
  {return mResource.getURI();}

void CBiologicalDescription::clearInvalidEntries()
{
  if ((mTriplet.Predicate == CRDFPredicate::unknown &&
       mTriplet.Predicate.getURI() == "") ||
      !mResource.isValid())
    {
      // Remove the edge with the predicate and object.
      mTriplet.pSubject->removeEdge(mTriplet.Predicate, mTriplet.pObject);
    }
}
