/**
 * CFunction
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CFunctionParameter.h"
#include "CFunctionParameters.h"
#include "CFunction.h"

CFunction::CFunction()
{
  CONSTRUCTOR_TRACE;
  mReversible = TriUnspecified;
}

CFunction::CFunction(const CFunction & src)
{
  CONSTRUCTOR_TRACE;
  mType = src.mType;
  mName = src.mName;
  mDescription = src.mDescription;
  mReversible = src.mReversible;
  mUsageDescriptions = CCopasiVectorNS < CUsageRange > (src.mUsageDescriptions);
  mParameters = CFunctionParameters(src.mParameters);
}

CFunction::~CFunction()
{
  cleanup();
  DESTRUCTOR_TRACE;
}

void CFunction::cleanup()
{
  mUsageDescriptions.cleanup();
  mParameters.cleanup();
}

void CFunction::load(CReadConfig & configBuffer,
                     CReadConfig::Mode mode)
{
  cleanup();

  if (configBuffer.getVersion() < "4")
    {
      C_INT32 Type;
      CUsageRange UsageDescription;

      mode = CReadConfig::SEARCH;
      configBuffer.getVariable("User-defined", "C_INT32", &Type, mode);

      switch (Type)
        {
        case 1:
          mType = CFunction::UserDefined;
          break;

        default:
          fatalError();
        }

      configBuffer.getVariable("Reversible", "C_INT32", &mReversible);

      configBuffer.getVariable("Substrates", "C_INT32", &Type);
      UsageDescription.setUsage("SUBSTRATES");
      UsageDescription.setLow(Type);
      mUsageDescriptions.add(UsageDescription);

      configBuffer.getVariable("Products", "C_INT32", &Type);
      UsageDescription.setUsage("PRODUCTS");
      UsageDescription.setLow(Type);
      mUsageDescriptions.add(UsageDescription);

      mode = CReadConfig::SEARCH;
    }
  else
    {
      configBuffer.getVariable("FunctionType", "C_INT32", &mType, mode);
      mode = CReadConfig::NEXT;
    }

  configBuffer.getVariable("FunctionName", "string", &mName, mode);
  configBuffer.getVariable("Description", "string", &mDescription);

  if (configBuffer.getVersion() >= "4")
    {
      unsigned C_INT32 Size;
      configBuffer.getVariable("Reversible", "C_INT32", &mReversible);
      configBuffer.getVariable("UsageDescriptionSize", "C_INT32", &Size);
      mUsageDescriptions.load(configBuffer, Size);
      mParameters.load(configBuffer);
    }

  // For older file version the parameters have to be build from information
  // dependend on the function type. Luckilly, only user defined functions are
  // the only ones occuring in those files.
}

void CFunction::save(CWriteConfig & configBuffer)
{
  configBuffer.setVariable("FunctionType", "C_INT32", &mType);
  configBuffer.setVariable("FunctionName", "string", &mName);
  configBuffer.setVariable("Description", "string", &mDescription);
  configBuffer.setVariable("Reversible", "C_INT32", &mReversible);

  unsigned C_INT32 Size = mUsageDescriptions.size();
  configBuffer.setVariable("UsageDescriptionSize", "C_INT32", &Size);
  mUsageDescriptions.save(configBuffer);
  mParameters.save(configBuffer);
}

void CFunction::saveOld(CWriteConfig & configBuffer)
{
  C_INT32 dummy, i, sizem, sizep;
  unsigned C_INT32 pos;
  string tmpstr1, tmpstr2;

  if (mType == UserDefined)
    dummy = 1;
  else
    dummy = 0;
  configBuffer.setVariable("UDKType", "string", &mName);
  configBuffer.setVariable("User-defined", "C_INT32", &dummy);
  configBuffer.setVariable("Reversible", "C_INT32", &mReversible);
  dummy = mUsageDescriptions["SUBSTRATES"]->getLow();
  configBuffer.setVariable("Substrates", "C_INT32", &dummy);
  dummy = mUsageDescriptions["PRODUCTS"]->getLow();
  configBuffer.setVariable("Products", "C_INT32", &dummy);
  sizem = mParameters.getUsageRanges()["MODIFIER"]->getLow();
  configBuffer.setVariable("Modifiers", "C_INT32", &sizem);
  sizep = mParameters.getUsageRanges()["PARAMETER"]->getLow();
  configBuffer.setVariable("Constants", "C_INT32", &sizep);
  for (i = 0, pos = 0; i < sizem; i++)
    {
      tmpstr1 = mParameters.getParameterByUsage("MODIFIER", pos).getName();
      tmpstr2 = StringPrint("Modifier%d", i);
      configBuffer.setVariable(tmpstr2, "string", &tmpstr1);
    }
  for (i = 0, pos = 0; i < sizep; i++)
    {
      tmpstr1 = mParameters.getParameterByUsage("PARAMETER", pos).getName();
      tmpstr2 = StringPrint("Paramter%d", i);
      configBuffer.setVariable(tmpstr2, "string", &tmpstr1);
    }
  configBuffer.setVariable("FunctionName", "string", &mName);
  configBuffer.setVariable("Description", "string", &mDescription);

  //  unsigned C_INT32 Size = mUsageDescriptions.size();
  //  configBuffer.setVariable("UsageDescriptionSize", "C_INT32", &Size);
  //  mUsageDescriptions.save(configBuffer);
  //  mParameters.save(configBuffer);
}

void CFunction::setName(const string& name)
{
  mName = name;
}

const string & CFunction::getName() const
  {
    return mName;
  }

void CFunction::setDescription(const string & description)
{
  mDescription = description;
}

const string & CFunction::getDescription() const
  {
    return mDescription;
  }

void CFunction::setType(const CFunction::Type & type)
{
  mType = type;
}

const CFunction::Type & CFunction::getType() const
  {
    return mType;
  }

void CFunction::setReversible(const TriLogic & reversible)
{
  mReversible = reversible;
}

const TriLogic & CFunction::isReversible() const
  {
    return mReversible;
  }

CFunctionParameters & CFunction::getParameters()
{
  return mParameters;
}

CCopasiVectorNS < CUsageRange > & CFunction::getUsageDescriptions()
{
  return mUsageDescriptions;
}

unsigned C_INT32 CFunction::getParameterPosition(const string & name)
{
  return mParameters[0] - mParameters[name];
}

C_FLOAT64 CFunction::calcValue(const CCallParameters & callParameters) const
  {
    return 0.0;
  }

void CFunction::addUsage(const string& usage, C_INT32 low, C_INT32 high)
{
  CUsageRange *u;
  u = new CUsageRange();
  u->setUsage(usage);
  u->setLow(low);
  u->setHigh(high);
  mUsageDescriptions.add(u);
}

void CFunction::addParameter(const string & name, const CFunctionParameter::DataType & type,
                             const string & usage)
{
  mParameters.add(name, type, usage);
}
