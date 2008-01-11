// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CMetabNameInterface.cpp,v $
//   $Revision: 1.27 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/11 15:12:28 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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

#include "copasi.h"

#include "CMetabNameInterface.h"
#include "CModel.h"
#include "CChemEqParser.h"

#include "report/CCopasiContainer.h"
#include "report/CKeyFactory.h"

CMetabNameInterface::~CMetabNameInterface()
{}

std::string CMetabNameInterface::getDisplayName(const CModel* model, const std::string & key)
{
  CMetab * metab = dynamic_cast< CMetab * >(GlobalKeys.get(key));
  if (metab)
    return getDisplayName(model, *metab);
  else
    return "";
}

std::string CMetabNameInterface::getDisplayName(const CModel* model, const CMetab & metab)
{
  return getDisplayName(model, metab.getObjectName(), metab.getCompartment()->getObjectName());
}

std::string CMetabNameInterface::getDisplayName(const CModel* model,
    const std::string & metabolite,
    const std::string & compartment)
{
  std::string DefaultCompartment;
  if (model->getCompartments().size() == 0)
    DefaultCompartment = "compartment";
  else
    DefaultCompartment = model->getCompartments()[0]->getObjectName();

  std::string Metabolite = quote(metabolite, "{}");
  if (isNumber(Metabolite))
    Metabolite = "\"" + Metabolite + "\"";

  if ((CMetabNameInterface::doesExist(model, metabolite, compartment) &&
       CMetabNameInterface::isUnique(model, metabolite)) ||
      (!CMetabNameInterface::doesExist(model, metabolite, "") &&
       compartment == DefaultCompartment))
    return Metabolite;

  std::string Compartment = quote(compartment, "{}");
  if (isNumber(Compartment))
    Compartment = "\"" + Compartment + "\"";

  return Metabolite + '{' + Compartment + '}';
}

std::string CMetabNameInterface::getMetaboliteKey(const CModel* model,
    const std::string & metabolite,
    const std::string & compartment)
{
  CMetab * metab = getMetabolite(model, metabolite, compartment);
  if (metab)
    return metab->getKey();
  else
    return "";
}

CMetab * CMetabNameInterface::getMetabolite(const CModel* model,
    const std::string & metabolite,
    const std::string & compartment)
{
  unsigned C_INT32 Index;

  if (compartment != "")
    {
      Index = model->getCompartments().getIndex(compartment);
      if (Index != C_INVALID_INDEX)
        {
          CCompartment *pCompartment = model->getCompartments()[Index];

          Index = pCompartment->getMetabolites().getIndex(metabolite);
          if (Index != C_INVALID_INDEX)
            return pCompartment->getMetabolites()[Index];
        }

      return NULL;
    }

  Index = model->findMetabByName(metabolite);

  if (Index != C_INVALID_INDEX)
    return model->getMetabolites()[Index];

  return NULL;
}

bool CMetabNameInterface::isUnique(const CModel* model, const std::string & name)
{
  bool unique = true;
  unsigned C_INT32 i;
  const CCopasiVector< CMetab > & metabs = model->getMetabolites();
  std::string metabName;

  for (i = 0; i < metabs.size(); i++)
    {
      metabName = metabs[i]->getObjectName();
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

bool CMetabNameInterface::doesExist(const CModel* model,
                                    const std::string & metabolite,
                                    const std::string & compartment)
{
  if (compartment != "")
    {
      unsigned C_INT32 Index = model->getCompartments().getIndex(compartment);
      if (Index == C_INVALID_INDEX) return false;

      Index = model->getCompartments()[Index]->getMetabolites().getIndex(metabolite);

      return (Index != C_INVALID_INDEX);
    }
  else
    return (model->findMetabByName(metabolite) != C_INVALID_INDEX);
}

std::pair< std::string, std::string > CMetabNameInterface::splitDisplayName(const std::string & name)
{
  // parse the description into a linked node tree
  std::stringstream buffer(name + " ->");

  CChemEqParser Parser(&buffer);

  std::pair< std::string, std::string > Result;

  if (Parser.yyparse() != 0)
    {
      Result.first = "";
      Result.second = "";
    }
  else
    {
      Result.first = Parser.getSubstrateNames()[0];
      Result.second = Parser.getSubstrateCompartments()[0];
    }

  return Result;
}

#ifdef XXXX
std::string CMetabNameInterface::extractCompartmentName(const std::string & name)
{
  // parse the description into a linked node tree
  std::stringstream buffer(name);
  buffer << " ->";

  CChemEqParser Parser(&buffer);

  if (Parser.yyparse() != 0) return "";

  return Parser.getSubstrateCompartments()[0];
}

std::string CMetabNameInterface::extractMetabName(const std::string & name)
{
  // parse the description into a linked node tree
  std::stringstream buffer(name);
  buffer << " ->";

  CChemEqParser Parser(&buffer);

  if (Parser.yyparse() != 0) return "";

  return Parser.getSubstrateNames()[0];
}

bool CMetabNameInterface::isValidMetabDisplayName(const std::string & name)
{
  // parse the description into a linked node tree
  std::stringstream buffer(name);
  buffer << " ->";

  CChemEqParser Parser(&buffer);

  return (Parser.yyparse() == 0);
}
#endif // XXXX
