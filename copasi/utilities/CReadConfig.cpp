// CReadConfig
// 
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001

//#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

#include <assert.h>

#include "copasi.h"
#include "CCopasiMessage.h"
#include "CReadConfig.h"

// char *initInputBuffer(char *name);
// static C_INT32 GetFileSize(const char *name);

CReadConfig::CReadConfig(void)
{
  // initialize everything
  mLineNumber   = 0;
  mMode         = CReadConfig::NEXT;
  mFail         = 0;

  initInputBuffer();
}

CReadConfig::CReadConfig(const string& name)
{
  // initialize everything
  mFilename     = name;  
  mLineNumber   = 0;
  mMode         = CReadConfig::NEXT;
  mFail         = 0;

  initInputBuffer();
    
  getVariable("Version", "string", &mVersion);
}

CReadConfig::~CReadConfig(void)
{
}

C_INT32 CReadConfig::fail()
{
  // return the failure state
  return mFail;
}

string CReadConfig::getVersion() {return mVersion;}

C_INT32 CReadConfig::getVariable(const string& name, 
                                 const string& type, 
                                 void * pout,
                                 enum Mode mode)
{
  char c[] = " ";
  C_INT32 equal = 0;
  string Line;
  string Name;
  string Value;

  mode = (mode & CReadConfig::LOOP) ? CReadConfig::ALL: mode;
    
  // Get the current line 
  while (TRUE)
    {

      Line.erase();

      // Read a line form the input buffer
      mLineNumber++;
      while (TRUE)
        {
	  mBuffer.read(c, 1);
	  if ( *c == '\n' || mBuffer.eof()) break;

	  //YH: here we need to delete ^M carriage return, it is \r
	  if ( *c == '\r' ) 
		continue;
	 
	  Line += c;
        }

      equal = Line.find('=');
      Name  = Line.substr(0, equal);

      Value = Line.substr(equal + 1);

      // The Compartment keyword is used twice. So we must determine by
      // the context if we have found the correct one in the case the mode
      // is SEARCH.
      if (mode & CReadConfig::SEARCH          &&
	  name == "Compartment"  &&
	  Name == "Compartment")
        {
	  if ( lookAhead() != "Volume" )
            {
	      Name = "<CONTINUE>";
            }
        }

      // The Title keyword is used twice. So we must determine by
      // the context if we have found the correct one in the case the mode
      // is SEARCH.
      if (mode & CReadConfig::SEARCH          &&
	  name == "Title"  &&
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
      if (name == Name) break;

      if (mode & CReadConfig::SEARCH) 
        {
	  if (mBuffer.eof())
            {
	      if (!(mode & CReadConfig::LOOP)) 
		CCopasiMessage(CCopasiMessage::ERROR, MCReadConfig + 1,
			       name.c_str(), mFilename.c_str(),
			       mLineNumber);

	      // Rewind the buffer                
	      mode = CReadConfig::SEARCH;
	      mBuffer.clear();
	      mBuffer.seekg(0);
	      mLineNumber = 0;
            }
	  continue;
        }

      // We should never reach this line!!!
      CCopasiMessage(CCopasiMessage::ERROR, MCReadConfig + 1, name.c_str(),
		     mFilename.c_str(), mLineNumber);
    }
    
  // Return the value depending on the type
  if ( type == "string" )
    {
      *(string *) pout = Value;
    }
  else if ( type == "C_FLOAT64" )
    {
      // may be we should check if Value is really a C_FLOAT64
      *(C_FLOAT64 *) pout = atof(Value.c_str());
    }
  else if ( type == "C_INT32" )
    {
      // may be we should check if Value is really a integer
      *(C_INT32 *) pout = atoi(Value.c_str());
    }
  else if ( type == "C_INT16" )
    {
      // may be we should check if Value is really a integer
      *(C_INT16 *) pout = atoi(Value.c_str());
    }
  else if ( type == "multiline" )
    {
      Value.erase();
        
      while (TRUE)
        {
	  Line.erase();

	  // Read a line form the input buffer
	  mLineNumber++;
	  while (TRUE)
            {
	      mBuffer.read(c, 1);
	      if ( *c == '\n' || mBuffer.eof()) break;

	      //YH: here we need to delete ^M carriage return, it is \r
	      if ( *c == '\r' ) 
		continue;

	      Line += c;
            }

	  if (Line == "End" + name) break;
            
	  if (Value.length()) Value += '\n';
	  Value += Line;
        }

      *(string *) pout = Value;
    }
  else
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCReadConfig + 5, type.c_str(),
		     name.c_str());
      mFail = 1; //Error
    }
    
  return mFail;
}

C_INT32 CReadConfig::getVariable(const string& name, 
                                 const string& type, 
                                 void * pout1,
                                 void * pout2,
                                 enum Mode mode)
{
  string Value;
    
  if ((mFail = getVariable(name, "string", &Value, mode)))
    return mFail;
    
  if (type == "node")
    {
      C_INT32 komma = 0;
	
      komma = Value.find(",");

      string Type = Value.substr(0, komma);
      * (char*) pout1 = (char) atoi(Type.c_str());

      string Subtype = Value.substr(komma + 1);
      * (char*) pout2 = (char) atoi(Subtype.c_str());
    }
  else
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCReadConfig + 5, type.c_str(),
		     name.c_str());
      mFail = 1; //Error
    }
    
  return mFail;
}

C_INT32 CReadConfig::initInputBuffer()
{
  char c[] = " ";
    
  // read the configuration file into the configuration buffer
  ifstream File(mFilename.c_str());
  if (File.fail()) 
    CCopasiMessage(CCopasiMessage::ERROR, MCReadConfig + 2,
		   mFilename.c_str());

  while (TRUE)
    {
      File.read(c, 1);
      if (File.eof()) break;
      if (File.fail())
	CCopasiMessage(CCopasiMessage::ERROR, MCReadConfig + 3,
		       mFilename.c_str());
      mBuffer << c;
    }
  File.clear();
    
  File.close();
  if (File.fail())
    CCopasiMessage(CCopasiMessage::ERROR, MCReadConfig + 4,
		   mFilename.c_str());
    
  return mFail;
}

string CReadConfig::lookAhead()
{
  streampos pos = mBuffer.tellg();
    
  string Line;
  mBuffer >> Line;
  mBuffer.seekg(pos);
    
  return Line.substr(0, Line.find("="));
}


