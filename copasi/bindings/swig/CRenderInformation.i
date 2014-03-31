// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 



%ignore GlobalRenderInformation;
%ignore GlobalStyle;
%ignore GradientBase;
%ignore GradientStop;
%ignore GraphicalObject;
%ignore GraphicalPrimitive1D;
%ignore GraphicalPrimitive2D;
%ignore Image;
%ignore LinearGradient;
%ignore LineEnding;
%ignore LocalRenderInformation;
%ignore LocalStyle;
%ignore RadialGradient;
%ignore RelAbsVector;
%ignore RenderCubicBezier;
%ignore RenderCurve;
%ignore RenderGroup;
%ignore RenderInformationBase;
%ignore RenderPoint;
%ignore sbmlEllipse;
%ignore sbmlPolygon;
%ignore sbmlRectangle;

#if SWIGCSHARP

%csmethodmodifiers  CLColorDefinition::getKey  "public new"
%csmethodmodifiers  CLEllipse::getKey  "public new"
%csmethodmodifiers  CLStyle::getKey  "public new"
%csmethodmodifiers  CLGradientBase::getKey  "public new"
%csmethodmodifiers  CLGradientStop::getKey  "public new"
%csmethodmodifiers  CLGroup::getKey  "public new"
%csmethodmodifiers  CLImage::getKey  "public new"
%csmethodmodifiers  CLLineEnding::getKey  "public new"
%csmethodmodifiers  CLPolygon::getKey  "public new"
%csmethodmodifiers  CLRenderInformationBase::getKey  "public new"
%csmethodmodifiers  CLRectangle::getKey  "public new"
%csmethodmodifiers  CLRenderCurve::getKey  "public new"
%csmethodmodifiers  CLText::getKey  "public new"

#endif

%ignore CLLocalStyle::isInKeyList;
%ignore CLRectangle::CLRectangle(const sbmlRectangle& source, CCopasiContainer* pParent = NULL);
%ignore CLRectangle::toSBML;
%ignore CLEllipse::CLEllipse(const sbmlEllipse& source, CCopasiContainer* pParent = NULL);
%ignore CLEllipse::toSBML;
%ignore CLPolygon::CLPolygon(const sbmlPolygon& source, CCopasiContainer* pParent = NULL);
%ignore CLPolygon::toSBML;
%ignore CLLocalRenderInformation::toSBML;
%ignore CLLocalRenderInformation::  CLLocalRenderInformation(const LocalRenderInformation& source,
                           CCopasiContainer* pParent = NULL);
%ignore CLGlobalRenderInformation::CLGlobalRenderInformation(const GlobalRenderInformation& source,
                            CCopasiContainer* pParent = NULL);
%ignore CLGlobalRenderInformation::toSBML;
%ignore CLGlyphWithCurve::CLGlyphWithCurve(const GraphicalObject & sbml, //TODO preliminary
                   const std::map<std::string, std::string> & modelmap,
                   std::map<std::string, std::string> & layoutmap,
                   const CCopasiContainer * pParent = NULL);
%ignore CLGeneralGlyph::CLGeneralGlyph(const GraphicalObject & sbml,
                 const std::map<std::string, std::string> & modelmap,
                 std::map<std::string, std::string> & layoutmap,
                 const CCopasiContainer * pParent = NULL);
%ignore CLColorDefinition::toSBML;
%ignore CLColorDefinition::CLColorDefinition(const ColorDefinition& source, CCopasiContainer* pParent = NULL);
%ignore CLGlobalStyle::CLGlobalStyle(const GlobalStyle& source, CCopasiContainer* pParent = NULL);
%ignore CLGlobalStyle::toSBML;
%ignore CLGradientBase::CLGradientBase(const GradientBase& source, const std::string& name, CCopasiContainer* pParent = NULL);
%ignore CLGradientBase::addSBMLAttributes;
%ignore CLGradientStop::toSBML;
%ignore CLGradientStop::CLGradientStop(const GradientStop& source, CCopasiContainer* pParent = NULL);
%ignore CLGraphicalPrimitive1D::CLGraphicalPrimitive1D(const GraphicalPrimitive1D& source);
%ignore CLGraphicalPrimitive1D::addSBMLAttributes;
%ignore CLGraphicalPrimitive2D::CLGraphicalPrimitive2D(const GraphicalPrimitive2D& source);
%ignore CLGraphicalPrimitive2D::addSBMLAttributes;
%ignore CLGroup::toSBML;
%ignore CLGroup::CLGroup(const RenderGroup& source, CCopasiContainer* pParent = NULL);
%ignore CLImage::toSBML;
%ignore CLImage::CLImage(const Image& source, CCopasiContainer* pParent = NULL);
%ignore CLLineEnding::toSBML;
%ignore CLLineEnding::CLLineEnding(const LineEnding& source, CCopasiContainer* pParent = NULL);
%ignore CLLinearGradient::toSBML;
%ignore CLLinearGradient::CLLinearGradient(const LinearGradient& source, CCopasiContainer* pParent = NULL);
%ignore CLLocalStyle::toSBML;
%ignore CLLocalStyle::CLLocalStyle(const LocalStyle& source, CCopasiContainer* pParent = NULL);
%ignore CLRadialGradient::toSBML;
%ignore CLRadialGradient::CLRadialGradient(const RadialGradient& source, CCopasiContainer* pParent = NULL);
%ignore CLRelAbsVector::toSBML;
%ignore CLRelAbsVector::CLRelAbsVector(const RelAbsVector& source);
%ignore CLRenderInformationBase::CLRenderInformationBase(const RenderInformationBase& source,
                          const std::string& name,
                          CCopasiContainer* pParent = NULL);
