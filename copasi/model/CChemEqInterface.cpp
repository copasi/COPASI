/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEqInterface.cpp,v $
   $Revision: 1.26.2.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/04 15:20:44 $
   End CVS Header */

#include "mathematics.h"

#include "copasi.h"
#include "CChemEqInterface.h"
#include "CMetabNameInterface.h"
#include "CChemEq.h"
#include "CChemEqParser.h"
#include "CReaction.h"
#include "CModel.h"

#include "utilities/CCopasiVector.h"
#include "utilities/utility.h"

CChemEqInterface::CChemEqInterface()
{}

CChemEqInterface::~CChemEqInterface()
{}

std::string CChemEqInterface::getChemEqString(bool expanded) const
  {
    std::string ChemicalEquation;
    unsigned C_INT32 j;

    if ((mSubstrateNames.size() == 0) && (mProductNames.size() == 0) && (mModifierNames.size() == 0))
      return "";

    for (j = 0; j < mSubstrateNames.size(); j++)
      {
        if (j)
          ChemicalEquation += " + ";

        ChemicalEquation += writeElement(mSubstrateNames[j], mSubstrateMult[j], expanded);
      }

    if (mReversibility)
      ChemicalEquation += " = ";
    else
      ChemicalEquation += " -> ";

    for (j = 0; j < mProductNames.size(); j++)
      {
        if (j)
          ChemicalEquation += " + ";

        ChemicalEquation += writeElement(mProductNames[j], mProductMult[j], expanded);
      }

    if (mModifierNames.size())
      {
        ChemicalEquation += ";";

        std::string Name;
        for (j = 0; j < mModifierNames.size(); j++)
          {
            ChemicalEquation += " ";

            Name = quote(mModifierNames[j]);
            if (isNumber(Name) ||
                Name[Name.length() - 1] == ';')
              Name = "\"" + Name + "\"";

            ChemicalEquation += Name;
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

      mProductNames = Parser.getProductNames();
      mProductMult = Parser.getProductMulitplicities();

      mModifierNames = Parser.getModifierNames();
      mModifierMult = Parser.getModifierMulitplicities();
    }

  return success;
}

bool CChemEqInterface::loadFromChemEq(const CModel * model, const CChemEq & ce)
{
  bool ret = true;
  const CCopasiVector<CChemEqElement> * elements;
  C_INT32 i, imax;

  elements = &ce.getSubstrates();
  imax = elements->size();
  mSubstrateNames.resize(imax);
  mSubstrateMult.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      mSubstrateNames[i] = CMetabNameInterface::getDisplayName(model, (*elements)[i]->getMetaboliteKey());
      mSubstrateMult[i] = (*elements)[i]->getMultiplicity();
    }

  elements = &ce.getProducts();
  imax = elements->size();
  mProductNames.resize(imax);
  mProductMult.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      mProductNames[i] = CMetabNameInterface::getDisplayName(model, (*elements)[i]->getMetaboliteKey());
      mProductMult[i] = (*elements)[i]->getMultiplicity();
    }

  elements = &ce.getModifiers();
  imax = elements->size();
  mModifierNames.resize(imax);
  mModifierMult.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      mModifierNames[i] = CMetabNameInterface::getDisplayName(model, (*elements)[i]->getMetaboliteKey());
      mModifierMult[i] = (*elements)[i]->getMultiplicity();
    }

  mReversibility = ce.getReversibility();

  return ret;
}

bool CChemEqInterface::writeToChemEq(const CModel * model, CChemEq & ce) const
  {
    bool ret = true;
    C_INT32 i, imax;

    ce.cleanup();

    imax = mSubstrateNames.size();
    for (i = 0; i < imax; ++i)
      ce.addMetabolite(CMetabNameInterface::getMetaboliteKey(model, mSubstrateNames[i]), mSubstrateMult[i], CChemEq::SUBSTRATE);

    imax = mProductNames.size();
    for (i = 0; i < imax; ++i)
      ce.addMetabolite(CMetabNameInterface::getMetaboliteKey(model, mProductNames[i]), mProductMult[i], CChemEq::PRODUCT);

    imax = mModifierNames.size();
    for (i = 0; i < imax; ++i)
      ce.addMetabolite(CMetabNameInterface::getMetaboliteKey(model, mModifierNames[i]), mModifierMult[i], CChemEq::MODIFIER);

    ce.setReversibility(mReversibility);

    return ret; //TODO: really check
  }

const std::vector<std::string> & CChemEqInterface::getListOfNames(CFunctionParameter::Role role) const
  {
    if (role == CFunctionParameter::SUBSTRATE) return mSubstrateNames;
    else if (role == CFunctionParameter::PRODUCT) return mProductNames;
    else if (role == CFunctionParameter::MODIFIER) return mModifierNames;
    else fatalError();

    return mSubstrateNames; //never reached
  }

const std::vector<C_FLOAT64> & CChemEqInterface::getListOfMultiplicities(CFunctionParameter::Role role) const
  {
    if (role == CFunctionParameter::SUBSTRATE) return mSubstrateMult;
    else if (role == CFunctionParameter::PRODUCT) return mProductMult;
    else if (role == CFunctionParameter::MODIFIER) return mModifierMult;
    else fatalError();

    return mSubstrateMult; //never reached
  }

