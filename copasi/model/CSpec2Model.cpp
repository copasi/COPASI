/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/Attic/CSpec2Model.cpp,v $
   $Revision: 1.43 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/02/18 16:25:27 $
   End CVS Header */

#undef yyFlexLexer
#define yyFlexLexer CScanInputFlexLexer

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/CCopasiException.h"
#include "FlexLexer.h"
#include "CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "CSpec2Model.h"
#include "CSpecLine.h"
#include "CDeTerm.h"
#include "function/CKinFunction.h"
#include "function/CFunctionDB.h"

CSpec2Model::CSpec2Model() {CONSTRUCTOR_TRACE;}

CSpec2Model::CSpec2Model(std::string filename)
{
  CONSTRUCTOR_TRACE;
  mSpecFileName = filename;
}
CSpec2Model::~CSpec2Model() {DESTRUCTOR_TRACE;}

C_INT32 CSpec2Model::addFileContents()
{
  if (0 == mSpecFileName.length())
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Input file not specified");
    }

  std::ifstream infile(mSpecFileName.c_str());

  if (!infile)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Error opening spec file %s", mSpecFileName.c_str());
    }

  std::string bufstr;

  while (std::getline(infile, bufstr, '\n'))
    {
      mSpecContents.push_back(bufstr);
    }

  return 0;
}

CModel *CSpec2Model::createModel()
{
  std::cout << "Creating a model\n";
  mModel = new CModel();
  addFileContents();
  // Read the lines in the file one at a time, determine the type,
  // and store each std::string in the list for the corresponding type.

  std::vector< std::string >::iterator it = mSpecContents.begin();
  while (it < mSpecContents.end())
    {
      determineType(*it);
      it++;
    }

  mModel->setQuantityUnit("mmol");

  processCompartments();
  processEQNs();
  processInits();
  processConstants();
  processRates();
  processFunctions();
  processMoieties();
  processDeTerms();
  mModel->initializeMetabolites();
  mModel->setCompileFlag();

  unsigned int i;    // should that not be in CModel::compile ?
  for (i = 0; i < mModel->getReactions().size(); i++)
    mModel->getReactions()[i]->compile(/*mModel->getCompartments()*/);

  return mModel;
}

void CSpec2Model::determineType(std::string str)
{
  std::istringstream *strstr = new std::istringstream(str);
  CScanInputFlexLexer scanner(strstr);
  int type = scanner.yylex();

  if (type)
    {
      mSpecLines.push_back(CSpecLine(type, scanner.YYText()));
    }
}

void CSpec2Model::processCompartments()
{
  std::vector<CSpecLine>::iterator it = mSpecLines.begin();

  for (; it < mSpecLines.end(); it++)
    {
      if (it->getType() == CSpecLine::CPT)
        {
          std::string comp_name = it->extractCpt();
          mModel->createCompartment(comp_name, atof(it->extractRight().c_str()));
        }
    }

  //for (unsigned C_INT32 i = 0; i < mModel->getCompartments().size(); i++)
  //  {
  //    CCompartment *comp = mModel->getCompartments()[i];
  //    std::cout << "Added compartment with name " << comp->getName() << " and volume = " << comp->getVolume() << std::endl;
  //}
}

void CSpec2Model::processEQNs()
{
  // pick out the EQN or DE lines. Store the compartment name, metabolite
  // name and contents string in a CBaseEqn instance, for later processing.

  std::vector<CSpecLine>::iterator it = mSpecLines.begin();

  for (; it < mSpecLines.end(); it++)
    {
      if (it->getType() == CSpecLine::DE)
        {
          std::string comp_name = it->extractCpt();
          std::string metab = it->extractLeft();
          std::string contents = it->extractRight();
          CBaseEqn tmp(comp_name, metab, contents);
          mDeVector.push_back(tmp);
        }

      if (it->getType() == CSpecLine::EQN)
        {
          std::string comp_name = it->extractCpt();
          std::string metab = it->extractLeft();
          std::string contents = it->extractRight();
          CBaseEqn tmp(comp_name, metab, contents);
          mMoietyVector.push_back(tmp);
        }
    }

  //for (std::vector<CBaseEqn>::iterator itb = mDeVector.begin(); itb < mDeVector.end(); itb++)
  //  {
  //    std::cout << "Added DE " << itb->getMetabolite();
  //    std::cout << " in compartment " << itb->getCompartment();
  //    std::cout << " with RHS = " << itb->getContents() << std::endl;
  //}

  //for (std::vector<CBaseEqn>::iterator itc = mMoietyVector.begin(); itc < mMoietyVector.end(); itc++)
  //  {
  //    std::cout << "Added EQN " << itc->getMetabolite();
  //    std::cout << " in compartment " << itc->getCompartment();
  //    std::cout << " with RHS = " << itc->getContents() << std::endl;
  //}
}

