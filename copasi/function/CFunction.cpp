/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunction.cpp,v $
   $Revision: 1.36 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/11 20:40:32 $
   End CVS Header */

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
#include "utilities/utility.h"
#include "report/CKeyFactory.h"

const std::string CFunction::TypeName[] =
  {"predefined", "predefined", "predefined", "userdefined", "userdefined", ""};

const char* CFunction::XMLType[] =
  {"Base", "MassAction", "PreDefined", "UserDefined", "Expression", NULL};

CFunction * CFunction::createFunction(const CFunction * pFunction)
{
  CFunction * pNewFunction = NULL;

  switch (pFunction->getType())
    {
    case Base:
      pNewFunction = new CFunction(* (CFunction *) pFunction);
      break;

    case MassAction:
      pNewFunction = new CMassAction(* (CMassAction *) pFunction);
      break;

    case PreDefined:
      pNewFunction = new CKinFunction(* (CKinFunction *) pFunction);
      pNewFunction->setType(PreDefined);
      break;

    case UserDefined:
      pNewFunction = new CKinFunction(* (CKinFunction *) pFunction);
      break;

    case Expression:
      //      pFunction = new
      //      break;

    default:
      fatalError();
    }
  return pNewFunction;
}

CFunction * CFunction::createFunction(enum CFunction::Type type)
{
  CFunction * pFunction = NULL;

  switch (type)
    {
    case Base:
      pFunction = new CFunction();
      break;

    case MassAction:
      pFunction = new CMassAction();
      break;

    case PreDefined:
      pFunction = new CKinFunction();
      pFunction->setType(PreDefined);
      break;

    case UserDefined:
      pFunction = new CKinFunction();
      break;

    case Expression:
      //      pFunction = new
      //      break;

    default:
      fatalError();
    }
  return pFunction;
}

