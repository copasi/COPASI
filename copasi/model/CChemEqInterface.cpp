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

#include <sstream>

#include "copasi/copasi.h"
#include "CChemEqInterface.h"
#include "CMetabNameInterface.h"
#include "CChemEq.h"
#include "CChemEqParser.h"
#include "CReaction.h"
#include "CModel.h"

#include "copasi/core/CDataVector.h"
#include "copasi/utilities/utility.h"

CChemEqInterface::CChemEqInterface():
  mpChemEq(NULL),
  mpModel(NULL),
  mSubstrateNames(),
  mProductNames(),
  mModifierNames(),
  mSubstrateMult(),
  mProductMult(),
  mModifierMult(),
  mSubstrateCompartments(),
  mProductCompartments(),
  mModifierCompartments(),
  mSubstrateDisplayNames(),
  mProductDisplayNames(),
  mModifierDisplayNames(),
  mReversibility(false)
{}

CChemEqInterface::~CChemEqInterface()
{}

bool CChemEqInterface::init(const CChemEq & ce)
{
  mpChemEq = const_cast< CChemEq * >(&ce);
  mpModel = dynamic_cast< CModel * >(mpChemEq->getObjectAncestor("Model"));

  const CDataVector< CChemEqElement > * elements;
  size_t i, imax;

  elements = &mpChemEq->getSubstrates();
  imax = elements->size();
  mSubstrateNames.resize(imax);
  mSubstrateMult.resize(imax);
  mSubstrateCompartments.resize(imax);

  for (i = 0; i < imax; ++i)
    {
      const CMetab* pMetab = (*elements)[i].getMetabolite();

      // invalid / outdated equation object
      if (pMetab == NULL)
        {
          clearAll();

          return false;
        }

      mSubstrateNames[i] = pMetab->getObjectName();
      mSubstrateMult[i] = (*elements)[i].getMultiplicity();
      mSubstrateCompartments[i] = pMetab->getCompartment()->getObjectName();
    }

  elements = &mpChemEq->getProducts();
  imax = elements->size();
  mProductNames.resize(imax);
  mProductMult.resize(imax);
  mProductCompartments.resize(imax);

  for (i = 0; i < imax; ++i)
    {
      const CMetab* pMetab = (*elements)[i].getMetabolite();

      // invalid / outdated equation object
      if (pMetab == NULL)
        {
          clearAll();

          return false;
        }

      mProductNames[i] = pMetab->getObjectName();
      mProductMult[i] = (*elements)[i].getMultiplicity();
      mProductCompartments[i] = pMetab->getCompartment()->getObjectName();
    }

  elements = &mpChemEq->getModifiers();
  imax = elements->size();
  mModifierNames.resize(imax);
  mModifierMult.resize(imax);
  mModifierCompartments.resize(imax);

  for (i = 0; i < imax; ++i)
    {
      const CMetab* pMetab = (*elements)[i].getMetabolite();

      // invalid / outdated equation object
      if (pMetab == NULL)
        {
          clearAll();

          return false;
        }

      mModifierNames[i] = pMetab->getObjectName();
      mModifierMult[i] = (*elements)[i].getMultiplicity();
      mModifierCompartments[i] = pMetab->getCompartment()->getObjectName();
    }

  mReversibility = mpChemEq->getReversibility();

  buildDisplayNames();

  return true;
}

std::string CChemEqInterface::getChemEqString(bool expanded) const
{
  std::string ChemicalEquation;
  size_t j;

  if ((mSubstrateNames.size() == 0) && (mProductNames.size() == 0) && (mModifierNames.size() == 0))
    return "";

  for (j = 0; j < mSubstrateNames.size(); j++)
    {
      if (j)
        ChemicalEquation += " + ";

      ChemicalEquation += writeElement(mSubstrateDisplayNames[j], mSubstrateMult[j], expanded);
    }

  if (mReversibility)
    ChemicalEquation += " = ";
  else
    ChemicalEquation += " -> ";

  for (j = 0; j < mProductNames.size(); j++)
    {
      if (j)
        ChemicalEquation += " + ";

      ChemicalEquation += writeElement(mProductDisplayNames[j], mProductMult[j], expanded);
    }

  if (mModifierNames.size())
    {
      ChemicalEquation += "; ";

      for (j = 0; j < mModifierNames.size(); j++)
        {
          ChemicalEquation += " ";

          ChemicalEquation += mModifierDisplayNames[j];
        }
    }

  return ChemicalEquation;
}

