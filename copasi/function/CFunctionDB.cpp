#include "CFunctionDB.h"
#include "CMassAction.h"

CFunctionDB::CFunctionDB() {}

void CFunctionDB::initialize() 
{
  CMassAction *MassActionReversible   = new CMassAction(TRUE);
  mBuiltinFunctions.push_back(MassActionReversible);
    
  CMassAction *MassActionIrreversible = new CMassAction(FALSE);
  mBuiltinFunctions.push_back(MassActionIrreversible);
}

CFunctionDB::~CFunctionDB() {}

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

  if ((Fail = configbuffer.getVariable("TotalUDKinetics", "C_INT32", &Size,
				       CReadConfig::LOOP)))
    return Fail;
    
  for (C_INT32 i = 0; i < Size; i++)
    {
      // We should really read the function type first before we allocate,
      // but since we currently have only one type this will do.
      pFunction = new CKinFunction;
      if ((Fail = pFunction->load(configbuffer))) return Fail;
      mLoadedFunctions.add(pFunction);
    }
  return Fail;
}

C_INT32 CFunctionDB::save(CWriteConfig &configbuffer)
{
  C_INT32 Size = mLoadedFunctions.size();
  C_INT32 Fail = 0;
    
  if ((Fail = configbuffer.setVariable("TotalUDKinetics", "C_INT32", &Size)))
    return Fail;

  for (C_INT32 i = 0; i < Size; i++)
    if ((Fail = mLoadedFunctions[i]->save(configbuffer))) return Fail;

  return Fail;
}

void CFunctionDB::setFilename(const string & filename) {mFilename = filename;}
    
string CFunctionDB::getFilename() const {return mFilename;}

CBaseFunction * CFunctionDB::dBLoad(const string & functionName) 
{
  C_INT32 Index = mLoadedFunctions.size();
  C_INT32 Fail = 0;
    
  CBaseFunction *pFunction = new CKinFunction;
  mLoadedFunctions.add(pFunction);
    
  CReadConfig inbuf(mFilename);
    
  while (functionName != pFunction->getName())
    {
      pFunction->cleanup();
      Fail = pFunction->load(inbuf);
    }

  return mLoadedFunctions[Index];
}

void CFunctionDB::add(CKinFunction & function)
{
  CKinFunction *Function = new CKinFunction;
  Function->initialize();
  Function->copy(function);
        
  mLoadedFunctions.add(Function);
}

// void CFunctionDB::dBDelete(const string & functionName)
// {
// }

CBaseFunction * CFunctionDB::findFunction(const string & functionName)
{
  unsigned C_INT32 i;
    
  for (i = 0; i < mLoadedFunctions.size(); i++)
    if (functionName == mLoadedFunctions[i]->getName())
      return mLoadedFunctions[i];

  for (i = 0; i < mBuiltinFunctions.size(); i++)
    if (functionName == mBuiltinFunctions[i]->getName())
      return mBuiltinFunctions[i];
    
  return dBLoad(functionName);
}

CCopasiVectorP < CBaseFunction * > & CFunctionDB::loadedFunctions()
{return mLoadedFunctions;}
