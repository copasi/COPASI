#include <string>

#include "CReactionInterface.h" 
//#include "qstring.h"
#include "model/CReaction.h"
#include "model/CModel.h"
#include "model/CChemEqElement.h"
#include "utilities/CGlobals.h"
#include "utilities/CMethodParameter.h"
#include "function/CFunctionDB.h"
#include "report/CKeyFactory.h"
#include "model/CMetabNameInterface.h"

CReactionInterface::CReactionInterface():
    //mpChemEq(NULL),
    mpParameters(NULL)
{emptyString = "";}
CReactionInterface::~CReactionInterface()
{
  pdelete(mpParameters);
  //pdelete(mpChemEq);
}

const std::vector<std::string> & CReactionInterface::getListOfMetabs(std::string role) const
  {
    return mChemEqI.getListOfNames(role);
  }

std::vector< std::string > CReactionInterface::getListOfPossibleFunctions() const
  {
    TriLogic reversible;
    if (isReversible() == false)
      reversible = TriFalse;
    else
      reversible = TriTrue;

    CCopasiVector<CFunction>* pFunctionVector =
      Copasi->pFunctionDB->suitableFunctions(mChemEqI.getMolecularity("SUBSTRATE"),
                                             mChemEqI.getMolecularity("PRODUCT"),
                                             reversible);

    std::vector<std::string> ret;
    ret.clear();
    C_INT32 i, imax = pFunctionVector->size();

    for (i = 0; i < imax; ++i)
      ret.push_back((*pFunctionVector)[i]->getName());
    delete pFunctionVector;

    /* //Here is for verification
     std::vector<std::string>::iterator it = ret.begin();
     std::vector<std::string>::iterator end = ret.end();
     while (it<end)
     {
      QString verification(it->c_str());
      it++;
     }
    */
    return ret;
  }

void CReactionInterface::initFromReaction(const CModel & model, const std::string & key)
{
  mReactionReferenceKey = key;

  const CReaction *rea;
  rea = (CReaction*)(CCopasiContainer*)CKeyFactory::get(key);

  mReactionName = rea->getName();

  //pdelete(mpChemEq);
  mChemEqI.loadFromChemEq(&model, rea->getChemEq());

  mpFunction = &(rea->getFunction());
  pdelete(mpParameters)
  mpParameters = new CFunctionParameters(mpFunction->getParameters());

  loadNameMap(model, *rea);

  C_INT32 i, imax = size();
  mValues.resize(imax);
  for (i = 0; i < imax; ++i)
    if (getUsage(i) == "PARAMETER") mValues[i] = rea->getParameterValue(getParameterName(i));

  mValid = true; //assume a reaction is valid before editing
}

void CReactionInterface::writeBackToReaction(CModel & model) const
  {
    if (!mValid) return; // do nothing

    if (!(*mpParameters == mpFunction->getParameters())) return; // do nothing

    CReaction *rea;
    rea = (CReaction*)(CCopasiContainer*)CKeyFactory::get(mReactionReferenceKey);

    rea->setName(mReactionName); //TODO: what else needs to be done here?

    mChemEqI.writeToChemEq(&model, rea->getChemEq());

    // TODO. check if function has changed since it was set in the R.I.
    rea->setFunction(mpFunction->getName());

    C_INT32 j, jmax;
    C_INT32 i, imax = size();

    for (i = 0; i < imax; ++i)
      {
        if (getUsage(i) == "PARAMETER")
        {rea->setParameterValue(getParameterName(i), mValues[i]);}
        else
          {
            if (isVector(i))
              {
                rea->clearParameterMapping(i);
                jmax = mNameMap[i].size();
                for (j = 0; j < jmax; ++j)
                  rea->addParameterMapping(i, CMetabNameInterface::getMetaboliteKey(&model, mNameMap[i][j]));
                //rea->addParameterMapping(i, model.getMetabolites()[model.findMetab(mNameMap[i][j])]->getKey());
              }
            else
              rea->setParameterMapping(i, CMetabNameInterface::getMetaboliteKey(&model, mNameMap[i][0]));
            //rea->setParameterMapping(i, model.getMetabolites()[model.findMetab(mNameMap[i][0])]->getKey());
          }
      }

    rea->compile(model.getCompartments());
  }

