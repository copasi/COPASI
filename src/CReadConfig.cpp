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

// char *InitInputBuffer(char *name);
// static long GetFileSize(const char *name);

CReadConfig::CReadConfig(void)
{
    // initialize everything
    mLineNumber   = 0;
    mMode         = CReadConfig::NEXT;
    mFail         = 0;

    InitInputBuffer();
}

CReadConfig::CReadConfig(const string& name)
{
    // initialize everything
    mFilename     = name;
    mLineNumber   = 0;
    mMode         = CReadConfig::NEXT;
    mFail         = 0;

    InitInputBuffer();
    
    GetVariable("Version", "string", &mVersion);
}

CReadConfig::~CReadConfig(void)
{
}

long CReadConfig::Fail()
{
    // return the failure state
    return mFail;
}

string CReadConfig::GetVersion() {return mVersion;}

long CReadConfig::GetVariable(const string& name, 
                              const string& type, 
                              void * pout,
                              enum Mode mode)
{
    char c[] = " ";
    long equal = 0;
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
            if ( LookAhead() != "Volume" )
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
                    CCopasiMessage(CCopasiMessage::ERROR, 1, name.c_str(),
                                   mFilename.c_str(), mLineNumber);

                // Rewind the buffer                
                mode = CReadConfig::SEARCH;
                mBuffer.clear();
                mBuffer.seekg(0);
                mLineNumber = 0;
            }
            continue;
        }

        // We should never reach this line!!!
        CCopasiMessage(CCopasiMessage::ERROR, 1, name.c_str(),
                       mFilename.c_str(), mLineNumber);
    }
    
    // Return the value depending on the type
    if ( type == "string" )
    {
        *(string *) pout = Value;
    }
    else if ( type == "double" )
    {
        // may be we should check if Value is really a double
        *(double *) pout = atof(Value.c_str());
    }
    else if ( type == "long" )
    {
        // may be we should check if Value is really a integer
        *(long *) pout = atoi(Value.c_str());
    }
    else if ( type == "short" )
    {
        // may be we should check if Value is really a integer
        *(short *) pout = atoi(Value.c_str());
    }
    else
    {
        CCopasiMessage(CCopasiMessage::ERROR, 5, type.c_str(), name.c_str());
        mFail = 1; //Error
    }
    
    return mFail;
}

long CReadConfig::GetVariable(const string& name, 
                              const string& type, 
                              void * pout1,
                              void * pout2,
                              enum Mode mode)
{
    string Value;
    
    if (mFail = GetVariable(name, "string", &Value, mode))
        return mFail;
    
    if (type == "node")
    {
        long komma = 0;
        
        komma = Value.find(",");
        string Type = Value.substr(0, komma);
        *(long *) pout1 = atoi(Type.c_str());

        string Subtype = Value.substr(komma + 1);
        *(long *) pout2 = atoi(Subtype.c_str());
    }
    else
    {
        CCopasiMessage(CCopasiMessage::ERROR, 5, type.c_str(), name.c_str());
        mFail = 1; //Error
    }
    
    return mFail;
}

long CReadConfig::InitInputBuffer()
{
    char c[] = " ";
    
    // read the configuration file into the configuration buffer
    ifstream File(mFilename.c_str());
    if (File.fail()) 
        CCopasiMessage(CCopasiMessage::ERROR, 2, mFilename.c_str());

    while (TRUE)
    {
        File.read(c, 1);
        if (File.eof()) break;
        if (File.fail())
            CCopasiMessage(CCopasiMessage::ERROR, 3, mFilename.c_str());
        mBuffer << c;
    }
    File.clear();
    
    File.close();
    if (File.fail())
        CCopasiMessage(CCopasiMessage::ERROR, 4, mFilename.c_str());
    
    return mFail;
}

string CReadConfig::LookAhead()
{
    streampos pos = mBuffer.tellg();
    
    string Line;
    mBuffer >> Line;
    mBuffer.seekg(pos);
    
    return Line.substr(0, Line.find("="));
}
