#include "CSpecLine.h"

CSpecLine::CSpecLine(C_INT32 type, string contents) 
    :mType(type), 
     mContents(contents) 
{}

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
