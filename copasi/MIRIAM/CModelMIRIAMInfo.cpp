// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModelMIRIAMInfo.cpp,v $
//   $Revision: 1.15 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/25 20:37:25 $
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

CModelMIRIAMInfo::CModelMIRIAMInfo() :
    mpRDFGraph(NULL),
    mpEntity(NULL)
{
  clearMembers();
  mpRDFGraph = new CRDFGraph();
  /*
  std::string buf;
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
  fillObjects("Creators", objects);
  objects.clear();
  fillObjects("References", objects);
  objects.clear();
  mpRDFGraph->getNodeIDsForTable("Created", objects, mCreatedObj);
  objects.clear();
  fillObjects("Modifieds", objects);
  objects.clear();
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

  mpRDFGraph->addRecordToTable("Creators", mCreatorsObj, pCreator->getRDFObject());
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

  if (mpRDFGraph->removeRecordFromTable("Creators", mCreatorsObj, pCreator->getRDFObject()))
  {mCreators.CCopasiVector< CCreator >::remove(index);}
  return true;
}

CCopasiVector <CReference> & CModelMIRIAMInfo::getReferences()
{return mReferences;}

CReference* CModelMIRIAMInfo::createReference(const std::string & objectName)
{
  CReference * pReference = new CReference(objectName);

  if (!mReferences.add(pReference, true))
    {
      delete pReference;
      return NULL;
    }

  mpRDFGraph->addRecordToTable("References", mReferencesObj, pReference->getRDFObject());
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

  if (mpRDFGraph->removeRecordFromTable("References", mReferencesObj, pReference->getRDFObject()))
  {mReferences.CCopasiVector< CReference >::remove(index);}
  return true;
}

const std::string CModelMIRIAMInfo::getCreatedDT() const
  {return mpRDFGraph->getFieldValue("Created", mCreatedObj);}

void CModelMIRIAMInfo::setCreatedDT(const std::string& dt)
{mpRDFGraph->setFieldValue("Created", mCreatedObj, dt);}

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

  mpRDFGraph->addRecordToTable("Modifieds", mModifiedsObj, pModified->getRDFObject());
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

  if (mpRDFGraph->removeRecordFromTable("Modifieds", mModifiedsObj, pModified->getRDFObject()))
  {mModifieds.CCopasiVector< CModified >::remove(index);}
  return true;
}

void CModelMIRIAMInfo::clearMembers()
{
  mCreators.cleanup(),
  mCreatorsObj.clearData(),
  mReferences.cleanup(),
  mReferencesObj.clearData(),
  mCreatedObj.clearData(),
  mModifieds.cleanup(),
  mModifiedsObj.clearData(),
  mCreatedObj.setType(CRDFObject::BLANK_NODE);
  mCreatedObj.setBlankNodeId("CreatedNode");
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

void CModelMIRIAMInfo::fillObjects(std::string tableName, std::vector<CRDFObject>& objects)
{
  std::vector<CRDFObject>::iterator it;
  if (tableName == "Creators" && mpRDFGraph->getNodeIDsForTable(tableName, objects, mCreatorsObj))
    {
      for (it = objects.begin(); it != objects.end(); it++)
        {
          //try finding this nodeId
          CCopasiVector<CCreator>::iterator ait;
          bool found = false;
          for (ait = mCreators.begin(); ait != mCreators.end(); ait++)
            {
              if ((*ait)->getRDFObject() == *it)
              {found = true;}
            }
          if (!found)
            mCreators.add(new CCreator((*it).getBlankNodeID(), NULL, new CRDFObject(*it)), true);
        }
    }
  else if (tableName == "References" && mpRDFGraph->getNodeIDsForTable("References", objects, mReferencesObj))
    {
      for (it = objects.begin(); it != objects.end(); it++)
        {
          //try finding this nodeId
          CCopasiVector<CReference>::iterator ait;
          bool found = false;
          for (ait = mReferences.begin(); ait != mReferences.end(); ait++)
            {
              if ((*ait)->getRDFObject() == *it)
              {found = true;}
            }
          if (!found)
            mReferences.add(new CReference((*it).getBlankNodeID(), NULL, new CRDFObject(*it)), true);
        }
    }
  else if (tableName == "Modifieds" && mpRDFGraph->getNodeIDsForTable("Modifieds", objects, mModifiedsObj))
    {
      for (it = objects.begin(); it != objects.end(); it++)
        {
          //try finding this nodeId
          CCopasiVector<CModified>::iterator ait;
          bool found = false;
          for (ait = mModifieds.begin(); ait != mModifieds.end(); ait++)
            {
              if ((*ait)->getRDFObject() == *it)
              {found = true;}
            }
          if (!found)
            mModifieds.add(new CModified((*it).getBlankNodeID(), NULL, new CRDFObject(*it)), true);
        }
    }
}