bool CChemEqInterface::setChemEqString(const std::string & ces)
{
  // parse the description into a linked node tree
  std::istringstream buffer(ces);
  CChemEqParser Parser(&buffer);

  bool success = (Parser.yyparse() == 0);

  if (success)
    {
      mReversibility = Parser.isReversible();

      mSubstrateNames = Parser.getSubstrateNames();
      mSubstrateMult = Parser.getSubstrateMulitplicities();
      mSubstrateCompartments = Parser.getSubstrateCompartments();

      mProductNames = Parser.getProductNames();
      mProductMult = Parser.getProductMulitplicities();
      mProductCompartments = Parser.getProductCompartments();

      mModifierNames = Parser.getModifierNames();
      mModifierMult = Parser.getModifierMulitplicities();
      mModifierCompartments = Parser.getModifierCompartments();
    }

  completeCompartments();

  buildDisplayNames();

  return success;
}

void CChemEqInterface::completeCompartments()
{
  std::string DefaultCompartment;

  if (mpModel->getCompartments().size() == 0)
    DefaultCompartment = "compartment";
  else
    DefaultCompartment = mpModel->getCompartments()[0].getObjectName();

  // We try to find a reaction compartment. Note, it is not possible to use
  // getCompartment as writeToChemEq may fail;
  std::string ReactionCompartment = "";
  bool first = true;
  bool HaveReactionCompartment = true;

  std::vector< std::string >::iterator itCompartment, endCompartment;

  itCompartment = mSubstrateCompartments.begin();
  endCompartment = mSubstrateCompartments.end();

  for (; itCompartment != endCompartment && HaveReactionCompartment; ++itCompartment)
    {
      if (*itCompartment == "") continue;

      if (first)
        {
          ReactionCompartment = *itCompartment;
          first = false;
        }
      else if (ReactionCompartment != *itCompartment)
        HaveReactionCompartment = false;
    }

  itCompartment = mProductCompartments.begin();
  endCompartment = mProductCompartments.end();

  for (; itCompartment != endCompartment && HaveReactionCompartment; ++itCompartment)
    {
      if (*itCompartment == "") continue;

      if (first)
        {
          ReactionCompartment = *itCompartment;
          first = false;
        }
      else if (ReactionCompartment != *itCompartment)
        HaveReactionCompartment = false;
    }

  itCompartment = mModifierCompartments.begin();
  endCompartment = mModifierCompartments.end();

  for (; itCompartment != endCompartment && HaveReactionCompartment; ++itCompartment)
    {
      if (*itCompartment == "") continue;

      if (first)
        {
          ReactionCompartment = *itCompartment;
          first = false;
        }
      else if (ReactionCompartment != *itCompartment)
        HaveReactionCompartment = false;
    }

  if (first)
    ReactionCompartment = DefaultCompartment;

  CMetab * pMetab;

  std::vector< std::string >::iterator itMetab;

  itMetab = mSubstrateNames.begin();
  itCompartment = mSubstrateCompartments.begin();
  endCompartment = mSubstrateCompartments.end();

  for (; itCompartment != endCompartment; ++itCompartment, ++itMetab)
    if (*itCompartment == "")
      {
        pMetab = CMetabNameInterface::getMetabolite(mpModel, *itMetab, "");

        if (pMetab == NULL)
          *itCompartment = ReactionCompartment;
        else if (CMetabNameInterface::isUnique(mpModel, *itMetab))
          *itCompartment = pMetab->getCompartment()->getObjectName();
        else // Multiple metabolites with the given name exist.
          {
            // 1. Metabolite in the reaction compartment
            pMetab = CMetabNameInterface::getMetabolite(mpModel, *itMetab, ReactionCompartment);

            // 2. Metabolite in the default compartment if different from reaction compartment
            if (pMetab == NULL && ReactionCompartment != DefaultCompartment)
              pMetab = CMetabNameInterface::getMetabolite(mpModel, *itMetab, DefaultCompartment);

            // 3. The first metabolite found
            if (pMetab == NULL)
              pMetab = CMetabNameInterface::getMetabolite(mpModel, *itMetab, "");

            *itCompartment = pMetab->getCompartment()->getObjectName();
          }
      }

  itMetab = mProductNames.begin();
  itCompartment = mProductCompartments.begin();
  endCompartment = mProductCompartments.end();

  for (; itCompartment != endCompartment; ++itCompartment, ++itMetab)
    if (*itCompartment == "")
      {
        pMetab = CMetabNameInterface::getMetabolite(mpModel, *itMetab, "");

        if (pMetab == NULL)
          *itCompartment = ReactionCompartment;
        else if (CMetabNameInterface::isUnique(mpModel, *itMetab))
          *itCompartment = pMetab->getCompartment()->getObjectName();
        else // Multiple metabolites with the given name exist.
          {
            // 1. Metabolite in the reaction compartment
            pMetab = CMetabNameInterface::getMetabolite(mpModel, *itMetab, ReactionCompartment);

            // 2. Metabolite in the default compartment if different from reaction compartment
            if (pMetab == NULL && ReactionCompartment != DefaultCompartment)
              pMetab = CMetabNameInterface::getMetabolite(mpModel, *itMetab, DefaultCompartment);

            // 3. The first metabolite found
            if (pMetab == NULL)
              pMetab = CMetabNameInterface::getMetabolite(mpModel, *itMetab, "");

            *itCompartment = pMetab->getCompartment()->getObjectName();
          }
      }

  itMetab = mModifierNames.begin();
  itCompartment = mModifierCompartments.begin();
  endCompartment = mModifierCompartments.end();

  for (; itCompartment != endCompartment; ++itCompartment, ++itMetab)
    if (*itCompartment == "")
      {
        pMetab = CMetabNameInterface::getMetabolite(mpModel, *itMetab, "");

        if (pMetab == NULL)
          *itCompartment = ReactionCompartment;
        else if (CMetabNameInterface::isUnique(mpModel, *itMetab))
          *itCompartment = pMetab->getCompartment()->getObjectName();
        else // Multiple metabolites with the given name exist.
          {
            // 1. Metabolite in the reaction compartment
            pMetab = CMetabNameInterface::getMetabolite(mpModel, *itMetab, ReactionCompartment);

            // 2. Metabolite in the default compartment if different from reaction compartment
            if (pMetab == NULL && ReactionCompartment != DefaultCompartment)
              pMetab = CMetabNameInterface::getMetabolite(mpModel, *itMetab, DefaultCompartment);

            // 3. The first metabolite found
            if (pMetab == NULL)
              pMetab = CMetabNameInterface::getMetabolite(mpModel, *itMetab, "");

            *itCompartment = pMetab->getCompartment()->getObjectName();
          }
      }
}

