// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CCopasiXML class.
 * This class implements a CCopasiXMLInterface to the COPASI XML specified in
 * http://www.copasi.org/schema/copasi.xsd
 *
 * Created for COPASI by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#ifndef COPASI_CCopasiXML
#define COPASI_CCopasiXML

#include "copasi/xml/CCopasiXMLInterface.h"
#include "copasi/utilities/CVersion.h"

class CAnnotation;
class CModel;
class CModelParameter;
class CEvaluationTree;
class CFunction;
class CCopasiTask;
class CReportDefinitionVector;
class COutputDefinitionVector;
class CListOfLayouts;
class CLPoint;
class CLDimensions;
class CLBoundingBox;
class CLCurve;
class CUnitDefinitionDB;

class CCopasiParameter;
class CCopasiParameterGroup;
class CRegisteredCommonName;
class CDataModel;

class CLLocalRenderInformation;
class CLGlobalRenderInformation;
class CLRenderInformationBase;
class CLLocalStyle;
class CLGlobalStyle;
class CLColorDefinition;
class CLGradientBase;
class CLLinearGradient;
class CLRadialGradient;
class CLLineEnding;
class CLRenderPoint;
class CLRenderCubicBezier;
class CLGroup;
class CLTransformation2D;
class CLImage;
class CLGraphicalPrimitive1D;
class CLText;
class CLRenderCurve;
class CLGraphicalPrimitive2D;
class CLRectangle;
class CLEllipse;
class CLPolygon;
class CLGradientStop;
class CLLineEnding;
class CLStyle;

class CCopasiXML : public CCopasiXMLInterface
{
  // Operations
public:
  /**
   * Constructor
   */
  CCopasiXML();

  /**
   * Destructor
   */
  ~CCopasiXML();

  /**
   * Save information to a given ostream.
   * @param std::ostream & os
   * @param const std::string & relativeTo
   * @return bool success
   */
  virtual bool save(std::ostream & os,
                    const std::string & relativeTo);

  /**
   * Save information to a given ostream.
   * @param std::ostream & os
   * @param const std::string & relativeTo
   * @return bool success
   */
  virtual bool saveModelParameterSets(std::ostream & os,
                                      const std::string & relativeTo);

  /**
   * Load information from a given istream.
   * @param std::istream & is
   * @param const std::string & pwd
   * @return bool success
   */
  virtual bool load(std::istream & is,
                    const std::string & pwd);

  /**
   * Set the model.
   * @param CModel * pModel
   * @return bool success
   */
  bool setModel(CModel * pModel);

  /**
   * Retreive the model.
   * @return CModel * pModel
   */
  CModel * getModel() const;

  /**
   * Retreive whether the XML contains a model.
   * @return bool have Model
   */
  bool haveModel() const;

  /**
   * Free the model.
   * @return bool success
   */
  bool freeModel();

  /**
   * Set the function list.
   * @param CopasiVectorN< CFunction > * pFunctionList
   * @return bool success
   */
  bool setFunctionList(CDataVectorN< CFunction > *pFunctionList);

  /**
   * Retrieve the function list.
   * @return CDataVectorN< CFunction > * pFunctionList
   */
  CDataVectorN< CFunction > * getFunctionList() const;

  /**
   * Retrieve whether the XML contains a function list.
   * @return bool haveFunctionList
   */
  bool haveFunctionList() const;

  /**
   * Free the function list.
   * @return bool success
   */
  bool freeFunctionList();

  /**
   * Set the task list.
   * @param CDataVectorN< CCopasiTask > *pTaskList
   * @return bool success
   */
  bool setTaskList(CDataVectorN< CCopasiTask > *pTaskList);

  /**
   * Set the datamodel.
   * @param CDataModel* pDataModel
   * @return bool success
   */
  bool setDatamodel(CDataModel* pDataModel);

  /**
   * Retrieve the task list.
   * @return CDataVectorN< CCopasiTask > * taskList
   */
  CDataVectorN< CCopasiTask > * getTaskList() const;

  /**
   * Retrieve whether the XML contains a task list.
   * @return bool haveTaskList
   */
  bool haveTaskList() const;

  /**
   * Free the task list.
   * @return bool success
   */
  bool freeTaskList();

  /**
   * Set the plot list.
   * @param COutputDefinitionVector * pPlotList
   * @return bool success
   */
  bool setPlotList(COutputDefinitionVector * pPlotList);

  /**
   * Retrieve the plot list.
   * @return COutputDefinitionVector * plotList
   */
  COutputDefinitionVector * getPlotList() const;

  /**
   * Retrieve whether the XML contains a plot list.
   * @return bool havePlotList
   */
  bool havePlotList() const;

  /**
   * Free the plot list.
   * @return bool success
   */
  bool freePlotList();

  /**
   * Set the report list.
   * @param CReportDefinitionVector *pReportList
   * @return bool success
   */
  bool setReportList(CReportDefinitionVector * pReportList);

  /**
   * Retrieve the report list.
   * @return CReportDefinitionVector * reportList
   */
  CReportDefinitionVector * getReportList() const;