CFunction::CFunction(const std::string & name,
                     const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Function"),
    mType(CFunction::Base),
    mKey(GlobalKeys.add("Function", this)),
    mDescription(),
    mReversible(TriUnspecified),
    mUsageDescriptions("Usage Descriptions", this),
    mParameters("Variable Descriptions", this)
{CONSTRUCTOR_TRACE;}

CFunction::CFunction(const CFunction & src,
                     const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mType(src.mType),
    mKey(GlobalKeys.add("Function", this)),
    mDescription(src.mDescription),
    mReversible(src.mReversible),
    mUsageDescriptions(src.mUsageDescriptions, this),
    mParameters(src.mParameters, this)
{CONSTRUCTOR_TRACE;}

CFunction::~CFunction()
{
  GlobalKeys.remove(mKey);
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
      if (Type == 0)
        UsageDescription.setRange(Type, CRange::Infinity);
      else
        UsageDescription.setRange(Type);
      mUsageDescriptions.add(UsageDescription);

      configBuffer.getVariable("Products", "C_INT32", &Type);
      UsageDescription.setUsage("PRODUCTS");
      if (Type == 0)
        UsageDescription.setRange(Type, CRange::Infinity);
      else
        UsageDescription.setRange(Type);
      mUsageDescriptions.add(UsageDescription);

      mode = CReadConfig::SEARCH;
    }
  else
    {
      configBuffer.getVariable("FunctionType", "C_INT32", &mType, mode);
      mode = CReadConfig::NEXT;
    }

  std::string tmp;
  configBuffer.getVariable("FunctionName", "string", &tmp, mode);
  setObjectName(tmp);

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

  guessModifierUsageRange();
}

/*void CFunction::save(CWriteConfig & configBuffer)
{
  std::string tmp;
  configBuffer.setVariable("FunctionType", "C_INT32", &mType);
  tmp = getObjectName();
  configBuffer.setVariable("FunctionName", "string", &tmp);
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
  std::string tmpstr1, tmpstr2;
  CCopasiVectorNS < CUsageRange > tmpusage;
 
  if (mType == UserDefined)
    dummy = 1;
  else
    dummy = 0;
  tmpstr1 = getObjectName();
  configBuffer.setVariable("UDKType", "string", &tmpstr1);
  configBuffer.setVariable("User-defined", "C_INT32", &dummy);
  configBuffer.setVariable("Reversible", "C_INT32", &mReversible);
  dummy = mUsageDescriptions["SUBSTRATES"]->getLow();
  configBuffer.setVariable("Substrates", "C_INT32", &dummy);
  dummy = mUsageDescriptions["PRODUCTS"]->getLow();
  configBuffer.setVariable("Products", "C_INT32", &dummy);
  tmpusage = mParameters.getUsageRanges();
  i = tmpusage.getIndex("MODIFIER");
  if (i == -1)
    sizem = 0;
  else
    sizem = tmpusage[i]->getLow();
  configBuffer.setVariable("Modifiers", "C_INT32", &sizem);
  sizep = mParameters.getUsageRanges()["PARAMETER"]->getLow();
  configBuffer.setVariable("Constants", "C_INT32", &sizep);
  for (i = 0, pos = 0; i < sizem; i++)
    {
      tmpstr1 = mParameters.getParameterByUsage("MODIFIER", pos).getObjectName();
      tmpstr2 = StringPrint("Modifier%d", i);
      configBuffer.setVariable(tmpstr2, "string", &tmpstr1);
    }
  for (i = 0, pos = 0; i < sizep; i++)
    {
      tmpstr1 = mParameters.getParameterByUsage("PARAMETER", pos).getObjectName();
      tmpstr2 = StringPrint("Parameter%d", i);
      configBuffer.setVariable(tmpstr2, "string", &tmpstr1);
    }
  tmpstr1 = getObjectName();
  configBuffer.setVariable("FunctionName", "string", &tmpstr1);
  configBuffer.setVariable("Description", "string", &mDescription);
}*/

/*std::string CFunction::getSBMLString(const std::vector< std::vector< std::string > > & C_UNUSED(callParameterNames),
                                     const std::string & C_UNUSED(r)) const
  {return "0";}*/

const std::string & CFunction::getKey() const {return mKey;}

bool CFunction::setName(const std::string& name) {return setObjectName(name);}

void CFunction::setDescription(const std::string & description) {mDescription = description;}

const std::string & CFunction::getDescription() const {return mDescription;}

void CFunction::setType(const CFunction::Type & type) {mType = type;}

const CFunction::Type & CFunction::getType() const {return mType;}

void CFunction::setReversible(const TriLogic & reversible) {mReversible = reversible;}

const TriLogic & CFunction::isReversible() const {return mReversible;}

CFunctionParameters & CFunction::getParameters() {return mParameters;}

const CFunctionParameters & CFunction::getParameters() const
  {return mParameters;}

CCopasiVectorNS < CUsageRange > & CFunction::getUsageDescriptions()
{return mUsageDescriptions;}

const CCopasiVectorNS < CUsageRange > & CFunction::getUsageDescriptions() const
  {return mUsageDescriptions;}

C_FLOAT64 CFunction::calcValue(const CCallParameterPointers & C_UNUSED(callParameters)) const
  {return 0.0;}

bool CFunction::dependsOn(const void * C_UNUSED(parameter),
                          const CCallParameterPointers & C_UNUSED(callParameters)) const
  {return false;}

void CFunction::addUsage(const std::string& usage, C_INT32 low, C_INT32 high)
{
  CUsageRange *u;
  u = new CUsageRange();
  u->setUsage(usage);
  u->setLow(low);
  u->setHigh(high);
  mUsageDescriptions.add(u);
}

bool CFunction::addParameter(const std::string & name,
                             const CFunctionParameter::DataType & type,
                             const std::string & usage)
{return mParameters.add(name, type, usage);}

void CFunction::guessModifierUsageRange()
{
  unsigned C_INT32 pos, imax;

  imax = mParameters.getNumberOfParametersByUsage("MODIFIER");

  if (!imax) return;

  pos = 0;
  if (mParameters.getParameterByUsage("MODIFIER", pos).getType() == CFunctionParameter::VFLOAT64)
  {addUsage("MODIFIER", 0, CRange::Infinity);}
  else
  {addUsage("MODIFIER", imax, CRange::NoRange);}
}

void CFunction::writeMathML(std::ostream & out) const
  {
    out << "!!!" << std::endl;
  }