void CReactionInterface::setFunction(const std::string & fn, bool force)
{
  //do nothing if the function is the same as before
  if ((getFunctionName() == fn) && (!force)) return;

if (fn == "") {clearFunction(); return;}

  // save the old parameter names
  CFunctionParameters *oldParameters = mpParameters;

  //get the function
  mpFunction = Copasi->pFunctionDB->findLoadFunction(fn);
  if (!mpFunction) fatalError();
  mpParameters = new CFunctionParameters(mpFunction->getParameters());

  //initialize mValues[]
  //try to keep old values if the name is the same
  std::vector<C_FLOAT64> oldValues = mValues;
  C_INT32 j, jmax = oldValues.size();
  C_INT32 i, imax = size();
  mValues.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      if (getUsage(i) == "PARAMETER")
        {
          for (j = 0; j < jmax; ++j)
            if ((*oldParameters)[j]->getName() == getParameterName(i)) break;

          if (j == jmax) mValues[i] = 0.1;
          else mValues[i] = oldValues[j];
        }
    }

  //initialize mNameMap[]
  mNameMap.clear();
  mNameMap.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      if (!isVector(i)) mNameMap[i].resize(1);
    }

  //guess initial connections between metabs and function parameters
  mValid = true;
  connectFromScratch("SUBSTRATE", true);
  connectFromScratch("PRODUCT", true);
  connectFromScratch("MODIFIER", false); // we can not be pedantic about modifiers
  // because modifiers are not taken into acount
  // when looking for suitable functions

  pdelete(oldParameters);
}

void CReactionInterface::clearFunction()
{
  mpFunction = NULL;
  pdelete(mpParameters);
  mValid = false;

  mValues.clear();
  mNameMap.clear();
}

void CReactionInterface::setChemEqString(const std::string & eq, const std::string & newFunction)
{
  //CModel * pModel = (CModel*) (CKeyFactory::get(mReactionReferenceKey)->getObjectAncestor("Model"));
  mChemEqI.setChemEqString(eq);
  findAndSetFunction(newFunction);
}

void CReactionInterface::setReversibility(bool rev, const std::string & newFunction)
{
  mChemEqI.setReversibility(rev);
  findAndSetFunction(newFunction);
}

void CReactionInterface::reverse(bool rev, const std::string & newFunction)
{
  mChemEqI.setReversibility(rev);
  mChemEqI.reverse();
  findAndSetFunction(newFunction);
}

void CReactionInterface::findAndSetFunction(const std::string & newFunction)
{
  // get list of possible functions and check if the current function
  // or the newFunction is in it.
  std::vector<std::string> fl = getListOfPossibleFunctions();

  C_INT32 i, imax = fl.size();
  std::string currentFunction = getFunctionName(), s = "";
  C_INT32 findresult = -1;

  if (imax == 0)
    {
      setFunction("", true);
      return;
    }

  if (newFunction == "")
    {
      for (i = 0; i < imax; ++i)
        if (fl[i] == currentFunction)
          {
            setFunction(fl[i], true);  //change function - brute force
            return;
          }
    }
  else
    {
      for (i = 0; i < imax; i++)
        if (fl[i] == newFunction)
          {
            setFunction(fl[i], true);  //change function - brute force
            return;
          }
    }

  // if not found then see if there is a best match in the list (i.e. a corresponding rev/irrev function).
  // otherwise just take the first function. no other heuristics yet

  // first prepare the substring - this is very clumsy at the moment
  s = currentFunction.substr(0, currentFunction.find ('(') - 1);     //'-1' so as to strip off the white space before '('

  for (i = 0; i < imax; i++)
    {
      findresult = fl[i].find(s);

      if (findresult >= 0)    // if find succeeds, the return value is likely to be 0
        //if (fl[i].find(s) >= 0) - for some reason this doesn't work
        {
          setFunction(fl[i], true);  //change function - brute force
          return;
        }
    }

  // now i = imax, so take the first function
  setFunction(fl[0], true);  //brute force
}

void CReactionInterface::connectFromScratch(std::string role, bool pedantic)
{
  unsigned C_INT32 j, jmax;
  unsigned C_INT32 i, imax = mpParameters->getNumberOfParametersByUsage(role);
  if (!imax) return;

  // get the list of chem eq elements
  std::vector<std::string> el = getExpandedMetabList(role);

  // get the first parameter with the respective role
  CFunctionParameter::DataType Type;
  unsigned C_INT32 pos = 0;
  Type = mpParameters->getParameterByUsage(role, pos).getType();

  if (Type == CFunctionParameter::VFLOAT64)
    {
      mNameMap[pos - 1] = el;
    }
  else if (Type == CFunctionParameter::FLOAT64)
    {
      if ((imax != el.size()) && pedantic) fatalError();

      if (el.size() > 0)
        mNameMap[pos - 1][0] = el[0];
    else {mNameMap[pos - 1][0] = "unknown"; mValid = false;}

      for (i = 1; i < imax; ++i)
        {
          Type = mpParameters->getParameterByUsage(role, pos).getType();
          if (Type != CFunctionParameter::FLOAT64) fatalError();

          if (el.size() > i)
            mNameMap[pos - 1][0] = el[i];
        else {mNameMap[pos - 1][0] = "unknown"; mValid = false;}
        }
    }
  else fatalError();
}

