// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include <sstream>

#include "copasi/copasi.h"

#include "copasi/core/CRegisteredCommonName.h"
#include "copasi/core/CDataObject.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"

using std::string;

//********** CRegisteredCommonName ***************

// static
std::set<CRegisteredCommonName*> CRegisteredCommonName::mSet;

// static
bool CRegisteredCommonName::mEnabled(true);

// static
std::set< CRegisteredCommonName::RenameInterface * > CRegisteredCommonName::mRegisteredHandlers;

CRegisteredCommonName::Rename::Rename(CRegisteredCommonName::Rename::Type method)
  : CRegisteredCommonName::RenameInterface()
  , mMethod(method)
{}

// virtual
CRegisteredCommonName::Rename::~Rename() {}

// virtual
void CRegisteredCommonName::Rename::operator()(const std::string & oldCN,
    const std::string & newCN)
{
  // execute member function
  return (*mMethod)(oldCN, newCN);
}

CRegisteredCommonName::CRegisteredCommonName()
  : CCommonName()
  , mpDataModel(nullptr)
{
#pragma omp critical (cregisteredcommonname_access)
  mSet.insert(this);
}

#ifndef DEPRECATE_CONSTRUCTOR
CRegisteredCommonName::CRegisteredCommonName(const std::string & name)
  : CCommonName(name)
  , mpDataModel(nullptr)
{
  const CDataObject * pObject = CObjectInterface::DataObject(CRootContainer::getRoot()->getObject(name));

  if (pObject != nullptr)
    mpDataModel = pObject->getObjectDataModel();

#pragma omp critical (cregisteredcommonname_access)
  mSet.insert(this);
}
#endif // DEPRECATE_CONSTRUCTOR

CRegisteredCommonName::CRegisteredCommonName(const std::string & name, const CObjectInterface * pObject)
  : CCommonName(name)
  , mpDataModel(CObjectInterface::DataObject(pObject) != nullptr
                ? CObjectInterface::DataObject(pObject)->getObjectDataModel() : nullptr)
{
#pragma omp critical (cregisteredcommonname_access)
  mSet.insert(this);
}

CRegisteredCommonName::CRegisteredCommonName(const CRegisteredCommonName & src)
  : CCommonName(src)
  , mpDataModel(src.mpDataModel)
{
#pragma omp critical (cregisteredcommonname_access)
  mSet.insert(this);
}

CRegisteredCommonName::~CRegisteredCommonName()
{
#pragma omp critical (cregisteredcommonname_access)
  mSet.erase(this);
}

const CDataModel * CRegisteredCommonName::getDataModel() const
{
  return mpDataModel;
}

// static
void CRegisteredCommonName::handle(const std::string & oldCN, const CRegisteredCommonName & newCN)
{
  if (mEnabled)
    {
      std::set< CRegisteredCommonName * >::const_iterator it = mSet.begin();
      std::set< CRegisteredCommonName * >::const_iterator itEnd = mSet.end();

      size_t oldSize = oldCN.size();
      size_t currentSize;

      std::map< std::string, CRegisteredCommonName * > Renamed;

      for (; it != itEnd; ++it)
        {
          // either need to take currentSize out, or need to use the variable
          // using it uninitialized makes no sense.
          currentSize = (*it)->size();

          // We need to make sure that we not change partial names
          if ((currentSize == oldSize ||
               (currentSize > oldSize && (**it)[oldSize] == ','))
              && (newCN.mpDataModel == nullptr
                  || newCN.mpDataModel == (*it)->mpDataModel)
              && oldCN.compare(0, oldSize, **it, 0, oldSize) == 0)
            {
              Renamed.insert(std::make_pair(**it, *it));
              (*it)->replace(0, oldSize, newCN);
            }
        }

      std::set< RenameInterface * >::const_iterator itHandler = mRegisteredHandlers.begin();
      std::set< RenameInterface * >::const_iterator endHandler = mRegisteredHandlers.end();

      for (; itHandler != endHandler; ++itHandler)
        {
          std::map< std::string, CRegisteredCommonName * >::const_iterator itRenamed = Renamed.begin();
          std::map< std::string, CRegisteredCommonName * >::const_iterator endRenamed = Renamed.end();

          for (; itRenamed != endRenamed; ++itRenamed)
            (*itHandler)->operator()(itRenamed->first, *itRenamed->second);
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
      CRegisteredCommonName & NewCN = **it;
      NewCN.clear();

      std::string Separator = "";
      bool ContinueFromElement = false;

      while (!OldCN.empty())
        {
          std::string::size_type pos = OldCN.findNext(",");
          CCommonName Primary(OldCN.substr(0, pos));

          if (pos != std::string::npos)
            {
              OldCN = OldCN.substr(pos + 1);
            }
          else
            {
              OldCN.clear();
            }

          while (!Primary.empty())
            {
              std::string ObjectType = Primary.getObjectType();

              // If the object type is String or Separator we must not sanitize.
              if (ObjectType == "Separator" ||
                  ObjectType == "String")
                {
                  NewCN += Separator + Primary;
                }
              else
                {
                  if (!ContinueFromElement)
                    {
                      NewCN += Separator + ObjectType;

                      std::string ObjectName = Primary.getObjectName();
                      CDataObject::sanitizeObjectName(ObjectName);

                      if (!ObjectName.empty())
                        {
                          NewCN += "=" + escape(ObjectName);
                        }
                    }

                  size_t pos = 0;
                  std::string ElementName = Primary.getElementName(pos);
                  std::string IndexSeparator = "[";

                  while (!ElementName.empty())
                    {
                      CDataObject::sanitizeObjectName(ElementName);
                      NewCN += IndexSeparator + escape(ElementName);

                      if (ObjectType != "Array")
                        {
                          IndexSeparator = ",";
                        }
                      else
                        {
                          IndexSeparator = "][";
                        }

                      ElementName = Primary.getElementName(++pos);
                    }

                  if (pos != 0)
                    {
                      Primary = Primary.getRemainder();
                      NewCN += "]";
                    }
                }

              Primary = Primary.getRemainder();
              ContinueFromElement = !Primary.empty();
              Separator.clear();
            }

          Separator = ",";
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

// static
void CRegisteredCommonName::registerHandler(CRegisteredCommonName::RenameInterface * pRenameHandler)
{
  mRegisteredHandlers.insert(pRenameHandler);
}

// static
void CRegisteredCommonName::deregisterHandler(CRegisteredCommonName::RenameInterface * pRenameHandler)
{
  mRegisteredHandlers.erase(pRenameHandler);
}
