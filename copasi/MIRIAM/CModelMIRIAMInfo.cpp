// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModelMIRIAMInfo.cpp,v $
//   $Revision: 1.21 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/03 13:20:02 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <iostream>
#include <fstream>
#include <string>

#include "copasi.h"

#include "CModelMIRIAMInfo.h"
#include "CRDFWriter.h"
#include "CRDFLiteral.h"
#include "CRDFParser.h"
#include "CConstants.h"
#include "CRDFObject.h"
#include "CRDFPredicate.h"
#include "CRDFNode.h"

#include "model/CModelValue.h"
#include "model/CReaction.h"
#include "function/CFunction.h"
#include "report/CKeyFactory.h"

CMIRIAMInfo::CMIRIAMInfo() :
    CCopasiContainer("CMIRIAMInfoObject", NULL, "CMIRIAMInfo"),
    mCreators("Creators", this),
    mReferences("References", this),
    mModifications("Modifieds", this),
    mBiologicalDescriptions("BiologicalDescriptions", this),
    mCreatedObj(),
    mpRDFGraph(NULL),
    mTriplet(NULL, CRDFPredicate::about, NULL),
    mCreated(),
    mpCopasiObject(NULL)
{}

CMIRIAMInfo::~CMIRIAMInfo()
{pdelete(mpRDFGraph);}

CRDFGraph * CMIRIAMInfo::getRDFGraph()
{return mpRDFGraph;}

CCopasiVector <CCreator> & CMIRIAMInfo::getCreators()
{return mCreators;}

CCreator* CMIRIAMInfo::createCreator(const std::string & /* objectName */)
{
  const CRDFSubject & Subject = mpRDFGraph->getAboutNode()->getSubject();
  CRDFObject Object;
  Object.setType(CRDFObject::BLANK_NODE);
  std::string Id = mpRDFGraph->generatedBlankNodeId();
  Object.setBlankNodeId(Id);

  CRDFGraph::CTriplet Triplet =
    mpRDFGraph->addTriplet(Subject,
                           CRDFPredicate::getURI(CRDFPredicate::dcterms_creator),
                           Object);

  if (!Triplet)
    return NULL;

  CCreator * pCreator = new CCreator(Triplet);

  if (!mCreators.add(pCreator, true))
    {
      delete pCreator;
      return NULL;
    }

  return pCreator;
}

bool CMIRIAMInfo::removeCreator(const std::string & key)
{
  CCreator * pCreator =
    dynamic_cast< CCreator * >(GlobalKeys.get(key));

  if (!pCreator)
    return false;

  const CRDFGraph::CTriplet & Triplet = pCreator->getTriplet();

  if (!mpRDFGraph->removeTriplet(Triplet.pSubject,
                                 CRDFPredicate::getURI(Triplet.Predicate),
                                 Triplet.pObject))
    return false;

  return mCreators.remove(pCreator);
}

void CMIRIAMInfo::loadCreators()
{
  mCreators.cleanup();

  CRDFPredicate::ePredicateType Predicates[] =
    {
      CRDFPredicate::dcterms_creator,
      CRDFPredicate::dc_creator,
      CRDFPredicate::end
    };

  CRDFPredicate::Path Path = mTriplet.pObject->getPath();
  std::set< CRDFGraph::CTriplet > Triples;

  CRDFPredicate::ePredicateType * pPredicate = Predicates;
  std::set< CRDFGraph::CTriplet >::iterator it;
  std::set< CRDFGraph::CTriplet >::iterator end;
  for (; *pPredicate != CRDFPredicate::end; ++pPredicate)
    {
      Triples =
        mTriplet.pObject->getTripletsWithPredicate(Path, *pPredicate, mTriplet);
      it = Triples.begin();
      end = Triples.end();

      for (; it != end; ++it)
        mCreators.add(new CCreator(*it), true);
    }

  return;
}

CCopasiVector <CReference> & CMIRIAMInfo::getReferences()
{return mReferences;}

