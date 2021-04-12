// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

/*
 * CAnnotation.cpp
 *
 *  Created on: Aug 12, 2010
 *      Author: shoops
 */

#include <sstream>

#include "copasi/copasi.h"

#include "CAnnotation.h"

#include "copasi/MIRIAM/CRDFUtilities.h"
#include "copasi/MIRIAM/CModelMIRIAMInfo.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/CVersion.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CEvent.h"
#include "copasi/model/CModelParameterSet.h"
#include "copasi/function/CFunction.h"
#include "copasi/utilities/CUnitDefinition.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/undo/CUndoData.h"

#include "copasi/xml/parser/CXMLParser.h"

// static
std::map< CDataContainer *, CMIRIAMInfo * > CAnnotation::Container2Info;

// static
CAnnotation * CAnnotation::castObject(CDataObject * pObject)
{
  CModelEntity * pEntity = NULL;
  CEvent * pEvent = NULL;
  CReaction * pReaction = NULL;
  CFunction * pFunction = NULL;
  CUnitDefinition * pUnitDefinition = NULL;
  CModelParameterSet * pParameterSet = NULL;

  if ((pEntity = dynamic_cast< CModelEntity * >(pObject)) != NULL)
    return static_cast< CAnnotation * >(pEntity);

  if ((pEvent = dynamic_cast< CEvent * >(pObject)) != NULL)
    return static_cast< CAnnotation * >(pEvent);

  if ((pReaction = dynamic_cast< CReaction * >(pObject)) != NULL)
    return static_cast< CAnnotation * >(pReaction);

  if ((pParameterSet = dynamic_cast< CModelParameterSet * >(pObject)) != NULL)
    return static_cast< CAnnotation * >(pParameterSet);

  if ((pFunction = dynamic_cast< CFunction * >(pObject)) != NULL)
    return static_cast< CAnnotation * >(pFunction);

  if ((pUnitDefinition = dynamic_cast< CUnitDefinition * >(pObject)) != NULL)
    return static_cast< CAnnotation * >(pUnitDefinition);

  return NULL;
}

// static
const CAnnotation * CAnnotation::castObject(const CDataObject * pObject)
{
  const CModelEntity * pEntity = NULL;
  const CEvent * pEvent = NULL;
  const CReaction * pReaction = NULL;
  const CFunction * pFunction = NULL;
  const CUnitDefinition * pUnitDefinition = NULL;
  const CModelParameterSet * pParameterSet = NULL;

  if ((pEntity = dynamic_cast< const CModelEntity * >(pObject)) != NULL)
    return static_cast< const CAnnotation * >(pEntity);

  if ((pEvent = dynamic_cast< const CEvent * >(pObject)) != NULL)
    return static_cast< const CAnnotation * >(pEvent);

  if ((pReaction = dynamic_cast< const CReaction * >(pObject)) != NULL)
    return static_cast< const CAnnotation * >(pReaction);

  if ((pParameterSet = dynamic_cast< const CModelParameterSet * >(pObject)) != NULL)
    return static_cast< const CAnnotation * >(pParameterSet);

  if ((pFunction = dynamic_cast< const CFunction * >(pObject)) != NULL)
    return static_cast< const CAnnotation * >(pFunction);

  if ((pUnitDefinition = dynamic_cast< const CUnitDefinition * >(pObject)) != NULL)
    return static_cast< const CAnnotation * >(pUnitDefinition);

  return NULL;
}

// static
CMIRIAMInfo * CAnnotation::allocateMiriamInfo(CDataContainer * pParent)
{
  std::map< CDataContainer *, CMIRIAMInfo * >::iterator found = Container2Info.find(pParent);

  if (found == Container2Info.end())
    {
      found = Container2Info.insert(std::make_pair(pParent, new CMIRIAMInfo())).first;
      found->second->load(found->first);
    }

  return found->second;
}

// static
void CAnnotation::freeMiriamInfo(CDataContainer * pParent)
{
  Container2Info.erase(pParent);
}

