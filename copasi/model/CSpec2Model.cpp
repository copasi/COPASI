#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "copasi.h"
#include "model.h"
#include "utilities/utilities.h"
//#include "utilities/CCopasiMessage.h"
#include "CSpecLine.h"

#undef yyFlexLexer
#define yyFlexLexer CScanInputFlexLexer

#include "function/FlexLexer.h"

CSpec2Model::CSpec2Model()
{}

CSpec2Model::CSpec2Model(std::string filename)
{
    mSpecFileName = filename;
}

CSpec2Model::~CSpec2Model()
{}

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
//     processDETerms();
    return mModel;
}

void CSpec2Model::determineType(string str)
{
    istringstream *strstr = new istringstream(str);
    CScanInputFlexLexer scanner(strstr);
//    yyFlexLexer scanner(strstr);
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
    
    for (vector<CSpecLine>::iterator it = mSpecLines.begin(); it < mSpecLines.end(); it++)
    {
        if (it->getType() == CSpecLine::DE)
        {
            string comp_name = it->extractCpt();
            string metab = it->extractLeft();
            string contents = it->extractRight();
            CBaseEqn tmp(comp_name, metab, contents);
            mReactVector.push_back(tmp);
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

    for (vector<CBaseEqn>::iterator itb = mReactVector.begin(); itb < mReactVector.end(); it++)
    {
        cout << "Added DE " << itb->getMetabolite();
        cout << " in compartment " << itb->getCompartment();
        cout << " with RHS = " << itb->getContents() << endl;
    }

    for (vector<CBaseEqn>::iterator itc = mMoietyVector.begin(); itc < mMoietyVector.end(); it++)
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
            vector<CBaseEqn>::iterator vit = find(mReactVector.begin(), mReactVector.end(), tmp);
            if (vit != mReactVector.end())
            {
                // this does correspond to a reactant.
                CMetab metab(metab_name);
                metab.setCompartment( mModel->getCompartments()[comp_name]);
                metab.setStatus(METAB_VARIABLE);
                C_FLOAT64 iconc = atof(contents.c_str());
                metab.setInitialConcentration(iconc);
                metab.setConcentration(iconc);    // XXX TODO: is this neccessary?
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
            string metab_name = it->extractLeft();
            string contents = it->extractRight();
            CMetab *metab = new CMetab(metab_name);
            metab->setStatus(METAB_FIXED);
            metab->setInitialConcentration(atof(contents.c_str()));
            metab->setConcentration(atof(contents.c_str()));
            mModel->getMetabolites().push_back(metab); // XXX TODO: is this the right place to store these?
            cout << "For fixed metabolite " << 
                mModel->getMetabolites()[mModel->getMetabolites().size() -1]->getName();
            cout << " set init concentration to " << *mModel->getMetabolites()[mModel->getMetabolites().size() -1]->getInitialConcentration() << endl;
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
            string contents = it->extractRight();
        }
    }            
}

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