CReference* CMIRIAMInfo::createReference(const std::string & /* objectName */)
{
  const CRDFSubject & Subject = mpRDFGraph->getAboutNode()->getSubject();
  CRDFObject Object;
  Object.setType(CRDFObject::BLANK_NODE);
  std::string Id = mpRDFGraph->generatedBlankNodeId();
  Object.setBlankNodeId(Id);

  CRDFGraph::CTriplet Triplet =
    mpRDFGraph->addTriplet(Subject,
                           CRDFPredicate::getURI(CRDFPredicate::dcterms_bibliographicCitation),
                           Object);

  if (!Triplet)
    return NULL;

  CReference * pReference = new CReference(Triplet);

  if (!mReferences.add(pReference, true))
    {
      delete pReference;
      return NULL;
    }

  return pReference;
}

bool CMIRIAMInfo::removeReference(const std::string & key)
{
  CReference * pReference =
    dynamic_cast< CReference * >(GlobalKeys.get(key));

  if (!pReference)
    return false;

  const CRDFGraph::CTriplet & Triplet = pReference->getTriplet();

  if (!mpRDFGraph->removeTriplet(Triplet.pSubject,
                                 CRDFPredicate::getURI(Triplet.Predicate),
                                 Triplet.pObject))
    return false;

  return mReferences.remove(pReference);
}

void CMIRIAMInfo::loadReferences()
{
  mReferences.cleanup();

  CRDFPredicate::ePredicateType Predicates[] =
    {
      CRDFPredicate::dcterms_bibliographicCitation,
      CRDFPredicate::bqbiol_isDescribedBy,
      CRDFPredicate::bqmodel_isDescribedBy,
      CRDFPredicate::end
    };

  CRDFPredicate::Path Path = mTriplet.pObject->getPath();
  std::set< CRDFGraph::CTriplet > Triples;

  CRDFPredicate::ePredicateType * pPredicate = Predicates;
  std::set< CRDFGraph::CTriplet >::iterator it;
  std::set< CRDFGraph::CTriplet >::iterator end;
  for (; *pPredicate != CRDFPredicate::end; ++pPredicate)
    {
      Triples =
        mTriplet.pObject->getTripletsWithPredicate(Path, *pPredicate, mTriplet);
      it = Triples.begin();
      end = Triples.end();

      for (; it != end; ++it)
        mReferences.add(new CReference(*it), true);
    }

  return;
}

const std::string CMIRIAMInfo::getCreatedDT() const
  {
    if (!mCreated)
      return "";

    return mCreated.pObject->getFieldValue(CRDFPredicate::dcterms_W3CDTF, mCreated.pObject->getPath(), mCreated);
  }

void CMIRIAMInfo::setCreatedDT(const std::string& dt)
{
  std::string Date = dt;
  if (Date == "0000-00-00T00:00:00")
    Date = ""; // This causes deletion of the edge

  if (!mCreated)
    {
      const CRDFSubject & Subject = mTriplet.pObject->getSubject();
      CRDFObject Object;
      Object.setType(CRDFObject::BLANK_NODE);
      std::string Id = mpRDFGraph->generatedBlankNodeId();
      Object.setBlankNodeId(Id);

      mCreated = mpRDFGraph->addTriplet(Subject,
                                        CRDFPredicate::getURI(CRDFPredicate::dcterms_created),
                                        Object);
      // Debugging
      assert(!mCreated == false);
    }

  mCreated.pObject->setFieldValue(Date, CRDFPredicate::dcterms_W3CDTF, mCreated.pObject->getPath(), mCreated);
}

CCopasiVector <CModification> & CMIRIAMInfo::getModifications()
{return mModifications;}