void CChemEqInterface::buildDisplayNames()
{
  std::vector< std::string >::const_iterator itName, itCompartment;
  std::vector< std::string >::iterator it, end;

  // We need to build the list of display names for the substrates;
  mSubstrateDisplayNames.resize(mSubstrateNames.size());

  for (itName = mSubstrateNames.begin(),
       itCompartment = mSubstrateCompartments.begin(),
       it = mSubstrateDisplayNames.begin(),
       end = mSubstrateDisplayNames.end();
       it != end;
       ++itName, ++itCompartment, ++it)
    *it = CMetabNameInterface::getDisplayName(mpModel, *itName, *itCompartment, true);

  // We need to build the list of display names for the products;
  mProductDisplayNames.resize(mProductNames.size());

  for (itName = mProductNames.begin(),
       itCompartment = mProductCompartments.begin(),
       it = mProductDisplayNames.begin(),
       end = mProductDisplayNames.end();
       it != end;
       ++itName, ++itCompartment, ++it)
    *it = CMetabNameInterface::getDisplayName(mpModel, *itName, *itCompartment, true);

  // We need to build the list of display names for the modifiers;
  mModifierDisplayNames.resize(mModifierNames.size());

  for (itName = mModifierNames.begin(),
       itCompartment = mModifierCompartments.begin(),
       it = mModifierDisplayNames.begin(),
       end = mModifierDisplayNames.end();
       it != end;
       ++itName, ++itCompartment, ++it)
    *it = CMetabNameInterface::getDisplayName(mpModel, *itName, *itCompartment, true);

  return;
}

