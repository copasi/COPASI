#include "copasi.h"
#include "utilities/utilities.h"
#include "CDeTerm.h"

CDeTerm::CDeTerm()
    : mSign(1),
      mMultiplier(1)
{}

CDeTerm::~CDeTerm()
{}

void CDeTerm::setSign(char sign)
{
    if (sign == '-')
    {
        mSign = -1;
    }
    else if (sign == '+')
    {
        mSign = 1;
    }
    else
    {
        CCopasiMessage(CCopasiMessage::ERROR, "Attempted to set sign to an unknown type: %c", sign);
    }
}

void CDeTerm::addElement(Type type, string token)
{
  mTokenStack.push_back(new pair<Type, string>(type, token));
}

void CDeTerm::deleteElement(C_INT32 index)
{
    vector <pair <Type,string>*>::iterator it = mTokenStack.begin() + index;
    if (*it)
    {
      delete mTokenStack[index];
      mTokenStack.erase(it);
    }
}

string CDeTerm::operator[](unsigned C_INT32 index)
{
    if (index >= mTokenStack.size())
    {
        CCopasiMessage(CCopasiMessage::ERROR, "Attempt to access CDeTerm token past end");
    }
    return mTokenStack[index]->second;
}

string CDeTerm::getDescription()
{
    string retval;
    vector<pair<Type,string>* >::iterator it = mTokenStack.begin();
    for (;it != mTokenStack.end(); it++)
    {
        retval += (*it)->first;
    }
    return retval;
}

void CDeTerm::compile(vector<CNameVal> &rates)
{
    // The multiplicative constant and the rate constant are both at level 0.
    // Here the level refers to the depth of nested parentheses
    C_INT32 level = 0;

    // For the multiplicative constant:
    // If it's at the end position, then we must remove the preceding '*', otherwise
    // we must remove the following '*'. If there is a '/' following, then we merely 
    // replace the multiplier with '1'. So we need the position.
    unsigned C_INT32 pos = 0;
    // Numbers which are exponents for metabolites should not be used as the multiplier!
    bool exponent = false;
    bool found_mult = false, found_rc = false;
    vector<pair<Type,string>* >::iterator it = mTokenStack.begin();
    for (; it != mTokenStack.end(), found_mult == false, found_rc == false; it++, pos++)
    {
        switch ((*it)->first)
        {
        case LPAREN:
            ++level;
            break;
        case RPAREN:
            --level;
            break;
        case EXPONENT:
            exponent = true;
            break;
        case NUM:
            if (exponent)
                exponent = false;
            else if ((level == 0) && (exponent == false))
            {
                // We've found the multiplier
                mMultiplier = atof((*it)->second.c_str());
                found_mult = true;
                if (pos < mTokenStack.size() - 1)
                {
                    // Check whether the following token is a '*' or a '/'
                    if (mTokenStack[pos]->first == MULT)
                    {
                        // Call delete twice, to remove the multiplier and '*'
                        deleteElement(pos);
                        deleteElement(pos); 
                    }
                    else if (mTokenStack[pos]->first == DIV)
                    {
                        // Replace the multiplier with 1
                        mTokenStack[pos]->second = "1";
                    }
                }
            }
            break;
        case IDENT:
            if (level == 0)
            {
                vector<CNameVal>::iterator nvit = rates.begin();
                for (; nvit != rates.end(); nvit++)
                {
                    if (nvit->getName() == (*it)->second)
                    {
                        // found the rate
                        mRateConstant = (*it)->second;
                    }
                }
            }
            break;
        default:
            break;
        }
    }
}
