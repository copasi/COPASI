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
CSpec2Model::CSpec2Model() {CONSTRUCTOR_TRACE; }

CSpec2Model::CSpec2Model(std::string filename)
{
  CONSTRUCTOR_TRACE;
  mSpecFileName = filename;
}
CSpec2Model::~CSpec2Model() {DESTRUCTOR_TRACE; }

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

  string bufstr;

  while (getline(infile, bufstr, '\n'))
    {
      mSpecContents.push_back(bufstr);
    }

  return 0;
}

void CSpec2Model::printInput()
{
  cout << "\n\n\n";
  //     std::cout << "What we read: \n";
  //     std::vector<std::string>::iterator it = mSpecContents.begin();
  //     int cnt = mSpecContents.size();
  //     std::cout << "There were " << cnt << " lines." << std::endl;
  //     int linecount = 0;
  //     while (it <  mSpecContents.end())
  //     {
  //         std::cout << "Line " << linecount++ << ": ";
  //         std::cout << *it++ << std::endl;
  //     }
  std::vector<CSpecLine>::iterator it = mSpecLines.begin();
  cout << endl;

  while (it < mSpecLines.end())
    {
      cout << "Type = " << CSpecLine::convertedType(it->getType());
      cout << " Contents = " << it->getString() << endl;
      it++;
    }
}

