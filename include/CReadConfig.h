/**
 *  CReadConfig class. A more elaborate class description.
 */

// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001


#ifndef COPASI_CReadConfig
#define COPASI_CReadConfig

class CReadConfig
{
public:
    /**
     *  Default constructor. 
     *  This opens the configuration file using a the default filename 
     *  "test.txt".
     */
    CReadConfig();
    /**
     *  Specified constructor. 
     *  This opens the configuration file using the filename specified 
     *  as the argument.
     *  @param name name of the confguration file. 
     */
    CReadConfig(string name);
    /**
     *  Destructor. 
     *  The destructor calls the method Free().
     */
    ~CReadConfig();
    /**
     *  Frees all allocated memory. 
     *  This method is called by the destructor.
     */
    Free();
    /**
     *  Returns the failure status.
     *  @return mFail
     *  @see mFail  
     */
    Fail();
    /**
     *  Retrieves the next variable from the input file.
     *  @param name name of the variable to be retrieved.
     *  @param type type of the variable to be retrieved.
     *  @param *pout pointer to the location where the retrieved variable 
     *               is stored.
     *  @return mFail
     *  @see mFail  
     */
    GetVariable(string name, string type, void * pout);

private:
    /**
     *  Initializes the input buffer for reading.
     */
    InitInputBuffer();
    /**
     *  Name of the configuration file.
     */
    string mFilename;               // Config File Name
    /**
     *  Begin of the input buffer
     */
    char*  mpBufferBegin;           // Input Buffer
    /**
     *  Current position in the input buffer
     */
    char*  mpBufferPos;             // Current Position
    /**
     *  Current line number in the configuration file
     */
    long   mLineNumber;             // Current Line Number 
    /**
     *  Failure status:
     *  0 = no error
     *  !0 = error
     */
    int    mFail;                   // Failure State
};
#endif // COPASI_CReadConfig

