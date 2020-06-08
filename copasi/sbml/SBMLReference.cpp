// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/copasi.h"

#include "SBMLReference.h"

std::string SBMLReference::NotFound = "";

SBMLReference::SBMLReference():
  mURL(""),
  mIdToKey(),
  mKeyToId()
{}

SBMLReference::SBMLReference(const SBMLReference & src):
  mURL(src.mURL),
  mIdToKey(src.mIdToKey),
  mKeyToId(src.mKeyToId)
{}

SBMLReference::~SBMLReference()
{}

bool SBMLReference::setURL(const std::string & url)
{
  mURL = url;
  return true;
}

const std::string & SBMLReference::getURL() const
{return mURL;}

const std::string & SBMLReference::getSBMLid(const std::string & key) const
{
  const_iterator it = mKeyToId.find(key);

  if (it != mKeyToId.end())
    return it->second;
  else
    return NotFound;
}

const std::string & SBMLReference::getCOPASIkey(const std::string & id) const
{
  const_iterator it = mIdToKey.find(id);

  if (it != mIdToKey.end())
    return it->second;
  else
    return NotFound;
}

bool SBMLReference::add(const std::string & id, const std::string & key)
{
  if (mIdToKey.find(id) != mIdToKey.end() ||
      mKeyToId.find(key) != mKeyToId.end()) return false;

  mIdToKey[id] = key;
  mKeyToId[key] = id;

  return true;
}

bool SBMLReference::removeSBMLid(const std::string & id)
{
  std::map<std::string, std::string>::iterator itId = mIdToKey.find(id);

  if (itId == mIdToKey.end()) return false;

  std::map<std::string, std::string>::iterator itKey = mKeyToId.find(itId->second);

  mIdToKey.erase(itId);

  if (itKey == mKeyToId.end()) return false;

  mKeyToId.erase(itKey);

  return true;
}

bool SBMLReference::removeCOPASIkey(const std::string & key)
{
  std::map<std::string, std::string>::iterator itKey = mKeyToId.find(key);

  if (itKey == mKeyToId.end()) return false;

  std::map<std::string, std::string>::iterator itId = mIdToKey.find(itKey->second);

  mKeyToId.erase(itKey);

  if (itId == mIdToKey.end()) return false;

  mIdToKey.erase(itId);

  return true;
}

SBMLReference::const_iterator SBMLReference::beginCOPASIkey() const
{return mKeyToId.begin();}

SBMLReference::const_iterator SBMLReference::endCOPASIkey() const
{return mKeyToId.end();}

SBMLReference::const_iterator SBMLReference::beginSBMLid() const
{return mIdToKey.begin();}

SBMLReference::const_iterator SBMLReference::endSBMLid() const
{return mIdToKey.end();}
