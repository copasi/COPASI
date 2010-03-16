/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CXMLHandler.h,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $
   $Date: 2010/03/16 18:59:03 $
   End CVS Header */

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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

  /**
   *
   */
  C_INT32 mLastKnownElement;

  // Operations
public:
  /**
   * Constructor
   */
  CXMLElementHandler(CType & parser, CCommon & common):
      mParser(parser),
      mCommon(common),
      mCurrentElement(-1),
      mpCurrentHandler(NULL),
      mLastKnownElement(-1)
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
  virtual void reset() {}

protected:
  /**
   * This assures that we do not accidentally delete common parser handlers.
   */
  void deleteCurrentHandler()
  {
    if (mpCurrentHandler != NULL &&
        mpCurrentHandler != &mParser.mUnknownElement &&
        mpCurrentHandler != &mParser.mCharacterDataElement &&
        mpCurrentHandler != &mParser.mCommentElement &&
        mpCurrentHandler != &mParser.mMiriamAnnotationElement)
      {
        delete mpCurrentHandler;
        mpCurrentHandler = NULL;
      }
  }
};

#endif // COPASI_CXMLHandler
