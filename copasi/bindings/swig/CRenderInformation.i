// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
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

%ignore operator/;
%ignore operator!=;
%ignore CLLocalStyle::isInKeyList;
%ignore CLLocalStyle::mKeyList;
%ignore CLLocalStyle::getKeyList;
%ignore CLLocalStyle::setKeyList;
%ignore CLRectangle::CLRectangle(const sbmlRectangle& source, CDataContainer* pParent = NULL);
%ignore CLRectangle::toSBML;
%ignore CLEllipse::CLEllipse(const sbmlEllipse& source, CDataContainer* pParent = NULL);
%ignore CLEllipse::getCX() const;
%ignore CLEllipse::getCY() const;
%ignore CLEllipse::getCZ() const;
%ignore CLEllipse::getRX() const;
%ignore CLEllipse::getRY() const;
%ignore CLEllipse::toSBML;
%ignore CLPolygon::CLPolygon(const sbmlPolygon& source, CDataContainer* pParent = NULL);
%ignore CLPolygon::toSBML;
%ignore CLPolygon::getListOfElements() const;
%ignore CLPolygon::getElement(size_t) const;
%ignore CLLocalRenderInformation::toSBML;
%ignore CLLocalRenderInformation::  CLLocalRenderInformation(const LocalRenderInformation& source,
                           CDataContainer* pParent = NULL);
%ignore CLGlobalRenderInformation::CLGlobalRenderInformation(const GlobalRenderInformation& source,
                            CDataContainer* pParent = NULL);
%ignore CLGlobalRenderInformation::toSBML;
%ignore CLGlyphWithCurve::CLGlyphWithCurve(const GraphicalObject & sbml, //TODO preliminary
                   const std::map<std::string, std::string> & modelmap,
                   std::map<std::string, std::string> & layoutmap,
                   const CDataContainer * pParent = NULL);
%ignore CLGeneralGlyph::CLGeneralGlyph(const GraphicalObject & sbml,
                 const std::map<std::string, std::string> & modelmap,
                 std::map<std::string, std::string> & layoutmap,
                 const CDataContainer * pParent = NULL);
%ignore CLColorDefinition::toSBML;
%ignore CLColorDefinition::CLColorDefinition(const ColorDefinition& source, CDataContainer* pParent = NULL);
%ignore CLGlobalStyle::CLGlobalStyle(const GlobalStyle& source, CDataContainer* pParent = NULL);
%ignore CLGlobalStyle::toSBML;
%ignore CLGradientBase::CLGradientBase(const GradientBase& source, const std::string& name, CDataContainer* pParent = NULL);
%ignore CLGradientBase::addSBMLAttributes;
%ignore CLGradientBase::getListOfGradientStops() const;
%ignore CLGradientBase::getGradientStop(size_t) const;
%ignore CLGradientStop::toSBML;
%ignore CLGradientStop::CLGradientStop(const GradientStop& source, CDataContainer* pParent = NULL);
%ignore CLGraphicalPrimitive1D::CLGraphicalPrimitive1D(const GraphicalPrimitive1D& source);
%ignore CLGraphicalPrimitive1D::addSBMLAttributes;
%ignore CLGraphicalPrimitive2D::CLGraphicalPrimitive2D(const GraphicalPrimitive2D& source);
%ignore CLGraphicalPrimitive2D::addSBMLAttributes;
%ignore CLGroup::getFontSize() const;
%ignore CLGroup::toSBML;
%ignore CLGroup::getListOfElements() const;
%ignore CLGroup::getElement(size_t) const;
%ignore CLGroup::CLGroup(const RenderGroup& source, CDataContainer* pParent = NULL);
%ignore CLImage::getX() const;
%ignore CLImage::getY() const;
%ignore CLImage::getZ() const;
%ignore CLImage::toSBML;
%ignore CLImage::CLImage(const Image& source, CDataContainer* pParent = NULL);
%ignore CLLineEnding::toSBML;
%ignore CLLineEnding::getBoundingBox() const;
%ignore CLLineEnding::getGroup() const;
%ignore CLLineEnding::CLLineEnding(const LineEnding& source, CDataContainer* pParent = NULL);
%ignore CLLinearGradient::toSBML;
%ignore CLLinearGradient::getXPoint1() const;
%ignore CLLinearGradient::getYPoint1() const;
%ignore CLLinearGradient::getZPoint1() const;
%ignore CLLinearGradient::getXPoint2() const;
%ignore CLLinearGradient::getYPoint2() const;
%ignore CLLinearGradient::getZPoint2() const;
%ignore CLRadialGradient::getCenterX() const;
%ignore CLRadialGradient::getCenterY() const;
%ignore CLRadialGradient::getCenterZ() const;
%ignore CLRadialGradient::getFocalPointX() const;
%ignore CLRadialGradient::getFocalPointY() const;
%ignore CLRadialGradient::getFocalPointZ() const;
%ignore CLRadialGradient::getRadius() const;
%ignore CLLinearGradient::CLLinearGradient(const LinearGradient& source, CDataContainer* pParent = NULL);
%ignore CLLocalStyle::toSBML;
%ignore CLLocalStyle::CLLocalStyle(const LocalStyle& source, CDataContainer* pParent = NULL);
%ignore CLRadialGradient::toSBML;
%ignore CLRadialGradient::CLRadialGradient(const RadialGradient& source, CDataContainer* pParent = NULL);
%ignore CLRectangle::getX() const;
%ignore CLRectangle::getWidth() const;
%ignore CLRectangle::getHeight() const;
%ignore CLRectangle::getRadiusX() const;
%ignore CLRectangle::getRadiusY() const;
%ignore CLRectangle::getY() const;
%ignore CLRectangle::getZ() const;
%ignore CLRelAbsVector::toSBML;
%ignore CLRelAbsVector::CLRelAbsVector(const RelAbsVector& source);
%ignore CLRenderInformationBase::CLRenderInformationBase(const RenderInformationBase& source,
                          const std::string& name,
                          CDataContainer* pParent = NULL);
