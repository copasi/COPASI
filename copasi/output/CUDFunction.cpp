/*****************************************************************************
* PROGRAM NAME: CUDFunction.cpp
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: Implement the user defined function object
*****************************************************************************/

#include <iostream>
#include "copasi.h"
#include "utilities/CGlobals.h"
#include "CNodeO.h"
#include "CUDFunction.h"

/**
 *  Default constructor
 */
CUDFunction::CUDFunction()
{
  setType(CBaseFunction::OUTPUT);
}
    
/**
 *  This creates a user defined function with a name an description
 *  @param "const string" &name
 *  @param "const string" &description
 */
CUDFunction::CUDFunction(const string & name,
	       const string & description)
{
	setType(CBaseFunction::OUTPUT);
	setName(name);
	setDescription(description);
}

/**
 *  Destructor
 */
CUDFunction::~CUDFunction()
{
}

/**
 *  Delete
 */
void CUDFunction::cleanup()
{
	mNodes.cleanup();
	//CBaseFunction.cleanup();
}


/**
 *  Copy
 */
void CUDFunction::copy(const CUDFunction & in)
{
  CBaseFunction::copy(in);

  mNodes = CCopasiVectorS < CNodeO > (in.mNodes);

  mNidx = in.mNidx;

  connectNodes();
}

/**
 *  Loads an object with data coming from a CReadConfig object.
 *  (CReadConfig object reads an input stream)
 *  @param pconfigbuffer reference to a CReadConfig object.
 *  @return Fail
 */
C_INT32 CUDFunction::load(CReadConfig & configbuffer,
	       CReadConfig::Mode mode)
{
  C_INT32 Fail = 0;
  CReadConfig::Mode Mode = mode;
  C_INT32 Size = 0;
  string Name, Description;

  if ((Fail = configbuffer.getVariable("Name", "string", &Name,
				       Mode)))
    return Fail;
  
  setName(Name);
  
  if ((Fail = configbuffer.getVariable("Description", "string", &Description)))
    return Fail;

  setDescription(Description);

  setType(CBaseFunction::OUTPUT);

  if ((Fail = configbuffer.getVariable("Nodes", "C_INT32", &Size)))
    return Fail;

  mNodes.load(configbuffer,Size);

  connectNodes();

  initIdentifiers();

  return Fail;

}

/**
 *  Saves the contents of the object to a CWriteConfig object.
 *  (Which usually has a file attached but may also have socket)
 *  @param pconfigbuffer reference to a CWriteConfig object.
 *  @return Fail
 */
C_INT32 CUDFunction::save(CWriteConfig & configbuffer)
{

  C_INT32 Fail;
  string name, description;
  
  name = getName();
  description = getDescription();

  if ((Fail = configbuffer.setVariable("Name", "string", &name)))
    return Fail;
    
  if ((Fail = configbuffer.setVariable("Description", "string", &description)))
    return Fail;

  C_INT32 Size = mNodes.size();

  if ((Fail = configbuffer.setVariable("Nodes", "C_INT32", &Size)))
    return Fail;

  mNodes.save(configbuffer);

  return Fail;
}

/**
 *  This retrieves the node tree of the function
 *  @return "CCopasiVectorS < CNodeO > &"
 */
CCopasiVectorS < CNodeO > & CUDFunction::nodes()
{
	return mNodes;
}

/**
 *  This clears all nodes of the function tree
 */
void CUDFunction::clearNodes()
{
	mNodes.cleanup();
}

/**
 *  This  connects the nodes to build the binary function tree
 */
C_INT32 CUDFunction::connectNodes()
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

CNodeO * CUDFunction::parseExpression(C_INT16 priority)
{
  C_INT32 errfl = 0;     // !!! do we need this?
  C_INT32 errnode = -1;  // !!! do we need this?

  CNodeO *lhs, *rhs;
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

/**
 * Calculate the value of this user defined function
 * return the pointer of this user defined function
 */
void CUDFunction::calcValue(CModel *model)
{
	CNodeO npt;

	npt = mNodes[0]->getLeft();
	mValue = npt.value(model);
}

/**
 *	Get the pointer of user defined functions
 */
void * CUDFunction::getValueAddr()
{
	return &mValue;
}

void CUDFunction::initIdentifiers()
{
  CUDIdentifier* pIdentifier;
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
	      pIdentifier = new CUDIdentifier;
	      pIdentifier->setName(mNodes[i]->getName());
	      pIdentifier->setType(mNodes[i]->getSubtype());
	      Index.second = callParameters()[0]->identifiers().size();
	      callParameters()[0]->identifiers().push_back(pIdentifier);
            }
	  mNodes[i]->setIndex(Index.second);
	  ((CUDIdentifier *) callParameters()[0]->
	   identifiers()[Index.second])->
	    mNodes.push_back(mNodes[i]);
        }
    }
  callParameters()[0]->setCount(callParameters()[0]->identifiers().size());
}

CUDIdentifier::CUDIdentifier() {}

CUDIdentifier::~CUDIdentifier() {} 
