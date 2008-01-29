// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModelMIRIAMInfo.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/01/29 17:12:35 $
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
    mAuthorsGraphID(""),
    mpRDFGraph(NULL)
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
   mpRDFGraph->printGraph();
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
      CModelEntity * pEntity = NULL;
      if ((pEntity = dynamic_cast< CModelEntity * >(GlobalKeys.get(key))) != NULL)
      {mpRDFGraph = CRDFParser::graphFromXml(pEntity->getMiriamAnnotation());}
      if (!mpRDFGraph)
      {mpRDFGraph = new CRDFGraph();}
      fillInfoFromGraph();
    }
}

CRDFGraph * CModelMIRIAMInfo::getRDFGraph()
{return mpRDFGraph;}

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
  {mpRDFGraph->addBagNodeToTable("Creators", mAuthorsGraphID);}
  mpRDFGraph->addObjectToTable("Creators", mAuthorsGraphID, pAuthor->getRDFGraphNodeID());
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

  mpRDFGraph->removeObjectFromTable("Creators", mAuthorsGraphID, pAuthor->getRDFGraphNodeID());
  mAuthors.CCopasiVector< CAuthor >::remove(index);
  if (mAuthors.size() == 1)
  {mpRDFGraph->removeBagNodeFromTable("Creators", mAuthorsGraphID);}
  return true;
}

bool CModelMIRIAMInfo::fillInfoFromGraph()
{
  if (!mpRDFGraph)
    return false;

  std::vector<std::string> nodeIds;
  if (mpRDFGraph->getNodeIDsForTable("Creators", nodeIds, mAuthorsGraphID))
    {
      std::vector<std::string>::iterator it;
      for (it = nodeIds.begin(); it != nodeIds.end(); it++)
        {
          //try finding this nodeId
          CCopasiVector<CAuthor>::iterator ait;
          bool found = false;
          for (ait = mAuthors.begin(); ait != mAuthors.end(); ait++)
            {
              if ((*ait)->getRDFGraphNodeID() == *it)
              {found = true;}
            }
          if (!found)
            mAuthors.add(new CAuthor(*it, NULL, *it), true);
        }
    }
  return true;
}