bool CChemEqInterface::writeToChemEq(CChemEq * pChemEq) const
{
  CChemEq * pCE = (pChemEq != NULL) ? pChemEq : const_cast< CChemEq * >(mpChemEq);

  if (pCE == NULL) return false;

  if (mpModel == NULL)
    {
      mpModel = dynamic_cast< CModel * >(pCE->getObjectAncestor("Model"));

      if (mpModel == NULL) return false;
    }

  bool ret = true;
  std::string metabkey;
  size_t i, imax;

  pCE->cleanup();

  imax = mSubstrateNames.size();

  for (i = 0; i < imax; ++i)
    {
      metabkey = CMetabNameInterface::getMetaboliteKey(mpModel, mSubstrateNames[i], mSubstrateCompartments[i]);

      if (metabkey.empty())
        ret = false;
      else
        pCE->addMetabolite(metabkey, mSubstrateMult[i], CChemEq::SUBSTRATE);
    }

  imax = mProductNames.size();

  for (i = 0; i < imax; ++i)
    {
      metabkey = CMetabNameInterface::getMetaboliteKey(mpModel, mProductNames[i], mProductCompartments[i]);

      if (metabkey.empty())
        ret = false;
      else
        pCE->addMetabolite(metabkey, mProductMult[i], CChemEq::PRODUCT);
    }

  imax = mModifierNames.size();

  for (i = 0; i < imax; ++i)
    {
      metabkey = CMetabNameInterface::getMetaboliteKey(mpModel, mModifierNames[i], mModifierCompartments[i]);

      if (metabkey.empty())
        ret = false;
      else
        pCE->addMetabolite(metabkey, mModifierMult[i], CChemEq::MODIFIER);
    }

  pCE->setReversibility(mReversibility);

  return ret; //TODO: really check
}

std::string CChemEqInterface::toDataValue() const
{
  std::ostringstream DataValue;
  DataValue.imbue(std::locale::classic());
  DataValue.precision(6);

  std::string Separator;
  std::vector< std::string >::const_iterator itSpecies;
  std::vector< std::string >::const_iterator endSpecies;
  std::vector< std::string >::const_iterator itCompartment;
  std::vector< C_FLOAT64 >::const_iterator itMultiplier;

  if (!mSubstrateNames.empty() ||
      !mProductNames.empty())
    {
      Separator.clear();
      itSpecies = mSubstrateNames.begin();
      endSpecies = mSubstrateNames.end();
      itCompartment = mSubstrateCompartments.begin();
      itMultiplier = mSubstrateMult.begin();

      for (; itSpecies != endSpecies; ++itSpecies, ++itCompartment, ++itMultiplier)
        {
          DataValue << Separator << *itMultiplier << " * " << CMetabNameInterface::createUniqueDisplayName(*itSpecies, *itCompartment, true);
          Separator = " + ";
        }

      DataValue << (mReversibility ?  " = " : " -> ");

      Separator.clear();
      itSpecies = mProductNames.begin();
      endSpecies = mProductNames.end();
      itCompartment = mProductCompartments.begin();
      itMultiplier = mProductMult.begin();

      for (; itSpecies != endSpecies; ++itSpecies, ++itCompartment, ++itMultiplier)
        {
          DataValue << Separator << *itMultiplier << " * " << CMetabNameInterface::createUniqueDisplayName(*itSpecies, *itCompartment, true);
          Separator = " + ";
        }
    }

  if (!mModifierNames.empty())
    {
      Separator = "; ";
      itSpecies = mModifierNames.begin();
      endSpecies = mModifierNames.end();
      itCompartment = mModifierCompartments.begin();

      for (; itSpecies != endSpecies; ++itSpecies, ++itCompartment)
        {
          DataValue << Separator << CMetabNameInterface::createUniqueDisplayName(*itSpecies, *itCompartment, true);
          Separator = " ";
        }
    }

  return DataValue.str();
}

