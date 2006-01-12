/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/Attic/MMASCIIExporter.cpp,v $
   $Revision: 1.14.2.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/12 15:07:23 $
   End CVS Header */

#include <math.h>
#include "copasi.h"

#include "CopasiDataModel/CCopasiDataModel.h"

#include "MMASCIIExporter.h"

#include "model/CModel.h"
#include "model/CMetab.h"
#include "utilities/CCopasiVector.h"
#include "model/CReaction.h"
#include "model/CMoiety.h"
#include "model/CChemEqElement.h"
#include "function/CFunction.h"
#include "function/CFunctionDB.h"
#include "report/CKeyFactory.h"
#include "function/CEvaluationTree.h"
#include "function/CEvaluationNode.h"
#include "function/CEvaluationNodeObject.h"
#include "function/CEvaluationNodeOperator.h"
#include "utilities/CCopasiTree.h"

#include <iostream>
#include <fstream>

/**
 ** Constructor for the exporter.
 */
MMASCIIExporter::MMASCIIExporter()
{}

/**
 ** Destructor for the exporter.
 */
MMASCIIExporter::~MMASCIIExporter()
{}
/**
 **       This method tests if a string only consists of whitespace characters
 **/
bool MMASCIIExporter::isEmptyString(std::string & str)
{
  return (str.find_first_not_of(" \n\t\r") == std::string::npos);
}
/**
 **        This method finds the metab by the name, returns an index
 **/
C_INT32 MMASCIIExporter::findMetabXByName(const CModel* copasiModel, const std::string & Target)
{
  std::string name;
  const CCopasiVector< CMetab > & metabs = copasiModel->getMetabolitesX();
  unsigned C_INT32 id, metabs_size = metabs.size();

  for (id = 0; id < metabs_size; id++)
    {
      name = metabs[id]->getObjectName();
      if (name == Target)
        return id;
    }
  return - 1;
}
/**
 **        This method finds the compartement by the name, returns an index
 **/
C_INT32 MMASCIIExporter::findCompByName(const CModel* copasiModel, const std::string & Target)
{
  std::string name;

  const CCopasiVector< CCompartment > & comps = copasiModel->getCompartments();
  unsigned C_INT32 comps_size = comps.size();
  unsigned C_INT32 id;

  for (id = 0; id < comps_size; id++)
    {
      name = comps[id]->getObjectName();
      if (name == Target)
        return id;
    }
  return - 1;
}
/**
 **        This method finds the global parameter by the name, returns an index   
 **/
C_INT32 MMASCIIExporter::findGlobalParamByName(const CModel* copasiModel, const std::string & Target)
{
  std::string name;
  const CCopasiVector< CModelValue > & modvals = copasiModel->getModelValues();
  unsigned C_INT32 modvals_size = modvals.size();
  unsigned C_INT32 id;

  for (id = 0; id < modvals_size; id++)
    {
      name = modvals[id]->getObjectName();
      if (name == Target)
        return id;
    }
  return - 1;
}
/**
 **        This method finds the local reactions parameter by the name, returns an index  
 **/
C_INT32 MMASCIIExporter::findKinParamByName(const CReaction* reac, const std::string & Target)
{
  std::string tmpname;
  unsigned C_INT32 tmp_k, tmp_size;

  tmp_size = reac->getParameters().size();

  for (tmp_k = 0; tmp_k < tmp_size; tmp_k++)
    {
      tmpname = reac->getParameters().getParameter(tmp_k)->getObjectName();
      if (tmpname == Target)
        return tmp_k;
    }
  return - 1;
}
/**
 **         This method assembles an expression sub tree for some internal call of Mass Action. 
 **         The sub tree has to be included in the tree of corresponding root kinetic function in order to    
 **         export this function in the C format whithout the user defined internall Mass Action calls  
 **/
