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
//#include "utilities/CCopasiVector.h"

std::string CMetabNameInterface::empty_string = "";

CMetabNameInterface::~CMetabNameInterface()
{}

std::string CMetabNameInterface::getDisplayName(const CModel* model, const std::string & key)
{
  CMetab * metab = (CMetab*)(CCopasiContainer*)CKeyFactory::get(key);
  if (metab)
    return getDisplayName(model, *metab);
  else
    return empty_string;
}

std::string CMetabNameInterface::getDisplayName(const CModel* model, const CMetab & metab)
{
  if (CMetabNameInterface::isUnique(model, metab.getName()))
    return metab.getName();
  else
    return metab.getName() + '{' + metab.getCompartment()->getName() + '}';
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
  C_INT32 pos = name.find('{');

  if (pos >= 0)
    {
      std::string metabName = CMetabNameInterface::extractMetabName(model, name);
      std::string compName = CMetabNameInterface::extractCompartmentName(model, name);
      return (model->getCompartments()[compName])->getMetabolites()[metabName];
    }
  else
    {
      C_INT32 index = model->findMetabByName(name);
      if (index == -1)
        return NULL;
      else
        return model->getMetabolites()[index];
    }

  std::string metabName = CMetabNameInterface::extractMetabName(model, name);
  C_INT32 index = model->findMetabByName(name);
  if (index == -1)
    return NULL;
  else
    return model->getMetabolites()[index];
}

bool CMetabNameInterface::isUnique(const CModel* model, const std::string & name)
{
  bool unique = true;
  unsigned C_INT32 i;
  CCopasiVector< CMetab > metabs = model->getMetabolites();
  std::string metabName;

  for (i = 0; i < metabs.size(); i++)
    {
      metabName = metabs[i]->getName();
      if (metabName == name)
        {
          if (unique)
            unique = false;
          else
            return false; //return true
        }
    }

  return true; //return unique;
}

bool CMetabNameInterface::doesExist(const CModel* model, const std::string & name)
{
  C_INT32 pos = name.find('{'), i;
  CCompartment *comp;
  CCopasiVectorNS<CMetab> metabs;

  if (pos >= 0)    //compartment specified, so check if the metabolite exists in this compartment
    {
      if (!pos)
        return false;

      std::string metabName = name. substr(0, pos), s;
      C_INT32 len = name.find('}') - pos - 1;

      C_INT32 index = model -> findCompartment(name.substr(pos + 1, len));
      if (index < 0)   // the specified compartment does not exist
        return false;

      comp = (model->getCompartments())[index];
      metabs = comp->getMetabolites();

      for (i = 0; i < metabs.size(); i++)
        {
          s = metabs[i]->getName();
          if (s == metabName)
            return true;
        }

      return false;
    }
  else
    //model->findMetab returns -1 if the metabolite is not found and a non-negative integer otherwise
    return (model->findMetabByName(name) + 1);
}

std::string CMetabNameInterface::extractCompartmentName(const CModel* model, const std::string & name)
{
  // name is expected to be in the format of "metabolite{compartment}" or simply "metabolite"
  C_INT32 pos1 = name.find('{'), pos2;
  const CCompartment *comp;

  if (pos1 > 0)  // extract the compartment name from the string if specified
    {
      pos2 = name.find('}');
      return name.substr(pos1 + 1, pos2 - pos1 - 1);
    }
  else
    {
      CCopasiVector< CMetab > metabs = model->getMetabolites();
      C_INT32 index = model->findMetabByName(name);

      if (index < 0)  // the metabolite doesn't exist, so return the first compartment of the model
        {
          CCopasiVectorNS< CCompartment > comps = model->getCompartments();
          comp = comps[0];
          return comp->getName();
        }
      else  //return the first compartment where the metabolite is present
        {
          CMetab *metb = metabs[index];
          comp = metb->getCompartment();
          return comp->getName();
        }
    }
}

std::string CMetabNameInterface::extractMetabName(const CModel* model, const std::string & name)
{
  // name is expected to be in the format of "metabolite{compartment}" or simply "metabolite"
  C_INT32 namelength = name.find('{');

  if (namelength >= 0) // compartment is specified, so strip that off
    return name.substr(0, namelength);
  else  //compartment is not specified
    return name;
}

bool CMetabNameInterface::isValidMetabName(const std::string name)
{
  // a valid name does not contain white spaces, and contains either matching or no curly braces
  C_INT32 pos1, pos2, pos3, end;
  end = name.find_last_not_of(" ") + 1;  // the end of the string
  if (end < 0)   // the string consists of white spaces only
    return false;

  // make sure the name is not an empty string
  unsigned C_INT32 len = name.length();
  if (len < 1)
    return false;

  // check for white spaces before the end of the string
  pos1 = name.find(" ");
  if ((pos1 >= 0) && (pos1 <= end))
    return false;

  // curly braces: '{' is not the first character in the string, and appears before '}'
  // if present, '}' should be the last character in the string
  pos1 = name.find('{');
  pos2 = name.find('}');
  pos3 = name.rfind('{');

  // ok if no braces appear
  if ((pos1 < 0) && (pos2 < 0))
    return true;

  // ok  if only one '{' and one '}', braces match, neither metabolite name nor compartment name is an empty string, and '}' is the last character that is not a white space
  if ((pos1 > 0) && (pos1 == pos3) && (pos2 > pos1 + 1) && (pos2 + 1 == end))
    return true;

  // otherwise the name is not valid
  return false;
}
