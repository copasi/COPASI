/**
 *  CWriteConfig class. A more elaborate class description.
 */

// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001


#ifndef COPASI_CWriteConfig
#define COPASI_CWriteConfig
#include <strstream>

class CWriteConfig
{
public:
    /**
     *  Default consructor. 
     *  This opens the configuration file using a the default filename 
     *  "test.txt".
     */
    CWriteConfig();

    /**
     *  Specified consructor. 
     *  This opens the configuration file using the filename specified 
     *  as the argument.
     *  @param name name of the confguration file. 
     */
    CWriteConfig(string name);

    /**
     *  Destructor. 
     *  The destructor calls the method Free().
     */
    ~CWriteConfig();

    /**
     *  Returns the failure status.
     *  @return mFail
     *  @see mFail  
     */
    Fail();

    /**
     *  Retrieves the next variable from the output file.
     *  @param name name of the variable to be retrieved.
     *  @param type type of the variable to be retrieved.
     *  @param *pout pointer to the location where the retrieved variable 
     *               is stored.
     *  @return mFail
     *  @see mFail  
     */
    SetVariable(string name, string type, void * pout);

private:
    /**
     *  Commits all information to the configuration file. 
     *  This method is called by the destructor.
     */
    Commit();

    /**
     *  Name of the configuration file.
     */
    string mFileName;               // Config File Name

    /**
     *  Output file
     */
    strstream mBuffer;
    
    /**
     *  Current line number in the configuration file
     */
    unsigned long   mLineNumber;             // Current Line Number 

    /**
     *  Failure status:
     *  0 = no error
     *  !0 = error
     */
    int    mFail;                   // Failure State
};
#endif // COPASI_CWriteConfig

