/*****************************************************************************
* PROGRAM NAME: CDatum.cpp
* PROGRAMMER: Wei Sun	wsun@vt.edu
* PURPOSE: CDatum Class Implemention
*****************************************************************************/

#include <string>
#include <malloc.h>

#include "copasi.h"
#include "CDatum.h"
#include "CCompartment.h"

/**
 *  Default constructor. 
 */
CDatum::CDatum()
{
	mTitle = "";
	mpValue = NULL;
	mType = 0;		//(????)
	mObject = "";
}

/**
 *  User Defined constructor. 
 *  Creates an object with contents passed as arguments
 *  @param title: title of the object.
 *  @param value: pointer to the memeory location containing the value of the object.
 *  @param type: type of the object (e.g. C_INT32).
 *  @param object: the name of this object 
 */
CDatum::CDatum(const string& title, void* value, C_INT32 type, const string& object)
{
	mTitle = title;
	mpValue = value;
	mType = type;
	mObject = object;
}

/**
 *  Assignement operator. 
 *  Copies the contents from one CDatum object to another.
 *  @param source reference to the recipient object.
 */
CDatum& CDatum::operator=(const CDatum &source)
{
	mTitle = source.mTitle;
	mpValue = source.mpValue;
	mType = source.mType;
	mObject = source.mObject;

	return *this;
}

/**
 *  Returns a string with the title of this object.
 *  @return mTitle
 */
string CDatum::GetTitle() const
{
	return mTitle;
}

/**
 *  Sets the title of this object
 *  @param title constant reference to a string.
 */
void CDatum::SetTitle(const string& title)
{
	mTitle = title;
}

/**
 *  Returns the value of this object.
 *  @return *mpValue
 */
void* CDatum::GetValue() const
{
	return mpValue;
}

/**
 *  Sets the value of mpValue with a pointer to a memory location that has 
 *  the value of this object.
 *  @param value pointer to a void.
 */
void CDatum::SetValue(void* value)
{
	mpValue = value;
}

/**
 *  Returns the type of this object.
 *  @return mType
 */	
C_INT32 CDatum::GetType() const
{
	return mType;
}

/**
 *  Sets the type of this object
 *  @param type constant reference to a string specifing the type of this object.
 */
void CDatum::SetType(const C_INT32 type)
{
	mType = type;
}

/**
 *  Returns a string with the name of this object.
 *  @return mObject
 */	
string CDatum::GetObject() const
{
	return mObject;
}

/**
 *  Sets the name of this object
 *  @param object constant reference to a string specifing the type of this object.
 */
void CDatum::SetObject(const string& object)
{
	mObject = object;
}

/**
 *  Loads an object with data coming from a CReadConfig object.
 *  (CReadConfig object reads an input stream)
 *  @param pconfigbuffer reference to a CReadConfig object.
 *  @return mFail
 *  @see mFail
 */
C_INT32 CDatum::load(CReadConfig & configbuffer)
{
	C_INT32 Fail;
	C_INT16 Type;
	string IStr, JStr;

    Fail = configbuffer.getVariable("Title", "string", &mTitle);
    if (Fail) return Fail;

	// Read data object, type see CDatum.h 
	Fail = configbuffer.getVariable("Type", "C_INT16", &Type);
    if (Fail) return Fail;

    // some types need more input... (mI or mJ)
    switch (Type)
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
						Fail = configbuffer.getVariable("I", "string", (void *) &IStr);
						if (Fail) return Fail;
						break;
		case D_KIN:     // Fall through as all have mI and mJ
		case D_ELAST:
		case D_CCC:
		case D_FCC:
		case D_EIG:
						Fail = configbuffer.getVariable("I", (string) "string",
                                          (void *) &IStr);

						if (Fail) return Fail;

						Fail = configbuffer.getVariable((string) "J", 
                                          (string) "string",
                                          (void *) &JStr);

						if (Fail) return Fail;

						break;

		default:        
						Fail = 1; // we should never get here!
						break;
    }

	string Model = "Bakker";
	CreateObject(Model, IStr, JStr, Type);

	return Fail;
}

