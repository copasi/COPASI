/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CWriteConfig.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:04 $
   End CVS Header */

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
#include "CCopasiMessage.h"

CWriteConfig::CWriteConfig(void)
{
  // initialize everything
  mFileName = "";
  mOpenMode = std::ios_base::out;
  mLineNumber = 0;
  mFail = 0;

  mBuffer.setf(std::ios_base::scientific);
  mBuffer.precision(16);
}

CWriteConfig::CWriteConfig(const std::string& name, std::ios_base::openmode mode)
{
  // initialize everything
  mFileName = name;
  mOpenMode = mode;
  mLineNumber = 0;
  mFail = 0;

  mBuffer.setf(std::ios_base::scientific);
  mBuffer.precision(16);

  if (mOpenMode & std::ios_base::out)
    writeVersion();
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

  mBuffer.str("");  // We need to reset the string buffer.

  return mFail;
}

C_INT32 CWriteConfig::commit(void)
{
#ifdef WIN32
  mOpenMode |= std::ios_base::binary;
#endif

  std::ofstream ConfigFile(mFileName.c_str(), mOpenMode);

  if (ConfigFile.fail())
    {
      fatalError();
      return mFail = 1;
    }

  ConfigFile << mBuffer.str();

  if (ConfigFile.fail())
    {
      fatalError();
      return mFail = 1;
    }

  mOpenMode |= std::ios_base::app;
  return mFail;
}

void CWriteConfig::setDefaults()
{}

C_INT32 CWriteConfig::fail()
{
  // return the failure state
  return mFail;
}

C_INT32 CWriteConfig::setVariable(const std::string & name,
                                  const std::string & type,
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
          mBuffer << *(std::string *) pout;
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
          mBuffer << (*(bool *) pout) ? 1 : 0;
        }
      else if (type == "multiline")
        {
          mBuffer << std::endl;
          mBuffer << *(std::string *) pout << std::endl;
          mBuffer << "End" << name;
        }
      else
        {
          fatalError();
          mFail = 1; //Error
        }
    }

  mBuffer << std::endl;
  mLineNumber++;

  return mFail;
}

C_INT32 CWriteConfig::setVariable(const std::string & name,
                                  const std::string & type,
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

  mBuffer << std::endl;
  mLineNumber++;

  return mFail;
}

void CWriteConfig::writeVersion(void)
{
  if (Copasi)
    setVariable("Version", "string", &Copasi->ProgramVersion.getVersion());
  else
    {
      std::string Version("4.0.0");
      setVariable("Version", "string", &Version);
    }
}
