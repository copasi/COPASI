// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#include "CODEExporterC.h"

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

#include <sbml/util/util.h>

#include <iostream>
#include <fstream>
#include <ctype.h>

/**
 ** Constructor for the exporter.
 */
CODEExporterC::CODEExporterC()
{}

std::string CODEExporterC::getSingleLineComment()
{
  return "// ";
}

bool startsWith(const std::string& str, const std::string& sub)
{
  if (str.length() < sub.length()) return false;

  if (sub.empty()) return true;

  for (size_t i = 0; i < sub.length(); ++i)
    if (str[i] != sub[i]) return false;

  return true;
}

void printNameForKey(std::ostringstream& stream, CKeyFactory* kf, const std::string& key, const std::string prefix = "")
{
  CDataObject* obj = kf->get(key);

  if (obj != NULL)
    {
      stream << "\"" << prefix << obj->getObjectName() << "\", ";
    }
  else if (startsWith(key, "sm_"))
    {
      printNameForKey(stream, kf, key.substr(3), "");
    }
  else if (startsWith(key, "ode_"))
    {
      printNameForKey(stream, kf, key.substr(4), "ODE ");
    }
  else
    {
      stream << "\"" << prefix << key << "\", ";
    }
}

bool CODEExporterC::exportTitleData(const CModel* copasiModel, std::ostream & os)
{

  size_t metab_size = copasiModel->getMetabolitesX().size();
  size_t indep_size = copasiModel->getNumIndependentReactionMetabs();
  size_t ode_size = copasiModel->getNumODEMetabs();
  size_t comps_size = copasiModel->getCompartments().size();
  size_t modvals_size = copasiModel->getModelValues().size();
  size_t reacs_size = copasiModel->getReactions().size();

  size_t i, j, num_params, count;
  const CDataVector< CReaction > & reacs = copasiModel->getReactions();
  const CReaction* reac;

  count = 0;

  for (i = 0; i < reacs_size; ++i)
    {

      reac = &reacs[i];
      num_params = reac->getFunctionParameters().size();

      for (j = 0; j < num_params; ++j)
        {
          if (reac->isLocalParameter(j))
            ++count;
        }
    }

  size_t numX = 0;
  size_t numY = 0;
  size_t numXC = 0;
  size_t numYC = 0;
  size_t numPC = 0;
  size_t numP = 0;
  size_t numDX = 0;
  size_t numCT = 0;

  std::ostringstream p_names;  p_names  << "const char* p_names[] = {";
  std::ostringstream x_names;  x_names  << "const char* x_names[] = {";
  std::ostringstream y_names;  y_names  << "const char* y_names[] = {";
  std::ostringstream xc_names; xc_names << "const char* xc_names[] = {";
  std::ostringstream pc_names; pc_names << "const char* pc_names[] = {";
  std::ostringstream yc_names; yc_names << "const char* yc_names[] = {";
  std::ostringstream dx_names; dx_names << "const char* dx_names[] = {";
  std::ostringstream ct_names; ct_names << "const char* ct_names[] = {";

  CKeyFactory* kf = CRootContainer::getKeyFactory();

  std::map< std::string, std::string >::const_iterator it = NameMap.begin();
  std::map< std::string, std::string > reverse_map;

  while (it != NameMap.end())
    {
      const std::string& abbrev = it->second;
      const std::string& key = it->first;

      if (startsWith(abbrev, "p["))
        {
          reverse_map[abbrev] = key;
          ++numP;
        }
      else if (startsWith(abbrev, "x["))
        {
          reverse_map[abbrev] = key;
          ++numX;
        }
      else if (startsWith(abbrev, "y["))
        {
          reverse_map[abbrev] = key;
          ++numY;
        }
      else if (startsWith(abbrev, "dx["))
        {
          reverse_map[abbrev] = key;
          ++numDX;
        }
      else if (startsWith(abbrev, "ct["))
        {
          reverse_map[abbrev] = key;
          ++numCT;
        }
      else if (startsWith(abbrev, "x_c["))
        {
          CDataObject* obj = kf->get(key);

          if (obj != NULL)
            {
              reverse_map[abbrev] = obj->getObjectName();
            }
          else
            {
              reverse_map[abbrev] = key;
            }

          ++numXC;
        }
      else if (startsWith(abbrev, "p_c["))
        {
          CDataObject* obj = kf->get(key);

          if (obj != NULL)
            {
              reverse_map[abbrev] = obj->getObjectName();
            }
          else
            {
              reverse_map[abbrev] = key;
            }

          ++numPC;
        }
      else if (startsWith(abbrev, "y_c["))
        {
          CDataObject* obj = kf->get(key);

          if (obj != NULL)
            {
              reverse_map[abbrev] = obj->getObjectName();
            }
          else
            {
              reverse_map[abbrev] = key;
            }

          ++numYC;
        }

      ++it;
    }

  for (size_t i = 0; i < numP; ++i)
    {
      std::stringstream str; str << "p[" << i << "]";
      printNameForKey(p_names, kf, reverse_map[str.str()]);
    }

  for (size_t i = 0; i < numX; ++i)
    {
      std::stringstream str; str << "x[" << i << "]";
      printNameForKey(x_names, kf, reverse_map[str.str()]);
    }

  for (size_t i = 0; i < numY; ++i)
    {
      std::stringstream str; str << "y[" << i << "]";
      printNameForKey(y_names, kf, reverse_map[str.str()]);
    }

  for (size_t i = 0; i < numDX; ++i)
    {
      std::stringstream str; str << "dx[" << i << "]";
      printNameForKey(dx_names, kf, reverse_map[str.str()]);
    }

  for (size_t i = 0; i < numCT; ++i)
    {
      std::stringstream str; str << "ct[" << i << "]";
      printNameForKey(ct_names, kf, reverse_map[str.str()]);
    }

  for (size_t i = 0; i < numXC; ++i)
    {
      std::stringstream str; str << "x_c[" << i << "]";
      xc_names << "\"" << reverse_map[str.str()] << "\", ";
    }

  for (size_t i = 0; i < numPC; ++i)
    {
      std::stringstream str; str << "p_c[" << i << "]";
      pc_names << "\"" << reverse_map[str.str()] << "\", ";
    }

  for (size_t i = 0; i < numYC; ++i)
    {
      std::stringstream str; str << "y_c[" << i << "]";
      yc_names << "\"" << reverse_map[str.str()] << "\", ";
    }

  os << "#ifdef SIZE_DEFINITIONS" << std::endl;
  os << "#define N_METABS " << metab_size << std::endl;
  os << "#define N_ODE_METABS " << ode_size << std::endl;
  os << "#define N_INDEP_METABS " << indep_size << std::endl;
  os << "#define N_COMPARTMENTS " << comps_size << std::endl;
  os << "#define N_GLOBAL_PARAMS " << modvals_size << std::endl;
  os << "#define N_KIN_PARAMS " << count << std::endl;
  os << "#define N_REACTIONS " << reacs_size << std::endl << std::endl;

  os << "#define N_ARRAY_SIZE_P  " << numP  << "\t// number of parameters" << std::endl;
  os << "#define N_ARRAY_SIZE_X  " << numX  << "\t// number of initials" << std::endl;
  os << "#define N_ARRAY_SIZE_Y  " << numY  << "\t// number of assigned elements" << std::endl;
  os << "#define N_ARRAY_SIZE_XC " << numXC << "\t// number of x concentration" << std::endl;
  os << "#define N_ARRAY_SIZE_PC " << numPC << "\t// number of p concentration" << std::endl;
  os << "#define N_ARRAY_SIZE_YC " << numYC << "\t// number of y concentration" << std::endl;
  os << "#define N_ARRAY_SIZE_DX " << numDX << "\t// number of ODEs " << std::endl;
  os << "#define N_ARRAY_SIZE_CT " << numCT << "\t// number of conserved totals" << std::endl << std::endl;

  os << "#endif // SIZE_DEFINITIONS" << std::endl;
  os << std::endl;

  os << "#ifdef TIME" << std::endl;
  os << "#define T  <set here a user name for the time variable> " << std::endl;
  os << "#endif // TIME" << std::endl;

  os << std::endl;
  os << "#ifdef NAME_ARRAYS" << std::endl;
  os << p_names.str()  << " \"\" };" << std::endl;
  os << x_names.str()  << " \"\" };" << std::endl;
  os << y_names.str()  << " \"\" };" << std::endl;
  os << xc_names.str() << " \"\" };" << std::endl;
  os << pc_names.str() << " \"\" };" << std::endl;
  os << yc_names.str() << " \"\" };" << std::endl;
  os << dx_names.str() << " \"\" };" << std::endl;
  os << ct_names.str() << " \"\" };" << std::endl;
  os << "#endif // NAME_ARRAYS" << std::endl;

  return true;
}

