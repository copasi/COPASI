/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CReaction.cpp,v $
   $Revision: 1.92 $
   $Name:  $
   $Author: lixu1 $ 
   $Date: 2003/10/30 20:40:12 $
   End CVS Header */

// CReaction
//
// Derived from Gepasi's cstep.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Stefan Hoops

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"

#include <algorithm>
#include <stdio.h>

#include "utilities/CGlobals.h"
#include "CReaction.h"
#include "CCompartment.h"
#include "CModel.h"
#include "utilities/readwrite.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/CCopasiException.h"
#include "utilities/utility.h"
#include "function/CFunctionDB.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "CMetabNameInterface.h"
#include "CChemEqInterface.h" //only for load()

C_FLOAT64 CReaction::mDefaultScalingFactor = 1.0;

CReaction::CReaction(const std::string & name,
                     const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Reaction"),
    mKey(CKeyFactory::add("Reaction", this)),
    mChemEq("Chemical Equation", this),
    mpFunction(NULL),
    mFlux(0),
    mScaledFlux(0),
    mScalingFactor(&mDefaultScalingFactor),
    mScalingFactor2(&mDefaultScalingFactor),
    mpFunctionCompartment(NULL),
    //mCompartmentNumber(1),
    mMetabKeyMap(),
    mParameters("Parameters", this)
{
  CONSTRUCTOR_TRACE;
  initObjects();
}

CReaction::CReaction(const CReaction & src,
                     const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(CKeyFactory::add("Reaction", this)),
    mChemEq(src.mChemEq, this),
    mpFunction(src.mpFunction),
    mFlux(src.mFlux),
    mScaledFlux(src.mScaledFlux),
    mScalingFactor(src.mScalingFactor),
    mScalingFactor2(src.mScalingFactor2),
    mpFunctionCompartment(src.mpFunctionCompartment),
    mMap(src.mMap),
    mMetabKeyMap(src.mMetabKeyMap),
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

  std::string tmp;

  if ((Fail = configbuffer.getVariable("Step", "string", &tmp,
                                       CReadConfig::SEARCH)))
    return Fail;
  setObjectName(tmp);

  std::string ChemEq;

  if ((Fail = configbuffer.getVariable("Equation", "string", &ChemEq)))
    return Fail;

  CModel * pModel = (CModel*) getObjectAncestor("Model");
  CChemEqInterface::setChemEqFromString(pModel, *this, ChemEq);

  if ((Fail = configbuffer.getVariable("KineticType", "string", &tmp)))
    return Fail;

  setFunction(tmp);

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
                           const CCopasiVector< CMetab > &metabolites)
{
  std::string tmp;
  C_FLOAT64 Dbl;

  C_INT32 Fail = 0;
  C_INT32 Size = 0;
  C_INT32 i = 0, j = 0, s = 0, c = -1;
  C_INT32 idx, multp;
  char strtmp[32];
  CCopasiVector < CChemEqElement > reactants;
  s = metabolites.size();
  tmp = getObjectName();
  if ((Fail = configbuffer.setVariable("Step", "string", &tmp)))
    return Fail;
  tmp = "TODO";  // mChemEq.getChemicalEquation();
  // CChemEqInterface is not guaranteed to write a chemical equation that gepasi will understand

  tmp = tmp.substr(0, tmp.find(';'));
  if ((Fail = configbuffer.setVariable("Equation", "string", &tmp)))
    return Fail;
  std::string KinType = mpFunction->getName();
  if ((Fail = configbuffer.setVariable("KineticType", "string", &KinType)))
    return Fail;
  if ((Fail = configbuffer.setVariable("Flux", "C_FLOAT64", &mFlux)))
    return Fail;

  bool revers = mChemEq.getReversibility();
  if ((Fail = configbuffer.setVariable("Reversible", "bool", &revers)))
    return Fail;
  Size = getSubstrateMolecularity();
  if ((Fail = configbuffer.setVariable("Substrates", "C_INT32", &Size)))
    return Fail;
  Size = getProductMolecularity();
  if ((Fail = configbuffer.setVariable("Products", "C_INT32", &Size)))
    return Fail;
  Size = getModifierMolecularity();
  if ((Fail = configbuffer.setVariable("Modifiers", "C_INT32", &Size)))
    return Fail;
  Size = mParameters.size();
  if ((Fail = configbuffer.setVariable("Constants", "C_INT32", &Size)))
    return Fail;
  reactants = mChemEq.getSubstrates();
  Size = reactants.size();
  for (i = 0, idx = 0; i < Size; i++)
    {
      for (j = 0, c = -1; j < s; j++)
        if (reactants[i]->getMetabolite().getName() == metabolites[j]->getName())
          {
            c = j;
            multp = (C_INT32) reactants[i]->getMultiplicity();
            break;
          }
      if (c == -1)
        return - 1;
      for (j = 0; j < multp; j++)
        {
          sprintf(strtmp, "Subs%ld", idx++);
          if ((Fail = configbuffer.setVariable(strtmp, "C_INT32", (void *) & c)))
            return Fail;
        }
    }
  reactants = mChemEq.getProducts();
  Size = reactants.size();
  for (i = 0, idx = 0; i < Size; i++)
    {
      for (j = 0, c = -1; j < s; j++)
        if (reactants[i]->getMetabolite().getName() == metabolites[j]->getName())
          {
            c = j;
            multp = (C_INT32) reactants[i]->getMultiplicity();
            break;
          }
      if (c == -1)
        return - 1;
      for (j = 0; j < multp; j++)
        {
          sprintf(strtmp, "Prod%ld", idx++);
          if ((Fail = configbuffer.setVariable(strtmp, "C_INT32", (void *) & c)))
            return Fail;
        }
    }
  reactants = mChemEq.getModifiers();
  Size = reactants.size();
  for (i = 0, idx = 0; i < Size; i++)
    {
      for (j = 0, c = -1; j < s; j++)
        if (reactants[i]->getMetabolite().getName() == metabolites[j]->getName())
          {
            c = j;
            multp = (C_INT32) reactants[i]->getMultiplicity();
            break;
          }
      if (c == -1)
        return - 1;
      for (j = 0; j < multp; j++)
        {
          sprintf(strtmp, "Modf%ld", idx++);
          if ((Fail = configbuffer.setVariable(strtmp, "C_INT32", (void *) & c)))
            return Fail;
        }
    }
  Size = mParameters.size();
  for (i = 0; i < Size; i++)
    {
      sprintf(strtmp, "Param%ld", i);
      Dbl = * (C_FLOAT64 *) mParameters.getValue(i);
      if ((Fail = configbuffer.setVariable(strtmp, "C_FLOAT64", &Dbl)))
        return Fail;
    }
  return 0;
}

void CReaction::saveSBML(std::ofstream &fout, C_INT32 r)
{
  std::string tmpstr, tmpstr2;
  unsigned C_INT32 i;
  CCopasiVector < CChemEqElement > rr;

  FixSName(getObjectName(), tmpstr);
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
          tmpstr2 = rr[i]->getMetabolite().getName(); //TODO: this name is not unique
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
          tmpstr2 = rr[i]->getMetabolite().getName(); //TODO: this name is not unique
          FixSName(tmpstr2, tmpstr);
          fout << "\t\t\t\t\t<specieReference specie=\"" << tmpstr << "\"";
          fout << " stoichiometry=\"" << rr[i]->getMultiplicity() << "\"/>" << std::endl;
        }
    }
  fout << "\t\t\t\t</listOfProducts>" << std::endl;

  fout << "\t\t\t\t<kineticLaw formula=\"";
  // kinetic function string
  tmpstr2 = StringPrint("_%ld", r);
  fout << mpFunction->getSBMLString(mMetabKeyMap, tmpstr2);
  fout << "\">" << std::endl;
  fout << "\t\t\t\t\t<listOfParameters>" << std::endl;
  for (i = 0; i < mParameters.size(); i++)
    {
      FixSName(mParameters.getName(i), tmpstr);
      fout << "\t\t\t\t\t\t<parameter name=\"" + tmpstr;
      fout << "_" << r << "\" value=\"" << mParameters.getValue(i) << "\"/>" << std::endl;
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
  {return getObjectName();}

const CChemEq & CReaction::getChemEq() const
  {return mChemEq;}

CChemEq & CReaction::getChemEq()
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
  return setObjectName(name);
}

