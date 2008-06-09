// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/CCopasiXML.h,v $
//   $Revision: 1.20 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/06/09 07:43:07 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*!
 \file CCopasiXML.h
 \brief Header file of class CCopasiXML.
 */

/**
 * CCopasiXML class.
 * This class implements a CCopasiXMLInterface to the COPASI XML specified in
 * http://www.copasi.org/schema/copasi.xsd
 *
 * Created for Copasi by Stefan Hoops 2003
 * Copyright Stefan Hoops
 */

#ifndef COPASI_CCopasiXML
#define COPASI_CCopasiXML

#include "xml/CCopasiXMLInterface.h"
#include "utilities/CVersion.h"

class CModel;
class CEvaluationTree;
class CCopasiTask;
class CReportDefinitionVector;
class COutputDefinitionVector;
#ifdef WITH_LAYOUT
class CListOfLayouts;
class CLPoint;
class CLDimensions;
class CLBoundingBox;
class CLCurve;
#endif

class CCopasiParameter;
class CCopasiParameterGroup;
class CRegisteredObjectName;

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
     * Load information from a given istream.
     * @param std::istream & is
     * @param const std::string & relativeTo
     * @return bool success
     */
    virtual bool load(std::istream & is,
                      const std::string & relativeTo);

    /**
     * Retrieve the version of the current XML file.
     * Before any load operation this contains the COPASI schema version supported by
     * the writer. After load it contains the schema version of the loaded file.
     * @return const CVersion & version
     */
    const CVersion & getVersion() const;

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
     * @param CopasiVectorN< CEvaluationTree > * pFunctionList
     * @return bool success
     */
    bool setFunctionList(CCopasiVectorN< CEvaluationTree > *pFunctionList);

    /**
     * Retreive the function list.
     * @return CCopasiVectorN< CEvaluationTree > * pFunctionList
     */
    CCopasiVectorN< CEvaluationTree > * getFunctionList() const;

    /**
     * Retreive whether the XML contains a function list.
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
     * @param CCopasiVectorN< CCopasiTask > *pTaskList
     * @return bool success
     */
    bool setTaskList(CCopasiVectorN< CCopasiTask > *pTaskList);

    /**
     * Retreive the task list.
     * @return CCopasiVectorN< CCopasiTask > * taskList
     */
    CCopasiVectorN< CCopasiTask > * getTaskList() const;

    /**
     * Retreive whether the XML contains a task list.
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
     * Retreive the plot list.
     * @return COutputDefinitionVector * plotList
     */
    COutputDefinitionVector * getPlotList() const;

    /**
     * Retreive whether the XML contains a plot list.
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
     * Retreive the report list.
     * @return CReportDefinitionVector * reportList
     */
    CReportDefinitionVector * getReportList() const;

    /**
     * Retreive whether the XML contains a report list.
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
     * Retreive the SCopasiXMLGUI.
     * @return SCopasiXMLGUI * pGUI
     */
    SCopasiXMLGUI * getGUI() const;

    /**
     * Retreive whether the XML contains a GUI.
     * @return bool have GUI
     */
    bool haveGUI() const;

    /**
     * Free the GUI.
     * @return bool success
     */
    bool freeGUI();

#ifdef WITH_LAYOUT
    /**
     * Set the layout list.
     * @param const CListOfLayouts & reportList
     * @return bool success
     */
    bool setLayoutList(const CListOfLayouts & reportList);

    /**
     * Retreive the layout list.
     * @return CListOfLayouts * layoutList
     */
    CListOfLayouts * getLayoutList() const;

    /**
     * Retreive whether the XML contains a layout list.
     * @return bool haveLayoutList
     */
    bool haveLayoutList() const;

    /**
     * Free the layout list.
     * @return bool success
     */
    bool freeLayoutList();
#endif

  private:
    /**
     * Save the model.
     * @return bool success
     */
    bool saveModel();

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

#ifdef WITH_LAYOUT
    /**
     * Save the list of reports.
     * @return bool success
     */
    bool saveLayoutList();

    void savePosition(const CLPoint& p, const std::string & tag = "Position");

    void saveDimensions(const CLDimensions& d);

    void saveBoundingBox(const CLBoundingBox& bb);

    void saveCurve(const CLCurve& c);
#endif

    /**
     * Save the SBML reference information
     * @return bool success
     */
    bool saveSBMLReference();

    /**
     * Save a Report Section such as Header, Body or Footer.
     * @param const std::string & name
     * @param const std::vector <CCopasiObjectName> & section
     * @return bool success
     */
    bool saveReportSection(const std::string & name,
                           const std::vector <CRegisteredObjectName> & section);

    /**
     * Build a list of functions.
     * @return bool success
     */
    bool buildFunctionList();

    // Attributes

    /**
     * The version of the COPASI XML Schema the current file adheres to.
     */
    CVersion mVersion;

    /**
     * Pointer to a model which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */
    CModel * mpModel;

    /**
     * Pointer to a vector of functions which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */
    CCopasiVectorN< CEvaluationTree > * mpFunctionList;

    /**
     * Pointer to a vector of tasks which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */
    CCopasiVectorN< CCopasiTask > * mpTaskList;

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

#ifdef WITH_LAYOUT
    /**
     * Pointer to a vector of plots which has been loaded or is to be saved.
     * The ownership is handed to the user.
     */
    CListOfLayouts * mpLayoutList;
#endif

    /**
     * SBML Reference
     */
    std::map< std::string, std::string > mSBMLReference;
  };

#endif // COPASI_CCopasiXML
