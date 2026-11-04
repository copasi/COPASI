// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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

#ifndef CODEExpoterXPPAUT_H__
#define CODEExpoterXPPAUT_H__

#include "CODEExporter.h"

class CDataModel;

class CODEExporterXPPAUT: public CODEExporter
{
protected:

public:

  /**
   ** Constructor for the exporter.
   */
  CODEExporterXPPAUT();

  virtual bool exportTitleData(const CDataModel* pDataModel, std::ostream & os);

  void setReservedNames() override;

  std::string translateTimeVariableName() override;

  std::string setConcentrationName(const std::string & objName) override;

  std::string setODEName(const std::string & objName) override;

  std::string translateObjectName(const std::string & realName) override;

  std::string testName(const std::string & name);

  void exportSingleLine(const std::string & line, std::ostringstream & which);

  bool exportSingleObject(std::ostringstream & which,
                          const std::string & name,
                          const std::string & expression,
                          const std::string & comments) override;

  bool exportSingleMetabolite(const CMetab* metab, std::string & expression, std::string & comments) override;

  bool exportSingleCompartment(const CCompartment* comp, std::string & expression, std::string & comments) override;

  bool exportSingleModVal(const CModelValue* modval, std::string & expression, std::string & comments) override;

  bool exportSingleModelEntity(const CModelEntity* tmp, std::string & expression, std::string & comments) override;

  bool exportSingleParameter(const CCopasiParameter* param, std::string & expression, std::string & comments) override;

  bool exportSingleODE(const CModelEntity* mentity, std::string & equation, std::string & comments) override;

  //bool exportSingleFunction(const CFunction *func, std::set<std::string>& isExported) override;

  std::string KineticFunction2ODEmember(const CReaction *reac) override;

  std::string getDisplayFunctionString(CFunction * func) override;

  std::string getDisplayExpressionString(CExpression * tmp) override;

  std::string exportTitleString(const size_t tmp) override;

  bool exportClosingData(const CModel* copasiModel, std::ostream & os) override;

  std::map< std::string, unsigned C_INT32 > Frequancy;
  std::set<std::string> NameSet;
};
#endif