//void CReaction::setChemEqFromString(const std::string & chemEq, const CModel & model)
//{mChemEq.setChemicalEquation(chemEq, model);}

/*bool CReaction::addSubstrate(CMetab * pMetab,
                             const C_FLOAT64 & multiplicity)
{return mChemEq.addMetabolite(pMetab, multiplicity, CChemEq::SUBSTRATE);}
 
bool CReaction::addProduct(CMetab * pMetab,
                           const C_FLOAT64 & multiplicity)
{return mChemEq.addMetabolite(pMetab, multiplicity, CChemEq::PRODUCT);}
 
bool CReaction::addModifier(CMetab * pMetab,
                            const C_FLOAT64 & multiplicity)
{return mChemEq.addMetabolite(pMetab, multiplicity, CChemEq::MODIFIER);}
 */

bool CReaction::addSubstrate(const std::string & metabKey,
                             const C_FLOAT64 & multiplicity)
{return mChemEq.addMetabolite(metabKey, multiplicity, CChemEq::SUBSTRATE);}

bool CReaction::addProduct(const std::string & metabKey,
                           const C_FLOAT64 & multiplicity)
{return mChemEq.addMetabolite(metabKey, multiplicity, CChemEq::PRODUCT);}

bool CReaction::addModifier(const std::string & metabKey,
                            const C_FLOAT64 & multiplicity)
{return mChemEq.addMetabolite(metabKey, multiplicity, CChemEq::MODIFIER);}

