// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/CODEExporter.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/01/11 15:12:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "model/CModel.h"
#include "model/CMetab.h"

#include <iostream>
#include <fstream>
#include <ctype.h>

#ifndef ODEExpoter_H__
#define ODEExpoter_H__

class CODEExporter
  {
  protected:

  public:

    /**
     ** Constructor for the exporter.
     */

    CODEExporter();

    /**
     ** Destructor for the exporter.
     */
    virtual ~CODEExporter();

    bool exportMathModel(const CModel* copasiModel, std::string mmasciiFilename, std::string Filter, bool overwriteFile);

    virtual bool preprocess(const CModel* copasiModel);

    virtual bool exportTitleData(const CModel* copasiModel, std::ofstream & outFile);

    virtual bool exportMetabolites(const CModel* copasiModel);

    virtual bool exportMetabolitesConcentrations(const CModel* copasiModel);

    bool exportCompartments(const CModel* copasiModel);

    bool exportModelValues(const CModel* copasiModel);

#if 1
    void exportObjectNodesFromModel(const CModel * model);

    CCopasiObject* findObjectFromRefresh(CCopasiObject * tmp, const Refresh* ref);

    void exportSimulatedObject(CCopasiObject * obj);

    bool exportModelEntityExpression(CCopasiObject * obj);

    std::string isModelEntityExpressionODEExporterCompatible(CModelEntity * tmp, const CExpression* pExpression);

    std::string exportExpression(const CExpression* pExpression);

    virtual bool exportSingleModelEntity(const CModelEntity* tmp, std::string & expression, std::string & comments);
#endif

    virtual std::string getDisplayExpressionString(CExpression* tmp);

    bool exportReacParamsAndFuncs(const CModel* copasiModel);

    bool exportODEs(const CModel* copasiModel);

    virtual bool exportClosingData(const CModel* copasiModel, std::ofstream & outFile);

    virtual void setReservedNames();

    virtual std::string translateTimeVariableName();

    virtual std::string translateObjectName(const std::string & realName);

    virtual std::string setConcentrationName(const std::string & objName);

    virtual std::string setODEName(const std::string & objName);

    virtual bool exportSingleObject(std::ostringstream & which, std::string & name, std::string & expression, std::string & comments);

    virtual bool exportSingleMetabolite(const CMetab* metab, std::string & expression, std::string & comments);

    virtual bool exportSingleCompartment(const CCompartment* comp, std::string & expression, std::string & comments);

    virtual bool exportSingleModVal(const CModelValue* modval, std::string & expression, std::string & comments);

    virtual bool exportSingleParameter(const CCopasiParameter* param, std::string & expression, std::string & comments);

    virtual std::string getDisplayFunctionString(CFunction * func);

    bool exportSingleFunction(CEvaluationNode* pNode, const CReaction *reac, unsigned C_INT32 &index);

    virtual bool exportKineticFunction (CReaction* reac);

    virtual bool exportSingleODE(const CModelEntity* mentity, std::string & equation, std::string & comments);

    virtual bool exportKineticFunctionGroup (const CModel* copasiModel);

    virtual std::string KineticFunction2ODEmember(const CReaction *reac);

    virtual std::string exportTitleString(const unsigned C_INT32 tmp);

    virtual std::string exportClosingString(const unsigned C_INT32 tmp);

    /**
    **        This method tests if a string consists only of whitespace characters
    **/
    bool isEmptyString(std::string & str);

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
