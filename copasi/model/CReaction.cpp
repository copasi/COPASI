// CReaction 
// 
// Derived from Gepasi's cstep.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Stefan Hoops


#include "copasi.h"
#include "utilities/CGlobals.h"
#include "CReaction.h"
#include "CCompartment.h"
#include "utilities/utilities.h"

CReaction::CReaction()
{
  mFlux = 0.0;
  mReversible = TRUE;
  mFunction = NULL;
}

CReaction::CReaction(const CReaction & src)
{
  mName = src.mName;
  mFlux = src.mFlux;
  mReversible = src.mReversible;
  mFunction = src.mFunction;

  mId2Substrates = CCopasiVector < CId2Metab > (src.mId2Substrates);
  mId2Products = CCopasiVector < CId2Metab > (src.mId2Products);
  mId2Modifiers = CCopasiVector < CId2Metab > (src.mId2Modifiers);
  mId2Parameters = CCopasiVector < CId2Param > (src.mId2Parameters);
  
  initIdentifiers();
}

CReaction::CReaction(const string & name)
{
  mName = name;
  mFlux = 0.0;
  mReversible = TRUE;
  mFunction = NULL;
}

CReaction::~CReaction() {}

void CReaction::cleanup()
{
  mId2Substrates.cleanup();
  mId2Products.cleanup();
  mId2Modifiers.cleanup();
  mId2Parameters.cleanup();
  mCallParameters.cleanup();
}

#ifdef XXXX
CReaction & CReaction::operator=(const CReaction & rhs)
{
  mName        = rhs.mName;
  mChemEq      = rhs.mChemEq;
  mFunction    = rhs.mFunction;
  mFlux        = rhs.mFlux;
  mReversible  = rhs.mReversible;
  mId2Substrates  = rhs.mId2Substrates;
  mId2Products    = rhs.mId2Products;
  mId2Modifiers   = rhs.mId2Modifiers;
  mId2Parameters  = rhs.mId2Parameters;
  mCallParameters = rhs.mCallParameters;

  return *this;
}
#endif // XXXX

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
  if (mFunction == NULL) return Fail = 1;

  initIdentifiers();
    
  if ((Fail = configbuffer.getVariable("Flux", "C_FLOAT64", &mFlux)))
    return Fail;
    
  if ((Fail = configbuffer.getVariable("Reversible", "C_INT32", &mReversible)))
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

  if ((Fail = configbuffer.setVariable("Flux", "C_FLOAT64", &mFlux)))
    return Fail;
    
  if ((Fail = configbuffer.setVariable("Reversible", "C_INT32", &mReversible)))
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

CCopasiVector < CReaction::CId2Metab > &CReaction::getId2Substrates() 
{return mId2Substrates;}

CCopasiVector < CReaction::CId2Metab > &CReaction::getId2Products() 
{return mId2Products;}

CCopasiVector < CReaction::CId2Metab > &CReaction::getId2Modifiers() 
{return mId2Modifiers;}

CCopasiVector < CReaction::CId2Param > &CReaction::getId2Parameters() 
{return mId2Parameters;}

string CReaction::getName() const {return mName;}

CChemEq & CReaction::getChemEq() {return mChemEq;}

CBaseFunction & CReaction::getFunction() {return *mFunction;}

C_FLOAT64 CReaction::getFlux() const {return mFlux;}

C_INT16 CReaction::isReversible() const {return (mReversible == TRUE);}

void CReaction::setName(const string & name) {mName = name;}

void CReaction::setChemEq(const string & chemEq) 
{mChemEq.setChemicalEquation(chemEq);}

void CReaction::setFlux(C_FLOAT64 flux) {mFlux = flux;}

void CReaction::setReversible(C_INT16 reversible) {mReversible = reversible;}

void CReaction::setFunction(const string & functionName)
{
  mFunction = Copasi.FunctionDB.findFunction(functionName);
}

