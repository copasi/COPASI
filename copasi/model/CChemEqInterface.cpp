#include <math.h>
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

      if (name != "")
        {
          names.push_back(name);
          mults.push_back(mult);
        }
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

    for (it = metabs.begin(); it != itEnd; ++it)
      model->addMetabolite(CMetabNameInterface::extractCompartmentName(model, *it),
                           CMetabNameInterface::extractMetabName(model, *it),
                           0.1, CMetab::METAB_VARIABLE);

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
bool CChemEqInterface::isValidEq(const std::string eq)
{
  //TODO: tidy up all the debugging output, and insert code to bring up message boxes as appropriate

  // a valid equation should be in the format of (metab + (metab)*) (= | ->) (metab (+ metab)*) (; (modifieer)*)
  // metab here can include moiety
  C_INT16 startMetab, endMetab, endEq, sep1, sep2, sep3;  // the positions of various characters looked for
  std::string unit;                                                                 // a unit in the equation to be checked

  startMetab = eq.find_first_not_of(" ");  // the starting position of the first metabolite, also the equation
  endEq = eq.find_last_not_of(" ") + 1;

  if (endEq <= startMetab)  // empty equation string
    {
      //debugging
      cout << "Empty equation string\n";
      return false;
    }

  sep1 = eq.find("->");
  sep3 = eq.rfind("->");
  if (sep1 != sep3)
    {
      //debugging
      cout << "Multiple separators found\n";
      return false;
    }

  sep2 = eq.find("=");
  sep3 = eq.rfind("=");
  if (sep2 != sep3)
    {
      //debugging
      cout << "Multiple separators found\n";
      return false;
    }

  // one of the separators must be present but not both
  if (sep1 < 0)
    {
      if (sep2 < 0)
        {
          //debugging
          cout << "no separator found\n";
          return false;
        }
      else
        sep1 = sep2;
    }
  else
    {
      if (sep2 >= 0)
        {
          //debugging
          cout << "two separators found\n";
          return false;
        }
    }

  sep2 = eq.find(";");
  sep3 = eq.rfind(";");
  if (sep2 != sep3)
    {
      //debugging
      cout << "found more than one \";\"\n";
      return false;
    }

  if (sep2 < 0)
    sep2 = endEq;

  if (sep2 <= sep1)
    {
      //debugging
      cout << "found \";\" on the LHS of the equation\n";
      return false;
    }

  // next check if each metabolite name is valid

  //very clumsy code, but hopefully does the job
  while (startMetab < sep2)  // the equation up to the modifiers, if any
    {
      sep3 = eq.find(" + ", startMetab);

      if (sep3 < 0)  // no "+" in the remaining equation
        {
          if (startMetab < sep1)  // i.e. still on the substrate side, so only one substrate (left)
            {
              endMetab = sep1;
              sep3 = sep1 - 1; // -1 because of the search at the end of the loop
            }
          else if (startMetab == sep1)   // no substrates in the equation, and only one product
            {
              startMetab = eq.find_first_not_of(">", sep1 + 1); // to account for the different lengths of "->" and "="
              startMetab = eq.find_first_not_of(" ", startMetab);  // and then get rid of the white spaces before metabolites
              endMetab = sep2;
              sep3 = sep2 - 1;   // -1 because of the search at the end of the loop (in order to skip ";")
            }
          else  // only one product (left)
            {
              endMetab = sep2;
              sep3 = sep2 - 1;
            }
        }
      else if (sep3 > sep2)
        {
          //debugging
          cout << "shouldn't have \"+\" beyond \";\" \n";
          return false;  // shouldn't have "+" beyond ";"
        }
      else if (sep3 + 2 == endEq)  // missing product
        {
          //debugging
          cout << "missing product\n";
          return false;
        }
      else if (startMetab == sep1)   // no substrates specified, so cross over to the product side
        {
          startMetab = eq.find_first_not_of(">", sep1 + 1); // to account for the different lengths of "->" and "="
          startMetab = eq.find_first_not_of(" ", startMetab);  // and then get rid of the white spaces before metabolites
          endMetab = sep3;
        }
      else if ((startMetab < sep1) && (sep3 > sep1))  // the next "+" is on the product side but we are still looking at the substrates
        {
          endMetab = sep1;
          sep3 = endMetab - 1;
        }
      else
        endMetab = sep3;

      // adjust the starting position to allow for moiety
      C_INT16 star = eq.find("*", startMetab);

      if ((star >= 0) && (star < endMetab))
        startMetab = eq.find_first_not_of(" ", star + 1);

      // note that if the last substrate name is missing after an *, the error detected might be invalid metabolite name or missing substrate

      if (startMetab < 0)  // this happens if the last metabolite is missing after a *, but there is one or more white spaces after *
        {
          // debugging
          cout << "missing metabolite name after *\n";
          return false;
        }

      unit = eq.substr(startMetab, endMetab - startMetab);
      // debugging
      //cout<<"metabolite name: ("<<unit<<")\n";

      if (!CMetabNameInterface::isValidMetabName(unit))
        {
          //debugging
          cout << "Not a valid metabolite name: (" << unit << ")\n";
          return false;
        }

      startMetab = eq.find_first_not_of(">", sep3 + 2);  // to account for the different lengths of "->" and "="
      startMetab = eq.find_first_not_of(" ", startMetab);

      if (startMetab < 0)  // this can happen if the end of the equation is already reached
        break;

      if ((startMetab == sep1) || (startMetab == sep2))  // this means a metabolite is missing after a "+"
        {
          //debugging
          cout << "substrate/product missing\n";
          return false;
        }
    }

  // no checks for modifiers, since nothing to check against modifier names

  return true;
}
