/**
 *  CReadConfig class. A more elaborate class description.
 *  New Class based on pmutils read functionality
 *
 *  (C) Stefan Hoops 2001
 */

#ifndef COPASI_CReadConfig
#define COPASI_CReadConfig

#include <strstream>
#include <string>

// available operations mode for the configurations buffer
// #define CReadConfig_SEARCH 0x01
// #define CReadConfig_LOOP   0x02

class CReadConfig
{
  // data
 public:
  enum Mode 
    {
    NEXT = 0,
    SEARCH,
    LOOP,
    ALL
    };
    
 private:
  /**
   *  Initializes the input buffer for reading.
   *  @return mFail
   *  @see mFail  
   */
  C_INT32 initInputBuffer();

  /**
   *  Look ahead to find the next variable name
   */
  string lookAhead();

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
  C_INT32   mLineNumber;             // Current Line Number 

  /**
   * Mode = CReadConfig::SEARCH
   */
  CReadConfig::Mode mMode;

  /**
   *  Failure status:
   *  0 = no error
   *  !0 = error
   */
  C_INT32    mFail;                   // Failure State

  /*
   *  The Version of the configuration file.
   */
  string mVersion;
    
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
   *  The destructor calls the method free().
   */
  ~CReadConfig();

  /**
   * Retrieves the version string of the configbuffer
   */
  string getVersion();

  /**
   * Load various system wide default values
   */
  void getDefaults();
  
  /**
   *  Returns the failure status.
   *  @return mFail
   *  @see mFail  
   */
  C_INT32 fail();

  /**
   *  Retrieves a variable from the input file.
   *  @param name name of the variable to be retrieved.
   *  @param type type of the variable to be retrieved.
   *  @param *pout pointer to the location where the retrieved variable 
   *               is stored.
   *  @return mFail
   *  @see mFail  
   */
  C_INT32 getVariable(const string& name, 
		      const string& type,
		      void * pout,
		      CReadConfig::Mode mode = CReadConfig::NEXT);

  /**
   *  Retrieves a variable from the input file.
   *  @param name name of the variable to be retrieved.
   *  @param type type of the variable to be retrieved.
   *  @param *pout1 pointer to the location where the first part of the 
   *                retrieved variable is stored.
   *  @param *pout2 pointer to the location where the second part of the 
   *                retrieved variable is stored.
   *  @return mFail
   *  @see mFail  
   */
  C_INT32 getVariable(const string& name, 
		      const string& type,
		      void * pout1,
		      void * pout2,
		      CReadConfig::Mode mode = CReadConfig::NEXT);
};
#endif // COPASI_CReadConfig
