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

/**
 * CExpatTemplate class.
 * The class CExpatTemplate is a demplate defining a C++ interface to
 * the expat library.
 *
 * Created for Copasi by Stefan Hoops 2003
 */
template <class _T>
class CExpatTemplate
  {
  public:

    /**
     * Default constructor
     */
    CExpatTemplate():
        m_p(NULL)
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
      // If the encoding or seperator are empty, then NULL
      //

      if (pszEncoding != NULL && pszEncoding [0] == 0)
        pszEncoding = NULL;
      if (pszSep != NULL && pszSep [0] == 0)
        pszSep = NULL;

      //
      // Create the new one
      //

      m_p = XML_ParserCreate_MM(pszEncoding, NULL, pszSep);
      if (m_p == NULL)
        return false;

      //
      // Invoke the post create routine
      //

      _T *pThis = static_cast <_T *>(this);
      pThis->onPostCreate();

      //
      // Set the user data used in callbacks
      //

      XML_SetUserData(m_p, (void *) this);
      return true;
    }

    /**
     * Destroy the parser
     */
    void destroy()
    {
      if (m_p != NULL)
        XML_ParserFree(m_p);
      m_p = NULL;
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

      assert(m_p != NULL);

      //
      // Get the length if not specified
      //

      if (nLength < 0)
        nLength = strlen(pszBuffer);

      //
      // Invoke the parser
      //

      return XML_Parse(m_p, pszBuffer, nLength, fIsFinal) != 0;
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

      assert(m_p != NULL);

      //
      // Get the length if not specified
      //

      if (nLength < 0)
        nLength = wcslen(pszBuffer) * 2;

      //
      // Invoke the parser
      //

      return XML_Parse(m_p, pszBuffer, nLength, fIsFinal) != 0;
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
      assert(m_p != NULL);
      return XML_ParseBuffer(m_p, nLength, fIsFinal) != 0;
    }

    /**
     * Get the internal buffer
     */
    void *getBuffer(int nLength)
    {
      assert(m_p != NULL);
      return XML_GetBuffer(m_p, nLength);
    }

    /**
     * Enable/Disable the start element handler
     * @param bool fEnable (Default: true)
     */
    void enableStartElementHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      XML_SetStartElementHandler(m_p, fEnable ? startElementHandler : NULL);
    }

    /**
     * Enable/Disable end element handler
     * @param bool fEnable (Default: true)
     */
    void enableEndElementHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      XML_SetEndElementHandler(m_p, fEnable ? endElementHandler : NULL);
    }

    /**
     * Enable/Disable the element handlers
     * @param bool fEnable (Default: true)
     */
    void enableElementHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      enableStartElementHandler(fEnable);
      enableEndElementHandler(fEnable);
    }

    /**
     * Enable/Disable the character data handler
     * @param bool fEnable (Default: true)
     */
    void enableCharacterDataHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      XML_SetCharacterDataHandler(m_p,
                                  fEnable ? characterDataHandler : NULL);
    }

    /**
     * Enable/Disable the processing instruction handler
     * @param bool fEnable (Default: true)
     */
    void enableProcessingInstructionHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      XML_SetProcessingInstructionHandler(m_p,
                                          fEnable ? processingInstructionHandler : NULL);
    }

    /**
     * Enable/Disable the comment handler
     * @param bool fEnable (Default: true)
     */
    void enableCommentHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      XML_SetCommentHandler(m_p, fEnable ? commentHandler : NULL);
    }

    /**
     * Enable/Disable the start CDATA section handler
     * @param bool fEnable (Default: true)
     */
    void enableStartCdataSectionHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      XML_SetStartCdataSectionHandler(m_p,
                                      fEnable ? startCdataSectionHandler : NULL);
    }

    /**
     * Enable/Disable the end CDATA section handlers
     * @param bool fEnable (Default: true)
     */
    void enableEndCdataSectionHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      XML_SetEndCdataSectionHandler(m_p,
                                    fEnable ? endCdataSectionHandler : NULL);
    }

    /**
     * Enable/Disable the CDATA section handlers
     * @param bool fEnable (Default: true)
     */
    void enableCdataSectionHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      enableStartCdataSectionHandler(fEnable);
      enableEndCdataSectionHandler(fEnable);
    }

    /**
     * Enable/Disable default handler
     * @param bool fEnable (Default: true)
     */
    void enableDefaultHandler(bool fEnable = true, bool fExpand = true)
    {
      assert(m_p != NULL);
      if (fExpand)
        {
          XML_SetDefaultHandlerExpand(m_p,
                                      fEnable ? defaultHandler : NULL);
        }
      else
        XML_SetDefaultHandler(m_p, fEnable ? defaultHandler : NULL);
    }

    /**
     * Enable/Disable external entity ref handler
     * @param bool fEnable (Default: true)
     */
    void enableExternalEntityRefHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      XML_SetExternalEntityRefHandler(m_p,
                                      fEnable ? externalEntityRefHandler : NULL);
    }

    /**
     * Enable/Disable unknown encoding handler
     * @param bool fEnable (Default: true)
     */
    void enableUnknownEncodingHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      XML_SetUnknownEncodingHandler(m_p,
                                    fEnable ? unknownEncodingHandler : NULL);
    }

    /**
     * Enable/Disable start namespace handler
     * @param bool fEnable (Default: true)
     */
    void enableStartNamespaceDeclHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      XML_SetStartNamespaceDeclHandler(m_p,
                                       fEnable ? startNamespaceDeclHandler : NULL);
    }

    /**
     * Enable/Disable end namespace handler
     * @param bool fEnable (Default: true)
     */
    void enableEndNamespaceDeclHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      XML_SetEndNamespaceDeclHandler(m_p,
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
      assert(m_p != NULL);
      XML_SetXmlDeclHandler(m_p, fEnable ? xmlDeclHandler : NULL);
    }

    /**
     * Enable/Disable the start DOCTYPE declaration handler
     * @param bool fEnable (Default: true)
     */
    void enableStartDoctypeDeclHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      XML_SetStartDoctypeDeclHandler(m_p,
                                     fEnable ? startDoctypeDeclHandler : NULL);
    }

    /**
     * Enable/Disable the end DOCTYPE declaration handler
     * @param bool fEnable (Default: true)
     */
    void enableEndDoctypeDeclHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      XML_SetEndDoctypeDeclHandler(m_p,
                                   fEnable ? endDoctypeDeclHandler : NULL);
    }

    /**
     * Enable/Disable the DOCTYPE declaration handler
     * @param bool fEnable (Default: true)
     */
    void enableDoctypeDeclHandler(bool fEnable = true)
    {
      assert(m_p != NULL);
      enableStartDoctypeDeclHandler(fEnable);
      enableEndDoctypeDeclHandler(fEnable);
    }

    /**
     * Get last error
     * @return enum XML_Error
     */
    enum XML_Error getErrorCode()
    {
      assert(m_p != NULL);
      return XML_GetErrorCode(m_p);
    }

    /**
     * Get last error string
     * @return  const XML_LChar * errorString
     */
    const XML_LChar *getErrorString()
    {return XML_ErrorString(GetErrorCode());}

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
      assert(m_p != NULL);
      return XML_GetCurrentByteIndex(m_p);
    }

    /**
     * Get the current line number
     * @return ing lineNumber
     */
    int getCurrentLineNumber()
    {
      assert(m_p != NULL);
      return XML_GetCurrentLineNumber(m_p);
    }

    /**
     * Get the current column number
     * @return in cloumnNumber
     */
    int getCurrentColumnNumber()
    {
      assert(m_p != NULL);
      return XML_GetCurrentColumnNumber(m_p);
    }

    /**
     * Get the current byte count
     * @return in byteCount
     */
    int getCurrentByteCount()
    {
      assert(m_p != NULL);
      return XML_GetCurrentByteCount(m_p);
    }

    /**
     * Get the input context
     * @const char * inputContext
     */
    const char *getInputContext(int *pnOffset, int *pnSize)
    {
      assert(m_p != NULL);
      return XML_GetInputContext(m_p, pnOffset, pnSize);
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
      _T *pThis = static_cast <_T *>((CExpatTemplate <_T> *) pUserData);
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
      _T *pThis = static_cast <_T *>((CExpatTemplate <_T> *) pUserData);
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
      _T *pThis = static_cast <_T *>((CExpatTemplate <_T> *) pUserData);
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
      _T *pThis = static_cast <_T *>((CExpatTemplate <_T> *) pUserData);
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
      _T *pThis = static_cast <_T *>((CExpatTemplate <_T> *) pUserData);
      pThis->onComment(pszData);
    }

    /**
     * Start CDATA section wrapper
     * @param void *pUserData
     */
    static void startCdataSectionHandler(void *pUserData)
    {
      _T *pThis = static_cast <_T *>((CExpatTemplate <_T> *) pUserData);
      pThis->onStartCdataSection();
    }

    /**
     * End CDATA section wrapper
     * @param void *pUserData
     */
    static void endCdataSectionHandler(void *pUserData)
    {
      _T *pThis = static_cast <_T *>((CExpatTemplate <_T> *) pUserData);
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
      _T *pThis = static_cast <_T *>((CExpatTemplate <_T> *) pUserData);
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
      _T *pThis = static_cast <_T *>((CExpatTemplate <_T> *) pUserData);
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
      _T *pThis = static_cast <_T *>((CExpatTemplate <_T> *) pUserData);
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
      _T *pThis = static_cast <_T *>((CExpatTemplate <_T> *) pUserData);
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
      _T *pThis = static_cast <_T *>((CExpatTemplate <_T> *) pUserData);
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
      _T *pThis = static_cast <_T *>((CExpatTemplate <_T> *) pUserData);
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
      _T *pThis = static_cast <_T *>((CExpatTemplate <_T> *) pUserData);
      pThis->onStartDoctypeDecl(pszDoctypeName, pszSysID,
                                pszPubID, nHasInternalSubset != 0);
    }

    /**
     * End Doctype declaration wrapper
     * @param void *pUserData
     */
    static void endDoctypeDeclHandler(void *pUserData)
    {
      _T *pThis = static_cast <_T *>((CExpatTemplate <_T> *) pUserData);
      pThis->onEndDoctypeDecl();
    }

    // Attributes
  protected:

    /**
     * The expat parser 
     */
    XML_Parser m_p;
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
