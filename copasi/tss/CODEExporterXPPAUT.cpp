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

#include "CODEExporterXPPAUT.h"

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
CODEExporterXPPAUT::CODEExporterXPPAUT()
{}

bool CODEExporterXPPAUT::exportTitleData(const CDataModel* pDataModel, std::ostream & os)
{
  os << "@ t0=0,";  //TODO
  const CTrajectoryTask * pTrajectory =
    dynamic_cast<const CTrajectoryTask *>(&const_cast<CDataModel*>(pDataModel)->getTaskList()->operator[]("Time-Course"));
  const CTrajectoryProblem * pTrajectoryProblem =
    dynamic_cast<const CTrajectoryProblem *>(pTrajectory->getProblem());

  os << "total=" << pTrajectoryProblem->getDuration() << ",";
  os << "dt=" << pTrajectoryProblem->getStepSize()
     << ",METH=stiff" << std::endl; //gear is the only method with automatic step size

  return true;
}

std::string CODEExporterXPPAUT::translateTimeVariableName()
{return "t";}
/**
 **      This method adapt a Copasi name for XPPAUT syntax:
 **      all XPPAUT names can have up to 9 letters each.
 **      Names can not start with a number.
 **      Any other combination of letters and numbers is valid as is the underscore.
 **/
std::string CODEExporterXPPAUT::translateObjectName(const std::string & realName)
{
  std::locale C("C");
  char ch;

  std::string newName;
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

            default:
              break;
          }
    }

  newName = tmpName.str();

  size_t newName_size = newName.size();

  if (newName_size > 7)
    {
      std::ostringstream cutName;

      for (i = 0; i < 7; i++)
        cutName << newName[i];

      newName = cutName.str();
    }

  return testName(newName);
}
/**
 **      This method tests whether the given XPPAUT name already assigned,
 **      put the new name (in cappital letters:
 **      all names can be upper or lower case)
 **      in the set of assigned names
 **      or  modify the name
 **/
std::string CODEExporterXPPAUT::testName(const std::string & name)
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

      std::string ecount;
      std::ostringstream tmpecount;
      std::ostringstream tmpname;
      size_t ecount_size, tmpname_size;

      Frequancy[tmp.str()]++;
      tmpecount << Frequancy[tmp.str()];

      ecount = tmpecount.str();

      ecount_size = ecount.size();

      if (ecount_size > 6)
        {
          CCopasiMessage(CCopasiMessage::ERROR, "too many repeated names to modify to XPP syntax"); //TODO
          fatalError();
        }

      tmpname_size = name_size + ecount_size;

      if (tmpname_size > 7)
        {
          for (i = 0; i < (7 - ecount_size); i++)
            tmpname << name[i];
        }
      else
        tmpname << name << ecount;

      return testName(tmpname.str());
    }
}

void CODEExporterXPPAUT::setReservedNames()
{
  size_t i;

  const std::string reserved[45] =
  {
    "SIN", "COS", "TAN", "ATAN", "ATAN2", "SINH", "EXP", "DELAY", "LN", "LOG10",
    "LOG", "T", "PI", "IF", "THEN", "ELSE", "ASIN", "ACOS", "HEAV", "SIGN",
    "CEIL", "FLR", "RAN", "ABS", "MAX", "MIN", "NORMAL", "BESSELJ", "BESSELY", "ERF",
    "ERFS", "ARG1", "ARG2", "ARG2", "ARG4", "ARG5", "ARG6", "ARG7", "ARG8", "ARG9",
    "SHIFT", "NOT", "INT", "SUM", "OF"
  };

  for (i = 0; i < 45; i++)
    {
      NameSet.insert(reserved[i]);
      Frequancy[reserved[i]] = 0;
    }

  return;
}

std::string CODEExporterXPPAUT::setODEName(const std::string & objName)
{
  return "d" + objName + "/dt";
}

std::string CODEExporterXPPAUT::setConcentrationName(const std::string & objName)
{
  return objName + "_c";
}

/*
 **   The line length in XPPAUT ODE files (ASCII readable files) is limited to 256 characters.
 **   Individual lines can be continued with the UNIX backslash character, "\".
 **   The total length of any line cannot exceed 1000 characters.
 */
void CODEExporterXPPAUT::exportSingleLine(const std::string & line, std::ostringstream & which)
{

  std::locale C("C");

  size_t limit = 256, total = 1000;

  //size_t limit = 10, total = 15;
  if (line.size() > total)
    CCopasiMessage(CCopasiMessage::WARNING, MCODEExporter + 1);

  if (line.size() > limit)
    {

      size_t i, pos0, pos, end = line.size();

      pos0 = 0;
      pos = limit - 1;

      while (pos < end)
        {

          std::string part;
          char ch;
          ch = line[pos];

          while (std::isalnum(ch, C) || ch == '_' || ch == ')')
            {
              pos--;
              ch = line[pos];
            }

          for (i = pos0; i < pos; i++)
            {
              part += line[i];
            }

          part += " \\";

          which << part.c_str() << std::endl;

          pos0 = pos;
          pos += limit;
        }

      if (pos > end)
        {
          std::string part;

          for (i = pos0; i < end; i++)
            {
              part += line[i];
            }

          which << part.c_str() << std::endl;
        }
    }
  else
    which << line << std::endl;

  return;
}

bool CODEExporterXPPAUT::exportSingleObject(std::ostringstream & which,
    const std::string & name,
    const std::string & expression,
    const std::string & /* comments */)
{
  std::ostringstream line;

  line << name << "=" << expression;
  exportSingleLine(line.str(), which);

  return true;
}

