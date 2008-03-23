// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseModel.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: aruff $
//   $Date: 2008/03/23 20:39:15 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CMiaseModel.h"

CMiaseChange::CMiaseChange() : CMiaseBase()
{}

CMiaseChange::~CMiaseChange()
{}

std::string CMiaseChange::returnTarget()
{
  return mTarget;
}

void CMiaseChange::setTarget(std::string target)
{
  mTarget = target;
}

//*****************************************************************************

CMiaseChangeAttribute::CMiaseChangeAttribute() : CMiaseChange()
{
  mType = ATTRIBUTE;
}

CMiaseChangeAttribute::~CMiaseChangeAttribute()
{}

CMiaseChange::TYPE CMiaseChangeAttribute::getType()
{
  return mType;
}

std::string CMiaseChangeAttribute::returnNewValue()
{
  return mNewValue;
}

void CMiaseChangeAttribute::setNewValue(std::string newValue)
{
  mNewValue = newValue;
}

//*****************************************************************************

CMiaseChangeMath::CMiaseChangeMath() : CMiaseChange()
{
  mType = MATH;
}

CMiaseChangeMath::~CMiaseChangeMath()
{}

CMiaseChange::TYPE CMiaseChangeMath::getType()
{
  return mType;
}

std::string CMiaseChangeMath::returnNewMath()
{
  return mNewMath;
}

void CMiaseChangeMath::setNewMath(std::string newMath)
{
  mNewMath = newMath;
}

//*****************************************************************************

CMiaseModel::CMiaseModel() : CMiaseBaseEnhanced()
{}

CMiaseModel::~CMiaseModel()
{
  mListOfChanges.clear();
}

std::string CMiaseModel::getType()
{
  return mType;
}

std::string CMiaseModel::getSource()
{
  return mSource;
}

void CMiaseModel::setType(std::string type)
{
  mType = type;
}

void CMiaseModel::setSource(std::string source)
{
  mSource = source;
}

void CMiaseModel::addChange (CMiaseChange* change)
{
  mListOfChanges.push_back(change);
}

CMiaseChange* CMiaseModel::getChange(int num)
{
  return mListOfChanges[ num ];
}

CMiaseChange* CMiaseModel::getLastChange()
{
  return mListOfChanges[ mListOfChanges.size() - 1];
}

//*****************************************************************************
