// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelParameterGroup.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/21 17:45:15 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <map>

#include "CModelParameterGroup.h"


CModelParameterGroup::CModelParameterGroup(CModelParameterGroup * pParent, const CModelParameter::Type & type):
    CModelParameter(pParent, type),
    mModelParameters()
{}

CModelParameterGroup::CModelParameterGroup(const CModelParameterGroup & src, CModelParameterGroup * pParent):
    CModelParameter(src, pParent),
    mModelParameters()
{
  mModelParameters.resize(src.mModelParameters.size());

  const_iterator itSrc = src.begin();
  const_iterator endSrc = src.end();
  iterator it = begin();

  for (; itSrc != endSrc; ++itSrc, ++it)
    {
      *it = new CModelParameter(**itSrc, this);
    }
}


// virtual
CModelParameterGroup::~CModelParameterGroup()
{
  clear();
}

// virtual
CModel * CModelParameterGroup::getModel()
{
  return mpParent->getModel();
}

CModelParameter * CModelParameterGroup::add(const CModelParameter::Type & type)
{
  CModelParameter * pModelParameter = NULL;

  switch (type)
    {
      case Model:
      case Compartment:
      case Species:
      case ModelValue:
      case ReactionParameter:
        pModelParameter = new CModelParameter(this, type);
        break;

      case Group:
        pModelParameter = new CModelParameterGroup(this, type);
        break;

      default:
        return pModelParameter;
        break;
    }

  mModelParameters.push_back(pModelParameter);

  return pModelParameter;
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
      pdelete(*it);
    }
}

// virtual
const CModelParameter::CompareResult & CModelParameterGroup::diff(const CModelParameter & other)
{
  mCompareResult = Identical;

  // We can only work on groups or sets.
  assert(other.getType() == Group || other.getType() == Set);

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

      if ((*itThis)->diff(*itOther->second) != Identical)
        {
          mCompareResult = Modified;
        }

      Map.erase(itOther->first);
    }

  std::map< CCopasiObjectName, CModelParameter * >::const_iterator itMissing = Map.begin();
  std::map< CCopasiObjectName, CModelParameter * >::const_iterator endMissing = Map.end();

  for (; itMissing != endMissing; ++itMissing)
    {
      CModelParameter * pMissing;

      if (itMissing->second->getType() != Group)
        {
          pMissing = new CModelParameterGroup(*static_cast< CModelParameterGroup *>(itMissing->second), this);
        }
      else
        {
          pMissing = new CModelParameter(*itMissing->second, this);
        }

      pMissing->setCompareResult(Missing);
      mCompareResult = Modified;
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
