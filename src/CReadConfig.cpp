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
#include "CReadConfig.h"

// char *InitInputBuffer(char *name);
static long GetFileSize(const char *name);

CReadConfig::CReadConfig(void)
{
    // initialize everything
    mFilename     = "";
    mLineNumber   = 0;
    mMode         = 0;
    mFail         = 0;

    InitInputBuffer();
}

CReadConfig::CReadConfig(const string& name)
{
    // initialize everything
    mFilename     = name;
    mLineNumber   = 0;
    mMode         = 0;
    mFail         = 0;

    InitInputBuffer();
}

CReadConfig::~CReadConfig(void)
{
}

int CReadConfig::Fail()
{
    // return the failure state
    return mFail;
}


int CReadConfig::GetVariable(const string& name, 
                             const string& type, 
                             void * pout)
{
    char c[] = " ";
    int equal = 0;
    int Mode = mMode;    
    string Line;
    string Name;
    string Value;

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
        if (Mode & CReadConfig_SEARCH &&
            name == "Compartment"     &&
            Name == "Compartment")
        {
            if ( LookAhead() != "Volume" )
            {
                Name = "<CONTINUE>";
            }
        }

        // We found what we are looking for
        if (name == Name) break;

        if (Mode & CReadConfig_SEARCH) 
        {
            if (mBuffer.eof())
            {
                if (!(Mode & CReadConfig_LOOP)) FatalError();

                // Rewind the buffer                
                Mode ^= CReadConfig_LOOP;
                mBuffer.clear();
                mBuffer.seekg(0);
                mLineNumber = 0;
            }
            continue;
        }

        // We should never reach this line!!!
        FatalError();
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
    else if ( type == "int" )
    {
        // may be we should check if Value is really a integer
        *(int *) pout = atoi(Value.c_str());
    }
    else
    {
        FatalError();
        mFail = 1; //Error
    }
    
    return mFail;
}

int CReadConfig::GetVariable(const string& name, 
                             const string& type, 
                             void * pout1,
                             void * pout2)
{
    string Value;
    
    if (mFail = GetVariable(name, "string", &Value))
        return mFail;
    
    if (type == "node")
    {
        int komma = 0;
        
        komma = Value.find(",");
        string Type = Value.substr(0, komma);
        *(int *) pout1 = atoi(Type.c_str());

        string Subtype = Value.substr(komma + 1);
        *(int *) pout2 = atoi(Subtype.c_str());
    }
    else
    {
        FatalError();
        mFail = 1; //Error
    }
    
    return mFail;
}
        
void CReadConfig::SetMode(int mode)
{
    switch (mode)
    {
    case  CReadConfig_SEARCH:
        mMode |= CReadConfig_SEARCH;
        break;
    case -CReadConfig_SEARCH:
        if (mMode & CReadConfig_SEARCH) mMode ^= CReadConfig_SEARCH;
        break;
    case  CReadConfig_LOOP:
        mMode |= CReadConfig_LOOP;
        break;
    case -CReadConfig_LOOP:
        if (mMode & CReadConfig_LOOP) mMode ^= CReadConfig_LOOP;
        break;
    default:
        // Invalid Mode
        FatalError();
        break;
    }
}

int CReadConfig::InitInputBuffer()
{
    char c[] = " ";
    
    // read the configuration file into the configuration buffer
    ifstream File(mFilename.c_str());
    if (File.fail()) FatalError();

    while (TRUE)
    {
        File.read(c, 1);
        if (File.eof()) break;
        if (File.fail()) FatalError();
        mBuffer << c;
    }
    File.clear();
    
    File.close();
    if (File.fail()) FatalError();
    
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

    
    
