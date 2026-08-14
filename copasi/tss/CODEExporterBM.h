// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
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

#ifndef CODEExpoterBM_H__
#define CODEExpoterBM_H__

#include "CODEExporter.h"

class CODEExporterBM: public CODEExporter
{
protected:

public:

  /**
   ** Constructor for the exporter.
   */
  CODEExporterBM();

  virtual bool exportTitleData(const CDataModel* pDataModel, std::ostream & os);

  void setReservedNames() override;

  std::string translateTimeVariableName() override;

  std::string setODEName(const std::string & objName) override;

  std::string setConcentrationName(const std::string & objName) override;

  std::string translateObjectName(const std::string & realName) override;

  std::string testName(const std::string & name);

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

  //virtual bool exportSingleFunction(const CFunction *func, std::set<std::string>& isExported);

  std::string KineticFunction2ODEmember(const CReaction *reac) override;

  std::string getDisplayFunctionString(CFunction * func) override;

  std::string getDisplayExpressionString(CExpression * tmp) override;

  std::string exportTitleString(const size_t tmp) override;

  std::map< std::string, size_t > Frequancy;
  std::set<std::string> NameSet;
};
#endif