CData CAnnotation::toData() const
{
  CData Data;

  Data.addProperty(CData::Property::NOTES, mNotes);
  Data.addProperty(CData::Property::MIRIAM_RDF_XML, mMiriamAnnotation);

  return Data;
}

bool CAnnotation::applyData(const CData & data, CUndoData::CChangeSet & changes)
{
  if (data.isSetProperty(CData::Property::NOTES))
    {
      mNotes = data.getProperty(CData::Property::NOTES).toString();
    }

  if (data.isSetProperty(CData::Property::MIRIAM_RDF_XML))
    {
      mMiriamAnnotation = data.getProperty(CData::Property::MIRIAM_RDF_XML).toString();
    }

  return true;
}

void CAnnotation::createUndoData(CUndoData & undoData,
                                 const CUndoData::Type & type,
                                 const CData & oldData,
                                 const CCore::Framework & framework) const
{
  switch (type)
    {
      case CUndoData::Type::CHANGE:
        undoData.addProperty(CData::Property::NOTES, oldData.getProperty(CData::Property::NOTES), mNotes);
        undoData.addProperty(CData::Property::MIRIAM_RDF_XML, oldData.getProperty(CData::Property::MIRIAM_RDF_XML), mMiriamAnnotation);
        break;

      case CUndoData::Type::REMOVE:
        undoData.addProperty(CData::Property::NOTES, oldData.getProperty(CData::Property::NOTES));
        undoData.addProperty(CData::Property::MIRIAM_RDF_XML, oldData.getProperty(CData::Property::MIRIAM_RDF_XML));
        break;

      case CUndoData::Type::INSERT:
        undoData.addProperty(CData::Property::NOTES, mNotes);
        undoData.addProperty(CData::Property::MIRIAM_RDF_XML, mMiriamAnnotation);
        break;
    }
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
  CRootContainer::getKeyFactory()->remove(mKey);
}

// virtual
const std::string & CAnnotation::getKey() const
{
  return mKey;
}

void CAnnotation::initMiriamAnnotation(const std::string & newId)
{
  mXMLId = newId;
  mMiriamAnnotation =
    "<rdf:RDF\n"
    "xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
    "xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
    "<rdf:Description rdf:about=\"#" + newId + "\">\n"
    "</rdf:Description>\n"
    "</rdf:RDF>";
}

void CAnnotation::setMiriamAnnotation(const std::string & miriamAnnotation,
                                      const std::string & newId,
                                      const std::string & oldId)
{
  mXMLId = newId;
  mMiriamAnnotation = miriamAnnotation;
  CRDFUtilities::fixLocalFileAboutReference(mMiriamAnnotation, newId, oldId);
}

const std::string & CAnnotation::getMiriamAnnotation() const
{return mMiriamAnnotation;}

void CAnnotation::setNotes(const std::string & notes)
{
  mNotes = notes;

  std::string::size_type start = mNotes.find_first_not_of("\x0a\x0d\t ");

  if (start != std::string::npos && mNotes[start] == '<')
    {
      std::string::size_type pos = mNotes.find('>');
      std::string FirstElement = mNotes.substr(0, pos);

      if (FirstElement.find("xmlns=\"http://www.w3.org/1999/xhtml\"") == std::string::npos
          && FirstElement.find("xmlns='http://www.w3.org/1999/xhtml'") == std::string::npos)
        mNotes.insert(pos, " xmlns=\"http://www.w3.org/1999/xhtml\"");
    }
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
  // The name must not be empty
  if (name == "")
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCAnnotation + 7);
      return false;
    }

  // We need to check whether we have valid XML.
  if (!isValidXML(xml))
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCAnnotation + 5, name.c_str());
      return false;
    }

  // if we already have an entry, we add it ...
  if (mUnsupportedAnnotations.find(name) != mUnsupportedAnnotations.end())
    {
      mUnsupportedAnnotations[name] += xml;
    }
  else
    {
      mUnsupportedAnnotations[name] = xml;
    }

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
  XML.precision(std::numeric_limits<double>::digits10 + 2);

  bool done = false;

  CVersion Version;
  CXMLParser Parser(Version);

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