void CODEExporterC::setReservedNames()
{return;}  // TODO

std::string CODEExporterC::translateTimeVariableName()
{return "T";}

std::string CODEExporterC::setExportName(const CModelEntity::Status & status, size_t n[], size_t dependent)
{
  std::ostringstream name;

  switch (status)
    {
      case CModelEntity::Status::FIXED:
        name << "p[" << n[0] << "]";
        n[0] ++;
        break;

      case CModelEntity::Status::REACTIONS:

        if (!dependent)
          {
            name << "x[" << n[1] << "]";
            n[1] ++;
          }
        else
          {
            name << "y[" << n[2] << "]";
            n[2] ++;
          }

        break;

      case CModelEntity::Status::ODE:
        name << "x[" << n[1] << "]";
        n[1] ++;
        break;

      case CModelEntity::Status::ASSIGNMENT:
        name << "y[" << n[2] << "]";
        n[2] ++;
        break;

      default:
        return " ";
        break;
    }

  return name.str();
}

std::string CODEExporterC::setConcentrationName(const CModelEntity::Status & status, size_t n[], size_t dependent)
{
  std::ostringstream name;

  switch (status)
    {
      case CModelEntity::Status::FIXED:
        name << "p_c[" << n[0] << "]";
        n[0] ++;
        break;

      case CModelEntity::Status::REACTIONS:

        if (!dependent)
          {
            name << "x_c[" << n[1] << "]";
            n[1] ++;
          }
        else
          {
            name << "y_c[" << n[2] << "]";
            n[2] ++;
          }

        break;

      case CModelEntity::Status::ODE:
        name << "x_c[" << n[1] << "]";
        n[1] ++;
        break;

      case CModelEntity::Status::ASSIGNMENT:
        name << "y_c[" << n[2] << "]";
        n[2] ++;
        break;

      default:
        return " ";
        break;
    }

  return name.str();
}

