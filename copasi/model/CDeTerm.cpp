#include "copasi.h"

#include "utilities/utilities.h"
#include "CDeTerm.h"

CDeTerm::CDeTerm()
    : mSign(1),
    mMultiplier(1)
{}

CDeTerm::~CDeTerm()
{}

void CDeTerm::setSign(const char *sign)
{
  if (*sign == '-')
    {
      mSign = -1;
    }
  else if (*sign == '+')
    {
      mSign = 1;
    }
  else
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Attempted to set sign to an unknown type: %c", sign);
    }
}

void CDeTerm::addElement(Type type, std::string token)
{
  std::string::size_type Begin = token.find_first_not_of(" \t");
  std::string::size_type End = token.find_last_not_of(" \t");
  mTokenStack.push_back(new std::pair<Type, std::string>(type, token.substr(Begin, End - Begin + 1)));
}

void CDeTerm::deleteElement(C_INT32 index)
{
  std::vector< std::pair <Type, std::string>*>::iterator it = mTokenStack.begin() + index;

  if (*it)
    {
      delete mTokenStack[index];
      mTokenStack.erase(it);
    }
}

std::string CDeTerm::operator[](unsigned C_INT32 index)
{
  if (index >= mTokenStack.size())
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Attempt to access CDeTerm token past end");
    }

  return mTokenStack[index]->second;
}

std::string CDeTerm::getDescription()
{
  std::string retval;
  std::vector< std::pair< Type, std::string>* >::iterator it = mTokenStack.begin();

  for (; it != mTokenStack.end(); it++)
    {
      retval += (*it)->second;
    }

  return retval;
}

void CDeTerm::compile(std::vector<CNameVal> &rates)
{
  // The multiplicative constant and the rate constant are both at level 0.
  // Here the level refers to the depth of nested parentheses
  C_INT32 level = 0;

  // For the multiplicative constant:
  // If it's at the end position, then we must remove the preceding '*', otherwise
  // we must remove the following '*'. If there is a '/' following, then we merely
  // replace the multiplier with '1'. So we need the position.
  unsigned C_INT32 pos = 0;
  // Make sure we don't use numbers which are exponents for metabolites as the multiplier!
  bool is_exponent = false;
  std::pair< std::string, C_INT32> *last_metab;
  std::vector< std::pair< Type, std::string>* >::iterator it = mTokenStack.begin();

  for (; it != mTokenStack.end(); it++, pos++)
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

          if (level == 0)
            is_exponent = true;

          break;

        case NUM:

          if (is_exponent)
            {
              is_exponent = false;
              last_metab->second = atoi((*it)->second.c_str());
            }

          else if ((level == 0) && (is_exponent == false))
            {
              // We've found the multiplier
              mMultiplier = atof((*it)->second.c_str());

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
              std::vector<CNameVal>::iterator nvit = rates.begin();

              for (; nvit != rates.end(); nvit++)
                {
                  if (nvit->getName() == (*it)->second)
                    {
                      // found the rate
                      mRateConstant = (*it)->second;
                      break;
                    }
                }

              if (nvit == rates.end())
                {
                  // If it's not a rate constant, it must be a metabolite
                  std::pair< std::string, C_INT32> *metab_pair = new std::pair< std::string, C_INT32>((*it)->second, 1);
                  mTopLevelMetabolites.push_back(metab_pair);
                  last_metab = metab_pair;
                }
            }

          break;

        default:
          break;
        }
    }
}

std::string CDeTerm::getTopLevelMetabolite(unsigned C_INT32 pos, C_INT32 &multiplicity)
{
  std::string retstring;

  if (pos < mTopLevelMetabolites.size())
    {
      multiplicity = mTopLevelMetabolites[pos]->second;
      retstring = mTopLevelMetabolites[pos]->first;
    }
  else
    retstring = "";

  return retstring;
}
