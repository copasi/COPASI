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
#include "function/CBaseFunction.h"
#include "CNodeO.h"

class CUDFunction: public CBaseFunction
{
 private:
  /**
   *  The vector of nodes of the binary tree of the function
   */
  CCopasiVectorS < CNodeO > mNodes;
  /**
   *  Internal variable
   */
  unsigned C_INT32 mNidx;

 public:
  /**
   *  Default constructor
   */
  CUDFunction();
    
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
  ~CUDFunction();

  /**
   *  Delete
   */
  void cleanup();

  /**
   *  Copy
   */
  void copy(const CUDFunction & in);

  /**
   *  Loads an object with data coming from a CReadConfig object.
   *  (CReadConfig object reads an input stream)
   *  @param pconfigbuffer reference to a CReadConfig object.
   *  @return Fail
   */
  C_INT32 load(CReadConfig & configbuffer,
	       CReadConfig::Mode mode = CReadConfig::LOOP);

  /**
   *  Saves the contents of the object to a CWriteConfig object.
   *  (Which usually has a file attached but may also have socket)
   *  @param pconfigbuffer reference to a CWriteConfig object.
   *  @return Fail
   */
  C_INT32 save(CWriteConfig & configbuffer);

  /**
   *  This retrieves the node tree of the function
   *  @return "CCopasiVectorS < CNodeO > &"
   */
  CCopasiVectorS < CNodeO > & nodes();

  /**
   * Calculate the value of this user defined function
   */
  C_FLOAT64 calcValue();

 private:
  /**
   *  This clears all nodes of the function tree
   */
  void clearNodes();

  /**
   *  This  connects the nodes to build the binary function tree
   */
  C_INT32 connectNodes();

  CNodeO * parseExpression(C_INT16 priority);

  CNodeO * parsePrimary();
};

#endif
