// CReaction
//
// Derived from Gepasi's cstep.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Stefan Hoops

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "utilities/CGlobals.h"
#include "CReaction.h"
#include "CCompartment.h"
#include "utilities/utilities.h"

#ifdef WIN32
#define max(a , b)  ((a) > (b) ? (a) : (b))
#define min(a , b)  ((a) < (b) ? (a) : (b))
#endif // WIN32

C_FLOAT64 CReaction::mDefaultScalingFactor = 1.0;

CReaction::CReaction()
{
  CONSTRUCTOR_TRACE;
  mFlux = 0.0;
  mScaledFlux = 0.0;
  mReversible = TRUE;
  mFunction = NULL;
  mScalingFactor = &mDefaultScalingFactor;
}

CReaction::CReaction(const CReaction & src)
{
  CONSTRUCTOR_TRACE;
  mName = src.mName;
  mFlux = src.mFlux;
  mScaledFlux = src.mScaledFlux;
  mReversible = src.mReversible;
  mChemEq = src.mChemEq;
  setFunction(src.mFunction->getName());
  mScalingFactor = src.mScalingFactor;

  mId2Substrates = CCopasiVector < CId2Metab > (src.mId2Substrates);
  mId2Products = CCopasiVector < CId2Metab > (src.mId2Products);
  mId2Modifiers = CCopasiVector < CId2Metab > (src.mId2Modifiers);
  mId2Parameters = CCopasiVector < CId2Param > (src.mId2Parameters);
}

CReaction::CReaction(const string & name)
{
  CONSTRUCTOR_TRACE;
  mName = name;
  mFlux = 0.0;
  mScaledFlux = 0.0;
  mReversible = TRUE;
  mFunction = NULL;
  mScalingFactor = &mDefaultScalingFactor;
}
CReaction::~CReaction() {cleanup(); DESTRUCTOR_TRACE; }

void CReaction::cleanup()
{
  mId2Substrates.cleanup();
  mId2Products.cleanup();
  mId2Modifiers.cleanup();
  mId2Parameters.cleanup();

  cleanupCallParameters();
  mParameterDescription.cleanup();
}

C_INT32 CReaction::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;

  string KinType;

  if ((Fail = configbuffer.getVariable("Step", "string", &mName,
                                       CReadConfig::SEARCH)))
    return Fail;

  string ChemEq;

  if ((Fail = configbuffer.getVariable("Equation", "string", &ChemEq)))
    return Fail;

  setChemEq(ChemEq);

  if ((Fail = configbuffer.getVariable("KineticType", "string", &KinType)))
    return Fail;

  setFunction(KinType);

  if (mFunction == NULL)
    return Fail = 1;

  if ((Fail = configbuffer.getVariable("Reversible", "bool", &mReversible,
                                       CReadConfig::SEARCH)))
    return Fail;

  if (configbuffer.getVersion() < "4")
    Fail = loadOld(configbuffer);
  else
    Fail = loadNew(configbuffer);

  return Fail;
}

C_INT32 CReaction::save(CWriteConfig & configbuffer)
{
  C_INT32 Fail = 0;
  C_INT32 Size = 0;
  C_INT32 i = 0;

  if ((Fail = configbuffer.setVariable("Step", "string", &mName)))
    return Fail;

  if ((Fail = configbuffer.setVariable("Equation", "string", &mChemEq)))
    return Fail;

  string KinType = mFunction->getName();

  if ((Fail = configbuffer.setVariable("KineticType", "string", &KinType)))
    return Fail;

  if ((Fail = configbuffer.setVariable("Reversible", "bool", &mReversible)))
    return Fail;

  Size = mId2Substrates.size();

  if ((Fail = configbuffer.setVariable("Substrates", "C_INT32", &Size)))
    return Fail;

  for (i = 0; i < Size; i++)
    {
      if ((Fail = configbuffer.setVariable("Identifier", "string",
                                           &mId2Substrates[i]->mIdentifierName)))
        return Fail;

      if ((Fail = configbuffer.setVariable("Compartment", "string",
                                           &mId2Substrates[i]->mCompartmentName)))
        return Fail;

      if ((Fail = configbuffer.setVariable("Metabolite", "string",
                                           &mId2Substrates[i]->mMetaboliteName)))
        return Fail;
    }

  Size = mId2Products.size();

  if ((Fail = configbuffer.setVariable("Products", "C_INT32", &Size)))
    return Fail;

  for (i = 0; i < Size; i++)
    {
      if ((Fail = configbuffer.setVariable("Identifier", "string",
                                           &mId2Products[i]->mIdentifierName)))
        return Fail;

      if ((Fail = configbuffer.setVariable("Compartment", "string",
                                           &mId2Products[i]->mCompartmentName)))
        return Fail;

      if ((Fail = configbuffer.setVariable("Metabolite", "string",
                                           &mId2Products[i]->mMetaboliteName)))
        return Fail;
    }

  Size = mId2Modifiers.size();

  if ((Fail = configbuffer.setVariable("Modifiers", "C_INT32", &Size)))
    return Fail;

  for (i = 0; i < Size; i++)
    {
      if ((Fail = configbuffer.setVariable("Identifier", "string",
                                           &mId2Modifiers[i]->mIdentifierName)))
        return Fail;

      if ((Fail = configbuffer.setVariable("Compartment", "string",
                                           &mId2Modifiers[i]->mCompartmentName)))
        return Fail;

      if ((Fail = configbuffer.setVariable("Metabolite", "string",
                                           &mId2Modifiers[i]->mMetaboliteName)))
        return Fail;
    }

  Size = mId2Parameters.size();

  if ((Fail = configbuffer.setVariable("Constants", "C_INT32", &Size)))
    return Fail;

  for (i = 0; i < Size; i++)
    {
      if ((Fail = configbuffer.setVariable("Identifier", "string",
                                           &mId2Parameters[i]->mIdentifierName)))
        return Fail;

      if ((Fail = configbuffer.setVariable("Value", "C_FLOAT64",
                                           &mId2Parameters[i]->mValue)))
        return Fail;
    }

  return Fail;
}

