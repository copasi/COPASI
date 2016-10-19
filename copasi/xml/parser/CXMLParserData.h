// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CXMLParserData
#define COPASI_CXMLParserData

#include <string>
#include <vector>
#include <map>
#include <stack>

#include "copasi/report/CCopasiObjectName.h"

class CCompartment;
class CMetab;
class CModel;
class CModelEntity;
class CModelValue;
class CEvent;
class CEventAssignment;
class CReaction;
class CEvaluationTree;
class CFunction;
class CExpression;
class CFunctionParameter;
class CXMLParser;
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
class CReportDefinition;
class CCopasiTask;
class CListOfLayouts;
class CLayout;
class CLCompartmentGlyph;
class CLMetabGlyph;
class CLReactionGlyph;
class CLGeneralGlyph;
class CLTextGlyph;
class CLGraphicalObject;
class CLCurve;
class CLLineSegment;
class CLMetabReferenceGlyph;
class CCopasiDataModel;
class CModelParameterSet;
class CModelParameterGroup;
class CModelParameter;
class CLRenderInformationBase;
class CLGradientBase;
class CLLineEnding;
class CLStyle;
class CLGroup;
class CLText;
class CLRenderPoint;
class CUnitDefinitionDB;
class CUnitDefinition;
class CKeyFactory;

template <class CType> class CCopasiVectorN;

class CXMLParserData
{
public:
  // Operations
  /**
   * Default Constructor
   */
  CXMLParserData();

  // Attributes
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
  std::string CharacterData;

  /**
   * Storage for assignments.
   */
  std::vector<std::pair<std::string, std::string> > mAssignments;

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
   * Pointer to the currently processed function.
   */
  CFunctionParameter * pFunctionVariable;

  /**
   * The description of the function.
   */
  std::string FunctionDescription;

  /**
   * Indicates whether the current function was already in the list;
   */
  bool mPredefinedFunction;

  /**
   * A map of new function to old keys  parameter definitions
   */
  std::map< size_t, std::string > mFunctionParameterKeyMap;

  /**
   * Pointer to the currently processed expression. This is only needed for old files
   * containing the objective function as part of the list of function definitions
   */
  CExpression * mpExpression;

  /**
   * A map of a key to the infix of the objective function. This is only needed for old files
   * containing the objective function as part of the list of function definitions
   */
  std::map< std::string, CExpression * > mKey2ObjectiveFunction;

  /**
   * Pointer to the currently processed reaction.
   */
  CReaction * pReaction;

  /**
   * Pointer to the currently processed event
   */
  CEvent * pEvent;

  /**
   * Pointer to the currently processed event assignment
   */
  CEventAssignment * pEventAssignment;

  /**
   * The keys of the source parameters for a call parameter.
   */
  std::map< std::string, std::vector< std::string > > SourceParameterKeys;

  /**
   * A map relating CopasiXML function keys with internal keys
   */
  //    std::map< std::string, std::string > KeyMap;
  CKeyFactory *mpKeyMap;

  /**
   * A map relating StateVariables to model entities.
   */
  std::vector< CModelEntity * > StateVariableList;

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

  /**
   * Stack of Model Parameter Groups which is needed since nesting
   * of groups is possible.
   */
  std::stack< CModelParameterGroup * > ModelParameterGroupStack;

  /**
   * The currently handeled Model Parameter
   */
  CModelParameter * pCurrentModelParameter;

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
   * Vector of parameters of type key which could not be updated due to missing target objects
   * at time of read.
   */
  std::vector< std::string > UnmappedKeyParameters;

  /**
   * Pointer to a list of Layouts which has been loaded or is to be saved.
   * The ownership is handed to the user.
   */
  CListOfLayouts * pLayoutList;

  /**
   * Pointer to the currently processed layout
   */
  CLayout * pCurrentLayout;

  CLCompartmentGlyph * pCompartmentGlyph;
  CLMetabGlyph * pMetaboliteGlyph;
  CLReactionGlyph * pReactionGlyph;
  CLTextGlyph * pTextGlyph;
  //CLGraphicalObject * pAdditionalGO;
  CLGeneralGlyph * pGeneralGlyph;
  CLCurve *pCurve;
  CLLineSegment *pLineSegment;
  CLMetabReferenceGlyph* pMetaboliteReferenceGlyph;
  CLRenderInformationBase* pRenderInformation;
  CLGradientBase* pGradient;
  CLLineEnding* pLineEnding;
  CLStyle* pStyle;
  CLGroup* pGroup;
  CLText* pText;
  std::vector<CLRenderPoint*>* pListOfCurveElements;

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
   * A map that stores a vector of pairs of header,body or footer addresses
   *  with the index together with the key to the reference.
   */
  std::map<std::string , std::vector < std::pair < std::vector < CRegisteredObjectName > *, size_t > > > reportReferenceMap;

  SCopasiXMLGUI * pGUI;

  /**
   * A pointer to the datamodel.
   */
  CCopasiDataModel* pDataModel;

  CUnitDefinitionDB * pUnitDefinitionImportList;

  CUnitDefinition * pCurrentUnitDefinition;
};

#endif // COPASI_CXMLParserData
