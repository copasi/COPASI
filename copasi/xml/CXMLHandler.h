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

class CXMLCharacterDataHandler()
  {
    // Attributes
  protected:
    /**
     * The character data
     */
    std::string mData;

    /**
     * The character to be stripped.
     */
    std::string mToBeStripped;

    /**
     * The characters used to replace new lines.
     */
    std::string mJoin;

    // Operations
  public:

    /**
     * Constructor
     */
    CXMLCharacterDataHandler(const std::string & toBeStripped = "\t\n ",
                             const std::string & join = " ");

    /**
     * Destructor
     */
    virtual ~CXMLCharacterDataHandler();
  }
#endif // COPASI_CXMLHandler