void CChemEqInterface::addModifier(const std::string & name)
{
  mModifierNames.push_back(name);
  mModifierMult.push_back(1.0);
}

void CChemEqInterface::clearModifiers()
{
  mModifierNames.clear();
  mModifierMult.clear();
}

std::string CChemEqInterface::writeElement(const std::string & name, C_FLOAT64 mult, bool expanded)
{
  std::string Name = quote(name);
  if (isNumber(Name) ||
      Name[Name.length() - 1] == ';')
    Name = "\"" + Name + "\"";

  if (expanded)
    {
      std::string ces;
      C_INT32 i, imax = (C_INT32) mult;
      for (i = 0; i < imax; ++i)
        {
          if (i) ces += " + ";
          ces += Name;
        }
      return ces;
    }
  else
    {
      if (mult == 1.0)
        return Name;
      else
        return StringPrint("%g * %s", mult, Name.c_str());
    }
}

C_INT32 CChemEqInterface::getMolecularity(CFunctionParameter::Role role) const
  {
    const std::vector<C_FLOAT64> * tmpVector = NULL;

    if (role == CFunctionParameter::SUBSTRATE)
      tmpVector = &mSubstrateMult;
    else if (role == CFunctionParameter::PRODUCT)
      tmpVector = &mProductMult;
    else if (role == CFunctionParameter::MODIFIER)
      tmpVector = &mModifierMult;
    else fatalError();

    C_INT32 ccc, i, imax = tmpVector->size();
    ccc = 0;
    for (i = 0; i < imax; ++i)
      ccc += (C_INT32)floor((*tmpVector)[i]);

    return ccc;
  }

void CChemEqInterface::reverse()
{
  std::vector<std::string> dummyNames;
  std::vector<C_FLOAT64> dummyMults;

  dummyNames = mSubstrateNames; dummyMults = mSubstrateMult;
  mSubstrateNames = mProductNames; mSubstrateMult = mProductMult;
  mProductNames = dummyNames; mProductMult = dummyMults;
}

std::set<std::string> CChemEqInterface::listOfNonUniqueMetabNames(const CModel * model) const
  {
    std::set<std::string> ret;

    std::vector<std::string>::const_iterator it, itEnd;

    itEnd = mSubstrateNames.end();
    for (it = mSubstrateNames.begin(); it != itEnd; ++it)
      if (!CMetabNameInterface::isUnique(model, *it))
        ret.insert(*it);

    itEnd = mProductNames.end();
    for (it = mProductNames.begin(); it != itEnd; ++it)
      if (!CMetabNameInterface::isUnique(model, *it))
        ret.insert(*it);

    itEnd = mModifierNames.end();
    for (it = mModifierNames.begin(); it != itEnd; ++it)
      if (!CMetabNameInterface::isUnique(model, *it))
        ret.insert(*it);

    return ret;
  }

std::set<std::string> CChemEqInterface::listOfNonExistingMetabNames(const CModel * model) const
  {
    std::set<std::string> ret;

    std::vector<std::string>::const_iterator it, itEnd;

    itEnd = mSubstrateNames.end();
    for (it = mSubstrateNames.begin(); it != itEnd; ++it)
      if (!CMetabNameInterface::doesExist(model, *it))
        ret.insert(*it);

    itEnd = mProductNames.end();
    for (it = mProductNames.begin(); it != itEnd; ++it)
      if (!CMetabNameInterface::doesExist(model, *it))
        ret.insert(*it);

    itEnd = mModifierNames.end();
    for (it = mModifierNames.begin(); it != itEnd; ++it)
      if (!CMetabNameInterface::doesExist(model, *it))
        ret.insert(*it);

    return ret;
  }

bool CChemEqInterface::createNonExistingMetabs(CModel * model) const
  {
    std::set<std::string> metabs = listOfNonExistingMetabNames(model);
    bool ret;
    if (metabs.size() == 0) ret = false; else ret = true;

    std::set<std::string>::const_iterator it, itEnd;

    itEnd = metabs.end();

    std::string compName;
    for (it = metabs.begin(); it != itEnd; ++it)
      {
        compName = CMetabNameInterface::extractCompartmentName(model, *it);
        if (model->getCompartments().getIndex(compName) == C_INVALID_INDEX)
          model->createCompartment(compName, 1);
        model->createMetabolite(CMetabNameInterface::extractMetabName(model, *it),
                                compName,
                                0.1, CModelEntity::REACTIONS);
      }

    return ret;
  }

/*static*/
std::string CChemEqInterface::getChemEqString(const CModel * model, const CReaction & rea, bool expanded)
{
  CChemEqInterface cei;
  cei.loadFromChemEq(model, rea.getChemEq());
  return cei.getChemEqString(expanded);
}

/*static*/
void CChemEqInterface::setChemEqFromString(const CModel * model, CReaction & rea, const std::string & ces)
{
  CChemEqInterface cei;
  cei.setChemEqString(ces);
  cei.writeToChemEq(model, rea.getChemEq());
}

/*static*/
bool CChemEqInterface::isValidEq(const std::string & eq)
{
  // parse the description into a linked node tree
  std::istringstream buffer(eq);
  CChemEqParser Parser(&buffer);

  return (Parser.yyparse() == 0);
}