CModel *CSpec2Model::createModel()
{
  cout << "Creating a model\n";
  mModel = new CModel();
  addFileContents();
  // Read the lines in the file one at a time, determine the type,
  // and store each string in the list for the corresponding type.
  vector<string>::iterator it = mSpecContents.begin();

  while (it < mSpecContents.end())
    {
      determineType(*it);
      it++;
    }

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

void CSpec2Model::determineType(string str)
{
  istringstream *strstr = new istringstream(str);
  CScanInputFlexLexer scanner(strstr);
  int type = scanner.yylex();

  if (type)
    {
      mSpecLines.push_back(CSpecLine(type, scanner.YYText()));
    }
}

void CSpec2Model::processCompartments()
{
  vector<CSpecLine>::iterator it = mSpecLines.begin();

  for (; it < mSpecLines.end(); it++)
    {
      if (it->getType() == CSpecLine::CPT)
        {
          string comp_name = it->extractCpt();
          C_FLOAT64 comp_vol = atof(it->extractRight().c_str());
          CCompartment *compartment = new CCompartment(comp_name, comp_vol);
          mModel->getCompartments().add(compartment);
        }
    }

  for (unsigned C_INT32 i = 0; i < mModel->getCompartments().size(); i++)
    {
      CCompartment *comp = mModel->getCompartments()[i];
      cout << "Added compartment with name " << comp->getName() << " and volume = " << comp->getVolume() << endl;
    }
}

void CSpec2Model::processEQNs()
{
  // pick out the EQN or DE lines. Store the compartment name, metabolite
  // name and contents string in a CBaseEqn instance, for later processing.

  vector<CSpecLine>::iterator it = mSpecLines.begin();

  for (; it < mSpecLines.end(); it++)
    {
      if (it->getType() == CSpecLine::DE)
        {
          string comp_name = it->extractCpt();
          string metab = it->extractLeft();
          string contents = it->extractRight();
          CBaseEqn tmp(comp_name, metab, contents);
          mDeVector.push_back(tmp);
        }

      if (it->getType() == CSpecLine::EQN)
        {
          string comp_name = it->extractCpt();
          string metab = it->extractLeft();
          string contents = it->extractRight();
          CBaseEqn tmp(comp_name, metab, contents);
          mMoietyVector.push_back(tmp);
        }
    }

  for (vector<CBaseEqn>::iterator itb = mDeVector.begin(); itb < mDeVector.end(); itb++)
    {
      cout << "Added DE " << itb->getMetabolite();
      cout << " in compartment " << itb->getCompartment();
      cout << " with RHS = " << itb->getContents() << endl;
    }

  for (vector<CBaseEqn>::iterator itc = mMoietyVector.begin(); itc < mMoietyVector.end(); itc++)
    {
      cout << "Added EQN " << itc->getMetabolite();
      cout << " in compartment " << itc->getCompartment();
      cout << " with RHS = " << itc->getContents() << endl;
    }
}

void CSpec2Model::processInits()
{
  // Find each INIT line, and determine whether it corresponds to a metabolite.
  vector<CSpecLine>::iterator it = mSpecLines.begin();

  for (; it < mSpecLines.end(); it++)
    {
      if (it->getType() == CSpecLine::INIT)
        {
          string comp_name = it->extractCpt();
          string metab_name = it->extractLeft();
          string contents = it->extractRight();
          CBaseEqn tmp(comp_name, metab_name, "");
          vector<CBaseEqn>::iterator vit = find(mDeVector.begin(), mDeVector.end(), tmp);

          if (vit != mDeVector.end())
            {
              // this _does_ correspond to a metabolite.
              CMetab metab;
              metab.setName(metab_name);
              metab.setStatus(METAB_VARIABLE);
              C_FLOAT64 iconc = atof(contents.c_str());
              metab.setInitialConcentration(iconc);
              mModel->getCompartments()[comp_name]->addMetabolite(metab);
            }
          else
            {
              CCopasiMessage(CCopasiMessage::ERROR, "Not a reactant initialization %s: %s = %s", comp_name.c_str(), metab_name.c_str(), contents.c_str());
            }
        }
    }

  unsigned C_INT32 i = 0, j = 0;

  for (i = 0 ; i < mModel->getCompartments().size(); i++)
    {
      CCompartment comp = *mModel->getCompartments()[i];
      cout << "In compartment " << comp.getName() << ":\n";

      for (j = 0 ; j < comp.metabolites().size(); j++)
        {
          CMetab metab = *comp.metabolites()[j];
          cout << "Metabolite " << metab.getName() << " with initial concentration " << metab.getInitialConcentration() << endl;
        }
    }
}

void CSpec2Model::processConstants()
{
  cout << "Doing consts\n";
  // Find each CNST line
  vector<CSpecLine>::iterator it = mSpecLines.begin();

  for (; it < mSpecLines.end(); it++)
    {
      if (it->getType() == CSpecLine::CNST)
        {
          string const_name = it->extractLeft();
          C_FLOAT64 val = atof(it->extractRight().c_str());
          mConstVector.push_back(CNameVal(const_name, val));
          cout << "Added constant " << const_name << " with value " << val << endl;

          //             CMetab *metab = new CMetab(metab_name);
          //             metab->setStatus(METAB_FIXED);
          //             metab->setInitialConcentration(atof(contents.c_str()));
          //             metab->setConcentration(atof(contents.c_str()));
          //             mModel->getMetabolites().push_back(metab); // XXX TODO: is this the right place to store these?
          //             cout << "For fixed metabolite " <<
          //                 mModel->getMetabolites()[mModel->getMetabolites().size() -1]->getName();
          //             cout << " set init concentration to " << *mModel->getMetabolites()[mModel->getMetabolites().size() -1]->getInitialConcentration() << endl;
        }
    }
}

void CSpec2Model::processRates()
{
  // Find each RATE line
  vector<CSpecLine>::iterator it = mSpecLines.begin();

  for (; it < mSpecLines.end(); it++)
    {
      if (it->getType() == CSpecLine::RATE)
        {
          string rate_name = it->extractLeft();
          C_FLOAT64 val = atof(it->extractRight().c_str());
          mRateVector.push_back(CNameVal(rate_name, val));
          cout << "Added rate constant " << rate_name << " with value " << val << endl;
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

  vector<CBaseEqn>::iterator it = mDeVector.begin();

  for (; it != mDeVector.end(); it++)
    {
      // Create a stack of terms on the RHS of the DE.
      cout << "Creating term stack\n";
      vector<CDeTerm *> termstack = createTermStack(it->getContents());
      // Get the metabolite on the LHS of the DE
      CMetab *LHSMetab = getLHSMetab(*it);
      // Step through each term of this differential equation.
      vector <CDeTerm *>::iterator termit = termstack.begin();

      for (; termit != termstack.end(); termit++)
        {
          cout << "In term\n";
          // The rate constant is used to relate this term to a particular reaction.
          string rate_constant = (*termit)->getRateConstant();
          num_change = (*termit)->getSign() * (*termit)->getMultiplier();
          // Find or create the CTempReaction with this rate constant
          CTempReaction *reaction = trs.findReaction(rate_constant);

          if (reaction == 0)
            {
              string rate = expandRate(*termit);
              reaction = new CTempReaction(rate_constant);
              reaction->setDescription(rate);
              reaction->setIdentifiers(*termit);
              trs.addReaction(reaction);
              reaction = trs.findReaction(rate_constant);
            }

          // Add the LHS metabolite to the temp reaction
          tmp_metab = reaction->addMetabolite(LHSMetab);

          tmp_metab->setNumChange(num_change);

          // Add the metabolites on the RHS of the DE.
          CMetab *metabolite = 0;

          string metabolite_name;

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
      cout << trs[i] << endl;
    }
}

vector<CDeTerm *> CSpec2Model::createTermStack(string str)
{
  istringstream *strstr = new istringstream(str);
  CScanInputFlexLexer scanner(strstr);
  CDeTerm::Type type;
  bool isbegin = true;
  C_INT32 level = 0;
  vector<CDeTerm *> *termstack = new vector<CDeTerm *>;
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
  cout << "Created term stack. Compiling...\n";

  vector<CDeTerm*>::iterator it = termstack->begin();

  for (; it != termstack->end(); it++)
    {
      (*it)->compile(mRateVector);
    }

  cout << "Done compiling\n";
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

CMetab *CSpec2Model::findMetabolite(string metab_name)
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
  vector<CSpecLine>::iterator it = mSpecLines.begin();
  string comparment_name;
  string moiety_name;
  string contents;
  CMetab metab;

  for (; it < mSpecLines.end(); it++)
    {
      if (it->getType() == CSpecLine::EQN)
        {
          comparment_name = it->extractCpt();
          moiety_name = it->extractLeft();
          contents = it->extractRight();

          mMoietyVector.push_back(CBaseEqn(comparment_name,
                                           moiety_name,
                                           contents));

          metab.setName(moiety_name);
          metab.setStatus(METAB_DEPENDENT);
          // :TODO: metab.setInitialConcentration(iconc);
          mModel->getCompartments()[comparment_name]->addMetabolite(metab);

          cout << "Added moiety " << moiety_name
          << ", " << comparment_name
          << ", " << contents << endl;
        }
    }
}

void CSpec2Model::processFunctions()
{
  // Find each function line
  CFunction *pFunction;
  vector<CSpecLine>::iterator it = mSpecLines.begin();

  for (; it < mSpecLines.end(); it++)
    {
      if (it->getType() == CSpecLine::FUN)
        {
          pFunction = new CKinFunction();
          string tmp = it->extractLeft();

          string::size_type p1 = tmp.find_first_not_of(" \t");
          string::size_type p2 = tmp.find_first_of("(");
          pFunction->setName(tmp.substr(p1, p2 - p1));

          string parameter =
            tmp.substr(p2 + 1, tmp.find_last_of(")") - p2 - 1);

          CFunctionParameters & Parameters = pFunction->getParameters();
          p1 = 0;
          p2 = 0;
          string ParameterName;

          while (p1 != string::npos)
            {
              p2 = parameter.find(",");
              ParameterName = parameter.substr(p1, p2 - p1);
              p1 = p2;
              Parameters.add(ParameterName,
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

          istringstream *strstr = new istringstream(tmp);
          CScanInputFlexLexer scanner(strstr);
          CDeTerm::Type type;

          while ((type = static_cast<CDeTerm::Type>(scanner.yylex())))
            if (type == CDeTerm::IDENT)
              {
                ParameterName = scanner.YYText();

                try
                  {
                    Parameters.add(ParameterName,
                                   CFunctionParameter::FLOAT64,
                                   "PARAMETER");
                  }
                catch (CCopasiException Exception)
                  {
                    /* Parameter exists not found */

                    if ((MCCopasiVector + 2) != Exception.getMessage().getNumber())
                      throw Exception;
                  }
              }

          Copasi->FunctionDB.add(pFunction);
          // ((CKinFunction *)pFunction)->compile();
          cout << it->getString() << endl;
        }
    }
}

string CSpec2Model::expandRate(CDeTerm *term)
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
//         }
//     }
//     return 0;
// }

// void CSpec2Model::addMetabolite(CReaction *react, CMetab *metab)
// {
//     // Add a metabolite to the reaction.
//     // Only add it if it hasn't already been added.
// }
C_INT32 CSpec2Model::parseLine(string) { return 0; }

#ifdef TEST

#include "../utilities/CGlobals.h"

CGlobals *Copasi = new CGlobals;

std::ofstream DebugFile("junk");

int main(int argc, char**argv)
{
  string filename = "exampleinput";

  if (argc == 2)
    {
      cout << "Assigning " << argv[1] << " to input file name\n";
      filename = argv[1];
    }
  else
    {
      cout << "Using default input file exampleinput\n";
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
      cout << Exception.getMessage().getText() << endl;
    }
}

#endif //TEST
