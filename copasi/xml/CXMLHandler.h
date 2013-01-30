// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CXMLHandler class.
 * This class is the base class of all XML event handlers.
 *
 * Created for COPASI by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#ifndef COPASI_CXMLHandler
#define COPASI_CXMLHandler

#include <stack>
#include <string>
#include <iostream>

#include "expat.h"

class CCopasiObject;

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
        mpCurrentHandler != &mParser.mListOfUnsupportedAnnotationsElement &&
        mpCurrentHandler != &mParser.mCommentElement &&
        mpCurrentHandler != &mParser.mMiriamAnnotationElement)
      {
        delete mpCurrentHandler;
        mpCurrentHandler = NULL;
      }
  }

  void addFix(const std::string & key, CCopasiObject * pObject)
  {
    if (!mCommon.KeyMap.addFix(key, pObject))
      {
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 22, key.c_str(), mParser.getCurrentLineNumber());
      }
  }
};

#endif // COPASI_CXMLHandler
