// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include <sstream>

#include "copasi.h"

#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/core/CDataObject.h"

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

// static
void CRegisteredCommonName::sanitizeObjectNames()
{
  std::set< CRegisteredCommonName * >::const_iterator it = mSet.begin();
  std::set< CRegisteredCommonName * >::const_iterator itEnd = mSet.end();

  for (; it != itEnd; ++it)
    {
      CCommonName OldCN = **it;
      CCommonName NewCN;

      std::string Separator = "";

      while (!OldCN.empty())
        {
          std::string ObjectType = OldCN.getObjectType();

          // If the object type is String or Separator we must not sanitize.
          if (ObjectType == "Separator" ||
              ObjectType == "String")
            {
              NewCN += Separator + OldCN.getPrimary();
            }
          else
            {
              NewCN += Separator + ObjectType;

              std::string ObjectName = OldCN.getObjectName();
              CDataObject::sanitizeObjectName(ObjectName);

              if (!ObjectName.empty())
                {
                  NewCN += "=" + escape(ObjectName);
                }

              size_t pos = 0;
              std::string ElementName = OldCN.getElementName(pos);
              std::string IndexSeparator = "[";

              while (!ElementName.empty())
                {
                  CDataObject::sanitizeObjectName(ElementName);
                  NewCN += IndexSeparator + ElementName;

                  IndexSeparator = ",";
                  ElementName = OldCN.getElementName(++pos);
                }

              if (pos != 0)
                NewCN += "]";
            }

          OldCN = OldCN.getRemainder();
          Separator = ",";
        }

      // If old an new CNs differ we need to update the registered common name
      if (**it != NewCN)
        {
          **it = NewCN;
        }
    }
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
