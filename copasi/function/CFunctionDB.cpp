/**
 * CFunctionDB
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CFunctionDB.h"
#include "CMassAction.h"
#include "output/CUDFunction.h"

CFunctionDB::CFunctionDB() {CONSTRUCTOR_TRACE;}

void CFunctionDB::initialize() 
{
  /*
  CMassAction *MassActionReversible   = new CMassAction(TriTrue);
  mBuiltinFunctions.push_back(MassActionReversible);
    
  CMassAction *MassActionIrreversible = new CMassAction(TriFalse);
  mBuiltinFunctions.push_back(MassActionIrreversible);
  */
}

CFunctionDB::~CFunctionDB() {cleanup(); DESTRUCTOR_TRACE;}

void CFunctionDB::cleanup()
{
  unsigned C_INT32 i;
    
  mLoadedFunctions.cleanup();
    
  for (i = 0; i < mBuiltinFunctions.size(); i++)
    delete mBuiltinFunctions[i];
  mBuiltinFunctions.clear();
}

C_INT32 CFunctionDB::load(CReadConfig &configbuffer)
{
  CKinFunction * pFunction = NULL;
  C_INT32 Size = 0;
  C_INT32 Fail = 0;

  if ((Fail = configbuffer.getVariable("TotalKinetics", "C_INT32", &Size,
				       CReadConfig::LOOP)))
    return Fail;
    
  for (C_INT32 i = 0; i < Size; i++)
    {
      // We should really read the function type first before we allocate,
      // but since we currently have only one type this will do.
      pFunction = new CKinFunction;
      pFunction->load(configbuffer);
      mLoadedFunctions.add(pFunction);
    }
  return Fail;
}

C_INT32 CFunctionDB::save(CWriteConfig &configbuffer)
{
  C_INT32 Size = mLoadedFunctions.size();
  C_INT32 Fail = 0;
    
  if ((Fail = configbuffer.setVariable("TotalKinetics", "C_INT32", &Size)))
    return Fail;

  for (C_INT32 i = 0; i < Size; i++)
    mLoadedFunctions[i]->save(configbuffer);

  return Fail;
}

void CFunctionDB::setFilename(const string & filename) {mFilename = filename;}
    
string CFunctionDB::getFilename() const {return mFilename;}

CFunction * CFunctionDB::dBLoad(const string & functionName) 
{
  CFunction Function;
  CFunction * pFunction = NULL;
  C_INT32 Index = mLoadedFunctions.size();

  CReadConfig inbuf(mFilename);
    
  while (functionName != Function.getName())
    {
      Function.cleanup();
      Function.load(inbuf);
    }

  switch (Function.getType())
    {
    case CFunction::Base:
      pFunction = new CFunction(Function);
      break;
    case CFunction::MassAction:
      pFunction = new CMassAction(Function.isReversible());
      break;
    case CFunction::PreDefined:
    case CFunction::UserDefined:
      pFunction = new CKinFunction(Function);
      break;
    case CFunction::Output:
      pFunction = new CUDFunction(Function);
      break;
    default:
      fatalError();
    }
  
  mLoadedFunctions.add(pFunction);

  return mLoadedFunctions[Index];
}

void CFunctionDB::add(CKinFunction & function)
{mLoadedFunctions.add(function);}

// void CFunctionDB::dBDelete(const string & functionName)
// {
// }

CFunction * CFunctionDB::findFunction(const string & functionName)
{
  unsigned C_INT32 i;

  for (i = 0; i < mLoadedFunctions.size(); i++)
    if (functionName == mLoadedFunctions[i]->getName())
      return mLoadedFunctions[i];
    
  return dBLoad(functionName);
}

CCopasiVectorN < CFunction > & CFunctionDB::loadedFunctions()
{return mLoadedFunctions;}