/**
 *  Saves the contents of the object to a CWriteConfig object.
 *  (Which usually has a file attached but may also have socket)
 *  @param pconfigbuffer reference to a CWriteConfig object.
 *  @return mFail
 *  @see mFail
 */
C_INT32 CDatum::save(CWriteConfig & configbuffer)
{
	C_INT32 Fail = 0;
	C_INT32 Type = 0;
	string IStr, JStr;

	// Output Title
    if (Fail = configbuffer.setVariable("Title", "string", &mTitle))
		return Fail;
	
	Type = GetObjectType(mObject);
	
	// Output Type
    if (Fail = configbuffer.setVariable("Type", "C_INT32", &Type))
		return Fail;

    // some types need more output... (mI or mJ)
    switch (Type)
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
						IStr = GetObjectIStr(mObject, 0);
						Fail = configbuffer.setVariable("I", "string", &IStr);
						if (Fail) return Fail;
						break;
		case D_KIN:     // Fall through as all have mI and mJ
		case D_ELAST:
		case D_CCC:
		case D_FCC:
		case D_EIG:
						IStr = GetObjectIStr(mObject, 1);
						Fail = configbuffer.setVariable("I", "string", &IStr);
						if (Fail) return Fail;

						JStr = GetObjectJStr(mObject);
						Fail = configbuffer.setVariable("J", "string", &JStr);
						if (Fail) return Fail;

						break;

		default:        
						Fail = 1; // we should never get here!
						break;
    }
	
	return Fail;
}

/**
 *  Creates the mObject
 *  @param object constant reference to a string specifing the name of the 
 *  model this datum is in, IStr, JStr, the type of this data, such as D_TCONC.
 */

void CDatum::CreateObject(const string& Model, const string& IStr, const string& JStr, C_INT32 Type)
{
	string member;

	// Create CModel part
	mObject.append("CModel = \"");
	mObject.append(Model);
	mObject.append("\", ");

    // Create CMetab part
    switch (Type)
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
		case D_UFUNC:
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
						mObject.append("CMetab = \"");
						mObject.append("\"");
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
						mObject.append("CMetab = \"" + IStr + "\"");
						break;
		case D_KIN:     // Fall through as all have mI and mJ
		case D_ELAST:
		case D_CCC:
		case D_FCC:
		case D_EIG:
						mObject.append("CMetab = \"" + IStr + "\"");
						mObject.append(", \"" + JStr + "\"");
						break;
    }

	// Create CMember part

	member = TransferType(Type);

	if (!member.length())
	{
		// types like D_T, see transferType
		mObject.append(", CMember = \"");
		mObject.append("\"");
	}
	else {
		// other types like D_TCONC
		mObject.append(", CMember = \"" + member + "\"");
	}

}

/**
 *  Transfers the Type to the associated member data in each class
 *  @Type object constant reference to a type of the datum, for example,D_TCONC
 */
string CDatum::TransferType(C_INT32 Type)
{
	string cMemb;

    // find the member for different associated type
    switch (Type)
    {
		case D_T:
		case D_RT:
		case D_INTS:
		case D_FEVAL:
		case D_JEVAL:
		case D_SSIZE:
		case D_RTOL:
		case D_ATOL:
		case D_SSRES:
		case D_UFUNC:
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
			
		case D_EIGVR:
		case D_EIGVI:   
		case D_EIG:		// These types have no assocaited member data
						break;
		case D_ICONC:   
						cMemb = "mIConc";
						break;
		case D_SCONC:
		case D_TCONC:
						cMemb = "mConc";
						break;
		case D_SFLUX:
		case D_TFLUX:
						cMemb = "mFlux";
						break;
		case D_VOL:
						cMemb = "mVolume";
						break;
		case D_MOIT:
						cMemb = "mIConc";
						break;
		case D_TT:
						cMemb = "mTT";
						break;
		case D_KIN:		//???
						cMemb = "mParameters";
						break;
		case D_ELAST:	//???
						cMemb = "mIColmIRow";
						break;
		case D_CCC:		//???
						cMemb = "mIRowmICol";
						break;						
		case D_FCC:		//???
						cMemb = "mIColmICol";
						break;
    }
	
	return cMemb;
}