C_INT32 CReaction::saveOld(CWriteConfig & configbuffer, const vector < CMetab* > &metabolites)
{
  C_INT32 Fail = 0;
  C_INT32 Size = 0;
  C_INT32 i = 0, j = 0, s = 0, c = -1;
  char strtmp[32];
  CCopasiVector < CChemEqElement > reactants;
  s = metabolites.size();
  if ((Fail = configbuffer.setVariable("Step", "string", &mName)))
    return Fail;
  if ((Fail = configbuffer.setVariable("Equation", "string", &mChemEq)))
    return Fail;
  string KinType = mFunction->getName();
  if ((Fail = configbuffer.setVariable("KineticType", "string", &KinType)))
    return Fail;
  if ((Fail = configbuffer.setVariable("Flux", "C_FLOAT64", &mFlux)))
    return Fail;
  if ((Fail = configbuffer.setVariable("Reversible", "bool", &mReversible)))
    return Fail;
  Size = mChemEq.getSubstrates().size();
  if ((Fail = configbuffer.setVariable("Substrates", "C_INT32", &Size)))
    return Fail;
  Size = mChemEq.getProducts().size();
  if ((Fail = configbuffer.setVariable("Products", "C_INT32", &Size)))
    return Fail;
  Size = mId2Modifiers.size();
  if ((Fail = configbuffer.setVariable("Modifiers", "C_INT32", &Size)))
    return Fail;
  Size = mId2Parameters.size();
  if ((Fail = configbuffer.setVariable("Constants", "C_INT32", &Size)))
    return Fail;
  reactants = mChemEq.getSubstrates();
  Size = reactants.size();
  for (i = 0; i < Size; i++)
    {
      for (j = 0, c = -1; j < s; j++)
        if (reactants[i]->getMetabolite().getName() == metabolites[j]->getName())
          {
            c = j;
            break;
          }
      if (c == -1)
        return -1;
      sprintf(strtmp, "Subs%ld", i);
      if ((Fail = configbuffer.setVariable(strtmp, "C_INT32", (void *) & c)))
        return Fail;
    }
  reactants = mChemEq.getProducts();
  Size = reactants.size();
  for (i = 0; i < Size; i++)
    {
      for (j = 0, c = -1; j < s; j++)
        if (reactants[i]->getMetabolite().getName() == metabolites[j]->getName())
          {
            c = j;
            break;
          }
      if (c == -1)
        return -1;
      sprintf(strtmp, "Prod%ld", i);
      if ((Fail = configbuffer.setVariable(strtmp, "C_INT32", (void *) & c)))
        return Fail;
    }
  Size = mId2Modifiers.size();
  for (i = 0; i < Size; i++)
    {
      for (j = 0, c = -1; j < s; j++)
        if (mId2Modifiers[i]->mMetaboliteName == metabolites[j]->getName())
          {
            c = j;
            break;
          }
      if (c == -1)
        return -1;
      sprintf(strtmp, "Modf%ld", i);
      if ((Fail = configbuffer.setVariable(strtmp, "C_INT32", (void *) & c)))
        return Fail;
    }
  Size = mId2Parameters.size();
  for (i = 0; i < Size; i++)
    {
      sprintf(strtmp, "Param%ld", i);
      if ((Fail = configbuffer.setVariable(strtmp, "C_FLOAT64", (void *) & mId2Parameters[i]->mValue)))
        return Fail;
    }
  return Fail;
}

