// CWriteConfig
//
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001

#include <string>
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <assert.h>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "CGlobals.h"
#include "CWriteConfig.h"
#include "trajectory/CODESolver.h"

CWriteConfig::CWriteConfig(void)
{
  // initialize everything
  mFileName = "";
  mOpenMode = ios::out;
  mLineNumber = 0;
  mFail = 0;

  mBuffer.setf(ios::scientific);
  mBuffer.precision(16);
}

CWriteConfig::CWriteConfig(const string& name)
{
  // initialize everything
  mFileName = name;
  mOpenMode = ios::out;
  mLineNumber = 0;
  mFail = 0;

  mBuffer.setf(ios::scientific);
  mBuffer.precision(16);

  if (Copasi)
    setVariable("Version", "string", &Copasi->ProgramVersion.getVersion());
  else
    {
      string Version("4.0.0");
      setVariable("Version", "string", &Version);
    }
}

CWriteConfig::~CWriteConfig(void)
{
  commit();
}

C_INT32 CWriteConfig::flush(void)
{
  if (commit())
    {
      fatalError();
      return mFail;
    }

  mBuffer.freeze(0);
  mBuffer.seekp(0);

  return mFail;
}

C_INT32 CWriteConfig::commit(void)
{
#ifdef WIN32
  mOpenMode |= ios::binary;
#endif

  ofstream ConfigFile(mFileName.c_str(), mOpenMode);

  if (ConfigFile.fail())
    {
      fatalError();
      return mFail = 1;
    }

  ConfigFile.write(mBuffer.str(), mBuffer.pcount());

  if (ConfigFile.fail())
    {
      fatalError();
      return mFail = 1;
    }

  mOpenMode |= ios::app;
  return mFail;
}

void CWriteConfig::setDefaults()
{
  CODESolver::saveLSODAParameters(*this);
}

C_INT32 CWriteConfig::fail()
{
  // return the failure state
  return mFail;
}

C_INT32 CWriteConfig::setVariable(const string & name,
                                  const string & type,
                                  const void *pout)
{
  mBuffer << name;

  if (pout)
    {
      if (type != "multiline")
        mBuffer << "=";

      // Return the value depending on the type
      if (type == "string")
        {
          mBuffer << *(string *) pout;
        }
      else if (type == "C_FLOAT64")
        {
          mBuffer << *(C_FLOAT64 *) pout;
        }
      else if (type == "C_INT32")
        {
          mBuffer << *(C_INT32 *) pout;
        }
      else if (type == "C_INT16")
        {
          mBuffer << *(C_INT16 *) pout;
        }
      else if (type == "bool")
        {
          mBuffer << *(bool *) pout;
        }
      else if (type == "multiline")
        {
          mBuffer << endl;
          mBuffer << *(string *) pout << endl;
          mBuffer << "End" << name;
        }
      else
        {
          fatalError();
          mFail = 1; //Error
        }
    }

  mBuffer << endl;
  mLineNumber++;

  return mFail;
}

C_INT32 CWriteConfig::setVariable(const string & name,
                                  const string & type,
                                  const void *pout1,
                                  const void *pout2)
{
  mBuffer << name << "=";

  // Return the value depending on the type

  if (type == "node")
    {
      // pout1 and pout2 point to chars mType and mSubtype.
      // Therfore, we need this complicated cast.
      mBuffer << (C_INT32) (*(char *) pout1) << ","
      << (C_INT32) (*(char *) pout2)
      //  This will help to debug
      //  << "\t" << *(char *) pout1 << "," << *(char *) pout2
      ;
    }
  else
    {
      fatalError();
      mFail = 1; //Error
    }

  mBuffer << endl;
  mLineNumber++;

  return mFail;
}
