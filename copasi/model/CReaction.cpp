// CReaction
//
// Derived from Gepasi's cstep.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Stefan Hoops

#define  COPASI_TRACE_CONSTRUCTION

#include <algorithm>
#include <stdio.h>

#include "copasi.h"
#include "utilities/CGlobals.h"
#include "CReaction.h"
#include "CCompartment.h"
#include "CModel.h"
#include "utilities/readwrite.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/CCopasiException.h"
#include "utilities/utility.h"
#include "utilities/CMethodParameter.h"
#include "function/CFunctionDB.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"

C_FLOAT64 CReaction::mDefaultScalingFactor = 1.0;

CReaction::CReaction(const std::string & name,
                     const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Reaction"),
    mKey(CKeyFactory::add("Reaction", this)),
    mName(mObjectName),
    mChemEq("Chemical Equation", this),
    mpFunction(NULL),
    mFlux(0),
    mScaledFlux(0),
    mScalingFactor(&mDefaultScalingFactor),
    mScalingFactor2(&mDefaultScalingFactor),
    mpFunctionCompartment(NULL),
    //mCompartmentNumber(1),
    mParameters("Parameters", this)
{
  CONSTRUCTOR_TRACE;
  initObjects();
}

CReaction::CReaction(const CReaction & src,
                     const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(CKeyFactory::add("Reaction", this)),
    mName(mObjectName),
    mChemEq(src.mChemEq, this),
    mpFunction(src.mpFunction),
    mFlux(src.mFlux),
    mScaledFlux(src.mScaledFlux),
    mScalingFactor(src.mScalingFactor),
    mScalingFactor2(src.mScalingFactor2),
    mpFunctionCompartment(src.mpFunctionCompartment),
    mMap(src.mMap),
    mMetabNameMap(src.mMetabNameMap),
    mParameters(src.mParameters, this)
{
  CONSTRUCTOR_TRACE;
  initObjects();
  if (mpFunction)
    {
      compileParameters();
    }
}

CReaction::~CReaction()
{
  CKeyFactory::remove(mKey);
  cleanup();
  DESTRUCTOR_TRACE;
}

void CReaction::cleanup()
{
  // TODO: mMap.cleanup();

  //mParameterDescription.cleanup();
}

C_INT32 CReaction::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;

  std::string KinType;

  if ((Fail = configbuffer.getVariable("Step", "string", &mName,
                                       CReadConfig::SEARCH)))
    return Fail;

  std::string ChemEq;

  if ((Fail = configbuffer.getVariable("Equation", "string", &ChemEq)))
    return Fail;

  setChemEq(ChemEq);

  if ((Fail = configbuffer.getVariable("KineticType", "string", &KinType)))
    return Fail;

  setFunction(KinType);

  if (mpFunction == NULL)
    return Fail = 1;

  bool revers;
  if ((Fail = configbuffer.getVariable("Reversible", "bool", &revers,
                                       CReadConfig::SEARCH)))
    return Fail;
  mChemEq.setReversibility(revers); // TODO: this should be consistent with the ChemEq string

  if (configbuffer.getVersion() < "4")
    Fail = loadOld(configbuffer);
  //else
  //Fail = loadNew(configbuffer);

  return Fail;
}

C_INT32 CReaction::save(CWriteConfig & C_UNUSED(configbuffer))
{return 0;}

C_INT32 CReaction::saveOld(CWriteConfig & configbuffer,
                           const CCopasiVectorN< CMetab > &metabolites)
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
  std::string KinType = mpFunction->getName();
  if ((Fail = configbuffer.setVariable("KineticType", "string", &KinType)))
    return Fail;
  if ((Fail = configbuffer.setVariable("Flux", "C_FLOAT64", &mFlux)))
    return Fail;

  bool revers = mChemEq.getReversibility();
  if ((Fail = configbuffer.setVariable("Reversible", "bool", &revers)))
    return Fail;
  Size = mChemEq.getSubstrates().size();
  if ((Fail = configbuffer.setVariable("Substrates", "C_INT32", &Size)))
    return Fail;
  Size = mChemEq.getProducts().size();
  if ((Fail = configbuffer.setVariable("Products", "C_INT32", &Size)))
    return Fail;
  Size = mChemEq.getModifiers().size();
  if ((Fail = configbuffer.setVariable("Modifiers", "C_INT32", &Size)))
    return Fail;
  Size = mParameters.size();
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
        return - 1;
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
        return - 1;
      sprintf(strtmp, "Prod%ld", i);
      if ((Fail = configbuffer.setVariable(strtmp, "C_INT32", (void *) & c)))
        return Fail;
    }

  reactants = mChemEq.getModifiers();
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
        return - 1;
      sprintf(strtmp, "Modf%ld", i);
      if ((Fail = configbuffer.setVariable(strtmp, "C_INT32", (void *) & c)))
        return Fail;
    }
  Size = mParameters.size();
  for (i = 0; i < Size; i++)
    {
      sprintf(strtmp, "Param%ld", i);
      if ((Fail = configbuffer.setVariable(strtmp, "C_FLOAT64", (void *) & mParameters[i]->getValue())))
        return Fail;
    }
  return 0;
}