void CSpec2Model::processInits()
{
  // Find each INIT line, and determine whether it corresponds to a metabolite.
  std::vector<CSpecLine>::iterator it = mSpecLines.begin();

  for (; it < mSpecLines.end(); it++)
    {
      if (it->getType() == CSpecLine::INIT)
        {
          std::string comp_name = it->extractCpt();
          std::string metab_name = it->extractLeft();
          std::string contents = it->extractRight();
          CBaseEqn tmp(comp_name, metab_name, "");
          std::vector<CBaseEqn>::iterator vit = std::find(mDeVector.begin(), mDeVector.end(), tmp);

          if (vit != mDeVector.end())  // this _does_ correspond to a metabolite.
            {
              C_FLOAT64 iconc = atof(contents.c_str());
              mModel->createMetabolite(metab_name, comp_name, iconc, CMetab::METAB_VARIABLE);
            }
          else
            {
              CCopasiMessage(CCopasiMessage::ERROR, "Not a reactant initialization %s: %s = %s", comp_name.c_str(), metab_name.c_str(), contents.c_str());
            }
        }
    }

  //unsigned C_INT32 i = 0, j = 0;
  //for (i = 0; i < mModel->getCompartments().size(); i++)
  //  {
  //    CCompartment comp = *mModel->getCompartments()[i];
  //    std::cout << "In compartment " << comp.getName() << ":\n";
  //    for (j = 0; j < comp.metabolites().size(); j++)
  //      {
  //        CMetab metab = *comp.metabolites()[j];
  //        std::cout << "Metabolite " << metab.getName() << " with initial concentration " << metab.getInitialConcentration() << std::endl;
  //}
  //}
}

void CSpec2Model::processConstants()
{
  std::cout << "Doing consts\n";
  // Find each CNST line
  std::vector<CSpecLine>::iterator it = mSpecLines.begin();

  for (; it < mSpecLines.end(); it++)
    {
      if (it->getType() == CSpecLine::CNST)
        {
          std::string const_name = it->extractLeft();
          C_FLOAT64 val = atof(it->extractRight().c_str());
          mConstVector.push_back(CNameVal(const_name, val));
          //std::cout << "Added constant " << const_name << " with value " << val << std::endl;

          //             CMetab *metab = new CMetab(metab_name);
          //             metab->setStatus(CMetab::METAB_FIXED);
          //             metab->setInitialConcentration(atof(contents.c_str()));
          //             metab->setConcentration(atof(contents.c_str()));
          //             mModel->getMetabolites().push_back(metab); // XXX TODO: is this the right place to store these?
          //             std::cout << "For fixed metabolite " <<
          //                 mModel->getMetabolites()[mModel->getMetabolites().size() -1]->getName();
          //             std::cout << " set init concentration to " << *mModel->getMetabolites()[mModel->getMetabolites().size() -1]->getInitialConcentration() << std::endl;
        }
    }
}

void CSpec2Model::processRates()
{
  // Find each RATE line
  std::vector<CSpecLine>::iterator it = mSpecLines.begin();

  for (; it < mSpecLines.end(); it++)
    {
      if (it->getType() == CSpecLine::RATE)
        {
          std::string rate_name = it->extractLeft();
          C_FLOAT64 val = atof(it->extractRight().c_str());
          mRateVector.push_back(CNameVal(rate_name, val));
          //std::cout << "Added rate constant " << rate_name << " with value " << val << std::endl;
        }
    }
}

