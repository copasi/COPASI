// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseParser.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/04/02 12:14:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CMiaseParser
#define COPASI_CMiaseParser

#include <iostream>
#include <stdio.h>
#include <expat.h>
#include "CMiaseBase.h"
#include "CMiaseML.h"

#if defined(__amigaos__) && defined(__USE_INLINE__)
#include <proto/expat.h>
#endif

#ifdef XML_LARGE_SIZE
#if defined(XML_USE_MSC_EXTENSIONS) && _MSC_VER < 1400
#define XML_FMT_INT_MOD "I64"
#else
#define XML_FMT_INT_MOD "ll"
#endif
#else
#define XML_FMT_INT_MOD "l"
#endif

#define BUFFSIZE        8192

class CMiaseParser
  {

  public:

    static XML_Char mVersion_1_0[];
    static char mNameSpace[];
    static char mEncoding[];

    CMiaseParser();

    ~CMiaseParser();

    static void XMLCALL
    start(void *data, const char *el, const char **attr);

    static void XMLCALL end(void *data, const char *el);

    static void XMLCALL xmldecl_handler(void *userData, const XML_Char *version,
                                        const XML_Char *encoding, int standalone);

    static void XMLCALL charhndl(void *userData, const XML_Char *s, int len);

    void load(std::string filename);

    void testDataStructure();
  protected:

  private:

    enum States
    {
      STATE_READY_TO_READ,
      STATE_LIST_OF_MODELS,
      STATE_LIST_OF_TASKS,
      STATE_LIST_OF_OUTPUTS,
      STATE_NOTES,
      STATE_ANNOTATION,
      STATE_STOPPED,
      STATE_MIASE,
      STATE_SED,
      STATE_LIST_OF_SIMULATIONS,
      STATE_MODEL,
      STATE_LIST_OF_CHANGES,
      STATE_TASK,
      STATE_LIST_OF_MEASUREMENT,
      STATE_OUTPUT,
      //more states for output lists
      STATE_LAST
    };

    /**
     * A pointer to the input stream
     */
    std::istream *mpIstream;

    CMiaseML* mMiase;
    States mActState;
    States mLastState;
    int mTmpDepth;
    int mDepth;
    XML_Parser mXmlParser;
    char mBuff[BUFFSIZE];
    std::string mContent;
    std::vector< std::vector<std::string> > mAllowedStateTags;

    void startElement(const char *el, const char **attr);

    void endElement(const char *el);

    void xmlDecl(const XML_Char *version,
                 const XML_Char *encoding);

    void xmlNameSpace(void *, const XML_Char *prefix,
                      const XML_Char *uri);

    void newContent(const XML_Char *s, int len);

    bool isValid(const char *el);

    void createAllowedStateTags();

    void newNotes(const char **attr);

    void newAnnotation(const char **attr);

    void newModel(const char **attr);

    void newSimulation(const char *el, const char **attr);

    void newChange(const char *el, const char **attr);

    void newTask(const char **attr);

    void newMeasurementData(const char **attr);

    void newOutput(const char **attr);

    void newMiase(const char **attr);

    void newState(States newState);

    void error(std::string errorString);

    void addContent(const char *el, const char **attr);

    CMiaseBase* getLastObj();
  };

static CMiaseParser* myParser;

#endif //COPASI_CMiaseParser
