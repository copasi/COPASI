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

class CXMLElementHandler
  {
    // Attributes
  protected:
    /**
     * The currently processed element.
     */
    C_INT32 mCurrentElement;

    /**
     * 
     */
    CXMLElementHandler * mpCurrentHandler;

    /**
     *
     */
    std::stack< CXMLElementHandler * > & mStack;

    // Operations
  public:
    /**
     * Constructor
     */
    CXMLElementHandler(std::stack< CXMLElementHandler * > & stack);

    /**
     * Destructor
     */
    virtual ~CXMLElementHandler();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void start(const XML_Char *pszName,
                       const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void end(const XML_Char *pszName);

    /**
     * Reset the element handler to start values.
     */
    virtual void reset();
  };

class CXMLCharacterDataHandler
  {
    // Attributes
  protected:
    /**
     * The character data
     */
    std::string mData;

    // Operations
  public:

    /**
     * Constructor
     */
    CXMLCharacterDataHandler();

    /**
     * Destructor
     */
    virtual ~CXMLCharacterDataHandler();

    /**
     * Retrieve the data. 
     * Any sequence of toBeStripped characters is replaced by a single
     * join character. The default is no stripping.
     * @param const std::string & toBeStripped (default: "")
     * @param const std::string & join (default: " ")
     * @return std::string data
     */
    std::string getData(const std::string & toBeStripped = "",
                        const std::string & join = " ") const;
  };
#endif // COPASI_CXMLHandler
