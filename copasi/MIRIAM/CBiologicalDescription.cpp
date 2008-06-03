// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CBiologicalDescription.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/03 13:20:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CRDFNode.h"

#include "CModelMIRIAMInfo.h"
#include "CReference.h"

#include "report/CKeyFactory.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"

CBiologicalDescription::CBiologicalDescription(const std::string & objectName,
    const CCopasiContainer * pParent):
    CCopasiContainer(objectName, pParent, "BiologicalDescription"),
    mTriplet(),
    mKey(GlobalKeys.add("BiologicalDescription", this)),
    mResource(NULL)
{}

CBiologicalDescription::CBiologicalDescription(const CRDFGraph::CTriplet & triplet,
    const std::string & objectName,
    const CCopasiContainer * pParent):
    CCopasiContainer(objectName, pParent, "BiologicalDescription"),
    mTriplet(triplet),
    mKey(GlobalKeys.add("BiologicalDescription", this)),
    mResource(mTriplet.pObject)
{}

CBiologicalDescription::CBiologicalDescription(const CBiologicalDescription & src,
    const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mTriplet(src.mTriplet),
    mKey(GlobalKeys.add("Creator", this)),
    mResource(src.mResource)
{}

CBiologicalDescription::~CBiologicalDescription()
{
  GlobalKeys.remove(mKey);
}

const CRDFGraph::CTriplet & CBiologicalDescription::getTriplet() const
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
  // Remove the edge with the predicate without destroying any objects.
  mTriplet.pSubject->removeEdgeInternal(CRDFEdge(mTriplet.Predicate, mTriplet.pObject));

  // Set the new predicate
  mTriplet.Predicate = CRDFPredicate::getPredicateFromDisplayName(predicate);

  // Add the edge with the new predicate without any object creation.
  mTriplet.pSubject->addEdgeInternal(CRDFEdge(mTriplet.Predicate, mTriplet.pObject));
}

void CBiologicalDescription::setResource(const std::string & resource)
{
  mResource = CMIRIAMResource(resource, mResource.getId());
  mTriplet.pObject->getObject().setResource(mResource.getURI(), false);
}

void CBiologicalDescription::setId(const std::string & id)
{
  mResource.setId(id);
  mTriplet.pObject->getObject().setResource(mResource.getURI(), false);
}