  /**
   * Retrieve whether the XML contains a report list.
   * @return bool haveReportList
   */
  bool haveReportList() const;

  /**
   * Free the report list.
   * @return bool success
   */
  bool freeReportList();

  /**
   * Set the GUI.
   * @param SCopasiXMLGUI *pGUI
   * @return bool success
   */
  bool setGUI(SCopasiXMLGUI *pGUI);

  /**
   * Retrieve the SCopasiXMLGUI.
   * @return SCopasiXMLGUI * pGUI
   */
  SCopasiXMLGUI * getGUI() const;

  /**
   * Retrieve whether the XML contains a GUI.
   * @return bool have GUI
   */
  bool haveGUI() const;

  /**
   * Free the GUI.
   * @return bool success
   */
  bool freeGUI();

  /**
   * Set the layout list.
   * @param const CListOfLayouts & reportList
   * @return bool success
   */
  bool setLayoutList(const CListOfLayouts & reportList);

  /**
   * Retrieve the layout list.
   * @return CListOfLayouts * layoutList
   */
  CListOfLayouts * getLayoutList() const;

  /**
   * Retrieve whether the XML contains a layout list.
   * @return bool haveLayoutList
   */
  bool haveLayoutList() const;

  /**
   * Free the layout list.
   * @return bool success
   */
  bool freeLayoutList();

  /**
   * Save the Unit Definition list.
   * @return bool success
   */
  bool saveUnitDefinitionList();

private:
  /**
   * Save the model.
   * @return bool success
   */
  bool saveModel();

  /**
   * Save the model parameter sets to stream
   */
  void saveModelParameterSets();

  /**
   * Save a model parameter
   * @param const CModelParameter * pModelParameter
   * @return bool success
   */
  bool saveModelParameter(const CModelParameter * pModelParameter);

  bool saveAnnotation(const CAnnotation * pAnnotation);

  /**
   * Save the list of functions.
   * @return bool success
   */
  bool saveFunctionList();

  /**
   * Save the list of tasks.
   * @return bool success
   */
  bool saveTaskList();

  /**
   * Save the list of plots.
   * @return bool success
   */
  bool savePlotList();

  /**
   * Save the list of reports.
   * @return bool success
   */
  bool saveReportList();

  /**
   * Save GUI information
   * @return bool success
   */
  bool saveGUI();

  /**
   * Save the list of layout.
   * @return bool success
   */
  bool saveLayoutList();

  void savePosition(const CLPoint& p, const std::string & tag = "Position");

  void saveDimensions(const CLDimensions& d);

  void saveBoundingBox(const CLBoundingBox& bb);

  void saveCurve(const CLCurve& c);

  /**
   * Save the SBML reference information
   * @return bool success
   */
  bool saveSBMLReference();

  /**
   * Save a Report Section such as Header, Body or Footer.
   * @param const std::string & name
   * @param const std::vector <CCommonName> & section
   * @return bool success
   */
  bool saveReportSection(const std::string & name,
                         const std::vector <CRegisteredCommonName> & section);

  /**
   * Build a list of functions.
   * @return bool success
   */
  bool buildFunctionList();

  /**
   * Fix files written with Version 4.0.18, which used units Mol, etc., instead of mol, . . .
   */
  void fixBuild18();

  /**
   * Fix files written with Version 4.10.55, which wrote the square root of user defined weights for the
   * parameter fitting task
   */
  void fixBuild55();

  /**
   * Fix files written with Version 4.12.81 and earlier, which wrote the exp(mean) and exp(std. deviation) for
   * normal random distributions in the scan task.
   */
  void fixBuild81();

  /**
   * After Build 104, at least, we shouldn't see any "m" in place of "min" for timeUnit.
   */
  void fixBuildBefore104();

  /**
   * The default kinetic law unit type needs to be corrected in rare cases.
   */
  void fixBuild113();

  /**
   * The object names no longer may have special character and are sanitized. This invalidates common names (CNs).
   */
  void fixBuild171();

  /**
   * Saves the list of global render information objects.
   */
  void saveListOfGlobalRenderInformation(const CDataVector<CLGlobalRenderInformation>& list);

  /**
   * Saves the list of local render information objects.
   */
  void saveListOfLocalRenderInformation(const CDataVector<CLLocalRenderInformation>& list);

  /**
   * Saves a single global render information object.
   */
  void saveGlobalRenderInformation(const CLGlobalRenderInformation& renderInfo);

  /**
   * Saves a single local render information object.
   */
  void saveLocalRenderInformation(const CLLocalRenderInformation& renderInfo);

  /**
   * Saves the attributes that render information objects have in common.
   */
  void saveRenderInformationAttributes(const CLRenderInformationBase& renderInfo, CXMLAttributeList& attributes);

  /**
   * Saves color definitions, gradient definitions  and line endings.
   */
  void saveRenderInformationDefinitionElements(const CLRenderInformationBase& renderInfo);

  /**
   * Save a single color definition element.
   */
  void saveColorDefinition(const CLColorDefinition& color);

  /**
   * Saves a single linear gradient definition.
   */
  void saveLinearGradient(const CLLinearGradient& gradient);

