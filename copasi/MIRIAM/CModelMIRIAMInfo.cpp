// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModelMIRIAMInfo.cpp,v $
//   $Revision: 1.16 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/03/03 16:58:28 $
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

#include "model/CModelValue.h"
#include "report/CKeyFactory.h"
#include "utilities/CCopasiVector.h"

#include "CModelMIRIAMInfo.h"
#include "CRDFWriter.h"
#include "CRDFLiteral.h"
#include "CRDFParser.h"

CModelMIRIAMInfo::CModelMIRIAMInfo() :
	mpRDFGraph(NULL),
    mpEntity(NULL)
{
  clearMembers();
  mpRDFGraph = new CRDFGraph();
  
  /*std::string buf;
  std::string line;
  std::ifstream xmlFile("example.xml");
  while (std::getline(xmlFile, line))
    buf += line + '\n';

  mpRDFGraph = CRDFParser::graphFromXml(buf);
  if (mpRDFGraph)
    {
      fillInfoFromGraph();
      std::string reprint = CRDFWriter::xmlFromGraph(mpRDFGraph);
    }
  xmlFile.close();*/
}

CModelMIRIAMInfo::~CModelMIRIAMInfo()
{pdelete(mpRDFGraph);}

CRDFGraph * CModelMIRIAMInfo::getRDFGraph()
{return mpRDFGraph;}

bool CModelMIRIAMInfo::fillInfoFromGraph()
{
  if (!mpRDFGraph)
    return false;

  clearMembers();
  std::vector<CRDFObject> objects;
  
  fillObjects("dc:creator");

  fillObjects("dcterms:references");
  fillObjects("bqmodel:isDescribedBy");
  fillObjects("bqbiol:isDescribedBy");
  
  mpRDFGraph->getNodeIDsForTable("dcterms:created", objects, mCreatedObj);
  objects.clear();
  
  fillObjects("dcterms:modified");
  return true;
}

CCopasiVector <CCreator> & CModelMIRIAMInfo::getCreators()
{return mCreators;}

CCreator* CModelMIRIAMInfo::createCreator(const std::string & objectName)
{
  CCreator * pCreator = new CCreator(objectName);

  if (!mCreators.add(pCreator, true))
    {
      delete pCreator;
      return NULL;
    }

  mpRDFGraph->addRecordToTable("dc:creator", mCreatorsObj, pCreator->getRDFObject());
  return pCreator;
}

bool CModelMIRIAMInfo::removeCreator(const std::string & key)
{
  CCreator * pCreator =
    dynamic_cast< CCreator * >(GlobalKeys.get(key));

  if (!pCreator)
    return false;

  //Check if Creator exists
  unsigned C_INT32 index =
    mCreators.getIndex(pCreator);

  if (index == C_INVALID_INDEX)
    return false;

  if (mpRDFGraph->removeRecordFromTable("dc:creator", mCreatorsObj, pCreator->getRDFObject()))
  {mCreators.CCopasiVector< CCreator >::remove(index);}
  return true;
}

CCopasiVector <CReference> & CModelMIRIAMInfo::getReferences()
{return mReferences;}

CReference* CModelMIRIAMInfo::createReference(const std::string & objectName)
{
  CReference * pReference = new CReference(objectName);
  pReference->setParentTag("dcterms:references");

  if (!mReferences.add(pReference, true))
    {
      delete pReference;
      return NULL;
    }

  mpRDFGraph->addRecordToTable("dcterms:references", mReferenceObjs["dcterms:references"], pReference->getRDFObject());
  return pReference;
}

bool CModelMIRIAMInfo::removeReference(const std::string & key)
{
  CReference * pReference =
    dynamic_cast< CReference * >(GlobalKeys.get(key));

  if (!pReference)
    return false;

  //Check if Reference exists
  unsigned C_INT32 index =
    mReferences.getIndex(pReference);

  if (index == C_INVALID_INDEX)
    return false;

  std::string parentTag = pReference->getParentTag();
  if (mpRDFGraph->removeRecordFromTable(parentTag, mReferenceObjs[parentTag], pReference->getRDFObject()))
  {mReferences.CCopasiVector< CReference >::remove(index);}
  
  return true;
}

const std::string CModelMIRIAMInfo::getCreatedDT() const
  {return mpRDFGraph->getFieldValue("dcterms:W3CDTF", mCreatedObj);}

void CModelMIRIAMInfo::setCreatedDT(const std::string& dt)
{mpRDFGraph->setFieldValue("dcterms:W3CDTF", mCreatedObj, dt);}

CCopasiVector <CModified> & CModelMIRIAMInfo::getModifieds()
{return mModifieds;}

