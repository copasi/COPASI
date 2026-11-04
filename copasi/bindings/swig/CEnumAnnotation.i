// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// 1. Inject headers safely into the C++ compiler's scope
%{
#include "copasi/core/CEnumAnnotation.h"
#include "copasi/utilities/CTaskEnum.h"
#include "copasi/utilities/CExpressionGenerator.h"
#include <vector>
#include <string>
%}

// Tell SWIG to load the standard library types for all target languages
%include "std_string.i"
%include "std_vector.i"

// Instantiate standard collection proxies so they are recognized by Java, C#, and Python
%template(StringVector) std::vector< std::string >;
%template(IntVector) std::vector< int >;

// SWIG cannot wrap operator[]. Lookups go through getIntValue and getStrValue.
%ignore CEnumAnnotation::operator[];
%ignore CEnumAnnotationInstance::operator[];
%ignore CEnumAnnotationSubset::operator[];

// Ignore the original values() method returning std::string_view vectors 
// to prevent code generation errors on unsupported types.
%ignore CEnumAnnotation::values;

// 4. Process the main header
%include "copasi/core/CEnumAnnotation.h"

// extend the class to add some convenience methods
%extend CEnumAnnotation
{
  int getIntValue(const std::string & annotation) const
  {
    return static_cast< int >($self->toEnum(std::string_view(annotation)));
  }

  std::string getStrValue(int value) const
  {
    return (*$self)[static_cast< std::int32_t >(value)];
  }

  std::vector< int > intValues() const
  {
    std::vector< int > result;
    result.reserve($self->size());

    for (auto key : $self->keys())
      result.push_back(static_cast< int >(key));

    return result;
  }

  // CROSS-PLATFORM FIX: Do the string_view to string conversion directly inside C++
  // SWIG will now automatically use the correct target language wrapper (StringVector)
  std::vector< std::string > values() const
  {
    auto views = $self->values();
    return std::vector< std::string >(views.begin(), views.end());
  }
}

// Included from the end of copasi.i, after the enum types have been parsed.
// include the task and expression generator enums
%include "copasi/utilities/CTaskEnum.h"
%include "copasi/utilities/CExpressionGenerator.h"

%define CENUM_ANNOTATION_STRING(Name, EnumType)
%template(Name) CEnumAnnotation< EnumType, std::string_view >;
%enddef

CENUM_ANNOTATION_STRING(CEnumAnnotation_Task, CTaskEnum::Task)
CENUM_ANNOTATION_STRING(CEnumAnnotation_Method, CTaskEnum::Method)
CENUM_ANNOTATION_STRING(CEnumAnnotation_Framework, CCore::Framework)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CDataValue_Type, CDataValue::Type)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CUndoData_Type, CUndoData::Type)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CData_Property, CData::Property)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CIssue_eKind, CIssue::eKind)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CIssue_eSeverity, CIssue::eSeverity)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CConfigurableRNG_Type, CConfigurableRNG::Type)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CFunctionParameter_Role, CFunctionParameter::Role)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CFunctionParameter_DataType, CFunctionParameter::DataType)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CModelEntity_Status, CModelEntity::Status)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CReaction_KineticLawUnit, CReaction::KineticLawUnit)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CModel_ModelType, CModel::ModelType)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CCopasiParameter_Type, CCopasiParameter::Type)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CModelParameter_Type, CModelParameter::Type)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CModelParameter_CompareResult, CModelParameter::CompareResult)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CPlotItem_LineType, CPlotItem::LineType)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CPlotItem_LineStyle, CPlotItem::LineStyle)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CPlotItem_SymbolType, CPlotItem::SymbolType)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CDataModel_ContentType, CDataModel::ContentType)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CNewtonMethod_eTargetCriterion, CNewtonMethod::eTargetCriterion)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CScanProblem_OutputType, CScanProblem::OutputType)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CMath_ValueType, CMath::ValueType)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CMath_SimulationType, CMath::SimulationType)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CMath_EntityType, CMath::EntityType)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CEvaluationNode_MainType, CEvaluationNode::MainType)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CEvaluationNode_SubType, CEvaluationNode::SubType)
CENUM_ANNOTATION_STRING(CEnumAnnotation_COpenMPConfig_ScheduleStrategy, COpenMPConfig::ScheduleStrategy)
CENUM_ANNOTATION_STRING(CEnumAnnotation_COpenMPConfig_Monotonic, COpenMPConfig::Monotonic)
CENUM_ANNOTATION_STRING(CEnumAnnotation_CExpressionGenerator_Operation, CExpressionGenerator::Operation)

#ifdef SWIGPYTHON
// Class attributes are copied while the module is still loading, before these
// proxy classes exist. Read them again so they are the annotation objects.
%pythoncode %{
CCore.FrameworkNames = cvar.CCore_FrameworkNames
CTaskEnum.TaskName = cvar.CTaskEnum_TaskName
CTaskEnum.TaskXML = cvar.CTaskEnum_TaskXML
CTaskEnum.MethodName = cvar.CTaskEnum_MethodName
CTaskEnum.MethodXML = cvar.CTaskEnum_MethodXML
CDataValue.TypeName = cvar.CDataValue_TypeName
CData.PropertyName = cvar.CData_PropertyName
CUndoData.TypeName = cvar.CUndoData_TypeName
CIssue.kindNames = cvar.CIssue_kindNames
CIssue.kindDescriptions = cvar.CIssue_kindDescriptions
CIssue.severityNames = cvar.CIssue_severityNames
CConfigurableRNG.TypeAnnotation = cvar.CConfigurableRNG_TypeAnnotation
CFunctionParameter.RoleNameXML = cvar.CFunctionParameter_RoleNameXML
CFunctionParameter.RoleNameDisplay = cvar.CFunctionParameter_RoleNameDisplay
CFunctionParameter.DataTypeName = cvar.CFunctionParameter_DataTypeName
CModelParameter.TypeNames = cvar.CModelParameter_TypeNames
CModelParameter.CompareResultNames = cvar.CModelParameter_CompareResultNames
CPlotItem.LineTypeNames = cvar.CPlotItem_LineTypeNames
CPlotItem.LineStyleNames = cvar.CPlotItem_LineStyleNames
CPlotItem.SymbolNames = cvar.CPlotItem_SymbolNames
CDataModel.ContentTypeNames = cvar.CDataModel_ContentTypeNames
CNewtonMethod.TargetCriterion = cvar.CNewtonMethod_TargetCriterion
CScanProblem.OutputTypeName = cvar.CScanProblem_OutputTypeName
COptProblem.ValidSubtasks = cvar.COptProblem_ValidSubtasks
CSensProblem.ValidSubtask = cvar.CSensProblem_ValidSubtask
CExpressionGenerator.OperationNames = cvar.CExpressionGenerator_OperationNames
%}
#endif