void MMASCIIExporter::assembleSubTreeForMassAction(CEvaluationNode* newNode, CEvaluationNode* child1, CEvaluationNode* child2)
{
  CEvaluationNode* newparent = newNode;
  CEvaluationNode* newchild1 = child1->copyBranch();
  newparent->addChild(newchild1, NULL);
  CEvaluationNode* newchild2;

  if (CEvaluationNode::type(child2->getType()) == CEvaluationNode::VARIABLE)
    {
      newchild2 = CEvaluationNode::create((CEvaluationNode::Type)(CEvaluationNode::OPERATOR | CEvaluationNodeOperator::MULTIPLY), "*");
      newparent->addChild(newchild2, newchild1);
      newparent = newchild2;
      newchild1 = child2->copyBranch();
      newparent->addChild(newchild1, NULL);
      newchild2 = child2->copyBranch();
      newparent->addChild(newchild2, newchild1);
    }

  if (0) // *************** TODO: the current Copasi version does not support the case bellow, the following part is not tested
    if (CEvaluationNode::type(child2->getType()) == CEvaluationNode::VECTOR)
      {
        const std::vector<CEvaluationNode *> & vector = dynamic_cast< CEvaluationNodeVector *> (child2) ->getVector();
        std::vector<CEvaluationNode *>::const_iterator it = vector.begin();
        std::vector<CEvaluationNode *>::const_iterator end = vector.end();

        unsigned C_INT32 i = 0;

        while (it != end)
          {
            newchild2 = CEvaluationNode::create((CEvaluationNode::Type)(CEvaluationNode::OPERATOR | CEvaluationNodeOperator::MULTIPLY), "*");
            newparent->addChild(newchild2, newchild1);

            newparent = newchild2;
            newchild1 = dynamic_cast<CEvaluationNode*>(vector[i]);
            newparent->addChild(newchild1, NULL);
            it++;
            i++;
          }

        if (it == end)
          {
            newchild2 = dynamic_cast<CEvaluationNode*>(vector[i]);
            newparent->addChild(newchild2, newchild1);
          }
      } // END of this TODO. ****************************************************************************************************
}
/**
 **         This method exports the functions in C format     
 **/
