/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunction.cpp,v $
   $Revision: 1.52 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/11/24 15:45:55 $
   End CVS Header */

#include "copasi.h"

#include "CFunction.h"

CFunction::CFunction(const std::string & name,
                     const CCopasiContainer * pParent,
                     const CEvaluationTree::Type & type):
    CEvaluationTree(name, pParent, type),
    mVariables(),
    mUsageDescriptions(),
    mpCallParameters(NULL),
    mReversible(TriUnspecified)
{}

CFunction::CFunction(const CFunction & src,
                     const CCopasiContainer * pParent):
    CEvaluationTree(src, pParent),
    mVariables(src.mVariables),
    mUsageDescriptions(src.mUsageDescriptions),
    mpCallParameters(NULL),
    mReversible(src.mReversible)
{}

CFunction::~CFunction()
{}

bool CFunction::setInfix(const std::string & infix)
{
  if (!CEvaluationTree::setInfix(infix)) return false;
  if (!initVariables()) return false;

  return true;
}

bool CFunction::compile()
{return compileNodes();}

unsigned C_INT32 CFunction::getVariableIndex(const std::string & name) const
  {
    CFunctionParameter::DataType VariableType;
    return mVariables.findParameterByName(name, VariableType);
  }

const C_FLOAT64 & CFunction::getVariableValue(const unsigned C_INT32 & index) const
  {return *(*mpCallParameters)[index].value;}

void CFunction::setReversible(const TriLogic & reversible)
{mReversible = reversible;}

const TriLogic & CFunction::isReversible() const
  {return mReversible;}

CFunctionParameters & CFunction::getVariables()
{return mVariables;}

const CFunctionParameters & CFunction::getVariables() const
  {return mVariables;}

bool CFunction::addVariable(const std::string & name,
                            const std::string & usage,
                            const CFunctionParameter::DataType & type)
{return mVariables.add(name, type, usage);}

CCopasiVectorN < CUsageRange > & CFunction::getUsageDescriptions()
{return mUsageDescriptions;}

const CCopasiVectorN < CUsageRange > & CFunction::getUsageDescriptions() const
  {return mUsageDescriptions;}

const C_FLOAT64 & CFunction::calcValue(const CCallParameters<C_FLOAT64> & callParameters)
{
  mpCallParameters = & callParameters;

  try
    {
      return mValue = mpRoot->value();
    }
  catch (...)
    {
      return mValue = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }
}

bool CFunction::dependsOn(const C_FLOAT64 * parameter,
                          const CCallParameters<C_FLOAT64> & callParameters) const
  {
    CCallParameters<C_FLOAT64>::const_iterator it = callParameters.begin();
    CCallParameters<C_FLOAT64>::const_iterator end = callParameters.end();

    while (it != end && parameter != it->value) it++;

    if (it != end)
      return true;
    else
      return false;
  }

void CFunction::addUsage(const std::string& usage,
                         const unsigned C_INT32 & lowerBound,
                         const unsigned C_INT32 & upperBound)
{
  CUsageRange *u;
  u = new CUsageRange();
  u->setUsage(usage);
  u->setLow(lowerBound);
  u->setHigh(upperBound);
  mUsageDescriptions.add(u);
}

void CFunction::load(CReadConfig & configBuffer,
                     CReadConfig::Mode mode)
{
  //  cleanup();

  C_INT32 Type;
  CUsageRange UsageDescription;

  mode = CReadConfig::SEARCH;
  configBuffer.getVariable("User-defined", "C_INT32", &Type, mode);

  switch (Type)
    {
    case 1:
      setType(UserDefined);
      break;

    default:
      fatalError();
    }

  configBuffer.getVariable("Reversible", "C_INT32", &mReversible);

  configBuffer.getVariable("Substrates", "C_INT32", &Type);
  UsageDescription.setUsage("SUBSTRATE");
  if (Type == 0)
    UsageDescription.setRange(Type, CRange::Infinity);
  else
    UsageDescription.setRange(Type);

  if (!mUsageDescriptions.add(UsageDescription) &&
      CCopasiMessage::peekLastMessage().getNumber() == MCCopasiVector + 2)
    CCopasiMessage::getLastMessage();

  configBuffer.getVariable("Products", "C_INT32", &Type);
  UsageDescription.setUsage("PRODUCT");
  if (Type == 0)
    UsageDescription.setRange(Type, CRange::Infinity);
  else
    UsageDescription.setRange(Type);

  if (!mUsageDescriptions.add(UsageDescription) &&
      CCopasiMessage::peekLastMessage().getNumber() == MCCopasiVector + 2)
    CCopasiMessage::getLastMessage();

  mode = CReadConfig::SEARCH;

  std::string tmp;
  configBuffer.getVariable("FunctionName", "string", &tmp, mode);
  setObjectName(tmp);

  configBuffer.getVariable("Description", "string", &tmp);
  setInfix(tmp);

  // For older file version the parameters have to be build from information
  // dependend on the function type. Luckilly, only user defined functions are
  // the only ones occuring in those files.

  guessModifierUsageRange();
}

bool CFunction::initVariables()
{
  if (mpNodeList == NULL) return false;

  std::vector< CEvaluationNode * >::iterator it
  = mpNodeList->begin();
  std::vector< CEvaluationNode * >::iterator end
  = mpNodeList->end();

  CFunctionParameters NewVariables;

  for (; it != end; ++it)
    if (CEvaluationNode::type((*it)->getType()) == CEvaluationNode::VARIABLE)
      {
        mVariables.add((*it)->getData(), CFunctionParameter::FLOAT64, "VARIABLE");
        NewVariables.add((*it)->getData(), CFunctionParameter::FLOAT64, "VARIABLE");
      }

  CFunctionParameter::DataType Type;
  unsigned C_INT32 i;
  for (i = mVariables.size() - 1; i < C_INVALID_INDEX; i--)
    if (NewVariables.findParameterByName(mVariables[i]->getObjectName(), Type) == C_INVALID_INDEX)
      mVariables.remove(mVariables[i]->getObjectName());

  return true;
}

bool CFunction::guessModifierUsageRange()
{
  unsigned C_INT32 imax = mVariables.getNumberOfParametersByUsage("MODIFIER");

  if (imax != 0)
    {
      unsigned C_INT32 pos = 0;

      if (mVariables.getParameterByUsage("MODIFIER", pos)->getType() == CFunctionParameter::VFLOAT64)
        addUsage("MODIFIER", 0, CRange::Infinity);
      else
        addUsage("MODIFIER", imax, CRange::NoRange);
    }

  return true;
}