/**
 **      This method adapt a Copasi name for C syntax:
 **      Names can not start with a number.
 **      Any other combination of letters and numbers is valid as is the underscore.
 **/
std::string CODEExporterC::translateObjectName(const std::string & realName)
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
            case '{':
            case '}':
            case '(':
            case ')':
            case '[':
            case ']':
              tmpName << "_";
              break;

            default:
              break;
          }
    }

  return testName(tmpName.str());
}
/**
 **      This method tests whether the given C name already assigned,
 **      put the new name (in cappital letters:
 **      all names can be upper or lower case)
 **      in the set of assigned names
 **      or  modify the name
 **/

std::string CODEExporterC::testName(const std::string & name)
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

std::string CODEExporterC::setODEName(const std::string & objName)
{
  return "d" + objName;
}

bool CODEExporterC::preprocess(const CModel* copasiModel)

{
  size_t n[3] = {0, 0, 0};
  size_t n_c[3] = {0, 0, 0};
  size_t i, j;
  size_t dependent;

  setReservedNames();

  NameMap[timeKey] = translateTimeVariableName();

  const CDataVector< CMetab > & metabs = copasiModel->getMetabolitesX();
  size_t metabs_size = metabs.size();

  for (i = 0; i < metabs_size; i++)
    {
      const CMetab * metab = &metabs[i];

      //if (metab->isUsed())
      {
        std::string smname;
        std::string name;
        dependent = metab->isDependent();

        smname = setExportName(metab->getStatus(), n, dependent);
        name = setConcentrationName(metab->getStatus(), n_c, dependent);

        NameMap[metab->getKey()] = name;

        std::ostringstream smKey;
        smKey << "sm_" << metab->getKey();

        NameMap[smKey.str()] = smname;

        if ((metab->getStatus() == CModelEntity::Status::REACTIONS && !metab->isDependent()) || metab->getStatus() == CModelEntity::Status::ODE)
          {
            std::ostringstream odeKey;
            odeKey << "ode_" << metab->getKey();

            NameMap[odeKey.str()] = setODEName(smname);
          }
      }
    }

  size_t comps_size = copasiModel->getCompartments().size();
  const CDataVector< CCompartment > & comps = copasiModel->getCompartments();

  for (i = 0; i < comps_size; i++)
    {
      const CCompartment * comp = &comps[i];

      std::string name;
      dependent = 0;

      name = setExportName(comp->getStatus(), n, dependent);
      NameMap[comp->getKey()] = name;

      if (comp->getStatus() == CModelEntity::Status::ODE)
        {
          std::ostringstream odeKey;
          odeKey << "ode_" << comp->getKey();

          NameMap[odeKey.str()] = setODEName(name);
        }
    }

  size_t modvals_size = copasiModel->getModelValues().size();
  const CDataVector< CModelValue > & modvals = copasiModel->getModelValues();

  for (i = 0; i < modvals_size; i++)
    {
      const CModelValue* modval = &modvals[i];
      std::string name = setExportName(modval->getStatus(), n, 0);
      NameMap[modval->getKey()] = name;

      if (modval->getStatus() == CModelEntity::Status::ODE)
        {
          std::ostringstream odeKey;
          odeKey << "ode_" << modval->getKey();
          NameMap[odeKey.str()] = setODEName(name);
        }
    }

  size_t reacs_size = copasiModel->getReactions().size();

  const CDataVector< CReaction > & reacs = copasiModel->getReactions();

  std::set<std::string> tmpset;

  for (i = 0; i < reacs_size; ++i)
    {
      size_t params_size;

      params_size = reacs[i].getParameters().size();

      for (j = 0; j < params_size; ++j)
        {
          if (!reacs[i].isLocalParameter(reacs[i].getParameters().getParameter(j)->getObjectName()))
            continue;

          std::ostringstream name;

          name << "p[" << n[0] << "]";
          n[0] ++;

          NameMap[reacs[i].getParameters().getParameter(j)->getKey()] = name.str();
        }

      const CFunction* func = reacs[i].getFunction();

      std::string name = func->getObjectName();

      if (func->getRoot())
        setExportNameOfFunction(func->getRoot(), tmpset);

      if (func->getType() != CEvaluationTree::MassAction)
        if (tmpset.find(name) == tmpset.end())
          {
            NameMap[func->getKey()] = translateObjectName(name);
            tmpset.insert(name);
          }
    }

  return true;
}

