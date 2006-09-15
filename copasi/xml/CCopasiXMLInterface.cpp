/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CCopasiXMLInterface.cpp,v $
   $Revision: 1.47 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/15 12:28:29 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CCopasiXMLInterface class.
 * The class CCopasiXMLInterface is the interface to various XML document
 * containing Copasi relevant informtion.
 *
 * Created for Copasi by Stefan Hoops 2003
 */

#include <fstream>
#include <limits>

#ifdef SunOS
# include <ieeefp.h>
#else
# include <float.h>
#endif

#include "copasi.h"
#include "CCopasiXMLInterface.h"
#include "model/CModel.h"
#include "report/CReportDefinition.h"
#include "report/CReportDefinitionVector.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotSpecification.h"
#include "CCopasiXMLParser.h"
#include "utilities/CCopasiVector.h"
#include "utilities/CSlider.h"
#include "utilities/CDirEntry.h"

SCopasiXMLGUI::SCopasiXMLGUI():
    pSliderList(new CCopasiVector<CSlider>)
{}

SCopasiXMLGUI::~SCopasiXMLGUI()
{
  pdelete(pSliderList);
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

  void (*encode)(const char & chr, std::ostringstream & xml);
  std::string::const_iterator it = str.begin();
  std::string::const_iterator end = str.end();

  switch (type)
    {
    case none:
      encode = encodeNONE;
      break;

    case std:
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
  if (-mValue < DBL_MIN && mValue < DBL_MIN && !isnan(mValue))
    mValue = 0.0;
}

#ifdef WIN32
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

CCopasiXMLInterface::DBL::DBL(const char * value):
    mValue(std::numeric_limits<C_FLOAT64>::quiet_NaN())
{
  if (!value || !*value) return;

  char * Tail;
  mValue = strtod(value, & Tail);

  if (-mValue < DBL_MIN && mValue < DBL_MIN)
    mValue = 0.0;

  if (!*Tail) return;

  if (!strcmp(value, "INF"))
    mValue = DBL_MAX * 2;
  else if (!strcmp(value, "-INF"))
    mValue = - DBL_MAX * 2;
  else mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
}

#ifdef WIN32
# pragma warning (default: 4056 4756)
#endif

CCopasiXMLInterface::DBL::~DBL() {}

CCopasiXMLInterface::DBL::operator const C_FLOAT64 & () const
  {return mValue;}

std::ostream & operator << (std::ostream & os, const CCopasiXMLInterface::DBL & dbl)
{
  if (isnan(dbl.mValue))
    os << "NaN";
  else if (finite(dbl.mValue))
    os << dbl.mValue;
  else if (dbl.mValue > 0.0)
    os << "INF";
  else if (dbl.mValue < 0.0)
    os << "-INF";

  return os;
}

std::string CCopasiXMLInterface::utf8(const std::string & str)
{
  return str;

  std::ostringstream utf8;

  /* Based on RFC 2279.
     Since every string whithin COPASI is treated as latin1 and input
     is only optained through QT and Expat which will provide latin1
     encoded strings the below should suffice. */
  unsigned C_INT32 i, imax;
  for (i = 0, imax = str.length(); i < imax; i++)
    {
      if ((unsigned char) str[i] < 0x80) utf8 << str[i];
      else
        {
          utf8 << 0xc0 + ((str[i] >> 6) & 0x03);
          utf8 << 0x80 + (str[i] & 0x3f);
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
  mFilename = relativeTo;

  std::ifstream is(utf8ToLocale(fileName).c_str());

  if (is.fail()) return false;

  return load(is, relativeTo);
}

bool CCopasiXMLInterface::save(const std::string & fileName,
                               const std::string & relativeTo)
{
  mFilename = relativeTo;

  std::ofstream os(utf8ToLocale(fileName).c_str());
  if (os.fail()) return false;

  if (!save(os, relativeTo)) return false;

  return true;
}

bool CCopasiXMLInterface::saveData(const std::string & data)
{
  *mpOstream << mIndent << CCopasiXMLInterface::encode(data) << std::endl;

  return true;
}

bool CCopasiXMLInterface::saveXhtml(const std::string & xhtml)
{
  if (xhtml[0] == '<')
    {
      std::string::size_type pos = xhtml.find('>');
      std::string FirstElement = xhtml.substr(0, pos);

      if (FirstElement.find("xmlns=\"http://www.w3.org/1999/xhtml\"") == std::string::npos)
        FirstElement += " xmlns=\"http://www.w3.org/1999/xhtml\"";

      *mpOstream << mIndent << FirstElement << xhtml.substr(pos) << std::endl;
    }
  else
    {
      CXMLAttributeList Attributes;
      Attributes.add("xmlns", "http://www.w3.org/1999/xhtml");

      startSaveElement("body", Attributes);

      saveData(xhtml);

      endSaveElement("body");
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
    case CCopasiParameter::DOUBLE:
      Attributes.add("value", * parameter.getValue().pDOUBLE);
      if (!saveElement("Parameter", Attributes)) success = false;
      break;

    case CCopasiParameter::UDOUBLE:
      Attributes.add("value", * parameter.getValue().pUDOUBLE);
      if (!saveElement("Parameter", Attributes)) success = false;
      break;

    case CCopasiParameter::INT:
      Attributes.add("value", * parameter.getValue().pINT);
      if (!saveElement("Parameter", Attributes)) success = false;
      break;

    case CCopasiParameter::UINT:
      Attributes.add("value", * parameter.getValue().pUINT);
      if (!saveElement("Parameter", Attributes)) success = false;
      break;

    case CCopasiParameter::BOOL:
      Attributes.add("value", * parameter.getValue().pBOOL);
      if (!saveElement("Parameter", Attributes)) success = false;
      break;

    case CCopasiParameter::STRING:
      Attributes.add("value", * parameter.getValue().pSTRING);
      if (!saveElement("Parameter", Attributes)) success = false;
      break;

    case CCopasiParameter::KEY:
      Attributes.add("value", * parameter.getValue().pKEY);
      if (!saveElement("Parameter", Attributes)) success = false;
      break;

    case CCopasiParameter::FILE:
      File = * parameter.getValue().pFILE;
      if (!CDirEntry::isRelativePath(File) &&
          !CDirEntry::makePathRelative(File, mFilename))
        File = CDirEntry::fileName(File);
      Attributes.add("value", File);
      if (!saveElement("Parameter", Attributes)) success = false;
      break;

    case CCopasiParameter::CN:
      Attributes.add("value", * parameter.getValue().pCN);
      if (!saveElement("Parameter", Attributes)) success = false;
      break;

    case CCopasiParameter::GROUP:
      Attributes.skip(1);
      if (!startSaveElement("ParameterGroup", Attributes)) success = false;
      if (!saveParameterGroup(* parameter.getValue().pGROUP)) success = false;
      if (!endSaveElement("ParameterGroup")) success = false;
      break;

    case CCopasiParameter::INVALID:
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

unsigned C_INT32 CXMLAttributeList::size() {return mAttributeList.size() / 2;}

bool CXMLAttributeList::add(const std::string & name, const C_FLOAT64 & value)
{
  return add(name,
             (CCopasiXMLInterface::DBL) value,
             CCopasiXMLInterface::attribute);
}

bool CXMLAttributeList::setName(const unsigned C_INT32 & index,
                                const std::string & name)
{
  mAttributeList[2 * index] = name;
  return true;
}

const std::string & CXMLAttributeList::getName(const unsigned C_INT32 & index) const
  {return mAttributeList[2 * index];}

const std::string & CXMLAttributeList::getValue(const unsigned C_INT32 & index) const
  {return mAttributeList[2 * index + 1];}

bool CXMLAttributeList::skip(const unsigned C_INT32 & index)
{
  mSaveList[index] = false;
  return true;
}

std::string CXMLAttributeList::getAttribute(const unsigned C_INT32 & index) const
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
