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

struct SCopasiXMLParserCommon
  {
    std::stack< CXMLElementHandler * > ElementHandlerStack;

    std::string CharacterData;

    CExpat * pParser;

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

  class ModelElement : public CXMLElementHandler
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

        /**
         * Attributes accessible through the whole parser.
         */
        SCopasiXMLParserCommon & mCommon;

        // Operations
      public:
        /**
         * Constructor
         */
        ModelElement(SCopasiXMLParserCommon & common);

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

  class ListOfTasksElement : public CXMLElementHandler
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

        /**
         * Attributes accessible through the whole parser.
         */
        SCopasiXMLParserCommon & mCommon;

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfTasksElement(SCopasiXMLParserCommon & common);

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

  class ListOfReportsElement : public CXMLElementHandler
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

        /**
         * Attributes accessible through the whole parser.
         */
        SCopasiXMLParserCommon & mCommon;

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfReportsElement(SCopasiXMLParserCommon & common);

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
  class COPASIElement : public CXMLElementHandler
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

        /**
         * Attributes accessible through the whole parser.
         */
        SCopasiXMLParserCommon & mCommon;

        // Operations
      public:
        /**
         * Constructor
         */
        COPASIElement(SCopasiXMLParserCommon & common);

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

  class ListOfFunctionsElement : public CXMLElementHandler
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

        /**
         * Attributes accessible through the whole parser.
         */
        SCopasiXMLParserCommon & mCommon;

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfFunctionsElement(SCopasiXMLParserCommon & common);

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

  class TextElement : public CXMLElementHandler
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

        /**
         * Attributes accessible through the whole parser.
         */
        SCopasiXMLParserCommon & mCommon;

        // Operations
      public:
        /**
         * Constructor
         */
        TextElement(SCopasiXMLParserCommon & common);

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

  class MathMLElement : public CXMLElementHandler
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

        /**
         * Attributes accessible through the whole parser.
         */
        SCopasiXMLParserCommon & mCommon;

        // Operations
      public:
        /**
         * Constructor
         */
        MathMLElement(SCopasiXMLParserCommon & common);

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

  class ParameterDescriptionElement : public CXMLElementHandler
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
         * Attributes accessible through the whole parser.
         */
        SCopasiXMLParserCommon & mCommon;

        /**
         * Order
         */
        unsigned C_INT32 mOrder;

        // Operations
      public:
        /**
         * Constructor
         */
        ParameterDescriptionElement(SCopasiXMLParserCommon & common);

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

  class ListOfParameterDescriptionsElement : public CXMLElementHandler
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

        /**
         * Attributes accessible through the whole parser.
         */
        SCopasiXMLParserCommon & mCommon;

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfParameterDescriptionsElement(SCopasiXMLParserCommon & common);

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

  class FunctionElement : public CXMLElementHandler
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
         * Attributes accessible through the whole parser.
         */
        SCopasiXMLParserCommon & mCommon;

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
        FunctionElement(SCopasiXMLParserCommon & common);

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
     * Character data handler
     * @param const XML_Char *pszData
     * @param int nLength
     */
    virtual void onCharacterData(const XML_Char *pszData,
                                 int nLength);
  };

#endif // COPASI_CCopasiXMLParser
