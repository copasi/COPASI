// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunctionParameters.cpp,v $
//   $Revision: 1.41 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/03/09 09:56:18 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CFunctionParameters
 *
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#include "copasi.h"
#include "CFunctionParameters.h"
#include "utilities/CCopasiException.h"

CFunctionParameters::CFunctionParameters(const std::string & name,
    const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Variable Description"),
    mParameters("Variables", this)
{CONSTRUCTOR_TRACE;}

CFunctionParameters::CFunctionParameters(const CFunctionParameters & src,
    const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mParameters(src.mParameters, this)
{CONSTRUCTOR_TRACE;}

CFunctionParameters::~CFunctionParameters() {DESTRUCTOR_TRACE;}

void CFunctionParameters::cleanup()
{
  mParameters.cleanup();
}

CFunctionParameters & CFunctionParameters::operator=(const CFunctionParameters & src)
{
  mParameters.deepCopy(src.mParameters);
  return *this;
}

void CFunctionParameters::add(const CFunctionParameter & parameter)
{
  mParameters.add(parameter);
}

bool CFunctionParameters::add(CFunctionParameter * parameter,
                              const bool & adopt)
{
  mParameters.add(parameter, adopt);

  return true;
}

bool CFunctionParameters::add(const std::string & name,
                              const CFunctionParameter::DataType & type,
                              CFunctionParameter::Role usage)
{
  unsigned C_INT32 Index = mParameters.getIndex(name);

  if (Index != C_INVALID_INDEX)
    return false;

  CFunctionParameter *parameter =
    new CFunctionParameter(name, type, usage);
  mParameters.add(parameter, true);

  return true;
}

void CFunctionParameters::remove(const std::string & name)
{
  mParameters.remove(name);
}

CFunctionParameter * CFunctionParameters::operator[](unsigned C_INT32 index)
{return mParameters[index];}

const CFunctionParameter * CFunctionParameters::operator[](unsigned C_INT32 index) const
  {return mParameters[index];}

CFunctionParameter * CFunctionParameters::operator[](const std::string &name)
{return mParameters[name];}

const CFunctionParameter * CFunctionParameters::operator[](const std::string &name) const
  {return mParameters[name];}

unsigned C_INT32 CFunctionParameters::size() const {return mParameters.size();}

void CFunctionParameters::swap(const unsigned C_INT32 & from, const unsigned C_INT32 & to)
{mParameters.swap(from, to);}

const CFunctionParameter *
CFunctionParameters::getParameterByUsage(CFunctionParameter::Role usage,
    unsigned C_INT32 & pos) const
  {
    unsigned C_INT32 i, imax = mParameters.size();

    for (i = pos; i < imax; i++)
      if (mParameters[i]->getUsage() == usage)
        {
          pos = i + 1;
          return mParameters[i];
        }

    CCopasiMessage(CCopasiMessage::WARNING,
                   MCFunctionParameters + 2,
                   CFunctionParameter::RoleNameDisplay[usage].c_str(), pos);

    return NULL;
  }

unsigned C_INT32 CFunctionParameters::getNumberOfParametersByUsage(CFunctionParameter::Role usage) const
  {
    unsigned C_INT32 i, imax = mParameters.size();
    unsigned C_INT32 count = 0;

    for (i = 0; i < imax; i++)
      if (mParameters[i]->getUsage() == usage) ++count;

    return count;
  }

unsigned C_INT32 CFunctionParameters::findParameterByName(const std::string & name,
    CFunctionParameter::DataType & dataType) const
  {
    //std::string VectorName = name.substr(0, name.find_last_of('_'));
    std::string Name;
    unsigned C_INT32 i, imax = mParameters.size();

    for (i = 0; i < imax; i++)
      {
        Name = mParameters[i]->getObjectName();

        if (Name == name)
          {
            dataType = mParameters[i]->getType();
            return i;
          }
      }

    return C_INVALID_INDEX;
  }

bool CFunctionParameters::isVector(CFunctionParameter::Role role) const
  {
    unsigned C_INT32 i, imax = mParameters.size();

    for (i = 0; i < imax; i++)
      if (mParameters[i]->getUsage() == role)
        return mParameters[i]->getType() >= CFunctionParameter::VINT32;
    //this assumes that if a parameter is not a vector then there
    //will not be a vector parameter with the same role.
    return false;
  }

bool CFunctionParameters::operator==(const CFunctionParameters & rhs) const
  {
    if (size() != rhs.size()) return false;

    C_INT32 i, imax = size();
    for (i = 0; i < imax; ++i)
      {
        if (mParameters[i]->getObjectName() != rhs.mParameters[i]->getObjectName()) return false;
        if (mParameters[i]->getType() != rhs.mParameters[i]->getType()) return false;
        if (mParameters[i]->getUsage() != rhs.mParameters[i]->getUsage()) return false;
      }
    return true;
  }

std::ostream & operator<<(std::ostream &os, const CFunctionParameters & d)
{
  //os << "++++CFunctionParameters: " << std::endl;
  //os << "    CFunctionParameters.mParameters " << std::endl << d.mParameters;
  //os << "----CFunctionParameters " << std::endl;

  C_INT32 i, imax = d.mParameters.size();
  for (i = 0; i < imax; ++i)
    {
      if (0 == i)
        os << "  (";
      else
        os << "    ";

      os << *d.mParameters[i];

      if (imax - 1 == i)
        os << ")\n";
      else
        os << ",\n";
    }

  return os;
}