void CReaction::initIdentifiers()
{
  unsigned C_INT32 i;
  C_INT32 Count;
    
  if (!mFunction) fatalError();

  mCallParameters.cleanup();
    
  mCallParameters.resize(mFunction->callParameters().size());
  for (i = 0; i < mCallParameters.size(); i++)
    {
      mCallParameters[i]->
	setType(mFunction->callParameters()[i]->getType());

      Count = mFunction->callParameters()[i]->getCountLow();
      mCallParameters[i]->identifiers().resize(Count);
      for (C_INT32 j = 0; j < Count; j++)
	mCallParameters[i]->identifiers()[j] = NULL;
    }
}

void CReaction::setIdentifiers()
{
  pair < unsigned C_INT32, unsigned C_INT32 > Tuple;
    
  unsigned C_INT32 i, j;
  unsigned C_INT32 OldSize;
    
  for (i = 0; i < mId2Substrates.size(); i++)
    {
      if (mId2Substrates[i]->mIdentifierName == "") continue;
        
      Tuple = mFunction->findIdentifier(mId2Substrates[i]->mIdentifierName);

      if ( !(Tuple.first + 1) || !(Tuple.second + 1)) fatalError();
      if (mCallParameters[Tuple.first]->getType() 
	  != CCallParameter::VECTOR_DOUBLE) fatalError();

      if ((OldSize = mCallParameters[Tuple.first]->identifiers().size()) <
	  Tuple.second + 1)
        {
	  mCallParameters[Tuple.first]->identifiers().
	    resize(Tuple.second + 1);
	  for( j = OldSize; j < Tuple.second + 1; j++)
	    mCallParameters[Tuple.first]->identifiers()[j] = NULL;
        }
        
      mCallParameters[Tuple.first]->identifiers()[Tuple.second] =
	mId2Substrates[i]->mpMetabolite->getConcentration();
    }

  /* :TODO: this is broken for "Mass action (irreversible)" */
  if (mFunction->getName() != "Mass action (irreversible)")
    for (i = 0; i < mId2Products.size(); i++)
      {
	if (mId2Products[i]->mIdentifierName == "") continue;
        
	Tuple = mFunction->findIdentifier(mId2Products[i]->mIdentifierName);

	if ( !(Tuple.first + 1) || !(Tuple.second + 1)) fatalError();
	if (mCallParameters[Tuple.first]->getType()
	    != CCallParameter::VECTOR_DOUBLE) fatalError();
                                                     
	if ((OldSize = mCallParameters[Tuple.first]->identifiers().size())
	    < Tuple.second + 1)
	  {
	    mCallParameters[Tuple.first]->identifiers().
	      resize(Tuple.second + 1);
	    for( j = OldSize; j < Tuple.second + 1; j++)
	      mCallParameters[Tuple.first]->identifiers()[j] = NULL;
	  }
        
	mCallParameters[Tuple.first]->identifiers()[Tuple.second] =
	  mId2Products[i]->mpMetabolite->getConcentration();
      }

  for (i = 0; i < mId2Modifiers.size(); i++)
    {
      if (mId2Modifiers[i]->mIdentifierName == "") continue;
        
      Tuple = mFunction->findIdentifier(mId2Modifiers[i]->mIdentifierName);

      if ( !(Tuple.first + 1) || !(Tuple.second + 1)) fatalError();
      if (mCallParameters[Tuple.first]->getType()
	  != CCallParameter::VECTOR_DOUBLE) fatalError();
                                                     
      if ((OldSize = mCallParameters[Tuple.first]->identifiers().size())
	  < Tuple.second + 1)
        {
	  mCallParameters[Tuple.first]->identifiers().
	    resize(Tuple.second + 1);
	  for( j = OldSize; j < Tuple.second + 1; j++)
	    mCallParameters[Tuple.first]->identifiers()[j] = NULL;
        }
        
      mCallParameters[Tuple.first]->identifiers()[Tuple.second] =
	mId2Modifiers[i]->mpMetabolite->getConcentration();
    }

  for (i = 0; i < mId2Parameters.size(); i++)
    {
      if (mId2Parameters[i]->mIdentifierName == "") continue;
        
      Tuple = mFunction->findIdentifier(mId2Parameters[i]->mIdentifierName);

      if ( !(Tuple.first + 1) || !(Tuple.second + 1)) fatalError();
      if (mCallParameters[Tuple.first]->getType()
	  != CCallParameter::VECTOR_DOUBLE) fatalError();
                                                     
      if ((OldSize = mCallParameters[Tuple.first]->identifiers().size())
	  < Tuple.second + 1)
        {
	  mCallParameters[Tuple.first]->identifiers().
	    resize(Tuple.second + 1);
	  for( j = OldSize; j < Tuple.second + 1; j++)
	    mCallParameters[Tuple.first]->identifiers()[j] = NULL;
        }
        
      mCallParameters[Tuple.first]->identifiers()[Tuple.second] =
	&mId2Parameters[i]->mValue;
    }
}