/**
 *  Transfers the associated member data to the Type to  in each class
 *  @Type object constant reference to a type of the datum, for example,D_TCONC
 */
C_INT32 CDatum::GetObjectType(string Object)
{
	C_INT32 Type = 0;
	C_INT16 Posi = 0;
	C_INT16 StrNum = 0;
	string TypeStr;
	string CMemb = "CMember = \"";

	Posi = Object.find(CMemb, 0);
	Posi += CMemb.length();
	StrNum = Object.length() - 1 - Posi;
	TypeStr = Object.substr(Posi, StrNum);
		
	if (!TypeStr.compare("mIConc"))
		Type = D_ICONC;

	if (!TypeStr.compare("mConc"))
		Type = D_SCONC;

	if (!TypeStr.compare("mConc"))
		Type = D_TCONC;

	if (!TypeStr.compare("mFlux"))
		Type = D_SFLUX;

	if (!TypeStr.compare("mFlux"))
		Type = D_TFLUX;

	if (!TypeStr.compare("mVolume"))
		Type = D_VOL;

	if (!TypeStr.compare("mIConc"))
		Type = D_MOIT;

	if (!TypeStr.compare("mTT"))
		Type = D_TT;

	if (!TypeStr.compare("mParameters"))
		Type = D_KIN;

	if (!TypeStr.compare("mIColmIRow"))
		Type = D_ELAST;

	if (!TypeStr.compare("mIRowmICol"))
		Type = D_CCC;

	if (!TypeStr.compare("mIColmICol"))
		Type = D_FCC;

	return Type;
}

/**
 *  Get the object I string part
 *  @object reference to CDatum object
 */
string CDatum::GetObjectIStr(string object, C_INT16 HasJStr)
{
	string Metab;
	C_INT16 Posi = 0;
	C_INT16	Posi1 = 0;
	C_INT16 StrNum = 0;
	string IStr;
	string CMetab = "CMetab = \"";

	Posi = object.find(CMetab, 0) + CMetab.length() - 1;
	Posi1 = object.find("\", CMember =", 0);
	StrNum = Posi1 - Posi - 1;
	Metab = object.substr(Posi+1, StrNum);

	if (!HasJStr)
		IStr = Metab;
	else {
		
		C_INT16 Posi2 = 0;

		Posi2 = Metab.find("\",", 0);
		IStr = Metab.substr(0, Posi2);		// Posi2-1???
	}
	return IStr;
}

/**
 *  Get the object J string part
 *  @object reference to CDatum object
 */
string CDatum::GetObjectJStr(string object)
{
	string Metab;
	C_INT16 Posi = 0;
	C_INT16	Posi1 = 0;
	C_INT16 StrNum = 0;
	string JStr;
	string CMetab = "CMetab = \"";

	Posi = object.find(CMetab, 0) + CMetab.length() - 1;
	Posi1 = object.find("\", CMember =", 0);
	StrNum = Posi1 - Posi - 1;
	Metab = object.substr(Posi+1, StrNum);

	Posi = Metab.find(", \"", 0);
	StrNum = Metab.length() - Posi - 3;

	JStr = Metab.substr(Posi+3, StrNum);

	return JStr;
}

/**
 *  Complie the mpValue in each CDatum
 */
