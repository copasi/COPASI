// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
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
#include <map>
#include <set>

#include "expat.h"

class CDataObject;
class CXMLParser;
class CXMLParserData;

class CXMLHandler
{
private:
  /**
   * Default Constructor
   */
  CXMLHandler();

public:

  enum Type
  {
    BEFORE = 0,
    AFTER,
    UNKNOWN,
    AdditionalGraphicalObject,
    Assignment,
    BasePoint1,
    BasePoint2,
    Body,
    BoundingBox,
    CallParameter,
    ChannelSpec,
    CharacterData,
    ColorDefinition,
    Comment,
    Compartment,
    CompartmentGlyph,
    Constant,
    COPASI,
    CubicBezier,
    Curve,
    CurveSegment,
    DelayExpression,
    Dimensions,
    Ellipse,
    End,
    Event,
    Expression,
    Footer,
    Function,
    GradientStop,
    Group,
    GUI,
    Header,
    Image,
    InitialExpression,
    InitialState,
    KineticLaw,
    Layout,
    LinearGradient,
    LineEnding,
    LineSegment,
    ListOfAdditionalGraphicalObjects,
    ListOfAssignments,
    ListOfCallParameters,
    ListOfChannels,
    ListOfColorDefinitions,
    ListOfCompartmentGlyphs,
    ListOfCompartments,
    ListOfConstants,
    ListOfCurveSegments,
    ListOfElements,
    ListOfEvents,
    ListOfFunctions,
    ListOfGlobalRenderInformation,
    ListOfGradientDefinitions,
    ListOfLayouts,
    ListOfLineEndings,
    ListOfMetabGlyphs,
    ListOfMetaboliteReferenceGlyphs,
    ListOfMetabolites,
    ListOfModelParameterSets,
    ListOfModelValues,
    ListOfModifiers,
    ListOfParameterDescriptions,
    ListOfPlotItems,
    ListOfPlots,
    ListOfProducts,
    ListOfReactionGlyphs,
    ListOfReactions,
    ListOfRenderInformation,
    ListOfReports,
    ListOfSliders,
    ListOfStyles,
    ListOfSubstrates,
    ListOfTasks,
    ListOfTextGlyphs,
    ListOfUnitDefinitions,
    ListOfUnsupportedAnnotations,
    MathML,
    Metabolite,
    MetaboliteGlyph,
    MetaboliteReferenceGlyph,
    Method,
    MiriamAnnotation,
    Model,
    ModelParameter,
    ModelParameterGroup,
    ModelParameterSet,
    ModelValue,
    Modifier,
    NoiseExpression,
    Object,
    Parameter,
    ParameterDescription,
    ParameterGroup,
    ParameterText,
    PlotItem,
    PlotSpecification,
    Point,
    Polygon,
    Position,
    PriorityExpression,
    Problem,
    Product,
    RadialGradient,
    Reaction,
    ReactionGlyph,
    Rectangle,
    RenderCurve,
    RenderCurveElement,
    RenderInformation,
    RenderText,
    ReportDefinition,
    ReportSection,
    ReportTarget,
    SBMLMap,
    SBMLReference,
    Slider,
    SourceParameter,
    Start,
    StateTemplate,
    StateTemplateVariable,
    Style,
    Substrate,
    Table,
    Task,
    Text,
    TextGlyph,
    TriggerExpression,
    Unit,
    UnitDefinition,
    UnsupportedAnnotation,
    HANDLER_COUNT // Do not remove! This must be the last type.
  };

  struct sProcessLogic
  {
    std::string elementName;
    Type elementType;
    Type handlerType;
    Type validElements[15];
  };

  // Operations
  /**
   * Constructor
   * @param CXMLParser & parser
   * @param CXMLParserData & data
   * @param const CXMLHandler::Type & type
   */
  CXMLHandler(CXMLParser & parser,
              CXMLParserData & data,
              const Type & type);

  /**
   * Destructor
   */
  virtual ~CXMLHandler();

  /**
   * Start element handler
   * @param const XML_Char *pszName
   * @param const XML_Char **papszAttrs
   */
  virtual void start(const XML_Char * pszName,
                     const XML_Char ** papszAttrs);

  /**
   * End element handler
   * @param const XML_Char *pszName
   */
  virtual void end(const XML_Char * pszName);

protected:
  /**
   * Process the start of an element
   * @param const XML_Char *pszName
   * @param const XML_Char **papszAttrs
   * @return CXMLHandler * pHandlerToCall
   */
  virtual CXMLHandler * processStart(const XML_Char * pszName,
                                     const XML_Char ** papszAttrs) = 0;

  /**
   * Process the end of an element
   * @param const XML_Char *pszName
   * @return bool finished
   */
  virtual bool processEnd(const XML_Char * pszName) = 0;

  /**
   * Retrieve the structure containing the process logic for the handler.
   * @return sProcessLogic *
   */
  virtual sProcessLogic * getProcessLogic() const = 0;

  CXMLHandler * getHandler(const Type & type);

  void addFix(const std::string & key, CDataObject * pObject);

  void init();

  std::string getElementName(const Type & type) const;
  std::string getExpectedElements(const Type & type) const;

  // Attributes
protected:
  /**
   * The underlying parser.
   */
  CXMLParser * mpParser;

  /**
   * The shared elements between all element handlers of a parser
   */
  CXMLParserData * mpData;

  /**
   *
   */
  const Type mHandlerType;

  /**
   *
   */
  Type mElementType;

  /**
   *
   */
  std::map< std::string, std::pair< Type, Type > > mElementName2Type;

  /**
   *
   */
  std::map< Type, std::set< Type > > mValidElements;

  /**
   * The currently processed element.
   */
  std::pair< Type, Type > mCurrentElement;

  /**
   *
   */
  std::pair< Type, Type > mLastKnownElement;

  /**
   *
   */
  size_t mLevel;
};

#endif // COPASI_CXMLHandler
