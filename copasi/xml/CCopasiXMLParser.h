/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CCopasiXMLParser.h,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/05 14:36:55 $
   End CVS Header */

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
#include <string>

#include "CExpat.h"
#include "CXMLHandler.h"
#include "utilities/CCopasiVector.h"

class CModel;
class CReaction;
class CFunction;
class CFunctionParameter;
class CCopasiXMLParser;
class CReportDefinition;

struct SCopasiXMLParserCommon
  {
    CCopasiXMLParser * pParser;

    CModel * pModel;

    /**
     * Storage for a comment.
     */
    std::string Comment;

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
     * The description of the function.
     */
    std::string FunctionDescription;

    /**
        * Pointer to the currently processed reaction.
        */
    CReaction * pReaction;

    /**
     * The keys of the source parameters for a call parameter.
     */
    std::vector< std::string > SourceParameterKeys;

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
    CCopasiVectorN< CReportDefinition > * pReportList;

    /**
     * Pointer to the currently processed report
     */
    CReportDefinition * pReport;
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

#ifdef  COPASI_TEMPLATE
  class TEMPLATEElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          TEMPLATE = 0,
          etc
        };

        // Operations
      public:
        /**
         * Constructor
         */
        TEMPLATEElement(CCopasiXMLParser & parser,
                        SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~TEMPLATEElement();

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

#endif // COPASI_TEMPLATE

  class CallParameterElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          CallParameter = 0,
          SourceParameter
        };

        /**
         * A pointer to the function parameter.
         */
        CFunctionParameter * mpFunctionParameter;

        // Operations
      public:
        /**
         * Constructor
         */
        CallParameterElement(CCopasiXMLParser & parser,
                             SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~CallParameterElement();

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

  class ListOfCallParametersElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          ListOfCallParameters = 0,
          CallParameter
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfCallParametersElement(CCopasiXMLParser & parser,
                                    SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfCallParametersElement();

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

  class KineticLawElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          KineticLaw = 0,
          ListOfCallParameters
        };

        // Operations
      public:
        /**
         * Constructor
         */
        KineticLawElement(CCopasiXMLParser & parser,
                          SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~KineticLawElement();

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

  class ConstantElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Constant = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ConstantElement(CCopasiXMLParser & parser,
                        SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ConstantElement();

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

  class ListOfConstantsElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          ListOfConstants = 0,
          Constant
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfConstantsElement(CCopasiXMLParser & parser,
                               SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfConstantsElement();

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

  class ModifierElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Modifier = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ModifierElement(CCopasiXMLParser & parser,
                        SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ModifierElement();

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

  class ListOfModifiersElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          ListOfModifiers = 0,
          Modifier
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfModifiersElement(CCopasiXMLParser & parser,
                               SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfModifiersElement();

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

  class ProductElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Product = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ProductElement(CCopasiXMLParser & parser,
                       SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ProductElement();

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

  class ListOfProductsElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          ListOfProducts = 0,
          Product
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfProductsElement(CCopasiXMLParser & parser,
                              SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfProductsElement();

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

  class SubstrateElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Substrate = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        SubstrateElement(CCopasiXMLParser & parser,
                         SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~SubstrateElement();

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

  class ListOfSubstratesElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          ListOfSubstrates = 0,
          Substrate
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfSubstratesElement(CCopasiXMLParser & parser,
                                SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfSubstratesElement();

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

  class ReactionElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Reaction = 0,
          ListOfSubstrates,
          ListOfProducts,
          ListOfModifiers,
          ListOfConstants,
          KineticLaw
        };

        /**
         * Pointer to ListOfSubstratesElement element handler.
         */
        ListOfSubstratesElement * mpListOfSubstratesElement;

        /**
         * Pointer to ListOfProductsElement element handler.
         */
        ListOfProductsElement * mpListOfProductsElement;

        /**
         * Pointer to ListOfModifiersElement element handler.
         */
        ListOfModifiersElement * mpListOfModifiersElement;

        /**
         * Pointer to ListOfConstantsElement element handler.
         */
        ListOfConstantsElement * mpListOfConstantsElement;

        /**
         * Pointer to ListOfConstantsElement element handler.
         */
        KineticLawElement * mpKineticLawElement;

        // Operations
      public:
        /**
         * Constructor
         */
        ReactionElement(CCopasiXMLParser & parser,
                        SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ReactionElement();

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

  class ListOfReactionsElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          ListOfReactions = 0,
          Reaction
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfReactionsElement(CCopasiXMLParser & parser,
                               SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfReactionsElement();

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

  class MetaboliteElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Metabolite = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        MetaboliteElement(CCopasiXMLParser & parser,
                          SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~MetaboliteElement();

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

  class ListOfMetabolitesElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          ListOfMetabolites = 0,
          Metabolite
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfMetabolitesElement(CCopasiXMLParser & parser,
                                 SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfMetabolitesElement();

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

  class CompartmentElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Compartment = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        CompartmentElement(CCopasiXMLParser & parser,
                           SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~CompartmentElement();

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

  class ListOfCompartmentsElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          ListOfCompartments = 0,
          Compartment
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfCompartmentsElement(CCopasiXMLParser & parser,
                                  SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfCompartmentsElement();

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

  class CommentElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Comment = 0,
          Ignore
        };

        // Operations
      public:
        /**
         * Constructor
         */
        CommentElement(CCopasiXMLParser & parser,
                       SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~CommentElement();

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

  class ModelElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Model = 0,
          Comment,
          ListOfCompartments,
          ListOfMetabolites,
          ListOfReactions,
          StateTemplate,
          InitialState
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

  class ObjectElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Object
         */
        enum Element
        {
          Object = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ObjectElement(CCopasiXMLParser & parser,
                      SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ObjectElement();

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

  class ComplexElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Complex
         */
        enum Element
        {
          Complex = 0,
          Object,
          Text
          //Report
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ComplexElement(CCopasiXMLParser & parser,
                       SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ComplexElement();

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

  class HeaderElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Header
         */
        enum Element
        {
          Header = 0,
          Object,
          Text
          /*Report*/
        };

        // Operations
      public:
        /**
         * Constructor
         */
        HeaderElement(CCopasiXMLParser & parser,
                      SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~HeaderElement();

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

  class BodyElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Body
         */
        enum Element
        {
          Body = 0,
          Complex
          //Table
        };

        // Operations
      public:
        /**
         * Constructor
         */
        BodyElement(CCopasiXMLParser & parser,
                    SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~BodyElement();

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

#ifdef XXXX
  class FooterElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         *  Footer
         */
        enum Element
        {
          Footer = 0,
          Object,
          Text
          // Report
        };

        // Operations
      public:
        /**
         * Constructor
         */
        FooterElement(CCopasiXMLParser & parser,
                      SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~FooterElement();

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
#endif // XXXX

  class ReportElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Report
         */
        enum Element
        {
          Report = 0,
          Comment,
          Header,
          Body
          //Footer
        };

        CommentElement * mpCommentElement;
        HeaderElement * mpHeaderElement;
        BodyElement * mpBodyElement;
        //FooterElement * mpFooterElement;

        // Operations
      public:
        /**
         * Constructor
         */
        ReportElement(CCopasiXMLParser & parser,
                      SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ReportElement();

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
