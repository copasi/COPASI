// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CODEExpoterC_H__
#define CODEExpoterC_H__

#include "CODEExporter.h"

class CODEExporterC: public CODEExporter
{
protected:

public:

  /**
   ** Constructor for the exporter.
   */
  CODEExporterC();

  virtual bool preprocess(const CModel* copasiModel);

  virtual bool exportTitleData(const CModel* copasiModel, std::ostream & os);

  virtual void setReservedNames();

  virtual std::string exportNumber(double number);

  virtual std::string translateTimeVariableName();

  std::string setExportName(const CModelEntity::Status & status, size_t n[], size_t dependent);

  std::string setConcentrationName(const CModelEntity::Status & status, size_t n[], size_t dependent);

  std::string setODEName(const std::string & objName);

  void setExportNameOfFunction(const CEvaluationNode* pNode, std::set<std::string> & tmpset);

  virtual std::string translateObjectName(const std::string & realName);

  std::string testName(const std::string & name);

  virtual bool exportSingleObject(std::ostringstream & which,
                                  const std::string & name,
                                  const std::string & expression,
                                  const std::string & comments);

  virtual bool exportSingleMetabolite(const CMetab* metab, std::string & expression, std::string & comments);

  virtual bool exportSingleCompartment(const CCompartment* comp, std::string & expression, std::string & comments);

  virtual bool exportSingleModVal(const CModelValue* modval, std::string & expression, std::string & comments);

  virtual bool exportSingleModelEntity(const CModelEntity* tmp, std::string & expression, std::string & comments);

  virtual bool exportSingleParameter(const CCopasiParameter* param, std::string & expression, std::string & comments);

  virtual bool exportSingleODE(const CModelEntity* mentity, std::string & equation, std::string & comments);

  virtual bool exportSingleFunction(const CFunction *func, std::set<std::string>& isExported);

  virtual std::string getSingleLineComment();

  virtual bool exportKineticFunctionGroup(const CModel* copasiModel);

  virtual std::string KineticFunction2ODEmember(const CReaction *reac);

  virtual std::string exportTitleString(const size_t tmp);

  virtual std::string exportClosingString(const size_t tmp);

  virtual bool exportKineticFunction(const CReaction* reac);

  virtual std::string getDisplayExpressionString(CExpression * tmp);

  std::map< std::string, size_t > Frequancy;
  std::set<std::string> NameSet;
};
#endif
