/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CExpat.h,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/28 14:26:20 $
   End CVS Header */

/**
 * This file describes the C++ interface to the expat library used by
 * COPASI.
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops 
 */

#ifndef COPASI_CExpat
#define COPASI_CExpat

#include <assert.h>
#include <expat.h>

#include "utilities/CCopasiMessage.h"

/**
 * CExpatTemplate class.
 * The class CExpatTemplate is a demplate defining a C++ interface to
 * the expat library.
 *
 * Created for Copasi by Stefan Hoops 2003
 */
template <class CType>
class CExpatTemplate
  {
    // Attributes
  protected:

    /**
     * The expat parser 
     */
    XML_Parser mParser;

  public:
    /**
     * Destroy the parser
     */
    void destroy()
    {
      if (mParser != NULL)
        XML_ParserFree(mParser);
      mParser = NULL;
    }

    /**
     * Default constructor
     */
    CExpatTemplate():
        mParser(NULL)
  {}

    /**
     * Destructor
     */
    ~CExpatTemplate() {destroy();}

    /**
     * Create a parser
     * @param const XML_Char *pszEncoding (Default = NULL)
     * @param const XML_Char *pszSep (Default = NULL)
     */
    bool create(const XML_Char *pszEncoding = NULL,
                const XML_Char *pszSep = NULL)
    {
      //
      // Destroy the old parser
      //

      destroy();

      //
      // If the encoding or separator are empty, then NULL
      //

      if (pszEncoding != NULL && pszEncoding [0] == 0)
        pszEncoding = NULL;
      if (pszSep != NULL && pszSep [0] == 0)
        pszSep = NULL;

      //
      // Create the new one
      //

      mParser = XML_ParserCreate_MM(pszEncoding, NULL, pszSep);
      if (mParser == NULL)
        return false;

      //
      // Invoke the post create routine
      //

      CType *pThis = static_cast <CType *>(this);
      pThis->onPostCreate();

      //
      // Set the user data used in callbacks
      //

      XML_SetUserData(mParser, (void *) this);
      return true;
    }

    /**
     * Parse a block of character data
     * @param const char *pszBuffer
     * @param int nLength (Default: -1 (zero terminated))
     * @param bool fIsFinal (Default: true)
     * @return bool Success
     */
    bool parse(const char *pszBuffer, int nLength = -1, bool fIsFinal = true)
    {
      //
      // Validate
      //

      assert(mParser != NULL);

      //
      // Get the length if not specified
      //

      if (nLength < 0)
        nLength = strlen(pszBuffer);

      //
      // Invoke the parser
      //

      return XML_Parse(mParser, pszBuffer, nLength, fIsFinal) != 0;
    }

#ifdef WCHAR
    /**
     * Parse a block of wide character data
     * @param const WCHAR *pszBuffer
     * @param int nLength (Default: -1 (zero terminated))
     * @param bool fIsFinal (Default: true)
     * @return bool Success
     */
    bool parse(const WCHAR *pszBuffer, int nLength = -1, bool fIsFinal = true)
    {
      //
      // Validate
      //

      assert(mParser != NULL);

      //
      // Get the length if not specified
      //

      if (nLength < 0)
        nLength = wcslen(pszBuffer) * 2;

      //
      // Invoke the parser
      //

      return XML_Parse(mParser, pszBuffer, nLength, fIsFinal) != 0;
    }
#endif

    /**
     * Parse internal buffer
     * @param int nLength
     * @param bool fIsFinal (Default: true)
     * @return bool Success
     */
    bool parseBuffer(int nLength, bool fIsFinal = true)
    {
      assert(mParser != NULL);
      return XML_ParseBuffer(mParser, nLength, fIsFinal) != 0;
    }

    /**
     * Get the internal buffer
     */
    void *getBuffer(int nLength)
    {
      assert(mParser != NULL);
      return XML_GetBuffer(mParser, nLength);
    }

    /**
     * Enable/Disable the start element handler
     * @param bool fEnable (Default: true)
     */
    void enableStartElementHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      XML_SetStartElementHandler(mParser, fEnable ? startElementHandler : NULL);
    }

    /**
     * Enable/Disable end element handler
     * @param bool fEnable (Default: true)
     */
    void enableEndElementHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      XML_SetEndElementHandler(mParser, fEnable ? endElementHandler : NULL);
    }

    /**
     * Enable/Disable the element handlers
     * @param bool fEnable (Default: true)
     */
    void enableElementHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      enableStartElementHandler(fEnable);
      enableEndElementHandler(fEnable);
    }

    /**
     * Enable/Disable the character data handler
     * @param bool fEnable (Default: true)
     */
    void enableCharacterDataHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      XML_SetCharacterDataHandler(mParser,
                                  fEnable ? characterDataHandler : NULL);
    }

    /**
     * Enable/Disable the processing instruction handler
     * @param bool fEnable (Default: true)
     */
    void enableProcessingInstructionHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      XML_SetProcessingInstructionHandler(mParser,
                                          fEnable ? processingInstructionHandler : NULL);
    }

    /**
     * Enable/Disable the comment handler
     * @param bool fEnable (Default: true)
     */
    void enableCommentHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      XML_SetCommentHandler(mParser, fEnable ? commentHandler : NULL);
    }

    /**
     * Enable/Disable the start CDATA section handler
     * @param bool fEnable (Default: true)
     */
    void enableStartCdataSectionHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      XML_SetStartCdataSectionHandler(mParser,
                                      fEnable ? startCdataSectionHandler : NULL);
    }

    /**
     * Enable/Disable the end CDATA section handlers
     * @param bool fEnable (Default: true)
     */
    void enableEndCdataSectionHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      XML_SetEndCdataSectionHandler(mParser,
                                    fEnable ? endCdataSectionHandler : NULL);
    }

    /**
     * Enable/Disable the CDATA section handlers
     * @param bool fEnable (Default: true)
     */
    void enableCdataSectionHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      enableStartCdataSectionHandler(fEnable);
      enableEndCdataSectionHandler(fEnable);
    }

    /**
     * Enable/Disable default handler
     * @param bool fEnable (Default: true)
     */
    void enableDefaultHandler(bool fEnable = true, bool fExpand = true)
    {
      assert(mParser != NULL);
      if (fExpand)
        {
          XML_SetDefaultHandlerExpand(mParser,
                                      fEnable ? defaultHandler : NULL);
        }
      else
        XML_SetDefaultHandler(mParser, fEnable ? defaultHandler : NULL);
    }

    /**
     * Enable/Disable external entity ref handler
     * @param bool fEnable (Default: true)
     */
    void enableExternalEntityRefHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      XML_SetExternalEntityRefHandler(mParser,
                                      fEnable ? externalEntityRefHandler : NULL);
    }

    /**
     * Enable/Disable unknown encoding handler
     * @param bool fEnable (Default: true)
     */
    void enableUnknownEncodingHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      XML_SetUnknownEncodingHandler(mParser,
                                    fEnable ? unknownEncodingHandler : NULL);
    }

    /**
     * Enable/Disable start namespace handler
     * @param bool fEnable (Default: true)
     */
    void enableStartNamespaceDeclHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      XML_SetStartNamespaceDeclHandler(mParser,
                                       fEnable ? startNamespaceDeclHandler : NULL);
    }

    /**
     * Enable/Disable end namespace handler
     * @param bool fEnable (Default: true)
     */
    void enableEndNamespaceDeclHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      XML_SetEndNamespaceDeclHandler(mParser,
                                     fEnable ? endNamespaceDeclHandler : NULL);
    }

    /**
     * Enable/Disable namespace handlers
     * @param bool fEnable (Default: true)
     */
    void enableNamespaceDeclHandler(bool fEnable = true)
    {
      enableStartNamespaceDeclHandler(fEnable);
      enableEndNamespaceDeclHandler(fEnable);
    }

    /**
     * Enable/Disable the XML declaration handler
     * @param bool fEnable (Default: true)
     */
    void enableXmlDeclHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      XML_SetXmlDeclHandler(mParser, fEnable ? xmlDeclHandler : NULL);
    }

    /**
     * Enable/Disable the start DOCTYPE declaration handler
     * @param bool fEnable (Default: true)
     */
    void enableStartDoctypeDeclHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      XML_SetStartDoctypeDeclHandler(mParser,
                                     fEnable ? startDoctypeDeclHandler : NULL);
    }

    /**
     * Enable/Disable the end DOCTYPE declaration handler
     * @param bool fEnable (Default: true)
     */
    void enableEndDoctypeDeclHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      XML_SetEndDoctypeDeclHandler(mParser,
                                   fEnable ? endDoctypeDeclHandler : NULL);
    }

    /**
     * Enable/Disable the DOCTYPE declaration handler
     * @param bool fEnable (Default: true)
     */
    void enableDoctypeDeclHandler(bool fEnable = true)
    {
      assert(mParser != NULL);
      enableStartDoctypeDeclHandler(fEnable);
      enableEndDoctypeDeclHandler(fEnable);
    }

    /**
     * Get last error
     * @return enum XML_Error
     */
    enum XML_Error getErrorCode()
    {
      assert(mParser != NULL);
      return XML_GetErrorCode(mParser);
    }

    /**
     * Get last error string
     * @return  const XML_LChar * errorString
     */
    const XML_LChar *getErrorString()
    {return XML_ErrorString(getErrorCode());}

    /**
     * Get error string
     * @param enum XML_Error nError
     * @return const XML_LChar * errorString
     */
    static const XML_LChar *getErrorString(enum XML_Error nError)
    {return XML_ErrorString(nError);}

    /**
     * Get the current byte index
     * @return long byteIndex
     */
    long getCurrentByteIndex()
    {
      assert(mParser != NULL);
      return XML_GetCurrentByteIndex(mParser);
    }

    /**
     * Get the current line number
     * @return ing lineNumber
     */
    int getCurrentLineNumber() const
      {
        assert(mParser != NULL);
        return XML_GetCurrentLineNumber(mParser);
      }

    /**
     * Get the current column number
     * @return in cloumnNumber
     */
    int getCurrentColumnNumber()
    {
      assert(mParser != NULL);
      return XML_GetCurrentColumnNumber(mParser);
    }

    /**
     * Get the current byte count
     * @return in byteCount
     */
    int getCurrentByteCount()
    {
      assert(mParser != NULL);
      return XML_GetCurrentByteCount(mParser);
    }

    /**
     * Get the input context
     * @const char * inputContext
     */
    const char *getInputContext(int *pnOffset, int *pnSize)
    {
      assert(mParser != NULL);
      return XML_GetInputContext(mParser, pnOffset, pnSize);
    }

    /**
     * Return the version string
     * @return const XML_LChar * version
     */
    static const XML_LChar *getExpatVersion()
    {return XML_ExpatVersion();}

    // @cmember Get the version information

    /**
     * Get the version information
     * @param int nMajor
     * @param int nMinor
     * @param int nMicro
     */
    static void getExpatVersion(int &nMajor, int &nMinor, int &nMicro)
    {
      XML_Expat_Version v = XML_ExpatVersionInfo();

      nMajor = v.major;
      nMinor = v.minor;
      nMicro = v.micro;
    }

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    void onStartElement(const XML_Char *pszName, const XML_Char **papszAttrs)
    {return;}

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    void onEndElement(const XML_Char *pszName)
    {return;}

    /**
     * Character data handler
     * @param const XML_Char *pszData
     * @param int nLength
     */
    void onCharacterData(const XML_Char *pszData, int nLength)
    {return;}

    /**
     * Processing instruction handler
     * @param const XML_Char *pszTarget
     * @param const XML_Char *pszData
     */
    void onProcessingInstruction(const XML_Char *pszTarget,
                                 const XML_Char *pszData)
    {return;}

    /**
     * Comment handler
     * @param const XML_Char *pszData
     */
    void onComment(const XML_Char *pszData)
    {return;}

    /**
     * Start CDATA section handler
     */
    void onStartCdataSection()
    {return;}

    /**
     * End CDATA section handler
     */
    void onEndCdataSection()
    {return;}

    /**
     * Default handler
     * @param const XML_Char *pszData
     * @param int nLength
     */
    void onDefault(const XML_Char *pszData, int nLength)
    {return;}

    /**
     * External entity ref handler
     * @param const XML_Char *pszContext
     * @param const XML_Char *pszBase
     * @param const XML_Char *pszSystemID
     * @param const XML_Char *pszPublicID
     */
    bool onExternalEntityRef(const XML_Char *pszContext,
                             const XML_Char *pszBase,
                             const XML_Char *pszSystemID,
                             const XML_Char *pszPublicID)
    {return false;}

    /**
     * Unknown encoding handler
     * @param const XML_Char *pszName
     * @param XML_Encoding *pInfo
     */
    bool onUnknownEncoding(const XML_Char *pszName, XML_Encoding *pInfo)
    {return false;}

    /**
     * Start namespace declaration handler
     * @param const XML_Char *pszPrefix
     * @param const XML_Char *pszURI
     */
    void onStartNamespaceDecl(const XML_Char *pszPrefix,
                              const XML_Char *pszURI)
    {return;}

    /**
     * End namespace declaration handler
     * @param const XML_Char *pszPrefix
     */
    void onEndNamespaceDecl(const XML_Char *pszPrefix)
    {return;}

    /**
     * XML declaration handler
     * @param const XML_Char *pszVersion
     * @param const XML_Char *pszEncoding
     * @param bool fStandalone
     */
    void onXmlDecl(const XML_Char *pszVersion,
                   const XML_Char *pszEncoding,
                   bool fStandalone)
    {return;}

    /**
     * Start DOCTYPE declaration handler
     * @param const XML_Char *pszDoctypeName
     * @param const XML_Char *pszSysID
     * @param const XML_Char *pszPubID
     * @param bool fHasInternalSubset
     */
    void onStartDoctypeDecl(const XML_Char *pszDoctypeName,
                            const XML_Char *pszSysID,
                            const XML_Char *pszPubID,
                            bool fHasInternalSubset)
    {return;}

    /**
     * End DOCTYPE declaration handler
     */
    void onEndDoctypeDecl()
    {return;}

    /**
     * Retreive the attribute value for the given name out of the list
     * of attributes. If required is true and the attribute is not found an
     * exception is thrown. If required is false and the attribute is not found
     * NULL is returned.
     *
     * @param const std::string & name
     * @param const char ** attributes
     * @param const bool & required (default: true)
     * @return const char * value
     */
    const char * getAttributeValue(const std::string & name,
                                   const char ** attributes,
                                   const bool & required = true) const
      {
        unsigned C_INT32 i;

        for (i = 0; attributes[i]; i += 2)
          if (attributes[i] == name) break;

        if (attributes[i]) return attributes[i + 1];

        if (required)
          CCopasiMessage(CCopasiMessage::ERROR, MCXML + 1,
                         name.c_str(), getCurrentLineNumber());
        return NULL;
      }

    /**
     * Retreive the attribute value for the given name out of the list
     * of attributes. If the attribute is not found default is returned.
     * @param const std::string & name
     * @param const char ** attributes
     * @param const char * default
     * @return const char * value
     */
    const char * getAttributeValue(const std::string & name,
                                   const char ** attributes,
                                   const char * def) const
      {
        const char * tmp = getAttributeValue(name, attributes, false);
        if (!tmp) return def;
        return tmp;
      }

    /**
     * Convert an attribute of type xs:boolean to bool. If attribute is NULL
     * false is returned.
     * @param const char * attribute
     * @return bool
     */
    static bool toBool(const char * attribute)
    {
      if (!attribute) return false;
      if (!strcmp(attribute, "true") || !strcmp(attribute, "1")) return true;
      return false;
    }

    /**
     * Convert an attribute to enum. If attribute is NULL
     * or no matching name is found -1 is returned. Note: enumNames must be 
     * zero terminated.
     * @param const char * attribute
     * @param const char ** enumNames 
     * @return bool
     */
    static int toEnum(const char * attribute,
                      const char ** enumNames)
    {
      if (!attribute) return - 1;

      for (int i = 0; *enumNames; i++, enumNames++)
        if (!strcmp(attribute, *enumNames)) return i;

      return - 1;
    }

    /**
     * Convert an attribute to double. If attribute is NULL
     * or cannot converted to a number NaN is returned. 
     * @param const char * attribute
     * @return double value
     */
    static double toDBL(const char * attribute)
    {
      if (!attribute)
        return std::numeric_limits<C_FLOAT64>::signaling_NaN();

      char * Tail;
      double Value = strtod(attribute, & Tail);

      if (!*Tail)
        return Value;

      if (!strcmp(attribute, "INF"))
        return std::numeric_limits<C_FLOAT64>::infinity();
      else if (!strcmp(attribute, "-INF"))
        return - std::numeric_limits<C_FLOAT64>::infinity();
      else
        return std::numeric_limits<C_FLOAT64>::quiet_NaN();
    }

  protected:
    /**
     * Handle any post creation
     */
    void onPostCreate()
  {}

    /**
     * Start element handler wrapper
     * @param void *pUserData
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    static void startElementHandler(void *pUserData,
                                    const XML_Char *pszName,
                                    const XML_Char **papszAttrs)
    {
      CType *pThis = static_cast <CType *>((CExpatTemplate <CType> *) pUserData);
      pThis->onStartElement(pszName, papszAttrs);
    }

    /**
     * End element handler wrapper
     * @param void *pUserData
     * @param const XML_Char *pszName
     */
    static void endElementHandler(void *pUserData,
                                  const XML_Char *pszName)
    {
      CType *pThis = static_cast <CType *>((CExpatTemplate <CType> *) pUserData);
      pThis->onEndElement(pszName);
    }

    /**
     * Character data handler wrapper
     * @param void *pUserData
     * @param const XML_Char *pszData
     * @param int nLength
     */
    static void characterDataHandler(void *pUserData,
                                     const XML_Char *pszData,
                                     int nLength)
    {
      CType *pThis = static_cast <CType *>((CExpatTemplate <CType> *) pUserData);
      pThis->onCharacterData(pszData, nLength);
    }

    /**
     * Processing instruction handler wrapper
     * @param void *pUserData
     * @param const XML_Char *pszTarget
     * @param const XML_Char *pszData
     */
    static void processingInstructionHandler(void *pUserData,
        const XML_Char *pszTarget,
        const XML_Char *pszData)
    {
      CType *pThis = static_cast <CType *>((CExpatTemplate <CType> *) pUserData);
      pThis->onProcessingInstruction(pszTarget, pszData);
    }

    /**
     * Comment handler wrapper
     * @param void *pUserData
     * @param const XML_Char *pszData
     */
    static void commentHandler(void *pUserData,
                               const XML_Char *pszData)
    {
      CType *pThis = static_cast <CType *>((CExpatTemplate <CType> *) pUserData);
      pThis->onComment(pszData);
    }

    /**
     * Start CDATA section wrapper
     * @param void *pUserData
     */
    static void startCdataSectionHandler(void *pUserData)
    {
      CType *pThis = static_cast <CType *>((CExpatTemplate <CType> *) pUserData);
      pThis->onStartCdataSection();
    }

    /**
     * End CDATA section wrapper
     * @param void *pUserData
     */
    static void endCdataSectionHandler(void *pUserData)
    {
      CType *pThis = static_cast <CType *>((CExpatTemplate <CType> *) pUserData);
      pThis->onEndCdataSection();
    }

    /**
     * Default wrapper
     * @param void *pUserData
     * @param const XML_Char *pszData
     * @param int nLength
     */
    static void defaultHandler(void *pUserData,
                               const XML_Char *pszData,
                               int nLength)
    {
      CType *pThis = static_cast <CType *>((CExpatTemplate <CType> *) pUserData);
      pThis->onDefault(pszData, nLength);
    }

    /**
     * External entity ref wrapper
     * @param void *pUserData
     * @param const XML_Char *pszContext
     * @param const XML_Char *pszBase
     * @param const XML_Char *pszSystemID
     * @param const XML_Char *pszPublicID
     */
    static int externalEntityRefHandler(void *pUserData,
                                        const XML_Char *pszContext,
                                        const XML_Char *pszBase,
                                        const XML_Char *pszSystemID,
                                        const XML_Char *pszPublicID)
    {
      CType *pThis = static_cast <CType *>((CExpatTemplate <CType> *) pUserData);
      return pThis->onExternalEntityRef(pszContext,
                                        pszBase, pszSystemID, pszPublicID) ? 1 : 0;
    }

    /**
     * Unknown encoding wrapper
     * @param void *pUserData
     * @param const XML_Char *pszName
     * @param XML_Encoding *pInfo
     */
    static int unknownEncodingHandler(void *pUserData,
                                      const XML_Char *pszName,
                                      XML_Encoding *pInfo)
    {
      CType *pThis = static_cast <CType *>((CExpatTemplate <CType> *) pUserData);
      return pThis->onUnknownEncoding(pszName, pInfo) ? 1 : 0;
    }

    /**
     * Start namespace decl wrapper
     * @param void *pUserData
     * @param const XML_Char *pszPrefix
     * @param const XML_Char *pszURI
     */
    static void startNamespaceDeclHandler(void *pUserData,
                                          const XML_Char *pszPrefix,
                                          const XML_Char *pszURI)
    {
      CType *pThis = static_cast <CType *>((CExpatTemplate <CType> *) pUserData);
      pThis->onStartNamespaceDecl(pszPrefix, pszURI);
    }

    /**
     * End namespace decl wrapper
     * @param void *pUserData
     * @param const XML_Char *pszPrefix
     */
    static void endNamespaceDeclHandler(void *pUserData,
                                        const XML_Char *pszPrefix)
    {
      CType *pThis = static_cast <CType *>((CExpatTemplate <CType> *) pUserData);
      pThis->onEndNamespaceDecl(pszPrefix);
    }

    /**
     * XML declaration wrapper
     * @param void *pUserData
     * @param const XML_Char *pszVersion
     * @param const XML_Char *pszEncoding
     * @param int nStandalone
     */
    static void xmlDeclHandler(void *pUserData,
                               const XML_Char *pszVersion,
                               const XML_Char *pszEncoding,
                               int nStandalone)
    {
      CType *pThis = static_cast <CType *>((CExpatTemplate <CType> *) pUserData);
      pThis->onXmlDecl(pszVersion, pszEncoding, nStandalone != 0);
    }

    /**
     * Start Doctype declaration wrapper
     * @param void *pUserData
     * @param const XML_Char *pszDoctypeName
     * @param const XML_Char *pszSysID
     * @param const XML_Char *pszPubID
     * @param int nHasInternalSubset
     */
    static void startDoctypeDeclHandler(void *pUserData,
                                        const XML_Char *pszDoctypeName,
                                        const XML_Char *pszSysID,
                                        const XML_Char *pszPubID,
                                        int nHasInternalSubset)
    {
      CType *pThis = static_cast <CType *>((CExpatTemplate <CType> *) pUserData);
      pThis->onStartDoctypeDecl(pszDoctypeName, pszSysID,
                                pszPubID, nHasInternalSubset != 0);
    }

    /**
     * End Doctype declaration wrapper
     * @param void *pUserData
     */
    static void endDoctypeDeclHandler(void *pUserData)
    {
      CType *pThis = static_cast <CType *>((CExpatTemplate <CType> *) pUserData);
      pThis->onEndDoctypeDecl();
    }
  };