bool CChemEqInterface::fromDataValue(const std::string & dataValue)
{
  return setChemEqString(dataValue);
}

const std::vector<C_FLOAT64> & CChemEqInterface::getListOfMultiplicities(CFunctionParameter::Role role) const
{
  if (role == CFunctionParameter::Role::SUBSTRATE) return mSubstrateMult;
  else if (role == CFunctionParameter::Role::PRODUCT) return mProductMult;
  else if (role == CFunctionParameter::Role::MODIFIER) return mModifierMult;
  else fatalError();

  return mSubstrateMult; //never reached
}

const std::vector<std::string> & CChemEqInterface::getListOfSpecies(CFunctionParameter::Role role) const
{
  if (role == CFunctionParameter::Role::SUBSTRATE) return mSubstrateNames;
  else if (role == CFunctionParameter::Role::PRODUCT) return mProductNames;
  else if (role == CFunctionParameter::Role::MODIFIER) return mModifierNames;
  else fatalError();

  return mSubstrateNames; //never reached
}

const std::vector<std::string> & CChemEqInterface::getListOfCompartments(CFunctionParameter::Role role) const
{
  if (role == CFunctionParameter::Role::SUBSTRATE) return mSubstrateCompartments;
  else if (role == CFunctionParameter::Role::PRODUCT) return mProductCompartments;
  else if (role == CFunctionParameter::Role::MODIFIER) return mModifierCompartments;
  else fatalError();

  return mSubstrateCompartments; //never reached
}

const std::vector<std::string> & CChemEqInterface::getListOfDisplayNames(CFunctionParameter::Role role) const
{
  if (role == CFunctionParameter::Role::SUBSTRATE) return mSubstrateDisplayNames;
  else if (role == CFunctionParameter::Role::PRODUCT) return mProductDisplayNames;
  else if (role == CFunctionParameter::Role::MODIFIER) return mModifierDisplayNames;
  else fatalError();

  return mSubstrateDisplayNames; //never reached
}

std::pair< std::string, std::string > CChemEqInterface::displayNameToNamePair(CFunctionParameter::Role role, const std::string displayName) const
{
  const std::vector< std::string > & DisplayNames = getListOfDisplayNames(role);
  std::vector<std::string>::const_iterator it = DisplayNames.begin();
  std::vector<std::string>::const_iterator end = DisplayNames.end();
  size_t Index = 0;

  for (; it != end; ++it, ++Index)
    if (*it == displayName || *it == CMetabNameInterface::unQuote(displayName))
      {
        return std::make_pair(getListOfSpecies(role)[Index], getListOfCompartments(role)[Index]);
      }

  return std::make_pair("unknown", "");
}

