/*****************************************************************************
 * PROGRAM NAME: CUDFunctionDB.h
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: Define the user defined function DB object to hold all the user
 *     defined function    
 *****************************************************************************/
#ifndef COPASI_CUDFunctionDB
#define COPASI_CUDFunctionDB

#include <string>

#include "copasi.h"
#include "output/output.h"
#include "utilities/utilities.h"

class CUDFunctionDB
  {
  private:
    /**
     * "User-defined functions" string in gps file 
     */
    std::string mNameStr;
    /**
     * The number of user defined function
     */
    C_INT32 mItems;
    /**
     *  Vector of user defined functions
     */
    CCopasiVectorN < CUDFunction > mUDFunctions;

  public:
    /**
     *
     */
    CUDFunctionDB();

    /**
     *
     */
    ~CUDFunctionDB();

    /**
     *
     */
    void cleanup();

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return mFail
     */
    C_INT32 load(CReadConfig & configbuffer);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     */
    C_INT32 save(CWriteConfig & configbuffer);

    /**
     *  Add the function to the database
     *  @param CUDFunction &function
     *  @return C_INT32 Fail
     */
    void add(CUDFunction & function);

    /**
     * Get the number of user defined functions
     */
    C_INT16 getItems() const;
    /**
     * Set the number of user defined funcstion
     */
    void setItems(const C_INT16 items);

    /**
     * Get the "User-defined functions" string
     */
    std::string getNameStr() const;

    /**
     * Get the UDFunction array
     */
    CCopasiVectorN < CUDFunction > & getFunctions();
  };

#endif
