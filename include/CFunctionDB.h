/**
 * CFunctionDB
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */


#ifndef COPASI_CFunctionDB
#define COPASI_CFunctionDB

#include <string>

#include "CKinFunction.h"

class CFunctionDB
{
// Attributes
private:
    /**
     *  Filename which contains the function database
     */
    string mFilename;

    /**
     *  Vector of the currently loaded functions
     */
    CCopasiVector < CKinFunction > mLoadedFunctions;
// Operations
public:
    /**
     *
     */
    CFunctionDB();

    /**
     *
     */
    ~CFunctionDB();

    /**
     *
     */
    SetFilename(const string & filename);
    
    /**
     *
     */
    string GetFilename();
    
    /**
     *  Load the function functionName from the database
     *  @param "const string" &functionName
     *  @return CKinFunction &
     */
    CKinFunction & DBLoad(const string & functionName);

    /**
     *  Add the function to the database
     *  @param CKinFunction &function
     *  @return long Fail
     */
    long DBAdd(CKinFunction & function);

    /**
     *  Delete the function functionName from the database
     *  @param "const string" &functionName
     *  @return long Fail
     */
    long DBDelete(const string & functionName);

    /**
     *  Search for a function among the loaded functions. If no
     *  function is found the database is searched and the apropriate 
     *  function is loaded.
     *  @param "const string" &functionName
     *  @return CKinFunction &
     */
    CKinFunction & FindFunction(const string & functionName);
};

#endif // COPASI_CFunctionDB