void CChemEqInterface::addModifier(const std::string & name)
{
  std::pair< std::string, std::string > Modifier = CMetabNameInterface::splitDisplayName(name);
  std::string quotedName = quote(name);

  if (Modifier.second.empty())
    {
      const CMetab* metab = CMetabNameInterface::getMetabolite(mpModel, Modifier.first, Modifier.second);

      if (metab != NULL && metab->getCompartment() != NULL)
        {
          Modifier.second = metab->getCompartment()->getObjectName();
          quotedName = CMetabNameInterface::getDisplayName(mpModel, Modifier.first, Modifier.second, true);
        }
    }


  //is the name already in the list
  std::vector< std::string >::const_iterator it, itEnd = mModifierNames.end();
  std::vector< std::string >::const_iterator itComp = mModifierCompartments.begin();

  for (it = mModifierNames.begin(); it != itEnd; ++it, ++itComp)
    if (Modifier.first == *it &&
        Modifier.second == *itComp) break;

  if (it == itEnd)
    {
      mModifierNames.push_back(Modifier.first);
      mModifierMult.push_back(1.0);
      mModifierCompartments.push_back(Modifier.second);
      mModifierDisplayNames.push_back(quotedName);
    }
}

void
CChemEqInterface::clearModifiers()
{
  mModifierNames.clear();
  mModifierMult.clear();
  mModifierCompartments.clear();
  mModifierDisplayNames.clear();
}

void
CChemEqInterface::clearAll()
{
  mSubstrateNames.clear();
  mProductNames.clear();
  mModifierNames.clear();

  mSubstrateMult.clear();
  mProductMult.clear();
  mModifierMult.clear();

  mSubstrateCompartments.clear();
  mProductCompartments.clear();
  mModifierCompartments.clear();

  mSubstrateDisplayNames.clear();
  mProductDisplayNames.clear();
  mModifierDisplayNames.clear();
}

bool
CChemEqInterface::getReversibility() const
{
  return mReversibility;
}

void CChemEqInterface::setReversibility(bool rev)
{
  mReversibility = rev;
}

std::string CChemEqInterface::writeElement(const std::string & name, C_FLOAT64 mult, bool expanded)
{
  std::ostringstream Element;
  Element.imbue(std::locale::classic());
  Element.precision(6);

  std::string Metabolite = name;

  // The last character must not be a ';' in a reaction.
  if (Metabolite[Metabolite.length() - 1] == ';')
    Metabolite = "\"" + Metabolite + "\"";

  if (isNumber(Metabolite))
    Metabolite = "\"" + Metabolite + "\"";

  if (expanded)
    {
      C_INT32 i, imax = (C_INT32) mult;

      for (i = 0; i < imax; ++i)
        {
          if (i) Element << " + ";

          Element << Metabolite;
        }
    }
  else
    {
      if (mult == 1.0)
        {
          Element << Metabolite;
        }
      else
        {
          Element << mult << " * " << Metabolite;
        }
    }

  return Element.str();
}

size_t CChemEqInterface::getMolecularity(CFunctionParameter::Role role) const
{
  const std::vector<C_FLOAT64> * tmpVector = NULL;

  if (role == CFunctionParameter::Role::SUBSTRATE)
    tmpVector = &mSubstrateMult;
  else if (role == CFunctionParameter::Role::PRODUCT)
    tmpVector = &mProductMult;
  else if (role == CFunctionParameter::Role::MODIFIER)
    tmpVector = &mModifierMult;
  else fatalError();

  size_t ccc, i, imax = tmpVector->size();
  ccc = 0;

  for (i = 0; i < imax; ++i)
    {
      if ((*tmpVector)[i] != floor((*tmpVector)[i] + 0.5))
        return C_INVALID_INDEX;

      ccc += (size_t) floor((*tmpVector)[i]);
    }

  return ccc;
}

void CChemEqInterface::reverse()
{
  std::vector<std::string> dummyNames;
  std::vector<C_FLOAT64> dummyMults;
  std::vector<std::string> dummyCompartments;

  dummyNames = mSubstrateNames;
  dummyMults = mSubstrateMult;
  dummyCompartments = mSubstrateCompartments;

  mSubstrateNames = mProductNames;
  mSubstrateMult = mProductMult;
  mSubstrateCompartments = mProductCompartments;

  mProductNames = dummyNames;
  mProductMult = dummyMults;
  mProductCompartments = dummyCompartments;
}