/**
 * CExpat class.
 * The class CExpat is an instantiation of the CExpatTemplate class above.
 * Is can be used where late binding is preferred to template behaviour.
 *
 * Created for Copasi by Stefan Hoops 2003
 */
class CExpat : public CExpatTemplate <CExpat>
  {
  public:

    /**
     * Default constructor
     */
    CExpat();

    /**
     * Destructor
     */
    virtual ~CExpat();

    /**
     * Start element handler
     * @param const XML_Char *pszName
     * @param const XML_Char **papszAttrs
     */
    virtual void onStartElement(const XML_Char *pszName,
                                const XML_Char **papszAttrs);

    /**
     * End element handler
     * @param const XML_Char *pszName
     */
    virtual void onEndElement(const XML_Char *pszName);

    /**
     * Character data handler
     * @param const XML_Char *pszData
     * @param int nLength
     */
    virtual void onCharacterData(const XML_Char *pszData,
                                 int nLength);

    /**
     * Processing instruction handler
     * @param const XML_Char *pszTarget
     * @param const XML_Char *pszData
     */
    virtual void onProcessingInstruction(const XML_Char *pszTarget,
                                         const XML_Char *pszData);

    /**
     * Comment handler
     * @param const XML_Char *pszData
     */
    virtual void onComment(const XML_Char *pszData);

    /**
     * Start CDATA section handler
     */
    virtual void onStartCdataSection();

    /**
     * End CDATA section handler
     */
    virtual void onEndCdataSection();

    /**
     * Default handler
     * @param const XML_Char *pszData
     * @param int nLength
     */
    virtual void onDefault(const XML_Char *pszData,
                           int nLength);

    /**
     * External entity ref handler
     * @param const XML_Char *pszContext
     * @param const XML_Char *pszBase
     * @param const XML_Char *pszSystemID
     * @param const XML_Char *pszPublicID
     */
    virtual bool onExternalEntityRef(const XML_Char *pszContext,
                                     const XML_Char *pszBase,
                                     const XML_Char *pszSystemID,
                                     const XML_Char *pszPublicID);

    /**
     * Unknown encoding handler
     * @param const XML_Char *pszName
     * @param XML_Encoding *pInfo
     */
    virtual bool onUnknownEncoding(const XML_Char *pszName,
                                   XML_Encoding *pInfo);

    /**
     * Start namespace declaration handler
     * @param const XML_Char *pszPrefix
     * @param const XML_Char *pszURI
     */
    virtual void onStartNamespaceDecl(const XML_Char *pszPrefix,
                                      const XML_Char *pszURI);

    /**
     * End namespace declaration handler
     * @param const XML_Char *pszPrefix
     */
    virtual void onEndNamespaceDecl(const XML_Char *pszPrefix);

    /**
     * XML declaration handler
     * @param const XML_Char *pszVersion
     * @param const XML_Char *pszEncoding
     * @param bool fStandalone
     */
    virtual void onXmlDecl(const XML_Char *pszVersion,
                           const XML_Char *pszEncoding,
                           bool fStandalone);

    /**
     * Start DOCTYPE declaration handler
     * @param const XML_Char *pszDoctypeName
     * @param const XML_Char *pszSysID
     * @param const XML_Char *pszPubID
     * @param bool fHasInternalSubset
     */
    virtual void onStartDoctypeDecl(const XML_Char *pszDoctypeName,
                                    const XML_Char *pszSysID,
                                    const XML_Char *pszPubID,
                                    bool fHasInternalSubset);

    /**
     * End DOCTYPE declaration handler
     */
    virtual void onEndDoctypeDecl();
  };

#endif // COPASI_CExpat
