/*****************************************************************************
 * PROGRAM NAME: CUDFunction.cpp
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: Implement the user defined function object
 *****************************************************************************/

#define COPASI_TRACE_CONSTRUCTION

#undef yyFlexLexer
#define yyFlexLexer CKinFunctionFlexLexer

#include <sstream>
#include <iostream>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "FlexLexer.h"
#include "CNodeO.h"
#include "CUDFunction.h"
#include "utilities/CGlobals.h"
#include "utilities/CCopasiException.h"

/**
 *  Default constructor
 */
CUDFunction::CUDFunction(const std::string & name,
                         const CCopasiContainer * pParent):
    CKinFunction(name, pParent)
{
  CONSTRUCTOR_TRACE;
  setType(CFunction::Output);
}

CUDFunction::CUDFunction(const CFunction & src,
                         const CCopasiContainer * pParent):
    CKinFunction(src, pParent)
{CONSTRUCTOR_TRACE;}

CUDFunction::CUDFunction(const CUDFunction & src,
                         const CCopasiContainer * pParent):
    CKinFunction(src, pParent)
{CONSTRUCTOR_TRACE;}

/**
 *  This creates a user defined function with a name an description
 *  @param "const string" &name
 *  @param "const string" &description
 */
CUDFunction::CUDFunction(const std::string & name,
                         const std::string & description,
                         const CCopasiContainer * pParent):
    CKinFunction(name, pParent)
{
  CONSTRUCTOR_TRACE;
  setType(CFunction::Output);
  setName(name);
  setDescription(description);
}

/**
 *  Destructor
 */
CUDFunction::~CUDFunction() {cleanup(); DESTRUCTOR_TRACE;}

/**
 *  Delete
 */
void CUDFunction::cleanup()
{
  cleanupNodes();

  CFunction::cleanup();
}

#ifdef XXXX 
/**
 *  Copy
 */
void CUDFunction::copy(const CUDFunction & in)
{
  CBaseFunction::copy(in);

  mNodes = CVector< CNodeO * > (in.mNodes);

  mNidx = in.mNidx;

  connectNodes();
}

#endif // XXXX

/**
 *  Loads an object with data coming from a CReadConfig object.
 *  (CReadConfig object reads an input stream)
 *  @param pconfigbuffer reference to a CReadConfig object.
 *  @return Fail
 */
void CUDFunction::load(CReadConfig & configbuffer,
                       CReadConfig::Mode mode)
{
  C_INT32 Size = 0;
  std::string Name, Description;

  if (configbuffer.getVersion() < "4")
    {
      configbuffer.getVariable("Name", "string", &Name, mode);
      setName(Name);

      configbuffer.getVariable("Description", "string", &Description);
      setDescription(Description);

      setType(CFunction::Output);
    }
  else
    CFunction::load(configbuffer, mode);

  parse();

  if (configbuffer.getVersion() < "4")
    {
      configbuffer.getVariable("Nodes", "C_INT32", &Size);

      mNodes.resize(Size);

      C_INT32 i;
      for (i = 0; i < Size; i++)
        {
          mNodes[i] = new CNodeO;
          mNodes[i]->load(configbuffer);
        }

      createParameters();
      //mNodes.cleanup();  // create exception
    }

  //compile();
  //parse();
  connectNodes();

  return;
}

void CUDFunction::createParameters()
{
  CCopasiVectorN < CFunctionParameter > Data;

  unsigned C_INT32 i, imax = mNodes.size();

  CFunctionParameter Parameter;
  Parameter.setType(CFunctionParameter::FLOAT64);

  for (i = 0; i < imax; i++)
    {
      if (mNodes[i]->getType() == N_IDENTIFIER)
        {
          try
            {
              Parameter.setName(getNodes()[i]->getName());
              Parameter.setUsage(mNodes[i]->getDatum().getObject());
              Data.add(Parameter);
            }

          catch (CCopasiException Exception)
            {
              if ((MCCopasiVector + 2) != Exception.getMessage().getNumber())
                throw Exception;
            }
        }
    }

  imax = Data.size();

  for (i = 0; i < imax; i++)
    getParameters().add(Data[i]);
}

/**
 * Calculate the value of this user defined function
 * return the pointer of this user defined function
 */
C_FLOAT64 CUDFunction::calcValue()
{
  mValue = mNodes[0]->getLeft().value();
  return mValue;
}

/**
 * Get the pointer of user defined functions
 */
void * CUDFunction::getValueAddr()
{
  return &mValue;
}

/**
 * Return the value of user defined function
 */
C_FLOAT64 CUDFunction::getValue() const
  {
    return mValue;
  }