void CSpec2Model::processDeTerms()
{
  // We need the number by which each metabolite changes in each
  // reaction and the number of each present in each reaction. We
  // also need the rate function for each term.

  // The basic idea: we break the RHS into a vector of terms, and
  // then analyse each term one by one. For each term, we extract
  // the rate constant and use it to name the function. The function
  // is the rate for this reaction, and is the DE term with the
  // multiplier removed.

  // For each term, we add to the associated reaction (determined
  // from the rate constant) the LHS metab and each top-level metab
  // on the RHS. The addMetabolite() function only adds a metabolite
  // if it has not previously been added. The multiplicative factor
  // is used to provide the definitive value for the number by which
  // the LHS metab changes in this reaction. The multiplicity is
  // deduced from the number of instances of the metabolite in the
  // rate.

  C_FLOAT64 num_change = 0; // The multiplicative factor
  C_INT32 multiplicity = 0;
  CTempReactionSet trs;
  CTempMetab *tmp_metab = 0;

  std::vector<CBaseEqn>::const_iterator it = mDeVector.begin();

  for (; it != mDeVector.end(); it++)  //every DE in File
    {
      // Create a stack of terms on the RHS of the DE.
      std::vector<CDeTerm *> termstack = createTermStack(it->getContents());
      // Get the metabolite on the LHS of the DE
      const CMetab *LHSMetab = getLHSMetab(*it);
      std::cout << std::endl << "LHS-Name: " << LHSMetab->getObjectName() << std::endl;

      // Step through each term of this differential equation.
      std::vector <CDeTerm *>::const_iterator termit = termstack.begin();
      for (; termit != termstack.end(); termit++)  //every Term in DE
        {
          // The rate constant is used to relate this term to a particular reaction.
          std::string rate_constant = (*termit)->getRateConstant();
          num_change = (*termit)->getSign() * (*termit)->getMultiplier();
          std::cout << "In term " << rate_constant << " num_change: " << num_change << std::endl;
          // Find or create the CTempReaction with this rate constant
          CTempReaction *reaction = trs.findReaction(rate_constant);

          if (reaction == 0)
            {
              std::cout << "new reaction" << std::endl;
              reaction = new CTempReaction(*termit);
              trs.addReaction(reaction);
              reaction = trs.findReaction(rate_constant);

              const CMetab *metabolite = 0;
              std::string metabolite_name;
              unsigned C_INT32 pos = 0;

              while ("" != (metabolite_name = (*termit)->getTopLevelMetabolite(pos++, multiplicity)))
                {
                  if ((metabolite = findMetabolite(metabolite_name)))
                    {
                      tmp_metab = reaction->addMetabolite(metabolite);
                      tmp_metab->setMultiplicity(multiplicity + tmp_metab->getMultiplicity());
                    }
                  else
                    {
                      // top level metabolite of CDeTerm is not in the list of metabolites. what to do?
                    }
                }
            }
          else // not a new reaction
            {
              // check
            }

          // Add the LHS metabolite to the temp reaction
          tmp_metab = reaction->addMetabolite(LHSMetab);
          tmp_metab->setNumChange((C_INT32) num_change + tmp_metab->getNumChange());
        }
    }

  // Now create proper CReaction's from each of the CTempReact's
  mModel->initializeMetabolites(); // really necessary?

  for (C_INT32 i = 0; i < trs.size(); i++)
    {
      trs[i].compile(mModel, mRateVector, mConstVector);
      std::cout << trs[i] << std::endl;
    }
}

std::vector<CDeTerm *> CSpec2Model::createTermStack(std::string str)
{
  std::istringstream *strstr = new std::istringstream(str);
  CScanInputFlexLexer scanner(strstr);
  CDeTerm::Type type;
  bool isbegin = true;
  C_INT32 level = 0;
  std::vector<CDeTerm *> *termstack = new std::vector<CDeTerm *>;
  CDeTerm *determ;

  while ((type = static_cast<CDeTerm::Type>(scanner.yylex())))
    {
      if (isbegin || ((level == 0) && ((type == CDeTerm::PLUS) || (type == CDeTerm::MINUS))))
        {
          // We're only at the beginning of a line once
          isbegin = false;
          // Create and set the sign of a CDeTerm
          determ = new CDeTerm();
          termstack->push_back(determ);

          if ((type == CDeTerm::MINUS) || (type == CDeTerm::PLUS))
            {
              determ->setSign(scanner.YYText());
            }
          else
            {
              level = adjustLevel(level, type);
              determ->addElement(type, scanner.YYText());
            }
        }
      else
        {
          determ->addElement(type, scanner.YYText());
          level = adjustLevel(level, type);
        }

      if (level < 0)
        {
          CCopasiMessage(CCopasiMessage::ERROR, "Error parsing differential equation");
        }
    }

  // Now, compile each term. i.e. extract the multiplier and rate constant

  std::vector<CDeTerm*>::iterator it = termstack->begin();

  for (; it != termstack->end(); it++)
    {
      std::cout << " ----------- " << std::endl << **it << std::endl;
      (*it)->compile(mRateVector);
      std::cout << **it << std::endl << std::endl;
    }
  return *termstack;
}

C_INT32 CSpec2Model::adjustLevel(C_INT32 level, C_INT32 type)
{
  if (type == CDeTerm::LPAREN)
    {
      level++;
    }
  else if (type == CDeTerm::RPAREN)
    {
      level--;
    }

  return level;
}

