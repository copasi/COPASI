/**
 * CFunctionParameter
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CFunctionParameter.h"

const string CFunctionParameter::DataTypeName[] =
  {
    "INT16", "INT32", "UINT16", "UINT32", "FLOAT32", "FLOAT64",
    "VINT16", "VINT32", "VUINT16", "VUINT32", "VFLOAT32", "VFLOAT64"
  };

CFunctionParameter::CFunctionParameter()
{
  CONSTRUCTOR_TRACE;
  mName = "untitled";
  mType = (CFunctionParameter::DataType) - 1;
  mUsage = "unknown";
}

CFunctionParameter::CFunctionParameter(const CFunctionParameter & src)
{
  CONSTRUCTOR_TRACE;
  mName = src.mName;
  mType = src.mType;
  mUsage = src.mUsage;
}

CFunctionParameter::CFunctionParameter(const string & name,
                                       const CFunctionParameter::DataType &type,
                                       const string & usage)
{
  CONSTRUCTOR_TRACE;
  mName = name;
  mType = type;
  mUsage = usage;
}
CFunctionParameter::~CFunctionParameter(){DESTRUCTOR_TRACE; }
void CFunctionParameter::cleanup() {}

void CFunctionParameter::load(CReadConfig & configbuffer,
                              CReadConfig::Mode mode)
{
  configbuffer.getVariable("FunctionParameter", "string", &mName, mode);
  configbuffer.getVariable("DataType", "C_INT32", &mType);
  configbuffer.getVariable("Usage", "string", &mUsage);
}

void CFunctionParameter::save(CWriteConfig & configbuffer)
{
  configbuffer.setVariable("FunctionParameter", "string", &mName);
  configbuffer.setVariable("DataType", "C_INT32", &mType);
  configbuffer.setVariable("Usage", "string", &mUsage);
}
void CFunctionParameter::setName(const string & name){mName = name; }
const string & CFunctionParameter::getName() const { return mName; }

void CFunctionParameter::setUsage(const string & usage)
{mUsage = usage; }

const string & CFunctionParameter::getUsage() const
  { return mUsage; }

void
CFunctionParameter::setType(const CFunctionParameter::DataType & type)
{mType = type; }

const CFunctionParameter::DataType &
CFunctionParameter::getType() const
  { return mType; }