CModification * CMIRIAMInfo::createModification(const std::string & /* objectName */)
{
  const CRDFSubject & Subject = mpRDFGraph->getAboutNode()->getSubject();
  CRDFObject Object;
  Object.setType(CRDFObject::BLANK_NODE);
  std::string Id = mpRDFGraph->generatedBlankNodeId();
  Object.setBlankNodeId(Id);

  CRDFGraph::CTriplet Triplet =
    mpRDFGraph->addTriplet(Subject,
                           CRDFPredicate::getURI(CRDFPredicate::dcterms_modified),
                           Object);

  if (!Triplet)
    return NULL;

  CModification * pModification = new CModification(Triplet);

  if (!mModifications.add(pModification, true))
    {
      delete pModification;
      return NULL;
    }

  return pModification;
}

bool CMIRIAMInfo::removeModification(const std::string & key)
{
  CModification * pModified =
    dynamic_cast< CModification * >(GlobalKeys.get(key));

  if (!pModified)
    return false;

  const CRDFGraph::CTriplet & Triplet = pModified->getTriplet();

  if (!mpRDFGraph->removeTriplet(Triplet.pSubject,
                                 CRDFPredicate::getURI(Triplet.Predicate),
                                 Triplet.pObject))
    return false;

  return mModifications.remove(pModified);
}

void CMIRIAMInfo::loadModifications()
{
  mModifications.cleanup();

  std::set< CRDFGraph::CTriplet > Triples =
    mTriplet.pObject->getTripletsWithPredicate(mTriplet.pObject->getPath(), CRDFPredicate::dcterms_modified, mTriplet);
  std::set< CRDFGraph::CTriplet >::iterator it = Triples.begin();
  std::set< CRDFGraph::CTriplet >::iterator end = Triples.end();

  for (; it != end; ++it)
    mModifications.add(new CModification(*it), true);

  return;
}

CCopasiVector <CBiologicalDescription> & CMIRIAMInfo::getBiologicalDescriptions()
{return mBiologicalDescriptions;}

CBiologicalDescription* CMIRIAMInfo::createBiologicalDescription()
{
  const CRDFSubject & Subject = mpRDFGraph->getAboutNode()->getSubject();
  CRDFObject Object;
  Object.setType(CRDFObject::RESOURCE);
  Object.setResource("", false);

  CRDFGraph::CTriplet Triplet = mpRDFGraph->addTriplet(Subject, "---", Object);

  if (!Triplet)
    return NULL;

  CBiologicalDescription * pBiologicalDescription =
    new CBiologicalDescription(Triplet);

  if (!mBiologicalDescriptions.add(pBiologicalDescription, true))
    {
      delete pBiologicalDescription;
      return NULL;
    }

  return pBiologicalDescription;
}

bool CMIRIAMInfo::removeBiologicalDescription(const std::string & key)
{
  CBiologicalDescription * pBiologicalDescription =
    dynamic_cast< CBiologicalDescription * >(GlobalKeys.get(key));

  if (!pBiologicalDescription)
    return false;

  const CRDFGraph::CTriplet & Triplet = pBiologicalDescription->getTriplet();

  if (!mpRDFGraph->removeTriplet(Triplet.pSubject,
                                 CRDFPredicate::getURI(Triplet.Predicate),
                                 Triplet.pObject))
    return false;

  return mBiologicalDescriptions.remove(pBiologicalDescription);
}

void CMIRIAMInfo::loadBiologicalDescriptions()
{
  mBiologicalDescriptions.cleanup();

  CRDFPredicate::ePredicateType Predicates[] =
    {
      CRDFPredicate::copasi_encodes,
      CRDFPredicate::copasi_hasPart,
      CRDFPredicate::copasi_hasVersion,
      CRDFPredicate::copasi_is,
      CRDFPredicate::copasi_isEncodedBy,
      CRDFPredicate::copasi_isHomologTo,
      CRDFPredicate::copasi_isPartOf,
      CRDFPredicate::copasi_isVersionOf,
      CRDFPredicate::copasi_occursIn,
      CRDFPredicate::bqbiol_encodes,
      CRDFPredicate::bqbiol_hasPart,
      CRDFPredicate::bqbiol_hasVersion,
      CRDFPredicate::bqbiol_is,
      CRDFPredicate::bqbiol_isEncodedBy,
      CRDFPredicate::bqbiol_isHomologTo,
      CRDFPredicate::bqbiol_isPartOf,
      CRDFPredicate::bqbiol_isVersionOf,
      CRDFPredicate::bqbiol_occursIn,
      CRDFPredicate::bqmodel_is,
      CRDFPredicate::end
    };

  CRDFPredicate::Path Path = mTriplet.pObject->getPath();
  std::set< CRDFGraph::CTriplet > Triples;

  CRDFPredicate::ePredicateType * pPredicate = Predicates;
  std::set< CRDFGraph::CTriplet >::iterator it;
  std::set< CRDFGraph::CTriplet >::iterator end;
  for (; *pPredicate != CRDFPredicate::end; ++pPredicate)
    {
      Triples =
        mTriplet.pObject->getTripletsWithPredicate(Path, *pPredicate, mTriplet);
      it = Triples.begin();
      end = Triples.end();

      for (; it != end; ++it)
        mBiologicalDescriptions.add(new CBiologicalDescription(*it), true);
    }
}

