// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/CODEExporterXPPAUT.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2007/01/18 12:13:48 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CODEExpoterXPPAUT_H__
#define CODEExpoterXPPAUT_H__

#include "CODEExporter.h"

class CODEExporterXPPAUT: public CODEExporter
  {
  protected:

  public:

    /**
     ** Constructor for the exporter.
     */
    CODEExporterXPPAUT();

    virtual bool exportTitleData(const CModel* copasiModel, std::ofstream & outFile);

    virtual void setReservedNames();

    virtual std::string translateTimeVariableName();

    std::string setODEName(const std::string & objName);

    virtual std::string translateObjectName(const std::string & realName);

    std::string testName(const std::string & name);

    void exportSingleLine(const std::string & line, std::ostringstream & which);

    virtual bool exportSingleObject(std::ostringstream & which, std::string & name, std::string & expression, std::string & comments);

    virtual bool exportSingleMetabolite(const CMetab* metab, std::string & expression, std::string & comments);

    virtual bool exportSingleCompartement(const CCompartment* comp, std::string & expression, std::string & comments);

    virtual bool exportSingleModVal(const CModelValue* modval, std::string & expression, std::string & comments);

    virtual bool exportSingleParameter(const CCopasiParameter* param, std::string & expression, std::string & comments);

    virtual bool exportSingleODE(const CModelEntity* mentity, std::string & equation, std::string & comments);

    bool exportSingleFunction(const CFunction *func, std::set<std::string>& isExported);

    virtual std::string KineticFunction2ODEmember(const CReaction *reac);

    virtual std::string getDisplayFunctionString(CFunction * func);

    virtual std::string getDisplayExpressionString(CExpression * tmp);

    virtual std::string exportTitleString(const unsigned C_INT32 tmp);

    bool exportClosingData(const CModel* copasiModel, std::ofstream & outFile);

    std::map< std::string, unsigned C_INT32 > Frequancy;
    std::set<std::string> NameSet;
  };
#endif
