/*****************************************************************************
 * PROGRAM NAME: CNodeO.h
 * PROGRAMMER: Wei Sun	wsun@vt.edu
 * PURPOSE: Define the node object in user defined function
 *****************************************************************************/
#ifndef COPASI_CNodeO
#define	COPASI_CNodeO

#include <string>
#include <vector>

#include "copasi.h"
#include "model/model.h"
#include "utilities/utilities.h"
#include "function/function.h"
#include "CDatum.h"

class CNodeO: public CNodeK
{
  // Attributes
 private:
  /**
   *  A datum needed to specify the identifiers
   */
  CDatum mDatum;

 public:
  /**
   * Default constructor
   */
  CNodeO();

  /**
   * Destructor
   */
  ~CNodeO();

  /**
   *  Loads an object with data coming from a CReadConfig object.
   *  (CReadConfig object reads an input stream)
   *  @param pconfigbuffer reference to a CReadConfig object.
   *  @return Fail
   */
  C_INT32 load(CReadConfig & configbuffer);

  /**
   *  Retreives the datum of an identifier node
   *  @return "const CDatum &" datum
   */
  const CDatum & getDatum() const;
};
#endif

