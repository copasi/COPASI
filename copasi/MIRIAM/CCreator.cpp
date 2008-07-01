// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CCreator.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/07/01 15:41:13 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CRDFGraph.h"
#include "CCreator.h"
#include "CRDFLiteral.h"
#include "CModelMIRIAMInfo.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"

CCreator::CCreator(const std::string & objectName,
                   const CCopasiContainer * pParent):
    CCopasiContainer(objectName, pParent, "Creator"),
    mTriplet(),
    mNodePath(),
    mKey(GlobalKeys.add("Creator", this))
{}

CCreator::CCreator(const CRDFTriplet & triplet,
                   const std::string & objectName,
                   const CCopasiContainer * pParent):
    CCopasiContainer(objectName, pParent, "Creator"),
    mTriplet(triplet),
    mNodePath(),
    mKey(GlobalKeys.add("Creator", this))
{
  if (!mTriplet)
    return;

  mNodePath = mTriplet.pObject->getPath();
}

CCreator::CCreator(const CCreator & src,
                   const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mTriplet(src.mTriplet),
    mNodePath(src.mNodePath),
    mKey(GlobalKeys.add("Creator", this))
{}

CCreator::~CCreator()
{
  GlobalKeys.remove(mKey);
}

const CRDFTriplet & CCreator::getTriplet() const
  {return mTriplet;}

const std::string & CCreator::getKey() const
  {return mKey;}

const std::string & CCreator::getFamilyName() const
  {return mTriplet.pObject->getFieldValue(CRDFPredicate::vcard_Family);}

const std::string & CCreator::getGivenName() const
  {return mTriplet.pObject->getFieldValue(CRDFPredicate::vcard_Given);}

const std::string & CCreator::getEmail() const
  {return mTriplet.pObject->getFieldValue(CRDFPredicate::vcard_EMAIL);}

const std::string & CCreator::getORG() const
  {return mTriplet.pObject->getFieldValue(CRDFPredicate::vcard_Orgname);}

void CCreator::setFamilyName(const std::string & familyName)
{mTriplet.pObject->setFieldValue(familyName, CRDFPredicate::vcard_Family, mNodePath);}

void CCreator::setGivenName(const std::string & givenName)
{mTriplet.pObject->setFieldValue(givenName, CRDFPredicate::vcard_Given, mNodePath);}

void CCreator::setEmail(const std::string & Email)
{mTriplet.pObject->setFieldValue(Email, CRDFPredicate::vcard_EMAIL, mNodePath);}

void CCreator::setORG(const std::string & Orgname)
{mTriplet.pObject->setFieldValue(Orgname, CRDFPredicate::vcard_Orgname, mNodePath);}