void CReaction::checkIdentifiers()
{
  for (unsigned C_INT32 i = 0; i < mCallParameters.size(); i++)
    {
      for (unsigned C_INT32 j = 0;
	   j < mCallParameters[i]->identifiers().size(); j++)
	if (!mCallParameters[i]->identifiers()[j]) fatalError();
    }
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
    
  initIdentifiers();
  setIdentifiers();
  checkIdentifiers();
  
  mChemEq.compile(compartments);
}

C_INT32 CReaction::loadNew(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;
  C_INT32 Size;
  C_INT32 i;
    
  if ((Fail = configbuffer.getVariable("Substrates", "C_INT32", &Size)))
    return Fail;
  mId2Substrates.resize(Size);
  for (i=0; i < Size; i++)
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
  for (i=0; i < Size; i++)
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
  C_INT32 Size;
  unsigned C_INT32 i;
  C_INT32 index;

  if ((Fail = configbuffer.getVariable("Substrates", "C_INT32", &Size)))
    return Fail;
  mId2Substrates.resize(Size);
    
  if ((Fail = configbuffer.getVariable("Products", "C_INT32", &Size)))
    return Fail;
  mId2Products.resize(Size);

  if ((Fail = configbuffer.getVariable("Modifiers", "C_INT32", &Size)))
    return Fail;
  mId2Modifiers.resize(Size);

  if ((Fail = configbuffer.getVariable("Constants", "C_INT32", &Size)))
    return Fail;
  mId2Parameters.resize(Size);

  for (i = 0; i < mId2Substrates.size(); i++)
    {
      name = StringPrint("Subs%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);

      if (mFunction->getName().substr(0,11) == "Mass action")
	mId2Substrates[i]->mIdentifierName = StringPrint("substrate_%d", i);
      else if (mFunction->callParameters()[0]->identifiers(N_SUBSTRATE).size()
	       < i + 1)
	mId2Substrates[i]->mIdentifierName = "";
      else
	mId2Substrates[i]->mIdentifierName = mFunction->callParameters()[0]->
	  identifiers(N_SUBSTRATE)[i]->getName();
        
      mId2Substrates[i]->mMetaboliteName = 
	Copasi.OldMetabolites[index]->getName();
    }
    
  for (i = 0; i < mId2Products.size(); i++)
    {
      name = StringPrint("Prod%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);
        
      if (mFunction->getName().substr(0,11) == "Mass action")
	mId2Products[i]->mIdentifierName = StringPrint("product_%d", i);
      else if (mFunction->callParameters()[0]->identifiers(N_PRODUCT).size()
	       < i + 1)
	mId2Products[i]->mIdentifierName = "";
      else
	mId2Products[i]->mIdentifierName = mFunction->callParameters()[0]->
	  identifiers(N_PRODUCT)[i]->getName();
        
      mId2Products[i]->mMetaboliteName = 
	Copasi.OldMetabolites[index]->getName();
    }
    
  for (i = 0; i < mId2Modifiers.size(); i++)
    {
      name = StringPrint("Modf%d", i);
      configbuffer.getVariable(name, "C_INT32", &index);
        
      if (mFunction->callParameters()[0]->identifiers(N_MODIFIER).size()
	  < i + 1)
	mId2Modifiers[i]->mIdentifierName = "";
      else
	mId2Modifiers[i]->mIdentifierName = mFunction->callParameters()[0]->
	  identifiers(N_MODIFIER)[i]->getName();

      mId2Modifiers[i]->mMetaboliteName = 
	Copasi.OldMetabolites[index]->getName();
    }
    
  for (i = 0; i < mId2Parameters.size(); i++)
    {
      name = StringPrint("Param%d", i);
      configbuffer.getVariable(name, "C_FLOAT64", 
			       &mId2Parameters[i]->mValue);
      if (mFunction->getName().substr(0,11) == "Mass action")
        {
	  if (i)
	    mId2Parameters[i]->mIdentifierName = "kp";
	  else
	    mId2Parameters[i]->mIdentifierName = "ks";
        }
      else if (mFunction->callParameters()[0]->identifiers(N_KCONSTANT).size()
	       < i + 1)
	mId2Parameters[i]->mIdentifierName = "";
      else
	mId2Parameters[i]->mIdentifierName = mFunction->callParameters()[0]->
	  identifiers(N_KCONSTANT)[i]->getName();
    }
    
        
  return Fail;
}

CReaction::CId2Metab::CId2Metab() {mpMetabolite = NULL;}

CReaction::CId2Metab::CId2Metab(const CId2Metab & src)
{
  mIdentifierName = src.mIdentifierName;
  mMetaboliteName = src.mMetaboliteName;
  mCompartmentName = src.mCompartmentName;
  mpMetabolite = NULL;
}

CReaction::CId2Metab::~CId2Metab() {}

void CReaction::CId2Metab::cleanup() {}

CReaction::CId2Param::CId2Param() {}

CReaction::CId2Param::CId2Param(const CId2Param & src)
{
  mIdentifierName = src.mIdentifierName;
  mValue = src.mValue;
}

CReaction::CId2Param::~CId2Param() {}

void CReaction::CId2Param::cleanup() {}

void CReaction::old2New(const vector < CMetab* > & metabolites)
{
  unsigned C_INT32 i, j;
    
  for (i = 0; i < mId2Substrates.size(); i++)
    {
      for (j = 0; j < metabolites.size(); j++)
	if (metabolites[j]->getName() ==
	    mId2Substrates[i]->mMetaboliteName) break;
      mId2Substrates[i]->mCompartmentName =
	metabolites[j]->getCompartment()->getName();
    }
    
  for (i = 0; i < mId2Products.size(); i++)
    {
      for (j = 0; j < metabolites.size(); j++)
	if (metabolites[j]->getName() ==
	    mId2Products[i]->mMetaboliteName) break;
      mId2Products[i]->mCompartmentName =
	metabolites[j]->getCompartment()->getName();
    }
    
  for (i = 0; i < mId2Modifiers.size(); i++)
    {
      for (j = 0; j < metabolites.size(); j++)
	if (metabolites[j]->getName() ==
	    mId2Modifiers[i]->mMetaboliteName) break;
      mId2Modifiers[i]->mCompartmentName =
	metabolites[j]->getCompartment()->getName();
    }
}

C_FLOAT64 CReaction::calculate() 
{
  return mFlux = mFunction->calcValue(mCallParameters);
}

/**
 *	Return Identifier Name		Wei Sun
 */
string CReaction::CId2Param::getIdentifierName() const
{
  return mIdentifierName;
}

/**
 *	Retun the value of the pararmeter
 */
C_FLOAT64 CReaction::CId2Param::getValue() const
{
  return mValue;
}

/**
 *	Returns the address of mValue
 */
void* CReaction::CId2Param::getValueAddr()
{
  return &mValue;
}

/**
 *	Returns the address of mFlux
 */
void* CReaction::getFluxAddr()
{
  return &mFlux;
}

/**
 *	Returns the index of the parameter
 */
C_INT32 CReaction::findPara(string &Target)
{
  unsigned C_INT32 i;
  string name;

  for(i = 0; i < mId2Parameters.size(); i++ )
    {
      name = mId2Parameters[i]->getIdentifierName();
      if( name == Target) return i;
    }

  return -1;
	
}