void MMASCIIExporter::functionCoutput(const CFunction *pFunc, std::set<std::string>& exportedFunctionSet, std::map< std::string, std::string > &functionNameMap, std::set<std::string> &functionNameSet, unsigned C_INT32 &findex, std::ostringstream & outFunction, std::ostringstream & outFunctionHeader)
{
  CFunctionDB* pFunctionDB = CCopasiDataModel::Global->getFunctionList();

  CFunction* tmpFunc = NULL;
  tmpFunc = new CFunction(*pFunc);

  if (pFunc->getType() != CEvaluationTree::MassAction)
    {
      std::ostringstream tmpName;

      if (functionNameSet.find(pFunc->getObjectName()) == functionNameSet.end())
        {
          tmpName << "function_" << findex << "_";
          functionNameMap[pFunc->getObjectName()] = tmpName.str();
          functionNameSet.insert(pFunc->getObjectName());
          findex++;
        }

      CCopasiTree< CEvaluationNode>::iterator treeIt = tmpFunc->getRoot();
      CCopasiTree< CEvaluationNode>::iterator newIt = treeIt;

      unsigned C_INT32 j, varbs_size = tmpFunc->getVariables().size();
      std::map< std::string, std::string > parameterNameMap;
      std::set<std::string> parameterNameSet;

      std::map< CFunctionParameter::Role, std::string > constName;
      std::map< CFunctionParameter::Role, unsigned C_INT32 > tmpIndex;

      constName[CFunctionParameter::SUBSTRATE] = "sub_"; tmpIndex[CFunctionParameter::SUBSTRATE] = 0;
      constName[CFunctionParameter::PRODUCT] = "prod_"; tmpIndex[CFunctionParameter::PRODUCT] = 0;
      constName[CFunctionParameter::PARAMETER] = "param_"; tmpIndex[CFunctionParameter::PARAMETER] = 0;
      constName[CFunctionParameter::MODIFIER] = "modif_"; tmpIndex[CFunctionParameter::MODIFIER] = 0;
      constName[CFunctionParameter::VOLUME] = "volume_"; tmpIndex[CFunctionParameter::VOLUME] = 0;
      constName[CFunctionParameter::VARIABLE] = "varb_"; tmpIndex[CFunctionParameter::VARIABLE] = 0;

      for (j = 0; j < varbs_size; ++j)
        {
          if (parameterNameSet.find(tmpFunc->getVariables()[j]->getObjectName()) == parameterNameSet.end())
            {
              std::ostringstream tmpName;
              CFunctionParameter::Role usage = tmpFunc->getVariables()[j]->getUsage();

              tmpName << constName[usage] << tmpIndex[usage];
              parameterNameMap[ tmpFunc->getVariables()[j]->getObjectName() ] = tmpName.str();
              parameterNameSet.insert(tmpFunc->getVariables()[j]->getObjectName());
              tmpIndex[usage]++;
            }
        }

      /********** The part bellow take care of the possible internal Mass Action calls *********/

      /* if (tmpFunc->getRoot())
        tmpFunc->getRoot()->printRecursively(std::cout); */

      while (treeIt != NULL)
        {
          if (CEvaluationNode::type(treeIt->getType()) == CEvaluationNode::CALL)
            {
              const CFunction* callFunc;
              callFunc = static_cast<CFunction*> (pFunctionDB->findFunction((*treeIt).getData()));

              if (callFunc->getType() == CEvaluationTree::MassAction)
                {
                  CEvaluationNode* parent = dynamic_cast<CEvaluationNode*>(treeIt->getParent());
                  CEvaluationNode* child1 = dynamic_cast<CEvaluationNode*>(treeIt->getChild());
                  CEvaluationNode* child2 = dynamic_cast<CEvaluationNode*>((treeIt->getChild())->getSibling());

                  CEvaluationNode* newNode;
                  CEvaluationNode* newNode1 = CEvaluationNode::create((CEvaluationNode::Type)(CEvaluationNode::OPERATOR | CEvaluationNodeOperator::MULTIPLY), "*");

                  assembleSubTreeForMassAction(newNode1, child1, child2);

                  if (callFunc->getObjectName() == "Mass action (irreversible)") newNode = newNode1;

                  if (callFunc->getObjectName() == "Mass action (reversible)")
                    {
                      newNode = CEvaluationNode::create((CEvaluationNode::Type)(CEvaluationNode::OPERATOR | CEvaluationNodeOperator::MINUS), "-");
                      newNode->addChild(newNode1, NULL);

                      CEvaluationNode* newNode2 = CEvaluationNode::create((CEvaluationNode::Type)(CEvaluationNode::OPERATOR | CEvaluationNodeOperator::MULTIPLY), "*");
                      CEvaluationNode* child3 = dynamic_cast<CEvaluationNode*>((child2)->getSibling());
                      CEvaluationNode* child4 = dynamic_cast<CEvaluationNode*>((child3)->getSibling());

                      assembleSubTreeForMassAction(newNode2, child3, child4);

                      newNode->addChild(newNode2, newNode1);
                    }

                  if (parent)
                    {
                      parent->addChild(newNode, &(*treeIt));
                      parent->removeChild(&(*treeIt));
                    }

                  delete &(*treeIt);
                  treeIt = newNode;
                }
            }

          ++treeIt;
        }

      /* if (tmpFunc->getRoot())
        tmpFunc->getRoot()->printRecursively(std::cout); */

      /***************************************************************************/

      while (newIt != NULL)
        {
          if (CEvaluationNode::type(newIt->getType()) == CEvaluationNode::VARIABLE)
            {
              newIt->setData(parameterNameMap[ tmpFunc->getVariables()[newIt->getData()]->getObjectName() ]);
            }

          if (CEvaluationNode::type(newIt->getType()) == CEvaluationNode::CALL)
            {
              const CFunction* callFunc;
              callFunc = static_cast<CFunction*> (pFunctionDB->findFunction((*newIt).getData()));
              if (callFunc->getType() != CEvaluationTree::MassAction)
                newIt->setData(functionNameMap[callFunc->getObjectName()]);
            }

          ++newIt;
        }

      /*
      if (tmpFunc->getRoot())
      tmpFunc->getRoot()->printRecursively(std::cout);
      */

      /* tmpFunc->updateTree(); */

      /*
      if (tmpFunc->getRoot())
        tmpFunc->getRoot()->printRecursively(std::cout); */

      std::string name = tmpFunc->getObjectName();

      if (exportedFunctionSet.find(name) == exportedFunctionSet.end())
        {
          unsigned C_INT32 j, varbs_size = tmpFunc->getVariables().size();

          outFunction << std::endl;
          outFunction << "double " << functionNameMap[name] << "(";

          outFunctionHeader << std::endl;
          outFunctionHeader << "double " << functionNameMap[name] << "(";

          for (j = 0; j < varbs_size; ++j)
            {
              outFunction << "double " << parameterNameMap[ tmpFunc->getVariables()[j]->getObjectName().c_str() ];
              if (j != varbs_size - 1) outFunction << ", ";

              outFunctionHeader << "double " << parameterNameMap[ tmpFunc->getVariables()[j]->getObjectName().c_str() ];
              if (j != varbs_size - 1) outFunctionHeader << ", ";
            }

          outFunction << ") ";
          outFunction << '\t' << "//" << name << std::endl;
          //outFunction << "{return  " << tmpFunc->getInfix().c_str() << "; } " << std::endl;
          outFunction << "{return  " << tmpFunc->getRoot()->getDisplay_C_String(tmpFunc).c_str() << "; } " << std::endl;

          outFunctionHeader << "); ";

          exportedFunctionSet.insert(name);
        }
    }
}