bool CODEExporterXPPAUT::exportSingleMetabolite(const CMetab* metab, std::string & expression, std::string & comments)
{
  std::string name;

  std::ostringstream smKey;
  smKey << "sm_" << metab->getKey();
  name = NameMap[smKey.str()];

  switch (metab->getStatus())
    {
      case CModelEntity::Status::FIXED:
      {
        fixed << "#" << comments << std::endl;
        fixed << "param ";

        if (!exportSingleObject(fixed, name, expression, comments))
          return false;

        break;
      }

      case CModelEntity::Status::ODE:
      case CModelEntity::Status::REACTIONS:
      {
        if (!metab->isDependent())
          {
            initial << "#" << comments << std::endl;
            initial << "init ";

            if (!exportSingleObject(initial, name, expression, comments))
              return false;
          }
        else
          {
            assignment << "#" << comments << std::endl;

            if (!exportSingleObject(assignment, name, expression, comments))
              return false;
          }

        break;
      }

      case CModelEntity::Status::ASSIGNMENT:
      {
        assignment << "#" << comments << std::endl;

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

bool CODEExporterXPPAUT::exportSingleCompartment(const CCompartment* comp, std::string & expression, std::string & comments)
{

  switch (comp->getStatus())
    {
      case CModelEntity::Status::FIXED:
      {
        fixed << "#" << comments << std::endl;
        fixed << "param ";

        if (!exportSingleObject(fixed, NameMap[comp->getKey()], expression, comments))
          return false;

        break;
      }

      case CModelEntity::Status::ODE:
      {
        initial << "#" << comments << std::endl;
        initial << "init ";

        if (!exportSingleObject(initial, NameMap[comp->getKey()], expression, comments))
          return false;

        break;
      }

      case CModelEntity::Status::ASSIGNMENT:
      {
#if 0
        assignment << "#" << comments << std::endl;

        if (!exportSingleObject(assignment, NameMap[comp->getKey()], expression, comments))
          return false;

#endif
        break;
      }

      default:
        return false;
        break;
    }

  return true;
}

bool CODEExporterXPPAUT::exportSingleModVal(const CModelValue* modval, std::string & expression, std::string & comments)
{

  switch (modval->getStatus())
    {
      case CModelEntity::Status::FIXED:
      {
        fixed << "#" << comments << std::endl;
        fixed << "param ";

        if (!exportSingleObject(fixed, NameMap[modval->getKey()], expression, comments))
          return false;

        break;
      }

      case CModelEntity::Status::ODE:
      {
        initial << "#" << comments << std::endl;
        initial << "init ";

        if (!exportSingleObject(initial, NameMap[modval->getKey()], expression, comments))
          return false;

        break;
      }

      case CModelEntity::Status::ASSIGNMENT:
      {
#if 0
        assignment << "#" << comments << std::endl;

        if (!exportSingleObject(assignment, NameMap[modval->getKey()], expression, comments))
          return false;

#endif
        break;
      }

      default:
        return false;
        break;
    }

  return true;
}

bool CODEExporterXPPAUT::exportSingleModelEntity(const CModelEntity* tmp, std::string & expression, std::string & comments)
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
        fixed << "#" << comments << std::endl;
        fixed << "param ";

        if (!exportSingleObject(fixed, name, expression, comments))
          return false;

        break;
      }

      case CModelEntity::Status::ODE:
      {
        initial << "#" << comments << std::endl;
        initial << "init ";

        if (!exportSingleObject(initial, name, expression, comments))
          return false;

        break;
      }

      case CModelEntity::Status::ASSIGNMENT:
      {
        assignment << "#" << comments << std::endl;

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

bool CODEExporterXPPAUT::exportSingleParameter(const CCopasiParameter* param, std::string & expression, std::string & comments)
{
  fixed << "#" << comments << std::endl;

  fixed << "param ";

  if (!exportSingleObject(fixed, NameMap[param->getKey()], expression, comments)) return false;

  return true;
}

std::string CODEExporterXPPAUT::getDisplayFunctionString(CFunction * func)
{
  std::string str1;
  str1 = func->getRoot()->buildXPPString();
  return str1;
}

std::string CODEExporterXPPAUT::getDisplayExpressionString(CExpression * tmp)
{
  std::string str1;
  str1 = tmp->getRoot()->buildXPPString();
  return str1;
}

std::string CODEExporterXPPAUT::KineticFunction2ODEmember(const CReaction *reac)
{

  std::ostringstream localKey;
  localKey << reac->getKey() << "_root_func";

  return NameMap[localKey.str()];
}

bool CODEExporterXPPAUT::exportSingleODE(const CModelEntity* mentity, std::string & equation, std::string & comments)
{
  std::ostringstream odeKey;

  if (!isEmptyString(comments)) ode << "#" << comments << std::endl;

  odeKey << "ode_" << mentity->getKey();

  if (!exportSingleObject(ode, NameMap[odeKey.str()], equation, comments)) return false;

  return true;
}

std::string CODEExporterXPPAUT::exportTitleString(const size_t tmp)
{
  switch (tmp)
    {
      case INITIAL:
        return "# Initial values:";

      case FIXED:
        return "# Fixed Model Entities:";

      case ASSIGNMENT:
        return "# Assignment Model Entities:";

      case FUNCTIONS:
        return "#Kinetics:  ";

      case HEADERS:
        return " ";

      case ODEs:
        return "# Equations:";

      default:
        return " ";
    }
}

bool CODEExporterXPPAUT::exportClosingData(const CModel* /* copasiModel */, std::ostream & os)
{
  os << "done" << std::endl;
  return true;
}
