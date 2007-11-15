// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/CRDFObject.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2007/11/15 22:33:54 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CRDFObject.h"

CRDFObject::CRDFObject(std::string resource) : mResource(resource)
{}

CRDFObject::~CRDFObject()
{}

std::string CRDFObject::getResource()
{return mResource;}

void CRDFObject::setResource(std::string resource)
{mResource = resource;}
