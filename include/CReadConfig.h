/**
 *  CReadConfig class. A more elaborate class description.
 */

// New Class based on pmutils read functionality
// (C) Stefan Hoops 2001


#ifndef COPASI_CReadConfig
#define COPASI_CReadConfig

#include <strstream>

// available operations mode for the configurations buffer
#define CReadConfig_SEARCH 0x01
#define CReadConfig_LOOP   0x02

class CReadConfig
{
public:
    /**
     *  Default consructor. 
     *  This creates a configuration buffer for input assigning a filename. 
     *  It is currently useless.
     */
    CReadConfig();

    /**
     *  Specified constructor. 
     *  This opens the configuration file using the filename specified 
     *  as the argument.
     *  @param name name of the confguration file. 
     */
    CReadConfig(const string& name);

    /**
     *  Destructor. 
     *  The destructor calls the method Free().
     */
    ~CReadConfig();

    /**
     *  Set the operations mode for configurations buffer.
     *  @param mode valid modes are: CReadConfig_SEARCH, CReadConfig_LOOP
     */
    void SetMode(int mode);
    
    /**
     *  Returns the failure status.
     *  @return mFail
     *  @see mFail  
     */
    int Fail();

    /**
     *  Retrieves the next variable from the input file.
     *  @param name name of the variable to be retrieved.
     *  @param type type of the variable to be retrieved.
     *  @param *pout pointer to the location where the retrieved variable 
     *               is stored.
     *  @return mFail
     *  @see mFail  
     */
    int GetVariable(const string& name, 
                    const string& type,
                    void * pout);
    int GetVariable(const string& name, 
                    const string& type,
                    void * pout1,
                    void * pout2);

private:
    /**
     *  Initializes the input buffer for reading.
     *  @return mFail
     *  @see mFail  
     */
    int InitInputBuffer();

    /**
     *  Look ahead to find the next variable name
     */
    string LookAhead();

    /**
     *  Name of the configuration file.
     */
    string mFilename;               // Config File Name

    /**
     *  Input buffer
     */
    strstream mBuffer;
    
   /**
     *  Current line number in the configuration file
     */
    long   mLineNumber;             // Current Line Number 

    /**
     * Mode = CReadConfig::SEARCH
     */
    int mMode;

    /**
     *  Failure status:
     *  0 = no error
     *  !0 = error
     */
    int    mFail;                   // Failure State
};
#endif // COPASI_CReadConfig

