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

const std::string & CMetabNameInterface::getDisplayName(const std::string & key)
{
  CMetab * metab = (CMetab*)(CCopasiContainer*)CKeyFactory::get(key);
  if (metab)
    return getDisplayName(*metab);
  else
    return empty_string;
}

const std::string & CMetabNameInterface::getDisplayName(const CMetab & metab)
{
  return metab.getName();
}

const std::string & CMetabNameInterface::getMetaboliteKey(const CModel* model, const std::string & name)
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
