#include <typeinfo>

#include "CBaseFunction.h"
#include "CKinFunction.h"
#include "utilities/utilities.h"

CBaseFunction::CBaseFunction() 
{mReversible = FALSE;}

CBaseFunction::~CBaseFunction() {}

void CBaseFunction::cleanup() 
{

  for (unsigned C_INT32 i=0; i < mCallParameters.size(); i++)
    {
      if (mCallParameters[i])
        {
	  mCallParameters[i]->cleanup();
	  mCallParameters[i] = NULL;
        }
    }
    
  mCallParameters.clear();
}

void CBaseFunction::copy(const CBaseFunction &in)
{
  CBaseCallParameter *pCallParameter;
    
  mType = in.mType;
  mName = in.mName;
  mDescription = in.mDescription;
  mReversible = in.mReversible;

  for(unsigned C_INT32 i = 0; i < in.mCallParameters.size(); i++)
    {
      pCallParameter = new CBaseCallParameter;
      pCallParameter->copy(*in.mCallParameters[i]);
      mCallParameters.push_back(pCallParameter);
    }
}
    
C_INT32 CBaseFunction::load(CReadConfig & configbuffer,
                            CReadConfig::Mode mode)
{
  C_INT32 Fail = 0;
  CReadConfig::Mode Mode = mode;
    
  if (configbuffer.getVersion() < "4")
    mType = CBaseFunction::USERDEFINED;
  else
    {
      if ((Fail = configbuffer.getVariable("FunctionType", "C_INT32", &mType,
					   Mode)))
	return Fail;
      Mode = CReadConfig::NEXT;
    }

  if ((Fail = configbuffer.getVariable("FunctionName", "string", &mName,
				       Mode)))
    return Fail;
    
  if ((Fail = configbuffer.getVariable("Description", "string", &mDescription)))
    return Fail;
    
  if (configbuffer.getVersion() < "4")
    mReversible = TRUE;
  else
    {
      if ((Fail = configbuffer.getVariable("Reversible", "C_INT16",
					   &mReversible)))
	return Fail;
    }
    
    
  return Fail;
}

C_INT32 CBaseFunction::save(CWriteConfig & configbuffer)
{
  C_INT32 Fail = 0;
    
  if ((Fail = configbuffer.setVariable("FunctionType", "C_INT32", &mType)))
    return Fail;

  if ((Fail = configbuffer.setVariable("FunctionName", "string", &mName)))
    return Fail;
    
  if ((Fail = configbuffer.setVariable("Description", "string", &mDescription)))
    return Fail;
    
  if ((Fail = configbuffer.setVariable("Reversible", "C_INT16", &mReversible)))
    return Fail;
    
  return Fail;
}

void CBaseFunction::setName(const string & name) {mName = name;}

void CBaseFunction::setType(enum Type type) {mType = type;}

void CBaseFunction::setDescription(const string & description) 
{mDescription = description;}

void CBaseFunction::setReversible(C_INT16 reversible) 
{mReversible = reversible;}

string CBaseFunction::getName() const {return mName;}

C_INT32 CBaseFunction::getType() const {return mType;}

string CBaseFunction::getDescription() const {return mDescription;}

C_INT16 CBaseFunction::isReversible() const {return mReversible;}

vector < CBaseCallParameter * > & CBaseFunction::callParameters() 
{return mCallParameters;}

C_FLOAT64 
CBaseFunction::calcValue(const CCopasiVector < CCallParameter > & callParameters) const
{return 0.0;}

pair < C_INT32, C_INT32 > 
CBaseFunction::findIdentifier(const string & name) const
{
  pair < unsigned C_INT32, unsigned C_INT32 > Tuple(-1, -1);
  unsigned C_INT32 j;
  unsigned C_INT32 i;
    
  for (j = 0; j < mCallParameters.size(); j++)
    for (i = 0; i < mCallParameters[j]->mIdentifiers.size(); i ++)
      if (mCallParameters[j]->mIdentifiers[i]->getName() == name) 
	{
	  Tuple.first = j;
	  Tuple.second = i;
	  break;
	}

  return Tuple;
}


/*** CBaseCallParameter ***/

CBaseCallParameter::CBaseCallParameter()
{
  mType = CCallParameter::VECTOR_DOUBLE;
  mCount.setRange(CRange::UNSPECIFIED, CRange::UNSPECIFIED);

  mIdentifierTypes.push_back(0);
}

