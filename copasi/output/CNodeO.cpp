/*****************************************************************************
* PROGRAM NAME: CNodeO.cpp
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: Implement the node object in user defined function
*****************************************************************************/

#include "copasi.h"
#include "CDatum.h"
#include "CNodeO.h"

/**
 * Default constructor
 */
CNodeO::CNodeO()
{
	mDatumType = 0;
	mTitle = "";
	mI = "";
	mJ = "";
}

/**
 * Constructor for operator
 * @param "const char" type
 * @param "const char" subtype
 */
CNodeO::CNodeO(string title, C_INT32 type, string i_str, string j_str)
{
	mDatumType = type;
	mTitle = title;
	mI = i_str;
	mJ = j_str;
}

/**
 * Destructor
 */
CNodeO::~CNodeO()
{
}

/**
 * Delete
 */
void CNodeO::cleanup()
{
}

/**
 *  Loads an object with data coming from a CReadConfig object.
 *  (CReadConfig object reads an input stream)
 *  @param pconfigbuffer reference to a CReadConfig object.
 *  @return Fail
 */
C_INT32 CNodeO::load(CReadConfig & configbuffer)
{

  C_INT32 Fail = 0;
  char Type, Subtype;
  C_FLOAT64 Constant;

  if ((Fail = configbuffer.getVariable("Node", "node", &Type, &Subtype,
				       CReadConfig::SEARCH)))
    return Fail;
    
  setType(Type);
  setSubtype(Subtype);

  if (isIdentifier() && getType() != N_IDENTIFIER)
    {
      setSubtype(getType());
      setType(N_IDENTIFIER);
    }
    
  // leave the Left & Right pointers out
  // value of the constant if one
  if (getType() == N_NUMBER)
    {
      if ((Fail = configbuffer.getVariable("Value", "C_FLOAT64", &Constant)))
		return Fail;
	  setConstant(Constant);
    }
  else if (getType() == N_IDENTIFIER)
    {
		if ((Fail = configbuffer.getVariable("Title", "string", &mTitle)))
			return Fail;
		if ((Fail = configbuffer.getVariable("Type", "C_INT32", &mDatumType)))
			return Fail;

		switch (mDatumType)
		{
			case D_UNDEF:   // Fall through as all have no mI and no mJ
			case D_T:
			case D_RT:
			case D_INTS:
			case D_FEVAL:
			case D_JEVAL:
			case D_SSIZE:
			case D_RTOL:
			case D_ATOL:
			case D_SSRES:
			case D_UFUNC:	// D_UFUNC has mI
			case D_DERIV:
			case D_ENDT:
			case D_POINT:
			case D_EIGMR:
			case D_EIGMI:
			case D_EIGPR:
			case D_EIGNR:
			case D_EIGR:
			case D_EIGI:
			case D_EIGC:
			case D_EIGZ:
			case D_THIER:
			case D_STIFF:   
						break;
			case D_ICONC:   // Fall through as all have mI but no mJ
			case D_SCONC:
			case D_TCONC:
			case D_SFLUX:
			case D_TFLUX:
			case D_VOL:
			case D_MOIT:
			case D_TT:
			case D_EIGVR:
			case D_EIGVI:   
						Fail = configbuffer.getVariable("I", "string", (void *) &mI);
						if (Fail) return Fail;
						break;
			case D_KIN:     // Fall through as all have mI and mJ
			case D_ELAST:
			case D_CCC:
			case D_FCC:
			case D_EIG:
						Fail = configbuffer.getVariable("I", (string) "string",
								(void *) &mI);
						if (Fail) return Fail;
						Fail = configbuffer.getVariable((string) "J", 
								(string) "string", (void *) &mJ);
						if (Fail) return Fail;
						break;
			default:        
						Fail = 1; // we should never get here!
						break;
		} // end of switch
    }

	return Fail;


}