void CMIRIAMInfo::load(const std::string& key)
{
  pdelete(mpRDFGraph);

  mpCopasiObject = dynamic_cast< CCopasiObject * >(GlobalKeys.get(key));

  if (mpCopasiObject != NULL)
    {
      const std::string * pMiriamAnnotation = NULL;
      if (dynamic_cast< CModelEntity * >(mpCopasiObject))
        pMiriamAnnotation =
          &dynamic_cast< CModelEntity * >(mpCopasiObject)->getMiriamAnnotation();
      else if (dynamic_cast< CReaction * >(mpCopasiObject))
        pMiriamAnnotation =
          &dynamic_cast< CReaction * >(mpCopasiObject)->getMiriamAnnotation();
      else if (dynamic_cast< CFunction * >(mpCopasiObject))
        pMiriamAnnotation =
          &dynamic_cast< CFunction * >(mpCopasiObject)->getMiriamAnnotation();

      if (pMiriamAnnotation && *pMiriamAnnotation != "")
        mpRDFGraph = CRDFParser::graphFromXml(*pMiriamAnnotation);
    }

  if (mpRDFGraph == NULL)
    mpRDFGraph = new CRDFGraph;

  // We make sure that we always have an about node.
  mTriplet.pObject = mpRDFGraph->createAboutNode(mpCopasiObject->getKey());

  // Load the created date if set;
  CRDFPredicate::Path Path = mTriplet.pObject->getPath();
  std::set< CRDFGraph::CTriplet > Triples =
    mTriplet.pObject->getTripletsWithPredicate(Path, CRDFPredicate::dcterms_created, mTriplet);
  if (Triples.size() > 0)
    mCreated = *Triples.begin();
  else
    mCreated = CRDFGraph::CTriplet(); // This is an invalid triplet, i.e., !mCreated is true.

  loadCreators();
  loadReferences();
  loadModifications();
  loadBiologicalDescriptions();

  return;
}

bool CMIRIAMInfo::save()
{
  if (mpCopasiObject && mpRDFGraph)
    {
      std::string XML = CRDFWriter::xmlFromGraph(mpRDFGraph);

      CModelEntity * pEntity = NULL;
      CReaction * pReaction = NULL;
      CFunction * pFunction = NULL;

      if ((pEntity = dynamic_cast< CModelEntity * >(mpCopasiObject)) != NULL)
        pEntity->setMiriamAnnotation(XML, pEntity->getKey());
      else if ((pReaction = dynamic_cast< CReaction * >(mpCopasiObject)) != NULL)
        pReaction->setMiriamAnnotation(XML, pReaction->getKey());
      else if ((pFunction = dynamic_cast< CFunction * >(mpCopasiObject)) != NULL)
        pFunction->setMiriamAnnotation(XML, pFunction->getKey());
      else
        return false;

      return true;
    }

  return false;
}

const std::string & CMIRIAMInfo::getKey() const
  {
    if (mpCopasiObject != NULL)
      return mpCopasiObject->getKey();

    return CCopasiObject::getKey();
  }