void CReaction::saveSBML(std::ofstream &fout, C_INT32 r)
{
  std::string tmpstr, tmpstr2;
  unsigned C_INT32 i;
  CCopasiVector < CChemEqElement > rr;

  FixSName(mName, tmpstr);
  fout << "\t\t\t<reaction name=\"" << tmpstr << "\"";
  fout << " reversible=\"";
  if (mChemEq.getReversibility())
    fout << "true";
  else
    fout << "false";
  fout << "\">" << std::endl;
  fout << "\t\t\t\t<listOfReactants>" << std::endl;
  // check if we need to reference the dummy metabolite
  rr = mChemEq.getSubstrates();
  if (rr.size() == 0)
    fout << "\t\t\t\t\t<specieReference specie=\"_void_\" stoichiometry=\"1\"/>" << std::endl;
  else
    {
      // write them out
      for (i = 0; i < rr.size(); i++)
        {
          tmpstr2 = rr[i]->getMetaboliteName();
          FixSName(tmpstr2, tmpstr);
          fout << "\t\t\t\t\t<specieReference specie=\"" << tmpstr << "\"";
          fout << " stoichiometry=\"" << rr[i]->getMultiplicity() << "\"/>" << std::endl;
        }
    }
  fout << "\t\t\t\t</listOfReactants>" << std::endl;
  fout << "\t\t\t\t<listOfProducts>" << std::endl;
  // check if we need to reference the dummy metabolite
  rr = mChemEq.getProducts();
  if (rr.size() == 0)
    fout << "\t\t\t\t\t<specieReference specie=\"_void_\" stoichiometry=\"1\"/>" << std::endl;
  else
    {
      // write them out
      for (i = 0; i < rr.size(); i++)
        {
          tmpstr2 = rr[i]->getMetaboliteName();
          FixSName(tmpstr2, tmpstr);
          fout << "\t\t\t\t\t<specieReference specie=\"" << tmpstr << "\"";
          fout << " stoichiometry=\"" << rr[i]->getMultiplicity() << "\"/>" << std::endl;
        }
    }
  fout << "\t\t\t\t</listOfProducts>" << std::endl;

  fout << "\t\t\t\t<kineticLaw formula=\"";
  // kinetic function string
  tmpstr2 = StringPrint("_%ld", r);
  fout << mpFunction->getSBMLString(mMetabNameMap, tmpstr2);
  fout << "\">" << std::endl;
  fout << "\t\t\t\t\t<listOfParameters>" << std::endl;
  for (i = 0; i < mParameters.size(); i++)
    {
      FixSName(mParameters[i]->getName(), tmpstr);
      fout << "\t\t\t\t\t\t<parameter name=\"" + tmpstr;
      fout << "_" << r << "\" value=\"" << mParameters[i]->getValue() << "\"/>" << std::endl;
    }
  fout << "\t\t\t\t\t</listOfParameters>" << std::endl;
  fout << "\t\t\t\t</kineticLaw>" << std::endl;
  fout << "\t\t\t</reaction>" << std::endl;
}

//C_INT32 CReaction::getSubstrateNumber() const
//  {return mChemEq.getSubstrates().size();}

//C_INT32 CReaction::getProductNumber() const
//  {return mChemEq.getProducts().size();}

std::string CReaction::getKey() const
  {return mKey;}

const std::string & CReaction::getName() const
  {return mName;}

const CChemEq & CReaction::getChemEq() const
  {return mChemEq;}

const CFunction & CReaction::getFunction() const
  {return *mpFunction;}

