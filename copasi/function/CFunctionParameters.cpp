/**
 * CFunctionParameters
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CFunctionParameters.h"
CFunctionParameters::CFunctionParameters() {CONSTRUCTOR_TRACE; }

CFunctionParameters::CFunctionParameters(const CFunctionParameters & src)
{
  CONSTRUCTOR_TRACE;
  mParameters = CCopasiVectorNS < CFunctionParameter >(src.mParameters);
  mUsageRanges = CCopasiVectorNS < CUsageRange >(src.mUsageRanges);
}
CFunctionParameters::~CFunctionParameters(){DESTRUCTOR_TRACE; }

void CFunctionParameters::cleanup()
{
  mParameters.cleanup();
  mUsageRanges.cleanup();
}

void CFunctionParameters::load(CReadConfig & configBuffer,
                               CReadConfig::Mode mode)
{
  unsigned C_INT32 Size;

  configBuffer.getVariable("ParameterSize", "C_INT32", &Size, mode);
  mParameters.load(configBuffer, Size);

  configBuffer.getVariable("UsageParameterSize", "C_INT32", &Size);
  mUsageRanges.load(configBuffer, Size);
}

void CFunctionParameters::save(CWriteConfig & configBuffer)
{
  unsigned C_INT32 Size = mParameters.size();
  configBuffer.setVariable("ParameterSize", "C_INT32", &Size);
  mParameters.save(configBuffer);

  Size = mUsageRanges.size();
  configBuffer.setVariable("UsageParameterSize", "C_INT32", &Size);
  mUsageRanges.save(configBuffer);
}

void CFunctionParameters::add
  (const CFunctionParameter & parameter)
  {
    mParameters.add(parameter);
    updateUsageRanges();
  }

void CFunctionParameters::add
  (CFunctionParameter * parameter)
  {
    mParameters.add(parameter);
    updateUsageRanges();
  }

void

CFunctionParameters::add
  (const string & name,
   const CFunctionParameter::DataType & type,
   const string & usage)
  {
    CFunctionParameter *parameter
    = new CFunctionParameter(name, type, usage);
    mParameters.add(parameter);
    updateUsageRanges();
  }

void CFunctionParameters::remove
  (const string & name)
  {
    mParameters.remove(name);
    updateUsageRanges();
  }

CFunctionParameter * & CFunctionParameters::operator[](unsigned C_INT32 index)
{return mParameters[index]; }

/*
const CFunctionParameter * & 
CFunctionParameters::operator[](unsigned C_INT32 index) const
{return mParameters[index]; }
 */

CFunctionParameter * CFunctionParameters::operator[](const string &name)
{ return mParameters[name]; }
unsigned C_INT32 CFunctionParameters::size() const { return mParameters.size(); }

CCopasiVectorNS < CUsageRange > & CFunctionParameters::getUsageRanges()
{ return mUsageRanges; }

CFunctionParameter &
CFunctionParameters::getParameterByUsage(const string & usage,
    unsigned C_INT32 & pos)
{
  unsigned C_INT32 i, imax = mParameters.size();

  for (i = pos; i < imax; i++, pos)
    if (mParameters[i]->getUsage() == usage)
      {
        pos = i + 1;
        return *mParameters[i];
      }

  CCopasiMessage(CCopasiMessage::ERROR,
                 MCFunctionParameters + 2,
                 usage.c_str(), pos);
  // This line is never reached!
  return *mParameters[i];
}

void CFunctionParameters::updateUsageRanges()
{
  unsigned C_INT32 i, imax = mParameters.size();

  CUsageRange * pUsageRange = NULL;
  CUsageRange UsageRange;

  string Usage;
  CFunctionParameter::DataType Type;

  mUsageRanges.cleanup();

  for (i = 0; i < imax; i++)
    {
      Usage = mParameters[i]->getUsage();
      Type = mParameters[i]->getType();

      try
        {
          pUsageRange = mUsageRanges[Usage];
        }

      catch (CCopasiException Exception)
        {
          /* Usage not found */

          if ((MCCopasiVector + 1) == Exception.getMessage().getNumber())
            {
              if (Type < CFunctionParameter::VINT16)
                {
                  /* Non vectors are assumed to have a fixed number
                     of elements */
                  UsageRange.setRange(1, CRange::NoRange);
                  UsageRange.setUsage(Usage);
                  mUsageRanges.add(UsageRange);
                }
              else
                {
                  /* Vectors are assumed to have an arbitrary
                     number of elements */
                  UsageRange.setRange(0, CRange::Infinity);
                  UsageRange.setUsage(Usage);
                  mUsageRanges.add(UsageRange);
                }

              pUsageRange = NULL;
            }
          else
            throw Exception;
        }

      if (pUsageRange)
        {
          if (CFunctionParameter::VINT16 <= Type)
            CCopasiMessage(CCopasiMessage::ERROR, MCFunctionParameters + 1,
                           Usage.c_str(), Type);

          pUsageRange->setLow(pUsageRange->getLow() + 1);
        }
    }
}

ostream & operator<<(ostream &os, const CFunctionParameters & d)
{
  os << "++++CFunctionParameters: " << endl;
  os << "    CFunctionParameters.mParameters " << endl << d.mParameters ;
  os << "    CFunctionParameters.mUsageRanges " << endl << d.mUsageRanges ;
  os << "----CFunctionParameters " << endl;

  return os;
}
