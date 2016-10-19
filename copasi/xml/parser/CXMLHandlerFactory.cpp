// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"
#include "CXMLHandlerFactory.h"
#include "CXMLParser.h"

#include "UNKNOWNHandler.h"
#include "AdditionalGraphicalObjectHandler.h"
#include "AssignmentHandler.h"
#include "BasePoint1Handler.h"
#include "BasePoint2Handler.h"
#include "BodyHandler.h"
#include "BoundingBoxHandler.h"
#include "CallParameterHandler.h"
#include "ChannelSpecHandler.h"
#include "ColorDefinitionHandler.h"
#include "CommentHandler.h"
#include "CompartmentHandler.h"
#include "CompartmentGlyphHandler.h"
#include "ConstantHandler.h"
#include "COPASIHandler.h"
#include "CubicBezierHandler.h"
#include "CurveHandler.h"
#include "CurveSegmentHandler.h"
#include "DelayExpressionHandler.h"
#include "DimensionsHandler.h"
#include "EllipseHandler.h"
#include "EndHandler.h"
#include "EventHandler.h"
#include "ExpressionHandler.h"
#include "FooterHandler.h"
#include "FunctionHandler.h"
#include "GroupHandler.h"
#include "GUIHandler.h"
#include "HeaderHandler.h"
#include "htmlHandler.h"
#include "ImageHandler.h"
#include "InitialExpressionHandler.h"
#include "InitialStateHandler.h"
#include "KineticLawHandler.h"
#include "LayoutHandler.h"
#include "LinearGradientHandler.h"
#include "LineEndingHandler.h"
#include "LineSegmentHandler.h"
#include "ListOfAdditionalGraphicalObjectsHandler.h"
#include "ListOfAssignmentsHandler.h"
#include "ListOfCallParametersHandler.h"
#include "ListOfChannelsHandler.h"
#include "ListOfColorDefinitionsHandler.h"
#include "ListOfCompartmentGlyphsHandler.h"
#include "ListOfCompartmentsHandler.h"
#include "ListOfConstantsHandler.h"
#include "ListOfCurveSegmentsHandler.h"
#include "ListOfElementsHandler.h"
#include "ListOfEventsHandler.h"
#include "ListOfFunctionsHandler.h"
#include "ListOfGlobalRenderInformationHandler.h"
#include "ListOfGradientDefinitionsHandler.h"
#include "ListOfLayoutsHandler.h"
#include "ListOfLineEndingsHandler.h"
#include "ListOfMetabGlyphsHandler.h"
#include "ListOfMetaboliteReferenceGlyphsHandler.h"
#include "ListOfMetabolitesHandler.h"
#include "ListOfModelParameterSetsHandler.h"
#include "ListOfModelValuesHandler.h"
#include "ListOfModifiersHandler.h"
#include "ListOfParameterDescriptionsHandler.h"
#include "ListOfPlotItemsHandler.h"
#include "ListOfPlotsHandler.h"
#include "ListOfProductsHandler.h"
#include "ListOfReactionGlyphsHandler.h"
#include "ListOfReactionsHandler.h"
#include "ListOfRenderInformationHandler.h"
#include "ListOfReportsHandler.h"
#include "ListOfSlidersHandler.h"
#include "ListOfStylesHandler.h"
#include "ListOfSubstratesHandler.h"
#include "ListOfTasksHandler.h"
#include "ListOfTextGlyphsHandler.h"
#include "ListOfUnitDefinitionsHandler.h"
#include "ListOfUnsupportedAnnotationsHandler.h"
#include "MetaboliteHandler.h"
#include "MetaboliteGlyphHandler.h"
#include "MetaboliteReferenceGlyphHandler.h"
#include "MethodHandler.h"
#include "MiriamAnnotationHandler.h"
#include "ModelHandler.h"
#include "ModelParameterHandler.h"
#include "ModelParameterGroupHandler.h"
#include "ModelParameterSetHandler.h"
#include "ModelValueHandler.h"
#include "ModifierHandler.h"
#include "NoiseExpressionHandler.h"
#include "ObjectHandler.h"
#include "ParameterHandler.h"
#include "ParameterDescriptionHandler.h"
#include "ParameterGroupHandler.h"
#include "ParameterTextHandler.h"
#include "PlotItemHandler.h"
#include "PlotSpecificationHandler.h"
#include "PolygonHandler.h"
#include "PositionHandler.h"
#include "PriorityExpressionHandler.h"
#include "ProblemHandler.h"
#include "ProductHandler.h"
#include "RadialGradientHandler.h"
#include "ReactionHandler.h"
#include "ReactionGlyphHandler.h"
#include "RectangleHandler.h"
#include "RenderCubicBezierHandler.h"
#include "RenderInformationHandler.h"
#include "RenderPointHandler.h"
#include "ReportDefinitionHandler.h"
#include "ReportTargetHandler.h"
#include "SBMLMapHandler.h"
#include "SBMLReferenceHandler.h"
#include "SliderHandler.h"
#include "SourceParameterHandler.h"
#include "StartHandler.h"
#include "StateTemplateHandler.h"
#include "StateTemplateVariableHandler.h"
#include "StyleLocalHandler.h"
#include "StyleGlobalHandler.h"
#include "SubstrateHandler.h"
#include "TableHandler.h"
#include "TaskHandler.h"
#include "TextHandler.h"
#include "TextGlyphHandler.h"
#include "UnitHandler.h"
#include "UnitDefinitionHandler.h"
#include "UnsupportedAnnotationHandler.h"

