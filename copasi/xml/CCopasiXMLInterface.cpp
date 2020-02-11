// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CCopasiXMLInterface class.
 * The class CCopasiXMLInterface is the interface to various XML document
 * containing COPASI relevant information.
 *
 * Created for COPASI by Stefan Hoops 2003
 */

#include <fstream>
#include <limits>
#include <cmath>

#include "copasi/copasi.h"
#include "CCopasiXMLInterface.h"
#include "copasi/model/CModel.h"
#include "copasi/report/CReportDefinition.h"
#include "copasi/report/CReportDefinitionVector.h"
#include "copasi/plot/COutputDefinitionVector.h"
#include "copasi/plot/CPlotSpecification.h"
#include "copasi/core/CDataVector.h"
#include "copasi/utilities/CSlider.h"
#include "copasi/utilities/CDirEntry.h"
#include "copasi/commandline/CLocaleString.h"

SCopasiXMLGUI::SCopasiXMLGUI(const std::string & name,
                             const CDataContainer * pParent,
                             const std::string & type,
                             const CFlags< Flag > & flag)
  : CDataContainer(name, pParent, type, flag),
    mpSliderList(new CDataVector<CSlider>("SliderList", this))
{}

SCopasiXMLGUI::~SCopasiXMLGUI()
{
}

/**
 * Returns a pointer the the slider list.
 */
CDataVector<CSlider>* SCopasiXMLGUI::getSliderList()
{
  return this->mpSliderList;
}

/**
 * Returns a const pointer to the slider list.
 */
const CDataVector<CSlider>* SCopasiXMLGUI::getSliderList() const
{
  return this->mpSliderList;
}

void encodeNONE(const char & chr, std::ostringstream & xml)
{
  xml << chr;
  return;
}

void encodeSTD(const char & chr, std::ostringstream & xml)
{
  switch (chr)
    {
      case '&':
        xml << "&amp;";
        break;

      case '\'':
        xml << "&apos;";
        break;

      case '<':
        xml << "&lt;";
        break;

      case '>':
        xml << "&gt;";
        break;

      case '\"':
        xml << "&quot;";
        break;

      default:
        xml << chr;
        break;
    }

  return;
}

void encodeATTRIBUTE(const char & chr, std::ostringstream & xml)
{
  switch (chr)
    {
      case '&':
        xml << "&amp;";
        break;

      case '<':
        xml << "&lt;";
        break;

      case '\"':
        xml << "&quot;";
        break;

      case '\t':            // Without this <tab> is converted to <space>
        xml << "&#x09;";
        break;

      case '\n':            // Without this linebreak is converted to <space>
        xml << "&#x0a;";
        break;

      default:
        xml << chr;
        break;
    }

  return;
}

void encodeCHARACTER(const char & chr, std::ostringstream & xml)
{
  switch (chr)
    {
      case '&':
        xml << "&amp;";
        break;

      case '<':
        xml << "&lt;";
        break;

      default:
        xml << chr;
        break;
    }

  return;
}

std::string CCopasiXMLInterface::encode(const std::string & str, const EncodingType & type)
{
  /* All COPASI std::strings and char are already UTF-8 encoded.*/
  std::string tmp = str;
  std::ostringstream xml;

  void (*encode)(const char & chr, std::ostringstream & xml) = encodeNONE;

  std::string::const_iterator it = str.begin();
  std::string::const_iterator end = str.end();

  switch (type)
    {
      case none:
        encode = encodeNONE;
        break;

      case standard:
        encode = encodeSTD;
        break;

      case attribute:
        encode = encodeATTRIBUTE;
        break;

      case character:
        encode = encodeCHARACTER;
        break;
    }

  for (; it != end; ++it)
    encode(*it, xml);

  return xml.str();
}

CCopasiXMLInterface::DBL::DBL(const C_FLOAT64 & value):
  mValue(value)
{
  if (-mValue < std::numeric_limits< C_FLOAT64 >::min() && mValue < std::numeric_limits< C_FLOAT64 >::min() && !std::isnan(mValue))
    mValue = 0.0;
}

CCopasiXMLInterface::DBL::DBL(const char * value):
  mValue(std::numeric_limits<C_FLOAT64>::quiet_NaN())
{
  if (!value || !*value) return;

  std::istringstream in;

  in.imbue(std::locale::classic());
  in.str(value);

  in >> mValue;

  if (std::isnan(mValue))
    {
      if (!strcmp(value, "INF"))
        mValue = std::numeric_limits<C_FLOAT64>::infinity();
      else if (!strcmp(value, "-INF"))
        mValue = - std::numeric_limits<C_FLOAT64>::infinity();
    }

  return;
}

CCopasiXMLInterface::DBL::~DBL() {}

CCopasiXMLInterface::DBL::operator const C_FLOAT64 & () const
{return mValue;}

