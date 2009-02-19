// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CModified.cpp,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/02/19 19:50:46 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CRDFGraph.h"
#include "CCreator.h"
#include "CRDFLiteral.h"
#include "CModelMIRIAMInfo.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "copasi/report/CCopasiRootContainer.h"

CModification::CModification(const std::string & objectName,
                             const CCopasiContainer * pParent):
    CCopasiContainer(objectName, pParent, "Modification"),
    mTriplet(),
    mNodePath(),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Modification", this))
{}

CModification::CModification(const CRDFTriplet & triplet,
                             const std::string & objectName,
                             const CCopasiContainer * pParent):
    CCopasiContainer(objectName, pParent, "Modification"),
    mTriplet(triplet),
    mNodePath(),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Modification", this))
{
  if (!mTriplet)
    return;

  mNodePath = mTriplet.pObject->getPath();
}

CModification::CModification(const CModification & src,
                             const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mTriplet(src.mTriplet),
    mNodePath(src.mNodePath),
    mKey(CCopasiRootContainer::getKeyFactory()->add("Modification", this))
{}

CModification::~CModification()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
}

const CRDFTriplet & CModification::getTriplet() const
  {return mTriplet;}

const std::string & CModification::getKey() const
  {return mKey;}

void CModification::setDate(const std::string & date)
{mTriplet.pObject->setFieldValue(date, CRDFPredicate::dcterms_W3CDTF, mNodePath);}

const std::string & CModification::getDate() const
  {return mTriplet.pObject->getFieldValue(CRDFPredicate::dcterms_W3CDTF);}
