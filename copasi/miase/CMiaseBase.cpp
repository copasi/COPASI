// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseBase.cpp,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/03/20 18:33:37 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CMiaseBase.h"
#include <iostream>

CMiaseNotes::CMiaseNotes()
{}

CMiaseNotes::~CMiaseNotes()
{}

std::string CMiaseNotes::getAnyNote()
{
  return mAnyNote;
}

void CMiaseNotes::setAnyNote(std::string anyNote)
{
  mAnyNote = anyNote;
}

std::string CMiaseNotes::getXmlNs()
{
  return mXmlNs;
}

void CMiaseNotes::setXmlNs(std::string xmlNs)
{
  mXmlNs = xmlNs;
}

//*****************************************************************************

CMiaseAnnotation::CMiaseAnnotation()
{}

CMiaseAnnotation::~CMiaseAnnotation()
{}

std::string CMiaseAnnotation::getAnyNote()
{
  return mAnyAnnotation;
}

void CMiaseAnnotation::setAnyNote(std::string anyAnnotation)
{
  mAnyAnnotation = anyAnnotation;
}

//*****************************************************************************

CMiaseBase::CMiaseBase()
{}

CMiaseBase::~CMiaseBase()
{}

std::string CMiaseBase::getMetaId()
{
  return mMetaId;
}

void CMiaseBase::setMetaId(std::string metaId)
{
  mMetaId = metaId;
}

void CMiaseBase::addAnnotation (CMiaseAnnotation* ann)
{
  mpAnnotation = ann;
}

CMiaseAnnotation* CMiaseBase::getAnnotation()
{
  return mpAnnotation;
}

void CMiaseBase::addNotes (CMiaseNotes* notes)
{
  mpNotes = notes;
}

CMiaseNotes* CMiaseBase::getNotes()
{
  return mpNotes;
}

//*****************************************************************************

CMiaseBaseEnhanced::CMiaseBaseEnhanced() : CMiaseBase()
{}

CMiaseBaseEnhanced::~CMiaseBaseEnhanced()
{}

std::string CMiaseBaseEnhanced::getId()
{
  return mId;
}

std::string CMiaseBaseEnhanced::getName()
{
  return mName;
}

void CMiaseBaseEnhanced::setId(std::string id)
{
  mId = id;
}

void CMiaseBaseEnhanced::setName(std::string name)
{
  mName = name;
}