void CReaction::saveSBML(std::ofstream &fout, C_INT32 r)
{
  string tmpstr, tmpstr2;
  C_INT32 i;
  CCopasiVector < CChemEqElement > rr;
  CCopasiVectorS < CNodeK > node;

  FixSName(mName, tmpstr);
  fout << "\t\t\t<reaction name=\"" << tmpstr << "\"";
  fout << " reversible=\"";
  if (mReversible)
    fout << "true";
  else
    fout << "false";
  fout << "\">" << endl;
  fout << "\t\t\t\t<listOfReactants>" << endl;
  // check if we need to reference the dummy metabolite
  rr = mChemEq.getSubstrates();
  if (rr.size() == 0)
    fout << "\t\t\t\t\t<specieReference specie=\"_void_\" stoichiometry=\"1\"/>" << endl;
  else
    {
      // write them out
      for (i = 0; i < rr.size(); i++)
        {
          tmpstr2 = rr[i]->getMetaboliteName();
          FixSName(tmpstr2, tmpstr);
          fout << "\t\t\t\t\t<specieReference specie=\"" << tmpstr << "\"";
          fout << " stoichiometry=\"" << rr[i]->getMultiplicity() << "\"/>" << endl;
        }
    }
  fout << "\t\t\t\t</listOfReactants>" << endl;
  fout << "\t\t\t\t<listOfProducts>" << endl;
  // check if we need to reference the dummy metabolite
  rr = mChemEq.getProducts();
  if (rr.size() == 0)
    fout << "\t\t\t\t\t<specieReference specie=\"_void_\" stoichiometry=\"1\"/>" << endl;
  else
    {
      // write them out
      for (i = 0; i < rr.size(); i++)
        {
          tmpstr2 = rr[i]->getMetaboliteName();
          FixSName(tmpstr2, tmpstr);
          fout << "\t\t\t\t\t<specieReference specie=\"" << tmpstr << "\"";
          fout << " stoichiometry=\"" << rr[i]->getMultiplicity() << "\"/>" << endl;
        }
    }
  fout << "\t\t\t\t</listOfProducts>" << endl;
  fout << "\t\t\t\t<kineticLaw formula=\"";
  // kinetic function string
  initCallParameterNames();
  setCallParameterNames();
  checkCallParameterNames();
  tmpstr2 = StringPrint("_%ld", r);
  fout << mFunction->getSBMLString(mCallParameterNames, tmpstr2);
  cleanupCallParameterNames();
  fout << "\">" << endl;
  fout << "\t\t\t\t\t<listOfParameters>" << endl;
  for (i = 0; i < mId2Parameters.size(); i++)
    {
      FixSName(mId2Parameters[i]->mIdentifierName, tmpstr);
      fout << "\t\t\t\t\t\t<parameter name=\"" + tmpstr;
      fout << "_" << r << "\" value=\"" << mId2Parameters[i]->mValue << "\"/>" << endl;
    }
  fout << "\t\t\t\t\t</listOfParameters>" << endl;
  fout << "\t\t\t\t</kineticLaw>" << endl;
  fout << "\t\t\t</reaction>" << endl;
}

C_INT32 CReaction::getSubstrateNumber(void)
{
  return mChemEq.getSubstrates().size();
}

C_INT32 CReaction::getProductNumber(void)
{
  return mChemEq.getProducts().size();
}

CCopasiVector < CReaction::CId2Metab > &CReaction::getId2Substrates()
{
  return mId2Substrates;
}

CCopasiVector < CReaction::CId2Metab > &CReaction::getId2Products()
{
  return mId2Products;
}

CCopasiVector < CReaction::CId2Metab > &CReaction::getId2Modifiers()
{
  return mId2Modifiers;
}

CCopasiVector < CReaction::CId2Param > &CReaction::getId2Parameters()
{
  return mId2Parameters;
}

const string & CReaction::getName() const
  {
    return mName;
  }

CChemEq & CReaction::getChemEq()
{
  return mChemEq;
}

CFunction & CReaction::getFunction()
{
  return *mFunction;
}

const C_FLOAT64 & CReaction::getFlux() const
  {
    return mFlux;
  }

const C_FLOAT64 & CReaction::getScaledFlux() const
  {
    return mScaledFlux;
  }

bool CReaction::isReversible() const
  {
    return (mReversible == TRUE);
  }

void CReaction::setName(const string & name)
{
  mName = name;
}

void CReaction::setChemEq(const string & chemEq)
{
  mReversible = mChemEq.setChemicalEquation(chemEq);
}

void CReaction::setReversible(bool reversible)
{
  mReversible = reversible;
}

void CReaction::setFunction(const string & functionName)
{
  mFunction = Copasi->FunctionDB.findLoadFunction(functionName);
  if (!mFunction)
    CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 1, functionName.c_str());

  initCallParameters();
}

