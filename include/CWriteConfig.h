/**
 *  CWriteConfig class. A more elaborate class description.
 *
 *  New Class based on pmutils read functionality
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CWriteConfig
#define COPASI_CWriteConfig

#include <strstream>

class CWriteConfig
{
public:
    /**
     *  Default consructor. 
     *  This creates a configuration buffer without assigning a filename. 
     *  It is currently useless.
     */
    CWriteConfig();

    /**
     *  Specified consructor. 
     *  This opens the configuration file using the filename specified 
     *  as the argument.
     *  @param name name of the confguration file. 
     */
    CWriteConfig(const string& name);

    /**
     *  Destructor. 
     *  The destructor calls the method flush().
     */
    ~CWriteConfig();

    /**
     *  Flush the output buffer to the configuration file.
     *  @return mFail
     *  @see mFail  
     */
    C_INT32 flush();

    /**
     *  Returns the failure status.
     *  @return mFail
     *  @see mFail  
     */
    C_INT32 fail();

    /**
     *  Writes a variable to the output file.
     *  @param name name of the variable to be written.
     *  @param type type of the variable to be written.
     *  @param *pout pointer to the location where the variable 
     *               is stored.
     *  @return mFail
     *  @see mFail  
     */
    C_INT32 setVariable(const string & name,
                        const string & type, 
                        const void * pout);
    C_INT32 setVariable(const string & name,
                        const string & type, 
                        const void * pout1, 
                        const void * pout2);

private:
    /**
     *  Commits all information to the configuration file. 
     *  This method is called by the destructor.
     */
    C_INT32 commit();

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
    unsigned C_INT32   mLineNumber;             // Current Line Number 

    /**
     *  Open mode
     */
    C_INT32 mOpenMode;
                                             
    /**
     *  Failure status:
     *  0 = no error
     *  !0 = error
     */
    C_INT32    mFail;                   // Failure State
};
#endif // COPASI_CWriteConfig