std::set<std::string> CChemEqInterface::listOfNonUniqueMetabNames() const
{
  std::set<std::string> ret;

  std::vector<std::string>::const_iterator it, itEnd;

  itEnd = mSubstrateNames.end();

  for (it = mSubstrateNames.begin(); it != itEnd; ++it)
    if (!CMetabNameInterface::isUnique(mpModel, *it))
      ret.insert(*it);

  itEnd = mProductNames.end();

  for (it = mProductNames.begin(); it != itEnd; ++it)
    if (!CMetabNameInterface::isUnique(mpModel, *it))
      ret.insert(*it);

  itEnd = mModifierNames.end();

  for (it = mModifierNames.begin(); it != itEnd; ++it)
    if (!CMetabNameInterface::isUnique(mpModel, *it))
      ret.insert(*it);

  return ret;
}

std::set< std::pair< std::string, std::string > > CChemEqInterface::listOfNonExistingMetabNames() const
{
  std::set< std::pair< std::string, std::string > > ret;
  std::pair< std::string, std::string > Insert;

  std::vector<std::string>::const_iterator it, itComp, itEnd;

  itEnd = mSubstrateNames.end();

  for (it = mSubstrateNames.begin(), itComp = mSubstrateCompartments.begin(); it != itEnd; ++it, ++itComp)
    if (!CMetabNameInterface::doesExist(mpModel, *it, *itComp))
      {
        Insert.first = *it;
        Insert.second = *itComp;
        ret.insert(Insert);
      }

  itEnd = mProductNames.end();

  for (it = mProductNames.begin(), itComp = mProductCompartments.begin(); it != itEnd; ++it, ++itComp)
    if (!CMetabNameInterface::doesExist(mpModel, *it, *itComp))
      {
        Insert.first = *it;
        Insert.second = *itComp;
        ret.insert(Insert);
      }

  itEnd = mModifierNames.end();

  for (it = mModifierNames.begin(), itComp = mModifierCompartments.begin(); it != itEnd; ++it, ++itComp)
    if (!CMetabNameInterface::doesExist(mpModel, *it, *itComp))
      {
        Insert.first = *it;
        Insert.second = *itComp;
        ret.insert(Insert);
      }

  return ret;
}

bool CChemEqInterface::createNonExistingMetabs(
  std::vector<std::string> &createdKeys)
{
  std::set< std::pair< std::string, std::string > > metabs
    = listOfNonExistingMetabNames();
  bool ret;

  if (metabs.size() == 0) ret = false; else ret = true;

  std::set< std::pair< std::string, std::string > >::const_iterator it, itEnd;

  itEnd = metabs.end();

  for (it = metabs.begin(); it != itEnd; ++it)
    {
      if (mpModel->getCompartments().getIndex(it->second) == C_INVALID_INDEX)
        {
          CCompartment* comp = mpModel->createCompartment(it->second, 1);

          if (comp != NULL)
            {
              createdKeys.insert(createdKeys.begin(), comp->getKey());
            }
        }

      CMetab* metab = mpModel->createMetabolite(it->first,
                      it->second,
                      1.0, CModelEntity::Status::REACTIONS);

      if (metab != NULL)
        {
          createdKeys.insert(createdKeys.begin(), metab->getKey());
        }
    }

  // Due to the creation of metabolites the display names may have changed.
  buildDisplayNames();

  return ret;
}

bool CChemEqInterface::isMulticompartment() const
{
  bool Initialize = true;
  std::string Compartment = "";

  std::vector< std::string >::const_iterator it;
  std::vector< std::string >::const_iterator end;

  for (it = mSubstrateCompartments.begin(), end = mSubstrateCompartments.end();
       it != end; ++it)
    if (Initialize)
      {
        Compartment = *it;
        Initialize = false;
      }
    else if (Compartment != *it)
      return true;

  for (it = mProductCompartments.begin(), end = mProductCompartments.end();
       it != end; ++it)
    if (Initialize)
      {
        Compartment = *it;
        Initialize = false;
      }
    else if (Compartment != *it)
      return true;

  for (it = mModifierCompartments.begin(), end = mModifierCompartments.end();
       it != end; ++it)
    if (Initialize)
      {
        Compartment = *it;
        Initialize = false;
      }
    else if (Compartment != *it)
      return true;

  return Compartment.empty();
}

