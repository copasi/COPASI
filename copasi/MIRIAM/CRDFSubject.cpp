// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/copasi.h"

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
