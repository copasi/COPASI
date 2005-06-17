/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CCopasiXMLParser.h,v $
   $Revision: 1.35 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/17 15:14:17 $
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
#include "report/CKeyFactory.h"

class CModel;
class CReaction;
class CEvaluationTree;
class CFunctionParameter;
class CCopasiXMLParser;
class CReportDefinitionVector;
class COutputDefinitionVector;
class CPlotSpecification;
class CPlotItem;
class CPlotDataChannelSpec;
class CCopasiParameter;
class CCopasiParameterGroup;
class CVersion;
class CSlider;
class SCopasiXMLGUI;

struct SCopasiXMLParserCommon
  {
    /**
     * The version of the parsed file
     */
    CVersion * pVersion;

    /**
     * The model which is build during parsing.
     */
    CModel * pModel;

    /**
     * Storage for a comment.
     */
    std::string Comment;

    /**
     * Pointer to a vector of functions which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */
    CCopasiVectorN< CEvaluationTree > * pFunctionList;

    /**
     * Pointer to the currently processed function.
     */
    CEvaluationTree * pFunction;

    /**
     * The description of the function.
     */
    std::string FunctionDescription;

    /**
     * Indicates whether the current function was already in the list;
     */
    bool mExistingFunction;

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
    //    std::map< std::string, std::string > KeyMap;
    CKeyFactory KeyMap;

    /**
     * A map relating StateVariables to Object keys
     */
    std::vector< std::string > StateVariableList;

    /**
     * Pointer to a vector of tasks which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */
    CCopasiVectorN< CCopasiTask > * pTaskList;

    /**
     * Pointer to a vector of reports which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */
    CReportDefinitionVector * pReportList;

    /**
     * Pointer to a vector of plots which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */
    COutputDefinitionVector * pPlotList;

    /**
     * Pointer to the currently processed report
     */
    CReportDefinition * pReport;

    /**
     * Pointer to the currently processed task
     */
    CCopasiTask* pCurrentTask;

    /**
     * Pointer to the currently processed parameter
     */
    CCopasiParameter* pCurrentParameter;

    /**
     * Stack of parameter groups which is needed since nesting 
     * of groups is possible.
     */
    std::stack< CCopasiParameterGroup * > ParameterGroupStack;
    //    CCopasiParameterGroup* pCurrentParameterGroup;

    /**
     * Pointer to the currently processed plot
     */
    CPlotSpecification* pCurrentPlot;

    /**
     * Pointer to the currently processed plot item.
     */
    CPlotItem* pCurrentPlotItem;

    /**
     * Pointer to the currently processed channel.
     */
    CPlotDataChannelSpec* pCurrentChannelSpec;

    /**
     * Nesting level of the currently processed parameter group
     */
    int mParameterGroupLevel;

    /**
     * A map that stores a vector of tasks that reference a certain key
     * together with the key to the reference.
     */
    std::map<std::string , std::vector < CCopasiTask* > > taskReferenceMap;

    /**
     * A map that stores a vector of pairs of header,body or footer adresses
     *  with the index together with the key to the reference.
     */
    std::map<std::string , std::vector < std::pair < std::vector <CRegisteredObjectName >*, unsigned int > > > reportReferenceMap;

    SCopasiXMLGUI * pGUI;
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

  class UnknownElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Unknown = 0
        };

        /**
         * The line number the unknown element was encountered.
         */
        unsigned C_INT32 mLineNumber;

        // Operations
      public:
        /**
         * Constructor
         */
        UnknownElement(CCopasiXMLParser & parser,
                       SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~UnknownElement();

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

  public:
    /**
     *
     */
    UnknownElement mUnknownElement;

  private:

  class InitialStateElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          InitialState = 0,
          etc
        };

        // Operations
      public:
        /**
         * Constructor
         */
        InitialStateElement(CCopasiXMLParser & parser,
                            SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~InitialStateElement();

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

  class StateTemplateVariableElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          StateTemplateVariable = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        StateTemplateVariableElement(CCopasiXMLParser & parser,
                                     SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~StateTemplateVariableElement();

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

  class StateTemplateElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          StateTemplate = 0,
          StateTemplateVariable
        };

        // Operations
      public:
        /**
         * Constructor
         */
        StateTemplateElement(CCopasiXMLParser & parser,
                             SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~StateTemplateElement();

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

  class SourceParameterElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          SourceParameter = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        SourceParameterElement(CCopasiXMLParser & parser,
                               SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~SourceParameterElement();

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

  class ModelValueElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          ModelValue = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ModelValueElement(CCopasiXMLParser & parser,
                          SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ModelValueElement();

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

  class ListOfModelValuesElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          ListOfModelValues = 0,
          ModelValue
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfModelValuesElement(CCopasiXMLParser & parser,
                                 SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfModelValuesElement();

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
          ListOfModelValues,
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

  class ChannelSpecElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * 
         */
        enum Element
        {
          ChannelSpec = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ChannelSpecElement(CCopasiXMLParser & parser,
                           SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ChannelSpecElement();

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

  class PlotItemElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * 
         */
        enum Element
        {
          PlotItem = 0,
          Parameter,
          ParameterGroup,
          ListOfChannels
        };

        /**
         * The line number the unknown parameter was encountered.
         */
        unsigned C_INT32 mLineNumber;

        // Operations
      public:
        /**
         * Constructor
         */
        PlotItemElement(CCopasiXMLParser & parser,
                        SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~PlotItemElement();

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

  class ListOfChannelsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * 
         */
        enum Element
        {
          ListOfChannels = 0,
          ChannelSpec
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfChannelsElement(CCopasiXMLParser & parser,
                              SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfChannelsElement();

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

  class ListOfPlotItemsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * 
         */
        enum Element
        {
          ListOfPlotItems = 0,
          PlotItem
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfPlotItemsElement(CCopasiXMLParser & parser,
                               SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfPlotItemsElement();

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

  class PlotSpecificationElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * 
         */
        enum Element
        {
          PlotSpecification = 0,
          Parameter,
          ParameterGroup,
          ListOfChannels,
          ListOfPlotItems
        };

        // Operations
      public:
        /**
         * Constructor
         */
        PlotSpecificationElement(CCopasiXMLParser & parser,
                                 SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~PlotSpecificationElement();

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

  class ListOfPlotsElement : public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * 
         */
        enum Element
        {
          ListOfPlots = 0,
          PlotSpecification
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfPlotsElement(CCopasiXMLParser & parser,
                           SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfPlotsElement();

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
          ListOfTasks = 0,
          Task
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

  class ReportInstanceElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Report = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ReportInstanceElement(CCopasiXMLParser & parser,
                              SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ReportInstanceElement();

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

  class ProblemInitialStateElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          InitialState = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ProblemInitialStateElement(CCopasiXMLParser & parser,
                                   SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ProblemInitialStateElement();

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

  class ParameterElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Parameter = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ParameterElement(CCopasiXMLParser & parser,
                         SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ParameterElement();

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

  class ParameterGroupElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          ParameterGroup = 0,
          Parameter
        };

        CCopasiParameterGroup* oldGroup;
        ParameterElement* mpParameterHandler;
        ParameterGroupElement* mpParameterGroupHandler;

        int level;

        // Operations
      public:
        /**
         * Constructor
         */
        ParameterGroupElement(CCopasiXMLParser & parser,
                              SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ParameterGroupElement();

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

  class ProblemElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Problem = 0,
          Parameter,
          ParameterGroup,
          InitialState
        };

        ProblemInitialStateElement* mpInitialStateHandler;
        ParameterGroupElement* mpParameterGroupHandler;
        ParameterElement* mpParameterHandler;

        /**
         * The line number the unknown parameter was encountered.
         */
        unsigned C_INT32 mLineNumber;

        // Operations
      public:
        /**
         * Constructor
         */
        ProblemElement(CCopasiXMLParser & parser,
                       SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ProblemElement();

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

  class MethodElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Method = 0,
          Parameter,
          ParameterGroup
        };

        ParameterElement* mpParameterHandler;
        ParameterGroupElement* mpParameterGroupHandler;

        /**
         * The line number the unknown parameter was encountered.
         */
        unsigned C_INT32 mLineNumber;

        // Operations
      public:
        /**
         * Constructor
         */
        MethodElement(CCopasiXMLParser & parser,
                      SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~MethodElement();

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

  class TaskElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Task = 0,
          Report,
          Problem,
          Method
        };

        ReportInstanceElement* mpReportElement;
        ProblemElement* mpProblemElement;
        MethodElement* mpMethodElement;

        // Operations
      public:
        /**
         * Constructor
         */
        TaskElement(CCopasiXMLParser & parser,
                    SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~TaskElement();

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
          ListOfReports = 0,
          Report
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
          Text,
          Report
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
          Object,
          Text,
          Report
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
          Text,
          Report
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

  class TableElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Table = 0,
          Object
        };

        // Operations
      public:
        /**
         * Constructor
         */
        TableElement(CCopasiXMLParser & parser,
                     SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~TableElement();

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
          Body,
          Footer,
          Table
        };

        CommentElement * mpCommentElement;
        HeaderElement * mpHeaderElement;
        BodyElement * mpBodyElement;
        FooterElement * mpFooterElement;
        TableElement* mpTableElement;

        bool tableFound;
        bool otherFound;

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
          ListOfReports,
          ListOfPlots,
          GUI
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

  class GUIElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          GUI = 0,
          ListOfSliders
        };

        // Operations
      public:
        /**
         * Constructor
         */
        GUIElement(CCopasiXMLParser & parser,
                   SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~GUIElement();

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

  class ListOfSlidersElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          ListOfSliders = 0,
          Slider
        };

        // Operations
      public:
        /**
         * Constructor
         */
        ListOfSlidersElement(CCopasiXMLParser & parser,
                             SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~ListOfSlidersElement();

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

  class SliderElement:
          public CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >
      {
        // Attributes
      private:
        /**
         * Enum of invoked parsers
         */
        enum Element
        {
          Slider = 0
        };

        // Operations
      public:
        /**
         * Constructor
         */
        SliderElement(CCopasiXMLParser & parser,
                      SCopasiXMLParserCommon & common);

        /**
         * Destructor
         */
        virtual ~SliderElement();

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
  private:
    /**
     * Constructor
     */
    CCopasiXMLParser();

  public:
    /**
     * Public constructor
     * @param CVersion & version
     */
    CCopasiXMLParser(CVersion & version);

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
     * Set the list of loaded functions
     * @param CCopasiVectorN< CEvaluationTree > * pFunctionList
     */
    void setFunctionList(CCopasiVectorN< CEvaluationTree > * pFunctionList);

    /**
     * Retrieve the list of loaded functions
     * @return CCopasiVectorN< CEvaluationTree > * pFunctionList
     */
    CCopasiVectorN< CEvaluationTree > * getFunctionList() const;

    /**
     * Set the loaded model functions
     * @param CModel * pModel
     */
    void setModel(CModel * pModel);

    /**
     * Retrieve the loaded model functions
     * @return CModel * pModel
     */
    CModel * getModel() const;

    /**
     * Set the list of loaded reports
     * @param CReportDefinitionVector * pReportList
     */
    void setReportList(CReportDefinitionVector * pReportList);

    /**
     * Retrieve the list of loaded reports
     * @return CReportDefinitionVector * pReportList
     */
    CReportDefinitionVector * CCopasiXMLParser::getReportList() const;

    //Mrinmayee
    /**
        * Set the list of loaded tasks
        * @param CCopasiVectorN< CCopasiTask > * pTaskList
        */
    void setTaskList(CCopasiVectorN< CCopasiTask > * pTaskList);

    /**
     * Retrieve the list of loaded functions
     * @return CCopasiVectorN< CTask > * pTaskList
     */
    CCopasiVectorN< CCopasiTask > * getTaskList() const;

    /**
     * Set the list of loaded plots
     * @param COutputDefinitionVector * pPlotList
     */
    void setPlotList(COutputDefinitionVector * pPlotList);

    /**
     * Retrieve the list of loaded functions
     * @return COutputDefinitionVector * pPlotList
     */
    COutputDefinitionVector * getPlotList() const;

    /**
     * Set the GUI information to be saved
     * @param SCopasiXMLGUI * pGUI
     */
    void setGUI(SCopasiXMLGUI * pGUI);

    /**
     * Retrieve the GUI information
     * @return SCopasiXMLGUI * pGUI
     */
    SCopasiXMLGUI * getGUI() const;

    /**
     * Retrieve an object by its CN within the context of the parser
     * @param const std::string & cn
     * @return const CCopasiObject * pObject
     */
    const CCopasiObject * getObjectFromName(const std::string & cn) const;
  };

#endif // COPASI_CCopasiXMLParser