void CODEExporterC::setExportNameOfFunction(const CEvaluationNode* pNode, std::set<std::string> & tmpset)
{
  if (pNode)
    {
      CFunctionDB* pFunctionDB = CRootContainer::getFunctionList();
      CCopasiTree<CEvaluationNode>::const_iterator treeIt = pNode;

      while (treeIt != NULL)
        {
          if (treeIt->mainType() == CEvaluationNode::MainType::CALL)
            {
              const CFunction* ifunc;
              ifunc = static_cast<CFunction*>(pFunctionDB->findFunction((*treeIt).getData()));

              setExportNameOfFunction(ifunc->getRoot(), tmpset);

              if (ifunc->getType() != CEvaluationTree::MassAction)
                if (tmpset.find(ifunc->getObjectName()) == tmpset.end())
                  {
                    NameMap[ifunc->getKey()] = translateObjectName(ifunc->getObjectName());
                    tmpset.insert(ifunc->getObjectName());
                  }
            }

          ++treeIt;
        }
    }
}

bool CODEExporterC::exportSingleObject(std::ostringstream & which, const std::string & name, const std::string & expression, const std::string & comments)
{
  // don't write out invalid expressions
  if (expression.empty() || expression == " ")
    return true;

  which << name << " = " << expression << ";";

  // only write comments if we have them
  if (!comments.empty() && comments != " ")
    which << '\t' << "//" << comments;

  which << std::endl;

  return true;
}

