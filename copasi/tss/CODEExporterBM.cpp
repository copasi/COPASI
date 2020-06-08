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

#include <sstream>
#include <locale>
#include <cmath>

#include "copasi/copasi.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"

#include "CODEExporterBM.h"

#include "copasi/model/CModel.h"
#include "copasi/model/CMetab.h"
#include "copasi/model/CMetabNameInterface.h"
#include "copasi/core/CDataVector.h"
#include "copasi/model/CReaction.h"
#include "copasi/model/CMoiety.h"
#include "copasi/model/CChemEqElement.h"
#include "copasi/function/CExpression.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/function/CEvaluationTree.h"
#include "copasi/function/CEvaluationNode.h"
#include "copasi/function/CEvaluationNodeObject.h"
#include "copasi/function/CEvaluationNodeOperator.h"
#include "copasi/function/CEvaluationNodeFunction.h"
#include "copasi/utilities/CCopasiTree.h"

#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/trajectory/CTrajectoryProblem.h"

#include <iostream>
#include <fstream>
#include <ctype.h>

/**
 ** Constructor for the exporter.
 */
CODEExporterBM::CODEExporterBM()
{}
bool CODEExporterBM::exportTitleData(const CDataModel* pDataModel, std::ostream & os)
{
  os << "METHOD stiff" << std::endl;
  os << std::endl;
  os << "STARTTIME = 0" << std::endl;

  const CTrajectoryTask * pTrajectory =
    dynamic_cast<const CTrajectoryTask *>(&const_cast<CDataModel*>(pDataModel)->getTaskList()->operator[]("Time-Course"));
  const CTrajectoryProblem * pTrajectoryProblem =
    dynamic_cast<const CTrajectoryProblem *>(pTrajectory->getProblem());

  os << "STOPTIME = " << pTrajectoryProblem->getDuration() << std::endl;
  os << "DT = " << pTrajectoryProblem->getStepSize() << std::endl;
  os << std::endl;

  return true;
}

std::string CODEExporterBM::translateTimeVariableName()
{return "TIME";}

/**
 **      This method adapt a Copasi name for Berkeley Madonna syntax:
 **      Names can not start with a number.
 **      Any other combination of letters and numbers is valid as is the underscore.
 **/
std::string CODEExporterBM::translateObjectName(const std::string & realName)
{
  std::locale C("C");
  char ch;

  std::ostringstream tmpName;

  size_t realName_size = realName.size();
  size_t i;

  ch = realName[0];

  if (!std::isalpha(ch, C))
    {
      tmpName << "_";

      if (std::isdigit(ch, C)) tmpName << ch;
    }
  else tmpName << ch;

  for (i = 1; i < realName_size; i++)
    {
      ch = realName[i];

      if (std::isalpha(ch, C))
        {
          if (std::isspace(realName[i - 1], C) && std::islower(ch, C))
            tmpName << (char) toupper(ch);
          else
            tmpName << ch;
        }

      if (std::isdigit(ch, C)) tmpName << ch;

      if (std::ispunct(ch, C))
        switch (ch)
          {
            case '_':
              tmpName << ch;
              break;

            case '-':
              tmpName << "_";
              break;

            case '{':
              tmpName << "_";
              break;

            case '}':
              tmpName << "_";
              break;

            case '(':
              tmpName << "_";
              break;

            case ')':
              tmpName << "_";
              break;

            default:
              break;
          }
    }

  return testName(tmpName.str());
}
/**
 **      This method tests whether the given Berkeley Madonna name already assigned,
 **      put the new name (in cappital letters:
 **      all names can be upper or lower case)
 **      in the set of assigned names
 **      or  modify the name
 **/

std::string CODEExporterBM::testName(const std::string & name)
{
  std::locale C("C");
  char ch;

  std::ostringstream newname, tmp;

  size_t name_size = name.size();
  size_t i;

  for (i = 0; i < name_size; i++)
    {
      ch = name[i];

      if (std::isalpha(ch, C) && std::islower(ch, C))
        tmp << (char) toupper(ch);
      else
        tmp << ch;
    }

  if (NameSet.find(tmp.str()) == NameSet.end())
    {
      NameSet.insert(tmp.str());
      Frequancy[tmp.str()] = 0;

      return name;
    }
  else
    {
      Frequancy[tmp.str()]++;
      newname << name << "_" << Frequancy[tmp.str()];

      return testName(newname.str());
    }
}

void CODEExporterBM::setReservedNames()
{return;}  // TODO

std::string CODEExporterBM::setConcentrationName(const std::string & objName)
{
  return objName + "_c";
}

std::string CODEExporterBM::setODEName(const std::string & objName)
{
  return "d/dt(" + objName + ")";
}

bool CODEExporterBM::exportSingleObject(std::ostringstream & which,
                                        const std::string & name,
                                        const std::string & expression,
                                        const std::string & comments)
{
  which << name << " = " << expression
        << '\t' << '\t' << "; " << comments << std::endl;

  return true;
}

