// UDKType.cpp : classes for user-defined kinetic types
//
/////////////////////////////////////////////////////////////////////////////

#include "copasi.h"
#include "utilities/CGlobals.h"
#include "CKinFunction.h"
#include "lexkk.h"
#include "utilities/utilities.h"

C_INT16 DefinedInsertAllowed(CNodeK src);

CKinFunction::CKinFunction()
{
  setType(CBaseFunction::USERDEFINED);
  // mNodes = NULL;
}

CKinFunction::CKinFunction(const string & name,
                           const string & description)
{
  setType(CBaseFunction::USERDEFINED);
  // mNodes = NULL;

  setName(name);
  setDescription(description);
}

CKinFunction::~CKinFunction() {}

void CKinFunction::cleanup() 
{
  // if (mNodes) delete mNodes;
  // mNodes = NULL;
  mNodes.cleanup();
  CBaseFunction::cleanup();
}

void CKinFunction::copy(const CKinFunction & in)
{
  CBaseFunction::copy(in);

  mNodes = CCopasiVectorS < CNodeK > (in.mNodes);
  //for (unsigned C_INT32 i = 0; i < in.mNodes.size(); i++)
  //  mNodes.add(in.mNodes[i]);
    
  mNidx = in.mNidx;    

  connectNodes();
  initIdentifiers();
}

C_INT32 CKinFunction::load(CReadConfig & configbuffer,
                           CReadConfig::Mode mode)
{
  string TmpString;
  C_INT32 Size = 0;
  C_INT32 Fail = 0;
    
  if ((Fail = CBaseFunction::load(configbuffer,mode))) return Fail;
    
  if ((Fail = configbuffer.getVariable("Nodes", "C_INT32", &Size)))
    return Fail;

  mNodes.load(configbuffer,Size);

  connectNodes();
  initIdentifiers();

  return Fail;
}

C_INT32 CKinFunction::save(CWriteConfig & configbuffer)
{
  string TmpString;
  C_INT32 TmpLong;
  C_INT32 Fail = 0;
    
  if ((Fail = CBaseFunction::save(configbuffer))) return Fail;

  TmpLong = mNodes.size();
  if ((Fail = configbuffer.setVariable("Nodes", "C_INT32", &TmpLong)))
    return Fail;

  mNodes.save(configbuffer);
    
  return Fail;
}

CCopasiVectorS < CNodeK > & CKinFunction::nodes() {return mNodes;}

void CKinFunction::setIdentifierType(const string & name,
                                     char identifierType)
{
  pair < unsigned C_INT32, unsigned C_INT32 > Index(0, 0);
    
  Index = findIdentifier(name);
    
  if ( !(Index.first + 1) || !(Index.second + 1) )
    CCopasiMessage(CCopasiMessage::ERROR, MCKinFunction + 1, name.c_str(), 
		   getName().c_str());

  for (unsigned C_INT32 i = 0; 
       i < ((CKinIdentifier *) callParameters()[Index.first]->
	    identifiers()[Index.second])->mNodes.size();
       i++)
    ((CKinIdentifier *) callParameters()[Index.first]->
     identifiers()[Index.second])->mNodes[i]->setSubtype(identifierType);
}

C_INT32 CKinFunction::parse()
{
  C_INT32 i;
  char *buffer;
  YY_BUFFER_STATE kkbuff;
  // create a buffer big enough to contain the function string
  buffer = new char[getDescription().length()+1];
  // copy it into the buffer
  strcpy(buffer, getDescription().c_str());
  // input for the scanner is from the buffer
  kkbuff = kk_scan_string(buffer);
  // add the root node
  mNodes.add(CNodeK(N_ROOT, N_NOP));
  // call the lexical analyser successively until done
  for (i=1; i!=0;)
    {
      i = kklex();
      switch (i)
        {
        case N_IDENTIFIER: mNodes.add(CNodeK(kktext)); break;
        case N_NUMBER:     mNodes.add(CNodeK(atof(kktext))); break;
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
	  clearNodes();
	  delete [] buffer;
	  kk_delete_buffer(kkbuff);
	  // should return the position for the erroneous character
	  return 1;
        }
    }
  // release allocated memory
  delete [] buffer;
  kk_delete_buffer(kkbuff);
  // connect the nodes
  initIdentifiers();
    
  return connectNodes();
}

C_FLOAT64 
CKinFunction::calcValue(const CCopasiVector < CCallParameter > & callParameters) const
{
  return mNodes[0]->getLeft().value(callParameters[0]->identifiers());
}

void CKinFunction::clearNodes() {mNodes.cleanup();}

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
		    //            sprintf(errstr, "ERROR - incorrect number of operands");
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

void CKinFunction::initIdentifiers()
{
  CKinIdentifier* pIdentifier;
  CBaseCallParameter* pCallParameter = new CBaseCallParameter;
    
  pCallParameter->identifierTypes().push_back(N_SUBSTRATE);
  pCallParameter->identifierTypes().push_back(N_PRODUCT);
  pCallParameter->identifierTypes().push_back(N_MODIFIER);
  pCallParameter->identifierTypes().push_back(N_KCONSTANT);
    
  unsigned C_INT32 i;

  pair < C_INT32, C_INT32 > Index;

  for (i = 0; i < callParameters().size(); i++)
    {
      callParameters()[i]->cleanup();
      delete callParameters()[i];
    }

  callParameters().clear();
  callParameters().push_back(pCallParameter);
    
  for(i = 0; i < mNodes.size(); i++)
    {
      if (mNodes[i]->isIdentifier())
        {
	  Index = findIdentifier(mNodes[i]->getName());
	  if ( Index.first == -1 )
            {
	      pIdentifier = new CKinIdentifier;
	      pIdentifier->setName(mNodes[i]->getName());
	      pIdentifier->setType(mNodes[i]->getSubtype());
	      Index.second = callParameters()[0]->identifiers().size();
	      callParameters()[0]->identifiers().push_back(pIdentifier);
            }
	  mNodes[i]->setIndex(Index.second);
	  ((CKinIdentifier *) callParameters()[0]->
	   identifiers()[Index.second])->
	    mNodes.push_back(mNodes[i]);
        }
    }
  callParameters()[0]->setCount(callParameters()[0]->identifiers().size());
}

CKinIdentifier::CKinIdentifier() {}

CKinIdentifier::~CKinIdentifier() {} 
