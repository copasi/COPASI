/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEqInterface.cpp,v $
   $Revision: 1.18 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/22 17:34:27 $
   End CVS Header */

#include "mathematics.h"

#include "copasi.h"
#include "CChemEqInterface.h"
#include "CMetabNameInterface.h"
#include "CChemEq.h"
#include "CReaction.h"
#include "utilities/CCopasiVector.h"
#include "utilities/utility.h"
#include "utilities/CGlobals.h"
#include "model/CModel.h"

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

        for (j = 0; j < mModifierNames.size(); j++)
          {
            ChemicalEquation += " ";
            ChemicalEquation += mModifierNames[j];
          }
      }

    return ChemicalEquation;
  }

void CChemEqInterface::setChemEqString(const std::string & ces)
{
  std::string Substrates, Products, Modifiers;

  //cleanup();
  if (!checkFirstLevel(ces)) return;
  mReversibility = splitChemEq(ces, Substrates, Products, Modifiers);

  setElements(mSubstrateNames, mSubstrateMult, Substrates);

  setElements(mProductNames, mProductMult, Products);

  // True tells the method to look for " " as separator instead of " + ".
  setElements(mModifierNames, mModifierMult, Modifiers, true);

  //  return mReversibility;
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

const std::vector<std::string> & CChemEqInterface::getListOfNames(const std::string & role) const
  {
    if (role == "SUBSTRATE") return mSubstrateNames;
    else if (role == "PRODUCT") return mProductNames;
    else if (role == "MODIFIER") return mModifierNames;
    else fatalError();

    return mSubstrateNames; //never reached
  }

const std::vector<C_FLOAT64> & CChemEqInterface::getListOfMultiplicities(const std::string & role) const
  {
    if (role == "SUBSTRATE") return mSubstrateMult;
    else if (role == "PRODUCT") return mProductMult;
    else if (role == "MODIFIER") return mModifierMult;
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
  if (expanded)
    {
      std::string ces;
      C_INT32 i, imax = (C_INT32) mult;
      for (i = 0; i < imax; ++i)
        {
          if (i) ces += " + ";
          ces += name;
        }
      return ces;
    }
  else
    {
      if (mult == 1.0)
        return name;
      else
        return StringPrint("%g * %s", mult, name.c_str());
    }
}

bool CChemEqInterface::splitChemEq(const std::string & input,
                                   std::string & left, std::string & right, std::string & mod)
{
  std::string::size_type equal = std::string::npos;
  std::string rightTmp;
  bool reversibility;

  std::string Separator[] = {"->", "=", ""};
  unsigned C_INT32 i = 0;
  while (*Separator != "" && equal == std::string::npos)
    equal = input.find(Separator[i++]);

  if (equal == std::string::npos)
    fatalError();

  if (input.substr(equal, 1) == "=")
    reversibility = true;
  else
    reversibility = false;

  left = input.substr(0, equal);

  rightTmp = input.substr(equal + (Separator[--i].length()));

  equal = rightTmp.find(";");
  if (equal == std::string::npos)
  {right = rightTmp; mod = ""; return reversibility;}

  right = rightTmp.substr(0, equal);
  mod = rightTmp.substr(equal + 1);

  return reversibility;
}

bool CChemEqInterface::setElements(std::vector<std::string> & names,
                                   std::vector<C_FLOAT64> & mults,
                                   const std::string & reaction,
                                   const bool modif)
{
  names.clear();
  mults.clear();

  std::string name;
  C_FLOAT64 mult;

  std::string::size_type pos = 0;

  while (pos != std::string::npos)
    {
      if (!modif)
        {
          if (!extractElement(reaction, pos, name, mult)) return false;
        }
      else
        {
          if (!extractModifier(reaction, pos, name)) return false;
          mult = 1.0;
        }

      if (name != "")
        {
          names.push_back(name);
          mults.push_back(mult);
        }
    }
  return true; //success
}

bool CChemEqInterface::extractElement(const std::string & input,
                                      std::string::size_type & pos,
                                      std::string & name, C_FLOAT64 & mult)
{
  std::string Value;

  std::string::size_type Start = input.find_first_not_of(" ", pos);
  if (Start == std::string::npos) //empty
    {
      name = ""; pos = std::string::npos;
      return true;
    }

  std::string::size_type End = input.find(" + ", Start);
  std::string::size_type eee = input.find_last_not_of(" ", End) + 1;
  std::string part = input.substr(Start, eee - Start);

  //part now contains the term we want to analyze
  std::cout << "    part " << part << std::endl;

  std::string::size_type Multiplier = part.find("*", Start);
  std::string::size_type Multiplier2 = part.find("*", Multiplier + 1);
  if (Multiplier2 != std::string::npos)
    {
      std::cout << "found 2 \"*\" in one term\n";
      return false;
    }

  std::string::size_type NameStart;
  if (Multiplier == std::string::npos)
    {
      NameStart = 0;
      mult = 1.0;
    }
  else
    {
      NameStart = part.find_first_not_of(" ", Multiplier + 1);
      Value = part.substr(0, Multiplier);
      mult = atof(Value.c_str());
      //TODO check if Value really contains a valid number

      if (NameStart == std::string::npos)
        {
          std::cout << "no metab name after \"*\" \n";
          return false;
        }
    }

  std::string::size_type NameEnd = part.find_last_not_of(" ") + 1;
  std::string nameString = part.substr(NameStart, NameEnd - NameStart);

  //nameString now contains the metab name of the term we want to analyze
  std::cout << "    nameString " << nameString << std::endl;

  if (!CMetabNameInterface::isValidMetabName(nameString))
    {
      std::cout << "invalid  metab name  \n";
      return false;
    }
  else
    name = nameString;

  pos = (End == std::string::npos) ? End : End + 3;
  return true; //success
}

bool CChemEqInterface::extractModifier(const std::string & input,
                                       std::string::size_type & pos,
                                       std::string & name)
{
  std::string Value;

  std::string::size_type Start = input.find_first_not_of(" ", pos);
  std::string::size_type End;
  if (Start == std::string::npos)
    End = Start;
  else
    End = input.find(" ", Start);

  if (Start != std::string::npos)
    name = input.substr(Start, End - Start);
  else
    name = "";

  pos = (End == std::string::npos) ? End : End + 1;
  return true;
}

C_INT32 CChemEqInterface::getMolecularity(const std::string & role) const
  {
    const std::vector<C_FLOAT64> * tmpVector = NULL;

    if (role == "SUBSTRATE")
      tmpVector = &mSubstrateMult;
    else if (role == "PRODUCT")
      tmpVector = &mProductMult;
    else if (role == "MODIFIER")
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
                                0.1, CMetab::METAB_VARIABLE);
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

//static
bool CChemEqInterface::isValidEqPart(const std::string & s)
{
  return true;
}

/*static*/
bool CChemEqInterface::isValidEq(const std::string & eq)
{
  // a valid equation should be in the format of (metab + (metab)*) (= | ->) (metab (+ metab)*) (; (modifieer)*)
  // metab here can include moiety

  if (!checkFirstLevel(eq)) return false;

  // it should be save now to split the string
  std::string substrates, products, modifiers;
  bool reversibility = splitChemEq(eq, substrates, products, modifiers);

  if (!isValidEqPart(substrates))
    {
      //debugging
      std::cout << "substrates part not valid\n";
      return false;
    }

  if (!isValidEqPart(products))
    {
      //debugging
      std::cout << "products part not valid\n";
      return false;
    }

  // next check if each metabolite name is valid

  return true;
}

//static
bool CChemEqInterface::checkFirstLevel(const std::string & eq)
{
  std::string::size_type startMetab = eq.find_first_not_of(" ");  // the starting position of the first metabolite, also the equation
  if (startMetab == std::string::npos)  // empty equation string
    {
      //debugging
      std::cout << "Empty equation string\n";
      return false;
    }

  std::string::size_type sep1 = eq.find("->");
  std::string::size_type sep2 = eq.find("=");

  if ((sep1 == std::string::npos) && (sep2 == std::string::npos))
    {
      std::cout << "no separator found\n";
      return false;
    }

  if ((sep1 != std::string::npos) && (sep2 != std::string::npos))
    {
      std::cout << "both -> and = found \n";
      return false;
    }

  if (sep2 != std::string::npos)
    sep1 = sep2; //now sep1 holds the position of the separator

  std::string::size_type sep3 = eq.find("->", sep1 + 1);
  if (sep3 != std::string::npos)
    {
      std::cout << "extra -> found " << sep1 << " " << sep3 << std::endl;
      return false;
    }

  sep3 = eq.find("=", sep1 + 1);
  if (sep3 != std::string::npos)
    {
      std::cout << "extra = found " << sep1 << " " << sep3 << std::endl;
      return false;
    }

  //now look for ";"

  sep2 = eq.find(";");
  sep3 = eq.rfind(";");

  if (sep2 != sep3)
    {
      std::cout << "found more than one \";\"\n";
      return false;
    }

  if (sep2 <= sep1)
    {
      std::cout << "found \";\" on the LHS of the equation\n";
      return false;
    }

  return true;
}
