// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/Attic/CAuthor.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2008/01/29 15:43:44 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "report/CKeyFactory.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"

#include "CAuthor.h"

CAuthor::CAuthor(const std::string & objectName, const CCopasiContainer * pParent,
                 const std::string & RDFGraphNodeID) :
    CCopasiContainer(objectName, pParent, "Author"),
    mKey(GlobalKeys.add("Author", this)),
    mRDFGraphNodeID(RDFGraphNodeID)
{
  if (strlen(RDFGraphNodeID.c_str()) == 0)
  {mRDFGraphNodeID = mKey;}
  initObjects();
  CONSTRUCTOR_TRACE;
}

CAuthor::CAuthor(const CAuthor & src,
                 const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Author", this))
{
  CONSTRUCTOR_TRACE;
  initObjects();
}

void CAuthor::initObjects()
{}

CAuthor::~CAuthor()
{
  GlobalKeys.remove(mKey);
}

const std::string CAuthor::getObjectName() const
  {return getFamilyName();}

const std::string CAuthor::getFamilyName() const
  {return CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("FamilyName", mRDFGraphNodeID);}

const std::string CAuthor::getGivenName() const
  {return CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("GivenName", mRDFGraphNodeID);}

const std::string CAuthor::getEmail() const
  {return CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("Email", mRDFGraphNodeID);}

const std::string CAuthor::getORG() const
  {return CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->getFieldValue("Orgname", mRDFGraphNodeID);}

std::string CAuthor::getRDFGraphNodeID()
{return mRDFGraphNodeID;}

void CAuthor::setFamilyName(const std::string familyName)
{CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("FamilyName", mRDFGraphNodeID, familyName);}

void CAuthor::setGivenName(const std::string givenName)
{CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("GivenName", mRDFGraphNodeID, givenName);}

void CAuthor::setEmail(const std::string Email)
{CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("Email", mRDFGraphNodeID, Email);}

void CAuthor::setORG(const std::string Orgname)
{CCopasiDataModel::Global->getModel()->getMIRIAMInfo().getRDFGraph()->setFieldValue("Orgname", mRDFGraphNodeID, Orgname);}

const std::string & CAuthor::getKey() const {return mKey;} //By G