%ignore CLRenderInformationBase::addSBMLAttributes;
%ignore CLRenderCubicBezier::toSBML;
%ignore CLRenderCubicBezier::CLRenderCubicBezier(const RenderCubicBezier& source);
%ignore CLRenderCurve::toSBML;
%ignore CLRenderCurve::CLRenderCurve(const RenderCurve& source, CCopasiContainer* pParent = NULL);
%ignore CLRenderPoint::addSBMLAttributes;
%ignore CLRenderPoint::toSBML;
%ignore CLRenderPoint::CLRenderPoint(const RenderPoint& source);
%ignore CLStyle::CLStyle(const Style& source, const std::string& name, CCopasiContainer* pParent = NULL);
%ignore CLStyle::addSBMLAttributes;
%ignore CLText::toSBML;
%ignore CLText::CLText(const Text& source, CCopasiContainer* pParent = NULL);


%{

#include <copasi/layout/CLColorDefinition.h>
#include <copasi/layout/CLGradientStop.h>
#include <copasi/layout/CLGradientBase.h>
#include <copasi/layout/CLLinearGradient.h>
#include <copasi/layout/CLRadialGradient.h>
#include <copasi/layout/CLStyle.h>
#include <copasi/layout/CLGlobalStyle.h>
#include <copasi/layout/CLLocalStyle.h>
#include <copasi/layout/CLTransformation.h>
#include <copasi/layout/CLTransformation2D.h>
#include <copasi/layout/CLGraphicalPrimitive1D.h>
#include <copasi/layout/CLGraphicalPrimitive2D.h>
#include <copasi/layout/CLRelAbsVector.h>
#include <copasi/layout/CLRenderPoint.h>
#include <copasi/layout/CLRenderCurve.h>
#include <copasi/layout/CLRenderCubicBezier.h>
#include <copasi/layout/CLRectangle.h>
#include <copasi/layout/CLEllipse.h>
#include <copasi/layout/CLGroup.h>
#include <copasi/layout/CLImage.h>
#include <copasi/layout/CLPolygon.h>
#include <copasi/layout/CLText.h>
#include <copasi/layout/CLLineEnding.h>
#include <copasi/layout/CLRenderInformationBase.h>
#include <copasi/layout/CLLocalRenderInformation.h>
#include <copasi/layout/CLGlobalRenderInformation.h>



%}

%include <copasi/layout/CLColorDefinition.h>
%include <copasi/layout/CLGradientStop.h>
%include <copasi/layout/CLGradientBase.h>
%include <copasi/layout/CLLinearGradient.h>
%include <copasi/layout/CLRadialGradient.h>
%include <copasi/layout/CLStyle.h>
%include <copasi/layout/CLGlobalStyle.h>
%include <copasi/layout/CLLocalStyle.h>
%include <copasi/layout/CLTransformation.h>
%include <copasi/layout/CLTransformation2D.h>
%include <copasi/layout/CLGraphicalPrimitive1D.h>
%include <copasi/layout/CLGraphicalPrimitive2D.h>
%include <copasi/layout/CLRelAbsVector.h>
%include <copasi/layout/CLRenderPoint.h>
%include <copasi/layout/CLRenderCurve.h>
%include <copasi/layout/CLRenderCubicBezier.h>
%include <copasi/layout/CLRectangle.h>
%include <copasi/layout/CLEllipse.h>
%include <copasi/layout/CLGroup.h>
%include <copasi/layout/CLImage.h>
%include <copasi/layout/CLPolygon.h>
%include <copasi/layout/CLText.h>
%include <copasi/layout/CLLineEnding.h>
%include <copasi/layout/CLRenderInformationBase.h>
%include <copasi/layout/CLLocalRenderInformation.h>
%include <copasi/layout/CLGlobalRenderInformation.h>





%template(ColorDefinitionVector) CCopasiVector<CLColorDefinition>;
%template(GlobalRenderInformationVector) CCopasiVector<CLGlobalRenderInformation>;
%template(GlobalStyleVector) CCopasiVector<CLGlobalStyle>;
%template(LocalStyleVector) CCopasiVector<CLLocalStyle>;
%template(GradientBaseVector) CCopasiVector<CLGradientBase>;
%template(CCopasiObjectVector) CCopasiVector<CCopasiObject>;
%template(GradientStopVector) CCopasiVector<CLGradientStop>;
%template(LineEndingVector) CCopasiVector<CLLineEnding>;
typedef CCopasiVector<CLColorDefinition> ColorDefinitionVector;
typedef CCopasiVector<CLGlobalRenderInformation> GlobalRenderInformationVector;
typedef CCopasiVector<CLGlobalStyle> GlobalStyleVector;
typedef CCopasiVector<CLLocalStyle> LocalStyleVector;
typedef CCopasiVector<CLGradientBase> GradientBaseVector;
typedef CCopasiVector<CCopasiObject> CCopasiObjectVector;
typedef CCopasiVector<CLGradientStop> GradientStopVector;
typedef CCopasiVector<CLLineEnding> LineEndingVector;

%template(RenderPointStdVector) std::vector<CLRenderPoint*>;
typedef std::vector<CLRenderPoint*> RenderPointStdVector;