C_INT32 CUDFunction::connectNodes()
{
  C_INT32 errfl = 0;     // !!! do we need this?
  C_INT32 errnode = -1;  // !!! do we need this?
  unsigned C_INT32 i;

  // initialise the control variables
  mNidx = 1;

  // point all Left & Right to the root node

  for (i = 1; i < mNodes.size(); i++)
    {
      mNodes[i]->setLeft(mNodes[0]);
      mNodes[i]->setRight(mNodes[0]);
    }

  // update pointers and references in the tree
  mNodes[0]->setLeft(parseExpression(0));

  // further checking for errors
  if (mNodes[0]->isLeftValid() &&
      mNodes[0]->getLeft().isOperator() &&
      mNodes[0]->getLeft().getSubtype() == '(')
    {
      //  sprintf(errstr, "ERROR - missing operand");
      //  errnode should index the node in error
      //  but we don't know its index (pointer only)
      CCopasiMessage(CCopasiMessage::ERROR, MCKinFunction + 2,
                     getName().c_str());
      errnode = -1;
      errfl++;
    }

  for (i = 1; i < mNodes.size() && !errfl; i++)
    {
      switch (mNodes[i]->getType())
        {
        case N_OPERATOR:

          if (!mNodes[i]->isLeftValid() ||
              !mNodes[i]->isRightValid() ||
              &mNodes[i]->getLeft() == mNodes[0] ||
              &mNodes[i]->getRight() == mNodes[0])
            if (mNodes[i]->getSubtype() != '(' &&
                mNodes[i]->getSubtype() != ')')
              {
                if (!errfl)
                  {
                    // sprintf(errstr, "ERROR - incorrect number of operands");
                    fatalError();
                    errnode = i;
                  }

                errfl++;
              }

          if (!errfl)
            {
              if (mNodes[i]->isLeftValid() &&
                  mNodes[i]->getLeft().isOperator() &&
                  mNodes[i]->getLeft().getSubtype() == '(')
                {
                  //           sprintf(errstr, "ERROR - missing operand");
                  fatalError();
                  errnode = -1;
                  errfl++;
                }

              if (mNodes[i]->isRightValid() &&
                  mNodes[i]->getRight().isOperator() &&
                  mNodes[i]->getRight().getSubtype() == ')')
                {
                  //           sprintf(errstr, "ERROR - missing operand");
                  fatalError();
                  errnode = -1;
                  errfl++;
                }
            }

          break;

        case N_IDENTIFIER:

          if (mNodes[i]->isLeftValid() ||
              mNodes[i]->isRightValid())
            {
              if (!errfl)
                {
                  //           sprintf(errstr, "ERROR - unexpected identifier");
                  fatalError();
                  errnode = -1;
                }

              ++errfl;
            }

          break;

        case N_NUMBER:

          if (mNodes[i]->isLeftValid() ||
              mNodes[i]->isRightValid())
            {
              if (!errfl)
                {
                  //           sprintf(errstr, "ERROR - unexpected constant");
                  fatalError();
                  errnode = -1;
                }

              ++errfl;
            }

          break;
        }
    }

  // return
  return errfl;
}

CNodeO * CUDFunction::parseExpression(C_INT16 priority)
{
  C_INT32 errfl = 0;     // !!! do we need this?
  C_INT32 errnode = -1;  // !!! do we need this?

  CNodeO *lhs, *rhs;
  C_INT32 op;

  lhs = parsePrimary();

  if (!lhs)
    return NULL;

  while (mNidx < mNodes.size() &&
         mNodes[mNidx]->isOperator() &&
         priority < mNodes[mNidx]->leftPrecedence())
    {
      op = mNidx;
      rhs = NULL;
      ++mNidx;
      rhs = parseExpression(mNodes[op]->rightPrecedence());

      if (!rhs)
        {
          if (!errfl)
            {
              //    sprintf(errstr, "ERROR - unexpected operator");
              fatalError();
              errnode = op;
            }

          ++errfl;
        }
      else
        {
          mNodes[op]->setLeft(lhs);
          mNodes[op]->setRight(rhs);
          lhs = mNodes[op];
        }
    }

  return lhs;
}

