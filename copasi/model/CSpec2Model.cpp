#undef yyFlexLexer
#define yyFlexLexer CScanInputFlexLexer

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "utilities/utilities.h"
#include "FlexLexer.h"
#include "model.h"
#include "utilities/CGlobals.h"
#include "CSpec2Model.h"
#include "CSpecLine.h"
#include "CDeTerm.h"

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

void CSpec2Model::printInput()
{
  std::cout << "\n\n\n";
  //     std::cout << "What we read: \n";
  //     std::vector<string>::iterator it = mSpecContents.begin();
  //     int cnt = mSpecContents.size();
  //     std::cout << "There were " << cnt << " lines." << std::endl;
  //     int linecount = 0;
  //     while (it <  mSpecContents.end())
  //     {
  //         std::cout << "Line " << linecount++ << ": ";
  //         std::cout << *it++ << std::endl;
  //}
  std::vector<CSpecLine>::iterator it = mSpecLines.begin();
  std::cout << std::endl;

  while (it < mSpecLines.end())
    {
      std::cout << "Type = " << CSpecLine::convertedType(it->getType());
      std::cout << " Contents = " << it->getString() << std::endl;
      it++;
    }
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

  //printInput();

  mModel->setQuantityUnit("mol");

  processCompartments();
  processEQNs();
  processInits();
  processConstants();
  processRates();
  processFunctions();
  processMoieties();
  processDeTerms();
  mModel->initializeMetabolites();
  mModel->compile();
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
          //C_FLOAT64 comp_vol = atof(it->extractRight().c_str());
          //CCompartment *compartment = new CCompartment(comp_name, comp_vol);
          //mModel->getCompartments().add(compartment);
          mModel->addCompartment(comp_name, atof(it->extractRight().c_str()));
        }
    }

  for (unsigned C_INT32 i = 0; i < mModel->getCompartments().size(); i++)
    {
      CCompartment *comp = mModel->getCompartments()[i];
      std::cout << "Added compartment with name " << comp->getName() << " and volume = " << comp->getVolume() << std::endl;
    }
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

  for (std::vector<CBaseEqn>::iterator itb = mDeVector.begin(); itb < mDeVector.end(); itb++)
    {
      std::cout << "Added DE " << itb->getMetabolite();
      std::cout << " in compartment " << itb->getCompartment();
      std::cout << " with RHS = " << itb->getContents() << std::endl;
    }

  for (std::vector<CBaseEqn>::iterator itc = mMoietyVector.begin(); itc < mMoietyVector.end(); itc++)
    {
      std::cout << "Added EQN " << itc->getMetabolite();
      std::cout << " in compartment " << itc->getCompartment();
      std::cout << " with RHS = " << itc->getContents() << std::endl;
    }
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

          if (vit != mDeVector.end())
            {
              // this _does_ correspond to a metabolite.
              //CMetab metab;
              //metab.setName(metab_name);
              //metab.setStatus(METAB_VARIABLE);
              C_FLOAT64 iconc = atof(contents.c_str());
              //metab.setInitialConcentration(iconc);
              //mModel->getCompartments()[comp_name]->addMetabolite(metab);
              mModel->addMetabolite(comp_name, metab_name, iconc, CMetab::METAB_VARIABLE);
            }
          else
            {
              CCopasiMessage(CCopasiMessage::ERROR, "Not a reactant initialization %s: %s = %s", comp_name.c_str(), metab_name.c_str(), contents.c_str());
            }
        }
    }

  unsigned C_INT32 i = 0, j = 0;

  for (i = 0; i < mModel->getCompartments().size(); i++)
    {
      CCompartment comp = *mModel->getCompartments()[i];
      std::cout << "In compartment " << comp.getName() << ":\n";

      for (j = 0; j < comp.metabolites().size(); j++)
        {
          CMetab metab = *comp.metabolites()[j];
          std::cout << "Metabolite " << metab.getName() << " with initial concentration " << metab.getInitialConcentration() << std::endl;
        }
    }
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
          std::cout << "Added constant " << const_name << " with value " << val << std::endl;

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
          std::cout << "Added rate constant " << rate_name << " with value " << val << std::endl;
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
  //    CTempReaction *reaction = 0;
  CTempMetab *tmp_metab = 0;

  std::vector<CBaseEqn>::iterator it = mDeVector.begin();

  for (; it != mDeVector.end(); it++)  //every DE in File
    {
      // Create a stack of terms on the RHS of the DE.
      std::vector<CDeTerm *> termstack = createTermStack(it->getContents());
      // Get the metabolite on the LHS of the DE
      CMetab *LHSMetab = getLHSMetab(*it);
      std::cout << std::endl << "LHS-Name: " << LHSMetab->getName() << std::endl;

      // Step through each term of this differential equation.
      std::vector <CDeTerm *>::iterator termit = termstack.begin();
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
              //std::string rate = expandRate(*termit);
              reaction = new CTempReaction(*termit);
              //reaction->setDescription(rate);
              //reaction->setIdentifiers(*termit);
              trs.addReaction(reaction);
              reaction = trs.findReaction(rate_constant);
            }

          // Add the LHS metabolite to the temp reaction
          tmp_metab = reaction->addMetabolite(LHSMetab);
          tmp_metab->setNumChange(num_change + tmp_metab->getNumChange());

          // Add the metabolites on the RHS of the DE.

          // todo: this is only necessary once. it should be checked if all reactions with the same rate const are identical
          CMetab *metabolite = 0;

          std::string metabolite_name;

          unsigned C_INT32 pos = 0;

          while ("" != (metabolite_name = (*termit)->getTopLevelMetabolite(pos++, multiplicity)))
            {
              if ((metabolite = findMetabolite(metabolite_name)))
                {
                  tmp_metab = reaction->addMetabolite(metabolite);
                  tmp_metab->setMultiplicity(multiplicity);
                }
            }
        }
    }

  // Now create proper CReaction's from each of the CTempReact's
  mModel->initializeMetabolites();

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