const C_FLOAT64 & CReaction::getFlux() const
  {return mFlux;}

const C_FLOAT64 & CReaction::getScaledFlux() const
  {return mScaledFlux;}

bool CReaction::isReversible() const
  {return mChemEq.getReversibility();}

bool CReaction::setName(const std::string & name)
{
  CCopasiContainer * pParent = getObjectParent();
  if (pParent)
    if (pParent->isNameVector())
      if (pParent->getIndex(name) != C_INVALID_INDEX)
        return false;

  mName = name;
  return true;
}

void CReaction::setChemEq(const std::string & chemEq)
{/*mReversible = */mChemEq.setChemicalEquation(chemEq);}

void CReaction::setReversible(bool reversible)
{mChemEq.setReversibility(reversible);}

void CReaction::setFunction(const std::string & functionName)
{
  mpFunction = Copasi->pFunctionDB->findLoadFunction(functionName);
  if (!mpFunction)
    CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 1, functionName.c_str());

  mMap.initializeFromFunctionParameters(mpFunction->getParameters());
  initializeMetaboliteNameMap(); //needs to be called before initializeParamters();
  initializeParameters();
}

// TODO: check if function is set and map initialized in the following methods
// also check if compiled. If compiled try to keep consistent.

void CReaction::setParameterValue(const std::string & parameterName, C_FLOAT64 value)
{
  if (!mpFunction) fatalError();
  mParameters[parameterName]->setValue(value);
}

const C_FLOAT64 & CReaction::getParameterValue(const std::string & parameterName) const
  {
    if (!mpFunction) fatalError();
    return mParameters[parameterName]->getValue();
  }

const CCopasiVectorN <CParameter> & CReaction::getParameters() const
  {
    return mParameters;
  }

void CReaction::setParameterMapping(const std::string & parameterName, const CMetab & metab)
{
  if (!mpFunction) fatalError();
  std::vector<CCopasiObject*>::const_iterator it, ende; //TODO: these lines should rather be CCopasiContainer::getObjectByName()
  it = metab.getObjects().begin();
  ende = metab.getObjects().end();
for (; it != ende; ++it) {if ((*it)->getName() == "Concentration") break;}
  if (it == ende) fatalError(); // concentration reference not found

  mMap.setCallParameter(parameterName, *it);
}

void CReaction::setParameterMapping(const std::string & parameterName, const std::string & metabName)
{
  if (!mpFunction) fatalError();
  CFunctionParameter::DataType type;
  unsigned C_INT32 index;
  index = mMap.findParameterByName(parameterName, type);
  if (type != CFunctionParameter::FLOAT64) fatalError(); //wrong data type
  mChemEq.findElementByName(metabName); //just to check if available
  // TODO : check if parameter role fits. At the moment do not allow PARAMETER.
  mMetabNameMap[index][0] = metabName;
}

void CReaction::setParameterMapping(C_INT32 index, const std::string & metabName)
{
  if (!mpFunction) fatalError();
  if (getFunctionParameters()[index]->getType() != CFunctionParameter::FLOAT64) fatalError();
  mChemEq.findElementByName(metabName); //just to check if available
  // TODO : check if parameter role fits. At the moment do not allow PARAMETER.
  mMetabNameMap[index][0] = metabName;
}

void CReaction::clearParameterMapping(const std::string & parameterName)
{
  if (!mpFunction) fatalError();
  CFunctionParameter::DataType type;
  unsigned C_INT32 index;
  index = mMap.findParameterByName(parameterName, type);
  if (type != CFunctionParameter::VFLOAT64) fatalError(); //wrong data type
  mMetabNameMap[index].clear();
  //mMap.clearCallParameter(parameterName);
}

void CReaction::clearParameterMapping(C_INT32 index)
{
  if (!mpFunction) fatalError();
  if (getFunctionParameters()[index]->getType() != CFunctionParameter::VFLOAT64) fatalError();
  mMetabNameMap[index].clear();
  //mMap.clearCallParameter(parameterName);
}

void CReaction::addParameterMapping(const std::string & parameterName, const CMetab & metab)
{
  if (!mpFunction) fatalError();
  std::vector<CCopasiObject*>::const_iterator it, ende;
  it = metab.getObjects().begin();
  ende = metab.getObjects().end();
for (; it != ende; ++it) {if ((*it)->getName() == "Concentration") break;}
  if (it == ende) fatalError(); // concentration reference not found

  mMap.addCallParameter(parameterName, *it);
}