bool CODEExporterC::exportSingleMetabolite(const CMetab* metab, std::string & expression, std::string & comments)
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
      case CModelEntity::Status::ODE:
      {
        if (metab->isDependent())
          {
            if (!exportSingleObject(assignment, name, expression, comments))
              return false;
          }
        else
          {
            if (!exportSingleObject(initial, name, expression, comments))
              return false;
          }

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

bool CODEExporterC::exportSingleCompartment(const CCompartment* comp, std::string & expression, std::string & comments)
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

std::string CODEExporterC::exportNumber(double number)
{
  if (util_isNaN(number))
    return "NaN";

  if (util_isInf(number))
    return "INFINITY";

  std::stringstream str; str << number;
  return str.str();
}

bool CODEExporterC::exportSingleModVal(const CModelValue* modval, std::string & expression, std::string & comments)
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

bool CODEExporterC::exportSingleModelEntity(const CModelEntity* tmp, std::string & expression, std::string & comments)
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
        // prevent assignment from being written multiple times ...
        if (Frequancy[name] == 1)
          break;

        if (!exportSingleObject(assignment, name, expression, comments))
          return false;

        Frequancy[name] = 1;
        break;
      }

      default:
        return false;
        break;
    }

  return true;
}

bool CODEExporterC::exportSingleParameter(const CCopasiParameter* param, std::string & expression, std::string & comments)
{
  if (!exportSingleObject(fixed, NameMap[param->getKey()], expression, comments)) return false;

  return true;
}

bool CODEExporterC::exportKineticFunction(const CReaction* /* reac */)
{return true;}

bool CODEExporterC::exportKineticFunctionGroup(const CModel* copasiModel)
{
  const CDataVector< CReaction > & reacs = copasiModel->getReactions();
  size_t size = reacs.size();
  const CReaction* reac;

  size_t i;

  for (i = 0; i < size; ++i)
    {
      reac = &reacs[i];
      const CFunction* func = reac->getFunction();

      if (func->getRoot())
        findFunctionsCalls(func->getRoot());

      if (func->getType() != CEvaluationTree::MassAction)
        {
          if (!CODEExporter::exportSingleFunction(func)) return false;
        }
    }

  return true;
}

