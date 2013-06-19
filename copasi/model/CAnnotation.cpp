// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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
#include "report/CKeyFactory.h"
#include "model/CModelValue.h"
#include "model/CReaction.h"
#include "model/CEvent.h"
#include "function/CFunction.h"
#include "report/CCopasiRootContainer.h"

// static
CAnnotation * CAnnotation::castObject(CCopasiObject * pObject)
{
  CModelEntity * pEntity = NULL;
  CEvent * pEvent = NULL;
  CReaction * pReaction = NULL;
  CFunction * pFunction = NULL;

  if ((pEntity = dynamic_cast< CModelEntity * >(pObject)) != NULL)
    return static_cast< CAnnotation * >(pEntity);

  if ((pEvent = dynamic_cast< CEvent * >(pObject)) != NULL)
    return static_cast< CAnnotation * >(pEvent);

  if ((pReaction = dynamic_cast< CReaction * >(pObject)) != NULL)
    return static_cast< CAnnotation * >(pReaction);

  if ((pFunction = dynamic_cast< CFunction * >(pObject)) != NULL)
    return static_cast< CAnnotation * >(pFunction);

  return NULL;
}

// static
const CAnnotation * CAnnotation::castObject(const CCopasiObject * pObject)
{
  const CModelEntity * pEntity = NULL;
  const CEvent * pEvent = NULL;
  const CReaction * pReaction = NULL;
  const CFunction * pFunction = NULL;

  if ((pEntity = dynamic_cast< const CModelEntity * >(pObject)) != NULL)
    return static_cast< const CAnnotation * >(pEntity);

  if ((pEvent = dynamic_cast< const CEvent * >(pObject)) != NULL)
    return static_cast< const CAnnotation * >(pEvent);

  if ((pReaction = dynamic_cast< const CReaction * >(pObject)) != NULL)
    return static_cast< const CAnnotation * >(pReaction);

  if ((pFunction = dynamic_cast< const CFunction * >(pObject)) != NULL)
    return static_cast< const CAnnotation * >(pFunction);

  return NULL;
}

CAnnotation::CAnnotation():
  mKey(""),
  mNotes(),
  mMiriamAnnotation(),
  mXMLId(),
  mUnsupportedAnnotations()
{}

CAnnotation::CAnnotation(const CAnnotation & src):
  mKey(""),
  mNotes(src.mNotes),
  mMiriamAnnotation(src.mMiriamAnnotation),
  mXMLId(src.mXMLId),
  mUnsupportedAnnotations(src.mUnsupportedAnnotations)
{}

CAnnotation::~CAnnotation()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
}

// virtual
const std::string & CAnnotation::getKey() const
{
  return mKey;
}

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
  if (!isValidXML(xml))
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCAnnotation + 5, name.c_str());
      return false;
    }

  // The name must not be empty
  if (name == "")
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCAnnotation + 7);
      return false;
    }

  // The name must be unique
  if (mUnsupportedAnnotations.find(name) != mUnsupportedAnnotations.end())
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCAnnotation + 6, name.c_str());
      return false;
    }

  mUnsupportedAnnotations[name] = xml;

  return true;
}

bool CAnnotation::replaceUnsupportedAnnotation(const std::string & name, const std::string & xml)
{
  // We need to check whether we have valid XML.
  if (!isValidXML(xml))
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCAnnotation + 5, name.c_str());
      return false;
    }

  // The annotation must exist
  if (mUnsupportedAnnotations.find(name) == mUnsupportedAnnotations.end())
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCAnnotation + 8, name.c_str());
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

  size_t Size = CCopasiMessage::size();

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

  // Remove error messages created by setExpression as this may fail
  // due to incomplete model specification at this time.
  while (CCopasiMessage::size() > Size)
    CCopasiMessage::getLastMessage();

  return true;
}
