#include "copasi.h"

#include <iostream>
#include <sstream>

#include "CSpecLine.h"
#include "CDeTerm.h"
#include "utilities/CGlobals.h"

CSpecLine::CSpecLine() {CONSTRUCTOR_TRACE;}

CSpecLine::CSpecLine(C_INT32 type, std::string contents)
    : mType(type),
    mContents(contents)
{CONSTRUCTOR_TRACE;}
CSpecLine::~CSpecLine() {DESTRUCTOR_TRACE;}

std::string CSpecLine::convertedType(int type)
{
  switch (type)
    {
    case CMNT:
      return "CMNT";

    case DE:
      return "DE";

    case EQN:
      return "EQN";

    case INIT:
      return "INIT";

    case CNST:
      return "CNST";

    case VOL:
      return "VOL";

    case CPT:
      return "CPT";

    case RATE:
      return "RATE";

    case FUN:
      return "FUN";

    default:
      return "Not a known type";
    }
}

std::string CSpecLine::extractLeft()
{
  // Find the operator position
  std::string::size_type op_pos = mContents.find_first_of('=');

  if (op_pos == std::string::npos || op_pos == 0)
    {
      // No operator like "=" or ":=", or LHS is empty, so LHS not defined
      return "";
    }
  else
    {
      if (mContents[op_pos - 1] == ':')
        {
          // We found the operator ":="
          --op_pos;

          if (op_pos == 0)
            {
              // LHS empty
              return "";
            }
        }
    }

  // Now find the start position. If the string begins with a
  // compartment specification, use the end of that +1 as the
  // start position; otherwise, use the string beginning.
  std::string ::size_type start_pos = mContents.find_first_of(':');

  if (start_pos == std::string::npos)
    {
      start_pos = 0;
    }
  else if (start_pos >= op_pos)
    {
      // invalid string
      return "";
    }
  else
    {
      start_pos++;
    }

  // Strip the leading blanks again
  start_pos = mContents.find_first_not_of(' ', start_pos);

  std::string tmp = stripBlanks(mContents.substr(start_pos, op_pos - start_pos));

  return tmp;
}

std::string CSpecLine::extractRight()
{
  std::string::size_type start_pos = mContents.find_first_of('=');

  if (start_pos == std::string::npos)
    {
      // No operator =, thus no RHS
      return "";
    }
  else
    {
      //        std::cout << "Returning RHS = " << mContents.substr(start_pos+1) << std::endl;
      return mContents.substr(start_pos + 1);
    }
}

std::string CSpecLine::extractCpt()
{
  std::string::size_type end_pos = mContents.find_first_of(':');

  if (mContents[end_pos + 1] == '=' || end_pos == std::string::npos)
    {
      // No compartment is specified
      return "";
    }

  // See if the first bit contains the keyword INIT or Init or init.
  // If it does, look for the compartment only after that
  std::string::size_type start_pos = mContents.find("INIT");

  if (start_pos == std::string::npos)
    {
      start_pos = mContents.find("init");
    }

  if (start_pos == std::string::npos)
    {
      start_pos = mContents.find("Init");
    }

  if (start_pos == std::string::npos)
    {
      start_pos = 0;
    }
  else
    {
      start_pos = mContents.substr(start_pos).find_first_not_of("INITinit");
    }

  return stripBlanks(mContents.substr(start_pos, end_pos - start_pos));
}

std::string CSpecLine::stripBlanks(const std::string instr)
{
  std::string::size_type start_pos = instr.find_first_not_of(" \t");
  std::string::size_type end_pos = instr.find_last_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_/+-*:=");

  if (start_pos == std::string::npos || end_pos == std::string::npos)
    {
      // error
      return "";
    }

  return instr.substr(start_pos, end_pos - start_pos + 1);
}

bool CBaseEqn::operator==(const CBaseEqn &rhs) const
{
  if ((mCompartment == rhs.getCompartment()) &&
      (mMetabolite == rhs.getMetabolite()))
  {
    return true;
  }

  return false;
}

CTempMetab::CTempMetab(const CTempMetab &rhs)
    : mMetab(rhs.mMetab),
    mMultiplicity(rhs.mMultiplicity),
    mNumChange(rhs.mNumChange)
{}

CTempMetab *CTempReaction::addMetabolite(CMetab *metab)
{
  // First try to find this metabolite on the existing stack

  for (unsigned C_INT32 i = 0; i < mMetabs.size(); i++)
    {
      if (mMetabs[i].getMetab()->getName() == metab->getName())
        {
          return &mMetabs[i];
        }
    }

  // If we get here, this metab has not yet been added
  mMetabs.push_back(CTempMetab(metab));

  return &*(mMetabs.end() - 1);
}

void CTempReaction::setIdentifiers(const CDeTerm *deTerm)
{
  const std::vector< std::pair<CDeTerm::Type, std::string>* > & TokenStack = deTerm->getTokenStack();
  unsigned int i, imax = TokenStack.size();

  for (i = 0; i < imax; i++)
    if (TokenStack[i]->first == CDeTerm::IDENT)
      mIdentifiers.push_back(TokenStack[i]->second);

  return;
}