CMetab *CSpec2Model::getLHSMetab(CBaseEqn &beqn)
{
  return mModel->getCompartments()[beqn.getCompartment()]->metabolites()[beqn.getMetabolite()];
}

CMetab *CSpec2Model::findMetabolite(std::string metab_name)
{
  for (unsigned C_INT32 i = 0; i < mModel->getCompartments().size(); i++)
    {
      for (unsigned C_INT32 j = 0; j < mModel->getCompartments()[i]->metabolites().size(); j++)
        {
          if (mModel->getCompartments()[i]->metabolites()[j]->getName() == metab_name)
            {
              return mModel->getCompartments()[i]->metabolites()[j];
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

          metab.setName(moiety_name);
          //metab.setStatus(CMetab::METAB_DEPENDENT);
          // :TODO: metab.setInitialConcentration(iconc);
          //mModel->getCompartments()[compartment_name]->addMetabolite(metab);
          mModel->addMetabolite(compartment_name, moiety_name, 0, CMetab::METAB_DEPENDENT);
          std::cout << "Added moiety " << moiety_name
          << ", " << compartment_name
          << ", " << contents << std::endl;
        }
    }
}

void CSpec2Model::processFunctions()
{
  // Find each function line
  CFunction *pFunction;
  std::vector<CSpecLine>::iterator it = mSpecLines.begin();

  for (; it < mSpecLines.end(); it++)
    {
      if (it->getType() == CSpecLine::FUN)
        {
          pFunction = new CKinFunction();
          std::string tmp = it->extractLeft();

          std::string::size_type p1 = tmp.find_first_not_of(" \t");
          std::string::size_type p2 = tmp.find_first_of("(");
          pFunction->setName(tmp.substr(p1, p2 - p1));

          std::string parameter =
            tmp.substr(p2 + 1, tmp.find_last_of(")") - p2 - 1);

          //CFunctionParameters & Parameters = pFunction->getParameters();
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
              pFunction->addParameter(ParameterName,
                                      CFunctionParameter::FLOAT64,
                                      "unknown");
            }

          tmp = it->extractRight();
          p1 = tmp.find_first_not_of(" \t");
          p2 = tmp.find_last_not_of(" \t");
          tmp = tmp.substr(p1, p2 - p1 + 1);
          pFunction->setDescription(tmp);
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
                      pFunction->addParameter(ParameterName,
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
          std::cout << pFunction->getParameters() << std::endl;
          Copasi->FunctionDB.add(pFunction);
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

// CReaction *CSpec2Model::findReaction(string search_name)
// {
//     CCopasiVectorS<CReaction> &reacts = mModel->getReactions();
//     for (unsigned C_INT32 i = 0; i < reacts.size(); i++)
//     {
//         if (reacts[i]->getName() == search_name)
//         {
//             return reacts[i];
//}
//}
//     return 0;
//}

// void CSpec2Model::addMetabolite(CReaction *react, CMetab *metab)
// {
//     // Add a metabolite to the reaction.
//     // Only add it if it hasn't already been added.
//}
C_INT32 CSpec2Model::parseLine(std::string) {return 0;}

#ifdef TEST

#include "../utilities/CGlobals.h"

CGlobals *Copasi = new std::CGlobals;

ofstream DebugFile("junk");

int main(int argc, char**argv)
{
  std::string filename = "exampleinput";

  if (argc == 2)
    {
      std::cout << "Assigning " << argv[1] << " to input file name\n";
      filename = argv[1];
    }
  else
    {
      std::cout << "Using default input file exampleinput\n";
    }

  try
    {
      CSpec2Model specreader(filename);
      CModel *model;
      // create a model
      model = specreader.createModel();
      // Test that we read the input file correctly
      specreader.printInput();
    }
  catch (CCopasiException Exception)
    {
      std::cout << Exception.getMessage().getText() << std::endl;
    }
}

#endif //TEST
