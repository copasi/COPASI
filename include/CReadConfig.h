// CReadConfig
// 
// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001


#ifndef COPASI_CReadConfig
#define COPASI_CReadConfig

class CReadConfig
{
public:
    CReadConfig();
    CReadConfig(string name);
    ~CReadConfig();
    Free();
    Fail();
    GetVariable(string name, string type, void * pout);

private:
    InitInputBuffer();
    string mFilename;               // Config File Name
    char*  mpBufferBegin;           // Input Buffer
    char*  mpBufferPos;             // Current Position
    long   mLineNumber;             // Current Line Number 
    int    mFail;                   // Failure State
};
#endif // COPASI_CReadConfig
