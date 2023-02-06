// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CFunctionParameters
 *
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#include "copasi/copasi.h"
#include "CFunctionParameters.h"
#include "copasi/utilities/CCopasiException.h"

CFunctionParameters::CFunctionParameters(const std::string & name,
    const CDataContainer * pParent):
  CDataContainer(name, pParent, "Variable Description"),
  mParameters("Variables", this)
{CONSTRUCTOR_TRACE;}

CFunctionParameters::CFunctionParameters(const CFunctionParameters & src,
    const CDataContainer * pParent):
  CDataContainer(src, pParent),
  mParameters(src.mParameters, this)
{CONSTRUCTOR_TRACE;}

CFunctionParameters::~CFunctionParameters() {DESTRUCTOR_TRACE;}

void CFunctionParameters::cleanup()
{
  mParameters.cleanup();
}

CFunctionParameters & CFunctionParameters::operator=(const CFunctionParameters & src)
{
  if (this == &src)
    return *this;

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
  size_t Index = mParameters.getIndex(name);

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

CFunctionParameter * CFunctionParameters::operator[](size_t index)
{return &mParameters[index];}

const CFunctionParameter * CFunctionParameters::operator[](size_t index) const
{return &mParameters[index];}

CFunctionParameter * CFunctionParameters::operator[](const std::string &name)
{return &mParameters[name];}

const CFunctionParameter * CFunctionParameters::operator[](const std::string &name) const
{return &mParameters[name];}

CFunctionParameters::iterator CFunctionParameters::begin()
{
  return mParameters.begin();
}

CFunctionParameters::iterator CFunctionParameters::end()
{
  return mParameters.end();
}

CFunctionParameters::const_iterator CFunctionParameters::begin() const
{
  return mParameters.begin();
}

CFunctionParameters::const_iterator CFunctionParameters::end() const
{
  return mParameters.end();
}

CFunctionParameters::name_iterator CFunctionParameters::begin_name()
{
  return mParameters.beginName();
}

CFunctionParameters::name_iterator CFunctionParameters::end_name()
{
  return mParameters.endName();
}

CFunctionParameters::const_name_iterator CFunctionParameters::begin_name() const
{
  return mParameters.beginName();
}

CFunctionParameters::const_name_iterator CFunctionParameters::end_name() const
{
  return mParameters.endName();
}

CDataVectorNS< CFunctionParameter > & CFunctionParameters::getParameters()
{
  return mParameters;
}

size_t CFunctionParameters::size() const {return mParameters.size();}

void CFunctionParameters::swap(const size_t & from, const size_t & to)
{mParameters.swap(from, to);}

const CFunctionParameter *
CFunctionParameters::getParameterByUsage(CFunctionParameter::Role usage,
    size_t & pos) const
{
  size_t i, imax = mParameters.size();

  for (i = pos; i < imax; i++)
    if (mParameters[i].getUsage() == usage)
      {
        pos = i + 1;
        return & mParameters[i];
      }

  CCopasiMessage(CCopasiMessage::WARNING,
                 MCFunctionParameters + 2,
                 CFunctionParameter::RoleNameDisplay[usage].c_str(), pos);

  return NULL;
}

size_t CFunctionParameters::getNumberOfParametersByUsage(CFunctionParameter::Role usage) const
{
  size_t i, imax = mParameters.size();
  size_t count = 0;

  for (i = 0; i < imax; i++)
    if (mParameters[i].getUsage() == usage) ++count;

  return count;
}

size_t CFunctionParameters::findParameterByName(const std::string & name,
    const CFunctionParameter ** ppFunctionParameter) const
{
  std::string Name;
  size_t imax = mParameters.size();

  size_t Index = mParameters.getIndex(name);

  if (ppFunctionParameter != NULL)
    if (Index != C_INVALID_INDEX)
      *ppFunctionParameter = &mParameters[Index];
    else
      *ppFunctionParameter = NULL;

  return Index;
}

bool CFunctionParameters::isVector(CFunctionParameter::Role role) const
{
  size_t i, imax = mParameters.size();

  for (i = 0; i < imax; i++)
    if (mParameters[i].getUsage() == role)
      return mParameters[i].getType() >= CFunctionParameter::DataType::VINT32;

  //this assumes that if a parameter is not a vector then there
  //will not be a vector parameter with the same role.
  return false;
}

bool CFunctionParameters::operator==(const CFunctionParameters & rhs) const
{
  if (size() != rhs.size()) return false;

  CFunctionParameter::Role lhsRole, rhsRole;

  size_t i, imax = size();

  for (i = 0; i < imax; ++i)
    {
      if (mParameters[i].getObjectName() != rhs.mParameters[i].getObjectName()) return false;

      if (mParameters[i].getType() != rhs.mParameters[i].getType()) return false;

      lhsRole = mParameters[i].getUsage();
      rhsRole = rhs.mParameters[i].getUsage();

      // We do not destinguish between PARAMETER and VARIABLE
      if ((lhsRole == CFunctionParameter::Role::PARAMETER || lhsRole == CFunctionParameter::Role::VARIABLE) &&
          (rhsRole == CFunctionParameter::Role::PARAMETER || rhsRole == CFunctionParameter::Role::VARIABLE))
        continue;

      if (lhsRole != rhsRole) return false;
    }

  return true;
}

std::ostream & operator<<(std::ostream &os, const CFunctionParameters & d)
{
  //os << "++++CFunctionParameters: " << std::endl;
  //os << "    CFunctionParameters.mParameters " << std::endl << d.mParameters;
  //os << "----CFunctionParameters " << std::endl;

  size_t i, imax = d.mParameters.size();

  for (i = 0; i < imax; ++i)
    {
      if (0 == i)
        os << "  (";
      else
        os << "    ";

      os << d.mParameters[i];

      if (imax - 1 == i)
        os << ")\n";
      else
        os << ",\n";
    }

  return os;
}