bool CODEExporterC::exportSingleFunction(const CFunction *func, std::set<std::string>& isExported)
{
  CFunctionDB* pFunctionDB = CRootContainer::getFunctionList();

  CFunction* tmpfunc = NULL;
  tmpfunc = new CFunction(*func, NO_PARENT);

  if (func->getType() != CEvaluationTree::MassAction)
    {

      CCopasiTree< CEvaluationNode>::iterator treeIt = tmpfunc->getRoot();
      CCopasiTree< CEvaluationNode>::iterator newIt = treeIt;

      size_t j, varbs_size = tmpfunc->getVariables().size();
      std::map< std::string, std::string > parameterNameMap;
      std::set<std::string> parameterNameSet;

      std::map< CFunctionParameter::Role, std::string > constName;
      std::map< CFunctionParameter::Role, size_t > tmpIndex;

      constName[CFunctionParameter::Role::SUBSTRATE] = "sub_"; tmpIndex[CFunctionParameter::Role::SUBSTRATE] = 0;
      constName[CFunctionParameter::Role::PRODUCT] = "prod_"; tmpIndex[CFunctionParameter::Role::PRODUCT] = 0;
      constName[CFunctionParameter::Role::PARAMETER] = "param_"; tmpIndex[CFunctionParameter::Role::PARAMETER] = 0;
      constName[CFunctionParameter::Role::MODIFIER] = "modif_"; tmpIndex[CFunctionParameter::Role::MODIFIER] = 0;
      constName[CFunctionParameter::Role::VOLUME] = "volume_"; tmpIndex[CFunctionParameter::Role::VOLUME] = 0;
      constName[CFunctionParameter::Role::VARIABLE] = "varb_"; tmpIndex[CFunctionParameter::Role::VARIABLE] = 0;
      constName[CFunctionParameter::Role::TIME] = "time_"; tmpIndex[CFunctionParameter::Role::VARIABLE] = 0;

      for (j = 0; j < varbs_size; ++j)
        {
          if (parameterNameSet.find(tmpfunc->getVariables()[j]->getObjectName()) == parameterNameSet.end())
            {
              std::ostringstream tmpName;
              CFunctionParameter::Role role = tmpfunc->getVariables()[j]->getUsage();

              tmpName << constName[role] << tmpIndex[role];
              parameterNameMap[ tmpfunc->getVariables()[j]->getObjectName()] = tmpName.str();
              parameterNameSet.insert(tmpfunc->getVariables()[j]->getObjectName());
              tmpIndex[role]++;
            }
        }

      CODEExporter::modifyTreeForMassAction(tmpfunc);

      while (newIt != NULL)
        {
          if (newIt->mainType() == CEvaluationNode::MainType::VARIABLE)
            {
              newIt->setData(parameterNameMap[ tmpfunc->getVariables()[newIt->getData()]->getObjectName()]);
            }

          if (newIt->mainType() == CEvaluationNode::MainType::CALL)
            {
              const CFunction* callfunc;
              callfunc = static_cast<CFunction*>(pFunctionDB->findFunction((*newIt).getData()));

              if (callfunc->getType() != CEvaluationTree::MassAction)
                newIt->setData(NameMap[callfunc->getKey()]);
            }

          ++newIt;
        }

      std::string name = func->getObjectName();

      if (isExported.find(name) == isExported.end())
        {
          size_t j, varbs_size = tmpfunc->getVariables().size();

          std::string mappedName = NameMap[func->getKey()];

          if (mappedName.empty())
            {
              NameMap[func->getKey()]  = translateObjectName(name);
              mappedName = NameMap[func->getKey()];
            }

          functions << "double " << mappedName << "(";
          headers << "double " << mappedName << "(";

          for (j = 0; j < varbs_size; ++j)
            {
              functions << "double " << parameterNameMap[ tmpfunc->getVariables()[j]->getObjectName().c_str()];

              if (j != varbs_size - 1) functions << ", ";

              headers << "double " << parameterNameMap[ tmpfunc->getVariables()[j]->getObjectName().c_str()];

              if (j != varbs_size - 1) headers << ", ";
            }

          functions << ") ";
          functions << '\t' << "//" << name << std::endl;
          functions << "{return  " << tmpfunc->getRoot()->buildCCodeString().c_str() << ";} " << std::endl;

          headers << "); " << std::endl;

          isExported.insert(name);
        }
    }

  return true;
}

