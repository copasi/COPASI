#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#define  COPASI_TRACE_CONSTRUCTION 

#include "copasi.h"
#include "model.h"
#include "utilities/utilities.h"
#include "CSpecLine.h"
#include "CDeTerm.h"

#undef yyFlexLexer
#define yyFlexLexer CScanInputFlexLexer

#include "function/FlexLexer.h"

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
//     processFunctions();
//     processMoieties();
//     processDeTerms();
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
    for ( ; it < mSpecLines.end(); it++)
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
    // Find each INIT line, and determine whether it corresponds to a reactant.
    vector<CSpecLine>::iterator it = mSpecLines.begin();
    for ( ; it < mSpecLines.end(); it++)
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
                // this does correspond to a reactant.
                CMetab metab(metab_name);
                metab.setCompartment( mModel->getCompartments()[comp_name]);
                metab.setStatus(METAB_VARIABLE);
                C_FLOAT64 iconc = atof(contents.c_str());
                metab.setInitialConcentration(iconc);
                metab.setConcentration(iconc);    // XXX TODO: is this necessary?
//                mModel.getMetabolites().push_back(&metab); // XXX TODO: Are metabolites also added to a model, or just compartment
                mModel->getCompartments()[comp_name]->addMetabolite(metab);
            }
            else
            {
//                CCopasiMessage(CCopasiMessage::ERROR, "Not a reactant initialization %s: %s = %s", comp_name, metab_name, contents);
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
            cout << "Metabolite " << metab.getName() << " with initial concentration " << *metab.getInitialConcentration() << endl;
        }
    }
}

void CSpec2Model::processConstants()
{
    cout << "Doing consts\n";
    // Find each CNST line
    vector<CSpecLine>::iterator it = mSpecLines.begin();
    for ( ; it < mSpecLines.end(); it++)
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
    for ( ; it < mSpecLines.end(); it++)
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

#if 0
void CSpec2Model::processDeTerms()
{
    vector<CBaseEqn>::iterator it = mDeVector.begin();
    for (; it != mDeVector.end(); it++)
    {
        vector<CDeTerm *> termstack = createTermStack(it->getContents());
        // We'll need the metabolite on the LHS as we go along, so get it now
        CMetab *LHSMetab = getLHSMetab(*it);
        // Step through each term of this differential equation.
        vector <CDeTerm *>::iterator termit = termstack.begin();
        for (; termit != termstack.end(); termit++)
        {
            // The rate constant is used to relate this term to a particular reaction.
            string rate_constant = (*termit)->getRateConstant();
            // Get the multiplicative constant
            C_FLOAT64 multiplier = (*termit)->getMultiplier();
            CReaction *reaction = findReaction(rate_constant);
            if (reaction == 0)
            {
                // This reaction hasn't been created yet. So do it.
                reaction = new CReaction(rate_constant);// XXX TODO: add the bits necessary
                string rate = expandRate(*termit);
                CKinFunction *fun = new CKinFunction();
                fun->setName(rate_constant);
                fun->setDescription(rate);
                fun->compile();
                Copasi->FunctionDB.add(fun);
                reaction->setFunction(rate_constant);
                // Now deduce the participating metabolites, and their multiplicity
                if (multiplier > 0)
                {
                    // The LHS metabolite is created in this reaction. 
                    // It may be autocatalytic (checked for later), or it 
                    // may be created by the reaction of other metabolites.
                    // We begin by assuming the latter.
                    addMetabolite(reaction, LHSmetab, multiplier, 0);
                }
                CMetabolite *metabolite = 0;
                C_INT32 multiplicity = 0;
                while ((metabolite = extractTopLevelMetabs(multiplicity)) != 0)
                {
                    if (metabolite == LHSMetab)
                    {
                        // check if it's autocatalytic
                        if (multiplier > 0)
                        {
                            adjustMetabolite(reaction, metab, multiplier + 1, multiplicity);
                        }
                        else
                        {
                            addMetabolite(reaction, metabolite, multiplicity);
                        }
                    }
                }
                else 
                {
                    // This reaction has already been created. We only need to set or adjust the 
                }
            }
        }
    }
}

vector<CDeTerm *> CSpec2Model::createTermStack(string str)
{
    istringstream *strstr = new istringstream(str);
    CScanInputFlexLexer scanner(strstr);
    C_INT32 type = 1;
    bool new = true;
    C_INT32 level = 0;
    vector<CDeTerm *> termstack;
    CDeTerm *determ;
    while (type = scanner.yylex())
    {
        if (new || ( (level == 0) && ( (type == CDeTerm::PLUS) || (type == CDeTerm::MINUS) ) ) )
        {
            // We're only at the beginning of a line once
            new = false;
            // Create and set the sign of a CDeTerm
            determ = new CDeTerm();
            termstack.push_back(determ);
            if ((type == CDeTerm::MINUS) || (type == CDeTerm::PLUS))
            {
                determ.setSign(scanner.YYTEXT());
            }
            else
            {
                level = adjustLevel(level, type);
                determ.add(type, scanner.YYTEXT());
            }
        }
        else
        {
            determ.add(scanner.YYTEXT());
            level = adjustLevel(level, type);
        }
        if (level < 0)
        {
            CCopasiMessage(CCopasiMessage::ERROR, "Error parsing differential equation");
        }
    }
    // Now, compile each term. i.e. extract the multiplier and rate constant
    vector<CDeTerm*>::iterator it = termstack.begin();
    for (; it != termstack.end(); it++)
    {
        (*it)->compile();
    }
}

C_INT32 CSpec2Model::adjustLevel(C_INT32 level, C_INT32 type)
{
    if (type == CDeTerm::LPAREN)
    {
        level++;
    }
    else if(type == CDeTerm::RPAREN)
    {
        level--
    }
    return level;
}

CMetab *CSpec2Model::getLHSMetab(CBaseEqn &beqn)
{
    return mModel->getCompartments()[beqn.getCompartment()]->metabolites()[beqn.getMetabolite()];
}

string CSpec2Model::expandRate(CDeTerm &term)
{
    // XXX TODO: expand functions and concatenate them
    // XXX At the moment, we just assume that there are no functions to expand
    return term.getDescription();
}

CReaction *CSpec2Model::findReaction(string)
{
    try
    {
        CReaction *retval = mModel->getReactions()[string];
        return retval;
    }
    catch(CCopasiException);
    return 0;
}

#endif // 0

C_INT32 CSpec2Model::parseLine(string) {return 0;}

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
