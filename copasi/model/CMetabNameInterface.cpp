// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"

#include "CMetabNameInterface.h"
#include "CModel.h"
#include "CChemEqParser.h"

#include "copasi/core/CDataContainer.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"

std::string
CMetabNameInterface::getDisplayName(const CModel* model, const std::string & key, const bool & quoted)
{
  CMetab * metab = dynamic_cast< CMetab * >(CRootContainer::getKeyFactory()->get(key));

  if (metab)
    return getDisplayName(model, *metab, quoted);
  else
    return "";
}

std::string
CMetabNameInterface::getDisplayName(const CModel* model, const CMetab & metab, const bool & quoted)
{
  return getDisplayName(model, metab.getObjectName(), metab.getCompartment()->getObjectName(), quoted);
}

std::string
CMetabNameInterface::getDisplayName(const CModel* model,
                                    const std::string & metabolite,
                                    const std::string & compartment,
                                    const bool & quoted)
{
  std::string DefaultCompartment;

  if (model == NULL || model->getCompartments().size() == 0)
    DefaultCompartment = "compartment";
  else
    DefaultCompartment = model->getCompartments()[0].getObjectName();

  std::string Metabolite = quoted ? quote(metabolite, "{}") : metabolite;

  if (quoted && isNumber(Metabolite))
    Metabolite = "\"" + Metabolite + "\"";

  if ((CMetabNameInterface::doesExist(model, metabolite, compartment) &&
       CMetabNameInterface::isUnique(model, metabolite)) ||
      (!CMetabNameInterface::doesExist(model, metabolite, "") &&
       compartment == DefaultCompartment))
    return Metabolite;

  return createUniqueDisplayName(Metabolite, compartment, quoted);
}

std::string
CMetabNameInterface::createUniqueDisplayName(const std::string & metabolite, const std::string & compartment, const bool & quoted)
{
  std::string Compartment = quoted ? quote(compartment, "{}") : compartment;

  if ((quoted && isNumber(Compartment)) ||
      (Compartment.find(' ') != std::string::npos && Compartment.find('"') == std::string::npos))
    Compartment = "\"" + Compartment + "\"";

  std::string Metabolite(metabolite);

  if (quoted && ((Metabolite.find(' ') != std::string::npos || isNumber(Metabolite)) && Metabolite.find('"') == std::string::npos))
    Metabolite = "\"" + Metabolite + "\"";

  return Metabolite + '{' + Compartment + '}';
}

std::string
CMetabNameInterface::createUniqueDisplayName(const CMetab & metab, const bool & quoted)
{
  return createUniqueDisplayName(metab.getObjectName(), metab.getCompartment()->getObjectName(), quoted);
}

std::string
CMetabNameInterface::getMetaboliteKey(const CModel* model,
                                      const std::string & metabolite,
                                      const std::string & compartment)
{
  CMetab * metab = getMetabolite(model, metabolite, compartment);

  if (metab)
    return metab->getKey();
  else
    return "";
}

// static
std::string CMetabNameInterface::getSpeciesCN(const CModel* pModel,
    const std::string & species,
    const std::string & compartment)
{
  assert(pModel != NULL);

  return  pModel->getCN() + ",Vector=Compartments[" + CCommonName::escape(compartment) + "],Vector=Metabolites[" + CCommonName::escape(species) + "]";
}

CMetab *
CMetabNameInterface::getMetabolite(const CModel* model,
                                   const std::string & metabolite,
                                   const std::string & compartment)
{
  size_t Index;

  if (model == NULL)
    return NULL;

  if (compartment != "")
    {
      std::string::size_type compPos = metabolite.find("{" + compartment + "}");
      std::string metabName(metabolite);

      if (compPos != std::string::npos)
        metabName = metabolite.substr(0, compPos);

      Index = model->getCompartments().getIndex(compartment);

      if (Index != C_INVALID_INDEX)
        {
          const CCompartment *pCompartment = &model->getCompartments()[Index];

          Index = pCompartment->getMetabolites().getIndex(metabName);

          if (Index != C_INVALID_INDEX)
            return const_cast< CMetab * >(&pCompartment->getMetabolites()[Index]);
        }

      return NULL;
    }

  return model->findMetabByName(metabolite);
}

bool
CMetabNameInterface::isUnique(const CModel* model, const std::string & name)
{
  if (model == NULL)
    return true;

  CDataContainer::objectMap::range Range = model->getMetabolites().getObjects().equal_range(name);
  CMetab * pSpecies = NULL;
  bool Found = false;

  for (; Range.first != Range.second; ++Range.first)
    if ((pSpecies = dynamic_cast< CMetab * >(*Range.first)) != NULL)
      {
        if (Found) return false;

        Found = true;
      }

  return true;
}

bool
CMetabNameInterface::doesExist(const CModel* model,
                               const std::string & metabolite,
                               const std::string & compartment)
{
  if (model == NULL)
    return false;

  CDataContainer::objectMap::range Range = model->getMetabolites().getObjects().equal_range(metabolite);
  CMetab * pSpecies = NULL;

  for (; Range.first != Range.second; ++Range.first)
    if ((pSpecies = dynamic_cast< CMetab * >(*Range.first)) != NULL)
      {
        if (compartment.empty() ||
            pSpecies->getCompartment()->getObjectName() == compartment) return true;
      }

  return false;
}

// static
std::pair< std::string, std::string >
CMetabNameInterface::splitDisplayName(const std::string & name)
{
  // parse the description into a linked node tree
  std::stringstream buffer((name.find('"') != std::string::npos ? name :  quote(name)) + " ->");

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

// static
std::string
CMetabNameInterface::unQuote(const std::string & displayName)
{
  // parse the description into a linked node tree
  std::stringstream buffer(displayName + " ->");

  CChemEqParser Parser(&buffer);

  std::pair< std::string, std::string > Names;

  if (Parser.yyparse() != 0)
    {
      Names.first = displayName;
      Names.second = "";
    }
  else
    {
      Names.first = Parser.getSubstrateNames()[0];
      Names.second = Parser.getSubstrateCompartments()[0];
    }

  std::string Name = Names.first;

  if (Names.second != "")
    {
      std::string compartment = Names.second;

      if (compartment.find(' ') != std::string::npos)
        compartment = "\"" + compartment + "\"";

      Name += "{" + compartment + "}";
    }

  return Name;
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