void CDatum::CompileDatum(CModel &Model)
{
	C_INT32 Type = 0;
	string IStr, JStr;
	int Index, Index1;

	Type = GetObjectType(mObject);
	
	switch (Type)
	{
#if 0
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
#endif
		case D_ICONC:   // Fall through as all have mI but no mJ
						IStr = GetObjectIStr(mObject, 0);
						Index = Model.findMetab(IStr);
						if (Index == -1) break;
						mpValue = Model.getMetabolites()[Index]->getIConcAddr();
						mType = CFLOAT64;
						break;
		case D_SCONC:
		case D_TCONC:
						IStr = GetObjectIStr(mObject, 0);
						Index = Model.findMetab(IStr);
						if (Index == -1) break;
						mpValue = Model.getMetabolites()[Index]->getConcAddr();
						mType = CFLOAT64;
						break;
		case D_TT:
						IStr = GetObjectIStr(mObject, 0);
						Index = Model.findMetab(IStr);
						if (Index == -1) break;
						mpValue = Model.getMetabolites()[Index]->getTTAddr();;
						mType = CFLOAT64;
						break;
		case D_SFLUX:
		case D_TFLUX:
						IStr = GetObjectIStr(mObject, 0);
						Index = Model.findStep(IStr);
						if (Index == -1) break;
						mpValue = (*Model.getSteps())[Index].getFluxAddr();
						mType = CFLOAT64; 
						break;
		case D_VOL:
						IStr = GetObjectIStr(mObject, 0);
						Index = Model.findCompartment(IStr);
						if (Index == -1) break;
						mpValue = (*Model.getCompartments())[Index].getVolumeAddr();
						mType = CFLOAT64;
						break;						
		case D_MOIT:
						IStr = GetObjectIStr(mObject, 0);
						Index = Model.findMoiety(IStr);
						if (Index == -1) break;
						mpValue = (*Model.getMoieties())[Index].getNumberAddr();
						mType = CFLOAT64;
						break;	
#if 0						
		case D_EIGVR:
		case D_EIGVI:   
						IStr = GetObjectIStr(mObject, 0);
						break;
#endif

		case D_KIN:     // Fall through as all have mI and mJ
						IStr = GetObjectIStr(mObject, 1);
						JStr = GetObjectJStr(mObject);
						Index = Model.findStep(IStr);
						if (Index == -1) break;
						Index1 = (*Model.getSteps())[Index].findPara(JStr);
						if (Index1 == -1) break;
						mpValue = (C_FLOAT64 *)(*Model.getSteps())[Index].parameters()[Index1].getValueAddr();
						mType = CFLOAT64;
						break;
#if 0
		case D_ELAST:
						IStr = GetObjectIStr(mObject, 1);
						JStr = GetObjectJStr(mObject);
						Index = outputList.Model.FindStep(IStr);
						Index1 = outputList.Model.FindMetab(JStr);
						if ((Index = -1) || (Index1 = -1))
							break;
						mpValue = &(Dxv[outputList.Model.mICol[Index]][outputList.Model.mIRow[Index1]] );
						mType = C_FLOAT64;
						break;
		case D_CCC:
						IStr = GetObjectIStr(mObject, 1);
						JStr = GetObjectJStr(mObject);
						Index = outputList.Model.FindMetab(IStr);
						Index1 = outputList.Model.FindStep(JStr);
						if ((Index == -1) || (Index1 == -1) || (outputList.Model.mMetabolite[Index].Status == METAB_FIXED))
							break;
						mpValue = &(Gamma[outputList.Model.mIRow[Index]][outputList.Model.mICol[Index1]] );
						mType = C_FLOAT64;
						break;
		case D_FCC:
						IStr = GetObjectIStr(mObject, 1);
						JStr = GetObjectJStr(mObject);
						Index = outputList.Model.FindMetab(IStr);
						Index1 = outputList.Model.FindMetab(JStr);
						if ((Index == -1) || (Index1 == -1))
							break;
						mpValue = &(FCC[outputList.Model.mICol[Index]][outputList.Model.mICol[Index1]] );
						mType = C_FLOAT64;
						break;
		case D_EIG:
						IStr = GetObjectIStr(mObject, 1);

						JStr = GetObjectJStr(mObject);

						break;
#endif
	}
}
