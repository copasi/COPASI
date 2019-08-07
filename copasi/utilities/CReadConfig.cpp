// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// CReadConfig
//
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001

#include <sstream>
#include <stdlib.h>
#include <assert.h>

#include "copasi/copasi.h"

#include "CCopasiMessage.h"
#include "CReadConfig.h"
#include "utility.h"
#include "copasi/commandline/CLocaleString.h"

// char *initFileBuffer(char *name);
// static C_INT32 GetFileSize(const char *name);

CReadConfig::CReadConfig(void):
  mpBuffer(NULL),
  mLineNumber(-1),
  mMode(CReadConfig::NEXT),
  mFail(0),
  mVersion(),
  mFilename(),
  mFileBuffer()
{}

CReadConfig::CReadConfig(const std::string& name):
  mpBuffer(NULL),
  mLineNumber(-1),
  mMode(CReadConfig::NEXT),
  mFail(0),
  mVersion(),
  mFilename(name),
  mFileBuffer()
{
  initFileBuffer();

  getVariable("Version", "string", &mVersion);
}

CReadConfig::CReadConfig(std::istream & in):
  mpBuffer(&in),
  mLineNumber(-1),
  mMode(CReadConfig::NEXT),
  mFail(0),
  mVersion(),
  mFilename(),
  mFileBuffer()
{}

CReadConfig::~CReadConfig(void)
{}

C_INT32 CReadConfig::fail()
{
  // return the failure state
  return mFail;
}
std::string CReadConfig::getVersion() {return mVersion;}

void CReadConfig::getDefaults()
{}

C_INT32 CReadConfig::getVariable(const std::string& name,
                                 const std::string& type,
                                 void * pout,
                                 enum Mode mode)
{
  char c[] = " ";
  size_t equal = 0;
  std::string Line;
  std::string Name;
  std::string Value;

  mode = (mode & CReadConfig::LOOP) ? CReadConfig::ALL : mode;

  // Get the current line

  while (true)
    {
      Line.erase();

      // Read a line form the input buffer
      mLineNumber++;

      while (true)
        {
          mpBuffer->read(c, 1);

          if (*c == '\n' || mpBuffer->eof())
            break;

          //YH: here we need to delete ^M carriage return, it is \r
          if (*c == '\r')
            continue;

          Line += c;
        }

      equal = Line.find('=');
      Name = Line.substr(0, equal);

      Value = Line.substr(equal + 1);

      // The Compartment keyword is used twice. So we must determine by
      // the context if we have found the correct one in the case the mode
      // is SEARCH.

      if ((mode & CReadConfig::SEARCH) &&
          name == "Compartment" &&
          Name == "Compartment")
        {
          if (lookAhead() != "Volume")
            {
              Name = "<CONTINUE>";
            }
        }

      // The Title keyword is used twice. So we must determine by
      // the context if we have found the correct one in the case the mode
      // is SEARCH.
      if ((mode & CReadConfig::SEARCH) &&
          name == "Title" &&
          Name == "Title")
        {
          if ((mVersion < "4" &&
               lookAhead() != "TotalMetabolites") ||
              (mVersion >= "4" &&
               lookAhead() != "Comments"))
            {
              Name = "<CONTINUE>";
            }
        }

      // We found what we are looking for
      if (name == Name)
        break;

      if (mode & CReadConfig::SEARCH)
        {
          if (mpBuffer->eof())
            {
              if (!(mode & CReadConfig::LOOP))
                CCopasiMessage(CCopasiMessage::EXCEPTION, MCReadConfig + 1,
                               name.c_str(), mFilename.c_str(),
                               mLineNumber);

              // Rewind the buffer
              mode = CReadConfig::SEARCH;
              rewind();
            }

          continue;
        }

      // We should never reach this line!!!
      CCopasiMessage(CCopasiMessage::ERROR, MCReadConfig + 1, name.c_str(),
                     mFilename.c_str(), mLineNumber);
    }

  // Return the value depending on the type
  if (type == "string")
    {
      *(std::string *) pout = Value;
    }
  else if (type == "C_FLOAT64")
    {
      // may be we should check if Value is really a C_FLOAT64
      *(C_FLOAT64 *) pout = strToDouble(Value.c_str(), NULL);
    }
  else if (type == "C_INT32")
    {
      // may be we should check if Value is really a integer
      *(C_INT32 *) pout = atoi(Value.c_str());
    }
  else if (type == "C_INT16")
    {
      // may be we should check if Value is really a integer
      *(C_INT16 *) pout = atoi(Value.c_str());
    }
  else if (type == "bool")
    {
      // may be we should check if Value is really a integer
      *(bool *) pout = (atoi(Value.c_str()) != 0);
    }
  else if (type == "multiline")
    {
      Value.erase();

      while (true)
        {
          Line.erase();

          // Read a line form the input buffer
          mLineNumber++;

          while (true)
            {
              mpBuffer->read(c, 1);

              if (*c == '\n' || mpBuffer->eof())
                break;

              //YH: here we need to delete ^M carriage return, it is \r
              if (*c == '\r')
                continue;

              Line += c;
            }

          if (Line == "End" + name)
            break;

          if (Value.length())
            Value += '\n';

          Value += Line;
        }

      *(std::string *) pout = Value;
    }
  else
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCReadConfig + 5, type.c_str(),
                     name.c_str());
      mFail = 1; //Error
    }

  return mFail;
}

C_INT32 CReadConfig::getVariable(const std::string& name,
                                 const std::string& type,
                                 void * pout1,
                                 void * pout2,
                                 enum Mode mode)
{
  std::string Value;

  if ((mFail = getVariable(name, "string", &Value, mode)))
    return mFail;

  if (type == "node")
    {
      size_t komma = 0;

      komma = Value.find(",");

      std::string Type = Value.substr(0, komma);
      *(char*) pout1 = (char) atoi(Type.c_str());

      std::string Subtype = Value.substr(komma + 1);
      *(char*) pout2 = (char) atoi(Subtype.c_str());
    }
  else
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCReadConfig + 5, type.c_str(),
                     name.c_str());
      mFail = 1; //Error
    }

  return mFail;
}

C_INT32 CReadConfig::initFileBuffer()
{
  char c[] = " ";

  mpBuffer = & mFileBuffer;

  // read the configuration file into the configuration buffer
#ifdef WIN32
  std::ifstream File(CLocaleString::fromUtf8(mFilename).c_str(), std::ios_base::binary);
#else
  std::ifstream File(CLocaleString::fromUtf8(mFilename).c_str());
#endif

  if (File.fail())
    CCopasiMessage(CCopasiMessage::ERROR, MCReadConfig + 2,
                   mFilename.c_str());

  while (true)
    {
      File.read(c, 1);

      if (File.eof())
        break;

      if (File.fail())
        CCopasiMessage(CCopasiMessage::ERROR, MCReadConfig + 3,
                       mFilename.c_str());

      mFileBuffer << c;
    }

  File.clear();

  File.close();

  if (File.fail())
    CCopasiMessage(CCopasiMessage::ERROR, MCReadConfig + 4,
                   mFilename.c_str());

  return mFail;
}

std::string CReadConfig::lookAhead()
{
  std::streampos pos = mpBuffer->tellg();

  std::string Line;
  *mpBuffer >> Line;

  mpBuffer->seekg(pos - mpBuffer->tellg(), std::ios_base::cur);

  return Line.substr(0, Line.find("="));
}

void CReadConfig::rewind()
{
  mpBuffer->clear();
  mpBuffer->seekg(0, std::ios_base::beg);
  mLineNumber = 0;

  return;
}
