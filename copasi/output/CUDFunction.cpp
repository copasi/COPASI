/*****************************************************************************
* PROGRAM NAME: CUDFunction.cpp
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: Implement the user defined function object
*****************************************************************************/

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
  unsigned C_INT32 i;
  C_INT32 errfl = 0;     // !!! do we need this?

  // initialise the control variables
  mNidx = 1;

  // point all Left & Right to the root node
  for (i = 1; i < mNodes.size(); i++)
  {
	  mNodes[i]->setLeft(mNodes[0]);
	  mNodes[i]->setRight(mNodes[0]);
  }

  //update pointers and references in the tree
  mNodes[0]->setLeft(parseExpression(0));

  return errfl;
}

CNodeO * CUDFunction::parseExpression(C_INT16 priority)
{
  CNodeO *lhs;

  lhs = parsePrimary();
  if (!lhs) return NULL;

  return lhs;
}

CNodeO * CUDFunction::parsePrimary()
{
  CNodeO *npt;

  if (mNidx >= mNodes.size())
	  return NULL;

  mNodes[mNidx]->setLeft(NULL);
  mNodes[mNidx]->setRight(NULL);
  npt = mNodes[mNidx];
  ++mNidx;
  return npt;
}