/**
 **         This method finds internal functions calls 
 **/
void MMASCIIExporter::findInternalFunctionsCalls(const CEvaluationNode* pNode, std::set<std::string>& exportedFunctionSet, std::map< std::string, std::string > &functionNameMap, std::set<std::string> &functionNameSet, unsigned C_INT32 &findex, std::ostringstream & outFunction, std::ostringstream & outFunctionHeader)
{
  if (pNode)
    {
      CFunctionDB* pFunctionDB = CCopasiDataModel::Global->getFunctionList();
      CCopasiTree<CEvaluationNode>::const_iterator treeIt = pNode;

      while (treeIt != NULL)
        {
          if (CEvaluationNode::type(treeIt->getType()) == CEvaluationNode::CALL)
            {
              const CFunction* iFunc;
              iFunc = static_cast<CFunction*> (pFunctionDB->findFunction((*treeIt).getData()));

              findInternalFunctionsCalls(iFunc->getRoot(), exportedFunctionSet, functionNameMap, functionNameSet, findex, outFunction, outFunctionHeader);

              if (iFunc->getType() != CEvaluationTree::MassAction)
                functionCoutput(iFunc, exportedFunctionSet, functionNameMap, functionNameSet, findex, outFunction, outFunctionHeader);
            }

          ++treeIt;
        }
    }
}

/**
 ** This method takes some of the copasi CModel objects 
 ** and writes them in the ASCII format in an output file.    
 ** The filename is given as the second
 ** argument to the function. The function return "true" on success and
 ** "false" on failure.
 */

