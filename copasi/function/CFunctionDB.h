/**
 * CFunctionDB
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CFunctionDB
#define COPASI_CFunctionDB

#include <string>

#include "report/CCopasiContainer.h"
#include "utilities/readwrite.h"
#include "utilities/CCopasiVector.h"

class CFunction;

/** @dia:pos 106.082,17.0878 */
class CFunctionDB : public CCopasiContainer
  {
    // Attributes

  private:
    /**
     *  Filename which contains the function database
     */
    std::string mFilename;

    /**
     *  Vector of the currently loaded functions
     *  @supplierCardinality 0..*
     */
    /** @dia:route 2,0; h,98.6992,12.15,102.581,17.0878,106.082 */
    CCopasiVectorNS < CFunction > mLoadedFunctions;

    // Operations

  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: RootContainer)
     */
    CFunctionDB(const std::string & name = "NoName",
                const CCopasiContainer * pParent = &RootContainer);

    /**
     * Destructor
     */
    ~CFunctionDB();

    /**
     *
     */
    void cleanup();

    virtual void initObjects();

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
     *  Saves the contents of the object to a CWriteConfig object.
     *  This function uses the file format of Gepasi 3.21
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return mFail
     */
    C_INT32 saveOld(CWriteConfig & configbuffer);

    /**
     *
     */
    void setFilename(const std::string & filename);

    /**
     *
     */
    std::string getFilename() const;

    /**
     *  Load the function functionName from the database
     *  @param "const string" &functionName
     *  @return CFunction * function (NULL if function can not be loaded)
     */
    CFunction * dBLoad(const std::string & functionName);

    /**
     *  Add the function to the database
     *  @param CKinFunction &function
     *  @return CFunction * pFunction
     */
    CFunction * add(const CFunction & function);

    /**
     *  Delete the function functionName from the database
     *  @param "const string" &functionName
     *  @return C_INT32 Fail
     */
    void dBDelete(const std::string & functionName);

    /**
     *  Search for a function among the loaded functions. If no
     *  function is found NULL is returned
     *  @param "const string" &functionName
     *  @return CFunction *
     */
    CFunction * findFunction(const std::string & functionName);

    /**
     *  Search for a function among the loaded functions. If no
     *  function is found the database is searched and the apropriate 
     *  function is loaded.
     *  @param "const string" &functionName
     *  @return CFunction * function (NULL if function is not found)
     */
    CFunction * findLoadFunction(const std::string & functionName);

    /**
     *  Retrieves the vector of loaded functions.
     *  @return "CCopasiVectorNS < CKinFunction > &" loadedFunctions
     */
    CCopasiVectorNS < CFunction > & loadedFunctions();

    /**
     *  Retrieves the vector of functions that are suitable for a
     *  number of substrates, products and reversibility status.
     *  @param "const unsigned C_INT32" noSubstrates the number of substrates
     *  @param "const unsigned C_INT32" noProducts the number of products
     *  @param "const TriLogic" reversible the reversibility status
     *  @return "CCopasiVectorN < CKinFunction > " suitableFunctions
     */
    CCopasiVectorN < CFunction > suitableFunctions(const unsigned C_INT32 noSubstrates,
        const unsigned C_INT32 noProducts,
        const TriLogic reversible);
  };

#endif // COPASI_CFunctionDB
