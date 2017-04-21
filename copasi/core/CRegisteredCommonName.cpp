// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include <sstream>

#include "copasi.h"

#include "CRegisteredCommonName.h"

using std::string;

//********** CRegisteredCommonName ***************

// static
std::set<CRegisteredCommonName*> CRegisteredCommonName::mSet;

// static
bool CRegisteredCommonName::mEnabled(true);;

CRegisteredCommonName::CRegisteredCommonName():
  CCommonName()
{
  mSet.insert(this);
}

CRegisteredCommonName::CRegisteredCommonName(const std::string & name):
  CCommonName(name)
{
  mSet.insert(this);
}

CRegisteredCommonName::CRegisteredCommonName(const CRegisteredCommonName & src):
  CCommonName(src)
{
  mSet.insert(this);
}

CRegisteredCommonName::~CRegisteredCommonName()
{
  mSet.erase(this);
}

// static
void CRegisteredCommonName::handle(const std::string & oldCN, const std::string & newCN)
{
  if (mEnabled)
    {
      std::set< CRegisteredCommonName * >::const_iterator it = mSet.begin();
      std::set< CRegisteredCommonName * >::const_iterator itEnd = mSet.end();

      size_t oldSize = oldCN.size();
      size_t currentSize;

      for (; it != itEnd; ++it)
        {
          // either need to take currentSize out, or need to use the variable
          // using it uninitialized makes no sense.
          currentSize = (*it)->size();

          // We need to make sure that we not change partial names
          if ((currentSize == oldSize ||
               (currentSize > oldSize && (**it)[oldSize] == ',')) &&
              oldCN.compare(0, oldSize, **it, 0, oldSize) == 0)
            {
              (**it).replace(0, oldSize, newCN);
            }
        }
    }

  return;
}

/**
 * Enable and disable the rename handler
 * @param const bool & enabled
 */
// static
void CRegisteredCommonName::setEnabled(const bool & enabled)
{
  mEnabled = enabled;
}

// static
const bool & CRegisteredCommonName::isEnabled()
{
  return mEnabled;
}
