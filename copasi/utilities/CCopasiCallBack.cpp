/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/Attic/CCopasiCallBack.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/03/30 22:09:43 $
   End CVS Header */

#include "copasi.h"

#include "CCopasiCallBack.h"
#include "report/CCopasiObject.h"

CCopasiCallBackItem::CCopasiCallBackItem():
    mText(""),
    mEndValue(0.0),
    mpObject(NULL)
{}

CCopasiCallBackItem::CCopasiCallBackItem(const std::string & text,
    const C_FLOAT64 & endValue,
    const CCopasiObject * pObject):
    mText(text),
    mEndValue(endValue),
    mpObject(pObject)
{}

CCopasiCallBackItem::CCopasiCallBackItem(const CCopasiCallBackItem & src):
    mText(src.mText),
    mEndValue(src.mEndValue),
    mpObject(src.mpObject)
{}

CCopasiCallBackItem::~CCopasiCallBackItem();

CCopasiCallBack::CCopasiCallBack():
    mCallBackItemList()
{}

CCopasiCallBack::~CCopasiCallBack() {}

bool CCopasiCallBack::init()
{return true;}

bool CCopasiCallBack::init(const std::vector< CCopasiCallBackItem > & callBackItemList)
{
  mCallBackItemList = callBackItemList;
  return true;
}

bool CCopasiCallBack::progress()
{return true;}

bool CCopasiCallBack::reset()
{return true;}

bool CCopasiCallBack::finish()
{return true;}

const std::vector< CCopasiCallBackItem > & CCopasiCallBack::getCallBackItemList() const
  {return mCallBackItemList;}
