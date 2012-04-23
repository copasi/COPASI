// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLStyle.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/04/23 15:44:52 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <sstream>

#include <sbml/packages/render/sbml/Style.h>

#include "CLStyle.h"

#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/report/CKeyFactory.h"

/**
 * Constructor.
 */
CLStyle::CLStyle(const std::string& name, CCopasiContainer* pParent):
    CLBase(),
    CCopasiContainer(name, pParent),
    mpGroup(NULL),
    mKey("")
{
}

/**
 * Copy Constructor.
 */
CLStyle::CLStyle(const CLStyle& source, CCopasiContainer* pParent):
    CLBase(source),
    CCopasiContainer(source, pParent),
    mRoleList(source.mRoleList),
    mTypeList(source.mTypeList),
    mpGroup(NULL),
    mKey("")
{
  if (source.mpGroup != NULL)
    {
      this->mpGroup = new CLGroup(*source.mpGroup, this);
    }
}

/**
 * Constructor to generate object from the corresponding SBML object.
 */
CLStyle::CLStyle(const Style& source, const std::string& name, CCopasiContainer* pParent):
    CLBase(),
    CCopasiContainer(name, pParent),
    mpGroup(new CLGroup(*source.getGroup(), this)),
    mKey("")
{
  CLStyle::readIntoSet(CLStyle::createStringFromSet(source.getRoleList()), this->mRoleList);
  CLStyle::readIntoSet(CLStyle::createStringFromSet(source.getTypeList()), this->mTypeList);
}

/**
 * Destructor
 */
CLStyle::~CLStyle()
{
  CCopasiRootContainer::getKeyFactory()->remove(this->mKey);
}

/**
 * Sets the group.
 */
void CLStyle::setGroup(const CLGroup* pGroup)
{
  if (pGroup)
    {
      if (this->mpGroup != NULL)
        {
          delete this->mpGroup;
        }

      this->mpGroup = new CLGroup(*pGroup, this);
    }
}

/**
 * Returns the group.
 */
const CLGroup* CLStyle::getGroup() const
{
  return this->mpGroup;
}

/**
 * Returns the group.
 */
CLGroup* CLStyle::getGroup()
{
  return this->mpGroup;
}

/**
 * Returns the number roles ids in the role list.
 */
size_t CLStyle::getNumRoles() const
{
  return this->mRoleList.size();
}

/**
 * Adds an role to the role list.
 */
void CLStyle::addRole(const std::string& role)
{
  this->mRoleList.insert(role);
}

/**
 * Checks whether a given role is in the role list.
 */
bool CLStyle::isInRoleList(const std::string& role) const
{
  return (this->mRoleList.find(role) != this->mRoleList.end());
}

/**
 * Removes an role from the role list.
 */
void CLStyle::removeRole(const std::string& role)
{
  this->mRoleList.erase(role);
}

/**
 * Returns the number of types in the type list.
 */
size_t CLStyle::getNumTypes() const
{
  return this->mTypeList.size();
}

/**
 * Adds an type to the type list.
 */
void CLStyle::addType(const std::string& type)
{
  this->mTypeList.insert(type);
}

/**
 * Checks whether a given type is in the type list.
 */
bool CLStyle::isInTypeList(const std::string& type) const
{
  return (this->mTypeList.find(type) != this->mTypeList.end());
}

/**
 * Removes an type from the type list.
 */
void CLStyle::removeType(const std::string& type)
{
  this->mTypeList.erase(type);
}

void CLStyle::readIntoSet(const std::string& s, std::set<std::string>& set)
{
  std::string delimiter = "\n\r\t ";
  std::size_t lastPos = s.find_first_not_of(delimiter);
  std::size_t pos;

  while (lastPos != std::string::npos)
    {
      pos = s.find_first_of(delimiter, lastPos);
      set.insert(s.substr(lastPos, pos - lastPos));
      lastPos = s.find_first_not_of(delimiter, pos);
    }
}

std::string CLStyle::createStringFromSet(const std::set<std::string>& set)
{
  std::ostringstream os;
  std::set<std::string>::const_iterator it = set.begin(), endit = set.end();

  while (it != endit)
    {
      os << *it << " ";
      ++it;
    }

  if (!os.str().empty())
    {
      os.str(os.str().substr(0, os.str().size() - 1));
    }

  return os.str();
}

const std::set<std::string>& CLStyle::getRoleList() const
{
  return this->mRoleList;
}

const std::set<std::string>& CLStyle::getTypeList() const
{
  return this->mTypeList;
}

void CLStyle::setRoleList(const std::set<std::string>& roleList)
{
  // I do not check roles on purpose since this is more versatil in the light
  // of future extensions
  this->mRoleList = roleList;
}

void CLStyle::setTypeList(const std::set<std::string>& typeList)
{
  // I do not check types on purpose since this is more versatil in the light
  // of future extensions
  this->mTypeList = typeList;
}

/**
 * Returns the key of the style
 */
const std::string& CLStyle::getKey() const
{
  return this->mKey;
}

/**
 * Adds the attributes for a style object to the passed in.
 * object.
 */
void CLStyle::addSBMLAttributes(Style* pStyle) const
{
  RenderGroup* pG = this->mpGroup->toSBML(pStyle->getLevel(), pStyle->getVersion());
  pStyle->setGroup(pG);
  delete pG;
  std::set<std::string> s;
  CLStyle::readIntoSet(CLStyle::createStringFromSet(this->mRoleList), s);
  pStyle->setRoleList(s);
  s.clear();
  CLStyle::readIntoSet(CLStyle::createStringFromSet(this->mTypeList), s);
  pStyle->setTypeList(s);
}
