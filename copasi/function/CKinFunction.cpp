/**
 * CKinFunction
 *
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2002
 */

#define COPASI_TRACE_CONSTRUCTION
#include "CKinFunction.h"

#undef yyFlexLexer
#define yyFlexLexer CKinFunctionFlexLexer
#include <FlexLexer.h>

#include <sstream>
// #include "lexkk.h"

CKinFunction::CKinFunction() : CFunction()
{  
  CONSTRUCTOR_TRACE;
  setType(CFunction::UserDefined);
}

CKinFunction::CKinFunction(const CFunction & src) : CFunction(src)
{
  CONSTRUCTOR_TRACE;
  compile();
}

CKinFunction::CKinFunction(const CKinFunction & src) : CFunction(src)
{
  CONSTRUCTOR_TRACE;
  compile();
}

#ifdef XXXX
CKinFunction::CKinFunction(const string & name,
                           const string & description)
{
  CONSTRUCTOR_TRACE;
  setType(CFunction::UserDefined);
  setName(name);
  setDescription(description);
}
#endif // XXXX

CKinFunction::~CKinFunction() {cleanup(); DESTRUCTOR_TRACE;}

void CKinFunction::cleanup()
{
  mNodes.cleanup();
  CFunction::cleanup();
}

void CKinFunction::load(CReadConfig & configBuffer,
                        CReadConfig::Mode mode)
{
  CFunction::load(configBuffer, mode);

  // For older file version the parameters have to be build from information
  // dependend on the function type. Luckilly, only user defined functions are
  // the only ones occuring in those files.
  if (configBuffer.getVersion() < "4")
    {
      unsigned C_INT32 Size;
      configBuffer.getVariable("Nodes", "C_INT32", &Size);

      mNodes.load(configBuffer, Size);
      createParameters();
      mNodes.cleanup();
    }

  compile();
}

void CKinFunction::compile()
{
  mNodes.cleanup();
  parse();
  connectNodes();
  initIdentifierNodes();
}

C_INT32 CKinFunction::parse()
{
  int i = 1;
  istringstream buffer(getDescription());
  CKinFunctionFlexLexer Scanner(&buffer);

  // add the root node
  mNodes.add(CNodeK(N_ROOT, N_NOP));

  // call the lexical analyser successively until done
  while (i)
    {
      i = Scanner.yylex();
      switch (i)
        {
        case N_IDENTIFIER: mNodes.add(CNodeK(Scanner.YYText())); break;
        case N_NUMBER:     mNodes.add(CNodeK(atof(Scanner.YYText()))); break;
        case '+':          mNodes.add(CNodeK(N_OPERATOR, '+')); break;
        case '-':          mNodes.add(CNodeK(N_OPERATOR, '-')); break;
        case '*':          mNodes.add(CNodeK(N_OPERATOR, '*')); break;
        case '/':          mNodes.add(CNodeK(N_OPERATOR, '/')); break;
        case '^':          mNodes.add(CNodeK(N_OPERATOR, '^')); break;
        case '(':          mNodes.add(CNodeK(N_OPERATOR, '(')); break;
        case ')':          mNodes.add(CNodeK(N_OPERATOR, ')')); break;
        case N_LOG:        mNodes.add(CNodeK(N_FUNCTION, N_LOG)); break;
        case N_LOG10:      mNodes.add(CNodeK(N_FUNCTION, N_LOG10)); break;
        case N_EXP:        mNodes.add(CNodeK(N_FUNCTION, N_EXP)); break;
        case N_SIN:        mNodes.add(CNodeK(N_FUNCTION, N_SIN)); break;
        case N_COS:        mNodes.add(CNodeK(N_FUNCTION, N_COS)); break;
        case N_NOP:        // this is an error
	  mNodes.cleanup();
          /* :TODO: create a valid error message returning the eroneous node */
          fatalError();
	  return 0;
        }
    }
  return 0;
}

C_FLOAT64 CKinFunction::calcValue(const CCallParameters & callParameters) const
{return mNodes[0]->getLeft().value(callParameters);}

