/*****************************************************************************
 * PROGRAM NAME: CUDFunction.h
 * PROGRAMMER: Wei Sun	wsun@vt.edu
 * PURPOSE: Define the user defined function object
 *****************************************************************************/
#ifndef COPASI_CUDFunction
#define	COPASI_CUDFunction

#include <string>

#include "copasi.h"
#include "utilities/utilities.h"
#include "function/function.h"
#include "model/CModel.h"
#include "CNodeO.h"

class CUDFunction: public CKinFunction
{
 private:
  /**
   *  The vector of nodes of the binary tree of the function
   */
  CCopasiVectorS < CNodeO > mNodes;

 public:
  /**
   *  Default constructor
   */
  CUDFunction();

  /**
   *  Copy constructor
   *  @param "const CFunction &" src
   */
  CUDFunction(const CFunction & src);
  
  /**
   *  Copy constructor
   *  @param "const CUDFunction &" src
   */
  CUDFunction(const CUDFunction & src);
  
  /**
   *  This creates a user defined function with a name an description
   *  @param "const string" &name
   *  @param "const string" &description
   */
  CUDFunction(const string & name,
              const string & description);

  /**
   *  Destructor
   */
  virtual ~CUDFunction();

  /**
   *  Delete
   */
  void cleanup();

  /**
   *  Loads an object with data coming from a CReadConfig object.
   *  (CReadConfig object reads an input stream)
   *  @param pconfigbuffer reference to a CReadConfig object.
   *  @return Fail
   */
  void load(CReadConfig & configbuffer,
            CReadConfig::Mode mode = CReadConfig::LOOP);

 private:
  /**
   *  This function creates the parameter description for older file versions
   */
  void createParameters();
};

#endif