CXMLHandlerFactory::CXMLHandlerFactory(CXMLParser & parser,
                                       CXMLParserData & data) :
  CVector< CXMLHandler * >(CXMLHandler::BEFORE),
  mpParser(&parser),
  mpData(&data)
{
  CVector< CXMLHandler * >::operator = (NULL);
}

CXMLHandlerFactory::~CXMLHandlerFactory()
{
  CXMLHandler ** ppIt = begin();
  CXMLHandler ** ppEnd = end();

  for (; ppIt != ppEnd; ++ppIt)
    {
      pdelete(*ppIt);
    }
}

CXMLHandler * CXMLHandlerFactory::getHandler(const CXMLHandler::Type & type)
{
  CXMLHandler * pHandler = CVector< CXMLHandler * >::operator[](type);

  if (pHandler == NULL)
    {
      pHandler = createHandler(type);

      assert(pHandler != NULL);
    }

  return pHandler;
}

CXMLHandler * CXMLHandlerFactory::createHandler(const CXMLHandler::Type & type)
{
  CXMLHandler * pHandler = NULL;

  switch (type)
    {
      case CXMLHandler::UNKNOWN:
        pHandler = new UNKNOWNHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::AdditionalGraphicalObject:
        pHandler = new AdditionalGraphicalObjectHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Assignment:
        pHandler = new AssignmentHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::BasePoint1:
        pHandler = new BasePoint1Handler(*mpParser, *mpData);
        break;

      case CXMLHandler::BasePoint2:
        pHandler = new BasePoint2Handler(*mpParser, *mpData);
        break;

      case CXMLHandler::Body:
        pHandler = new BodyHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::BoundingBox:
        pHandler = new BoundingBoxHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::CallParameter:
        pHandler = new CallParameterHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ChannelSpec:
        pHandler = new ChannelSpecHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ColorDefinition:
        pHandler = new ColorDefinitionHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Comment:
        pHandler = new CommentHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Compartment:
        pHandler = new CompartmentHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::CompartmentGlyph:
        pHandler = new CompartmentGlyphHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Constant:
        pHandler = new ConstantHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::COPASI:
        pHandler = new COPASIHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::CubicBezier:
        pHandler = new CubicBezierHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Curve:
        pHandler = new CurveHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::CurveSegment:
        pHandler = new CurveSegmentHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::DelayExpression:
        pHandler = new DelayExpressionHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Dimensions:
        pHandler = new DimensionsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Ellipse:
        pHandler = new EllipseHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::End:
        pHandler = new EndHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Event:
        pHandler = new EventHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Expression:
        pHandler = new ExpressionHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Footer:
        pHandler = new FooterHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Function:
        pHandler = new FunctionHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Group:
        pHandler = new GroupHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::GUI:
        pHandler = new GUIHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Header:
        pHandler = new HeaderHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::html:
        pHandler = new htmlHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Image:
        pHandler = new ImageHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::InitialExpression:
        pHandler = new InitialExpressionHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::InitialState:
        pHandler = new InitialStateHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::KineticLaw:
        pHandler = new KineticLawHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Layout:
        pHandler = new LayoutHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::LinearGradient:
        pHandler = new LinearGradientHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::LineEnding:
        pHandler = new LineEndingHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::LineSegment:
        pHandler = new LineSegmentHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfAdditionalGraphicalObjects:
        pHandler = new ListOfAdditionalGraphicalObjectsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfAssignments:
        pHandler = new ListOfAssignmentsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfCallParameters:
        pHandler = new ListOfCallParametersHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfChannels:
        pHandler = new ListOfChannelsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfColorDefinitions:
        pHandler = new ListOfColorDefinitionsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfCompartmentGlyphs:
        pHandler = new ListOfCompartmentGlyphsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfCompartments:
        pHandler = new ListOfCompartmentsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfConstants:
        pHandler = new ListOfConstantsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfCurveSegments:
        pHandler = new ListOfCurveSegmentsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfElements:
        pHandler = new ListOfElementsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfEvents:
        pHandler = new ListOfEventsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfFunctions:
        pHandler = new ListOfFunctionsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfGlobalRenderInformation:
        pHandler = new ListOfGlobalRenderInformationHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfGradientDefinitions:
        pHandler = new ListOfGradientDefinitionsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfLayouts:
        pHandler = new ListOfLayoutsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfLineEndings:
        pHandler = new ListOfLineEndingsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfMetabGlyphs:
        pHandler = new ListOfMetabGlyphsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfMetaboliteReferenceGlyphs:
        pHandler = new ListOfMetaboliteReferenceGlyphsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfMetabolites:
        pHandler = new ListOfMetabolitesHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfModelParameterSets:
        pHandler = new ListOfModelParameterSetsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfModelValues:
        pHandler = new ListOfModelValuesHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfModifiers:
        pHandler = new ListOfModifiersHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfParameterDescriptions:
        pHandler = new ListOfParameterDescriptionsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfPlotItems:
        pHandler = new ListOfPlotItemsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfPlots:
        pHandler = new ListOfPlotsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfProducts:
        pHandler = new ListOfProductsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfReactionGlyphs:
        pHandler = new ListOfReactionGlyphsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfReactions:
        pHandler = new ListOfReactionsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfRenderInformation:
        pHandler = new ListOfRenderInformationHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfReports:
        pHandler = new ListOfReportsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfSliders:
        pHandler = new ListOfSlidersHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfStyles:
        pHandler = new ListOfStylesHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfSubstrates:
        pHandler = new ListOfSubstratesHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfTasks:
        pHandler = new ListOfTasksHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfTextGlyphs:
        pHandler = new ListOfTextGlyphsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfUnitDefinitions:
        pHandler = new ListOfUnitDefinitionsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfUnsupportedAnnotations:
        pHandler = new ListOfUnsupportedAnnotationsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Metabolite:
        pHandler = new MetaboliteHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::MetaboliteGlyph:
        pHandler = new MetaboliteGlyphHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::MetaboliteReferenceGlyph:
        pHandler = new MetaboliteReferenceGlyphHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Method:
        pHandler = new MethodHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::MiriamAnnotation:
        pHandler = new MiriamAnnotationHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Model:
        pHandler = new ModelHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ModelParameter:
        pHandler = new ModelParameterHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ModelParameterGroup:
        pHandler = new ModelParameterGroupHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ModelParameterSet:
        pHandler = new ModelParameterSetHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ModelValue:
        pHandler = new ModelValueHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Modifier:
        pHandler = new ModifierHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::NoiseExpression:
        pHandler = new NoiseExpressionHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Object:
        pHandler = new ObjectHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Parameter:
        pHandler = new ParameterHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ParameterDescription:
        pHandler = new ParameterDescriptionHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ParameterGroup:
        pHandler = new ParameterGroupHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ParameterText:
        pHandler = new ParameterTextHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::PlotItem:
        pHandler = new PlotItemHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::PlotSpecification:
        pHandler = new PlotSpecificationHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Polygon:
        pHandler = new PolygonHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Position:
        pHandler = new PositionHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::PriorityExpression:
        pHandler = new PriorityExpressionHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Problem:
        pHandler = new ProblemHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Product:
        pHandler = new ProductHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::RadialGradient:
        pHandler = new RadialGradientHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Reaction:
        pHandler = new ReactionHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ReactionGlyph:
        pHandler = new ReactionGlyphHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Rectangle:
        pHandler = new RectangleHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::RenderCubicBezier:
        pHandler = new RenderCubicBezierHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::RenderInformation:
        pHandler = new RenderInformationHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::RenderPoint:
        pHandler = new RenderPointHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ReportDefinition:
        pHandler = new ReportDefinitionHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ReportTarget:
        pHandler = new ReportTargetHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::SBMLMap:
        pHandler = new SBMLMapHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::SBMLReference:
        pHandler = new SBMLReferenceHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Slider:
        pHandler = new SliderHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::SourceParameter:
        pHandler = new SourceParameterHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Start:
        pHandler = new StartHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::StateTemplate:
        pHandler = new StateTemplateHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::StateTemplateVariable:
        pHandler = new StateTemplateVariableHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::StyleLocal:
        pHandler = new StyleLocalHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::StyleGlobal:
        pHandler = new StyleGlobalHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Substrate:
        pHandler = new SubstrateHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Table:
        pHandler = new TableHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Task:
        pHandler = new TaskHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Text:
        pHandler = new TextHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::TextGlyph:
        pHandler = new TextGlyphHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Unit:
        pHandler = new UnitHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::UnitDefinition:
        pHandler = new UnitDefinitionHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::UnsupportedAnnotation:
        pHandler = new UnsupportedAnnotationHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Template:
      case CXMLHandler::BEFORE:
        break;
    }

  return pHandler;
}
