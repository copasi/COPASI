/**
 * CCopasiXMLInterface class.
 * The class CCopasiXMLInterface is the interface to various XML document 
 * containing Copasi relevant informtion.
 *
 * Created for Copasi by Stefan Hoops 2003
 */

#include <fstream>
#include <sstream>

#include "copasi.h"
#include "CCopasiXMLInterface.h"
#include "model/CModel.h"

std::string CCopasiXMLInterface::encode(const std::string & str)
{
  /* We first need to encode the ASII string to UTF-8 */
  std::string tmp = utf8(str);
  std::ostringstream xml;

  unsigned C_INT32 i, imax;
  for (i = 0, imax = tmp.length(); i < imax; i++)
    {
      switch (tmp[i])
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
          xml << tmp[i];
          break;
        }
    }

  return xml.str();
}

std::string CCopasiXMLInterface::utf8(const std::string & str)
{
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
    mpModel(NULL),
    mpFunctionList(NULL),
    mpTaskList(NULL),
    mpReportList(NULL),
    mpIstream(NULL),
    mpOstream(NULL),
    mIndent()
{}

CCopasiXMLInterface::~CCopasiXMLInterface() {}

bool CCopasiXMLInterface::load(const std::string & fileName)
{
  std::ifstream is(fileName.c_str());

  if (is.fail()) return false;
  else return load(is);
}

bool CCopasiXMLInterface::save(const std::string & fileName)
{
  std::ofstream os(fileName.c_str());

  if (os.fail()) return false;
  else return save(os);
}

bool CCopasiXMLInterface::setModel(const CModel & model)
{
  mpModel = const_cast<CModel *>(&model);
  return true;
}

CModel * CCopasiXMLInterface::getModel() const {return mpModel;}

bool CCopasiXMLInterface::haveModel() const {return mpModel != NULL;}

bool CCopasiXMLInterface::freeModel()
{
  pdelete(mpModel);
  return true;
}

bool CCopasiXMLInterface::setFunctionList(const CCopasiVectorN< CFunction > & functionList)
{
  mpFunctionList = const_cast<CCopasiVectorN< CFunction > *>(&functionList);
  return true;
}

CCopasiVectorN< CFunction > * CCopasiXMLInterface::getFunctionList() const
  {return mpFunctionList;}

bool CCopasiXMLInterface::haveFunctionList() const
  {return mpFunctionList != NULL;}

bool CCopasiXMLInterface::freeFunctionList()
{
  pdelete(mpFunctionList);
  return true;
}

bool CCopasiXMLInterface::setTaskList(const CCopasiVectorN< CCopasiTask > & taskList)
{
  mpTaskList = const_cast<CCopasiVectorN< CCopasiTask > *>(&taskList);
  return true;
}

CCopasiVectorN< CCopasiTask > * CCopasiXMLInterface::getTaskList() const
  {return mpTaskList;}

bool CCopasiXMLInterface::haveTaskList() const
  {return mpTaskList != NULL;}

bool CCopasiXMLInterface::freeTaskList()
{
  pdelete(mpTaskList);
  return true;
}

bool CCopasiXMLInterface::setReportList(const CCopasiVectorN< CCopasiReport > & reportList)
{
  mpReportList = const_cast<CCopasiVectorN< CCopasiReport > *>(&reportList);
  return true;
}

CCopasiVectorN< CCopasiReport > * CCopasiXMLInterface::getReportList() const
  {return mpReportList;}

bool CCopasiXMLInterface::haveReportList() const
  {return mpReportList != NULL;}

bool CCopasiXMLInterface::freeReportList()
{
  pdelete(mpReportList);
  return true;
}

bool CCopasiXMLInterface::saveElement(const std::string & name,
                                      CXMLAttributeList & attributeList)
{
  *mpOstream << mIndent << "<" << name;

  unsigned C_INT32 i, imax;
  for (i = 0, imax = attributeList.size(); i < imax; i++)
    *mpOstream << " " << attributeList.getAttribute(i);

  *mpOstream << "/>" << std::endl;

  return true;
}

bool CCopasiXMLInterface::startSaveElement(const std::string & name,
    CXMLAttributeList & attributeList)
{
  *mpOstream << mIndent << "<" << name;

  unsigned C_INT32 i, imax;
  for (i = 0, imax = attributeList.size(); i < imax; i++)
    *mpOstream << " " << attributeList.getAttribute(i);

  *mpOstream << ">" << std::endl;

  mIndent += "  ";
  return true;
}

bool CCopasiXMLInterface::endSaveElement(const std::string & name)
{
  *mpOstream << mIndent << "</" << name << ">" << std::endl;

  mIndent.substr(0, mIndent.length() - 2);
  return true;
}

CXMLAttributeList::CXMLAttributeList():
    mAttributeList()
{}

CXMLAttributeList::CXMLAttributeList(const CXMLAttributeList & src):
    mAttributeList(src.mAttributeList)
{}

CXMLAttributeList::~CXMLAttributeList() {}

bool CXMLAttributeList::erase()
{
  mAttributeList.clear();
  return true;
}

bool CXMLAttributeList::addAttribute(const std::string & name,
                                     const std::string & value)
{
  mAttributeList.push_back(name);
  mAttributeList.push_back(CCopasiXMLInterface::encode(value));

  return true;
}
unsigned C_INT32 CXMLAttributeList::size() {return mAttributeList.size() / 2;}

bool CXMLAttributeList::setName(const unsigned C_INT32 & index,
                                const std::string & name)
{
  mAttributeList[2 * index] = name;
  return true;
}

const std::string & CXMLAttributeList::getName(const unsigned C_INT32 & index) const
  {return mAttributeList[2 * index];}

bool CXMLAttributeList::setValue(const unsigned C_INT32 & index,
                                 const std::string & value)
{
  mAttributeList[2 * index + 1] = CCopasiXMLInterface::encode(value);
  return true;
}

const std::string & CXMLAttributeList::getValue(const unsigned C_INT32 & index) const
  {return mAttributeList[2 * index + 1];}

std::string CXMLAttributeList::getAttribute(const unsigned C_INT32 & index) const
  {
    return mAttributeList[2 * index] + "=\"" + mAttributeList[2 * index + 1] + "\"";
  }