CNodeO * CUDFunction::parsePrimary()
{
  C_INT32 errfl = 0;     // !!! do we need this?
  C_INT32 errnode = -1;  // !!! do we need this?

  CNodeO *npt, *primary;
  char t;
  C_INT32 op;
  npt = NULL;

  //    if (Node[mNidx]==NULL)

  if (mNidx >= mNodes.size())
    {
      //  if (!errfl) // execute only if no previous error
      //   errnode = mNidx-1;
      //  errfl++;
      return NULL;
    }

  t = mNodes[mNidx]->getType();
  if (t == N_IDENTIFIER ||
      t == N_OBJECT ||
      t == N_NUMBER)
    {
      t = 'K';
    }
  else
    {
      t = mNodes[mNidx]->getSubtype();
    }

  switch (t)
    {
    case 'K':
      mNodes[mNidx]->setLeft(NULL);
      mNodes[mNidx]->setRight(NULL);
      npt = mNodes[mNidx];
      ++mNidx;
      return npt;

    case '(':
      ++mNidx;
      npt = parseExpression(0);

      if (mNidx < mNodes.size() &&
          mNodes[mNidx]->isOperator() &&
          mNodes[mNidx]->getSubtype() == ')')
        {
          ++mNidx;
          return npt;
        }
      else
        {
          if (!errfl) // execute only if no previous error
            {
              //             sprintf(errstr, "ERROR - right bracket missing");
              errnode = mNidx;
            }

          errfl++;
        }

    case '+':

    case '-':

    case N_LOG:

    case N_LOG10:

    case N_EXP:

    case N_SIN:

    case N_COS:
      op = mNidx;
      primary = NULL;
      ++mNidx;
      primary = parsePrimary();

      if (primary == NULL)
        {
          if (!errfl)
            {
              //                  sprintf(errstr, "ERROR - missing operator");
              errnode = op;
            }

          ++errfl;
        }
      else
        {
          npt = mNodes[op];
          // unary operators are taken as functions
          mNodes[op]->setType(N_FUNCTION);
          mNodes[op]->setLeft(primary);
          mNodes[op]->setRight(NULL);
          return mNodes[op];
        }

    default:
      return NULL;
    }

  if (mNidx < mNodes.size() &&
      mNodes[mNidx]->isOperator() &&
      mNodes[mNidx]->getSubtype() == '(')
    {
      ++mNidx;

      if (mNidx < mNodes.size() &&
          mNodes[mNidx]->isOperator() &&
          mNodes[mNidx]->getSubtype() == ')')
        {
          mNodes[mNidx]->setLeft(npt);
          mNodes[mNidx]->setRight(NULL);
          return mNodes[mNidx];
        }
      else
        parseExpression(0);
    }
}
std::vector< CNodeO * > & CUDFunction::getNodes() {return mNodes;}

void CUDFunction::compile()
{
  cleanupNodes();
  parse();
  connectNodes();
}

C_INT32 CUDFunction::parse()
{
  int i = 1;
  std::istringstream buffer(getDescription());
  CKinFunctionFlexLexer Scanner((std::istream *) &buffer);

  // add the root node
  mNodes.push_back(new CNodeO(N_ROOT, N_NOP));

  // call the lexical analyser successively until done

  while (i)
    {
      i = Scanner.yylex();

      switch (i)
        {
        case N_IDENTIFIER:
          mNodes.push_back(new CNodeO(Scanner.YYText()));
          break;

        case N_NUMBER:
          mNodes.push_back(new CNodeO(atof(Scanner.YYText())));
          break;

        case '+':
          mNodes.push_back(new CNodeO(N_OPERATOR, '+'));
          break;

        case '-':
          mNodes.push_back(new CNodeO(N_OPERATOR, '-'));
          break;

        case '*':
          mNodes.push_back(new CNodeO(N_OPERATOR, '*'));
          break;

        case '/':
          mNodes.push_back(new CNodeO(N_OPERATOR, '/'));
          break;

        case '^':
          mNodes.push_back(new CNodeO(N_OPERATOR, '^'));
          break;

        case '(':
          mNodes.push_back(new CNodeO(N_OPERATOR, '('));
          break;

        case ')':
          mNodes.push_back(new CNodeO(N_OPERATOR, ')'));
          break;

        case N_LOG:
          mNodes.push_back(new CNodeO(N_FUNCTION, N_LOG));
          break;

        case N_LOG10:
          mNodes.push_back(new CNodeO(N_FUNCTION, N_LOG10));
          break;

        case N_EXP:
          mNodes.push_back(new CNodeO(N_FUNCTION, N_EXP));
          break;

        case N_SIN:
          mNodes.push_back(new CNodeO(N_FUNCTION, N_SIN));
          break;

        case N_COS:
          mNodes.push_back(new CNodeO(N_FUNCTION, N_COS));
          break;

        case N_NOP:              // this is an error
          cleanupNodes();
          /* :TODO: create a valid error message returning the eroneous node */
          fatalError();
          return 0;
        }
    }

  return 0;
}

void CUDFunction::cleanupNodes()
{
  unsigned C_INT32 i, imax = mNodes.size();

  for (i = 0; i < imax; i++)
    if (mNodes[i]) delete mNodes[i];

  mNodes.clear();

  return;
}