//bool CReaction::deleteModifier(const std::string &name)
//{return false;} /* :TODO: this needs to be implemented on CChemEq first. */

void CReaction::setReversible(bool reversible)
{mChemEq.setReversibility(reversible);}

bool CReaction::setFunction(const std::string & functionName)
{
  CFunction * pFunction = Copasi->pFunctionDB->findLoadFunction(functionName);
  if (!pFunction)
    CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 1, functionName.c_str());

  return setFunction(pFunction);
}

bool CReaction::setFunction(CFunction * pFunction)
{
  if (!pFunction) fatalError();

  mpFunction = pFunction;

  mMap.initializeFromFunctionParameters(mpFunction->getParameters());
  initializeMetaboliteNameMap(); //needs to be called before initializeParamters();
  initializeParameters();

  return true;
}

// TODO: check if function is set and map initialized in the following methods

void CReaction::setParameterValue(const std::string & parameterName, C_FLOAT64 value)
{
  if (!mpFunction) fatalError();
  mParameters.setValue(parameterName, value);
}

const C_FLOAT64 & CReaction::getParameterValue(const std::string & parameterName) const
  {
    if (!mpFunction) fatalError();
    return * (C_FLOAT64 *) mParameters.getValue(parameterName);
  }

const CCopasiParameterGroup & CReaction::getParameters() const
{return mParameters;}

CCopasiParameterGroup & CReaction::getParameters()
{return mParameters;}

//bool CReaction::setParameterKeys(const std::string & parameterName,
//                                 const std::vector< std::string > & sourceKeys)
//{return true;}

//void CReaction::setParameterMapping(const std::string & parameterName, const CMetab & metab)
//{
//  if (!mpFunction) fatalError();
//  mMap.setCallParameter(parameterName, &metab);
//}

/*void CReaction::setParameterMappingKey(const std::string & parameterName, const CMetab & metab)
{
  CFunctionParameter::DataType type;
  unsigned C_INT32 index;
 
  if (!mpFunction) fatalError();
 
  index = mMap.findParameterByName(parameterName, type);
  if (type == CFunctionParameter::VFLOAT64) fatalError();
 
  mMetabKeyMap[index][0] = metab.getKey();
}*/

void CReaction::setParameterMapping(C_INT32 index, const std::string & key)
{
  if (!mpFunction) fatalError();
  if (getFunctionParameters()[index]->getType() != CFunctionParameter::FLOAT64) fatalError(); //wrong data type

  mMetabKeyMap[index][0] = key;
}

void CReaction::addParameterMapping(C_INT32 index, const std::string & key)
{
  if (!mpFunction) fatalError();
  if (getFunctionParameters()[index]->getType() != CFunctionParameter::VFLOAT64) fatalError(); //wrong data type

  mMetabKeyMap[index].push_back(key);
}

