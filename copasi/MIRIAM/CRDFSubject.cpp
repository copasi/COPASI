// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFSubject.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/06/10 20:31:11 $
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
    mIsLocalResource(false),
    mBlankNodeId("")
{}

CRDFSubject::CRDFSubject(const CRDFSubject & src):
    mType(src.mType),
    mResource(src.mResource),
    mIsLocalResource(src.mIsLocalResource),
    mBlankNodeId(src.mBlankNodeId)
{}

CRDFSubject::~CRDFSubject()
{}

CRDFSubject& CRDFSubject::operator =(const CRDFSubject& rhs)
{
  if (this != &rhs)
    {
      mType = rhs.mType;
      mResource = rhs.mResource;
      mBlankNodeId = rhs.mBlankNodeId;
      mIsLocalResource = rhs.mIsLocalResource;
    }
  return *this;
}

bool CRDFSubject::operator ==(const CRDFSubject& rhs) const
  {
    if (mType == rhs.mType)
      {
        switch (mType)
          {
          case CRDFSubject::BLANK_NODE:
            if (mBlankNodeId == rhs.mBlankNodeId)
            {return true;}
            break;
          case CRDFSubject::RESOURCE:
            if (mResource == rhs.mResource && mIsLocalResource == rhs.mIsLocalResource)
            {return true;}
            break;
          }
      }
    return false;
  }

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
{
  mBlankNodeId = "";
  mResource = "";
  mType = CRDFSubject::RESOURCE;
  mIsLocalResource = false;
}

std::ostream & operator << (std::ostream & os, const CRDFSubject & subject)
{
  switch (subject.getType())
    {
    case CRDFSubject::BLANK_NODE:
      os << subject.getBlankNodeID();
      break;
    case CRDFSubject::RESOURCE:
      os << subject.getResource();
      break;
    }

  return os;
}
