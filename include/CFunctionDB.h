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
     *
     */
    string mFilename;

    /**
     *
     */
    CCopasiVector < CKinFunction > LoadedFunctions;
// Operations
public:
    /**
     *
     */
    CFunctionDB (  );

    /**
     *
     */
    ~CFunctionDB (  );

    /**
     *
     */
    CKinFunction & DBLoad ( const string & functionName );

    /**
     *
     */
    long DBAdd ( CKinFunction & function );

    /**
     *
     */
    long DBDelete ( const string & functionName );

    /**
     *
     */
    CKinFunction & FindFunction ( const string & functionName );
};

#endif // COPASI_CFunctionDB