void CReaction::setParameterMapping(const std::string & parameterName, const std::string & key)
{
  if (!mpFunction) fatalError();

  CFunctionParameter::DataType type;
  unsigned C_INT32 index;
  index = mMap.findParameterByName(parameterName, type);
  if (type != CFunctionParameter::FLOAT64) fatalError();

  mMetabKeyMap[index][0] = key;
}

void CReaction::addParameterMapping(const std::string & parameterName, const std::string & key)
{
  if (!mpFunction) fatalError();

  CFunctionParameter::DataType type;
  unsigned C_INT32 index;
  index = mMap.findParameterByName(parameterName, type);
  if (type != CFunctionParameter::VFLOAT64) fatalError();

  mMetabKeyMap[index].push_back(key);
}

void CReaction::setParameterMappingVector(const std::string & parameterName,
    const std::vector<std::string> & keys)
{
  if (!mpFunction) fatalError();

  CFunctionParameter::DataType type;
  unsigned C_INT32 index;
  index = mMap.findParameterByName(parameterName, type);
  if ((type == CFunctionParameter::FLOAT64) && (keys.size() != 1)) fatalError();

  mMetabKeyMap[index] = keys;
}

void CReaction::clearParameterMapping(const std::string & parameterName)
{
  if (!mpFunction) fatalError();
  CFunctionParameter::DataType type;
  unsigned C_INT32 index;
  index = mMap.findParameterByName(parameterName, type);
  if (type != CFunctionParameter::VFLOAT64) fatalError(); //wrong data type
  mMetabKeyMap[index].clear();
  //mMap.clearCallParameter(parameterName);
}

void CReaction::clearParameterMapping(C_INT32 index)
{
  if (!mpFunction) fatalError();
  if (getFunctionParameters()[index]->getType() != CFunctionParameter::VFLOAT64) fatalError();
  mMetabKeyMap[index].clear();
  //mMap.clearCallParameter(parameterName);
}

//void CReaction::addParameterMapping(const std::string & parameterName, const CMetab & metab)
//{
//  if (!mpFunction) fatalError();
//  mMap.addCallParameter(parameterName, &metab);
//}

/*void CReaction::addParameterMappingKey(const std::string & parameterName, const CMetab & metab)
{
  CFunctionParameter::DataType type;
  unsigned C_INT32 index;
 
  if (!mpFunction) fatalError();
 
  index = mMap.findParameterByName(parameterName, type);
  if (type != CFunctionParameter::VFLOAT64) fatalError();
 
  mMetabKeyMap[index].push_back(metab.getKey());
}*/

#ifdef xxx
const std::vector< std::vector<std::string> > CReaction::getParameterMappingName() const
  {
    std::vector< std::vector<std::string> > ParameterNames;
    std::vector< std::vector<std::string> >::const_iterator it
    = mMetabKeyMap.begin();
    std::vector< std::vector<std::string> >::const_iterator iEnd
    = mMetabKeyMap.end();
    std::vector<std::string> SubList;
    std::vector<std::string>::const_iterator jt;
    std::vector<std::string>::const_iterator jEnd;
    //CMetab * pMetab;
    std::string metabName;

    for (; it != iEnd; ++it)
      {
        SubList.clear();
        for (jt = it->begin(), jEnd = it->end(); jt != jEnd; ++jt)
          {
            metabName = CMetabNameInterface::getDisplayName(*jt);
            if (metabName != "")
              SubList.push_back(metabName);
            else
              SubList.push_back(*jt);
            //pMetab = ((CMetab*)(CCopasiContainer*)(CKeyFactory::get(*jt)));
            //if (pMetab)
            //  SubList.push_back(pMetab->getName());
            //else
            //  SubList.push_back(*jt);
          }
        ParameterNames.push_back(SubList);
      }

    return ParameterNames;
  } //TODO: this functionality should be in CReactionInterface
#endif

