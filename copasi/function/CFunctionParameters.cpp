/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunctionParameters.cpp,v $
   $Revision: 1.26 $
   $Name:  $
   $Author: chlee $ 
   $Date: 2003/11/13 22:08:20 $
   End CVS Header */

/**
 * CFunctionParameters
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CFunctionParameters.h"
#include "utilities/CCopasiException.h"

CFunctionParameters::CFunctionParameters(const std::string & name,
    const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Variable Description"),
    mParameters("Variables", this),
    mUsageRanges("Usage Ranges", this)
{CONSTRUCTOR_TRACE;}

CFunctionParameters::CFunctionParameters(const CFunctionParameters & src,
    const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mParameters(src.mParameters, this),
    mUsageRanges(src.mUsageRanges, this)
{CONSTRUCTOR_TRACE;}

CFunctionParameters::~CFunctionParameters() {DESTRUCTOR_TRACE;}

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

void CFunctionParameters::add(const CFunctionParameter & parameter)
{
  mParameters.add(parameter);
  updateUsageRanges();
}

void CFunctionParameters::add(CFunctionParameter * parameter,
                              const bool & adopt)
{
  mParameters.add(parameter, adopt);
  updateUsageRanges();
}

bool CFunctionParameters::add(const std::string & name,
                              const CFunctionParameter::DataType & type,
                              const std::string & usage)
{
  if (mParameters.getIndex(name) != C_INVALID_INDEX) return false;

  CFunctionParameter *parameter
  = new CFunctionParameter(name, type, usage);
  mParameters.add(parameter);
  updateUsageRanges();
  return true;
}

void CFunctionParameters::remove(const std::string & name)
{
  mParameters.remove(name);
  updateUsageRanges();
}

CFunctionParameter * CFunctionParameters::operator[](unsigned C_INT32 index)
{return mParameters[index];}

const CFunctionParameter * CFunctionParameters::operator[](unsigned C_INT32 index) const
  {return mParameters[index];}

CFunctionParameter * CFunctionParameters::operator[](const std::string &name)
{return mParameters[name];}

const CFunctionParameter * CFunctionParameters::operator[](const std::string &name) const
  {return mParameters[name];}

unsigned C_INT32 CFunctionParameters::size() const {return mParameters.size();}

const CCopasiVectorNS < CUsageRange > & CFunctionParameters::getUsageRanges() const
  {return mUsageRanges;}

const CFunctionParameter &
CFunctionParameters::getParameterByUsage(const std::string & usage,
    unsigned C_INT32 & pos) const
  {
    unsigned C_INT32 i, imax = mParameters.size();

    for (i = pos; i < imax; i++)
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

unsigned C_INT32 CFunctionParameters::getNumberOfParametersByUsage(const std::string & usage) const
  {
    unsigned C_INT32 i, imax = mParameters.size();
    unsigned C_INT32 count = 0;

    for (i = 0; i < imax; i++)
      if (mParameters[i]->getUsage() == usage) ++count;

    return count;
  }

unsigned C_INT32 CFunctionParameters::findParameterByName(const std::string & name,
    CFunctionParameter::DataType & dataType) const
  {
    std::string VectorName = name.substr(0, name.find_last_of('_'));
    std::string Name;
    unsigned C_INT32 i, imax = mParameters.size();

    for (i = 0; i < imax; i++)
      {
        Name = mParameters[i]->getName();

        if (Name == name || Name == VectorName)
          {
            dataType = mParameters[i]->getType();
            return i;
          }
      }

    return C_INVALID_INDEX;
  }

void CFunctionParameters::updateUsageRanges()
{
  unsigned C_INT32 i, imax = mParameters.size();
  unsigned C_INT32 index;

  CUsageRange * pUsageRange = NULL;

  const std::string * Usage;
  const CFunctionParameter::DataType * Type;

  mUsageRanges.cleanup();

  for (i = 0; i < imax; i++)
    {
      Usage = &mParameters[i]->getUsage();
      Type = &mParameters[i]->getType();

      if ((index = mUsageRanges.getIndex(*Usage)) == C_INVALID_INDEX)
        {
          pUsageRange = new CUsageRange(*Usage);
          mUsageRanges.add(pUsageRange, true);

          if (*Type < CFunctionParameter::VINT32)
            {
              /* Non vectors are assumed to have a fixed number
                 of elements */
              pUsageRange->setRange(1, CRange::NoRange);
            }
          else
            {
              /* Vectors are assumed to have at least one element */
              pUsageRange->setRange(1, CRange::Infinity);
            }
        }
      else
        {
          pUsageRange = mUsageRanges[index];

          if ((CFunctionParameter::VINT32 <= *Type) ||
              (pUsageRange->getHigh() == (unsigned C_INT32) CRange::Infinity))
            CCopasiMessage(CCopasiMessage::ERROR, MCFunctionParameters + 1,
                           Usage->c_str(), Type);
          // this means a vector parameter must be the only parameter with the respective usage

          pUsageRange->setLow(pUsageRange->getLow() + 1);
        }
    }
}

bool CFunctionParameters::operator==(const CFunctionParameters & rhs) const
  {
    if (size() != rhs.size()) return false;

    C_INT32 i, imax = size();
    for (i = 0; i < imax; ++i)
      {
        if (mParameters[i]->getName() != rhs.mParameters[i]->getName()) return false;
        if (mParameters[i]->getType() != rhs.mParameters[i]->getType()) return false;
        if (mParameters[i]->getUsage() != rhs.mParameters[i]->getUsage()) return false;
      }
    return true;
  }
