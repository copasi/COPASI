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
#include "BoundingBoxHandler.h"
#include "CallParameterHandler.h"
#include "ChannelSpecHandler.h"
#include "CharacterDataHandler.h"
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
#include "FunctionHandler.h"
#include "GroupHandler.h"
#include "GUIHandler.h"
#include "ImageHandler.h"
#include "InitialExpressionHandler.h"
#include "InitialStateHandler.h"
#include "KineticLawHandler.h"
#include "LayoutHandler.h"
#include "LinearGradientHandler.h"
#include "LineEndingHandler.h"
#include "LineSegmentHandler.h"
#include "ListOfAdditionalGraphicalObjectsHandler.h"
#include "ListOfColorDefinitionsHandler.h"
#include "ListOfCompartmentGlyphsHandler.h"
#include "ListOfCurveSegmentsHandler.h"
#include "ListOfElementsHandler.h"
#include "ListOfGlobalRenderInformationHandler.h"
#include "ListOfGradientDefinitionsHandler.h"
#include "ListOfHandler.h"
#include "ListOfLayoutsHandler.h"
#include "ListOfLineEndingsHandler.h"
#include "ListOfMetabGlyphsHandler.h"
#include "ListOfMetaboliteReferenceGlyphsHandler.h"
#include "ListOfReactionGlyphsHandler.h"
#include "ListOfRenderInformationHandler.h"
#include "ListOfStylesHandler.h"
#include "ListOfTextGlyphsHandler.h"
#include "ListOfUnitDefinitionsHandler.h"
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
#include "ProductHandler.h"
#include "RadialGradientHandler.h"
#include "ReactionHandler.h"
#include "ReactionGlyphHandler.h"
#include "RectangleHandler.h"
#include "RenderCubicBezierHandler.h"
#include "RenderInformationHandler.h"
#include "RenderPointHandler.h"
#include "ReportDefinitionHandler.h"
#include "ReportSectionHandler.h"
#include "ReportTargetHandler.h"
#include "SBMLMapHandler.h"
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
  CVector< CXMLHandler * >(CXMLHandler::HANDLER_COUNT),
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

      case CXMLHandler::BoundingBox:
        pHandler = new BoundingBoxHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::CallParameter:
        pHandler = new CallParameterHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ChannelSpec:
        pHandler = new ChannelSpecHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::CharacterData:
        pHandler = new CharacterDataHandler(*mpParser, *mpData);
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

      case CXMLHandler::Function:
        pHandler = new FunctionHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::Group:
        pHandler = new GroupHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::GUI:
        pHandler = new GUIHandler(*mpParser, *mpData);
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
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfAssignments", CXMLHandler::ListOfAssignments, CXMLHandler::ListOfAssignments};
        CXMLHandler::sProcessLogic contentLogic = {"Assignment", CXMLHandler::Assignment, CXMLHandler::Assignment};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfCallParameters:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfCallParameters", CXMLHandler::ListOfCallParameters, CXMLHandler::ListOfCallParameters};
        CXMLHandler::sProcessLogic contentLogic = {"CallParameter", CXMLHandler::CallParameter, CXMLHandler::CallParameter};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfChannels:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfChannels", CXMLHandler::ListOfChannels, CXMLHandler::ListOfChannels};
        CXMLHandler::sProcessLogic contentLogic = {"ChannelSpec", CXMLHandler::ChannelSpec, CXMLHandler::ChannelSpec};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfColorDefinitions:
        pHandler = new ListOfColorDefinitionsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfCompartmentGlyphs:
        pHandler = new ListOfCompartmentGlyphsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfCompartments:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfCompartments", CXMLHandler::ListOfCompartments, CXMLHandler::ListOfCompartments};
        CXMLHandler::sProcessLogic contentLogic = {"Compartment", CXMLHandler::Compartment, CXMLHandler::Compartment};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfConstants:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfConstants", CXMLHandler::ListOfConstants, CXMLHandler::ListOfConstants};
        CXMLHandler::sProcessLogic contentLogic = {"Constant", CXMLHandler::Constant, CXMLHandler::Constant};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }

      break;

      case CXMLHandler::ListOfCurveSegments:
        pHandler = new ListOfCurveSegmentsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfElements:
        pHandler = new ListOfElementsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfEvents:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfEvents", CXMLHandler::ListOfEvents, CXMLHandler::ListOfEvents};
        CXMLHandler::sProcessLogic contentLogic = {"Event", CXMLHandler::Event, CXMLHandler::Event};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfFunctions:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfFunctions", CXMLHandler::ListOfFunctions, CXMLHandler::ListOfFunctions};
        CXMLHandler::sProcessLogic contentLogic = {"Function", CXMLHandler::Function, CXMLHandler::Function};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
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
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfMetabolites", CXMLHandler::ListOfMetabolites, CXMLHandler::ListOfMetabolites};
        CXMLHandler::sProcessLogic contentLogic = {"Metabolite", CXMLHandler::Metabolite, CXMLHandler::Metabolite};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfModelParameterSets:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfModelParameterSets", CXMLHandler::ListOfModelParameterSets, CXMLHandler::ListOfModelParameterSets};
        CXMLHandler::sProcessLogic contentLogic = {"ModelParameterSet", CXMLHandler::ModelParameterSet, CXMLHandler::ModelParameterSet};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfModelValues:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfModelValues", CXMLHandler::ListOfModelValues, CXMLHandler::ListOfModelValues};
        CXMLHandler::sProcessLogic contentLogic = {"ModelValue", CXMLHandler::ModelValue, CXMLHandler::ModelValue};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfModifiers:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfModifiers", CXMLHandler::ListOfModifiers, CXMLHandler::ListOfModifiers};
        CXMLHandler::sProcessLogic contentLogic = {"Modifier", CXMLHandler::Modifier, CXMLHandler::Modifier};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfParameterDescriptions:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfParameterDescriptions", CXMLHandler::ListOfParameterDescriptions, CXMLHandler::ListOfParameterDescriptions};
        CXMLHandler::sProcessLogic contentLogic = {"ParameterDescription", CXMLHandler::ParameterDescription, CXMLHandler::ParameterDescription};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfPlotItems:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfPlotItems", CXMLHandler::ListOfPlotItems, CXMLHandler::ListOfPlotItems};
        CXMLHandler::sProcessLogic contentLogic = {"PlotItem", CXMLHandler::PlotItem, CXMLHandler::PlotItem};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfPlots:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfPlots", CXMLHandler::ListOfPlots, CXMLHandler::ListOfPlots};
        CXMLHandler::sProcessLogic contentLogic = {"PlotSpecification", CXMLHandler::PlotSpecification, CXMLHandler::PlotSpecification};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfProducts:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfProducts", CXMLHandler::ListOfProducts, CXMLHandler::ListOfProducts};
        CXMLHandler::sProcessLogic contentLogic = {"Product", CXMLHandler::Product, CXMLHandler::Product};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfReactionGlyphs:
        pHandler = new ListOfReactionGlyphsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfReactions:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfReactions", CXMLHandler::ListOfReactions, CXMLHandler::ListOfReactions};
        CXMLHandler::sProcessLogic contentLogic = {"Reaction", CXMLHandler::Reaction, CXMLHandler::Reaction};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfRenderInformation:
        pHandler = new ListOfRenderInformationHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfReports:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfReports", CXMLHandler::ListOfReports, CXMLHandler::ListOfReports};
        CXMLHandler::sProcessLogic contentLogic = {"Report", CXMLHandler::ReportDefinition, CXMLHandler::ReportDefinition};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfSliders:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfSliders", CXMLHandler::ListOfSliders, CXMLHandler::ListOfSliders};
        CXMLHandler::sProcessLogic contentLogic = {"Slider", CXMLHandler::Slider, CXMLHandler::Slider};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfStyles:
        pHandler = new ListOfStylesHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfSubstrates:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfSubstrates", CXMLHandler::ListOfSubstrates, CXMLHandler::ListOfSubstrates};
        CXMLHandler::sProcessLogic contentLogic = {"Substrate", CXMLHandler::Substrate, CXMLHandler::Substrate};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfTasks:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfTasks", CXMLHandler::ListOfTasks, CXMLHandler::ListOfTasks};
        CXMLHandler::sProcessLogic contentLogic = {"Task", CXMLHandler::Task, CXMLHandler::Task};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
      break;

      case CXMLHandler::ListOfTextGlyphs:
        pHandler = new ListOfTextGlyphsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfUnitDefinitions:
        pHandler = new ListOfUnitDefinitionsHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ListOfUnsupportedAnnotations:
      {
        CXMLHandler::sProcessLogic listLogic = {"ListOfUnsupportedAnnotations", CXMLHandler::ListOfUnsupportedAnnotations, CXMLHandler::ListOfUnsupportedAnnotations};
        CXMLHandler::sProcessLogic contentLogic = {"UnsupportedAnnotation", CXMLHandler::UnsupportedAnnotation, CXMLHandler::UnsupportedAnnotation};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
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

      case CXMLHandler::ReportSection:
        pHandler = new ReportSectionHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::ReportTarget:
        pHandler = new ReportTargetHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::SBMLMap:
        pHandler = new SBMLMapHandler(*mpParser, *mpData);
        break;

      case CXMLHandler::SBMLReference:
      {
        CXMLHandler::sProcessLogic listLogic = {"SBMLReference", CXMLHandler::SBMLReference, CXMLHandler::SBMLReference};
        CXMLHandler::sProcessLogic contentLogic = {"SBMLMap", CXMLHandler::SBMLMap, CXMLHandler::SBMLMap};

        pHandler = new ListOfHandler(listLogic, contentLogic, *mpParser, *mpData);
      }
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

      case CXMLHandler::HANDLER_COUNT:
      case CXMLHandler::BEFORE:
        break;
    }

  return pHandler;
}
