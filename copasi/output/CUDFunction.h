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

class CUDIdentifier: public CBaseIdentifier
{
  // Attributes
 public:
  /*
   *  The nodes which access the same identifier.
   */
  vector < CNodeO * > mNodes;

  // Operations
 public:
  /**
   *  Default constructor
   */
  CUDIdentifier();
                    
  /**
   *  Destructor
   */
  ~CUDIdentifier();
};

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
  /**
   * Value of user defined function
   */
  C_FLOAT64 mValue;
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
   * return the pointer of this user defined function
   */
  void calcValue(CModel *model);

  /**
   * Get the pointer of user defined function
   */
  void * getValueAddr();

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

  void initIdentifiers();

};

#endif
