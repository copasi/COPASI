// Copyright (C) 2011 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <map>
#include <iostream>

#include "CModelParameterGroup.h"

CModelParameterGroup::CModelParameterGroup(CModelParameterGroup * pParent, const CModelParameter::Type & type):
  CModelParameter(pParent, type),
  mModelParameters()
{}

CModelParameterGroup::CModelParameterGroup(const CModelParameterGroup & src,
    CModelParameterGroup * pParent,
    const bool & createMissing):
  CModelParameter(src, pParent),
  mModelParameters()
{
  assignGroupContent(src, createMissing);
}

// virtual
CModelParameterGroup::~CModelParameterGroup()
{
  clear();
}

void CModelParameterGroup::assignGroupContent(const CModelParameterGroup & src,
    const bool & createMissing)
{
  clear();

  mModelParameters.resize(src.mModelParameters.size());

  const_iterator itSrc = src.begin();
  const_iterator endSrc = src.end();
  iterator it = begin();

  for (; itSrc != endSrc; ++itSrc)
    {
      if (createMissing ||
          (*itSrc)->getCompareResult() != Missing)
        {
          switch ((*itSrc)->getType())
            {
              case Compartment:
                *it = new CModelParameterCompartment(*static_cast< CModelParameterCompartment *>(*itSrc), this);
                break;

              case Species:
                *it = new CModelParameterSpecies(*static_cast< CModelParameterSpecies *>(*itSrc), this);
                break;

              case ReactionParameter:
                *it = new CModelParameterReactionParameter(*static_cast< CModelParameterReactionParameter *>(*itSrc), this);
                break;

              case Model:
              case ModelValue:
                *it = new CModelParameter(**itSrc, this);
                break;

              case Reaction:
              case Group:
                *it = new CModelParameterGroup(*static_cast< CModelParameterGroup *>(*itSrc), this, createMissing);
                break;

              default:
                break;
            }

          // We need to advance the insert point.
          ++it;
        }
    }

  if (it != mModelParameters.end())
    {
      mModelParameters.erase(it, mModelParameters.end());
    }
}

CModelParameter * CModelParameterGroup::add(const CModelParameter::Type & type)
{
  CModelParameter * pModelParameter = NULL;

  switch (type)
    {
      case Compartment:
        pModelParameter = new CModelParameterCompartment(this);
        break;

      case Species:
        pModelParameter = new CModelParameterSpecies(this);
        break;

      case ReactionParameter:
        pModelParameter = new CModelParameterReactionParameter(this, type);
        break;

      case Model:
      case ModelValue:
        pModelParameter = new CModelParameter(this, type);
        break;

      case Reaction:
      case Group:
        pModelParameter = new CModelParameterGroup(this, type);
        break;

      default:
        return pModelParameter;
        break;
    }

  add(pModelParameter);

  return pModelParameter;
}

void CModelParameterGroup::add(CModelParameter * pModelParameter)
{
  mModelParameters.push_back(pModelParameter);
}

void CModelParameterGroup::remove(CModelParameter * pModelParameter)
{
  iterator it = begin();
  iterator End = end();

  for (; it != End; ++it)
    {
      if (*it == pModelParameter)
        {
          mModelParameters.erase(it);
          break;
        }
    }
}

void CModelParameterGroup::remove(const size_t & index)
{
  if (index < mModelParameters.size())
    {
      iterator it = mModelParameters.begin() + index;
      pdelete(*it);

      mModelParameters.erase(it);
    }
}

size_t CModelParameterGroup::size() const
{
  return mModelParameters.size();
}

CModelParameterGroup::iterator CModelParameterGroup::begin()
{
  return mModelParameters.begin();
}

CModelParameterGroup::iterator CModelParameterGroup::end()
{
  return mModelParameters.end();
}

CModelParameterGroup::const_iterator CModelParameterGroup::begin() const
{
  return mModelParameters.begin();
}

CModelParameterGroup::const_iterator CModelParameterGroup::end() const
{
  return mModelParameters.end();
}

void CModelParameterGroup::compile()
{
  CModelParameter::compile();

  iterator it = begin();
  iterator End = end();

  for (; it != End; ++it)
    {
      (*it)->compile();
    }
}

void CModelParameterGroup::clear()
{
  // Clear existing model parameters.
  iterator it = begin();
  iterator End = end();

  for (; it != End; ++it)
    {
      (*it)->setParent(NULL);
      pdelete(*it);
    }

  mModelParameters.clear();
}

