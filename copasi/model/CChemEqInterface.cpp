#include <math.h>
#include "CChemEqInterface.h"
#include "CMetabNameInterface.h"
#include "CChemEq.h"
#include "CReaction.h"
#include "utilities/CCopasiVector.h"
#include "utilities/utility.h"
#include "utilities/CGlobals.h"

CChemEqInterface::CChemEqInterface()
{}

CChemEqInterface::~CChemEqInterface()
{}

std::string CChemEqInterface::getChemEqString(bool expanded) const
  {
    std::string ChemicalEquation;
    unsigned C_INT32 j;

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

bool CChemEqInterface::setChemEqString(const std::string & ces)
{
  std::string Substrates, Products, Modifiers;

  //cleanup();
  mReversibility = splitChemEq(ces, Substrates, Products, Modifiers);

  setElements(mSubstrateNames, mSubstrateMult, Substrates);

  setElements(mProductNames, mProductMult, Products);

  // True tells the method to look for " " as separator instead of " + ".
  setElements(mModifierNames, mModifierMult, Modifiers, true);

  return mReversibility;
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
    bool ret;
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

    return ret;
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

void CChemEqInterface::setElements(std::vector<std::string> & names,
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
        extractElement(reaction, pos, name, mult);
      else
      {extractModifier(reaction, pos, name); mult = 1.0;}

      names.push_back(name);
      mults.push_back(mult);
    }
}

void CChemEqInterface::extractElement(const std::string & input,
                                      std::string::size_type & pos,
                                      std::string & name, C_FLOAT64 & mult)
{
  std::string Value;

  std::string::size_type Start = input.find_first_not_of(" ", pos);
  std::string::size_type End = input.find(" + ", Start);
  std::string::size_type Multiplier = input.find("*", Start);
  std::string::size_type NameStart;
  std::string::size_type NameEnd;

  if (Multiplier == std::string::npos || Multiplier > End)
    {
      NameStart = Start;
      mult = 1.0;
    }
  else
    {
      NameStart = input.find_first_not_of(" ", Multiplier + 1);
      Value = input.substr(Start, Multiplier - Start);
      mult = atof(Value.c_str());
    }

  NameEnd = input.find_first_of(" ", NameStart);

  if (NameStart != std::string::npos)
    name = input.substr(NameStart, NameEnd - NameStart);
  else
    name = "";

  pos = (End == std::string::npos) ? End : End + 3;
}

void CChemEqInterface::extractModifier(const std::string & input,
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
}

C_INT32 CChemEqInterface::getMolecularity(const std::string & role) const
  {
    const std::vector<C_FLOAT64> * tmpVector;

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