void CReaction::addParameterMapping(const std::string & parameterName, const std::string & metabName)
{
  if (!mpFunction) fatalError();
  CFunctionParameter::DataType type;
  unsigned C_INT32 index;
  index = mMap.findParameterByName(parameterName, type);
  if (type != CFunctionParameter::VFLOAT64) fatalError(); //wrong data type
  mChemEq.findElementByName(metabName); //just to check if available
  // TODO : check if parameter role fits. At the moment do not allow PARAMETER.
  mMetabNameMap[index].push_back(metabName);
  //addParameterMapping(parameterName, mChemEq.findElementByName(metabName).getMetabolite());
}

void CReaction::addParameterMapping(C_INT32 index, const std::string & metabName)
{
  if (!mpFunction) fatalError();
  if (getFunctionParameters()[index]->getType() != CFunctionParameter::VFLOAT64) fatalError(); //wrong data type
  mChemEq.findElementByName(metabName); //just to check if available
  // TODO : check if parameter role fits. At the moment do not allow PARAMETER.
  mMetabNameMap[index].push_back(metabName);
}

const std::vector<std::string> & CReaction::getParameterMappingName(C_INT32 index) const  //TODO reference&
  {
    return mMetabNameMap[index];
  }

std::vector<const CMetab *> CReaction::getParameterMappingMetab(C_INT32 index) const
  {
    if (!mpFunction) fatalError();
    if (getFunctionParameters()[index]->getUsage() == "PARAMETER") fatalError();
    std::vector<const CMetab *> metablist;
    unsigned C_INT32 i, imax = mMetabNameMap[index].size();

    for (i = 0; i < imax; ++i) metablist.push_back(&mChemEq.findElementByName(mMetabNameMap[index][i]).getMetabolite());

    return metablist;
  }

//***********************************************************************************************

void CReaction::compileParameters()
{
  if (!mpFunction) fatalError();
  unsigned C_INT32 i;
  unsigned C_INT32 imax = mMap.getFunctionParameters().getNumberOfParametersByUsage("PARAMETER");
  unsigned C_INT32 pos;
  std::string name;

  for (i = 0, pos = 0; i < imax; ++i)
    {
      name = mMap.getFunctionParameters().getParameterByUsage("PARAMETER", pos).getName();
      mMap.setCallParameter(name, mParameters[name]);
    }
}

void CReaction::initializeParameters()
{
  if (!mpFunction) fatalError();
  unsigned C_INT32 i;
  unsigned C_INT32 imax = mMap.getFunctionParameters().getNumberOfParametersByUsage("PARAMETER");
  unsigned C_INT32 pos;
  std::string name;
  CParameter param;

  mParameters.cleanup();

  param.setType(CParameter::DOUBLE);
  param.setValue(1.0);

  for (i = 0, pos = 0; i < imax; ++i)
    {
      name = mMap.getFunctionParameters().getParameterByUsage("PARAMETER", pos).getName();
      param.setName(name);
      mParameters.add(param);
      mMetabNameMap[pos - 1][0] = name;
    }

  compileParameters();
}

void CReaction::initializeMetaboliteNameMap()
{
  if (!mpFunction) fatalError();
  unsigned C_INT32 i;
  unsigned C_INT32 imax = mMap.getFunctionParameters().size();

  mMetabNameMap.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      if (mMap.getFunctionParameters()[i]->getType() >= CFunctionParameter::VINT32)
        mMetabNameMap[i].resize(0);
      else
        mMetabNameMap[i].resize(1);
    }
}

const CFunctionParameters & CReaction::getFunctionParameters() const
  {
    if (!mpFunction) fatalError();
    return mMap.getFunctionParameters();
  }