std::ostream & operator << (std::ostream & os, const CCopasiXMLInterface::DBL & dbl)
{
  os.precision(std::numeric_limits<double>::digits10 + 2);

  if (std::isnan(dbl.mValue))
    os << "NaN";
  else if (std::isfinite(dbl.mValue))
    os << dbl.mValue;
  else if (dbl.mValue > 0.0)
    os << "INF";
  else if (dbl.mValue < 0.0)
    os << "-INF";

  return os;
}

std::string CCopasiXMLInterface::utf8(const std::string & str)
{
  std::ostringstream utf8;

  /* Based on RFC 2279.
     Since every string within COPASI is treated as latin1 and input
     is only obtained through QT and Expat which will provide latin1
     encoded strings the below should suffice. */
  size_t i, imax;

  for (i = 0, imax = str.length(); i < imax; i++)
    {
      const unsigned char Char = str[i];

      if (Char < 0x80)
        utf8 << Char;
      else
        {
          utf8 << (unsigned char)(0xc0 + ((Char >> 6) & 0x03));
          utf8 << (unsigned char)(0x80 + (Char & 0x3f));
        }
    }

  return utf8.str();
}

CCopasiXMLInterface::CCopasiXMLInterface():
  mpIstream(NULL),
  mpOstream(NULL),
  mIndent()
{}

CCopasiXMLInterface::~CCopasiXMLInterface() {}

bool CCopasiXMLInterface::load(const std::string & fileName,
                               const std::string & relativeTo)
{
  mPWD = relativeTo;

  std::ifstream is(CLocaleString::fromUtf8(fileName).c_str());

  if (is.fail()) return false;

  return load(is, relativeTo);
}

bool CCopasiXMLInterface::save(const std::string & fileName,
                               const std::string & relativeTo)
{
  mPWD = relativeTo;

  std::ofstream os(CLocaleString::fromUtf8(fileName).c_str());

  if (os.fail()) return false;

  if (!save(os, relativeTo)) return false;

  return true;
}

bool CCopasiXMLInterface::saveData(const std::string & data)
{
  *mpOstream << mIndent << CCopasiXMLInterface::encode(data, character) << std::endl;

  return true;
}

bool CCopasiXMLInterface::saveXhtml(const std::string & xhtml)
{
  // if there is nothing to save bail
  if (xhtml.empty())
    return true;

  std::string::size_type start = xhtml.find_first_not_of("\x0a\x0d\t ");

  if (start != std::string::npos && xhtml[start] == '<')
    {
      std::string::size_type pos = xhtml.find('>');
      std::string FirstElement = xhtml.substr(0, pos);

      if (FirstElement.find("xmlns=\"http://www.w3.org/1999/xhtml\"") == std::string::npos
          && FirstElement.find("xmlns='http://www.w3.org/1999/xhtml'") == std::string::npos)
        FirstElement += " xmlns=\"http://www.w3.org/1999/xhtml\"";

      *mpOstream << mIndent << FirstElement << xhtml.substr(pos) << std::endl;
    }
  else
    {
      saveData(xhtml);
    }

  return true;
}

bool CCopasiXMLInterface::saveElement(const std::string & name,
                                      CXMLAttributeList & attributeList)
{
  *mpOstream << mIndent << "<" << name;
  *mpOstream << attributeList;
  *mpOstream << "/>" << std::endl;

  return true;
}

bool CCopasiXMLInterface::startSaveElement(const std::string & name)
{
  *mpOstream << mIndent << "<" << name << ">" << std::endl;

  mIndent += "  ";
  return true;
}

bool CCopasiXMLInterface::startSaveElement(const std::string & name,
    CXMLAttributeList & attributeList)
{
  *mpOstream << mIndent << "<" << name;
  *mpOstream << attributeList;
  *mpOstream << ">" << std::endl;

  mIndent += "  ";
  return true;
}

bool CCopasiXMLInterface::endSaveElement(const std::string & name)
{
  mIndent = mIndent.substr(0, mIndent.length() - 2);
  *mpOstream << mIndent << "</" << name << ">" << std::endl;

  return true;
}