CBaseCallParameter::~CBaseCallParameter() {}

void CBaseCallParameter::cleanup()
{
  for (unsigned C_INT32 i = 0; i < mIdentifiers.size(); i++ )
    if (mIdentifiers[i]) delete mIdentifiers[i];
    
  mIdentifiers.clear();
}

void CBaseCallParameter::copy(const CBaseCallParameter & in)
{
  CBaseIdentifier * pIdentifier;
    
  mType = in.mType;
  mCount = in.mCount;
  mIdentifierTypes = in.mIdentifierTypes;

  for (unsigned C_INT32 i = 0; i < in.mIdentifiers.size(); i++)
    {
      pIdentifier = new CBaseIdentifier;
      //        memcpy(pIdentifier, in.mIdentifiers[i], sizeof(CBaseIdentifier));
      pIdentifier->setName(in.mIdentifiers[i]->getName());
      pIdentifier->setType(in.mIdentifiers[i]->getType());
      mIdentifiers.push_back(pIdentifier);
    }
}

C_INT32 CBaseCallParameter::noIdentifiers(char identifierType)
{
  if (identifierType) 
    {
      C_INT32 Count = 0;
      for (unsigned C_INT32 i = 0; i < mIdentifiers.size(); i ++)
	if (mIdentifiers[i]->getType() == identifierType) Count++;
      return Count;
    }
  else
    return mIdentifiers.size();
}

void CBaseCallParameter::setType(enum CCallParameter::Type type)
{mType = type;}

void CBaseCallParameter::setCount() 
{mCount.setRange(mIdentifiers.size(), mIdentifiers.size());}

void CBaseCallParameter::setCount(unsigned C_INT32 count) 
{mCount.setRange(count, count);}

void CBaseCallParameter::setCount(unsigned C_INT32 low,
                                  unsigned C_INT32 high)
{mCount.setRange(low, high);}

enum CCallParameter::Type CBaseCallParameter::getType() const
{return mType;}

unsigned C_INT32 CBaseCallParameter::getCountLow() const
{return mCount.getLow();}

unsigned C_INT32 CBaseCallParameter::getCountHigh() const
{return mCount.getHigh();}

vector < C_INT32 > & CBaseCallParameter::identifierTypes()
{return mIdentifierTypes;}

vector < CBaseIdentifier * > & CBaseCallParameter::identifiers()
{return mIdentifiers;}

vector < CBaseIdentifier * > 
CBaseCallParameter::identifiers(char identifierType)
{
  vector < CBaseIdentifier * > Identifiers;

  for (unsigned C_INT32 i = 0; i < mIdentifiers.size(); i ++)
    if (mIdentifiers[i]->getType() == identifierType) 
      Identifiers.push_back(mIdentifiers[i]);

  return Identifiers;
}


/*** CCallParameter ***/

CCallParameter::CCallParameter()
{mType = VECTOR_DOUBLE;}

CCallParameter::~CCallParameter() {}

void CCallParameter::cleanup() {}

void CCallParameter::setType(enum CCallParameter::Type type) {mType = type;}

enum CCallParameter::Type CCallParameter::getType() const {return mType;}

const vector < void * > & CCallParameter::identifiers() const {return mIdentifiers;}

vector < void * > & CCallParameter::identifiers() {return mIdentifiers;}

/*** CRange ***/

CRange::CRange() {mLow = mHigh = CRange::UNSPECIFIED;}

CRange::CRange(unsigned C_INT32 low, unsigned C_INT32 high) 
{mLow = low; mHigh = high; checkRange();}

CRange::~CRange() {}

void CRange::setLow(unsigned C_INT32 low) {mLow = low; checkRange();} 
void CRange::setHigh(unsigned C_INT32 high) {mHigh = high; checkRange();}

void CRange::setRange(unsigned C_INT32 low, unsigned C_INT32 high)
{mLow = low; mHigh = high; checkRange();}

unsigned C_INT32 CRange::getLow() const {return mLow;}

unsigned C_INT32 CRange::getHigh() const {return mHigh;}

C_INT16 CRange::isRange() const
{
  if (mHigh - mLow) return 1;
  else return 0;
}

void CRange::checkRange() const
{
  if (mLow > mHigh) 
    CCopasiMessage(CCopasiMessage::ERROR, MCRange + 1, mLow, mHigh);
}
