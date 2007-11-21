// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFObject.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/21 16:15:07 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CRDFObject.h"
#include "CRDFLiteral.h"

CRDFObject::CRDFObject():
    mType(RESOURCE),
    mResource(""),
    mBlankNodeId(""),
    mpLiteral(NULL)
{}

CRDFObject::CRDFObject(const CRDFObject & src):
    mType(src.mType),
    mResource(src.mResource),
    mBlankNodeId(src.mBlankNodeId),
    mpLiteral(src.mpLiteral == NULL ? NULL : new CRDFLiteral(*src.mpLiteral))
{}

CRDFObject::~CRDFObject()
{pdelete(mpLiteral);}

void CRDFObject::setType(const CRDFObject::eObjectType & type)
{mType = type;}

const CRDFObject::eObjectType & CRDFObject::getType() const
  {return mType;}

void CRDFObject::setResource(const std::string & resource)
{mResource = resource;}

const std::string & CRDFObject::getResource() const
  {return mResource;}

void CRDFObject::setBlankNodeId(const std::string & blankNodeId)
{mBlankNodeId = blankNodeId;}

const std::string & CRDFObject::getBlankNodeID() const
  {return mBlankNodeId;}

void CRDFObject::setLiteral(const CRDFLiteral & literal)
{
  pdelete(mpLiteral);
  mpLiteral = new CRDFLiteral(literal);
}

const CRDFLiteral & CRDFObject::getLiteral() const
  {
    if (mpLiteral == NULL)
      mpLiteral = new CRDFLiteral;

    return *mpLiteral;
  }
