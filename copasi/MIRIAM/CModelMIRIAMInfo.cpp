// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModelMIRIAMInfo.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/02/07 18:58:15 $
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

CModelMIRIAMInfo::CModelMIRIAMInfo() :
    mAuthors(),
    mAuthorsObj(),
    mPublications(),
    mPublicationsObj(),
    mpRDFGraph(NULL),
    mpEntity(NULL)
{
  /*
  std::string buf;
  std::string line;
  std::ifstream xmlFile("example.xml");
  while(std::getline(xmlFile, line))
   buf += line + '\n';

  //mpRDFParser = new CRDFParser();
  mpRDFGraph = CRDFParser::graphFromXml(buf);
  if (mpRDFGraph)
  {
   fillInfoFromGraph();
   std::string reprint = CRDFWriter::xmlFromGraph(mpRDFGraph);
  }
  xmlFile.close();*/
}

CModelMIRIAMInfo::~CModelMIRIAMInfo()
{delete mpRDFGraph;}

void CModelMIRIAMInfo::loadGraph(const std::string& key)
{
  if (!mpRDFGraph)
    {
      if ((mpEntity = dynamic_cast< CModelEntity * >(GlobalKeys.get(key))) != NULL)
      {mpRDFGraph = CRDFParser::graphFromXml(mpEntity->getMiriamAnnotation());}
      if (!mpRDFGraph)
      {mpRDFGraph = new CRDFGraph();}
      fillInfoFromGraph();
    }
}

bool CModelMIRIAMInfo::saveGraph()
{
  if (mpEntity)
    {
      mpRDFGraph->compressGraph();
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

  if (mAuthors.size() == 2)
  {mpRDFGraph->addBagNodeToTable("Creators", mAuthorsObj);}
  mpRDFGraph->addObjectToTable("Creators", mAuthorsObj, pAuthor->getRDFObject());
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

  mpRDFGraph->removeObjectFromTable("Creators", mAuthorsObj, pAuthor->getRDFObject());
  mAuthors.CCopasiVector< CAuthor >::remove(index);
  if (mAuthors.size() == 1)
  {mpRDFGraph->removeBagNodeFromTable("Creators", mAuthorsObj);}
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

  if (mPublications.size() == 2)
  {mpRDFGraph->addBagNodeToTable("Publications", mPublicationsObj);}
  mpRDFGraph->addObjectToTable("Publications", mPublicationsObj, pPublication->getRDFObject());
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

  mpRDFGraph->removeObjectFromTable("Publications", mPublicationsObj, pPublication->getRDFObject());
  mPublications.CCopasiVector< CPublication >::remove(index);
  if (mPublications.size() == 1)
  {mpRDFGraph->removeBagNodeFromTable("Publications", mPublicationsObj);}
  return true;
}
