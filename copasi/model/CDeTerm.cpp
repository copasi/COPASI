#include "copasi.h"
#include "CDeTerm.h"

#include "utilities/CCopasiMessage.h"

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

void CDeTerm::deleteElement(std::vector< std::pair <Type, std::string>*>::iterator it)
{
  if (*it)
    {
      delete (*it);
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

std::string CDeTerm::getDescription() const
  {
    std::string retval;
    std::vector< std::pair< Type, std::string>* >::const_iterator it = mTokenStack.begin();

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
  // replace the multiplier with '1'.

  bool mc_found = false; // to check if several multiplicative constants are in the term
  bool rate_found = false; // to check if several rate constants are in the term
  std::pair< std::string, C_INT32> * last_metab = NULL;
  std::vector< std::pair< Type, std::string>* >::iterator it = mTokenStack.begin();

  bool is_first_token = true;
  bool is_multiplier;
  bool should_inc_it;

  for (; it < mTokenStack.end();)
    {
      should_inc_it = true;

      switch ((*it)->first)
        {
        case LPAREN:
          ++level;
          break;

        case RPAREN:
          --level;
          break;

        case EXPONENT:
          if ((it + 1) >= mTokenStack.end())
            {
              std::cout << "ERROR" << std::endl; //ERROR: '^' at the end of a term
            }
          break;

        case NUM:

          // check if the number is a top level multiplicative constant
          is_multiplier = false;
          if (level == 0)
            {
              if (is_first_token == true)
                {
                  is_multiplier = true;
                }
              else if ((*(it - 1))->first == MULT)
                {
                  is_multiplier = true;
                }
              else if ((*(it - 1))->first == EXPONENT)
                {
                  // NUM is top level exponent
                  if (last_metab)
                    last_metab->second = atoi((*it)->second.c_str());
                }
            }
          if (is_multiplier)
            {
              if (mc_found == true)
                {
                  std::cout << "ERROR" << std::endl; //Error: several multiplier in term
                }

              mMultiplier = atof((*it)->second.c_str());
              mc_found = true;
              if (is_first_token == true)
                {
                  // Check whether the following token is a '*' or a '/'
                  if ((*(it + 1))->first == MULT)
                    {
                      // Call delete twice, to remove the multiplier and '*'
                      deleteElement(it);
                      deleteElement(it);
                      should_inc_it = false;
                    }
                  else if ((*(it + 1))->first == DIV)
                    {
                      // Replace the multiplier with 1
                      (*it)->second = "1";
                    }
                }
              else // not first token
                {
                  it--;
                  deleteElement(it);
                  deleteElement(it);
                  should_inc_it = false;
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
                      if (rate_found == true)
                        {
                          std::cout << "ERROR" << std::endl; //Error: several rate constants in term
                        }
                      // found the rate
                      // todo: check if rc is multiplicative
                      mRateConstant = (*it)->second;
                      rate_found = true;
                      break;
                    }
                }

              if (nvit == rates.end())
                {
                  // If it's not a rate constant, it must be a metabolite or a constant?
                  std::pair< std::string, C_INT32> *metab_pair = new std::pair< std::string, C_INT32>((*it)->second, 1);
                  mTopLevelMetabolites.push_back(metab_pair);
                  last_metab = metab_pair;
                  // todo: check the surroundings
                }
            }

          break;

        default:
          break;
        }
      is_first_token = false;

      if (should_inc_it) it++; // in some cases it should not be increased
    }

  if (rate_found == false)
    {
      std::cout << "ERROR" << std::endl; //Error: no rate constant found
    }
}

std::string CDeTerm::getTopLevelMetabolite(unsigned C_INT32 pos, C_INT32 &multiplicity) const
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
