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
#include "report/CCopasiObjectReference.h" 
// #include "report/CKeyFactory.h"
#include "utilities/CMethodParameter.h"
#include "xml/CCopasiXML.h"

CFunctionDB::CFunctionDB(const std::string & name,
                         const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "FunctionDB"),
    mFilename(),
    mLoadedFunctions("Functions", this)
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

CFunctionDB::~CFunctionDB()
{
  cleanup();
  DESTRUCTOR_TRACE;
}

void CFunctionDB::cleanup() {mLoadedFunctions.cleanup();}

void CFunctionDB::initObjects()
{
  addObjectReference("File", mFilename);
}

bool CFunctionDB::load()
{
  CCopasiXML XML;
  std::ifstream DB(mFilename.c_str());
  if (DB.fail()) return false;
  if (!XML.load(DB)) return false;

  CCopasiVectorN< CFunction > * pFunctionList = XML.getFunctionList();

  unsigned C_INT32 i, imax = pFunctionList->size();

  for (i = 0; i < imax; i++)
    mLoadedFunctions.add((*pFunctionList)[i], true);

  XML.freeFunctionList();

  return true;
}

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
          pFunction = new CFunction(Function);
          break;

        case CFunction::MassAction:
          pFunction = new CMassAction(Function);
          break;

        case CFunction::PreDefined:

        case CFunction::UserDefined:
          pFunction = new CKinFunction(Function,
                                       &configbuffer);
          break;

        default:
          fatalError();
        }

      try
        {
          mLoadedFunctions.add(pFunction, true);
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
  CFunction Function("NoName", &mLoadedFunctions);
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

    case CFunction::Expression:
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

bool CFunctionDB::addFunction(const std::string & name, const CFunction::Type & type)
{
  if (mLoadedFunctions.getIndex(name) != C_INVALID_INDEX)
    return false;

  //CFunction * pFunction = new CFunction(name);

  CFunction * pFunction = NULL;
  switch (type)
    {
    case CFunction::Base:
      pFunction = new CFunction(name);
      break;

    case CFunction::MassAction:
      pFunction = new CMassAction(name);
      break;

    case CFunction::PreDefined:

    case CFunction::UserDefined:
      pFunction = new CKinFunction(name);
      break;

    default:
      fatalError();
    }

  if (!mLoadedFunctions.add(pFunction, true))
    {
      delete pFunction;
      return false;
    }
  return true;
}

CFunction * CFunctionDB::add(const CFunction & function)
{
  if (mLoadedFunctions.getIndex(function.getName()) != C_INVALID_INDEX)
    return findFunction(function.getName());

  CFunction * pFunction = NULL;
  switch (function.getType())
    {
    case CFunction::Base:
      pFunction = new CFunction(function, &mLoadedFunctions);
      break;

    case CFunction::MassAction:
      pFunction = new CMassAction(function, &mLoadedFunctions);
      break;

    case CFunction::PreDefined:

    case CFunction::UserDefined:
      pFunction = new CKinFunction(function,
                                   NULL,
                                   &mLoadedFunctions);
      break;

    default:
      fatalError();
    }

  mLoadedFunctions.add(pFunction);

  return pFunction;
}

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

CCopasiVector <CFunction> *
CFunctionDB::suitableFunctions(const unsigned C_INT32 noSubstrates,
                               const unsigned C_INT32 noProducts,
                               const TriLogic reversible)
{
  CCopasiVector< CFunction >* pFunctionVector = new CCopasiVector< CFunction >();
  unsigned C_INT32 i, imax;
  unsigned C_INT32 j, jmax;
  CFunction *pFunction;
  CUsageRange * pRange;

  for (i = 0, imax = mLoadedFunctions.size(); i < imax; i++)
    {
      pFunction = mLoadedFunctions[i];

      if (reversible != TriUnspecified &&
          reversible != pFunction->isReversible() &&
          pFunction->isReversible() != TriUnspecified)
        continue;

      for (j = 0, jmax = pFunction->getUsageDescriptions().size();
           j < jmax; j++)
        {
          pRange = pFunction->getUsageDescriptions()[j];

          if (pRange->getUsage() == "SUBSTRATES")
            if (!pRange->isInRange(noSubstrates)) break;

          if (pRange->getUsage() == "PRODUCTS")
            if (!pRange->isInRange(noProducts)) break;
        }

      if (j == jmax) pFunctionVector->add(pFunction);
    }

  return pFunctionVector;
}