  /**
   * Saves a single radial gradient definition.
   */
  void saveRadialGradient(const CLRadialGradient& gradient);

  /**
   * Adds the attributes common to radial and linear gradient.
   */
  void saveGradientAttributes(const CLGradientBase& gradient, CXMLAttributeList& attributes);

  /**
   * Saves the elements that are common to linear and radial gradients.
   */
  void saveGradientElements(const CLGradientBase& gradient);

  /**
   * Saves a single gradient stop element.
   */
  void saveGradientStop(const CLGradientStop& stop);

  /**
   * Saves a line ending definiton,
   */
  void saveLineEnding(const CLLineEnding& lineEnding);

  /**
   * Saves a single local style element.
   */
  void saveLocalStyle(const CLLocalStyle& style);

  /**
   * Saves a single local style element.
   */
  void saveGlobalStyle(const CLGlobalStyle& style);

  /**
   * Adds the attributes common to both style types.
   */
  void saveStyleAttributes(const CLStyle& style, CXMLAttributeList& attributes);

  /**
   * Saves the elements common to both style types.
   */
  void saveStyleElements(const CLStyle& style);

  /**
   * Saves a group element.
   */
  void saveGroupElement(const CLGroup& group);

  /**
   * Saves the attributes for a transformation.
   */
  void saveTransformationAttributes(const CLTransformation2D& transformation, CXMLAttributeList& attributes);

  /**
   * Saves the attributes for a 1D element
   */
  void save1DAttributes(const CLGraphicalPrimitive1D& primitive, CXMLAttributeList& attributes);

  /**
   * Saves the attributes for a 2D element
   */
  void save2DAttributes(const CLGraphicalPrimitive2D& primitive, CXMLAttributeList& attributes);

  /**
   * Saves the attributes for a text element.
   * We make this a template so that we can use it for a group as well as a text element.
   */
  template<typename TEXTELEMENT>
  void saveTextAttributes(const TEXTELEMENT& text, CXMLAttributeList& attributes);

  /**
   * Saves the startHead and endHead attribute as found in group and curves.
   * We write it as a template so that it can be used on curves and group elements.
   */
  template<typename HEADELEMENT>
  void saveArrowHeadAttributes(const HEADELEMENT& element, CXMLAttributeList& attributes);

  /**
   * Saves a class that is subclasses from Transformation2D.
   * This covers images, curves, rectangles, ellipses, polygons, text elements and groups.
   */
  void saveTransformation2D(const CLTransformation2D& transformation);

  /**
   * saves a single image element.
   */
  void saveImageElement(const CLImage& image);

  /**
   * saves a single rectangle element.
   */
  void saveRectangleElement(const CLRectangle& rectangle);

  /**
   * saves a single ellipse element.
   */
  void saveEllipseElement(const CLEllipse& ellipse);

  /**
   * saves a single text element.
   */
  void saveRenderTextElement(const CLText& text);

  /**
   * saves a single image element.
   */
  void savePolygonElement(const CLPolygon& polygon);

  /**
   * saves a single image element.
   */
  void saveRenderCurveElement(const CLRenderCurve& curve);

  /**
   * saves a vector of curve elements. This can be called from the polygon as well as the curve.
   */
  void saveCurveElements(const std::vector<CLRenderPoint*>& curveElements);

  /**
   * saves a single render point element.
   */
  void saveRenderPoint(const CLRenderPoint& point);

  /**
   * Load in Unit Definitions we don't already have.
   * Create new names and symbols for conflicts.
   * Update model to use any created symbols.
   */
  void mergeUnitDefinitions(CUnitDefinitionDB * pUnitDefImportList);

  // Attributes

  /**
   * Pointer to a model which has been loaded or is to be saved.
   * The ownership is handed to the user.
   */
  CModel * mpModel;

  /**
   * Pointer to a vector of functions which has been loaded or is to be saved.
   * The ownership is handed to the user.
   */
  CDataVectorN< CFunction > * mpFunctionList;

  /**
   * Pointer to a vector of tasks which has been loaded or is to be saved.
   * The ownership is handed to the user.
   */
  CDataVectorN< CCopasiTask > * mpTaskList;

  /**
   * Pointer to a vector of reports which has been loaded or is to be saved.
   * The ownership is handed to the user.
   */
  CReportDefinitionVector * mpReportList;

  /**
   * Pointer to a vector of plots which has been loaded or is to be saved.
   * The ownership is handed to the user.
   */
  COutputDefinitionVector * mpPlotList;

  /**
   * Pointer to a GUI related information, which has been loaded or is to be saved.
   * The ownership is handed to the user.
   */
  SCopasiXMLGUI * mpGUI;

  /**
   * Pointer to a vector of plots which has been loaded or is to be saved.
   * The ownership is handed to the user.
   */
  CListOfLayouts * mpLayoutList;

  /**
   * SBML Reference
   */
  std::map< std::string, std::string > mSBMLReference;

  /**
   * Pointer to the datamodel
   */
  CDataModel* mpDataModel;

  /**
   * Remember if we already issued MCXML21
   */
  bool mMCXML21Issued;
};

#endif // COPASI_CCopasiXML
