/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/Attic/CCopasiCallBack.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/03/30 22:09:43 $
   End CVS Header */

#ifndef COPASI_CCopasiCallBack
#define COPASI_CCopasiCallBack

#include <string>
#include <vector>

class CCopasiObject;

class CCopasiCallBackItem
  {
    // Operations
  public:
    CCopasiCallBackItem();

    CCopasiCallBackItem(const std::string & text,
                        const C_FLOAT64 & endValue,
                        const CCopasiObject * pObject);

    CCopasiCallBackItem(const CCopasiCallBackItem & src);

    ~CCopasiCallBackItem();

    // Attributes
  public:
    std::string mText;

    C_FLOAT64 mEndValue;

    const CCopasiObject * mpObject;
  };

class CCopasiCallBack
  {
    // Operations
  public:
    CCopasiCallBack();

    virtual ~CCopasiCallBack();

    virtual bool init();

    virtual bool init(const std::vector< CCopasiCallBackItem > & callBackItemList);

    virtual bool progress();

    virtual bool reset();

    virtual bool finish();

    const std::vector< CCopasiCallBackItem > & getCallBackItemList() const;

    // Attributes
  public:
    std::vector< CCopasiCallBackItem > mCallBackItemList;
  };

#endif // COPASI_CCopasiCallBack