bool MMASCIIExporter::exportMathModel(const CModel* copasiModel, std::string mmasciiFilename, bool overwriteFile)
{
  /* check if the file already exisits.
          If yes, write if overwrite is true, 
          else create an appropriate  CCopasiMessage. */

  std::ifstream testInfile(mmasciiFilename.c_str(), std::ios::in);

  if (testInfile && !overwriteFile)
    {
      // create a CCopasiMessage with the appropriate error
      CCopasiMessage(CCopasiMessage::ERROR, MCDirEntry + 1, mmasciiFilename.c_str());
      return false;
    }

  std::ofstream outFile(mmasciiFilename.c_str(), std::ios::out);

  outFile << "#ifdef SIZE_DEFINITIONS" << std::endl;
  unsigned C_INT32 metab_size = copasiModel->getMetabolitesX().size();
  unsigned C_INT32 indep_size = copasiModel->getNumIndependentMetabs();
  unsigned C_INT32 comps_size = copasiModel->getCompartments().size();
  unsigned C_INT32 modvals_size = copasiModel->getModelValues().size();
  unsigned C_INT32 reacs_size = copasiModel->getReactions().size();

  unsigned C_INT32 i, count;
  const CCopasiVector< CReaction > & reacs = copasiModel->getReactions();
  CReaction* reac;

  count = 0;
  for (i = 0; i < reacs_size; ++i)
    {
      reac = reacs[i];
      count = count + reac->getParameters().size();
    }

  outFile << "#define N_METABS " << metab_size << std::endl;
  outFile << "#define N_INDEP_METABS " << indep_size << std::endl;
  outFile << "#define N_COMPARTMENTS " << comps_size << std::endl;
  outFile << "#define N_GLOBAL_PARAMS " << modvals_size << std::endl;
  outFile << "#define N_KIN_PARAMS " << count << std::endl;
  outFile << "#define N_REACTIONS " << reacs_size << std::endl;

  outFile << "#endif // SIZE_DEFINITIONS" << std::endl;
  outFile << std::endl;

  outFile << "#ifdef METABOLITES" << std::endl;

  CMetab* metab;

  for (i = 0; i < metab_size; i++)
    {
      metab = copasiModel->getMetabolitesX()[i];

      outFile << "y[" << i << "]="
      << metab->getInitialConcentration() << ";"
      << '\t' << "//" << metab->getObjectName().c_str() << ","
      << '\t' << CModelEntity::StatusName[metab->getStatus()]
      << std::endl;
    }
  outFile << "#endif // METABOLITES" << std::endl;
  outFile << std::endl;

  outFile << "#ifdef INDEP_METABOLITES" << std::endl;

  for (i = 0; i < indep_size; i++)
    {
      metab = copasiModel->getMetabolitesX()[i];

      outFile << "x[" << i << "]="
      << metab->getInitialConcentration() << ";"
      << '\t' << "//" << metab->getObjectName().c_str() << ","
      << '\t' << CModelEntity::StatusName[metab->getStatus()]
      << std::endl;
    }
  outFile << "#endif // INDEP_METABOLITES" << std::endl;
  outFile << std::endl;

  outFile << "#ifdef MOIETY" << std::endl;

  const CModel::CLinkMatrixView & L = copasiModel->getL();

  unsigned C_INT32 indep_dep_size;
  unsigned C_INT32 j;
  C_FLOAT64 Value;

  indep_dep_size = indep_size + copasiModel->getNumDependentMetabs();

  for (i = indep_size; i < indep_dep_size; i++)
    {
      std::ostringstream Description;
      std::ostringstream comment;

      metab = copasiModel->getMetabolitesX()[i];
      if (metab->getStatus() == CModelEntity::UNUSED) continue;
      if (metab->getStatus() == CModelEntity::FIXED) continue;

      Value = metab->getInitialConcentration();
      comment << metab->getObjectName();

      for (j = 0; j < indep_size; j++)
        if (L(i, j) != 0.0)
          {
            if (L(i, j) < 0.0)
              {
                Description << " - ";
                comment << " + ";
              }
            else
              {
                Description << " + ";
                comment << " - ";
              }
            if (fabs(L(i, j)) != 1.0)
              {
                Description << fabs(L(i, j)) << " * " << "y[" << j << "]";
                comment << fabs(L(i, j)) << " * " << copasiModel->getMetabolitesX()[j]->getObjectName();
              }
            else
              {
                Description << "y[" << j << "]";
                comment << copasiModel->getMetabolitesX()[j]->getObjectName();
              }

            Value -= L(i, j) * copasiModel->getMetabolitesX()[j]->getInitialConcentration();
          }

      outFile << "y[" << i << "] = " << Value << Description.str() << ";" << '\t'
      << "// " << comment.str() << " = const" << std::endl;
    }

  outFile << "#endif // MOIETY" << std::endl;
  outFile << std::endl;

  outFile << "#ifdef COMPARTMENTS" << std::endl;

  const CCopasiVector< CCompartment > & comps = copasiModel->getCompartments();

  for (i = 0; i < comps_size; i++)
    {
      outFile << "c[" << i << "]="
      << comps[i]->getVolume() << ";"
      << '\t' << "//" << comps[i]->getObjectName().c_str()
      << std::endl;
    }

  outFile << "#endif // COMPARTMENTS" << std::endl;
  outFile << std::endl;

  outFile << "#ifdef GLOBAL_PARAMETERS" << std::endl;

  const CCopasiVector< CModelValue > & modvals = copasiModel->getModelValues();

  for (i = 0; i < modvals_size; i++)
    {
      outFile << "gk[" << i << "]="
      << modvals[i]->getValue() << ";"
      << '\t' << "//" << modvals[i]->getObjectName().c_str()
      << std::endl;
    }

  outFile << "#endif // GLOBAL_PARAMETERS" << std::endl;
  outFile << std::endl;

  outFile << "#ifdef KINETIC_PARAMETERS" << std::endl;

  count = 0;

  for (i = 0; i < reacs_size; ++i)
    {
      unsigned C_INT32 params_size;
      reac = reacs[i];

      outFile << "// in reaction:" << reac->getObjectName().c_str() << std::endl;

      params_size = reac->getParameters().size();

      for (j = 0; j < params_size; ++j)
        {
          outFile << "k[" << count++ << "]="
          << *reac->getParameters().getParameter(j)->getValue().pDOUBLE << ";"
          << '\t' << "//" << reac->getParameters().getParameter(j)->getObjectName().c_str()
          << std::endl;
        }
    }

  outFile << "#endif // KINETIC_PARAMETERS" << std::endl;
  outFile << std::endl;

  std::map< std::string, std::string > functionNameMap;
  std::set<std::string> functionNameSet;
  std::set<std::string> exportedFunctionSet;
  unsigned C_INT32 findex = 0;
  std::ostringstream outFunction;
  std::ostringstream outFunctionHeader;

  for (i = 0; i < reacs_size; ++i)
    {
      reac = reacs[i];

      const CFunction* pFunc = &(reac->getFunction());

      if (pFunc->getRoot())
        findInternalFunctionsCalls(pFunc->getRoot(), exportedFunctionSet, functionNameMap, functionNameSet, findex, outFunction, outFunctionHeader);

      if (pFunc->getType() != CEvaluationTree::MassAction)
        functionCoutput(pFunc, exportedFunctionSet, functionNameMap, functionNameSet, findex, outFunction, outFunctionHeader);
    }

  outFile << "#ifdef KINETIC_FUNCTIONS_HEADER";
  outFile << outFunctionHeader.str();
  outFile << std::endl;
  outFile << "#endif // KINETIC_FUNCTIONS_HEADER" << std::endl;
  outFile << std::endl;

  outFile << "#ifdef KINETIC_FUNCTIONS";
  outFile << outFunction.str();
  outFile << std::endl;
  outFile << "#endif // KINETIC_FUNCTIONS" << std::endl;
  outFile << std::endl;

  outFile << "#ifdef DIFFERENTIAL_EQUATIONS" << std::endl;

  const CMatrix< C_FLOAT64 > & redStoi = copasiModel->getRedStoi();
  const CCopasiVector< CMetab > & metabs = copasiModel->getMetabolitesX();

  for (i = 0; i < indep_size; ++i)
    {
      unsigned C_INT32 counter = 0;

      std::ostringstream equation;
      std::string tmpstr;

      unsigned C_INT32 compartment_index;
      const CCompartment* compartment = metabs[i]->getCompartment();

      compartment_index = findCompByName(copasiModel, compartment->getObjectName());

      for (j = 0; j < reacs_size; ++j)
        {
          unsigned C_INT32 k;
          tmpstr = equation.str();

          reac = reacs[j];

          if (fabs(redStoi[i][j]) > 0.0)
            {
              if (redStoi[i][j] < 0.0)
                equation << " - ";
              else
                if (!(isEmptyString(tmpstr))) equation << " + ";

              if (fabs(redStoi[i][j]) != 1.0) equation << fabs(redStoi[i][j]) << " * ";

              if (reac->getFunction().getType() != CEvaluationTree::MassAction)
                {
                  const CFunctionParameters & params = reac->getFunctionParameters();
                  unsigned C_INT32 params_size = params.size();
                  const std::vector<std::vector<std::string> > & keyMap = reac->getParameterMappings();

                  equation
                  << functionNameMap[reac->getFunction().getObjectName()]
                  << "(";

                  for (k = 0; k < params_size; ++k)
                    {
                      C_INT32 index;
                      CFunctionParameter::Role usage = params[k]->getUsage();
                      std::string name;

                      CCopasiObject * tmp = GlobalKeys.get(keyMap[k][0]);

                      if ((usage == CFunctionParameter::SUBSTRATE) || (usage == CFunctionParameter::PRODUCT)
                          || (usage == CFunctionParameter::MODIFIER))
                        {
                          CMetab* metab;

                          metab = dynamic_cast< CMetab * >(tmp);

                          if (metab->getStatus() == CModelEntity::FIXED)
                            {
                              equation << metab->getInitialConcentration();
                            }
                          else
                            {
                              name = metab ->getObjectName();
                              index = findMetabXByName(copasiModel, name);
                              equation << "y[" << index << "]";
                            }
                        }
                      if (usage == CFunctionParameter::PARAMETER)
                        if (!(reac->isLocalParameter(k)))
                          {
                            CModelValue* modval;
                            modval = dynamic_cast< CModelValue * >(tmp);
                            name = modval ->getObjectName();
                            index = findGlobalParamByName(copasiModel, name);
                            equation << "gk[" << index << "]";
                          }
                        else
                          {
                            CCopasiParameter* param;
                            param = dynamic_cast< CCopasiParameter * >(tmp);
                            name = param->getObjectName();

                            index = findKinParamByName(reac, name);
                            equation << "k[" << counter + index << "]";
                          }
                      if (usage == CFunctionParameter::VOLUME)
                        {
                          CCompartment* comp;
                          comp = dynamic_cast< CCompartment * >(tmp);
                          name = comp->getObjectName();

                          index = findCompByName(copasiModel, name);
                          equation << "c[";
                          equation << index << "]";
                        }
                      if (usage == CFunctionParameter::VARIABLE)
                        {
                          CModelValue* modval;
                          modval = dynamic_cast< CModelValue * >(tmp);

                          std::cout << std::endl;
                          std::cout << "******* Function parameter" << modval->getObjectName().c_str()
                          << ": this version does not support the parameters usage VARIABLE ******";

                          return false;
                        }

                      if (k != params_size - 1) equation << ", ";
                    }

                  equation << ")";
                }
              else
                {
                  std::ostringstream massaction;
                  std::string name;
                  //CFunctionParameter::Role usage; //seems to be unused

                  const CCopasiVector<CChemEqElement> & substrs = reac->getChemEq().getSubstrates();
                  const CCopasiVector<CChemEqElement> & prods = reac->getChemEq().getProducts();
                  const std::vector<std::vector<std::string> > & keyMap = reac->getParameterMappings();
                  CCopasiObject * tmp;

                  unsigned C_INT32 substrs_size = substrs.size(), prods_size = prods.size();
                  unsigned C_INT32 m, mult;
                  C_INT32 index;

                  CChemEqElement* substr;
                  CChemEqElement* prod;

                  const CMassAction cMassAction = static_cast<const CMassAction>(reac->getFunction());

                  massaction << "(";

                  //usage = cMassAction.getVariables()[0]->getUsage(); //seems to be unused
                  tmp = GlobalKeys.get(keyMap[0][0]);

                  if (!(reac->isLocalParameter(0)))
                    {
                      CModelValue* modval;
                      modval = dynamic_cast< CModelValue * >(tmp);
                      name = modval ->getObjectName();
                      index = findGlobalParamByName(copasiModel, name);
                      massaction << "gk[" << index << "]";
                    }
                  else
                    {
                      CCopasiParameter* param;
                      param = dynamic_cast< CCopasiParameter * >(tmp);
                      name = param->getObjectName();

                      index = findKinParamByName(reac, name);
                      massaction << "k[" << counter + index << "]";
                    }

                  for (k = 0; k < substrs_size; ++k)
                    {
                      substr = substrs[k];
                      mult = substr->getMultiplicity();

                      if (substr->getMetabolite().getStatus() == CModelEntity::FIXED)
                        {
                          massaction << " * " << substr->getMetabolite().getInitialConcentration();

                          if (mult > 1)
                            for (m = 1; m < mult; ++m)
                              massaction << " * " << substr->getMetabolite().getInitialConcentration();
                        }
                      else
                        {
                          name = substr->getMetabolite().getObjectName();
                          index = findMetabXByName(copasiModel, name);
                          massaction << " * y[" << index << "]";

                          if (mult > 1)
                            for (m = 1; m < mult; ++m)
                              massaction << " * y[" << index << "]";
                        }
                    }

                  if (cMassAction.isReversible() == TriTrue)
                    {
                      massaction << " - ";
                      //usage = cMassAction.getVariables()[0]->getUsage(); //seems to be unused

                      tmp = GlobalKeys.get(keyMap[2][0]);

                      if (!(reac->isLocalParameter(2)))
                        {
                          CModelValue* modval;
                          modval = dynamic_cast< CModelValue * >(tmp);
                          name = modval ->getObjectName();
                          index = findGlobalParamByName(copasiModel, name);
                          massaction << "gk[" << index << "]";
                        }
                      else
                        {
                          CCopasiParameter* param;
                          param = dynamic_cast< CCopasiParameter * >(tmp);
                          name = param->getObjectName();

                          index = findKinParamByName(reac, name);
                          massaction << "k[" << counter + index << "]";
                        }

                      for (k = 0; k < prods_size; ++k)
                        {
                          prod = prods[k];
                          mult = prod->getMultiplicity();

                          if (prod->getMetabolite().getStatus() == CModelEntity::FIXED)
                            {
                              massaction << " * " << prod->getMetabolite().getInitialConcentration();

                              if (mult > 1)
                                for (m = 1; m < mult; ++m)
                                  massaction << " * " << prod->getMetabolite().getInitialConcentration();
                            }
                          else
                            {
                              name = metab->getObjectName();
                              index = findMetabXByName(copasiModel, name);
                              massaction << " * y[" << index << "]";

                              if (mult > 1)
                                for (m = 1; m < mult; ++m)
                                  massaction << " * y[" << index << "]";
                            }
                        }
                    }
                  massaction << ") ";
                  equation << massaction.str();
                }

              if (reac->getCompartmentNumber() != 1) equation << " / c[" << compartment_index << "]";
            }

          counter += reac->getParameters().size();
        }
      outFile << "dxdt[" << i << "] = " << equation.str() << ";" << std::endl;
    }
  outFile << "#endif // DIFFERENTIAL_EQUATIONS" << std::endl;

  return true;
}
