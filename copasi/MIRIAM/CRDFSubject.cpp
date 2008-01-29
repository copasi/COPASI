// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFSubject.cpp,v $
//   $Revision: 1.4 $
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

#include "copasi.h"

#include "CRDFSubject.h"

CRDFSubject::CRDFSubject():
    mType(RESOURCE),
    mResource(""),
    mBlankNodeId("")
{}

CRDFSubject::CRDFSubject(const CRDFSubject & src):
    mType(src.mType),
    mResource(src.mResource),
    mBlankNodeId(src.mBlankNodeId)
{}

CRDFSubject::~CRDFSubject()
{}

void CRDFSubject::setType(const CRDFSubject::eSubjectType & type)
{mType = type;}

const CRDFSubject::eSubjectType & CRDFSubject::getType() const
  {return mType;}

void CRDFSubject::setResource(const std::string & resource, const bool & isLocal)
{
  mResource = resource;
  mIsLocalResource = isLocal;
}

const std::string & CRDFSubject::getResource() const
  {return mResource;}

const bool & CRDFSubject::isLocal() const
  {return mIsLocalResource;}

void CRDFSubject::setBlankNodeId(const std::string & blankNodeId)
{mBlankNodeId = blankNodeId;}

const std::string & CRDFSubject::getBlankNodeID() const
  {return mBlankNodeId;}

void CRDFSubject::clearData()
{mBlankNodeId = ""; mResource = ""; mType = CRDFSubject::RESOURCE;}