bool CReactionInterface::isLocked(C_INT32 index) const
{return isLocked(getUsage(index));}

bool CReactionInterface::isLocked(std::string usage) const
  {
    // get number of metabs in chemEq
    unsigned C_INT32 listSize;
    if (usage == "PARAMETER")
      return false;
    else
      listSize = mChemEqI.getListOfNames(usage).size();

    // get number of parameters
    unsigned C_INT32 paramSize = mpParameters->getNumberOfParametersByUsage(usage);

    // get index of first parameter
    unsigned C_INT32 pos = 0;
    mpParameters->getParameterByUsage(usage, pos); --pos;

    // decide
    if (isVector(pos))
      {
        if (paramSize != 1) fatalError();
        return true;
      }
    else
      {
        if (listSize <= 1) return true; else return false;
      }
  }

void CReactionInterface::setMetab(C_INT32 index, std::string mn)
{
  std::string usage = getUsage(index);
  C_INT32 listSize;
  if (usage == "PARAMETER")
    return;
  else
    listSize = mChemEqI.getListOfNames(usage).size();

  if (isVector(index)) mNameMap[index].push_back(mn);
  else
    {
      mNameMap[index][0] = mn;

      // if we have two parameters of this usage change the other one.
      if ((listSize == 2) && (mpParameters->getNumberOfParametersByUsage(usage) == 2))
        {
          // get index of other parameter
          unsigned C_INT32 pos = 0;
          mpParameters->getParameterByUsage(usage, pos);
          if ((pos - 1) == index) mpParameters->getParameterByUsage(usage, pos);
          --pos;

          // get name if other metab
          std::vector<std::string> ml = getListOfMetabs(usage);
          std::string otherMetab;
          if (ml[0] == mn) otherMetab = ml[1]; else otherMetab = ml[0];

          // set other parameter
          mNameMap[pos][0] = otherMetab;
        }
    }
}

std::vector<std::string> CReactionInterface::getExpandedMetabList(const std::string & role) const
  {
    const std::vector<std::string> & names = mChemEqI.getListOfNames(role);
    const std::vector<C_FLOAT64> & mults = mChemEqI.getListOfMultiplicities(role);

    //if (role == "SUBSTRATE") el = &(mpChemEq->getSubstrates());
    //else if (role == "PRODUCT") el = &(mpChemEq->getProducts());
    //else if (role == "MODIFIER") el = &(mpChemEq->getModifiers());
    //else fatalError();

    unsigned C_INT32 j, jmax;
    unsigned C_INT32 i, imax = names.size();

    std::vector<std::string> ret;

    for (i = 0; i < imax; ++i)
      {
        if (role == "MODIFIER") jmax = 1;
        else jmax = mults[i];

        for (j = 0; j < jmax; ++j)
          ret.push_back(names[i]);
      }
    return ret;
  }

void CReactionInterface::loadNameMap(const CModel & model, const CReaction & rea)
{
  std::vector< std::vector<std::string> >::const_iterator it;
  std::vector< std::vector<std::string> >::const_iterator iEnd;
  std::vector<std::string>::const_iterator jt;
  std::vector<std::string>::const_iterator jEnd;

  std::string metabName;
  std::vector<std::string> SubList;

  mNameMap.clear();

  it = rea.getParameterMappings().begin();
  iEnd = rea.getParameterMappings().end();
  for (; it != iEnd; ++it)
    {
      SubList.clear();
      for (jt = it->begin(), jEnd = it->end(); jt != jEnd; ++jt)
        {
          metabName = CMetabNameInterface::getDisplayName(&model, *jt);
          if (metabName != "")
            SubList.push_back(metabName);
          else
            SubList.push_back(*jt);
        }
      mNameMap.push_back(SubList);
    }
}

bool CReactionInterface::createMetabolites(CModel & model) const
  {
    return mChemEqI.createNonExistingMetabs(&model);
  }