CModified* CModelMIRIAMInfo::createModified(const std::string & objectName)
{
  CModified * pModified = new CModified(objectName);

  if (!mModifieds.add(pModified, true))
    {
      delete pModified;
      return NULL;
    }

  mpRDFGraph->addRecordToTable("dcterms:modified", mModifiedsObj, pModified->getRDFObject());
  return pModified;
}

bool CModelMIRIAMInfo::removeModified(const std::string & key)
{
  CModified * pModified =
    dynamic_cast< CModified * >(GlobalKeys.get(key));

  if (!pModified)
    return false;

  //Check if Reference exists
  unsigned C_INT32 index =
    mModifieds.getIndex(pModified);

  if (index == C_INVALID_INDEX)
    return false;

  if (mpRDFGraph->removeRecordFromTable("dcterms:modified", mModifiedsObj, pModified->getRDFObject()))
  {mModifieds.CCopasiVector< CModified >::remove(index);}
  return true;
}

void CModelMIRIAMInfo::clearMembers()
{
  mOldReferencesMoved = false;
  mCreators.cleanup();
  mCreatorsObj.clearData();
  
  mReferences.cleanup();
  mReferenceObjs["dcterms:references"].clearData();
  mReferenceObjs["bqmodel:isDescribedBy"].clearData();
  mReferenceObjs["bqbiol:isDescribedBy"].clearData();
  
  mCreatedObj.clearData();
  mCreatedObj.setType(CRDFObject::BLANK_NODE);
  mCreatedObj.setBlankNodeId("CreatedNode");
  
  mModifieds.cleanup();
  mModifiedsObj.clearData();
}

void CModelMIRIAMInfo::loadGraph(const std::string& key)
{
  if (!mpEntity)
    {
      if ((mpEntity = dynamic_cast< CModelEntity * >(GlobalKeys.get(key))) != NULL)
        {
          CRDFGraph * oldGraph = mpRDFGraph;
          mpRDFGraph = mpRDFGraph->loadGraph(mpEntity);
          pdelete(oldGraph);
          fillInfoFromGraph();
        }
    }
}

bool CModelMIRIAMInfo::saveGraph()
{
  if (mpEntity && mpRDFGraph)
    {
      if (mpRDFGraph->saveGraph(mpEntity))
        {
          fillInfoFromGraph();
          return true;
        }
    }
  return false;
}

void CModelMIRIAMInfo::fillObjects(std::string tableName)
{
  std::vector<CRDFObject> objects;
  std::vector<CRDFObject>::iterator it;

  if (tableName == "dc:creator" && mpRDFGraph->getNodeIDsForTable(tableName, objects, mCreatorsObj))
    {
      for (it = objects.begin(); it != objects.end(); it++)
      {	mCreators.add(new CCreator((*it).getBlankNodeID(), NULL, new CRDFObject(*it)), true);	}
    }
  else if ((tableName == "dcterms:references" || tableName == "bqmodel:isDescribedBy"|| tableName == "bqbiol:isDescribedBy") && mpRDFGraph->getNodeIDsForTable(tableName, objects, mReferenceObjs[tableName]))
    {
      for (it = objects.begin(); it != objects.end(); it++)
	  {
		  CReference *pReference = new CReference((*it).getBlankNodeID(), NULL, new CRDFObject(*it));
		  pReference->setParentTag(tableName);
		  mReferences.add(pReference, true);
      }
    }
  else if (tableName == "dcterms:modified" && mpRDFGraph->getNodeIDsForTable("dcterms:modified", objects, mModifiedsObj))
    {
      for (it = objects.begin(); it != objects.end(); it++)
	  {	mModifieds.add(new CModified((*it).getBlankNodeID(), NULL, new CRDFObject(*it)), true);	}
    }
}

std::map<std::string, std::string> CModelMIRIAMInfo::moveOldReferences()
{
  std::map<std::string, std::string> movedReferencesMap;
  std::vector <std::string> referencesToDelete;
  if (mOldReferencesMoved)
		return movedReferencesMap;
  
  CCopasiVector<CReference>::iterator it = mReferences.begin();
  CCopasiVector<CReference>::const_iterator end = mReferences.end();
  for (; it != end; it++)
  {
      if ((*it)->getParentTag() != "dcterms:references")
      {	referencesToDelete.push_back((*it)->getKey());	}
  }
  
  std::vector <std::string>::iterator vit = referencesToDelete.begin();
  for (; vit != referencesToDelete.end(); vit++)
  {	
	  CReference* oldReference = dynamic_cast< CReference * >(GlobalKeys.get(*vit));
	  CReference* newReference = createReference("");
	  newReference->setPubmedId(oldReference->getPubmedId());
	  newReference->setDOI(oldReference->getDOI());
	  movedReferencesMap[oldReference->getKey()] = newReference->getKey();
	  removeReference(*vit);
  }

  mOldReferencesMoved = true;
  return movedReferencesMap;
}