void CReaction::compile(CCopasiVectorNS < CCompartment > & compartments)
{
  unsigned C_INT32 i;

  for (i = 0; i < mId2Substrates.size(); i++)
    mId2Substrates[i]->mpMetabolite =
      compartments[mId2Substrates[i]->mCompartmentName]->
      metabolites()[mId2Substrates[i]->mMetaboliteName];

  for (i = 0; i < mId2Products.size(); i++)
    mId2Products[i]->mpMetabolite =
      compartments[mId2Products[i]->mCompartmentName]->
      metabolites()[mId2Products[i]->mMetaboliteName];

  for (i = 0; i < mId2Modifiers.size(); i++)
    mId2Modifiers[i]->mpMetabolite =
      compartments[mId2Modifiers[i]->mCompartmentName]->
      metabolites()[mId2Modifiers[i]->mMetaboliteName];

  initCallParameters();
  setCallParameters();
  checkCallParameters();
  mChemEq.compile(compartments);
  setScalingFactor();
}

C_INT32 CReaction::loadNew(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;
  C_INT32 Size;
  C_INT32 i;

  if ((Fail = configbuffer.getVariable("Substrates", "C_INT32", &Size)))
    return Fail;

  mId2Substrates.resize(Size);

  for (i = 0; i < Size; i++)
    {
      if ((Fail = configbuffer.getVariable("Identifier", "string",
                                           &mId2Substrates[i]->mIdentifierName)))
        return Fail;

      if ((Fail = configbuffer.getVariable("Compartment", "string",
                                           &mId2Substrates[i]->mCompartmentName)))
        return Fail;

      if ((Fail = configbuffer.getVariable("Metabolite", "string",
                                           &mId2Substrates[i]->mMetaboliteName)))
        return Fail;
    }

  if ((Fail = configbuffer.getVariable("Products", "C_INT32", &Size)))
    return Fail;

  mId2Products.resize(Size);

  for (i = 0; i < Size; i++)
    {
      if ((Fail = configbuffer.getVariable("Identifier", "string",
                                           &mId2Products[i]->mIdentifierName)))
        return Fail;

      if ((Fail = configbuffer.getVariable("Compartment", "string",
                                           &mId2Products[i]->mCompartmentName)))
        return Fail;

      if ((Fail = configbuffer.getVariable("Metabolite", "string",
                                           &mId2Products[i]->mMetaboliteName)))
        return Fail;
    }

  if ((Fail = configbuffer.getVariable("Modifiers", "C_INT32", &Size)))
    return Fail;

  mId2Modifiers.resize(Size);

  for (i = 0; i < Size; i++)
    {
      if ((Fail = configbuffer.getVariable("Identifier", "string",
                                           &mId2Modifiers[i]->mIdentifierName)))
        return Fail;

      if ((Fail = configbuffer.getVariable("Compartment", "string",
                                           &mId2Modifiers[i]->mCompartmentName)))
        return Fail;

      if ((Fail = configbuffer.getVariable("Metabolite", "string",
                                           &mId2Modifiers[i]->mMetaboliteName)))
        return Fail;
    }

  if ((Fail = configbuffer.getVariable("Constants", "C_INT32", &Size)))
    return Fail;

  mId2Parameters.resize(Size);

  for (i = 0; i < Size; i++)
    {
      if ((Fail = configbuffer.getVariable("Identifier", "string",
                                           &mId2Parameters[i]->mIdentifierName)))
        return Fail;

      if ((Fail = configbuffer.getVariable("Value", "C_FLOAT64",
                                           &mId2Parameters[i]->mValue)))
        return Fail;
    }

  return Fail;
}

