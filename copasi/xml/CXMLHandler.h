/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CXMLHandler.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:36:26 $
   End CVS Header */

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

template<class CType, class CCommon>
      class CXMLElementHandler
    {
      // Attributes
    protected:
      /**
       * The underlying parser.
       */
      CType & mParser;

      /**
       * The shared elements between all element handlers of a parser
       */
      CCommon & mCommon;

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
      CXMLElementHandler(CType & parser, CCommon & common):
          mParser(parser),
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