%ignore CLRenderInformationBase::addSBMLAttributes;
%ignore CLRenderInformationBase::getListOfColorDefinitions() const;
%ignore CLRenderInformationBase::getColorDefinition(size_t) const;
%ignore CLRenderInformationBase::getListOfGradientDefinitions() const;
%ignore CLRenderInformationBase::getGradientDefinition(size_t) const;
%ignore CLRenderInformationBase::getListOfLineEndings() const;
%ignore CLRenderInformationBase::getLineEnding(size_t) const;
%ignore CLLocalRenderInformation::getListOfStyles() const;
%ignore CLLocalRenderInformation::getStyle(size_t) const;
%ignore CLGlobalRenderInformation::getListOfStyles() const;
%ignore CLGlobalRenderInformation::getStyle(size_t) const;
%ignore CLRenderCubicBezier::basePoint1_X() const;
%ignore CLRenderCubicBezier::basePoint1_Y() const;
%ignore CLRenderCubicBezier::basePoint1_Z() const;
%ignore CLRenderCubicBezier::basePoint2_X() const;
%ignore CLRenderCubicBezier::basePoint2_Y() const;
%ignore CLRenderCubicBezier::basePoint2_Z() const;
%ignore CLRenderCubicBezier::toSBML;
%ignore CLRenderCubicBezier::CLRenderCubicBezier(const RenderCubicBezier& source);
%ignore CLRenderCurve::toSBML;
%ignore CLRenderCurve::getCurveElement(size_t) const;
%ignore CLRenderCurve::getListOfCurveElements() const;
%ignore CLRenderCurve::CLRenderCurve(const RenderCurve& source, CDataContainer* pParent = NULL);
%ignore CLRenderPoint::addSBMLAttributes;
%ignore CLRenderPoint::toSBML;
%ignore CLRenderPoint::x() const;
%ignore CLRenderPoint::y() const;
%ignore CLRenderPoint::z() const;
%ignore CLRenderPoint::getXOffset() const;
%ignore CLRenderPoint::getYOffset() const;
%ignore CLRenderPoint::getZOffset() const;
%ignore CLRenderPoint::CLRenderPoint(const RenderPoint& source);
%ignore CLStyle::CLStyle(const Style& source, const std::string& name, CDataContainer* pParent = NULL);
%ignore CLStyle::addSBMLAttributes;
%ignore CLStyle::setRoleList;
%ignore CLStyle::setTypeList;
%ignore CLStyle::getRoleList;
%ignore CLStyle::getTypeList;
%ignore CLStyle::readIntoSet;
%ignore CLStyle::createStringFromSet;
%ignore CLStyle::getGroup() const;
%ignore CLText::toSBML;
%ignore CLText::getX() const;
%ignore CLText::getY() const;
%ignore CLText::getZ() const;
%ignore CLText::getFontSize() const;
%ignore CLText::CLText(const Text& source, CDataContainer* pParent = NULL);
%ignore CLTransformation::IDENTITY3D;
%ignore CLTransformation::getIdentityMatrix;
%ignore CLTransformation::CLTransformation(const double matrix[12]);
%ignore CLTransformation::getMatrix;
%ignore CLTransformation::setMatrix;
%ignore CLTransformation2D::IDENTITY2D;
%ignore CLTransformation2D::getIdentityMatrix2D;
%ignore CLTransformation2D::CLTransformation2D(const Transformation2D& source);
%ignore CLTransformation2D::CLTransformation2D(const double m[6]);
%ignore CLTransformation2D::setMatrix2D;
%ignore CLTransformation2D::setMatrix;
%ignore CLTransformation2D::getMatrix2D;

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





%template(ColorDefinitionVector) CDataVector<CLColorDefinition>;
%template(GlobalRenderInformationVector) CDataVector<CLGlobalRenderInformation>;
%template(GlobalStyleVector) CDataVector<CLGlobalStyle>;
%template(LocalStyleVector) CDataVector<CLLocalStyle>;
%template(GradientBaseVector) CDataVector<CLGradientBase>;
%template(CDataObjectVector) CDataVector<CDataObject>;
%template(GradientStopVector) CDataVector<CLGradientStop>;
%template(LineEndingVector) CDataVector<CLLineEnding>;
typedef CDataVector<CLColorDefinition> ColorDefinitionVector;
typedef CDataVector<CLGlobalRenderInformation> GlobalRenderInformationVector;
typedef CDataVector<CLGlobalStyle> GlobalStyleVector;
typedef CDataVector<CLLocalStyle> LocalStyleVector;
typedef CDataVector<CLGradientBase> GradientBaseVector;
typedef CDataVector<CDataObject> CDataObjectVector;
typedef CDataVector<CLGradientStop> GradientStopVector;
typedef CDataVector<CLLineEnding> LineEndingVector;

%template(RenderPointStdVector) std::vector<CLRenderPoint*>;
typedef std::vector<CLRenderPoint*> RenderPointStdVector;