std::vector<const CMetab *> CReaction::getParameterMappingMetab(C_INT32 index) const
  {
    if (!mpFunction) fatalError();
    if (getFunctionParameters()[index]->getUsage() == "PARAMETER") fatalError();
    std::vector<const CMetab *> metablist;
    unsigned C_INT32 i, imax = mMetabKeyMap[index].size();

    for (i = 0; i < imax; ++i)
      //      metablist.push_back(&mChemEq.findElementByName(mMetabNameMap[index][i]).getMetabolite());
      metablist.push_back((CMetab*)(CCopasiContainer*)CKeyFactory::get(mMetabKeyMap[index][i]));

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
      mMap.setCallParameter(name, mParameters.getParameter(name));
    }
}

void CReaction::initializeParameters()
{
  if (!mpFunction) fatalError();
  unsigned C_INT32 i;
  unsigned C_INT32 imax = mMap.getFunctionParameters().getNumberOfParametersByUsage("PARAMETER");
  unsigned C_INT32 pos;
  std::string name;
  //  CCopasiParameter param("NoName", CCopasiParameter::DOUBLE);
  //  param.setValue((C_FLOAT64) 1.0);

  mParameters.clear();

  for (i = 0, pos = 0; i < imax; ++i)
    {
      name = mMap.getFunctionParameters().getParameterByUsage("PARAMETER", pos).getName();
      //      param.setName(name);
      mParameters.addParameter(name, CCopasiParameter::DOUBLE, (C_FLOAT64) 1.0);
      mMetabKeyMap[pos - 1][0] = name;
    }

  compileParameters();
}

void CReaction::initializeMetaboliteNameMap()
{
  if (!mpFunction) fatalError();
  unsigned C_INT32 i;
  unsigned C_INT32 imax = mMap.getFunctionParameters().size();

  mMetabKeyMap.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      if (mMap.getFunctionParameters()[i]->getType() >= CFunctionParameter::VINT32)
        mMetabKeyMap[i].resize(0);
      else
        mMetabKeyMap[i].resize(1);
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
              jmax = mMetabKeyMap[i].size();
              for (j = 0; j < jmax; ++j)
                mMap.addCallParameter(paramName, CKeyFactory::get(mMetabKeyMap[i][j]));
            }
          else
            mMap.setCallParameter(getFunctionParameters()[i]->getName(), CKeyFactory::get(mMetabKeyMap[i][0]));
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

  CModel * pModel = (CModel*) getObjectAncestor("Model");
  const CCopasiVector< CMetab > & Metabolites = pModel->getMetabolites();

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
        addParameterMapping(parName, Metabolites[pModel->findMetabByName(metabName)]->getKey());
      else
        setParameterMapping(parName, Metabolites[pModel->findMetabByName(metabName)]->getKey());
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
        addParameterMapping(parName, Metabolites[pModel->findMetabByName(metabName)]->getKey());
      else
        setParameterMapping(parName, Metabolites[pModel->findMetabByName(metabName)]->getKey());
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
        addParameterMapping(parName, Metabolites[pModel->findMetabByName(metabName)]->getKey());
      else
        setParameterMapping(parName, Metabolites[pModel->findMetabByName(metabName)]->getKey());

      // in the old files the chemical equation does not contain
      // information about modifiers. This has to be extracted from here.
      mChemEq.addMetabolite(Metabolites[pModel->findMetabByName(metabName)]->getKey(), 1, CChemEq::MODIFIER);
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
    unsigned C_INT32 Index;

    Index = mMap.getFunctionParameters().getUsageRanges().getIndex(usage);
    if (Index != C_INVALID_INDEX)
      pUsageRange = mMap.getFunctionParameters().getUsageRanges()[Index];

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

C_INT32 CReaction::getSubstrateMolecularity() const
  {return mChemEq.getMolecularity(CChemEq::SUBSTRATE);}
C_INT32 CReaction::getProductMolecularity() const
  {return mChemEq.getMolecularity(CChemEq::PRODUCT);}
C_INT32 CReaction::getModifierMolecularity() const
  {return mChemEq.getMolecularity(CChemEq::MODIFIER);}

void CReaction::initObjects()
{
  addObjectReference("Name", *const_cast<std::string *>(&getObjectName()));
  addObjectReference("Flux", mFlux, CCopasiObject::ValueDbl);
  addObjectReference("ScaledFlux", mScaledFlux, CCopasiObject::ValueDbl);
  //add(&mParameters);
  //add(&mMap);
}