const CMetab *CSpec2Model::getLHSMetab(const CBaseEqn &beqn) const
  {
    return mModel->getCompartments()[beqn.getCompartment()]->getMetabolites()[beqn.getMetabolite()];
  }

CMetab *CSpec2Model::findMetabolite(std::string metab_name)
{
  for (unsigned C_INT32 i = 0; i < mModel->getCompartments().size(); i++)
    {
      for (unsigned C_INT32 j = 0; j < mModel->getCompartments()[i]->getMetabolites().size(); j++)
        {
          if (mModel->getCompartments()[i]->getMetabolites()[j]->getObjectName() == metab_name)
            {
              return mModel->getCompartments()[i]->getMetabolites()[j];
            }
        }
    }

  return 0;
}

void CSpec2Model::processMoieties()
{
  // Find each moiety line
  std::vector<CSpecLine>::iterator it = mSpecLines.begin();
  std::string compartment_name;
  std::string moiety_name;
  std::string contents;
  CMetab metab;

  for (; it < mSpecLines.end(); it++)
    {
      if (it->getType() == CSpecLine::EQN)
        {
          compartment_name = it->extractCpt();
          moiety_name = it->extractLeft();
          contents = it->extractRight();

          mMoietyVector.push_back(CBaseEqn(compartment_name,
                                           moiety_name,
                                           contents));

          metab.setObjectName(moiety_name);
          mModel->createMetabolite(moiety_name, compartment_name, 0, CMetab::METAB_DEPENDENT);
          std::cout << "Added moiety " << moiety_name
          << ", " << compartment_name
          << ", " << contents << std::endl;
        }
    }
}

void CSpec2Model::processFunctions()
{
  // Find each function line
  CKinFunction Function;
  std::vector<CSpecLine>::iterator it = mSpecLines.begin();

  for (; it < mSpecLines.end(); it++)
    {
      if (it->getType() == CSpecLine::FUN)
        {
          Function.cleanup();
          std::string tmp = it->extractLeft();

          std::string::size_type p1 = tmp.find_first_not_of(" \t");
          std::string::size_type p2 = tmp.find_first_of("(");
          Function.setName(tmp.substr(p1, p2 - p1));

          std::string parameter =
            tmp.substr(p2 + 1, tmp.find_last_of(")") - p2 - 1);

          //CFunctionParameters & Parameters = Function.getParameters();
          p1 = 0;
          p2 = 0;
          std::string ParameterName;

          while (p1 != std::string::npos)
            {
              p2 = parameter.find(",");
              ParameterName = parameter.substr(p1, p2 - p1);
              p1 = p2;
              //Parameters.add(ParameterName,
              //               CFunctionParameter::FLOAT64,
              //               "unknown");
              Function.addParameter(ParameterName,
                                    CFunctionParameter::FLOAT64,
                                    "unknown");
            }

          tmp = it->extractRight();
          p1 = tmp.find_first_not_of(" \t");
          p2 = tmp.find_last_not_of(" \t");
          tmp = tmp.substr(p1, p2 - p1 + 1);
          Function.setDescription(tmp);
          // :TODO: We have to identify constants
          //        and define them as parameters.

          std::istringstream *strstr = new std::istringstream(tmp);
          CScanInputFlexLexer scanner(strstr);
          CDeTerm::Type type;

          while ((type = static_cast<CDeTerm::Type>(scanner.yylex())))
            {
              std::cout << type << std::endl;
              if (type == CDeTerm::IDENT)
                {
                  ParameterName = scanner.YYText();
                  std::cout << "ParameterName: " << ParameterName << std::endl;
                  try
                    {
                      //Parameters.add(ParameterName,
                      //               CFunctionParameter::FLOAT64,
                      //               "PARAMETER");
                      Function.addParameter(ParameterName,
                                            CFunctionParameter::FLOAT64,
                                            "PARAMETER");
                    }
                  catch (CCopasiException Exception)
                    {
                      /* Parameter exists not found */

                      std::cout << "Exception" << std::endl;
                      if ((MCCopasiVector + 2) != Exception.getMessage().getNumber())
                        throw Exception;
                    }
                }
            }
          std::cout << Function.getParameters() << std::endl;
          CCopasiDataModel::Global->getFunctionList()->add(Function);
          // ((CKinFunction *)pFunction)->compile();
          std::cout << it->getString() << std::endl;
        }
    }
}

std::string CSpec2Model::expandRate(CDeTerm *term)
{
  // XXX TODO: expand functions and concatenate them
  // XXX At the moment, we just assume that there are no functions to expand
  return term->getDescription();
}
