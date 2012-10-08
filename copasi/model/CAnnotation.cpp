// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CAnnotation.cpp
 *
 *  Created on: Aug 12, 2010
 *      Author: shoops
 */

#include <sstream>

#include "copasi.h"

#include "CAnnotation.h"

#include "MIRIAM/CRDFUtilities.h"
#include "utilities/CCopasiMessage.h"
#include "xml/CCopasiXMLParser.h"
#include "utilities/CVersion.h"

CAnnotation::CAnnotation():
  mNotes(),
  mMiriamAnnotation(),
  mXMLId(),
  mUnsupportedAnnotations()
{}

CAnnotation::CAnnotation(const CAnnotation & src):
  mNotes(src.mNotes),
  mMiriamAnnotation(src.mMiriamAnnotation),
  mXMLId(src.mXMLId),
  mUnsupportedAnnotations(src.mUnsupportedAnnotations)
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

  std::string Annotation = mMiriamAnnotation;
  CRDFUtilities::fixLocalFileAboutReference(Annotation, rhs.mXMLId, mXMLId);

  // We need to ignore white spaces when comparing.
  std::string::const_iterator it = Annotation.begin();
  std::string::const_iterator end = Annotation.end();
  std::string::const_iterator itRhs = rhs.mMiriamAnnotation.begin();
  std::string::const_iterator endRhs = rhs.mMiriamAnnotation.end();

  while (it != end && itRhs != endRhs)
    {
      if (*it == * itRhs)
        {
          ++it;
          ++itRhs;

          continue;
        }

      // Advance past white spaces
      while (it != end)
        {
          if (*it == '\x20' || *it == '\x09' || *it == '\x0d' || *it == '\x0a')
            {
              ++it;

              continue;
            }

          break;
        }

      // Advance past white spaces
      while (itRhs != endRhs)
        {
          if (*itRhs == '\x20' || *itRhs == '\x09' || *itRhs == '\x0d' || *itRhs == '\x0a')
            {
              ++itRhs;

              continue;
            }

          break;
        }

      if (it == end && itRhs == endRhs)
        {
          return true;
        }

      if (it == end || itRhs == endRhs)
        {
          return false;
        }

      if (*it != *itRhs)
        {
          return false;
        }

      ++it;
      ++itRhs;
    }

  return true;
}

CAnnotation::UnsupportedAnnotation & CAnnotation::getUnsupportedAnnotations()
{
  return mUnsupportedAnnotations;
}

const CAnnotation::UnsupportedAnnotation & CAnnotation::getUnsupportedAnnotations() const
{
  return mUnsupportedAnnotations;
}

bool CAnnotation::addUnsupportedAnnotation(const std::string & name, const std::string & xml)
{
  // We need to check whether we have valid XML.
  // TODO: isValidXML is currently not working as it expects COAPSI elements
  // if (!isValidXML(xml))
  //   {
  //     return false;
  //}

  if (mUnsupportedAnnotations.find(name) != mUnsupportedAnnotations.end())
    {
      return false;
    }

  mUnsupportedAnnotations[name] = xml;

  return true;
}

bool CAnnotation::replaceUnsupportedAnnotation(const std::string & name, const std::string & xml)
{
  // We need to check whether we have valid XML.
  // TODO: isValidXML is currently not working as it expects COAPSI elements
  //if (!isValidXML(xml))
  //  {
  //    return false;
  //}

  if (mUnsupportedAnnotations.find(name) == mUnsupportedAnnotations.end())
    {
      return false;
    }

  mUnsupportedAnnotations[name] = xml;

  return true;
}

bool CAnnotation::removeUnsupportedAnnotation(const std::string & name)
{
  UnsupportedAnnotation::iterator it = mUnsupportedAnnotations.find(name);

  if (it == mUnsupportedAnnotations.end())
    {
      return false;
    }

  mUnsupportedAnnotations.erase(it);

  return true;
}

// static
bool CAnnotation::isValidXML(const std::string & xml)
{
  std::istringstream XML;
  XML.str(xml);
  XML.imbue(std::locale::classic());
  XML.precision(16);

  bool done = false;

  CVersion Version;
  CCopasiXMLParser Parser(Version);

#define BUFFER_SIZE 0xfffe
  char * pBuffer = new char[BUFFER_SIZE + 1];

  while (!done)
    {
      XML.get(pBuffer, BUFFER_SIZE, 0);

      if (XML.eof()) done = true;

      if (XML.fail() && !done)
        {
          done = true;
          return false;
        }

      if (!Parser.parse(pBuffer, -1, done))
        {
          done = true;
          return false;
        }
    }

  delete [] pBuffer;
#undef BUFFER_SIZE

  return true;
}
