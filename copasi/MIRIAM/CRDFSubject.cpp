// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFSubject.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/21 16:15:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
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

void CRDFSubject::setResource(const std::string & resource)
{mResource = resource;}

const std::string & CRDFSubject::getResource() const
  {return mResource;}

void CRDFSubject::setBlankNodeId(const std::string & blankNodeId)
{mBlankNodeId = blankNodeId;}

const std::string & CRDFSubject::getBlankNodeID() const
  {return mBlankNodeId;}