/**
 *  Saves the contents of the object to a CWriteConfig object.
 *  (Which usually has a file attached but may also have socket)
 *  @param pconfigbuffer reference to a CWriteConfig object.
 *  @return Fail
 */
C_INT32 CNodeO::save(CWriteConfig & configbuffer) const
{
	C_INT32 Fail = 0;
    char Type, Subtype;
	
	Type = getType();
	Subtype = getSubtype();

	if ((Fail = configbuffer.setVariable("Node", "node", &Type, &Subtype)))
		return Fail;
	// leave the Left & Right pointers out
	// value of the constant if one
	if (Type==N_NUMBER)
    {
		C_FLOAT64 Constant = getConstant();
		if ((Fail = configbuffer.setVariable("Value", "C_FLOAT64", &Constant)))
			return Fail;
    }
	else if (isIdentifier())
    {
		// Output Title
		if ((Fail = configbuffer.setVariable("Title", "string", &mTitle)))
			return Fail;

		// Output Type
		if ((Fail = configbuffer.setVariable("Type", "C_INT32", &mDatumType)))
			return Fail;

		// Output Type as well as I String
		// some types need more output... (mI or mJ)
		switch (mDatumType)
		{
			case D_UNDEF:   // Fall through as all have no mI and no mJ
			case D_T:
			case D_RT:
			case D_INTS:
			case D_FEVAL:
			case D_JEVAL:
			case D_SSIZE:
			case D_RTOL:
			case D_ATOL:
			case D_SSRES:
			case D_UFUNC:	// D_UFUNC has mI
			case D_DERIV:
			case D_ENDT:
			case D_POINT:
			case D_EIGMR:
			case D_EIGMI:
			case D_EIGPR:
			case D_EIGNR:
			case D_EIGR:
			case D_EIGI:
			case D_EIGC:
			case D_EIGZ:
			case D_THIER:
			case D_STIFF:   
						break;
			case D_ICONC:   // Fall through as all have mI but no mJ
			case D_SCONC:
			case D_TCONC:
			case D_SFLUX:
			case D_TFLUX:
			case D_VOL:
			case D_MOIT:
			case D_TT:
			case D_EIGVR:
			case D_EIGVI:   
						Fail = configbuffer.setVariable("I", "string", &mI);
						if (Fail) return Fail;
						break;
			case D_KIN:     // Fall through as all have mI and mJ
			case D_ELAST:
			case D_CCC:
			case D_FCC:
			case D_EIG:
						Fail = configbuffer.setVariable("I", "string", &mI);
						if (Fail) return Fail;
						Fail = configbuffer.setVariable("J", "string", &mJ);
						if (Fail) return Fail;
						break;
			default:        
						Fail = 1; // we should never get here!
						break;
		} // end of switch
    }
	
	return Fail;

}

	
/**
 * Retrieving the Title of a node
 * @return string
 */
string CNodeO::getTitle() const
{
	return mTitle;
}

/**
 * Retrieving I String of a node
 * @return string
 */
string CNodeO::getIString() const
{
	return mI;
}

/**
 * Retrieving J String of a node
 * @return string
 */
string CNodeO::getJString() const
{
	return mJ;
}
  
/**
 * Setting Title of the node
 * @param "const string" &title
 */
void CNodeO::setTitle(const string & title)
{
	mTitle = title;
}

/**
 * Setting I String of the node
 * @param "const string" &i_string
 */
void CNodeO::setIString(const string & i_string)
{
	mI = i_string;
}

/**
 * Setting I String of the node
 * @param "const string" &j_string
 */
void CNodeO::setJString(const string & j_string)
{
	mJ = j_string;
}

/**
 * Set the node's Datum Type
 */
//void setDatumType(C_INT32 datum)
//{
//	mDatumType = datum;
//}


/**
 * Get the node's Datum type
 */
C_INT32 CNodeO::getDatumType() const
{
	return mDatumType;
}