void CTempReaction::compile(CModel *model,
                            const std::vector<CNameVal> & rates,
                            const std::vector<CNameVal> & constants)
{
  // Create the reaction
  CReaction *reaction = new CReaction(mName); // XXX TODO: add the bits necessary
  // Determine the substrates and products of the reaction
  CTempMetab *tmp_metab = 0;
  C_INT32 substrate_mult, product_mult, num_change;
  unsigned C_INT32 i;

  for (i = 0; i < mMetabs.size(); i++)
    {
      substrate_mult = mMetabs[i].getMultiplicity();
      num_change = mMetabs[i].getNumChange();
      product_mult = substrate_mult + num_change;

      if (substrate_mult > 0)
        {
          tmp_metab = new CTempMetab(mMetabs[i]);
          mSubstrates.push_back(*tmp_metab);
        }

      if (product_mult > 0)
        {
          tmp_metab = new CTempMetab(mMetabs[i]);
          tmp_metab->setMultiplicity(product_mult);
          mProducts.push_back(*tmp_metab);
        }
    }

  // Create strings describing the chemical equation
  std::ostringstream lhs_desc;

  std::ostringstream rhs_desc;

  C_INT32 mult = 0;

  bool is_first;

  is_first = true;

  for (i = 0; i < mSubstrates.size(); i++)
    {
      mult = mSubstrates[i].getMultiplicity();

      if (is_first == false)
        {
          lhs_desc << " + ";
        }

      is_first = false;

      if (mult > 1)
        {
          lhs_desc << substrate_mult << "*";
        }

      lhs_desc << mSubstrates[i].getMetab()->getName();
    }

  is_first = true;

  for (i = 0; i < mProducts.size(); i++)
    {
      mult = mProducts[i].getMultiplicity();

      if (is_first == false)
        {
          rhs_desc << " + ";
        }

      is_first = false;

      if (mult > 1)
        {
          rhs_desc << mult + "*";
        }

      rhs_desc << mProducts[i].getMetab()->getName();
    }

  std::string chemeqdesc = lhs_desc.str() + "->" + rhs_desc.str();
  // Set the chemical equation description in the reaction. This
  // automatically parses the description, extracts the metabolites
  // and constructs the chemical equations.
  reaction->setChemEq(chemeqdesc);

  // Set up the kinetic function, and add it to the database
  CKinFunction *fun = new CKinFunction();
  fun->setName(mName);
  fun->setDescription(mRateDescription);
  // Parse the identifiers to specify the function parameters and the
  // Is2... stuff of the reaction
  std::string *name;
  CFunctionParameters & Parameters = fun->getParameters();
  int index;
  CReaction::CId2Param *id2Param;
  CReaction::CId2Metab *id2Metab;

  for (i = 0; i < mIdentifiers.size(); i++)
    {
      name = &mIdentifiers[i];
      index = model->findMetab(*name);

      if (-1 == index) // A parameter
        {
          id2Param = new CReaction::CId2Param();
          id2Param->setIdentifierName(*name);
          id2Param->setValue(getParameterValue(*name, rates, constants));
          Parameters.add(*name, CFunctionParameter::FLOAT64, "PARAMETER");
        }
      else
        {
          id2Metab = new CReaction::CId2Metab();
          id2Metab->setIdentifierName(*name);
          id2Metab->setMetaboliteName(model->getMetabolites()[i]->getName());
          id2Metab->setCompartmentName(model->getMetabolites()[i]->getCompartment()->getName());

          if (isIn(mSubstrates, *name))
            {
              Parameters.add(*name, CFunctionParameter::FLOAT64, "SUBSTRATE");
              reaction->getId2Substrates().add(id2Metab);
            }
          else if (isIn(mProducts, *name))
            {
              Parameters.add(*name, CFunctionParameter::FLOAT64, "PRODUCT");
              reaction->getId2Products().add(id2Metab);
            }
          else // is Modifier
            {
              Parameters.add(*name, CFunctionParameter::FLOAT64, "MODIFIER");
              reaction->getId2Modifiers().add(id2Metab);
            }
        }
    }

  fun->compile();
  Copasi->FunctionDB.loadedFunctions().add(*fun);
  // Associate this kinetic function with the reaction
  reaction->setFunction(mName);
  // Finally, add the reaction to the model
  model->getReactions().add(reaction);
}
CTempReactionSet::CTempReactionSet() {}

void CTempReactionSet::addReaction(CTempReaction *tempreact)
{
  mReactions.push_back(*tempreact);
}

CTempReaction *CTempReactionSet::findReaction(std::string name)
{
  for (unsigned C_INT32 i = 0; i < mReactions.size(); i++)
    {
      if (name == mReactions[i].getName())
        {
          return &mReactions[i];
        }
    }

  return 0; // If we get here, we didn't find it
}

bool CTempReaction::isIn(std::vector<CTempMetab> & metabs, const std::string & target)
{
  unsigned int i, imax = metabs.size();

  for (i = 0; i < imax; i++)
    if (target == metabs[i].getMetab()->getName())
      return true;

  return false;
}

C_FLOAT64 CTempReaction::getParameterValue(const std::string & name,
    const std::vector<CNameVal> & rates,
    const std::vector<CNameVal> & C_UNUSED(constants))
{
  unsigned i, imax = rates.size();

  for (i = 0; i < imax; i++)
    if (name == rates[i].getName())
      return rates[i].getVal();

  return 0;
}