bool CODEExporterBM::exportSingleMetabolite(const CMetab* metab, std::string & expression, std::string & comments)
{
  std::string name;

  std::ostringstream smKey;
  smKey << "sm_" << metab->getKey();
  name = NameMap[smKey.str()];

  switch (metab->getStatus())
    {
      case CModelEntity::Status::FIXED:

        if (!exportSingleObject(fixed, name, expression, comments))
          return false;

        break;

      case CModelEntity::Status::REACTIONS:
      {
        if (metab->isDependent())
          {
            if (!exportSingleObject(assignment, name, expression, comments))
              return false;
          }
        else
          {
            initial << "init ";

            if (!exportSingleObject(initial, name, expression, comments))
              return false;
          }

        break;
      }

      case CModelEntity::Status::ODE:
      {
        initial << "init ";

        if (!exportSingleObject(initial, name, expression, comments))
          return false;

        break;
      }

      case CModelEntity::Status::ASSIGNMENT:
      {
        if (!exportSingleObject(assignment, name, expression, comments))
          return false;

        break;
      }

      default:
        return false;
        break;
    }

  return true;
}

bool CODEExporterBM::exportSingleCompartment(const CCompartment* comp, std::string & expression, std::string & comments)
{
  switch (comp->getStatus())
    {
      case CModelEntity::Status::FIXED:
      {
        if (!exportSingleObject(fixed, NameMap[comp->getKey()], expression, comments))
          return false;

        break;
      }

      case CModelEntity::Status::ODE:
      {
        initial << "init ";

        if (!exportSingleObject(initial, NameMap[comp->getKey()], expression, comments))
          return false;

        break;
      }

      case CModelEntity::Status::ASSIGNMENT:
      {
        if (!exportSingleObject(assignment, NameMap[comp->getKey()], expression, comments))
          return false;

        break;
      }

      default:
        return false;
        break;
    }

  return true;
}

bool CODEExporterBM::exportSingleModVal(const CModelValue* modval, std::string & expression, std::string & comments)
{
  switch (modval->getStatus())
    {
      case CModelEntity::Status::FIXED:
      {
        if (!exportSingleObject(fixed, NameMap[modval->getKey()], expression, comments))
          return false;

        break;
      }

      case CModelEntity::Status::ODE:
      {
        initial << "init ";

        if (!exportSingleObject(initial, NameMap[modval->getKey()], expression, comments))
          return false;

        break;
      }

      case CModelEntity::Status::ASSIGNMENT:
      {
        if (!exportSingleObject(assignment, NameMap[modval->getKey()], expression, comments))
          return false;

        break;
      }

      default:
        return false;
        break;
    }

  return true;
}

bool CODEExporterBM::exportSingleModelEntity(const CModelEntity* tmp, std::string & expression, std::string & comments)
{

  std::string name;

  const CMetab* metab;
  metab = dynamic_cast< const CMetab * >(tmp);

  if (metab)
    {
      std::ostringstream smKey;
      smKey << "sm_" << metab->getKey();
      name = NameMap[smKey.str()];
    }
  else
    name = NameMap[tmp->getKey()];

  switch (tmp->getStatus())
    {
      case CModelEntity::Status::FIXED:
      {
        if (!exportSingleObject(fixed, name, expression, comments))
          return false;

        break;
      }

      case CModelEntity::Status::ODE:
      {
        if (!exportSingleObject(initial, name, expression, comments))
          return false;

        break;
      }

      case CModelEntity::Status::ASSIGNMENT:
      {
        if (!exportSingleObject(assignment, name, expression, comments))
          return false;

        break;
      }

      default:
        return false;
        break;
    }

  return true;
}

bool CODEExporterBM::exportSingleParameter(const CCopasiParameter* param, std::string & expression, std::string & comments)
{
  if (!exportSingleObject(fixed, NameMap[param->getKey()], expression, comments)) return false;

  return true;
}

bool CODEExporterBM::exportSingleODE(const CModelEntity* mentity, std::string & equation, std::string & comments)
{
  std::ostringstream odeKey;

  odeKey << "ode_" << mentity->getKey();

  if (!exportSingleObject(ode, NameMap[odeKey.str()], equation, comments)) return false;

  return true;
}

std::string CODEExporterBM::getDisplayFunctionString(CFunction * func)
{
  std::string str1;
  str1 = func->getRoot()->buildBerkeleyMadonnaString();
  return str1;
}

std::string CODEExporterBM::getDisplayExpressionString(CExpression * tmp)
{
  std::string str1;
  str1 = tmp->getRoot()->buildBerkeleyMadonnaString();
  return str1;
}

std::string CODEExporterBM::KineticFunction2ODEmember(const CReaction *reac)
{
  std::ostringstream localKey;
  localKey << reac->getKey() << "_root_func";
  return NameMap[localKey.str()];
}

std::string CODEExporterBM::exportTitleString(const size_t tmp)
{
  switch (tmp)
    {
      case INITIAL:
        return "{Initial values:}";

      case FIXED:
        return "{Fixed Model Entities: }";

      case ASSIGNMENT:
        return "{Assignment Model Entities: }";

      case FUNCTIONS:
        return "{Kinetics: }";

      case HEADERS:
        return " ";

      case ODEs:
        return "{Equations:}";

      default:
        return " ";
    }
}
