/*****************************************************************************
 * PROGRAM NAME: CDatum.cpp
 * PROGRAMMER: Wei Sun wsun@vt.edu
 * PURPOSE: CDatum Class Implemention
 *****************************************************************************/

#include <string>

#define  COPASI_TRACE_CONSTRUCTION

//#include "copasi.h"
#include "CDatum.h"
#include "utilities/CGlobals.h"
#include "model/CCompartment.h"
#include "model/CState.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CEigen.h"
#include "output/CUDFunction.h"
#include "CUDFunctionDB.h" 
/**
 *  Default constructor. 
 */
CDatum::CDatum(const std::string & name,
               const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Datum"),
    mTitle(),
    mpValue(NULL),
    mType(0),
    mObject(mObjectName)
{}

CDatum::CDatum(const CDatum & src,
               const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mTitle(src.mTitle),
    mpValue(src.mpValue),
    mType(src.mType),
    mObject(mObjectName)
{}

/**
 *  User Defined constructor. 
 *  Creates an object with contents passed as arguments
 *  @param title: title of the object.
 *  @param value: pointer to the memeory location containing the value of the object.
 *  @param type: type of the object (e.g. C_INT32).
 *  @param object: the name of this object 
 */
CDatum::CDatum(const std::string& title,
               void* value,
               C_INT32 type,
               const std::string& object,
               const CCopasiContainer * pParent):
    CCopasiContainer(object, pParent, "Datum"),
    mTitle(title),
    mpValue(value),
    mType(type),
    mObject(mObjectName)
{}

void CDatum::cleanup() {}

/**
 *  Returns a string with the title of this object.
 *  @return mTitle
 */
std::string CDatum::getTitle() const
  {
    return mTitle;
  }

/**
 *  Sets the title of this object
 *  @param title constant reference to a string.
 */
void CDatum::setTitle(const std::string& title)
{
  mTitle = title;
}

/**
 *  Returns the value of this object.
 *  @return *mpValue
 */
const void* CDatum::getValue() const
  {
    return mpValue;
  }

/**
 *  Sets the value of mpValue with a pointer to a memory location that has 
 *  the value of this object.
 *  @param value pointer to a void.
 */
void CDatum::setValue(void* value)
{
  mpValue = value;
}

/**
 *  Returns the type of this object.
 *  @return mType
 */
C_INT32 CDatum::getType() const
  {
    return mType;
  }

/**
 *  Sets the type of this object
 *  @param type constant reference to a string specifing the type of this object.
 */
void CDatum::setType(const C_INT32 type)
{
  mType = type;
}

/**
 *  Returns a string with the name of this object.
 *  @return mObject
 */
std::string CDatum::getObject() const
  {
    return mObject;
  }

/**
 *  Sets the name of this object
 *  @param object constant reference to a string specifing the type of this object.
 */
void CDatum::setObject(const std::string& object)
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
  std::string IStr, JStr;

  Fail = configbuffer.getVariable("Title", "string", &mTitle);
  if (Fail)
    return Fail;

  // Read data object, type see CDatum.h
  Fail = configbuffer.getVariable("Type", "C_INT16", &Type);
  if (Fail)
    return Fail;

  // some types need more input... (mI or mJ)
  switch (Type)
    {
    case D_UNDEF:             // Fall through as all have no mI and no mJ
    case D_T:
    case D_RT:
    case D_INTS:
    case D_FEVAL:
    case D_JEVAL:
    case D_SSIZE:
    case D_RTOL:
    case D_ATOL:
    case D_SSRES:
    case D_UFUNC:           // D_UFUNC has mI
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
    case D_ICONC:             // Fall through as all have mI but no mJ
    case D_SCONC:
    case D_TCONC:
    case D_SFLUX:
    case D_TFLUX:
    case D_VOL:
    case D_MOIT:
    case D_TT:
    case D_EIGVR:
    case D_EIGVI:
      Fail = configbuffer.getVariable("I", "string", (void *) & IStr);
      if (Fail)
        return Fail;
      break;
    case D_KIN:               // Fall through as all have mI and mJ
    case D_ELAST:
    case D_CCC:
    case D_FCC:
    case D_EIG:
      Fail = configbuffer.getVariable("I", (std::string) "string",
                                      (void *) & IStr);

      if (Fail)
        return Fail;

      Fail = configbuffer.getVariable((std::string) "J",
                                      (std::string) "string",
                                      (void *) & JStr);

      if (Fail)
        return Fail;

      break;

    default:
      Fail = 1; // we should never get here!
      break;
    }

  createObjectString(Copasi->pModel->getTitle(), IStr, JStr, Type);

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
  std::string IStr, JStr;

  // Output Title
  if ((Fail = configbuffer.setVariable("Title", "string", &mTitle)))
    return Fail;

  Type = getObjectType(mObject);

  // Output Type
  if ((Fail = configbuffer.setVariable("Type", "C_INT32", &Type)))
    return Fail;

  // some types need more output... (mI or mJ)
  switch (Type)
    {
    case D_UNDEF:             // Fall through as all have no mI and no mJ
    case D_T:
    case D_RT:
    case D_INTS:
    case D_FEVAL:
    case D_JEVAL:
    case D_SSIZE:
    case D_RTOL:
    case D_ATOL:
    case D_SSRES:
    case D_UFUNC:           // D_UFUNC has mI
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
    case D_ICONC:             // Fall through as all have mI but no mJ
    case D_SCONC:
    case D_TCONC:
    case D_SFLUX:
    case D_TFLUX:
    case D_VOL:
    case D_MOIT:
    case D_TT:
    case D_EIGVR:
    case D_EIGVI:
      IStr = getObjectIStr(mObject, 0);
      Fail = configbuffer.setVariable("I", "string", &IStr);
      if (Fail)
        return Fail;
      break;
    case D_KIN:               // Fall through as all have mI and mJ
    case D_ELAST:
    case D_CCC:
    case D_FCC:
    case D_EIG:
      IStr = getObjectIStr(mObject, 1);
      Fail = configbuffer.setVariable("I", "string", &IStr);
      if (Fail)
        return Fail;

      JStr = getObjectJStr(mObject);
      Fail = configbuffer.setVariable("J", "string", &JStr);
      if (Fail)
        return Fail;

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

void CDatum::createObjectString(const std::string& model, const std::string& IStr, const std::string& JStr, C_INT32 Type)
{
  std::string member;

  mObject = "";
  // Create CModel part
  mObject.append("CModel = \"");
  //mObject.append(Copasi->Model->getTitle());
  mObject.append(model);
  mObject.append("\", ");

  // Create CMetab part
  switch (Type)
    {
    case D_UNDEF:             // Fall through as all have no mI and no mJ
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
    case D_ICONC:             // Fall through as all have mI but no mJ
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
    case D_KIN:               // Fall through as all have mI and mJ
    case D_ELAST:
    case D_CCC:
    case D_FCC:
    case D_EIG:
      mObject.append("CMetab = \"" + IStr + "\"");
      mObject.append(", \"" + JStr + "\"");
      break;
    }

  // Create CMember part

  member = transferType(Type);

  if (!member.length())
    {
      // types like D_T, see transferType
      mObject.append(", CMember = \"");
      mObject.append("\"");
    }
  else
    {
      // other types like D_TCONC
      mObject.append(", CMember = \"" + member + "\"");
    }
}

/**
 *  Transfers the Type to the associated member data in each class
 *  @Type object constant reference to a type of the datum, for example,D_TCONC
 */
std::string CDatum::transferType(C_INT32 Type)
{
  std::string cMemb;

  // find the member for different associated type
  // find the member for different associated type
  switch (Type)
    {
    case D_T:
      cMemb = "mTime";
      break;
    case D_RT:
    case D_INTS:
    case D_FEVAL:
    case D_JEVAL:
    case D_SSIZE:
    case D_RTOL:
    case D_ATOL:
    case D_SSRES:
    case D_UFUNC:
      cMemb = "mUFUNC";
      break;
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
    case D_EIG:            // These types have no assocaited member data
      break;
    case D_ICONC:
      cMemb = "mIConc";
      break;
    case D_SCONC:
      cMemb = "mSConc";
      break;
    case D_TCONC:
      cMemb = "mTConc";
      break;
    case D_SFLUX:
      cMemb = "mSFlux";
      break;
    case D_TFLUX:
      cMemb = "mTFlux";
      break;
    case D_VOL:
      cMemb = "mVolume";
      break;
    case D_MOIT:
      cMemb = "mINumber";
      break;
    case D_TT:
      cMemb = "mTT";
      break;
    case D_KIN:            //???
      cMemb = "mParameters";
      break;
    case D_ELAST:           //???
      cMemb = "mIColmIRow";
      break;
    case D_CCC:            //???
      cMemb = "mIRowmICol";
      break;
    case D_FCC:            //???
      cMemb = "mIColmICol";
      break;
    }

  return cMemb;
}

/**
 *  Transfers the associated member data to the Type to  in each class
 *  @Type object constant reference to a type of the datum, for example,D_TCONC
 */
C_INT32 CDatum::getObjectType(std::string Object)
{
  C_INT32 Type = 0;
  C_INT16 Posi = 0;
  C_INT16 StrNum = 0;
  std::string TypeStr;
  std::string CMemb = "CMember = \"";

  Posi = Object.find(CMemb, 0);
  Posi += CMemb.length();
  StrNum = Object.length() - 1 - Posi;
  TypeStr = Object.substr(Posi, StrNum);

  if (!TypeStr.compare("mTime"))
    Type = D_T;
  else if (!TypeStr.compare("mIConc"))
    Type = D_ICONC;
  else if (!TypeStr.compare("mSConc"))
    Type = D_SCONC;
  else if (!TypeStr.compare("mTConc"))
    Type = D_TCONC;
  else if (!TypeStr.compare("mSFlux"))
    Type = D_SFLUX;
  else if (!TypeStr.compare("mTFlux"))
    Type = D_TFLUX;
  else if (!TypeStr.compare("mVolume"))
    Type = D_VOL;
  else if (!TypeStr.compare("mINumber"))
    Type = D_MOIT;
  else if (!TypeStr.compare("mTT"))
    Type = D_TT;
  else if (!TypeStr.compare("mParameters"))
    Type = D_KIN;
  else if (!TypeStr.compare("mIColmIRow"))
    Type = D_ELAST;
  else if (!TypeStr.compare("mIRowmICol"))
    Type = D_CCC;
  else if (!TypeStr.compare("mIColmICol"))
    Type = D_FCC;
  else if (!TypeStr.compare("mUFUNC"))
    Type = D_UFUNC;

  return Type;
}

/**
 *  Get the object I string part
 *  @object reference to CDatum object
 */
std::string CDatum::getObjectIStr(std::string object, C_INT16 HasJStr)
{
  std::string Metab;
  C_INT16 Posi = 0;
  C_INT16 Posi1 = 0;
  C_INT16 StrNum = 0;
  std::string IStr;
  std::string CMetab = "CMetab = \"";

  Posi = object.find(CMetab, 0) + CMetab.length() - 1;
  Posi1 = object.find("\", CMember =", 0);
  StrNum = Posi1 - Posi - 1;
  Metab = object.substr(Posi + 1, StrNum);

  if (!HasJStr)
    IStr = Metab;
  else
    {
      C_INT16 Posi2 = 0;

      Posi2 = Metab.find("\",", 0);
      IStr = Metab.substr(0, Posi2);  // Posi2-1???
    }
  return IStr;
}

/**
 *  Get the object J string part
 *  @object reference to CDatum object
 */
std::string CDatum::getObjectJStr(std::string object)
{
  std::string Metab;
  C_INT16 Posi = 0;
  C_INT16 Posi1 = 0;
  C_INT16 StrNum = 0;
  std::string JStr;
  std::string CMetab = "CMetab = \"";

  Posi = object.find(CMetab, 0) + CMetab.length() - 1;
  Posi1 = object.find("\", CMember =", 0);
  StrNum = Posi1 - Posi - 1;
  Metab = object.substr(Posi + 1, StrNum);

  Posi = Metab.find(", \"", 0);
  StrNum = Metab.length() - Posi - 3;

  JStr = Metab.substr(Posi + 3, StrNum);

  return JStr;
}

/**
 *  Complie the mpValue in each CDatum
 */
void CDatum::compileDatum(CModel *Model, CState *state, CSteadyStateTask *soln)
{
  C_INT32 Type = 0;
  std::string IStr, JStr;
  int Index;
  CUDFunction *pFunct;

  Type = getObjectType(mObject);

  switch (Type)
    {
#if 0
    case D_UNDEF:             // Fall through as all have no mI and no mJ
    case D_RT:
    case D_INTS:
    case D_FEVAL:
    case D_JEVAL:
    case D_SSIZE:
    case D_RTOL:
    case D_ATOL:
#endif

    case D_SSRES:           // steady-state resolution
      //   mpValue = soln->getSSResAddr();
      fatalError();
      mType = CFLOAT64;
      break;
    case D_UFUNC:           // user functions
      Index = FindUDFunct(mTitle);
      if (Index == -1)
        break;
      pFunct = Copasi->pUDFunctionDB->getFunctions()[Index];
      //pFunct->calcValue(Model);
      mpValue = pFunct->getValueAddr();
      mType = CFLOAT64;
      break;
    case D_DERIV:           // Derive Factor
      //   mpValue = soln->getDerivFactorAddr();
      fatalError();
      mType = CFLOAT64;
      break;
#if 0

    case D_ENDT:
    case D_POINT:
#endif

    case D_EIGMR:           // max real eigenvalue component
      mpValue = &soln->getEigenValues()->getEigen_maxrealpart();
      mType = CFLOAT64;
      break;
    case D_EIGMI:           // max absolute imaginary eigenvalue component
      mpValue = &soln->getEigenValues()->getEigen_maximagpart();
      mType = CFLOAT64;
      break;
    case D_EIGPR:            // number of eigenvalues w/ positive real parts
      mpValue = &soln->getEigenValues()->getEigen_nposreal();
      mType = CFLOAT64;
      break;
    case D_EIGNR:           // number of eigenvalues w/ negative real parts
      mpValue = &soln->getEigenValues()->getEigen_nnegreal();
      mType = CFLOAT64;
      break;
    case D_EIGR:            // number of real eigenvalues
      mpValue = &soln->getEigenValues()->getEigen_nreal();
      mType = CFLOAT64;
      break;
    case D_EIGI:           // number of imaginary eigenvalues
      mpValue = &soln->getEigenValues()->getEigen_nimag();
      mType = CFLOAT64;
      break;
    case D_EIGC:           // number of complex eigenvalues
      mpValue = &soln->getEigenValues()->getEigen_ncplxconj();
      mType = CFLOAT64;
      break;
    case D_EIGZ:           // number of zero eigenvalues
      mpValue = &soln->getEigenValues()->getEigen_nzero();
      mType = CFLOAT64;
      break;
    case D_THIER:           // time hierarchy
      mpValue = &soln->getEigenValues()->getEigen_hierarchy();
      mType = CFLOAT64;
      break;
    case D_STIFF:           // stiffness
      mpValue = &soln->getEigenValues()->getEigen_stiffness();
      mType = CFLOAT64;
      break;
    case D_T:           // time
      mpValue = &state->getTime();
      mType = CFLOAT64;
      break;
    case D_ICONC:             // Fall through as all have mI but no mJ
      IStr = getObjectIStr(mObject, 0);
      Index = Model->findMetab(IStr);
      if (Index == -1)
        break;
      mpValue = Model->getMetabolites()[Index]->getIConcAddr();
      mType = CFLOAT64;
      break;
    case D_SCONC:
    case D_TCONC:
      IStr = getObjectIStr(mObject, 0);
      Index = Model->findMetab(IStr);
      if (Index == -1)
        break;
      mpValue = Model->getMetabolites()[Index]->getConcAddr();
      mType = CFLOAT64;
      break;
    case D_TT:
      IStr = getObjectIStr(mObject, 0);
      Index = Model->findMetab(IStr);
      if (Index == -1)
        break;
      mpValue = Model->getMetabolites()[Index]->getTTAddr();
;
      mType = CFLOAT64;
      break;
    case D_SFLUX:
    case D_TFLUX:
      IStr = getObjectIStr(mObject, 0);
      Index = Model->findStep(IStr);
      if (Index == -1)
        break;
      mpValue = & Model->getReactions()[Index]->getFlux();
      mType = CFLOAT64;
      break;
    case D_VOL:
      IStr = getObjectIStr(mObject, 0);
      Index = Model->findCompartment(IStr);
      if (Index == -1)
        break;
      mpValue = Model->getCompartments()[Index]->getVolumeAddr();
      mType = CFLOAT64;
      break;
    case D_MOIT:
      IStr = getObjectIStr(mObject, 0);
      Index = Model->findMoiety(IStr);
      if (Index == -1)
        break;
      mpValue = Model->getMoieties()[Index]->getNumberAddr();
      mType = CFLOAT64;
      break;
#if 0

    case D_EIGVR:
    case D_EIGVI:
      IStr = getObjectIStr(mObject, 0);
      break;
#endif

    case D_KIN:               // Fall through as all have mI and mJ
      IStr = getObjectIStr(mObject, 1);
      JStr = getObjectJStr(mObject);
      Index = Model->findStep(IStr);
      if (Index == -1)
        break;
      //Index1 = Model->getReactions()[Index]->findPara(JStr);
      //if (Index1 == -1)
      //  break;
      mpValue = & Model->getReactions()[Index]->getParameterValue(JStr);
      mType = CFLOAT64; // TODO: last changes are not tested at all.
      break;
#if 0

    case D_ELAST:
      IStr = getObjectIStr(mObject, 1);
      JStr = getObjectJStr(mObject);
      Index = outputList.Model.FindStep(IStr);
      Index1 = outputList.Model.FindMetab(JStr);
      if ((Index = -1) || (Index1 = -1))
        break;
      mpValue = &(Dxv[outputList.Model.mICol[Index]][outputList.Model.mIRow[Index1]]);
      mType = C_FLOAT64;
      break;
    case D_CCC:
      IStr = getObjectIStr(mObject, 1);
      JStr = getObjectJStr(mObject);
      Index = outputList.Model.FindMetab(IStr);
      Index1 = outputList.Model.FindStep(JStr);
      if ((Index == -1) || (Index1 == -1) || (outputList.Model.mMetabolite[Index].Status == METAB_FIXED))
        break;
      mpValue = &(Gamma[outputList.Model.mIRow[Index]][outputList.Model.mICol[Index1]]);
      mType = C_FLOAT64;
      break;
    case D_FCC:
      IStr = getObjectIStr(mObject, 1);
      JStr = getObjectJStr(mObject);
      Index = outputList.Model.FindMetab(IStr);
      Index1 = outputList.Model.FindMetab(JStr);
      if ((Index == -1) || (Index1 == -1))
        break;
      mpValue = &(FCC[outputList.Model.mICol[Index]][outputList.Model.mICol[Index1]]);
      mType = C_FLOAT64;
      break;
    case D_EIG:
      IStr = getObjectIStr(mObject, 1);

      JStr = getObjectJStr(mObject);

      break;
#endif
    }
}

/**
 * Returns the index of a user defined function
 */
int CDatum::FindUDFunct(std::string title)
{
  int i;

  for (i = 0; i < Copasi->pUDFunctionDB->getItems(); i++)
    if (Copasi->pUDFunctionDB->getFunctions()[i]->getName() == title)
      return i;

  return - 1;
}

/**
 * Dynamically calculate the value of user defined function
 */
void CDatum::calcFunc()
{
  CUDFunction *pFunct;
  int Index;

  Index = FindUDFunct(mTitle);
  if (Index != -1)
    {
      pFunct = Copasi->pUDFunctionDB->getFunctions()[Index];
      pFunct->calcValue();
    }
}