C_INT32 CReaction::loadOld(CReadConfig & configbuffer)
{
  string name;

  C_INT32 Fail = 0;
  unsigned C_INT32 SubstrateSize, ProductSize, ModifierSize, ParameterSize;
  unsigned C_INT32 i, imax, pos;
  C_INT32 index;

  CFunctionParameter::DataType Type;

  configbuffer.getVariable("Substrates", "C_INT32", &SubstrateSize);
  mId2Substrates.resize(min(SubstrateSize, usageRangeSize("SUBSTRATE")));

  configbuffer.getVariable("Products", "C_INT32", &ProductSize);
  mId2Products.resize(min(ProductSize, usageRangeSize("PRODUCT")));

  configbuffer.getVariable("Modifiers", "C_INT32", &ModifierSize);
  mId2Modifiers.resize(min(ModifierSize, usageRangeSize("MODIFIER")));

  configbuffer.getVariable("Constants", "C_INT32", &ParameterSize);
  mId2Parameters.resize(min(ParameterSize, usageRangeSize("PARAMETER")));

  // Construct Id2Substrate
  imax = mId2Substrates.size();

  for (i = 0, pos = 0, Type = CFunctionParameter::INT16; i < imax; i++)
    {
      name = StringPrint("Subs%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);

      mId2Substrates[i]->mMetaboliteName =
        Copasi->OldMetabolites[index]->getName();

      if (Type < CFunctionParameter::VINT16)
        Type =
          mParameterDescription.getParameterByUsage("SUBSTRATE", pos).getType();

      mId2Substrates[i]->mIdentifierName =
        mParameterDescription[pos - 1]->getName();

      if (Type >= CFunctionParameter::VINT16)
        mId2Substrates[i]->mIdentifierName += StringPrint("_%ld", i);
    }

  for (i = imax; i < SubstrateSize; i++)
    {
      name = StringPrint("Subs%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);
    }

  // Construct Id2Product
  imax = mId2Products.size();

  for (i = 0, pos = 0, Type = CFunctionParameter::INT16; i < imax; i++)
    {
      name = StringPrint("Prod%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);

      mId2Products[i]->mMetaboliteName =
        Copasi->OldMetabolites[index]->getName();

      if (Type < CFunctionParameter::VINT16)
        Type =
          mParameterDescription.getParameterByUsage("PRODUCT", pos).getType();

      mId2Products[i]->mIdentifierName =
        mParameterDescription[pos - 1]->getName();

      if (Type >= CFunctionParameter::VINT16)
        mId2Products[i]->mIdentifierName += StringPrint("_%ld", i);
    }

  for (i = imax; i < ProductSize; i++)
    {
      name = StringPrint("Prod%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);
    }

  // Construct Id2Modifier
  imax = mId2Modifiers.size();

  for (i = 0, pos = 0, Type = CFunctionParameter::INT16; i < imax; i++)
    {
      name = StringPrint("Modf%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);

      mId2Modifiers[i]->mMetaboliteName =
        Copasi->OldMetabolites[index]->getName();

      if (Type < CFunctionParameter::VINT16)
        Type =
          mParameterDescription.getParameterByUsage("MODIFIER", pos).getType();

      mId2Modifiers[i]->mIdentifierName =
        mParameterDescription[pos - 1]->getName();

      if (Type >= CFunctionParameter::VINT16)
        mId2Modifiers[i]->mIdentifierName += StringPrint("_%ld", i);
    }

  for (i = imax; i < ModifierSize; i++)
    {
      name = StringPrint("Modf%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);
    }

  // Construct Id2Parameter
  imax = mId2Parameters.size();

  for (i = 0, pos = 0, Type = CFunctionParameter::INT16; i < imax; i++)
    {
      name = StringPrint("Param%d", i);
      configbuffer.getVariable(name, "C_FLOAT64",
                               &mId2Parameters[i]->mValue);

      if (Type < CFunctionParameter::VINT16)
        Type =
          mParameterDescription.getParameterByUsage("PARAMETER", pos).getType();

      mId2Parameters[i]->mIdentifierName =
        mParameterDescription[pos - 1]->getName();

      if (Type >= CFunctionParameter::VINT16)
        mId2Parameters[i]->mIdentifierName += StringPrint("_%ld", i);
    }

  for (i = imax; i < ParameterSize; i++)
    {
      name = StringPrint("Param%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);
    }

  return Fail;
}

CReaction::CId2Metab::CId2Metab()
{
  mpMetabolite = NULL;
}

CReaction::CId2Metab::CId2Metab(const CId2Metab & src)
{
  mIdentifierName = src.mIdentifierName;
  mMetaboliteName = src.mMetaboliteName;
  mCompartmentName = src.mCompartmentName;
  mpMetabolite = NULL;
}

CReaction::CId2Metab::~CId2Metab()
{}

void CReaction::CId2Metab::cleanup()
{}

CReaction::CId2Param::CId2Param()
{}

CReaction::CId2Param::CId2Param(const CId2Param & src)
{
  mIdentifierName = src.mIdentifierName;
  mValue = src.mValue;
}

CReaction::CId2Param::~CId2Param()
{}

void CReaction::CId2Param::cleanup()
{}

void CReaction::old2New(const vector < CMetab* > & metabolites)
{
  string Name;
  unsigned C_INT32 i, j, s, z;

  z = metabolites.size();
  s = mId2Substrates.size();
  for (i = 0; i < s; i++)
    {
      Name = mId2Substrates[i]->mMetaboliteName;
      for (j = 0; j < z; j++)
        if (Name == metabolites[j]->getName())
          break;
      mId2Substrates[i]->mCompartmentName =
        metabolites[j]->getCompartment()->getName();
    }

  s = mId2Products.size();
  for (i = 0; i < s; i++)
    {
      Name = mId2Products[i]->mMetaboliteName;
      for (j = 0; j < z; j++)
        if (Name == metabolites[j]->getName())
          break;
      mId2Products[i]->mCompartmentName =
        metabolites[j]->getCompartment()->getName();
    }

  s = mId2Modifiers.size();
  for (i = 0; i < s; i++)
    {
      Name = mId2Modifiers[i]->mMetaboliteName;
      for (j = 0; j < z; j++)
        if (Name == metabolites[j]->getName())
          break;
      mId2Modifiers[i]->mCompartmentName =
        metabolites[j]->getCompartment()->getName();
    }
}

C_FLOAT64 CReaction::calculate()
{
  mFlux = *mScalingFactor * mFunction->calcValue(mCallParameters);
  mScaledFlux = *mScalingFactor2 * mFlux;
  return mFlux;
}

void CReaction::CId2Metab::setIdentifierName(const string & identifierName)
{
  mIdentifierName = identifierName;
}

const string & CReaction::CId2Metab::getIdentifierName() const
  {
    return mIdentifierName;
  }

void CReaction::CId2Metab::setMetaboliteName(const string & metaboliteName)
{
  mMetaboliteName = metaboliteName;
}

const string & CReaction::CId2Metab::getMetaboliteName() const
  {
    return mMetaboliteName;
  }

void CReaction::CId2Metab::setCompartmentName(const string & compartmentName)
{
  mCompartmentName = compartmentName;
}

const string & CReaction::CId2Metab::getCompartmentName() const
  {
    return mCompartmentName;
  }

CMetab * CReaction::CId2Metab::getMetabolite() const
  {
    return mpMetabolite;
  }

void CReaction::CId2Param::setIdentifierName(const string & identifierName)
{
  mIdentifierName = identifierName;
}

const string & CReaction::CId2Param::getIdentifierName() const
  {
    return mIdentifierName;
  }

void CReaction::CId2Param::setValue(const C_FLOAT64 & value)
{
  mValue = value;
}

const C_FLOAT64 & CReaction::CId2Param::getValue() const
  {
    return mValue;
  }

/**
 * Returns the address of mValue
 */
void* CReaction::CId2Param::getValueAddr()
{
  return &mValue;
}

/**
 * Returns the address of mFlux
 */
void* CReaction::getFluxAddr()
{
  return &mFlux;
}

/**
 * Returns the index of the parameter
 */
C_INT32 CReaction::findPara(string &Target)
{
  unsigned C_INT32 i;
  string name;

  for (i = 0; i < mId2Parameters.size(); i++)
    {
      name = mId2Parameters[i]->getIdentifierName();

      if (name == Target)
        return i;
    }

  return -1;
}

void CReaction::cleanupCallParameters()
{
  unsigned C_INT32 i, imax = mParameterDescription.size();

  for (i = 0; i < imax; i++)
    {
      if (mParameterDescription[i]->getType() >= CFunctionParameter::VINT16)
        if (mCallParameters[i])
          delete (vector < void * > *) mCallParameters[i];
      mCallParameters[i] = NULL;
    }

  mCallParameters.clear();
}

void CReaction::initCallParameters()
{
  cleanupCallParameters();
  mParameterDescription.cleanup();

  mParameterDescription = CFunctionParameters(mFunction->getParameters());

  unsigned C_INT32 i, imax = mParameterDescription.size();
  mCallParameters.resize(imax);

  for (i = 0; i < imax; i++)
    {
      mCallParameters[i] = NULL;

      if (mParameterDescription[i]->getType() < CFunctionParameter::VINT16)
        continue;

      switch (mParameterDescription[i]->getType())
        {
        case CFunctionParameter::VINT16:
          mCallParameters[i] = new vector < C_INT16 * >;
          break;

        case CFunctionParameter::VINT32:
          mCallParameters[i] = new vector < C_INT32 * >;
          break;

        case CFunctionParameter::VUINT16:
          mCallParameters[i] = new vector < unsigned C_INT16 * >;
          break;

        case CFunctionParameter::VUINT32:
          mCallParameters[i] = new vector < unsigned C_INT32 * >;
          break;

        case CFunctionParameter::VFLOAT32:
          mCallParameters[i] = new vector < C_FLOAT32 * >;
          break;

        case CFunctionParameter::VFLOAT64:
          mCallParameters[i] = new vector < C_FLOAT64 * >;
          break;

        default:
          fatalError();
          break;
        }
    }
}

void CReaction::setCallParameters()
{
  unsigned C_INT32 i, imax;
  unsigned C_INT32 Index;

  CFunctionParameter::DataType dataType;

  imax = mId2Substrates.size();

  for (i = 0; i < imax; i++)
    {
      Index = findParameter(mId2Substrates[i]->mIdentifierName, dataType);

      if (dataType < CFunctionParameter::VINT16)
        mCallParameters[Index] =
          & mId2Substrates[i]->mpMetabolite->getConcentration();
      else
        ((vector <const void *> *) mCallParameters[Index])->
        push_back(& mId2Substrates[i]->mpMetabolite->getConcentration());
    }

  imax = mId2Products.size();

  for (i = 0; i < imax; i++)
    {
      Index = findParameter(mId2Products[i]->mIdentifierName, dataType);

      if (dataType < CFunctionParameter::VINT16)
        mCallParameters[Index] =
          & mId2Products[i]->mpMetabolite->getConcentration();
      else
        ((vector < const void * > *) mCallParameters[Index])->
        push_back(& mId2Products[i]->mpMetabolite->getConcentration());
    }

  imax = mId2Modifiers.size();

  for (i = 0; i < imax; i++)
    {
      Index = findParameter(mId2Modifiers[i]->mIdentifierName, dataType);

      if (dataType < CFunctionParameter::VINT16)
        mCallParameters[Index] =
          & mId2Modifiers[i]->mpMetabolite->getConcentration();
      else
        ((vector < const void * > *) mCallParameters[Index])->
        push_back(& mId2Modifiers[i]->mpMetabolite->getConcentration());
    }

  imax = mId2Parameters.size();

  for (i = 0; i < imax; i++)
    {
      Index = findParameter(mId2Parameters[i]->mIdentifierName, dataType);

      if (dataType < CFunctionParameter::VINT16)
        mCallParameters[Index] = &mId2Parameters[i]->mValue;
      else
        ((vector < void * > *) mCallParameters[Index])->
        push_back(&mId2Parameters[i]->mValue);
    }
}

void CReaction::checkCallParameters()
{
  unsigned C_INT32 i, imax = mParameterDescription.size();
  unsigned C_INT32 j, jmax;
  vector < void * > * pVector;

  for (i = 0; i < imax; i++)
    {
      if (mCallParameters[i] == NULL)
        fatalError();

      if (mParameterDescription[i]->getType() < CFunctionParameter::VINT16)
        continue;

      pVector = (vector < void * > *) mCallParameters[i];

      jmax = pVector->size();

      for (j = 0; j < jmax; j++)
        if ((*pVector)[j] == NULL)
          fatalError();
    }
}

void CReaction::cleanupCallParameterNames()
{
  unsigned C_INT32 i, imax = mParameterDescription.size();

  for (i = 0; i < imax; i++)
    {
      if (mParameterDescription[i]->getType() >= CFunctionParameter::VINT16)
        if (mCallParameterNames[i])
          delete (vector < string * > *) mCallParameterNames[i];
      mCallParameterNames[i] = NULL;
    }

  mCallParameterNames.clear();
}

// this function requires that a compile() has already happened
void CReaction::initCallParameterNames()
{
  unsigned C_INT32 i, imax = mParameterDescription.size();

  mCallParameterNames.resize(imax);
  for (i = 0; i < imax; i++)
    {
      mCallParameterNames[i] = NULL;
      if (mParameterDescription[i]->getType() >= CFunctionParameter::VINT16)
        mCallParameterNames[i] = new vector < string * >;
    }
}

void CReaction::setCallParameterNames()
{
  unsigned C_INT32 i, imax;
  unsigned C_INT32 Index;
  CFunctionParameter::DataType dataType;

  imax = mId2Substrates.size();
  for (i = 0; i < imax; i++)
    {
      Index = findParameter(mId2Substrates[i]->mIdentifierName, dataType);
      if (dataType < CFunctionParameter::VINT16)
        mCallParameterNames[Index] =
          & mId2Substrates[i]->mMetaboliteName;
      else
        {
          ((vector <const string *> *) mCallParameterNames[Index])->
          push_back(& (mId2Substrates[i]->mMetaboliteName));
        }
    }

  imax = mId2Products.size();

  for (i = 0; i < imax; i++)
    {
      Index = findParameter(mId2Products[i]->mIdentifierName, dataType);
      if (dataType < CFunctionParameter::VINT16)
        mCallParameterNames[Index] =
          & mId2Products[i]->mMetaboliteName;
      else
        ((vector < const string * > *) mCallParameterNames[Index])->
        push_back(& mId2Products[i]->mMetaboliteName);
    }

  imax = mId2Modifiers.size();

  for (i = 0; i < imax; i++)
    {
      Index = findParameter(mId2Modifiers[i]->mIdentifierName, dataType);
      if (dataType < CFunctionParameter::VINT16)
        mCallParameterNames[Index] =
          & mId2Modifiers[i]->mMetaboliteName;
      else
        ((vector < const string * > *) mCallParameterNames[Index])->
        push_back(& mId2Modifiers[i]->mMetaboliteName);
    }

  imax = mId2Parameters.size();

  for (i = 0; i < imax; i++)
    {
      Index = findParameter(mId2Parameters[i]->mIdentifierName, dataType);
      if (dataType < CFunctionParameter::VINT16)
        mCallParameterNames[Index] = &mId2Parameters[i]->mIdentifierName;
      else
        ((vector < string * > *) mCallParameterNames[Index])->
        push_back(&mId2Parameters[i]->mIdentifierName);
    }
}

void CReaction::checkCallParameterNames()
{
  unsigned C_INT32 i, imax = mParameterDescription.size();
  unsigned C_INT32 j, jmax;
  vector < void * > * pVector;

  for (i = 0; i < imax; i++)
    {
      if (mCallParameterNames[i] == NULL)
        fatalError();

      if (mParameterDescription[i]->getType() < CFunctionParameter::VINT16)
        continue;

      pVector = (vector < void * > *) mCallParameterNames[i];

      jmax = pVector->size();

      for (j = 0; j < jmax; j++)
        if ((*pVector)[j] == NULL)
          fatalError();
    }
}

unsigned C_INT32 CReaction::findParameter(const string & name,
    CFunctionParameter::DataType & dataType)
{
  string VectorName = name.substr(0, name.find_last_of('_'));
  string Name;
  unsigned C_INT32 i, imax = mParameterDescription.size();

  for (i = 0; i < imax; i++)
    {
      Name = mParameterDescription[i]->getName();

      if (Name == name || Name == VectorName)
        {
          dataType = mParameterDescription[i]->getType();
          return i;
        }
    }

  fatalError()
  return 0;
}

unsigned C_INT32 CReaction::usageRangeSize(const string & usage)
{
  CUsageRange * pUsageRange = NULL;
  C_INT32 Size = 0;

  try
    {
      pUsageRange = mParameterDescription.getUsageRanges()[usage];
    }

  catch (CCopasiException Exception)
    {
      if ((MCCopasiVector + 1) != Exception.getMessage().getNumber())
        throw Exception;

      pUsageRange = NULL;
    }

  if (pUsageRange)
    Size = max(pUsageRange->getLow(), pUsageRange->getHigh());

  return Size;
}

// Added by cvg
CMetab * CReaction::findSubstrate(string ident_name)
{
  for (unsigned C_INT32 i = 0; i < mId2Substrates.size(); i++)
    {
      if (mId2Substrates[i]->mIdentifierName == ident_name)
        {
          // found it
          return mId2Substrates[i]->mpMetabolite;
        }
    }
  // If we get here, we found nothing
  return NULL;
}

CMetab * CReaction::findModifier(string ident_name)
{
  for (unsigned C_INT32 i = 0; i < mId2Modifiers.size(); i++)
    {
      if (mId2Modifiers[i]->mIdentifierName == ident_name)
        {
          // found it
          return mId2Modifiers[i]->mpMetabolite;
        }
    }

  // If we get here, we found nutting
  return 0;
}

unsigned C_INT32 CReaction::getCompartmentNumber()
{
  const CCopasiVector < CChemEqElement > & Balances
  = mChemEq.getBalances();
  unsigned C_INT32 i, imax = Balances.size();
  unsigned C_INT32 j, jmax;
  unsigned C_INT32 Number;
  vector <CCompartment *> Compartments;

  for (i = 0, Number = 0; i < imax; i++)
    {
      for (j = 0, jmax = Compartments.size(); j < jmax; j++)
        if (Compartments[j] == Balances[i]->getMetabolite().getCompartment())
          break;

      if (j == jmax)
        {
          Number ++;
          Compartments.push_back(Balances[i]->getMetabolite().getCompartment());
        }
    }

  return Number;
}

void CReaction::setScalingFactor()
{
  if (1 == getCompartmentNumber())
    {
      mScalingFactor = & mChemEq.getBalances()[0]->getMetabolite().getCompartment()->getVolume();
    }
  else
    {
      mScalingFactor = &mDefaultScalingFactor;
    }

  mScalingFactor2 =
    & mChemEq.getBalances()[0]->getMetabolite().getModel()->getQuantity2NumberFactor();
}

void CReaction::setReactantsFromChemEq()
{
  C_INT32 i, nsub, nprod;
  unsigned C_INT32 pos;
  CCopasiVector < CChemEqElement > sub;
  CCopasiVector < CChemEqElement > prod;
  CFunctionParameter::DataType Type = CFunctionParameter::FLOAT64;

  if (mChemEq.initialized())
    {
      sub = mChemEq.getSubstrates();
      nsub = sub.size();
      prod = mChemEq.getProducts();
      nprod = prod.size();
      mId2Substrates.resize(nsub);
      for (i = 0, pos = 0; i < nsub; i++)
        {
          mId2Substrates[i]->mMetaboliteName = sub[i]->getMetaboliteName();
          mId2Substrates[i]->mCompartmentName = sub[i]->getMetabolite().getCompartment()->getName();
          if (Type < CFunctionParameter::VINT16)
            Type = mParameterDescription.getParameterByUsage("SUBSTRATE", pos).getType();
          mId2Substrates[i]->mIdentifierName = mParameterDescription[pos - 1]->getName();
          if (Type >= CFunctionParameter::VINT16)
            mId2Substrates[i]->mIdentifierName += StringPrint("_%ld", i);
        }
      mId2Products.resize(nprod);
      for (i = 0, pos = 0; i < nprod; i++)
        {
          mId2Products[i]->mMetaboliteName = prod[i]->getMetaboliteName();
          mId2Products[i]->mCompartmentName = prod[i]->getMetabolite().getCompartment()->getName();
          if (Type < CFunctionParameter::VINT16)
            Type = mParameterDescription.getParameterByUsage("PRODUCT", pos).getType();
          mId2Products[i]->mIdentifierName = mParameterDescription[pos - 1]->getName();
          if (Type >= CFunctionParameter::VINT16)
            mId2Products[i]->mIdentifierName += StringPrint("_%ld", i);
        }
    }
}

void CReaction::compileChemEq(CCopasiVectorN < CCompartment > & compartments)
{
  mChemEq.compile(compartments);
}
