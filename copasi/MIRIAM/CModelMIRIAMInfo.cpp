// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <iostream>
#include <fstream>
#include <string>

#include "copasi/copasi.h"

#include "copasi/MIRIAM/CModelMIRIAMInfo.h"
#include "copasi/MIRIAM/CRDFWriter.h"
#include "copasi/MIRIAM/CRDFLiteral.h"
#include "copasi/MIRIAM/CRDFParser.h"
#include "copasi/MIRIAM/CConstants.h"
#include "copasi/MIRIAM/CRDFObject.h"
#include "copasi/MIRIAM/CRDFPredicate.h"
#include "copasi/MIRIAM/CRDFGraph.h"

#include "copasi/commandline/CConfigurationFile.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CEvent.h"
#include "copasi/model/CReaction.h"
#include "copasi/function/CFunction.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"

// virtual
CData CMIRIAMInfo::toData() const
{
  CData Data = CDataContainer::toData();

  // We need to add the object parent
  Data.addProperty(CData::DATE, getCreatedDT());

  return Data;
}

// virtual
bool CMIRIAMInfo::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  bool success = CDataContainer::applyData(data, changes);

  if (data.isSetProperty(CData::DATE))
    {
      setCreatedDT(data.getProperty(CData::DATE).toString());
    }

  success &= save();

  return success;
}

// virtual
void CMIRIAMInfo::createUndoData(CUndoData & undoData,
                                 const CUndoData::Type & type,
                                 const CData & oldData,
                                 const CCore::Framework & framework) const
{
  CDataContainer::createUndoData(undoData, type, oldData, framework);

  if (type != CUndoData::Type::CHANGE)
    {
      return;
    }

  undoData.addProperty(CData::DATE, oldData.getProperty(CData::DATE), getCreatedDT());
}

CMIRIAMInfo::CMIRIAMInfo() :
  CDataContainer("CMIRIAMInfoObject", NULL, "CMIRIAMInfo"),
  mpObject(NULL),
  mpAnnotation(NULL),
  mCreators("Creators", this),
  mReferences("References", this),
  mModifications("Modifications", this),
  mBiologicalDescriptions("BiologicalDescriptions", this),
  mCreatedObj(),
  mpRDFGraph(NULL),
  mTriplet(NULL, CRDFPredicate::about, NULL),
  mCreated()
{}

CMIRIAMInfo::~CMIRIAMInfo()
{
  CAnnotation::freeMiriamInfo(mpObject);

  pdelete(mpRDFGraph);
}

CRDFGraph * CMIRIAMInfo::getRDFGraph()
{return mpRDFGraph;}

bool CMIRIAMInfo::empty() const
{
  return (mpRDFGraph == NULL || mpRDFGraph->empty());
}

CDataVector <CCreator> & CMIRIAMInfo::getCreators()
{return mCreators;}

const CDataVector <CCreator> & CMIRIAMInfo::getCreators() const
{return mCreators;}

