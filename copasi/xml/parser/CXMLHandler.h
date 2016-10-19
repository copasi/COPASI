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

class CCopasiObject;
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
    BEFORE = -1,
    UNKNOWN = 0,
    AdditionalGraphicalObject,
    Assignment,
    BasePoint1,
    BasePoint2,
    Body,
    BoundingBox,
    CallParameter,
    ChannelSpec,
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
    Group,
    GUI,
    Header,
    html,
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
    Polygon,
    Position,
    PriorityExpression,
    Problem,
    Product,
    RadialGradient,
    Reaction,
    ReactionGlyph,
    Rectangle,
    RenderCubicBezier,
    RenderInformation,
    RenderPoint,
    ReportDefinition,
    ReportTarget,
    SBMLMap,
    SBMLReference,
    Slider,
    SourceParameter,
    Start,
    StateTemplate,
    StateTemplateVariable,
    StyleLocal,
    StyleGlobal,
    Substrate,
    Table,
    Task,
    Text,
    TextGlyph,
    Unit,
    UnitDefinition,
    UnsupportedAnnotation,
    Template // Do not remove! This must be the last type.
  };

  struct sProcessLogic
  {
    std::string elementName;
    Type elementType;
    Type validElements[10];
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

  void addFix(const std::string & key, CCopasiObject * pObject);

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
  const Type mType;

  /**
   *
   */
  std::map< std::string, Type > mElementName2Type;

  /**
   *
   */
  std::map< Type, std::set< Type > > mValidElements;

  /**
   * The currently processed element.
   */
  Type mCurrentElement;

  /**
   *
   */
  Type mLastKnownElement;
};

#endif // COPASI_CXMLHandler
