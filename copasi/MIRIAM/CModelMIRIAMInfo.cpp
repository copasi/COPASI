// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModelMIRIAMInfo.cpp,v $
//   $Revision: 1.13 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/20 20:28:31 $
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

#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "model/CModelValue.h"
#include "utilities/CCopasiVector.h"

#include "CModelMIRIAMInfo.h"
#include "CRDFParser.h"
#include "CRDFWriter.h"
#include "CRDFLiteral.h"

CModelMIRIAMInfo::CModelMIRIAMInfo() :
    mAuthors(),
    mAuthorsObj(),
    mPublications(),
    mPublicationsObj(),
    mCreatedObj(),
    mModifieds(),
    mModifiedsObj(),
    mpRDFGraph(NULL),
    mpEntity(NULL)
{
  mCreatedObj.setType(CRDFObject::BLANK_NODE);
  mCreatedObj.setBlankNodeId("CreatedNode");

  //mpRDFGraph = new CRDFGraph();

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
  xmlFile.close();
}

CModelMIRIAMInfo::~CModelMIRIAMInfo()
{pdelete(mpRDFGraph);}

void CModelMIRIAMInfo::loadGraph(const std::string& key)
{
  /*if (!mpEntity)
    {
      if ((mpEntity = dynamic_cast< CModelEntity * >(GlobalKeys.get(key))) != NULL)
        {
          pdelete(mpRDFGraph);
          mpRDFGraph = CRDFParser::graphFromXml(mpEntity->getMiriamAnnotation());
          fillInfoFromGraph();
        }
    }*/
}

bool CModelMIRIAMInfo::saveGraph()
{
  mpRDFGraph->compressGraph();
  if (mpEntity && mpRDFGraph)
    {
      mpEntity->setMiriamAnnotation(CRDFWriter::xmlFromGraph(mpRDFGraph));
      return true;
    }
  return false;
}

CRDFGraph * CModelMIRIAMInfo::getRDFGraph()
{return mpRDFGraph;}

bool CModelMIRIAMInfo::fillInfoFromGraph()
{
  if (!mpRDFGraph)
    return false;

  std::vector<CRDFObject> objects;
  if (mpRDFGraph->getNodeIDsForTable("Creators", objects, mAuthorsObj))
    {
      std::vector<CRDFObject>::iterator it;
      for (it = objects.begin(); it != objects.end(); it++)
        {
          //try finding this nodeId
          CCopasiVector<CAuthor>::iterator ait;
          bool found = false;
          for (ait = mAuthors.begin(); ait != mAuthors.end(); ait++)
            {
              if ((*ait)->getRDFObject() == *it)
              {found = true;}
            }
          if (!found)
            mAuthors.add(new CAuthor((*it).getBlankNodeID(), NULL, new CRDFObject(*it)), true);
        }
    }
  if (mpRDFGraph->getNodeIDsForTable("Publications", objects, mPublicationsObj))
    {
      std::vector<CRDFObject>::iterator it;
      for (it = objects.begin(); it != objects.end(); it++)
        {
          //try finding this nodeId
          CCopasiVector<CPublication>::iterator ait;
          bool found = false;
          for (ait = mPublications.begin(); ait != mPublications.end(); ait++)
            {
              if ((*ait)->getRDFObject() == *it)
              {found = true;}
            }
          if (!found)
            mPublications.add(new CPublication((*it).getResource(), NULL, new CRDFObject(*it)), true);
        }
    }
  mpRDFGraph->getNodeIDsForTable("Created", objects, mCreatedObj);
  if (mpRDFGraph->getNodeIDsForTable("Modifieds", objects, mModifiedsObj))
    {
      std::vector<CRDFObject>::iterator it;
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
            mModifieds.add(new CModified((*it).getResource(), NULL, new CRDFObject(*it)), true);
        }
    }

  return true;
}

CCopasiVector <CAuthor> & CModelMIRIAMInfo::getAuthors()
{return mAuthors;}

CAuthor* CModelMIRIAMInfo::createAuthor(const std::string & objectName)
{
  CAuthor * pAuthor = new CAuthor(objectName);

  if (!mAuthors.add(pAuthor, true))
    {
      delete pAuthor;
      return NULL;
    }

  mpRDFGraph->addRecordToTable("Creators", mAuthorsObj, pAuthor->getRDFObject());
  return pAuthor;
}

bool CModelMIRIAMInfo::removeAuthor(const std::string & key)
{
  CAuthor * pAuthor =
    dynamic_cast< CAuthor * >(GlobalKeys.get(key));

  if (!pAuthor)
    return false;

  //Check if Author exists
  unsigned C_INT32 index =
    mAuthors.getIndex(pAuthor);

  if (index == C_INVALID_INDEX)
    return false;

  mpRDFGraph->removeRecordFromTable("Creators", mAuthorsObj, pAuthor->getRDFObject());
  mAuthors.CCopasiVector< CAuthor >::remove(index);
  return true;
}

CCopasiVector <CPublication> & CModelMIRIAMInfo::getPublications()
{return mPublications;}

CPublication* CModelMIRIAMInfo::createPublication(const std::string & objectName)
{
  CPublication * pPublication = new CPublication(objectName);

  if (!mPublications.add(pPublication, true))
    {
      delete pPublication;
      return NULL;
    }

  mpRDFGraph->addRecordToTable("Publications", mPublicationsObj, pPublication->getRDFObject());
  return pPublication;
}

bool CModelMIRIAMInfo::removePublication(const std::string & key)
{
  CPublication * pPublication =
    dynamic_cast< CPublication * >(GlobalKeys.get(key));

  if (!pPublication)
    return false;

  //Check if Publication exists
  unsigned C_INT32 index =
    mPublications.getIndex(pPublication);

  if (index == C_INVALID_INDEX)
    return false;

  mpRDFGraph->removeRecordFromTable("Publications", mPublicationsObj, pPublication->getRDFObject());
  mPublications.CCopasiVector< CPublication >::remove(index);
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

  //Check if Publication exists
  unsigned C_INT32 index =
    mModifieds.getIndex(pModified);

  if (index == C_INVALID_INDEX)
    return false;

  mpRDFGraph->removeRecordFromTable("Modifieds", mModifiedsObj, pModified->getRDFObject());
  mModifieds.CCopasiVector< CModified >::remove(index);
  return true;
}