C_INT32 CKinFunction::connectNodes()
{
  C_INT32 errfl = 0;     // !!! do we need this?
  C_INT32 errnode = -1;  // !!! do we need this?
  unsigned C_INT32 i;

  // initialise the control variables
  mNidx = 1;

  // point all Left & Right to the root node
  for (i=1; i<mNodes.size(); i++)
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

  for (i=1; i<mNodes.size() && !errfl; i++)
    {
      switch (mNodes[i]->getType())
        {
        case N_OPERATOR:
	  if (!mNodes[i]->isLeftValid()      ||
	      !mNodes[i]->isRightValid()     ||
	      &mNodes[i]->getLeft()  == mNodes[0] ||
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
	      if (mNodes[i]->isLeftValid()    &&
		  mNodes[i]->getLeft().isOperator() &&
		  mNodes[i]->getLeft().getSubtype() == '(' )
                {
		  //           sprintf(errstr, "ERROR - missing operand");
		  fatalError();
		  errnode = -1;
		  errfl++;
                }
	      if (mNodes[i]->isRightValid()    &&
		  mNodes[i]->getRight().isOperator() &&
		  mNodes[i]->getRight().getSubtype() == ')' )
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
	      mNodes[i]->isRightValid()  )
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
	      mNodes[i]->isRightValid()  )
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

CNodeK * CKinFunction::parseExpression(C_INT16 priority)
{
  C_INT32 errfl = 0;     // !!! do we need this?
  C_INT32 errnode = -1;  // !!! do we need this?

  CNodeK *lhs, *rhs;
  C_INT32 op;

  lhs = parsePrimary();
  if (!lhs) return NULL;

  while( mNidx < mNodes.size() &&
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
	  lhs = mNodes[op] ;
        }
    }
  return lhs;
}

CNodeK * CKinFunction::parsePrimary()
{
  C_INT32 errfl = 0;     // !!! do we need this?
  C_INT32 errnode = -1;  // !!! do we need this?

  CNodeK *npt, *primary;
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

  if (mNodes[mNidx]->isNumber() ||
      mNodes[mNidx]->isIdentifier())
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
    case '(': ++mNidx;
      npt = parseExpression(0);
      if (mNidx < mNodes.size()      &&
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
    case N_COS:   op = mNidx; primary = NULL;
      ++mNidx;
      primary = parsePrimary();
      if (primary==NULL)
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
    default:  return NULL;
    }
  if (mNidx < mNodes.size()      &&
      mNodes[mNidx]->isOperator() &&
      mNodes[mNidx]->getSubtype() == '(')
    {
      ++mNidx;
      if (mNidx < mNodes.size()      &&
	  mNodes[mNidx]->isOperator() &&
	  mNodes[mNidx]->getSubtype() == ')')
        {
	  mNodes[mNidx]->setLeft(npt);
	  mNodes[mNidx]->setRight(NULL);
	  return mNodes[mNidx];
        }
      else parseExpression(0);
    }
}

void CKinFunction::createParameters()
{

  CCopasiVectorN < CFunctionParameter > Substrates;
  CCopasiVectorN < CFunctionParameter > Products;
  CCopasiVectorN < CFunctionParameter > Modifiers;
  CCopasiVectorN < CFunctionParameter > Parameters;

  unsigned C_INT32 i, imax = mNodes.size();
  
  CFunctionParameter Parameter;
  Parameter.setType(CFunctionParameter::FLOAT64);
  
  for (i=0; i<imax; i++)
    {
      if (mNodes[i]->getType() == N_IDENTIFIER)
        {
          try
            {
              Parameter.setName(mNodes[i]->getName());
              
              switch (mNodes[i]->getSubtype())
                {
                case N_SUBSTRATE:
                  Parameter.setUsage("SUBSTRATE");
                  Substrates.add(Parameter);
                  break;
                case N_PRODUCT:
                  Parameter.setUsage("PRODUCT");
                  Products.add(Parameter);
                  break;
                case N_MODIFIER:
                  Parameter.setUsage("MODIFIER");
                  Modifiers.add(Parameter);
                  break;
                case N_KCONSTANT:
                  Parameter.setUsage("PARAMETER");
                  Parameters.add(Parameter);
                  break;
                case N_NOP:
                  Parameter.setUsage("UNKNOWN");
                  Parameters.add(Parameter);
                  break;
                default:
                  fatalError();
                }
            }

          catch (CCopasiException Exception)
            {
              if ((MCCopasiVector + 2) != Exception.getMessage().getNumber())
                throw Exception;
            }
        }
    }

  imax = Substrates.size();
  for (i=0; i<imax; i++)
      getParameters().add(Substrates[i]);

  imax = Products.size();
  for (i=0; i<imax; i++)
      getParameters().add(Products[i]);

  imax = Modifiers.size();
  for (i=0; i<imax; i++)
      getParameters().add(Modifiers[i]);

  imax = Parameters.size();
  for (i=0; i<imax; i++)
      getParameters().add(Parameters[i]);

}

void CKinFunction::initIdentifierNodes()
{
  // CCopasiVectorNS < CFunctionParameter > * BaseParameters;
  // BaseParameters = &getParameters().getParameters();

  string IdentifierName, ParameterName, Usage;

  unsigned C_INT32 i, imax = getParameters().size();
  unsigned C_INT32 j, jmax = mNodes.size();
  
  for (j=0; j<jmax; j++)
    {
      if (mNodes[j]->getType() != N_IDENTIFIER) continue;
      IdentifierName = mNodes[j]->getName();
      
      for (i=0; i<imax; i++)
        {
          ParameterName = getParameters()[i]->getName();
          if (IdentifierName != ParameterName) continue;
          
          mNodes[j]->setIndex(i);
          break;
          
          // We really do not need the usage information in the binary
          // tree anymore. 
          Usage = getParameters()[i]->getUsage();
          if      (Usage == "SUBSTRATE") mNodes[j]->setSubtype(N_SUBSTRATE);
          else if (Usage == "PRODUCT")   mNodes[j]->setSubtype(N_PRODUCT);
          else if (Usage == "MODIFIER")  mNodes[j]->setSubtype(N_MODIFIER);
          else if (Usage == "PARAMETER") mNodes[j]->setSubtype(N_KCONSTANT);
          else if (Usage == "UNKNOWN")   mNodes[j]->setSubtype(N_NOP);
          else    fatalError();
          
          break;
        }
      if (i == imax) fatalError();
    }
}

CCopasiVectorS < CNodeK > & CKinFunction::getNodes() {return mNodes;}

