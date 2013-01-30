// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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

/**
 *  CReadConfig class. A more elaborate class description.
 *  New Class based on pmutils read functionality
 *
 *  (C) Stefan Hoops 2001
 */

#ifndef COPASI_CReadConfig
#define COPASI_CReadConfig

#include <iostream>
#include <sstream>

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
   *  Default constructor.
   *  This creates a configuration buffer for input assigning a filename.
   *  It is currently useless.
   */
  CReadConfig();

  /**
   *  Initializes the input buffer for reading.
   *  @return mFail
   *  @see mFail
   */
  C_INT32 initFileBuffer();

  /**
   *  Look ahead to find the next variable name
   */
  std::string lookAhead();

  /**
   *  A pointer to the input buffer
   */
  std::istream * mpBuffer;

  /**
   *  Current line number in the configuration file
   */
  C_INT32 mLineNumber;

  /**
   * Mode = CReadConfig::SEARCH
   */
  CReadConfig::Mode mMode;

  /**
   *  Failure status:
   *  0 = no error
   *  !0 = error
   */
  C_INT32 mFail;

  /*
   *  The Version of the configuration file.
   */
  std::string mVersion;

  /**
   * Name of the configuration file.
   */
  std::string mFilename;

  /**
   * A buffer for reading the file.
   */
  std::stringstream mFileBuffer;

public:
  /**
   *  Specified constructor.
   *  This opens the configuration file using the filename specified
   *  as the argument.
   *  @param name name of the configuration file.
   */
  CReadConfig(const std::string& name);

  /**
   *  Specified constructor.
   *  This opens the configuration file using the filename specified
   *  as the argument.
   *  @param std::istream & in
   */
  CReadConfig(std::istream & in);

  /**
   *  Destructor.
   *  The destructor calls the method free().
   */
  ~CReadConfig();

  /**
   * Retrieves the version string of the configbuffer
   */
  std::string getVersion();

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
  C_INT32 getVariable(const std::string& name,
                      const std::string& type,
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
  C_INT32 getVariable(const std::string& name,
                      const std::string& type,
                      void * pout1,
                      void * pout2,
                      CReadConfig::Mode mode = CReadConfig::NEXT);

  /**
   * Rewind the buffer
   */
  void rewind();
};

#endif // COPASI_CReadConfig
