#include <iostream>
#include <sstream>

#include "CSpecLine.h"
#include "utilities/CGlobals.h"

CSpecLine::CSpecLine() {CONSTRUCTOR_TRACE;}

CSpecLine::CSpecLine(C_INT32 type, string contents) 
    :mType(type), 
     mContents(contents) 
{CONSTRUCTOR_TRACE;}

CSpecLine::~CSpecLine() {DESTRUCTOR_TRACE;}

string CSpecLine::convertedType(int type)
{
    switch(type)
    {
    case CMNT: return "CMNT";
    case DE: return "DE";
    case EQN: return "EQN";
    case INIT: return "INIT";
    case CNST: return "CNST";
    case VOL: return "VOL";
    case CPT: return "CPT";
    case RATE: return "RATE";
    case FUN: return "FUN"; 
    default: return "Not a known type";
    }
}

string CSpecLine::extractLeft()
{
    // Find the operator position
    string::size_type op_pos = mContents.find_first_of('=');
    if (op_pos == string::npos || op_pos == 0)
    {
        // No operator like "=" or ":=", or LHS is empty, so LHS not defined
        return "";
    }
    else
    {
        if (mContents[op_pos - 1] == ':')
        {
            // We found the operator ":="
            --op_pos;
            if (op_pos == 0)
            {
                // LHS empty
                return "";
            }
        }
    }
    // Now find the start position. If the string begins with a 
    // compartment specification, use the end of that +1 as the 
    // start position; otherwise, use the string beginning.
    string ::size_type start_pos = mContents.find_first_of(':');
    if (start_pos == string::npos)
    {
        start_pos = 0;
    }
    else if (start_pos >= op_pos)
    {
        // invalid string
        return "";
    }
    else
    {
        start_pos++;
    }
    // Strip the leading blanks again
    start_pos = mContents.find_first_not_of(' ', start_pos);
    string tmp = stripBlanks(mContents.substr(start_pos, op_pos - start_pos));
    return tmp;
}

string CSpecLine::extractRight()
{
    string::size_type start_pos = mContents.find_first_of('=');
    if (start_pos == string::npos)
    {
        // No operator =, thus no RHS
        return "";
    }
    else
    {
//        cout << "Returning RHS = " << mContents.substr(start_pos+1) << endl;
        return mContents.substr(start_pos+1);
    }
}

string CSpecLine::extractCpt()
{
    string::size_type end_pos = mContents.find_first_of(':');
    if (mContents[end_pos + 1] == '=' || end_pos == string::npos)
    {
        // No compartment is specified
        return "";
    }
    // See if the first bit contains the keyword INIT or Init or init.
    // If it does, look for the compartment only after that
    string::size_type start_pos = mContents.find("INIT");
    if (start_pos == string::npos)
    {
        start_pos = mContents.find("init");
    }
    if (start_pos == string::npos)
    {
        start_pos = mContents.find("Init");
    }
    if (start_pos == string::npos)
    {
        start_pos = 0;
    }
    else 
    {
        start_pos = mContents.substr(start_pos).find_first_not_of("INITinit");
    }
    return stripBlanks(mContents.substr(start_pos, end_pos - start_pos));
}
        
string CSpecLine::stripBlanks(const string instr)
{
    string::size_type start_pos = instr.find_first_not_of(" \t");
    string::size_type end_pos = instr.find_last_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_/+-*:=");
    if (start_pos == string::npos || end_pos == string::npos)
    {
        // error
        return "";
    }
    return instr.substr(start_pos, end_pos - start_pos + 1);
}
    
bool CBaseEqn::operator==(const CBaseEqn &rhs) const
{
    if ((mCompartment == rhs.getCompartment()) &&
        (mMetabolite == rhs.getMetabolite()))
    {
        return true;
    }
    return false;
}

CTempMetab::CTempMetab(const CTempMetab &rhs)
    : mMetab(rhs.mMetab),
      mMultiplicity(rhs.mMultiplicity),
      mNumChange(rhs.mNumChange)
{}    

CTempMetab *CTempReaction::addMetabolite(CMetab *metab)
{
    // First try to find this metabolite on the existing stack
    for (unsigned C_INT32 i = 0; i < mMetabs.size(); i++)
    {
        if (mMetabs[i].getMetab()->getName() == metab->getName())
        {
            return &mMetabs[i];
        }
    }
    // If we get here, this metab has not yet been added
    CTempMetab *tmp_metab = new CTempMetab(metab);
    mMetabs.push_back(*tmp_metab);
    return tmp_metab;
}

void CTempReaction::compile(CModel *model)
{
    // Create the reaction
    CReaction *reaction = new CReaction(mName);// XXX TODO: add the bits necessary
    // Determine the substrates and products of the reaction
    CTempMetab *tmp_metab = 0;
    C_INT32 substrate_mult, product_mult, num_change;
    for (unsigned C_INT32 i = 0; i < mMetabs.size(); i++)
    {
        substrate_mult = mMetabs[i].getMultiplicity();
        num_change = mMetabs[i].getNumChange();
        product_mult =  substrate_mult + num_change;
        if (substrate_mult > 0)
        {
            tmp_metab = new CTempMetab(mMetabs[i]);
            mSubstrates.push_back(*tmp_metab);
        }
        if (product_mult > 0)
        {
            tmp_metab = new CTempMetab(mMetabs[i]);
            tmp_metab->setMultiplicity(product_mult);
            mProducts.push_back(*tmp_metab);
        }
    }
    // Create strings describing the chemical equation
    ostringstream lhs_desc;
    ostringstream rhs_desc;
    C_INT32 mult = 0;
    bool is_first;
    is_first = true;
    for (unsigned C_INT32 i = 0; i < mSubstrates.size(); i++)
    {
        mult = mSubstrates[i].getMultiplicity();
        if (is_first == false)
        {
            lhs_desc << "+";
        }
        is_first = false;
        if (mult > 1)
        {
            lhs_desc << substrate_mult << "*";
        }
        lhs_desc << mSubstrates[i].getMetab()->getName();
    }
    is_first = true;
    for (unsigned C_INT32 i = 0; i < mProducts.size(); i++)
    {
        mult = mProducts[i].getMultiplicity();
        if (is_first == false)
        {
            rhs_desc << "+";
        }
        is_first = false;
        if (mult > 1)
        {
            rhs_desc << mult + "*";
        }
        rhs_desc << mProducts[i].getMetab()->getName();
    }
    string chemeqdesc = lhs_desc.str() + "->" + rhs_desc.str();
    // Set the chemical equation description in the reaction. This
    // automatically parses the description, extracts the metabolites
    // and constructs the chemical equations.
    reaction->setChemEq(chemeqdesc);
    // Set up the kinetic function, and add it to the database
    CKinFunction *fun = new CKinFunction();
    fun->setName(mName);
    fun->setDescription(mRateDescription);
    fun->compile();
    Copasi->FunctionDB.loadedFunctions().add(*fun);
    // Associate this kinetic function with the reaction
    reaction->setFunction(mName);
    // Finally, add the reaction to the model
    model->getReactions().add(reaction);
}    

CTempReactionSet::CTempReactionSet() {}

void CTempReactionSet::addReaction(CTempReaction *tempreact)
{
    mReactions.push_back(*tempreact);
}

CTempReaction *CTempReactionSet::findReaction(string name)
{
    for (unsigned C_INT32 i = 0; i < mReactions.size(); i++)
    {
        if (name == mReactions[i].getName())
        {
            return &mReactions[i];
        }
    }
    return 0; // If we get here, we didn't find it
}