const CCompartment * CChemEqInterface::getCompartment() const
{
  CChemEq ce;
  writeToChemEq(&ce);

  if (isMulticompartment())
    return NULL;
  else
    {
      const CMetab * metab = NULL;

      if (ce.getSubstrates().size())
        metab = ce.getSubstrates()[0].getMetabolite();
      else if (ce.getProducts().size())
        metab = ce.getProducts()[0].getMetabolite();

      if (metab)
        return metab->getCompartment();
      else
        return NULL;
    }
}

std::string CChemEqInterface::getDefaultCompartment() const
{
  std::map< std::string, size_t > CompartmentCount;
  std::pair< std::map< std::string, size_t >::iterator, bool > Inserted;

  std::vector< std::string >::const_iterator it;
  std::vector< std::string >::const_iterator end;

  for (it = mSubstrateCompartments.begin(), end = mSubstrateCompartments.end(); it != end; ++it)
    {
      Inserted = CompartmentCount.insert(std::make_pair(*it, 0));

      if (!Inserted.second)
        {
          Inserted.first->second++;
        }
    }

  for (it = mProductCompartments.begin(), end = mProductCompartments.end(); it != end; ++it)
    {
      Inserted = CompartmentCount.insert(std::make_pair(*it, 0));

      if (!Inserted.second)
        {
          Inserted.first->second++;
        }
    }

  for (it = mModifierCompartments.begin(), end = mModifierCompartments.end(); it != end; ++it)
    {
      Inserted = CompartmentCount.insert(std::make_pair(*it, 0));

      if (!Inserted.second)
        {
          Inserted.first->second++;
        }
    }

  std::map< std::string, size_t >::const_iterator itMap = CompartmentCount.begin();
  std::map< std::string, size_t >::const_iterator endMap = CompartmentCount.end();

  if (itMap == endMap) return "";

  std::map< std::string, size_t >::const_iterator itCompartment = itMap++;

  for (; itMap != endMap; ++itMap)
    {
      if (itMap->second > itCompartment->second)
        {
          itCompartment = itMap;
        }
    }

  return itCompartment->first;
}

std::set< std::string > CChemEqInterface::getCompartments() const
{
  std::set< std::string > Compartments;

  std::vector< std::string >::const_iterator it;
  std::vector< std::string >::const_iterator end;

  for (it = mSubstrateCompartments.begin(), end = mSubstrateCompartments.end(); it != end; ++it)
    Compartments.insert(*it);

  for (it = mProductCompartments.begin(), end = mProductCompartments.end(); it != end; ++it)
    Compartments.insert(*it);

  for (it = mModifierCompartments.begin(), end = mModifierCompartments.end(); it != end; ++it)
    Compartments.insert(*it);

  return Compartments;
}

/*static*/
std::string CChemEqInterface::getChemEqString(const CReaction & rea, bool expanded)
{
  CChemEqInterface cei;

  cei.init(rea.getChemEq());
  return cei.getChemEqString(expanded);
}

/*static*/
bool CChemEqInterface::setChemEqFromString(CReaction & rea, const std::string & ces)
{
  CChemEqInterface cei;

  cei.init(rea.getChemEq());

  if (cei.setChemEqString(ces))
    {
      cei.writeToChemEq();
      return true;
    };

  return false;
}

/*static*/
bool CChemEqInterface::isValidEq(const std::string & eq)
{
  if (eq.empty()) return false;

  // parse the description into a linked node tree
  std::istringstream buffer(eq);
  CChemEqParser Parser(&buffer);

  return (Parser.yyparse() == 0);
}
