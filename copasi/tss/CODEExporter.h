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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"

#include <iostream>
#include <fstream>
#include <ctype.h>

#ifndef ODEExpoter_H__
#define ODEExpoter_H__

class CDataModel;

class CODEExporter
{
protected:
  std::set<std::string> mExportedFunctions;
public:

  /**
   ** Constructor for the exporter.
   */

  CODEExporter();

  /**
   ** Destructor for the exporter.
   */
  virtual ~CODEExporter();

  bool exportToStream(const CDataModel* pDataModel, std::ostream & os);

  virtual bool preprocess(const CModel* copasiModel);

  virtual bool exportTitleData(const CModel* copasiModel, std::ostream & os);

  virtual bool exportMetabolites(const CModel* copasiModel);

  virtual bool exportMetabolitesConcentrations(const CModel* copasiModel);

  bool exportCompartments(const CModel* copasiModel);

  bool exportModelValues(const CModel* copasiModel);

#if 1
  void exportObjectNodesFromModel(const CDataModel* pDataModel);

  // CDataObject* findObjectFromRefresh(const CDataObject * tmp, const Refresh* ref);

  void exportSimulatedObject(const CDataObject * obj, const CDataModel* pDataModel);

  bool exportModelEntityExpression(const CDataObject * obj, const CDataModel* pDataModel);

  bool exportModelValuesExpressions(const CModel* copasiModel);

  void findFunctionsCalls(const CEvaluationNode* pNode);

  bool exportSingleFunction(const CFunction *func);

  virtual bool exportSingleFunction(const CFunction *func, std::set<std::string>& isExported);

  std::string isModelEntityExpressionODEExporterCompatible(const CModelEntity * tmp, const CExpression* pExpression, const CDataModel* pDataModel);

  std::string exportExpression(const CExpression* pExpression, const CDataModel* pDataModel);

  virtual std::string getSingleLineComment();

  virtual bool exportSingleModelEntity(const CModelEntity* tmp, std::string & expression, std::string & comments);
#endif

  virtual std::string getDisplayExpressionString(CExpression* tmp);

  bool exportReacParamsAndFuncs(const CModel* copasiModel);

  bool exportODEs(const CModel* copasiModel);

  virtual bool exportClosingData(const CModel* copasiModel, std::ostream & os);

  virtual void setReservedNames();

  virtual std::string exportNumber(double number);

  virtual std::string translateTimeVariableName();

  virtual std::string translateObjectName(const std::string & realName);

  virtual std::string setConcentrationName(const std::string & objName);

  virtual std::string setODEName(const std::string & objName);

  virtual bool exportSingleObject(std::ostringstream & which,
                                  const std::string & name,
                                  const std::string & expression,
                                  const std::string & comments);

  virtual bool exportSingleMetabolite(const CMetab* metab, std::string & expression, std::string & comments);

  virtual bool exportSingleCompartment(const CCompartment* comp, std::string & expression, std::string & comments);

  virtual bool exportSingleModVal(const CModelValue* modval, std::string & expression, std::string & comments);

  virtual bool exportSingleParameter(const CCopasiParameter* param, std::string & expression, std::string & comments);

  virtual std::string getDisplayFunctionString(CFunction * func);

  bool exportSingleFunction(CEvaluationNode* pNode, const CReaction *reac, size_t &index);
  bool exportSingleFunction(CEvaluationNode* pNode, const std::string& key, size_t &index);

  virtual bool exportKineticFunction(const CReaction* reac);

  virtual bool exportSingleODE(const CModelEntity* mentity, std::string & equation, std::string & comments);

  virtual bool exportKineticFunctionGroup(const CModel* copasiModel);

  virtual std::string KineticFunction2ODEmember(const CReaction *reac);

  virtual std::string exportTitleString(const size_t tmp);

  virtual std::string exportClosingString(const size_t tmp);

  /**
  **        This method tests if a string consists only of whitespace characters
  **/
  virtual bool isEmptyString(std::string & str);

  /**
   **      This method modifies the export tree of the function for internal calls of Mass Action
  **/
  void modifyTreeForMassAction(CFunction* tmpfunc);

  /**
   **         This method assembles an expression sub tree for some internal call of Mass Action.
   **         The sub tree has to be included in the tree of corresponding root kinetic function in order to
   **         export this function  whithout the user defined internall Mass Action calls
   **/
  void assembleSubTreeForMassAction(CEvaluationNode* newNode, CEvaluationNode* child1, CEvaluationNode* child2);

  std::map< std::string, std::string > NameMap;
  std::string timeKey;
  std::map< std::string, std::string > equations;

  std::ostringstream initial;
  std::ostringstream fixed;
  std::ostringstream assignment;
  std::ostringstream functions;
  std::ostringstream headers;
  std::ostringstream ode;

  enum Object
  {
    INITIAL = 0,
    FIXED,
    ASSIGNMENT,
    HEADERS,
    FUNCTIONS,
    ODEs
  };
};
#endif