CCreator* CMIRIAMInfo::createCreator(const std::string & /* objectName */)
{
  const CRDFSubject & Subject = mpRDFGraph->getAboutNode()->getSubject();
  CRDFObject Object;
  Object.setType(CRDFObject::BLANK_NODE);
  std::string Id = mpRDFGraph->generatedNodeId();
  Object.setBlankNodeId(Id);

  CRDFTriplet Triplet =
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

bool CMIRIAMInfo::removeCreator(CCreator * pCreator)
{
  if (!pCreator)
    return false;

  const CRDFTriplet & Triplet = pCreator->getTriplet();

  mpRDFGraph->removeTriplet(Triplet.pSubject,
                            CRDFPredicate::getURI(Triplet.Predicate),
                            Triplet.pObject);

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
  std::set< CRDFTriplet > Triples;

  CRDFPredicate::ePredicateType * pPredicate = Predicates;
  std::set< CRDFTriplet >::iterator it;
  std::set< CRDFTriplet >::iterator end;

  for (; *pPredicate != CRDFPredicate::end; ++pPredicate)
    {
      Triples =
        mTriplet.pObject->getDescendantsWithPredicate(*pPredicate);
      it = Triples.begin();
      end = Triples.end();

      for (; it != end; ++it)
        mCreators.add(new CCreator(*it), true);
    }

  return;
}

CCreator * CMIRIAMInfo::addDefaultCreator(bool force)
{
  if ((!mCreators.empty() || !getCreatedDT().empty()) && !force)
    return NULL;

  CConfigurationFile * pConfig = CRootContainer::getConfiguration();

  if ((pConfig->getCurrentAuthorGivenName().empty() || pConfig->getCurrentAuthorGivenName() == "Anonymous")
      && (pConfig->getCurrentAuthorGivenName().empty() || pConfig->getCurrentAuthorFamilyName() == "Anonymous")
      && (pConfig->getCurrentAuthorEmail().empty() || pConfig->getCurrentAuthorEmail() == "An.other@mailinator.com")
      && pConfig->getCurrentAuthorOrganization().empty())
    return NULL;

  CCreator * pCreator = createCreator("");

  if (pConfig->getCurrentAuthorGivenName() != "Anonymous" && !pConfig->getCurrentAuthorGivenName().empty())
    pCreator->setGivenName(pConfig->getCurrentAuthorGivenName());

  if (pConfig->getCurrentAuthorFamilyName() != "Anonymous" && !pConfig->getCurrentAuthorGivenName().empty())
    pCreator->setFamilyName(pConfig->getCurrentAuthorFamilyName());

  if (pConfig->getCurrentAuthorEmail() != "An.other@mailinator.com" && !pConfig->getCurrentAuthorEmail().empty())
    pCreator->setEmail(pConfig->getCurrentAuthorEmail());

  if (!pConfig->getCurrentAuthorOrganization().empty())
    pCreator->setORG(pConfig->getCurrentAuthorOrganization());

  return pCreator;
}

CDataVector <CReference> & CMIRIAMInfo::getReferences()
{return mReferences;}

const CDataVector <CReference> & CMIRIAMInfo::getReferences() const
{return mReferences;}

CReference* CMIRIAMInfo::createReference(const std::string & /* objectName */)
{
  const CRDFSubject & Subject = mpRDFGraph->getAboutNode()->getSubject();
  CRDFObject Object;
  Object.setType(CRDFObject::BLANK_NODE);
  std::string Id = mpRDFGraph->generatedNodeId();
  Object.setBlankNodeId(Id);

  CRDFTriplet Triplet =
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

bool CMIRIAMInfo::removeReference(CReference * pReference)
{
  if (!pReference)
    return false;

  const CRDFTriplet & Triplet = pReference->getTriplet();

  mpRDFGraph->removeTriplet(Triplet.pSubject,
                            CRDFPredicate::getURI(Triplet.Predicate),
                            Triplet.pObject);

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
  std::set< CRDFTriplet > Triples;

  CRDFPredicate::ePredicateType * pPredicate = Predicates;
  std::set< CRDFTriplet >::iterator it;
  std::set< CRDFTriplet >::iterator end;

  for (; *pPredicate != CRDFPredicate::end; ++pPredicate)
    {
      Triples = mTriplet.pObject->getDescendantsWithPredicate(*pPredicate);
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

  return mCreated.pObject->getFieldValue(CRDFPredicate::dcterms_W3CDTF);
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
      std::string Id = mpRDFGraph->generatedNodeId();
      Object.setBlankNodeId(Id);

      mCreated = mpRDFGraph->addTriplet(Subject,
                                        CRDFPredicate::getURI(CRDFPredicate::dcterms_created),
                                        Object);
      // Debugging
      assert(!mCreated == false);
    }

  mCreated.pObject->setFieldValue(Date, CRDFPredicate::dcterms_W3CDTF, mCreated.pObject->getPath());
}

bool CMIRIAMInfo::addDefaultCreatedDT()
{
  if (!getCreatedDT().empty())
    return false;

  setCreatedDT(UTCTimeStamp());

  return true;
}

CDataVector <CModification> & CMIRIAMInfo::getModifications()
{return mModifications;}

const CDataVector <CModification> & CMIRIAMInfo::getModifications() const
{return mModifications;}

CModification * CMIRIAMInfo::createModification(const std::string& dateTime)
{
  const CRDFSubject & Subject = mpRDFGraph->getAboutNode()->getSubject();
  CRDFObject Object;
  Object.setType(CRDFObject::BLANK_NODE);
  std::string Id = mpRDFGraph->generatedNodeId();
  Object.setBlankNodeId(Id);

  CRDFTriplet Triplet =
    mpRDFGraph->addTriplet(Subject,
                           CRDFPredicate::getURI(CRDFPredicate::dcterms_modified),
                           Object);

  if (!Triplet)
    return NULL;

  CModification * pModification = new CModification(Triplet);

  if (dateTime.size())
    pModification->setDate(dateTime);

  if (!mModifications.add(pModification, true))
    {
      delete pModification;
      return NULL;
    }

  return pModification;
}

bool CMIRIAMInfo::removeModification(CModification * pModified)
{
  if (!pModified)
    return false;

  const CRDFTriplet & Triplet = pModified->getTriplet();

  mpRDFGraph->removeTriplet(Triplet.pSubject,
                            CRDFPredicate::getURI(Triplet.Predicate),
                            Triplet.pObject);

  return mModifications.remove(pModified);
}

void CMIRIAMInfo::loadModifications()
{
  mModifications.cleanup();

  std::set< CRDFTriplet > Triples =
    mTriplet.pObject->getDescendantsWithPredicate(CRDFPredicate::dcterms_modified);
  std::set< CRDFTriplet >::iterator it = Triples.begin();
  std::set< CRDFTriplet >::iterator end = Triples.end();

  for (; it != end; ++it)
    mModifications.add(new CModification(*it), true);

  return;
}

CDataVector <CBiologicalDescription> & CMIRIAMInfo::getBiologicalDescriptions()
{return mBiologicalDescriptions;}

const CDataVector <CBiologicalDescription> & CMIRIAMInfo::getBiologicalDescriptions() const
{return mBiologicalDescriptions;}

CBiologicalDescription* CMIRIAMInfo::createBiologicalDescription()
{
  const CRDFSubject & Subject = mpRDFGraph->getAboutNode()->getSubject();
  CRDFObject Object;
  Object.setType(CRDFObject::RESOURCE);
  Object.setResource("", false);

  CRDFTriplet Triplet = mpRDFGraph->addTriplet(Subject, std::string("---"), Object);

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

bool CMIRIAMInfo::removeBiologicalDescription(CBiologicalDescription * pBiologicalDescription)
{
  if (!pBiologicalDescription)
    return false;

  const CRDFTriplet & Triplet = pBiologicalDescription->getTriplet();

  mpRDFGraph->removeTriplet(Triplet.pSubject,
                            Triplet.Predicate,//CRDFPredicate::getURI(Triplet.Predicate),
                            Triplet.pObject);

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
    CRDFPredicate::copasi_isDescribedBy,
    CRDFPredicate::copasi_isEncodedBy,
    CRDFPredicate::copasi_isHomologTo,
    CRDFPredicate::copasi_isPartOf,
    CRDFPredicate::copasi_isVersionOf,
    CRDFPredicate::copasi_occursIn,
    CRDFPredicate::bqbiol_encodes,
    CRDFPredicate::bqbiol_hasPart,
    CRDFPredicate::bqbiol_hasProperty,
    CRDFPredicate::bqbiol_hasVersion,
    CRDFPredicate::bqbiol_is,
    CRDFPredicate::bqbiol_isEncodedBy,
    CRDFPredicate::bqbiol_isHomologTo,
    CRDFPredicate::bqbiol_isPartOf,
    CRDFPredicate::bqbiol_isPropertyOf,
    CRDFPredicate::bqbiol_isVersionOf,
    CRDFPredicate::bqbiol_occursIn,
    CRDFPredicate::bqbiol_hasTaxon,
    CRDFPredicate::bqmodel_is,
    CRDFPredicate::bqmodel_isDerivedFrom,
    CRDFPredicate::bqmodel_isInstanceOf,
    CRDFPredicate::bqmodel_hasInstance,
    CRDFPredicate::unknown,
    CRDFPredicate::end
  };

  CRDFPredicate::Path Path = mTriplet.pObject->getPath();
  std::set< CRDFTriplet > Triples;

  CRDFPredicate::ePredicateType * pPredicate = Predicates;
  std::set< CRDFTriplet >::iterator it;
  std::set< CRDFTriplet >::iterator end;

  for (; *pPredicate != CRDFPredicate::end; ++pPredicate)
    {
      Triples = mTriplet.pObject->getDescendantsWithPredicate(*pPredicate);
      it = Triples.begin();
      end = Triples.end();

      for (; it != end; ++it)
        {
          if (!CMIRIAMResources::isCitation(it->pObject->getObject().getResource()))
            {
              mBiologicalDescriptions.add(new CBiologicalDescription(*it), true);
            }
        }
    }
}

void CMIRIAMInfo::load(CDataContainer * pObject)
{
  pdelete(mpRDFGraph);

  pObject->add(this, true);
  mpObject = getObjectParent();

  mpAnnotation = CAnnotation::castObject(mpObject);

  if (mpAnnotation != NULL &&
      !mpAnnotation->getMiriamAnnotation().empty())
    {
      mpRDFGraph = CRDFParser::graphFromXml(mpAnnotation->getMiriamAnnotation());
    }

  if (mpRDFGraph == NULL)
    mpRDFGraph = new CRDFGraph;

  // We make sure that we always have an about node.

  if (mpObject != NULL)
    mTriplet.pObject = mpRDFGraph->createAboutNode(mpObject->getKey());
  else
    mTriplet.pObject = mpRDFGraph->createAboutNode("");

  // Load the created date if set;
  CRDFPredicate::Path Path = mTriplet.pObject->getPath();
  std::set< CRDFTriplet > Triples =
    mTriplet.pObject->getDescendantsWithPredicate(CRDFPredicate::dcterms_created);

  if (Triples.size() > 0)
    mCreated = *Triples.begin();
  else
    mCreated = CRDFTriplet(); // This is an invalid triplet, i.e., !mCreated is true.

  loadCreators();
  loadReferences();
  loadModifications();
  loadBiologicalDescriptions();

  return;
}

bool CMIRIAMInfo::save()
{
  if (mpAnnotation && mpRDFGraph)
    {
      mpRDFGraph->clean();
      mpRDFGraph->updateNamespaces();

      mpAnnotation->setMiriamAnnotation(CRDFWriter::xmlFromGraph(mpRDFGraph), mpAnnotation->getKey(), mpAnnotation->getKey());

      return true;
    }

  return false;
}

// virtual
const std::string & CMIRIAMInfo::getKey() const
{
  if (mpAnnotation != NULL)
    {
      return mpAnnotation->getKey();
    }

  return CDataContainer::getKey();
}