// virtual
const CModelParameter::CompareResult & CModelParameterGroup::diff(const CModelParameter & other,
    const CModelParameter::Framework & framework,
    const bool & createMissing)
{
  // We can only work on reactions, groups or sets.
  assert(other.getType() == Reaction ||
         other.getType() == Group ||
         other.getType() == Set);

  if (mCompareResult == Missing ||
      mCompareResult == Obsolete)
    {
      return mCompareResult;
    }

  mCompareResult = Identical;

  const CModelParameterGroup * pOther = dynamic_cast< const CModelParameterGroup * >(&other);

  const_iterator itConst = pOther->begin();
  const_iterator endConst = pOther->end();

  std::map< CCopasiObjectName, CModelParameter * > Map;

  for (; itConst != endConst; ++itConst)
    {
      Map[(*itConst)->getCN()] = *itConst;
    }

  iterator itThis = begin();
  iterator endThis = end();

  for (; itThis != endThis; ++itThis)
    {
      std::map< CCopasiObjectName, CModelParameter * >::const_iterator itOther = Map.find((*itThis)->getCN());

      if (itOther == Map.end())
        {
          (*itThis)->setCompareResult(Obsolete);
          mCompareResult = Modified;

          continue;
        }

      if ((*itThis)->diff(*itOther->second, framework, createMissing) != Identical)
        {
          mCompareResult = Modified;
        }

      Map.erase(itOther->first);
    }

  if (createMissing)
    {
      std::map< CCopasiObjectName, CModelParameter * >::const_iterator itMissing = Map.begin();
      std::map< CCopasiObjectName, CModelParameter * >::const_iterator endMissing = Map.end();

      for (; itMissing != endMissing; ++itMissing)
        {
          CModelParameter * pMissing;

          switch (itMissing->second->getType())
            {
              case Compartment:
                pMissing = new CModelParameterCompartment(*static_cast< CModelParameterCompartment *>(itMissing->second), this);
                break;

              case Species:
                pMissing = new CModelParameterSpecies(*static_cast< CModelParameterSpecies *>(itMissing->second), this);
                break;

              case ReactionParameter:
                pMissing = new CModelParameterReactionParameter(*static_cast< CModelParameterReactionParameter *>(itMissing->second), this);
                break;

              case Model:
              case ModelValue:
                pMissing = new CModelParameter(*itMissing->second, this);
                break;

              case Reaction:
              case Group:
                pMissing = new CModelParameterGroup(*static_cast< CModelParameterGroup *>(itMissing->second), this, createMissing);
                break;

              default:
                break;
            }

          pMissing->setCompareResult(Missing);
          mModelParameters.push_back(pMissing);

          mCompareResult = Modified;
        }
    }
  else if (Map.size() > 0)
    {
      std::map< CCopasiObjectName, CModelParameter * >::const_iterator itMissing = Map.begin();
      std::map< CCopasiObjectName, CModelParameter * >::const_iterator endMissing = Map.end();

      for (; itMissing != endMissing; ++itMissing)
        {
          if (itMissing->second->getCompareResult() != CModelParameter::Missing)
            {
              mCompareResult = Modified;
              break;
            }
        }
    }

  return mCompareResult;
}

// virtual
bool CModelParameterGroup::updateModel()
{
  bool success = true;

  iterator it = begin();
  iterator End = end();

  for (; it != End; ++it)
    {
      success &= (*it)->updateModel();
    }

  return success;
}

// virtual
bool CModelParameterGroup::refreshFromModel(const bool & modifyExistence)
{
  bool success = true;

  if (modifyExistence)
    {
      if (mCompareResult == CModelParameter::Obsolete)
        {
          delete this;

          return true;
        }

      if (mCompareResult == CModelParameter::Missing)
        {
          mCompareResult = CModelParameter::Identical;
        }
    }

  iterator it = begin();
  iterator End = end();

  std::vector< CModelParameter * > ToBeDeleted;

  for (; it != End; ++it)
    {
      if (modifyExistence &&
          (*it)->getCompareResult() == CModelParameter::Obsolete)
        {
          ToBeDeleted.push_back(*it);
        }
      else
        {
          success &= (*it)->refreshFromModel(modifyExistence);
        }
    }

  std::vector< CModelParameter * >::iterator itDelete = ToBeDeleted.begin();
  std::vector< CModelParameter * >::iterator endDelete = ToBeDeleted.end();

  for (; itDelete != endDelete; ++itDelete)
    {
      success &= (*itDelete)->refreshFromModel(modifyExistence);
    }

  return success;
}

CModelParameter * CModelParameterGroup::getModelParameter(const std::string & cn) const
{
  CModelParameter * pModelParameter = NULL;

  const_iterator it = begin();
  const_iterator End = end();

  for (; it != End && pModelParameter == NULL; ++it)
    {
      if (cn == (*it)->getCN())
        {
          pModelParameter = *it;
        }
      else if ((*it)->getType() == CModelParameter::Reaction ||
               (*it)->getType() == CModelParameter::Group ||
               (*it)->getType() == CModelParameter::Set)
        {
          pModelParameter = static_cast< const CModelParameterGroup * >(*it)->getModelParameter(cn);
        }
    }

  return pModelParameter;
}

CModelParameter * CModelParameterGroup::getModelParameter(const std::string & name,
    const CModelParameter::Type & type) const
{
  CModelParameter * pModelParameter = NULL;

  const_iterator it = begin();
  const_iterator End = end();

  for (; it != End && pModelParameter == NULL; ++it)
    {
      if (type == (*it)->getType() &&
          name == (*it)->getName())
        {
          pModelParameter = *it;
        }
      else if ((*it)->getType() == CModelParameter::Reaction ||
               (*it)->getType() == CModelParameter::Group ||
               (*it)->getType() == CModelParameter::Set)
        {
          pModelParameter = static_cast< const CModelParameterGroup * >(*it)->getModelParameter(name, type);
        }
    }

  return pModelParameter;
}

// virtual
size_t CModelParameterGroup::getNumChildren() const
{
  return size();
}

// virtual
const CModelParameter * CModelParameterGroup::getChild(const size_t & index) const
{
  if (index < size())
    {
      return mModelParameters[index];
    }

  return NULL;
}