void CReaction::compile(const CCopasiVectorNS < CCompartment > & compartments)
{
  mChemEq.compile(compartments);

  if (mpFunction)
    {
      unsigned C_INT32 i, j, jmax;
      unsigned C_INT32 imax = mMap.getFunctionParameters().size();
      std::string paramName;

      for (i = 0; i < imax; ++i)
        {
          if (mMap.getFunctionParameters()[i]->getUsage() == "PARAMETER") continue;
          if (mMap.getFunctionParameters()[i]->getType() >= CFunctionParameter::VINT32)
            {
              paramName = getFunctionParameters()[i]->getName();
              mMap.clearCallParameter(paramName);
              jmax = mMetabNameMap[i].size();
              for (j = 0; j < jmax; ++j)
                addParameterMapping(paramName,
                                    mChemEq.findElementByName(mMetabNameMap[i][j]).getMetabolite());
            }
          else
            setParameterMapping(getFunctionParameters()[i]->getName(),
                                mChemEq.findElementByName(mMetabNameMap[i][0]).getMetabolite());
        }
    }

  setScalingFactor();
}

C_INT32 CReaction::loadOld(CReadConfig & configbuffer)
{
  std::string name;

  C_INT32 Fail = 0;
  unsigned C_INT32 SubstrateSize, ProductSize, ModifierSize, ParameterSize;
  unsigned C_INT32 i, imax, pos;
  C_INT32 index;
  std::string parName, metabName;

  CFunctionParameter::DataType Type;

  configbuffer.getVariable("Substrates", "C_INT32", &SubstrateSize);
  configbuffer.getVariable("Products", "C_INT32", &ProductSize);
  configbuffer.getVariable("Modifiers", "C_INT32", &ModifierSize);
  configbuffer.getVariable("Constants", "C_INT32", &ParameterSize);

  // Construct substrates mapping
  // this works only because of a strange signed->unsigned cast in usageRangeSize()!
  imax = std::min(SubstrateSize, usageRangeSize("SUBSTRATE")); //some checks?
  for (i = 0, pos = 0, Type = CFunctionParameter::INT32; i < imax; i++)
    {
      name = StringPrint("Subs%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);

      metabName = (*Copasi->pOldMetabolites)[index]->getName();

      if (Type < CFunctionParameter::VINT32)
        {
          Type = mMap.getFunctionParameters().getParameterByUsage("SUBSTRATE", pos).getType();
          parName = mMap.getFunctionParameters()[pos - 1]->getName();
          if (Type >= CFunctionParameter::VINT32)
            clearParameterMapping(parName);
        }

      if (Type >= CFunctionParameter::VINT32)
        addParameterMapping(parName, metabName);
      else
        setParameterMapping(parName, metabName);
    }

  for (i = imax; i < SubstrateSize; i++)
    {
      name = StringPrint("Subs%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);
    }

  // Construct Products mapping
  imax = std::min(ProductSize, usageRangeSize("PRODUCT"));

  for (i = 0, pos = 0, Type = CFunctionParameter::INT32; i < imax; i++)
    {
      name = StringPrint("Prod%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);

      metabName = (*Copasi->pOldMetabolites)[index]->getName();

      if (Type < CFunctionParameter::VINT32)
        {
          Type = mMap.getFunctionParameters().getParameterByUsage("PRODUCT", pos).getType();
          parName = mMap.getFunctionParameters()[pos - 1]->getName();
          if (Type >= CFunctionParameter::VINT32)
            clearParameterMapping(parName);
        }

      if (Type >= CFunctionParameter::VINT32)
        addParameterMapping(parName, metabName);
      else
        setParameterMapping(parName, metabName);
    }

  for (i = imax; i < ProductSize; i++)
    {
      name = StringPrint("Prod%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);
    }

  // Construct modifiers mapping
  imax = std::min(ModifierSize, usageRangeSize("MODIFIER"));

  for (i = 0, pos = 0, Type = CFunctionParameter::INT32; i < imax; i++)
    {
      name = StringPrint("Modf%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);

      metabName = (*Copasi->pOldMetabolites)[index]->getName();

      if (Type < CFunctionParameter::VINT32)
        {
          Type = mMap.getFunctionParameters().getParameterByUsage("MODIFIER", pos).getType();
          parName = mMap.getFunctionParameters()[pos - 1]->getName();
          if (Type >= CFunctionParameter::VINT32)
            clearParameterMapping(parName);
        }

      if (Type >= CFunctionParameter::VINT32)
        addParameterMapping(parName, metabName);
      else
        setParameterMapping(parName, metabName);

      // in the old files the chemical equation does not contain
      // information about modifiers. This has to be extracted from here.
      mChemEq.addMetaboliteByName(metabName, 1, CChemEq::MODIFIER);
    }

  for (i = imax; i < ModifierSize; i++)
    {
      name = StringPrint("Modf%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);
    }

  // Construct parameters
  imax = ParameterSize;
  C_FLOAT64 value;
  for (i = 0, pos = 0; i < imax; i++)
    {
      name = StringPrint("Param%d", i);
      configbuffer.getVariable(name, "C_FLOAT64", &value);

      Type = mMap.getFunctionParameters().getParameterByUsage("PARAMETER", pos).getType();
      if (Type != CFunctionParameter::FLOAT64) {Fail = 1; return Fail;}

      setParameterValue(mMap.getFunctionParameters()[pos - 1]->getName(), value);
    }

  for (i = imax; i < ParameterSize; i++)
    {
      name = StringPrint("Param%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);
    }

  return Fail;
}

C_FLOAT64 CReaction::calculate()
{
  mFlux = *mScalingFactor * mpFunction->calcValue(mMap.getPointers());
  mScaledFlux = *mScalingFactor2 * mFlux;
  return mFlux;
}

C_FLOAT64 CReaction::calculatePartialDerivative(C_FLOAT64 & xi,
    const C_FLOAT64 & derivationFactor,
    const C_FLOAT64 & resolution)
{
  if (mpFunction->dependsOn(&xi, mMap.getPointers()))
    {
      C_FLOAT64 store = xi;
      C_FLOAT64 f1, f2;
      C_FLOAT64 tmp =
        (store < resolution) ? resolution * (1.0 + derivationFactor) : store;

      xi = tmp * (1.0 + derivationFactor);
      f1 = calculate();

      xi = tmp * (1.0 - derivationFactor);
      f2 = calculate();

      xi = store;

      return *mScalingFactor * (f1 - f2) / (2.0 * tmp * derivationFactor);
    }
  else
    return 0.0;
}

unsigned C_INT32 CReaction::usageRangeSize(const std::string & usage) const
  {
    if (!mpFunction) fatalError();
    const CUsageRange * pUsageRange = NULL;
    C_INT32 Size = 0;

    try
      {
        pUsageRange = mMap.getFunctionParameters().getUsageRanges()[usage];
      }

    catch (CCopasiException Exception)
      {
        if ((MCCopasiVector + 1) != Exception.getMessage().getNumber())
          throw Exception;

        pUsageRange = NULL;
      }

    if (pUsageRange)
      Size = std::max(pUsageRange->getLow(), pUsageRange->getHigh());

    return Size;
    // if I understand correctly this works only because infinity=-1 becomes a very big number when
    // converted to unsigned int
  }

unsigned C_INT32 CReaction::getCompartmentNumber() const
{return mChemEq.getCompartmentNumber();}

void CReaction::setScalingFactor()
{
  if (1 == getCompartmentNumber())
    mScalingFactor = & mChemEq.getBalances()[0]->getMetabolite().getCompartment()->getVolume();
  else
    mScalingFactor = &mDefaultScalingFactor;

#ifdef XXXX
  if (mpFunctionCompartment)
    {
      // should propably check if the compartment appears in the chemical equation
      mScalingFactor = & mpFunctionCompartment->getVolume();
    }
  else
    {
      try
      {mScalingFactor = & mChemEq.CheckAndGetFunctionCompartment()->getVolume();}
      catch (CCopasiException Exc)
        {
          unsigned C_INT32 nr = Exc.getMessage().getNumber();
          if ((MCChemEq + 2 == nr) || (MCChemEq + 3 == nr))
            CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 2, getName().c_str());
          if (MCChemEq + 1 == nr)
            CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 3, getName().c_str());
          throw;
        }
    }
#endif // XXXX

  CModel * pModel = (CModel *) getObjectAncestor("Model");
  if (pModel)
    mScalingFactor2 = & pModel->getQuantity2NumberFactor();
  else
    mScalingFactor2 = & mDefaultScalingFactor;
}

void CReaction::setCompartment(const CCompartment* comp)
{mpFunctionCompartment = comp;}

const CCompartment* CReaction::getCompartment() const
  {return mpFunctionCompartment;}

const CCallParameterPointers & CReaction::getCallParameterObjects() const
  {return mMap.getObjects();}

void CReaction::initObjects()
{
  addObjectReference("Name", mName);
  addObjectReference("Flux", mFlux);
  addObjectReference("ScaledFlux", mScaledFlux);
  //add(&mParameters);
  //add(&mMap);
}
