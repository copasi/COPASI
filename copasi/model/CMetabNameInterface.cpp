//
//
// C++ Implementation: $MODULE$
//
// Description:
//
//
// Author: sven <sven@ares>, (C) 2003
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "CMetabNameInterface.h"

#include "report/CCopasiContainer.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"

std::string CMetabNameInterface::empty_string = "";

CMetabNameInterface::~CMetabNameInterface()
{}

const std::string & CMetabNameInterface::getDisplayName(const CModel* model, const std::string & key)
{
  CMetab * metab = (CMetab*)(CCopasiContainer*)CKeyFactory::get(key);
  if (metab)
    return getDisplayName(model, *metab);
  else
    return empty_string;
}

const std::string & CMetabNameInterface::getDisplayName(const CModel* model, const CMetab & metab)
{
  return metab.getName();
}

std::string CMetabNameInterface::getMetaboliteKey(const CModel* model, const std::string & name)
{
  CMetab * metab = getMetabolite(model, name);
  if (metab)
    return metab->getKey();
  else
    return empty_string;
}

CMetab * CMetabNameInterface::getMetabolite(const CModel* model, const std::string & name)
{
  C_INT32 index = model->findMetab(name);
  if (index == -1)
    return NULL;
  else
    return model->getMetabolites()[index];
}

bool CMetabNameInterface::isUnique(const CModel* model, const std::string & name)
{
  bool found = false;
  unsigned C_INT32 i;
  CCopasiVectorN< CMetab > metabs = model->getMetabolites();
  std::string metabName;

  for (i = 0; i < metabs.size(); i++)
    {
      metabName = metabs[i]->getName();
      if (metabName == name)
        {
          if (found)
            return false;
          else
            found = true;
        }
    }

  return found;
}

bool CMetabNameInterface::doesExist(const CModel* model, const std::string & name)
{
  //model->findMetab returns -1 if the metabolite is not found and a non-negative integer otherwise
  return (model->findMetab(name) + 1);
}
