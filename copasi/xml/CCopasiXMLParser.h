/**
 * CCopasiXMLParser class.
 * This class is the parses a Copasi XML file.
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#ifndef COPASI_CCopasiXMLParser
#define COPASI_CCopasiXMLParser

#include <stack>
#include <map>

#include "CExpat.h"
#include "CXMLHandler.h"
#include "utilities/CCopasiVector.h"

class CModel;
class CFunction;
class CCopasiXMLParser;

struct SCopasiXMLParserCommon
  {
    CCopasiXMLParser * pParser;

    CModel * pModel;

    /**
     * Pointer to a vector of functions which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */
    CCopasiVectorN< CFunction > * pFunctionList;

    /**
     * Pointer to the currently processed function.
     */
    CFunction * pFunction;

    /**
     * A map relating CopasiXML function keys with internal keys
     */
    std::map< std::string, std::string > KeyMap;

    /**
     * Pointer to a vector of tasks which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */ 
    // CCopasiVectorN< CCopasiTask > * pTaskList;

    /**
     * Pointer to a vector of reports which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */ 
    // CCopasiVectorN< CCopasiReport > * pReportList;
  };

class CCopasiXMLParser : public CExpat
  {
    // Attributes
  private:
    /**
     * Attributes accessible through the whole parser.
     */
    SCopasiXMLParserCommon mCommon;

    /**
     * The character data.
     */
    std::string mCharacterData;

    /**
     * The element hndler stack
     */
    std::stack< CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon > * > mElementHandlerStack;

  class ModelElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * 
         */
        enum Element
        {
          COPASI = 0,
          ListOfFunctions,
          Model,
          ListOfTasks,
          ListOfReports
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ModelElement(CCopasiXMLParser & parser,
                     SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ModelElement();

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
      };

  class ListOfTasksElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * 
         */
        enum Element
        {
          COPASI = 0,
          ListOfFunctions,
          Model,
          ListOfTasks,
          ListOfReports
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfTasksElement(CCopasiXMLParser & parser,
                           SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfTasksElement();

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
      };

  class ListOfReportsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * 
         */
        enum Element
        {
          COPASI = 0,
          ListOfFunctions,
          Model,
          ListOfTasks,
          ListOfReports
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfReportsElement(CCopasiXMLParser & parser,
                             SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfReportsElement();

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
      };

    /**
     * 
     */
  class COPASIElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * 
         */
        enum Element
        {
          COPASI = 0,
          ListOfFunctions,
          Model,
          ListOfTasks,
          ListOfReports
        };

        // Operations
      public:
        /**
         * Constructor
         */
        COPASIElement(CCopasiXMLParser & parser,
                      SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~COPASIElement();

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
      };

  class ListOfFunctionsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * 
         */
        enum Element
        {
          ListOfFunctions = 0,
          Function
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfFunctionsElement(CCopasiXMLParser & parser,
                               SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfFunctionsElement();

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
      };

  class TextElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Text
         */
        enum Element
        {
          Text = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        TextElement(CCopasiXMLParser & parser,
                    SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~TextElement();

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
      };

  class MathMLElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Text
         */
        enum Element
        {
          MathML = 0,
          Text
        };

        // Operations
      public:
        /**
         * Constructor
         */
        MathMLElement(CCopasiXMLParser & parser,
                      SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~MathMLElement();

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
      };

  class ParameterDescriptionElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * 
         */
        enum Element
        {
          ParameterDescription = 0
        };

        /**
         * Order
         */
        unsigned C_INT32 mOrder;

        // Operations
      public:
        /**
         * Constructor
         */
        ParameterDescriptionElement(CCopasiXMLParser & parser,
                                    SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ParameterDescriptionElement();

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

  class ListOfParameterDescriptionsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * 
         */
        enum Element
        {
          ListOfParameterDescriptions = 0,
          ParameterDescription
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfParameterDescriptionsElement(CCopasiXMLParser & parser,
                                           SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfParameterDescriptionsElement();

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
      };

  class FunctionElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * 
         */
        enum Element
        {
          Function = 0,
          MathML,
          ListOfParameterDescriptions
        };

        /**
         * 
         */
        MathMLElement * mpMathMLElement;

        /**
         * 
         */
        ListOfParameterDescriptionsElement * mpListOfParameterDescriptionsElement;

        // Operations
      public:
        /**
         * Constructor
         */
        FunctionElement(CCopasiXMLParser & parser,
                        SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~FunctionElement();

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
      };

    // Operations
  public:
    /**
     * Constructor
     */
    CCopasiXMLParser();

    /**
     * Destructor
     */
    ~CCopasiXMLParser();

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

#ifdef XXXX
    /**
     * Start CDATA section handler
     */
    virtual void onStartCdataSection();

    /**
     * End CDATA section handler
     */
    virtual void onEndCdataSection();
#endif // XXXX

    /**
     * Enable/Disable the character data handler
     * @param bool fEnable (Default: true)
     */
    void enableCharacterDataHandler(bool fEnable = true);

    /**
     * Character data handler
     * @param const XML_Char *pszData
     * @param int nLength
     */
    virtual void onCharacterData(const XML_Char *pszData,
                                 int nLength);
    /**
     * Retrieve the data. 
     * Any sequence of toBeStripped characters is replaced by a single
     * join character. The default is no stripping.
     * @param const std::string & toBeStripped (default: "")
     * @param const std::string & join (default: " ")
     * @return std::string data
     */
    std::string getCharacterData(const std::string & toBeStripped = "",
                                 const std::string & join = " ");

    /**
     * Push the element handler on the stack.
     * @param CXMLHandler< CCopasiXMLParser > elementHandler
     */
    void pushElementHandler(CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon > * elementHandler);

    /**
     * Pop the element handler form the stack.
     */
    void popElementHandler();

    /**
     * Retrieve the list of loaded functions
     * @return  CCopasiVectorN< CFunction > * pFunctionList
     */
    CCopasiVectorN< CFunction > * getFunctionList() const;

    /**
     * Retrieve the loaded model functions
     * @return   CModel * pModel
     */
    CModel * getModel() const;
  };

#endif // COPASI_CCopasiXMLParser
