/**
 * CXMLHandler class.
 * This class is the base class of all XML event handlers.
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#ifndef COPASI_CXMLHandler
#define COPASI_CXMLHandler

#include <stack>
#include <string>

#include "expat.h"

template<class CType>
class CXMLElementHandler
  {
    // Attributes
  protected:
    /**
     *
     */
    CType & mCommon;

    /**
     * The currently processed element.
     */
    C_INT32 mCurrentElement;

    /**
     * 
     */
    CXMLElementHandler * mpCurrentHandler;

    // Operations
  public:
    /**
     * Constructor
     */
    CXMLElementHandler(CType & common):
        mCommon(common),
        mCurrentElement(-1),
        mpCurrentHandler(NULL)
    {}

    /**
     * Destructor
     */
    virtual ~CXMLElementHandler() {}

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char * C_UNUSED(pszName),
                       const XML_Char ** C_UNUSED(papszAttrs)) {}

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char * C_UNUSED(pszName)) {}

    /**
     * Reset the element handler to start values.
     */
    virtual void reset() {}};

#endif // COPASI_CXMLHandler
