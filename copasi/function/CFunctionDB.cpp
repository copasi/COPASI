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
#include "utilities/CCopasiException.h"

CFunctionDB::CFunctionDB() {CONSTRUCTOR_TRACE;}

void CFunctionDB::initialize() {}

CFunctionDB::~CFunctionDB() {cleanup(); DESTRUCTOR_TRACE;}

void CFunctionDB::cleanup() {mLoadedFunctions.cleanup();}

C_INT32 CFunctionDB::load(CReadConfig &configbuffer)
{
  CFunction Function;
  CFunction * pFunction = NULL;

  C_INT32 Size = 0;
  C_INT32 Fail = 0;

  if (configbuffer.getVersion() < "4")
    configbuffer.getVariable("TotalUDKinetics", "C_INT32", &Size,
                             CReadConfig::LOOP);
  else
    configbuffer.getVariable("TotalKinetics", "C_INT32", &Size,
                             CReadConfig::LOOP);

  for (C_INT32 i = 0; i < Size; i++)
    {
      Function.load(configbuffer);

      switch (Function.getType())
        {
        case CFunction::Base:
          pFunction = new CFunction(Function, &mLoadedFunctions);
          break;

        case CFunction::MassAction:
          pFunction = new CMassAction(Function, &mLoadedFunctions);
          break;

        case CFunction::PreDefined:

        case CFunction::UserDefined:
          pFunction = new CKinFunction(Function,
                                       &configbuffer,
                                       &mLoadedFunctions);
          break;

        default:
          fatalError();
        }

      try
        {
          mLoadedFunctions.add(pFunction);
        }

      catch (CCopasiException Exception)
        {
          if ((MCCopasiVector + 2) != Exception.getMessage().getNumber())
            throw Exception;
        }
    }

  return Fail;
}

C_INT32 CFunctionDB::save(CWriteConfig &configbuffer)
{
  C_INT32 Size = mLoadedFunctions.size();
  C_INT32 Fail = 0;

  if ((Fail = configbuffer.setVariable("TotalKinetics", "C_INT32", &Size)))
    return Fail;

  mLoadedFunctions.save(configbuffer);

  return Fail;
}

C_INT32 CFunctionDB::saveOld(CWriteConfig &configbuffer)
{
  C_INT32 Size;
  C_INT32 Fail = 0;
  C_INT32 i, j;

  Size = mLoadedFunctions.size();
  for (i = j = 0; i < Size; i++)
    if (mLoadedFunctions[i]->getType() == CFunction::UserDefined)
      j++;

  if ((Fail = configbuffer.setVariable("TotalUDKinetics", "C_INT32", &j)))
    return Fail;

  // because CCopasiVector does not have saveOld, we will save them one by one
  for (i = 0; i < Size; i++)
    if (mLoadedFunctions[i]->getType() == CFunction::UserDefined)
      mLoadedFunctions[i]->saveOld(configbuffer);

  return Fail;
}

void CFunctionDB::setFilename(const std::string & filename)
{mFilename = filename;}

std::string CFunctionDB::getFilename() const
  {return mFilename;}

CFunction * CFunctionDB::dBLoad(const std::string & functionName)
{
  CFunction Function;
  CFunction * pFunction = NULL;

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
      pFunction = new CKinFunction(Function, &inbuf);
      break;

    case CFunction::Output:
      pFunction = new CUDFunction(Function);
      break;

    default:
      fatalError();
    }

  try
    {
      mLoadedFunctions.add(pFunction);
    }
  catch (CCopasiException Exception)
    {
      pdelete(pFunction);
      // We ignore:
      // CCopasiVector (2): Object '%s' allready exists.
      if ((MCCopasiVector + 2) != Exception.getMessage().getNumber())
        throw Exception;
      pFunction = mLoadedFunctions[Function.getName()];
    }

  return pFunction;
}

void CFunctionDB::add(CFunction * function)
{mLoadedFunctions.add(function);}

// void CFunctionDB::dBDelete(const string & functionName)
// {
//}

CFunction * CFunctionDB::findFunction(const std::string & functionName)
{
  unsigned C_INT32 i;

  for (i = 0; i < mLoadedFunctions.size(); i++)
    if (functionName == mLoadedFunctions[i]->getName())
      return mLoadedFunctions[i];

  return NULL;
}

CFunction * CFunctionDB::findLoadFunction(const std::string & functionName)
{
  unsigned C_INT32 i;

  for (i = 0; i < mLoadedFunctions.size(); i++)
    if (functionName == mLoadedFunctions[i]->getName())
      return mLoadedFunctions[i];

  return dBLoad(functionName);
}

CCopasiVectorNS < CFunction > & CFunctionDB::loadedFunctions()
{return mLoadedFunctions;}

CCopasiVectorN < CFunction >
CFunctionDB::suitableFunctions(const unsigned C_INT32 noSubstrates,
                               const unsigned C_INT32 noProducts,
                               const TriLogic reversible)
{
  CCopasiVectorN < CFunction > Functions;
  unsigned C_INT32 i, imax = mLoadedFunctions.size();
  CFunction *pFunction;
  CUsageRange *UsageRange;
  bool Suitable;

  for (i = 0; i < imax; i++)
    {
      Suitable = true;
      pFunction = mLoadedFunctions[i];

      if (reversible != TriUnspecified &&
          reversible != pFunction->isReversible())
        Suitable = false;

      try
        {
          UsageRange = pFunction->getUsageDescriptions()["SUBSTRATES"];

          if (!UsageRange->isInRange(noSubstrates))
            Suitable = false;

          UsageRange = pFunction->getUsageDescriptions()["PRODUCTS"];

          if (!UsageRange->isInRange(noProducts))
            Suitable = false;
        }

      catch (CCopasiException Exception)
        {
          if ((MCCopasiVector + 1) != Exception.getMessage().getNumber())
            throw Exception;
          else
            Suitable = false;
        }

      if (Suitable)
        Functions.add(pFunction);
    }

  return Functions;
}