std::string CODEExporterC::KineticFunction2ODEmember(const CReaction *reac)
{
  std::ostringstream equation;

  if (reac->getFunction()->getType() != CEvaluationTree::MassAction)
    {
      const CFunctionParameters & params = reac->getFunctionParameters();
      size_t k, params_size = params.size();
      const std::vector< std::vector< const CDataObject * > > & ObjectMap = reac->getParameterObjects();
      std::string name;
      equation << NameMap[reac->getFunction()->getKey()] << "(";

      for (k = 0; k < params_size; ++k)
        {

          CFunctionParameter::Role role = params[k]->getUsage();

          const CDataObject * obj = ObjectMap[k][0];

          if (role == CFunctionParameter::Role::TIME)
            {
              name = "T";
            }
          else
            {
              if (obj)
                name = NameMap[obj->getKey()];
              else
                name = "unknown";
            }

          if (name.empty())
            {
              std::string message = "Could not export C code, since one of the arguments could not be resolved. Please consider filing a bug with the COPASI tracker: http://tracker..copasi.org";
              CCopasiMessage(CCopasiMessage::EXCEPTION, message.c_str());
            }

          equation << name;

          if (k != params_size - 1)
            equation << ", ";
        }

      equation << ")";
    }
  else
    {
      const CDataVector<CChemEqElement> & substrs = reac->getChemEq().getSubstrates();
      const CDataVector<CChemEqElement> & prods = reac->getChemEq().getProducts();
      const std::vector< std::vector< const CDataObject * > > & ObjectMap = reac->getParameterObjects();
      const CDataObject * obj;

      size_t substrs_size = substrs.size(), prods_size = prods.size();
      size_t k, m, mult;

      const CChemEqElement* substr;
      const CChemEqElement* prod;

      const CMassAction & cMassAction = *static_cast<const CMassAction*>(reac->getFunction());

      equation << "(";

      obj = ObjectMap[0][0];

      if (!(reac->isLocalParameter(0)))
        {
          const CModelValue* modval;
          modval = dynamic_cast< const CModelValue * >(obj);

          equation << NameMap[modval->getKey()];
        }
      else
        {
          const CCopasiParameter* param;
          param = dynamic_cast< const CCopasiParameter * >(obj);

          equation << NameMap[param->getKey()];
        }

      for (k = 0; k < substrs_size; ++k)
        {
          substr = &substrs[k];
          mult = (size_t) substr->getMultiplicity();

          assert(substr->getMetabolite());
          equation << " * " << NameMap[substr->getMetabolite()->getKey()];

          if (mult > 1)
            for (m = 1; m < mult; ++m)
              equation << " * " << NameMap[substr->getMetabolite()->getKey()];
        }

      if (cMassAction.isReversible() == TriTrue)
        {
          equation << " - ";

          obj = ObjectMap[2][0];

          if (!(reac->isLocalParameter(2)))
            {
              const CModelValue* modval;
              modval = dynamic_cast< const CModelValue * >(obj);

              equation << NameMap[modval->getKey()];
            }
          else
            {
              const CCopasiParameter* param;
              param = dynamic_cast< const CCopasiParameter * >(obj);

              equation << NameMap[param->getKey()];
            }

          for (k = 0; k < prods_size; ++k)
            {
              prod = &prods[k];
              mult = (size_t) prod->getMultiplicity();

              assert(prod->getMetabolite());
              equation << " * " << NameMap[prod->getMetabolite()->getKey()];

              if (mult > 1)
                for (m = 1; m < mult; ++m)
                  equation << " * " << NameMap[prod->getMetabolite()->getKey()];
            }
        }

      equation << ") ";
    }

  return equation.str();
}

bool CODEExporterC::exportSingleODE(const CModelEntity* mentity, std::string & equation, std::string & comments)
{
  std::ostringstream odeKey;
  odeKey << "ode_" << mentity->getKey();

  if (!exportSingleObject(ode, NameMap[odeKey.str()], equation, comments)) return false;

  return true;
}

std::string CODEExporterC::exportTitleString(const size_t tmp)
{
  switch (tmp)
    {
      case INITIAL:
        return "#ifdef INITIAL";

      case FIXED:
        return "#ifdef FIXED";

      case ASSIGNMENT:
        return "#ifdef ASSIGNMENT";

      case HEADERS:
        return "#ifdef FUNCTIONS_HEADERS";

      case FUNCTIONS:
        return "#ifdef FUNCTIONS";

      case ODEs:
        return "#ifdef ODEs";

      default:
        return " ";
    }
}

std::string CODEExporterC::getDisplayExpressionString(CExpression * tmp)
{
  std::string str1;

  str1 = tmp->getRoot()->buildCCodeString().c_str();

  return str1;
}

std::string CODEExporterC::exportClosingString(const size_t tmp)
{
  switch (tmp)
    {
      case INITIAL:
        return "#endif /* INITIAL */\n";

      case FIXED:
        return "#endif /* FIXED */\n";

      case ASSIGNMENT:
        return "#endif /* ASSIGNMENT */\n";

      case HEADERS:
        return "#endif /* FUNCTIONS_HEADERS */\n";

      case FUNCTIONS:
        return "#endif /* FUNCTIONS */\n";

      case ODEs:
        return "#endif /* ODEs */\n";

      default:
        return " ";
    }
}
