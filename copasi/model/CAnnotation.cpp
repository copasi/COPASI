// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CAnnotation.cpp,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/02/07 15:34:59 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CAnnotation.cpp
 *
 *  Created on: Aug 12, 2010
 *      Author: shoops
 */

#include "copasi.h"

#include "CAnnotation.h"

#include "MIRIAM/CRDFUtilities.h"

CAnnotation::CAnnotation():
    mNotes(),
    mMiriamAnnotation(),
    mXMLId()
{}

CAnnotation::CAnnotation(const CAnnotation & src):
    mNotes(src.mNotes),
    mMiriamAnnotation(src.mMiriamAnnotation),
    mXMLId(src.mXMLId)
{}

CAnnotation::~CAnnotation()
{}

void CAnnotation::setMiriamAnnotation(const std::string & miriamAnnotation,
                                      const std::string & newId,
                                      const std::string & oldId)
{
  mMiriamAnnotation = miriamAnnotation;
  mXMLId = newId;
  CRDFUtilities::fixLocalFileAboutReference(mMiriamAnnotation, newId, oldId);
}

const std::string & CAnnotation::getMiriamAnnotation() const
{return mMiriamAnnotation;}

void CAnnotation::setNotes(const std::string & notes)
{
  mNotes = notes;
}
const std::string & CAnnotation::getNotes() const
{
  return mNotes;
}

bool CAnnotation::operator == (const CAnnotation & rhs) const
{
  if (mNotes != rhs.mNotes)
    return false;

  std::string TmpAnnotation = mMiriamAnnotation;
  CRDFUtilities::fixLocalFileAboutReference(TmpAnnotation, rhs.mXMLId, mXMLId);

  return (TmpAnnotation == rhs.mMiriamAnnotation);
}

