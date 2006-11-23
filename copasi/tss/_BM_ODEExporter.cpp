/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/Attic/_BM_ODEExporter.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: nsimus $
   $Date: 2006/11/23 10:35:32 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <locale>
#include <math.h>
#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"

#include "_BM_ODEExporter.h"

#include "model/CModel.h"
#include "model/CMetab.h"
#include "model/CMetabNameInterface.h"
#include "utilities/CCopasiVector.h"
#include "model/CReaction.h"
#include "model/CMoiety.h"
#include "model/CChemEqElement.h"
#include "function/CExpression.h"
#include "function/CFunction.h"
#include "function/CFunctionDB.h"
#include "report/CKeyFactory.h"
#include "function/CEvaluationTree.h"
#include "function/CEvaluationNode.h"
#include "function/CEvaluationNodeObject.h"
#include "function/CEvaluationNodeOperator.h"
#include "function/CEvaluationNodeFunction.h"
#include "utilities/CCopasiTree.h"

#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"

#include <iostream>
#include <fstream>
#include <ctype.h>

/**
 ** Constructor for the exporter.
 */
_BM_ODEExporter::_BM_ODEExporter()
{}
bool _BM_ODEExporter::exportTitleData(const CModel* copasiModel, std::ofstream & outFile)
{
  outFile << "METHOD stiff" << std::endl;
  outFile << std::endl;
  outFile << "STARTTIME = 0" << std::endl;

  CTrajectoryTask * pTrajectory =
    dynamic_cast<CTrajectoryTask *>((*CCopasiDataModel::Global->getTaskList())["Time-Course"]);
  CTrajectoryProblem * pTrajectoryProblem =
    dynamic_cast<CTrajectoryProblem *>(pTrajectory->getProblem());

  outFile << "STOPTIME = " << pTrajectoryProblem->getDuration() << std::endl;
  outFile << "DT = " << pTrajectoryProblem->getStepSize() << std::endl;
  outFile << std::endl;

  return true;
}

std::string _BM_ODEExporter::translateTimeVariableName()
{return "TIME";}

/**
 **      This method adapt a Copasi name for Berkeley Madonna syntax:
 **      Names can not start with a number.
 **      Any other combination of letters and numbers is valid as is the underscore.
 **/
std::string _BM_ODEExporter::translateObjectName(const std::string & realName)
{
  std::locale C("C");
  char ch;

  std::ostringstream tmpName;

  unsigned C_INT32 realName_size = realName.size();
  unsigned C_INT32 i;

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

std::string _BM_ODEExporter::testName(const std::string & name)
{
  std::locale C("C");
  char ch;

  std::ostringstream newname, tmp;

  unsigned C_INT32 name_size = name.size();
  unsigned C_INT32 i;

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

void _BM_ODEExporter::setReservedNames()
{return;}  // TODO

std::string _BM_ODEExporter::setODEName(const std::string & objName)
{
  return "d/dt(" + objName + ")";
}

bool _BM_ODEExporter::exportSingleObject(std::ostringstream & which, std::string & name, std::string & expression, std::string & comments)
{
  which << name << " = " << expression
  << '\t' << '\t' << "; " << comments << std::endl;

  return true;
}

bool _BM_ODEExporter::exportSingleMetabolite(const CMetab* metab, std::string & expression, std::string & comments)
{
  switch (metab->getStatus())
    {
    case CModelEntity::FIXED:
      {
        if (!exportSingleObject(fixed, NameMap[metab->getKey()], expression, comments))
          return false;
        break;
      }
    case CModelEntity::REACTIONS:
      {
        if (!metab->isDependent())
          {
            initial << "init ";
            if (!exportSingleObject(initial, NameMap[metab->getKey()], expression, comments))
              return false;
          }
        else
          {
            if (!exportSingleObject(assignment, NameMap[metab->getKey()], expression, comments))
              return false;
          }
        break;
      }
    case CModelEntity::ASSIGNMENT:
      {
        if (!exportSingleObject(assignment, NameMap[metab->getKey()], expression, comments))
          return false;
        break;
      }
    default:
      return false;
      break;
    }

  return true;
}

bool _BM_ODEExporter::exportSingleCompartement(const CCompartment* comp, std::string & expression, std::string & comments)
{
  if (!exportSingleObject(fixed, NameMap[comp->getKey()], expression, comments)) return false;

  return true;
}

bool _BM_ODEExporter::exportSingleModVal(const CModelValue* modval, std::string & expression, std::string & comments)
{
  switch (modval->getStatus())
    {
    case CModelEntity::FIXED:
      {
        if (!exportSingleObject(fixed, NameMap[modval->getKey()], expression, comments))
          return false;
        break;
      }
    case CModelEntity::ODE:
      {
        initial << "init ";
        if (!exportSingleObject(initial, NameMap[modval->getKey()], expression, comments))
          return false;
        break;
      }
    case CModelEntity::ASSIGNMENT:
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

bool _BM_ODEExporter::exportSingleParameter(const CCopasiParameter* param, std::string & expression, std::string & comments)
{
  if (!exportSingleObject(fixed, NameMap[param->getKey()], expression, comments)) return false;

  return true;
}

bool _BM_ODEExporter::exportSingleODE(const CModelEntity* mentity, std::string & equation, std::string & comments)
{
  std::ostringstream odeKey;

  odeKey << "ode_" << mentity->getKey();

  if (!exportSingleObject(ode, NameMap[odeKey.str()], equation, comments)) return false;

  return true;
}

std::string _BM_ODEExporter::getDisplayFunctionString(CFunction * func)
{
  std::string str1;
  str1 = func->getRoot()->getDisplay_MMD_String(func).c_str();
  return str1;
}

std::string _BM_ODEExporter::getDisplayExpressionString(CExpression * tmp)
{
  std::string str1;
  str1 = tmp->getRoot()->getDisplay_MMD_String(tmp).c_str();
  return str1;
}

std::string _BM_ODEExporter::KineticFunction2ODEmember(const CReaction *reac)
{
  std::ostringstream localKey;
  localKey << reac->getKey() << "_root_func";
  return NameMap[localKey.str()];
}

std::string _BM_ODEExporter::exportTitleString(const unsigned C_INT32 tmp)
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