bool CCopasiXMLInterface::saveParameter(const CCopasiParameter & parameter)
{
  bool success = true;

  CXMLAttributeList Attributes;
  std::string File;

  Attributes.add("name", parameter.getObjectName());

  CCopasiParameter::Type Type = parameter.getType();
  Attributes.add("type", CCopasiParameter::XMLType[Type]);

  switch (parameter.getType())
    {
      case CCopasiParameter::Type::DOUBLE:
        Attributes.add("value", parameter.getValue< C_FLOAT64 >());

        if (!saveElement("Parameter", Attributes)) success = false;

        break;

      case CCopasiParameter::Type::UDOUBLE:
        Attributes.add("value", parameter.getValue< C_FLOAT64 >());

        if (!saveElement("Parameter", Attributes)) success = false;

        break;

      case CCopasiParameter::Type::INT:
        Attributes.add("value", parameter.getValue< C_INT32 >());

        if (!saveElement("Parameter", Attributes)) success = false;

        break;

      case CCopasiParameter::Type::UINT:
        Attributes.add("value", parameter.getValue< unsigned C_INT32 >());

        if (!saveElement("Parameter", Attributes)) success = false;

        break;

      case CCopasiParameter::Type::BOOL:
        Attributes.add("value", parameter.getValue< bool >());

        if (!saveElement("Parameter", Attributes)) success = false;

        break;

      case CCopasiParameter::Type::STRING:
        Attributes.add("value", parameter.getValue< std::string >());

        if (!saveElement("Parameter", Attributes)) success = false;

        break;

      case CCopasiParameter::Type::KEY:
        Attributes.add("value", parameter.getValue< std::string >());

        if (!saveElement("Parameter", Attributes)) success = false;

        break;

      case CCopasiParameter::Type::FILE:
        File = parameter.getValue< std::string >();

        if (!CDirEntry::isRelativePath(File) &&
            !CDirEntry::makePathRelative(File, mPWD))
          {
            // the following code, will break the working filename
            // File = CDirEntry::fileName(File);
            CCopasiMessage(CCopasiMessage::WARNING, "Couldn't create relative path for File '%s' to '%s', leaving the absolute path.", File.c_str(), mPWD.c_str());
          }

        Attributes.add("value", File);

        if (!saveElement("Parameter", Attributes)) success = false;

        break;

      case CCopasiParameter::Type::CN:
        Attributes.add("value", parameter.getValue< CCommonName >());

        if (!saveElement("Parameter", Attributes)) success = false;

        break;

      case CCopasiParameter::Type::EXPRESSION:

        if (!startSaveElement("ParameterText", Attributes)) success = false;

        if (!saveData(parameter.getValue< std::string >())) success = false;

        if (!endSaveElement("ParameterText")) success = false;

        break;

      case CCopasiParameter::Type::GROUP:
        Attributes.skip(1);

        if (!startSaveElement("ParameterGroup", Attributes)) success = false;

        if (!saveParameterGroup(parameter.getValue< CCopasiParameterGroup::elements >())) success = false;

        if (!endSaveElement("ParameterGroup")) success = false;

        break;

      case CCopasiParameter::Type::INVALID:
      default:
        success = false;
        break;
    }

  return success;
}

bool CCopasiXMLInterface::saveParameterGroup(const std::vector< CCopasiParameter * > & group)
{
  bool success = true;

  std::vector< CCopasiParameter * >::const_iterator it = group.begin();
  std::vector< CCopasiParameter * >::const_iterator end = group.end();

  for (; it != end; ++it)
    if (!saveParameter(**it)) success = false;

  return success;
}

CXMLAttributeList::CXMLAttributeList():
  mAttributeList(),
  mSaveList()
{}

CXMLAttributeList::CXMLAttributeList(const CXMLAttributeList & src):
  mAttributeList(src.mAttributeList),
  mSaveList(src.mSaveList)
{}

CXMLAttributeList::~CXMLAttributeList() {}

bool CXMLAttributeList::erase()
{
  mAttributeList.clear();
  mSaveList.clear();

  return true;
}

size_t CXMLAttributeList::size() {return mAttributeList.size() / 2;}

bool CXMLAttributeList::add(const std::string & name, const C_FLOAT64 & value)
{
  return add(name,
             (CCopasiXMLInterface::DBL) value,
             CCopasiXMLInterface::attribute);
}

bool CXMLAttributeList::setName(const size_t & index,
                                const std::string & name)
{
  mAttributeList[2 * index] = name;
  return true;
}

const std::string & CXMLAttributeList::getName(const size_t & index) const
{return mAttributeList[2 * index];}

const std::string & CXMLAttributeList::getValue(const size_t & index) const
{return mAttributeList[2 * index + 1];}

bool CXMLAttributeList::skip(const size_t & index)
{
  mSaveList[index] = false;
  return true;
}

std::string CXMLAttributeList::getAttribute(const size_t & index) const
{
  if (mSaveList[index])
    return " " + mAttributeList[2 * index] + "=\"" + mAttributeList[2 * index + 1] + "\"";
  else
    return "";
}

std::ostream &operator<<(std::ostream &os, const CXMLAttributeList & attr)
{
  std::vector< std::string >::const_iterator itAttr = attr.mAttributeList.begin();
  std::vector< bool >::const_iterator itSave = attr.mSaveList.begin();
  std::vector< bool >::const_iterator endSave = attr.mSaveList.end();

  for (; itSave != endSave; ++itSave)
    if (*itSave)
      {
        os << " " << *itAttr++;
        os << "=\"" << *itAttr++ << "\"";
      }
    else
      itAttr += 2;

  return os;
}
